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
				if (探索先->探索率 > Game::地図発見探索率&& 探索先->部屋[1].地図 > 0 && !探索先->部屋[1].is入場)
				{
					room_deck.push_back(1);
					return;
				}

				//未探索部屋から抽選
				if (Rand::Coin(Guild::P->未開探索))
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
				部屋探索完了();

				探索状態 = ExplorerType::収集中;

				発見素材種 = Rand::Coin(0.5) ? CraftType::鍛造 : CraftType::木工;

				if (発見素材種 == CraftType::木工)
				{
					発見物 = &MIcon::アイコン[IconType::探索_伐採];
				} else {
					発見物 = &MIcon::アイコン[IconType::探索_採掘];
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

				double レア素材確率 = 探索先->レア収集率;
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

					if (発見素材種 == CraftType::木工)
					{
						素材ID = 探索先->伐採素材[id];
					} else {
						素材ID = 探索先->採掘素材[id];
					}

					if (Rand::Coin(レア素材確率))
					{
						獲得レア素材[素材ID] += 素材数;
					}else {
						獲得素材[素材ID] += 素材数;
					}

					Effect::素材[パーティID].emplace_back(&MIcon::アイコン[Material::data[素材ID].アイコン] , a);
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

					素材ID = it.種族->素材;

					if (Rand::Coin(レア率))
					{
						獲得レア素材[素材ID]++;
					} else {
						獲得素材[素材ID]++;
					}

					Effect::素材[パーティID].emplace_back(&MIcon::アイコン[Material::data[素材ID].アイコン],a,it.隊列ID);
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
				Guild::P->クエスト進行(QuestType::雑魚討伐, (int)敵.size());

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
					味方[a]->現在HP += (int)(味方[a]->戦闘後回復 * 味方[a]->補正ステ[StatusType::生命]);
					味方[a]->現在HP = std::min(味方[a]->現在HP, 味方[a]->補正ステ[StatusType::生命]);
					味方[a]->エフェクトダメージ(-(int)(味方[a]->戦闘後回復 * 味方[a]->補正ステ[StatusType::生命]));
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
				Guild::P->クエスト進行(QuestType::雑魚討伐, ザコ討伐数);

				探索先->部屋[部屋ID].is入場 = false;
				探索状態 = ExplorerType::全滅中;
				MSound::効果音[SE::全滅].Play();
				Guild::P->総全滅++;
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
					Guild::P->総地図++;
					Guild::P->クエスト進行(QuestType::ダンジョン発見, 探索先->ID);
					EventLog::Add(0, Game::日付, LogDetailType::地図発見, 探索先->ID);
				}

				探索先->部屋[部屋ID].地図 = -1;
			}

			void 財宝獲得()
			{
				探索先->発見財宝++;
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

					Guild::P->クエスト進行(QuestType::雑魚討伐, ザコ討伐数);
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
		std::vector<Crafter> 製造要員;

		//Party test;
		Party 探索パーティ[CV::最大パーティ数];
		std::vector<Hunter*> ギルメン控え;

		EnumArray<std::vector<Crafter*>, CraftType> 製造メンバー;

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 投資Lv;
		EnumArray<double, ManagementType> 投資経験値;

		int 集客力 = 100;//10で割った数値が一日の来客期待値

		//キャラクリ関係
		std::string 求人名前 = "ナナーシ";
		ID_Job 求人職業 = 0;

		//経営戦術効果
		double 集客補正 = 1.0;
		double 価格補正 = 1.0;

		double 戦闘経験補正 = 1.0;
		double 技術経験補正 = 1.0;

		double 素材節約 = 0.0;//確率で素材消費0

		double 未開探索 = Game::基礎未探索部屋発見率;//未探索部屋抽選補正

		//製造関連
		EnumArray<double, CraftType> 必要製造力;
		EnumArray<double, CraftType> 合計製造力;
		EnumArray<double, CraftType> 製造進行度;
		EnumArray<bool, CraftType> is製造レア使用;
		EnumArray<double, CraftType> 製造ランク;

		EnumArray<int, CraftType> 完成品;
		EnumArray<bool, CraftType> is装備修復;

		EnumArray<int, CraftType> 壊れた装備;

		EnumArray<int, CraftType> 製造Lv;
		EnumArray<double, CraftType> 製造経験;

		EnumArray<bool, CraftType> 製造ゲージ色;
		//--製造特殊効果とか(未実装)

		//装備品
		bool is装備開発[CV::装備種] = {false};
		bool is新規[CV::装備種] = { false };
		int 装備所持数[CV::装備種] = { 0 };
		int 販売可能数[CV::装備種] = { 0 };//仕様を戻す可能性もあるので消さない

		EnumArray < bool, ItemType> is新開発タブ;

		//各種記録_Record
		int 総石版 = 0;
		int 総人数 = 0;
		int 総販売 = 0;
		double 総売上 = 0;
		int 総製造 = 0;
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

			for (auto& it : 製造進行度)
			{
				it = 0;
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

		void 製造移動( Crafter*メンバー , int 並びID , Crafter* 移動先製造メンバー, CraftType 移動先部門, int 移動先ID = 0)
		{
			CraftType 部署 = メンバー->配置部門;

			//移動先が空き
			if (移動先製造メンバー == nullptr)
			{
				//現在の部署から削除して、新部署の最後に移動
				for (int a = 0; a < (int)製造メンバー[部署].size(); a++)
				{
					if (メンバー == 製造メンバー[部署][a])
					{
						製造メンバー[部署].erase(製造メンバー[部署].begin() + a);
						break;
					}
				}
				製造メンバー[移動先部門].emplace_back(メンバー);
				メンバー->配置部門 = 移動先部門;
			}
			else {
				//移動先と入れ替え
				製造メンバー[移動先部門][移動先ID] = メンバー;
				製造メンバー[部署][並びID] = 移動先製造メンバー;

				メンバー->配置部門 = 移動先部門;
				移動先製造メンバー->配置部門 = 部署;
			}

			MSound::効果音[SE::配置換え].Play();
		}

		//製造関係処理
		void 製造力計算()
		{
			合計製造力[CraftType::裁縫] = 0;
			合計製造力[CraftType::鍛造] = 0;
			合計製造力[CraftType::魔術] = 0;
			合計製造力[CraftType::木工] = 0;


			for (int a= 0 ; a< (int)CraftType::COUNT ; a++)
			{
				for (auto& it : 製造メンバー[CraftType(a)])
				{
					it->基礎ステータス計算();
					合計製造力[CraftType(a)] += it->製造力;
				}
			}
		}

		void 製造処理()
		{

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				CraftType n = (CraftType)a;
				//素材チェック
				if (製造進行度[n] <= 0 && 合計製造力[n] > 0)
				{
					if (製造開始(n) == false) { continue; }
				}

				製造進行度[n] += 合計製造力[n];

				if (製造進行度[n] >= 必要製造力[n] && 完成品[n] >= 0)
				{
					装備完成処理(n);
				}
			}
		}

		int 必要技術経験(CraftType 種類)
		{
			if (製造Lv[種類] >= CV::最大技術Lv) { return 1; }

			return (製造Lv[種類] * 2 + 1) * 100000;
		}

		bool 製造開始(CraftType 種類)
		{
			//素材所持チェックと消費		
			int 素材ID = -1;
			bool isレア = false;

			//技術力以下で一番ランクが高い素材を選択
			//レア素材をチェック
			for (int a = CV::最大素材種 - 1; a >= 0; a--)
			{
				if (Material::data[a].製造部門 != 種類) { continue; }
				if ( レア素材数[a] <= 0 ) { continue; }
				素材ID = a;
				isレア = true;
				レア素材数[素材ID]--;
				break;
			}


			//通常素材をチェック-素材IDが後半の物を優先
			if (isレア == false)
			{
				for (int a = CV::最大素材種 - 1; a >= 0; a--)
				{
					if (Material::data[a].製造部門 != 種類) { continue; }
					if (素材数[a] < CV::素材消費数) { continue; }
					素材ID = a;

					if (!Rand::Coin(素材節約))
					{
						素材数[素材ID] -= CV::素材消費数;
					}

					break;
				}
			}

			//素材が無ければ製造開始しない
			if (素材ID < 0) { return false; }

			必要製造力[種類] = 10000 + Material::data[素材ID].Lv * 2000;
			is製造レア使用[種類] = isレア;

			std::vector<int> 抽選リスト;
			int 合計確率 = 0;
			int レシピ数 = 0;


			for (auto& it : Material::data[素材ID].レシピ)
			{
				if (it.id > 0)
				{
					合計確率 += it.製造確率;
					レシピ数++;
				}
			}

			//最後のレシピはレアレシピ扱い
			if (isレア)
			{
				合計確率 += Material::data[素材ID].レシピ[レシピ数-1].製造確率 * CV::レア素材レア率;
			}

			//レシピから抽選
			int 抽選 = Rand::Get(合計確率);

			for (int a = 0; a < レシピ数; a++)
			{
				抽選 -= Material::data[素材ID].レシピ[a].製造確率;

				if (抽選 <= 0 || a == レシピ数 - 1)
				{
					完成品[種類] = Material::data[素材ID].レシピ[a].id;
					break;
				}
			}


			製造進行度[種類] = 0;
			return true;
		}

		void 装備完成処理(CraftType 種類)
		{
			int itemID = 完成品[種類];
			bool 効果音優先 = false;
			double 経験値補正 = 1;


			if (is製造レア使用[種類] == true)
			{
				経験値補正 = CV::レア素材経験倍率;
			}

			//所持数だけ追加して販売可能数は+しない
			装備所持数[itemID]++;
			総製造++;
			製造経験[種類] += 必要製造力[種類] * Guild::P->技術経験補正 * 経験値補正;
			Item::data[itemID].Add品質経験値(int(CV::基礎品質経験値 * 経験値補正));

			//LvUP判定
			if (製造Lv[種類] < CV::最大技術Lv && 製造経験[種類] >= 必要技術経験(種類) )
			{
				製造経験[種類] -= 必要技術経験(種類);
				製造Lv[種類] ++;
				MSound::効果音[SE::技術Lv上昇].Play();
				EventLog::Add(0, Game::日付, LogDetailType::技術Lv上昇, (int)種類);
				効果音優先 = true;
			}

			if ( is装備開発[itemID] == false )
			{
				is装備開発[itemID] = true;
				if (効果音優先 == false) { MSound::効果音[SE::新装備作成].Play(); }
				EventLog::Add(0, Game::日付, LogDetailType::新装備開発, itemID);
			} else {
				if (効果音優先 == false) { MSound::効果音[SE::装備作成].Play(); }
			}

			//非製造状態にする
			完成品[種類] = -1;
			製造進行度[種類] = 0;
			製造ゲージ色[種類] = !製造ゲージ色[種類];

			クエスト進行(QuestType::装備製造, 1);
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

		void 装備自動更新()
		{
			if (Config::is装備自動更新 == false) { return; }

			for (int a = 0; a < CV::最大パーティ数; a++)
			{
				for (int b = 0; b < CV::パーティ人数; b++)
				{
					auto it = 探索パーティ[a].メンバー[b];

					個別装備更新(it,0);
					個別装備更新(it,1);
				}
			}
		}

		//no 0-1 装備部位
		void 個別装備更新(Hunter* ギルメン , int 部位)
		{
			if (ギルメン == nullptr) { return; }

			//同じ系統でランク上の装備があったら交換

			int a = -1;
			for (auto& it : 装備所持数)
			{
				a++;
				//在庫1つ以上、装備種一致、基礎性能 + 品質補正 が今の装備より大きい場合更新
				if (it > 0 &&
					Item::data[a].種類 == ギルメン->装備[部位]->種類 &&
					Item::data[a].Get性能() > ギルメン->装備[部位]->Get性能() )
				{
					it--;
					装備所持数[ギルメン->装備[部位]->ID];
					ギルメン->装備[部位] = &Item::data[a];
				}
			}

		}

		//販売関係処理-仕様再変更に備えて残す
		void アイテム販売()
		{
			//客が来る判定-一日に集客力/10人が期待値
			if (集客力 * Guild::P->集客補正 < Rand::Get( (Game::終業時間 - Game::始業時間)*10 )) { return; }
			MSound::効果音[SE::販売].Play();

			//在庫から売るアイテムを抽選
			int total_wait = 0;

			for (int a = 0; a < CV::装備種; a++)
			{
				if (販売可能数[a] > 0 && 装備所持数[a] > 1)
				{
					total_wait += Item::data[a].Lv;
				}			
			}

			int 乱数 = Rand::Get(total_wait);

			for (int a = 0; a < CV::装備種; a++)
			{
				if (販売可能数[a] > 0 && 装備所持数[a] > 1)
				{
					乱数 -= Item::data[a].Lv;
					if (乱数 <= 0)
					{
						販売可能数[a]--;
						装備所持数[a]--;
						資金 += 0;
						総売上 += 0;
						総販売++;
						クエスト進行(QuestType::装備販売, 1);
						break;
					}
				}
			}

		}

		void 装備取置解除()
		{
			for (int a = 0; a < CV::装備種; a++)
			{
				販売可能数[a] = 装備所持数[a];
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

			クエスト.達成度 = クエスト.条件数値;
			クエスト.is完了 = true;
			Guild::P->名声 += クエスト.報酬名誉;
			Guild::P->資金 += クエスト.報酬金;

			for (auto& it : クエスト.次依頼)
			{
				if (it >= 0)
				{
					Quest::data[it].is受注 = true;
				}
			}

			if (クエスト.isメイン)
			{
				Game::isメインクエスト = true;
			}
		}

		bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}
	};
}