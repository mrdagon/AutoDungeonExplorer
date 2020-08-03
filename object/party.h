//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
namespace SDX_BSC
{
	using namespace SDX;

	//テンプレートで循環参照解決する場合
	template<typename TGuild>
	class Party
	{
	private:

	public:
		Party() :
			isボス戦(false)
		{
			味方.reserve(6);
			敵.reserve(6);
			魔物.reserve(6);

			for (auto& it : メンバー)
			{
				it = nullptr;
			}
		}

		int ギルドID;

		Dungeon* 探索先 = nullptr;
		Dungeon* 探索先予約 = nullptr;
		OrderType 探索指示 = OrderType::探索;

		std::vector<Monster> 魔物;
		Hunter* メンバー[CV::パーティ人数];

		std::vector<Fighter*> 味方;
		std::vector<Fighter*> 敵;

		int 獲得素材[CV::最大素材種];

		double 獲得経験値;
		int 獲得財宝数;
		int 獲得地図数;
		int 撃破ボス数;

		ExplorerType 探索状態 = ExplorerType::編成中;
		int 待ち時間 = 0;//移動、戦闘後、素材回収中などの待ち時間

		bool isボス戦 = false;

		int 部屋ID = 0;

		//演出用
		int 移動量 = 0;
		int 暗転 = 0;
		Image* 発見物 = nullptr;//地図、石版、鉱脈、木

		int 発見物X座標 = 0;

		int 戦闘中行動待機 = 0;

		void 基礎ステ再計算()
		{
			味方.clear();
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] == nullptr) { continue; }

