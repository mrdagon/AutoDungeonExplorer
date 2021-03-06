//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ギルド*/
	class Guild
	{
	private:
	public:
		//内部クラスにして循環参照解決する場合
		class Party
		{
		private:

		public:
			Party() :
				isボス戦(false)
			{
				魔物.reserve(6);

				for (auto& it : メンバー)
				{
					it = nullptr;
				}
			}

			int パーティID;

			Dungeon* 探索先 = nullptr;
			Dungeon* 探索先予約 = nullptr;
			OrderType 探索指示 = OrderType::探索;

			std::vector<Monster> 魔物;
			Hunter* メンバー[CV::パーティ人数];

			std::vector<Fighter*> 味方;
			std::vector<Fighter*> 敵;

			CraftType 発見素材種;
			int 獲得素材[CV::最大素材種];
			int 獲得レア素材[CV::最大素材種];

			double 獲得経験値;
			int 獲得石版数;
			int 獲得地図数;
			int 撃破ボス数;

			ExplorerType 探索状態 = ExplorerType::編成中;
			int 待ち時間 = 0;//移動、戦闘後、素材回収中などの待ち時間

			bool isボス戦 = false;

			int 部屋ID = 0;

			//演出用
			int 移動量 = 0;
			int 暗転 = 0;
			Image* 発見物 = nullptr;//地図、宝箱、鉱脈、木
			int 発見物X座標 = 0;

			int 戦闘中行動待機 = 0;

			void 基礎ステ再計算()
			{
				味方.clear();
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					味方.push_back(メンバー[a]);
					メンバー[a]->パッシブスキル.clear();
				}

				//パーティスキルや装備品スキル等の計算
				for (int a = 0; a < (int)味方.size(); a++)
				{
					味方[a]->隊列ID = a;
					味方[a]->パーティID = パーティID;
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
				待ち時間 = CV::探索開始時待ち時間;

				//獲得素材数リセット
				獲得経験値 = 0;
				for (auto& it : 獲得素材) { it = 0; }
				for (auto& it : 獲得レア素材) { it = 0; }
				獲得石版数 = 0;
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
						Guild::P->素材数[a] += 獲得素材[a];
						Guild::P->資金 += Material::data[a].価格 * 獲得素材[a];
						Guild::P->総素材 += 獲得素材[a];
						Guild::P->is素材発見[a] = true;
					}
					if (獲得レア素材[a] > 0)
					{
						Guild::P->レア素材数[a] += 獲得レア素材[a];
						Guild::P->資金 += Material::data[a].価格 * 獲得レア素材[a] * CV::レア素材値段倍率;
						Guild::P->総素材 += 獲得レア素材[a];
						Guild::P->is素材発見[a] = true;
					}
				}

				//経験値獲得とレベルアップ
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					メンバー[a]->経験値 += 獲得経験値 * Guild::P->戦闘経験補正;
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
					移動量 += CV::探索移動速度;
					if (待ち時間 == 0) { 部屋選び(); }
					break;
				case ExplorerType::収集中:
					収集処理();
					break;
				case ExplorerType::撤退中:
					撤退処理();
					break;
				case ExplorerType::全滅中:
					if (暗転 > CV::全滅暗さ)
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
				if (探索先->探索率 > Game::地図発見探索率 && !探索先->部屋[1].is入場)
				{
					room_deck.push_back(1);
					return;
				}

				//未探索部屋から抽選
				if (Rand::Coin(Guild::P->未開探索))
				{
					for (int a = 1; a < 探索先->部屋.size(); a++)
					{
						if (探索先->部屋[a].is入場 || 探索先->部屋[a].is探索) { continue; }
						room_deck.push_back(a);
					}
				}

				if (room_deck.size() > 0) { return; }

				//未探索部屋0の場合
				for (int a = 1; a < 探索先->部屋.size(); a++)
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
				部屋探索完了();

				探索状態 = ExplorerType::収集中;

				double coin = Rand::Get(3);

				switch (Rand::Get(3))
				{
				case 0:
					発見素材種 = CraftType::木材;
					発見物 = &MIcon::アイコン[IconType::探索_伐採];
					break;
				case 1:
					発見素材種 = CraftType::木材;
					発見物 = &MIcon::アイコン[IconType::探索_採掘];
					break;
				case 2:
					発見素材種 = CraftType::木材;
					発見物 = &MIcon::アイコン[IconType::探索_採掘];
					break;
				default:
					break;
				}

				待ち時間 = CV::収集待機A;
				発見物X座標 = CV::収集待機A;
			}

			void 収集処理()
			{
				if (発見物X座標 > 0)
				{
					移動量 += CV::探索移動速度;
					発見物X座標 -= CV::探索移動速度;

					if (発見物X座標 == 0)
					{
						素材収集処理();
					}
				}

				待ち時間--;
				if (待ち時間 == 0)
				{
					発見物 = nullptr;
					探索状態 = ExplorerType::移動中;
					待ち時間 = CV::収集待機B;
				}
			}

			void 素材収集処理()
			{
				//素材数とレア率を計算
				int 素材ID = 0;
				int 素材数 = Rand::Get(2,3);

				double レア素材確率 = 0;
				double 素材数増加率 = 0;

				//パッシブ補正
				for (auto& it : 味方)
				{
					レア素材確率 += it->レア素材収集補正;
					素材数増加率 += it->素材収集量;
				}

				//素材獲得処理
				if (Rand::Coin(素材数増加率))
				{
					素材数++;
				}

				for (int a = 0; a < 素材数; a++)
				{
					int id = Rand::Get(CV::最大収集種 - 1);

					if (発見素材種 == CraftType::木材)
					{
						//素材ID = 探索先->伐採素材[id];
					} else {
						//素材ID = 探索先->採掘素材[id];
					}

					if (Rand::Coin(レア素材確率))
					{
						獲得レア素材[素材ID] += 素材数;
					}else {
						獲得素材[素材ID] += 素材数;
					}

					Effect::素材[パーティID].emplace_back(Material::data[素材ID].image , a);
				}
			}

			void 素材剥取処理(Monster& it)
			{
				//素材獲得処理
				int 素材ID = 0;
				double レア率 = it.種族->レア素材率;
				double 素材数増加率 = 0;

				for (auto& it : 味方)
				{
					レア率 += it->レア素材剥取補正;
					素材数増加率 += it->素材剥取量;
				}

				int 素材数 = Rand::Coin(素材数増加率) ? 2 : 1;
			
				for (int a = 0; a < 素材数; a++)
				{
					if (Rand::Coin(0.5) && !it.isボス) { continue; }//とりあえず基本ドロップ率50%

					if (Rand::Coin(レア率))
					{
						獲得レア素材[素材ID]++;
					} else {
						獲得素材[素材ID]++;
					}

					Effect::素材[パーティID].emplace_back( Material::data[素材ID].image,a,it.隊列ID);
				}

				獲得経験値 += it.経験値;
			}

			//戦闘関係
			void 戦闘開始(int 敵数)
			{
				敵.clear();
				魔物.clear();

				//敵の生成
				if (isボス戦 == true)
				{
					MMusic::BGM[BGMType::通常ボス].Play();
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
					敵[a]->パーティID = パーティID;
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

				戦闘中行動待機 = CV::戦闘開始後待ち時間;
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
					//スキルCT上がってるかチェック
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

					//スキルクールタイムとバフ/デバフ持続計算
					for (auto& it : 味方)
					{
						it->ターン経過();
					}
					for (auto& it : 敵)
					{
						it->ターン経過();
					}				
				}

				for (auto& it : 魔物)
				{
					if (it.is死亡 == false && it.現在HP <= 0)
					{
						it.is死亡 = true;
						素材剥取処理(it);
					}
				}


				戦闘終了判定();
				戦闘中行動待機 = CV::戦闘1ターン待ち時間;
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
				Guild::P->クエスト進行(QuestType::魔物討伐, (int)敵.size());

				//特殊部屋攻略
				switch (探索先->部屋[部屋ID].種類)
				{
				case RoomType::ボス:
					if (Config::isボス戦時等速 == true)
					{
						Game::ゲームスピード = 1;
					}

					MMusic::BGM[BGMType::探検中].Play();
					探索先->isボス生存 = false;
					探索先->部屋[部屋ID].種類 = RoomType::ザコ;
					撃破ボス数++;
					Guild::P->総討伐++;
					Guild::P->クエスト進行(QuestType::ボス討伐, 探索先->ID);
					Guild::P->クエスト進行(QuestType::固定ボス討伐, 探索先->ID);
					EventLog::Add(0, Game::日付, LogDetailType::ボス討伐, 探索先->ID);
					//if (探索先->部屋[部屋ID].地図 < 0)
					//{
					//	財宝獲得();
					//}
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
					味方[a]->現在HP += (int)(味方[a]->戦闘後回復 * 味方[a]->補正ステ[StatusType::HP]);
					味方[a]->現在HP = std::min(味方[a]->現在HP, 味方[a]->補正ステ[StatusType::HP]);
					味方[a]->エフェクトダメージ(-(int)(味方[a]->戦闘後回復 * 味方[a]->補正ステ[StatusType::HP]));
				}

				探索状態 = ExplorerType::収集中;
				待ち時間 = CV::戦闘終了後待ち時間;
			}

			void 戦闘敗北()
			{
				if (探索先->部屋[部屋ID].種類 == RoomType::ボス)
				{
					MMusic::BGM[BGMType::探検中].Play();
				}

				int ザコ討伐数 = 0;
				for (auto& it : 敵)
				{
					ザコ討伐数++;
				}
				Guild::P->クエスト進行(QuestType::魔物討伐, ザコ討伐数);

				探索先->部屋[部屋ID].is入場 = false;
				探索状態 = ExplorerType::全滅中;
				MSound::効果音[SE::全滅].Play();
				Guild::P->総全滅++;
			}

			void 地図発見()
			{
				//if (探索先->部屋[部屋ID].地図 <= 0) { return; }

				//探索先->発見地図++;
				発見物 = &MIcon::アイコン[IconType::地図];
				獲得地図数++;
				/*if (!Dungeon::data[探索先->部屋[部屋ID].地図].is発見)
				{
					Dungeon::data[探索先->部屋[部屋ID].地図].is発見 = true;
					MSound::効果音[SE::地図発見].Play();
					Guild::P->総地図++;
					Guild::P->クエスト進行(QuestType::ダンジョン発見, 探索先->ID);
					EventLog::Add(0, Game::日付, LogDetailType::地図発見, 探索先->ID);
				}*/

				//探索先->部屋[部屋ID].地図 = -1;
			}

			void 財宝獲得()
			{
				//探索先->発見財宝++;
				獲得石版数++;
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

					Guild::P->クエスト進行(QuestType::魔物討伐, ザコ討伐数);
				}

				for (auto& it : 味方)
				{
					if (it->現在HP <= 0) { continue; }
					it->エフェクト移動(-3, 10000);
				}

				探索状態 = ExplorerType::撤退中;
				探索先->部屋[部屋ID].is入場 = false;
				待ち時間 = CV::撤退後待ち時間;
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

			bool SaveLoad(File& ファイル, FileMode 読み書きモード)
			{

			}

		};

		int 素材数[CV::最大素材種];
		int レア素材数[CV::最大素材種];
		bool is素材発見[CV::最大素材種];

		double 資金 = 123456789;
		MSkillType 選択戦術 = MSkillType::COUNT;
		int 名声 = 100;

		//従業員一覧
		std::vector<Hunter> 探索要員;

		//Party test;
		Party 探索パーティ[CV::最大パーティ数];
		std::vector<Hunter*> ギルメン控え;


		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 投資Lv;
		EnumArray<double, ManagementType> 投資経験値;

		int 集客力 = 100;//10で割った数値が一日の来客期待値

		//キャラクリ関係
		std::string 求人名前 = "ナナーシ";
		ID_Job 求人職業 = 0;

		//経営戦術効果
		double 戦闘経験補正 = 1.0;

		double 素材節約 = 0.0;//確率で素材消費0
		double 未開探索 = Game::基礎未探索部屋発見率;//未探索部屋抽選補正

		//装備品
		int 装備所持数[CV::装備種] = { 0 };

		EnumArray < bool, ItemType> is新開発タブ;

		//各種記録_Record
		int 総石版 = 0;
		int 総人数 = 0;

		int 総素材 = 0;//探索後増加
		int 総地図 = 0;//発見時増加
		int 総討伐 = 0;//討伐時増加
		int 総全滅 = 0;//全滅時増加

		//日別記録
		std::vector<int> R団員;
		std::vector<double> R資金;
		std::vector<int> R販売;
		std::vector<int> R製造;
		std::vector<int> R素材在庫;
		std::vector<int> R地図数;
		std::vector<int> R討伐数;
		std::vector<int> R全滅数;
		std::vector<int> R名声;

		inline static Guild* P;//プレイヤーのギルド

		Guild()
		{
			for (int a = 0; a < CV::最大パーティ数; a++)
			{
				探索パーティ[a].パーティID = a;
			}
		}

		//人事関係処理
		void 求人リロール()
		{
			std::string 求人名前 = "デフォ子";
			求人職業 = Rand::Get(4);
		}

		void 求人採用()
		{
			探索要員.emplace_back();
			探索要員.back().Make((int)探索要員.size()-1, 求人職業, 1, 求人名前);
			ギルメン控え.push_back(&探索要員.back());
			求人リロール();
		}

		void 除名(int ID)
		{
			if (ID >= 0)
			{
				//探索パーティから除名
				装備所持数[探索パーティ[ID / 5].メンバー[ID % 5]->装備[0]->ID]++;
				装備所持数[探索パーティ[ID / 5].メンバー[ID % 5]->装備[1]->ID]++;
				装備所持数[探索パーティ[ID / 5].メンバー[ID % 5]->装備[2]->ID]++;

				探索パーティ[ID / 5].メンバー[ID % 5] = nullptr;
			} else {
				//控えから除名
				装備所持数[ギルメン控え[-(ID + 1)]->装備[0]->ID]++;
				装備所持数[ギルメン控え[-(ID + 1)]->装備[1]->ID]++;
				装備所持数[ギルメン控え[-(ID + 1)]->装備[2]->ID]++;

				ギルメン控え.erase(ギルメン控え.begin() -(ID+1));
			}

		}

		void パーティ移動(Hunter* メンバー , int 並びID , Hunter* 移動先メンバー, int 移動先ID)
		{
			//控え枠へドロップ
			if (移動先メンバー == nullptr && 移動先ID == -100)
			{
				if (並びID >= 0)
				{
					//パーティから控え
					探索パーティ[並びID / 5].メンバー[並びID % 5] = nullptr;
					ギルメン控え.push_back(メンバー);
				}
				else {
					//控えから控え最後までバブルソート
					for (int a = 0; a < ギルメン控え.size() - 1; a++)
					{
						if (ギルメン控え[a] == メンバー)
						{
							ギルメン控え[a] = ギルメン控え[a + 1];
							ギルメン控え[a + 1] = メンバー;
						}
					}
				}
			}
			else if (移動先ID >= 0 && 並びID >= 0)
			{
				//両方パーティ
				探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = メンバー;
				探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			}
			else if (移動先ID < 0 && 並びID < 0) {
				//両方控え
				ギルメン控え[(-移動先ID - 1)] = メンバー;
				ギルメン控え[(-並びID - 1)] = 移動先メンバー;
			}
			else if (移動先ID < 0) {
				//移動先が控え
				ギルメン控え[(-移動先ID - 1)] = メンバー;
				探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			}
			else {
				//控えからパーティ
				探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = メンバー;
				ギルメン控え[(-並びID - 1)] = 移動先メンバー;
				ギルメン控え.erase(std::remove( ギルメン控え.begin(), ギルメン控え.end(), nullptr), ギルメン控え.end());
			}

			//控えメンバーは
			for (auto& it : ギルメン控え)
			{
				it->基礎ステータス計算();
			}

			//全パーティメンバーの基礎ステ再計算
			for (auto& it : 探索パーティ)
			{
				it.基礎ステ再計算();
			}

			MSound::効果音[SE::配置換え].Play();
		}

		//探索関係処理
		void 探索開始()
		{
			//エフェクト初期化
			for (int a = 0; a < CV::最大パーティ数; a++)
			{
				Effect::アニメ[a].clear();
				Effect::素材[a].clear();
				Effect::文字[a].clear();
			}

			for (int a = 0; a < 最大パーティ数; a++)
			{
				//パーティ人数をチェック
				探索パーティ[a].探索開始();
			}
		}

		void 探索処理()
		{
			エフェクト更新();

			for (int a = 0; a < 最大パーティ数; a++)
			{
				探索パーティ[a].探索処理();
			}
		}

		void エフェクト更新()
		{
			for (int a = 0; a < CV::最大パーティ数; a++)
			{
				Effect::UpdateAndDelete(Effect::アニメ[a]);
				Effect::UpdateAndDelete(Effect::素材[a]);
				Effect::UpdateAndDelete(Effect::文字[a]);
			}
		}


		//クエスト関係
		void クエスト進行(QuestType クエスト種, int id)
		{
			for (auto& it : Quest::data)
			{
				if (it.種類 == クエスト種 && !it.is完了 && it.is受注) 
				{
					if (it.達成度計算(id)) { クエスト完了(it); }
				}
			}
		}

		void クエスト完了(Quest &クエスト)
		{
			MSound::効果音[SE::クエスト完了].Play();

			クエスト.is完了 = true;


		}

		bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}
	};
}