				味方.push_back(メンバー[a]);
				メンバー[a]->Pスキル.clear();
			}

			//パーティスキルや装備品スキル等の計算
			for (int a = 0; a < (int)味方.size(); a++)
			{
				味方[a]->隊列ID = a;
				味方[a]->基礎ステータス計算();
			}
			for (int a = 0; a < (int)味方.size(); a++)
			{
				味方[a]->基礎Pスキル補正(味方, 敵);
			}
		}

		void 探索開始()
		{
			暗転 = 255;
			移動量 = 0;
			発見物X座標 = 0;
			発見物 = nullptr;

			探索状態 = ExplorerType::移動中;
			待ち時間 = 60;

			//獲得素材数リセット
			獲得経験値 = 0;
			for (auto& it : 獲得素材) { it = 0; }
			獲得財宝数 = 0;
			獲得地図数 = 0;
			撃破ボス数 = 0;

			//パーティメンバーの体力回復、ステータス再計算等
			基礎ステ再計算();

			//０人パーティは全滅扱いにする
			if (味方.size() == 0) { 探索状態 = ExplorerType::全滅中; }
		}

		void 探索終了()
		{
			//素材獲得

			for (int a = 0; a < CV::最大素材種; a++)
			{
				if (獲得素材[a] > 0)
				{
					TGuild::P->素材数[a] += 獲得素材[a];
					TGuild::P->総素材 += 獲得素材[a];
					TGuild::P->is素材発見[a] = true;
				}
			}

			//経験値獲得とレベルアップ
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] == nullptr) { continue; }

				メンバー[a]->経験値 += 獲得経験値 * TGuild::P->戦闘経験補正;
				メンバー[a]->レベルアップ判定();
			}

			if (探索先予約 != nullptr)
			{
				探索先 = 探索先予約;
				探索先予約 = nullptr;
			}

		}

		void 探索処理()
		{
			//エフェクト更新
			for (auto& it : 味方)
			{
				it->エフェクト更新();
			}
			for (auto& it : 敵)
			{
				it->エフェクト更新();
			}

			//探索終了判定
			if (Game::時間 == Game::終業時間)
			{
				撤退開始();
			}
			if (Game::時間 == Game::起床時間)
			{
				探索状態 = ExplorerType::編成中;
			}

			//待機中(収集中、戦闘後待機、宝部屋etc)				
			switch (探索状態)
			{
			case ExplorerType::戦闘中:
				戦闘処理();
				break;
			case ExplorerType::移動中:
				待ち時間--;
				移動量 += 2;
				if (待ち時間 == 0) { 部屋選び(); }
				break;
			case ExplorerType::収集中:
				収集処理();
				break;
			case ExplorerType::撤退中:
				撤退処理();
				break;
			case ExplorerType::全滅中:
				if (暗転 > 128)
				{
					暗転--;
				}
			case ExplorerType::リザルト中:
				//特に処理しない
				break;
			}
		}

		bool 探索先前後(bool is進む)
		{
			if (is進む)
			{
				for (auto& it : Dungeon::data)
				{
					if (it.ID > 探索先->ID&& it.is発見)
					{
						探索先 = &it;
						return true;
					}
				}
			}
			else {

				for (int a = (int)Dungeon::data.size() - 1; a >= 0; a--)
				{
					if (Dungeon::data[a].ID < 探索先->ID && Dungeon::data[a].is発見)
					{
						探索先 = &Dungeon::data[a];
						return true;
					}
				}
			}

			return false;
		}

		//部屋選択関係の処理
		void 部屋選び()
		{
			std::vector<int> room_deck;
			room_deck.clear();

			switch (探索指示)
			{
			case OrderType::探索:
				Set部屋抽選リスト(room_deck, false);
				break;
			case OrderType::ボス://発見済みならボス戦へ
				Set部屋抽選リスト(room_deck, true);
				break;
			}

			//抽選
			部屋ID = room_deck[Rand::Get((int)room_deck.size() - 1)];
			部屋選択後処理();
		}

		void Set部屋抽選リスト(std::vector<int>& room_deck, bool isボス戦)
		{
			if (探索先->isボス発見 && 探索先->部屋[0].種類 == RoomType::ボス && isボス戦 && !探索先->部屋[0].is入場)
			{
				room_deck.push_back(0);
				return;
			}

			//地図部屋確定
			if (探索先->探索率 > Game::地図発見探索率&& 探索先->部屋[1].地図 > 0 && !探索先->部屋[1].is入場)
			{
				room_deck.push_back(1);
				return;
			}

			//未探索部屋から抽選
			if (Rand::Coin(TGuild::P->未開探索))
			{
				for (int a = 1; a < 探索先->部屋数; a++)
				{
					if (探索先->部屋[a].is入場 || 探索先->部屋[a].is探索) { continue; }
					room_deck.push_back(a);
				}
			}

			if (room_deck.size() > 0) { return; }

			//未探索部屋0の場合
			for (int a = 1; a < 探索先->部屋数; a++)
			{
				if (探索先->部屋[a].is入場)
				{
					continue;
				}

				room_deck.push_back(a);
			}
		}

		void 部屋選択後処理()
		{
			//入室フラグON
			探索先->部屋[部屋ID].is入場 = true;

			switch (探索先->部屋[部屋ID].種類)
			{
			case RoomType::ザコ:
				探索状態 = ExplorerType::戦闘中;
				isボス戦 = false;
				戦闘開始(5);
				break;
			case RoomType::素材:
				探索状態 = ExplorerType::収集中;
				収集開始();
				break;
			case RoomType::財宝:
				探索状態 = ExplorerType::戦闘中;
				isボス戦 = false;
				戦闘開始(6);
				break;
			case RoomType::地図:
				探索状態 = ExplorerType::戦闘中;
				isボス戦 = false;
				戦闘開始(6);
				break;
			case RoomType::ボス:
				探索状態 = ExplorerType::戦闘中;
				isボス戦 = true;
				戦闘開始(1);
				break;
			}

		}

		//素材収集関係
		void 収集開始()
		{
			//素材獲得処理
			int 素材ID = 0;
			int 素材数 = 1;

			double レア素材確率 = 探索先->レア収集率;
			double 素材数増加率 = 0;

			for (auto& it : 味方)
			{
				レア素材確率 += it->レア素材収集補正;
				素材数増加率 += it->素材収集量;
			}

			if (Rand::Coin(素材数増加率))
			{
				素材数++;
			}

			if (Rand::Coin(レア素材確率))
			{
				素材ID = 探索先->レア収集素材[Rand::Get(CV::最大収集種 - 1)];
			}
			else {
				素材ID = 探索先->収集素材[Rand::Get(CV::最大収集種 - 1)];
			}

			素材獲得(素材ID, 素材数);

			部屋探索完了();
			探索状態 = ExplorerType::収集中;
			待ち時間 = 120;

			発見物X座標 = 120;
		}

		void 収集処理()
		{
			if (発見物X座標 > 0)
			{
				移動量 += 2;
				発見物X座標 -= 2;
			}

			待ち時間--;
			if (待ち時間 == 0)
			{
				発見物 = nullptr;
				探索状態 = ExplorerType::移動中;
				待ち時間 = 60;
			}
		}

		void 素材獲得(int 素材ID, int 素材数)
		{
			獲得素材[素材ID] += 素材数;

			

			if (発見物 == nullptr) { 発見物 = &MIcon::アイコン[Material::data[素材ID].アイコン]; }
		}

		//戦闘関係
		void 戦闘開始(int 敵数)
		{
			敵.clear();
			魔物.clear();

			//敵の生成
			if (isボス戦 == true)
			{
				敵数 = 1;
				魔物.emplace_back(探索先->ボスモンスター[0]);
			}
			else
			{
				for (int a = 0; a < 敵数; a++)
				{
					int mn = Rand::Get(2);
					魔物.emplace_back(探索先->雑魚モンスター[mn]);
				}
			}

			敵.resize(敵数);

			for (int a = 0; a < 敵数; a++)
			{
				敵[a] = &魔物[a];
				敵[a]->隊列ID = a;
			}

			//戦闘開始時のパッシブ
			for (auto& it : 味方)
			{
				it->戦闘開始(味方, 敵);
			}

			for (auto& it : 敵)
			{
				it->戦闘開始(敵, 味方);
			}
		}

		void 戦闘処理()
		{
			//全員の全スキルのCT計算
			if (戦闘中行動待機 > 0)
			{
				戦闘中行動待機--;
				return;
			}

			bool isBreak = false;

			while (true)
			{
				for (auto& it : 味方)
				{
					it->ターン経過();
				}
				for (auto& it : 敵)
				{
					it->ターン経過();
				}

				for (auto& it : 味方)
				{
					if (it->Aスキル使用チェック(味方, 敵) == true) { isBreak = true;  break; }
				}
				if (isBreak) { break; }

				for (auto& it : 敵)
				{
					if (it->Aスキル使用チェック(敵, 味方) == true) { isBreak = true;  break; }
				}
				if (isBreak) { break; }

			}

			戦闘終了判定();
			戦闘中行動待機 = 15;
		}

		bool 戦闘終了判定()
		{
			//味方全滅or逃走
			int is生存 = false;
			for (auto& it : 味方)
			{
				if (it->現在HP > 0)
				{
					is生存 = true;
				}
			}

			if (!is生存)
			{
				戦闘敗北();
				探索先->部屋[部屋ID].is入場 = false;
				return true;
			}
			//敵全滅
			is生存 = false;
			for (auto& it : 敵)
			{
				if (it->現在HP > 0)
				{
					is生存 = true;
				}
			}

			if (!is生存)
			{
				戦闘勝利();
				探索先->部屋[部屋ID].is入場 = false;
				return true;
			}

			return false;
		}

		void 戦闘勝利()
		{
			//クエスト処理
			TGuild::P->クエスト進行(QuestType::雑魚討伐, (int)敵.size());

			//特殊部屋攻略
			switch (探索先->部屋[部屋ID].種類)
			{
			case RoomType::ボス:
				探索先->isボス生存 = false;
				探索先->部屋[部屋ID].種類 = RoomType::ザコ;
				撃破ボス数++;
				TGuild::P->総討伐++;
				TGuild::P->クエスト進行(QuestType::ボス討伐, 探索先->ID);
				TGuild::P->クエスト進行(QuestType::固定ボス討伐, 探索先->ID);
				EventLog::Add(0, Game::日付, LogDetailType::ボス討伐, 探索先->ID);
				if (探索先->部屋[部屋ID].地図 < 0)
				{
					財宝獲得();
				}
				break;
			case RoomType::地図:
				探索先->部屋[部屋ID].種類 = RoomType::ザコ;
				break;
			case RoomType::財宝:
				探索先->部屋[部屋ID].種類 = RoomType::ザコ;
				財宝獲得();
				break;
			}

			地図発見();
			部屋探索完了();

			//体力回復
			for (int a = 0; a < (int)味方.size(); a++)
			{
				味方[a]->現在HP += (int)(味方[a]->戦闘後回復 * 味方[a]->補正ステ[StatusType::Hp]);
				味方[a]->現在HP = std::min(味方[a]->現在HP, 味方[a]->補正ステ[StatusType::Hp]);
				味方[a]->Eダメージ = -(int)(味方[a]->戦闘後回復 * 味方[a]->補正ステ[StatusType::Hp]);
				味方[a]->Eダメージ時間 = 16;
			}

			//経験値獲得 - 素材獲得処理
			for (auto& it : 魔物)
			{
				獲得経験値 += it.経験値;

				int 素材数 = 1;
				int 素材ID = 0;

				double レア率 = it.種族->レア素材率;
				double 素材数増加率 = 0;

				for (auto& it : 味方)
				{
					レア率 += it->レア素材剥取補正;
					素材数増加率 += it->素材剥取量;
				}

				if (Rand::Coin(素材数増加率))
				{
					素材数++;
				}

				if (Rand::Coin(レア率))
				{
					素材ID = it.種族->レア素材;
				}
				else {
					素材ID = it.種族->通常素材;
				}

				素材獲得(素材ID, 素材数);
			}



			敵.clear();
			魔物.clear();
			探索状態 = ExplorerType::収集中;
			待ち時間 = 60;
		}

		void 戦闘敗北()
		{
			int ザコ討伐数 = 0;
			for (auto& it : 敵)
			{
				ザコ討伐数++;
			}
			TGuild::P->クエスト進行(QuestType::雑魚討伐, ザコ討伐数);


			探索先->部屋[部屋ID].is入場 = false;
			探索状態 = ExplorerType::全滅中;
			MSound::効果音[SE::全滅].Play();
			TGuild::P->総全滅++;
		}

		void 地図発見()
		{
			if (探索先->部屋[部屋ID].地図 <= 0) { return; }

			探索先->発見地図++;
			発見物 = &MIcon::アイコン[IconType::地図];
			獲得地図数++;
			if (!Dungeon::data[探索先->部屋[部屋ID].地図].is発見)
			{
				Dungeon::data[探索先->部屋[部屋ID].地図].is発見 = true;
				MSound::効果音[SE::地図発見].Play();
				TGuild::P->総地図++;
				TGuild::P->クエスト進行(QuestType::ダンジョン発見, 探索先->ID);
				EventLog::Add(0, Game::日付, LogDetailType::地図発見, 探索先->ID);
			}

			探索先->部屋[部屋ID].地図 = -1;
		}

		void 財宝獲得()
		{
			探索先->発見財宝++;
			獲得財宝数++;
			発見物 = &MIcon::アイコン[IconType::宝箱];
		}

		void 撤退開始()
		{
			if (探索状態 == ExplorerType::戦闘中)
			{
				int ザコ討伐数 = 0;
				for (auto& it : 敵)
				{
					if (it->現在HP <= 0)
					{
						ザコ討伐数++;
					}
				}

				TGuild::P->クエスト進行(QuestType::雑魚討伐, ザコ討伐数);

				//倒した敵の分だけ素材獲得
			}
			else {
				//戦闘中以外は敵消去
				魔物.clear();
				敵.clear();
			}

			for (auto& it : 味方)
			{
				if (it->現在HP <= 0) { continue; }
				it->エフェクト移動(-3, 10000);
			}

			探索状態 = ExplorerType::撤退中;
			探索先->部屋[部屋ID].is入場 = false;
			待ち時間 = 120;
		}

		void 撤退処理()
		{
			待ち時間--;
			if (待ち時間 == 0)
			{
				探索終了();
				探索状態 = ExplorerType::リザルト中;
			}
		}

		void 部屋探索完了()
		{
			探索先->部屋[部屋ID].is探索 = true;
			探索先->部屋[部屋ID].is入場 = false;
			探索先->探索率計算();

			if (探索先->探索率 > Game::ボス発見探索率 && !探索先->isボス発見)
			{
				MSound::効果音[SE::ボス発見].Play();
				探索先->isボス発見 = true;
				EventLog::Add(0, Game::日付, LogDetailType::ボス発見, 探索先->ID);
			}
		}
	};


}