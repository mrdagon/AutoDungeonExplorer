//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class IFacility
	{

	};

	/*ギルド*/
	class Guild
	{
	public:
		//内部クラスにして循環参照解決する場合
		class Party
		{
		private:

		public:
			Party() :
				isボス戦中(false)
			{
				魔物.reserve(6);

				for (auto& it : メンバー)
				{
					it = nullptr;
				}
			}

			int パーティID;

			Dungeon* 探索先 = nullptr;
			OrderType 探索指示 = OrderType::なし;

			Explorer* メンバー[CV::パーティ人数];
			std::vector<Monster> 魔物;//戦闘中の相手

			std::vector<Battler*> 味方;
			std::vector<Battler*> 敵;

			CraftType 発見素材種;
			double 獲得経験値;
			int 獲得素材[CV::上限素材種類];
			int 獲得財宝[10];//最大で10個まで、-は地図、0は未発見

			ExplorerType 探索状態 = ExplorerType::編成中;
			int 待ち時間 = 0;//移動、戦闘後、素材回収中などの待ち時間

			bool isボス戦中 = false;

			int 部屋ID = 0;//探索,戦闘中の

			//★探索中演出用
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
					メンバー[a]->Pスキル.clear();
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

				//パーティメンバーの体力回復、ステータス再計算等
				基礎ステ再計算();

				//０人パーティは全滅扱いにする
				if (味方.size() == 0) { 探索状態 = ExplorerType::全滅中; }
			}

			void 探索終了()
			{
				//素材獲得
				for (int a = 0; a < CV::素材系統; a++)
				{
					if (獲得素材[a] > 0)
					{
						Guild::P->素材数[a] += 獲得素材[a];
						Guild::P->資金 += Material::data[a].価格 * 獲得素材[a];
						Guild::P->総素材 += 獲得素材[a];
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

			bool 操作_探索フロア増減(int 変化値)
			{
				if (変化値 == -1)
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
				else
				{

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

			bool 操作_探索指示(int 変化値)
			{
				int n = int(探索指示) + 変化値;

				if (n == (int)OrderType::COUNT) { n = 0; }
				if (n < 0) { n = (int)OrderType::COUNT - 1; }

				探索指示 = OrderType(n);
			}

			//部屋選択関係の処理
			void 部屋選び()
			{
				std::vector<int> room_deck;
				room_deck.clear();

				Set部屋抽選リスト(room_deck, true);

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
					isボス戦中 = false;
					戦闘開始(5);
					break;
				case RoomType::素材:
					探索状態 = ExplorerType::収集中;
					収集開始();
					break;
				case RoomType::財宝:
					探索状態 = ExplorerType::戦闘中;
					isボス戦中 = false;
					戦闘開始(6);
					break;
				case RoomType::階段:
					探索状態 = ExplorerType::戦闘中;
					isボス戦中 = false;
					戦闘開始(6);
					break;
				case RoomType::ボス:
					探索状態 = ExplorerType::戦闘中;
					isボス戦中 = true;
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
					発見物 = &MIcon::UI[IconType::探索_伐採];
					break;
				case 1:
					発見素材種 = CraftType::木材;
					発見物 = &MIcon::UI[IconType::探索_採掘];
					break;
				case 2:
					発見素材種 = CraftType::木材;
					発見物 = &MIcon::UI[IconType::探索_採掘];
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
					int id = Rand::Get(2);

					if (発見素材種 == CraftType::木材)
					{
						//素材ID = 探索先->伐採素材[id];
					} else {
						//素材ID = 探索先->採掘素材[id];
					}

					獲得素材[素材ID] += 素材数;

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

					獲得素材[素材ID]++;
					
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
				if (isボス戦中 == true)
				{
					MMusic::BGM[BGMType::通常ボス].Play();
					敵数 = 1;
					//魔物.emplace_back(探索先->ボスモンスター[0]);
				}
				else
				{
					for (int a = 0; a < 敵数; a++)
					{
						int mn = Rand::Get(2);
						//魔物.emplace_back(探索先->雑魚モンスター[mn]);
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
					if (it.is気絶 == false && it.現在HP <= 0)
					{
						it.is気絶 = true;
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
					Guild::P->総討伐++;
					Guild::P->クエスト進行(QuestType::ボス討伐, 探索先->ID);
					Guild::P->クエスト進行(QuestType::固定ボス討伐, 探索先->ID);
					EventLog::Add(0, Game::日付, LogType::探索 );
					//if (探索先->部屋[部屋ID].地図 < 0)
					//{
					//	財宝獲得();
					//}
					break;
				case RoomType::階段:
					探索先->部屋[部屋ID].種類 = RoomType::ザコ;
					break;
				case RoomType::財宝:
					探索先->部屋[部屋ID].種類 = RoomType::ザコ;
					財宝獲得();
					break;
				}

				階段発見();
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

			void 階段発見()
			{
				//if (探索先->部屋[部屋ID].地図 <= 0) { return; }

				//探索先->発見地図++;
				発見物 = &MIcon::UI[IconType::地図];

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
				発見物 = &MIcon::UI[IconType::宝箱];
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

				if (探索先->探索率 > Game::ボス発見探索率 && 探索先->isボス発見 == false)
				{
					MSound::効果音[SE::ボス発見].Play();
					探索先->isボス発見 = true;
					EventLog::Add(0, Game::日付, LogType::探索);
				}
			}

			bool SaveLoad(File& ファイル, FileMode 読み書きモード)
			{

			}

		};


		int 素材数[CV::上限素材種類];
		bool is素材発見[CV::素材系統];

		double 資金 = 1000;
		int 名声 = 100;

		//従業員一覧
		Explorer 探索者[CV::上限探索者登録数];

		Party パーティ[CV::上限パーティ数];
		Explorer* 控え探索者[CV::最大控え人数];

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		int 街Lv = 0;
		int 街経験値 = 0;

		//経営戦術効果
		double 戦闘経験補正 = 1.0;
		double 素材節約 = 0.0;//確率で素材消費0
		double 未開探索 = Game::基礎未探索部屋発見率;//未探索部屋抽選補正

		//装備品
		int アクセサリー所持数[CV::上限アクセサリ種類] = { 0 };

		EnumArray < bool, ItemType> is新開発タブ;

		//各種記録_Record
		int 総石版 = 0;

		int 総素材 = 0;
		int 総フロア = 0;//全探索フロア数
		int 総討伐 = 0;//討伐時増加
		int 総全滅 = 0;//全滅時増加

		inline static Guild* P;//プレイヤーのギルド

		Guild()
		{
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				パーティ[a].パーティID = a;
			}
		}

		void Init()
		{
			for (int a = 1; a <= 9; a++)
			{
				アクセサリー所持数[a] = 3;
			}

			for (auto& it : is素材発見)
			{
				it = false;
			}

			探索者登録(0, "ギルメンA");
			探索者登録(1, "ギルメンB");
			探索者登録(2, "ギルメンC");
			探索者登録(3, "ギルメンD");
			探索者登録(4, "ギルメンE");

			for (auto& it : 控え探索者)
			{
				it = nullptr;
			}

			//初期、探索者、テスト用
			for (int a = 0; a < 5; a++)
			{
				パーティ[0].メンバー[a] = &Guild::P->探索者[a];
			}

			探索者登録(5, "ギルメンF");
			探索者登録(6, "ギルメンG");
			探索者登録(7, "ギルメンH");
			探索者登録(8, "ギルメンI");
			探索者登録(9, "ギルメンJ");

			for (auto& it : Explorer::装備強化リスト)
			{
				it = -1;
			}

			//パーティ初期化
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				パーティ[a].探索先 = &Dungeon::data[0];
				パーティ[a].基礎ステ再計算();
			}
		}


		Explorer* GetMember(int パーティID, int 並びID)
		{
			if (パーティID < 0)
			{
				return 控え探索者[並びID];
			}
			else
			{
				return パーティ[パーティID].メンバー[並びID];
			}
		}

		bool MemberToID(Explorer* メンバー , int& パーティID ,  int& 並びID)
		{
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				for (int b = 0; b < CV::パーティ人数; b++)
				{
					if (パーティ[a].メンバー[b] == メンバー)
					{
						パーティID = a;
						並びID = b;
						return true;
					}
				}
			}

			for (int a = 0; a < CV::最大控え人数; a++)
			{
				if (控え探索者[a] == メンバー)
				{
					パーティID = -1;
					並びID = a;
					return true;
				}
			}

			パーティID = -2;
			並びID = -1;
			return false;
		}

		void 探索者登録(ID_Job 求人職業 , std::string 求人名前)
		{
			for (int i = 0; i < CV::上限探索者登録数; i++)
			{
				if (探索者[i].is登録済み == false)
				{
					探索者[i].登録(i, 求人職業,1, 求人名前);
					for (auto& it : 控え探索者)
					{
						if (it != nullptr) { continue; }

						it = &探索者[i];
						break;
					}
					break;
				}
			}
		}

		void 除名(Explorer* メンバー)
		{
			bool isHit = false;
			int パーティID = 0;
			int 並びID = 0;

			if (MemberToID(メンバー, パーティID, 並びID) == false) { return; }

			if (パーティID >= 0)
			{
				//探索パーティから除名
				アクセサリー所持数[パーティ[パーティID].メンバー[並びID]->装備[2]->ID]++;
				パーティ[パーティID].メンバー[並びID]->is登録済み = false;
				パーティ[パーティID].メンバー[並びID] = nullptr;
			} else {
				//控えから除名
				アクセサリー所持数[控え探索者[並びID]->装備[2]->ID]++;
				控え探索者[並びID]->is登録済み = false;

				for (int a = 並びID; a < CV::最大控え人数 - 1; a++)
				{
					控え探索者[a] = 控え探索者[a + 1];
				}
				控え探索者[CV::最大控え人数 - 1] = nullptr;
			}

		}

		//操作処理
		void 操作_配置変更(int パーティA , int 並びA , int パーティB , int 並びB)
		{
			Explorer* メンバーA;
			Explorer* メンバーB;

			if (パーティA < 0)
			{
				メンバーA = 控え探索者[並びA];
			} else {
				メンバーA = パーティ[パーティA].メンバー[並びA];
			}

			if (パーティB < 0)
			{
				メンバーB = 控え探索者[並びB];
				控え探索者[並びB] = メンバーA;
			} else {
				メンバーB = パーティ[パーティB].メンバー[並びB];
				パーティ[パーティB].メンバー[並びB] = メンバーA;
			}

			if (パーティA < 0)
			{
				控え探索者[並びA] = メンバーB;
			} else {
				パーティ[パーティA].メンバー[並びA] = メンバーB;
			}

			ソート控え();
		}

		void 操作_装備在庫(Explorer* メンバー , int 新装備ID , int 装備スロット)
		{
			//現在の装備を外して、在庫+1
			アクセサリー所持数[メンバー->装備[装備スロット]->ID]++;
			

			//装備を変更して、在庫-1
			メンバー->装備[装備スロット] = &Item::accessory_data[新装備ID];
			アクセサリー所持数[新装備ID]--;
		}

		void 操作_装備スワップ(Explorer* メンバーA,int 装備部位A, Explorer* メンバーB, int 装備部位B)
		{
			std::swap(メンバーA->装備[装備部位A], メンバーB->装備[装備部位B]);
		}

		void 操作_武器防具クリック(Explorer* メンバー , int 装備スロット)
		{
			メンバー->強化予約(装備スロット);
		}

		Explorer* 操作_スキル画面前後(Explorer* メンバー , int 前後)
		{
			//パーティ1～3、控え
			int パーティID,並びID;

			if (MemberToID(メンバー, パーティID, 並びID) == false) { return メンバー; }

			int no = 並びID;
			Explorer* member;

			while (1)
			{
				no += 前後;
				if (no < 0) { no = CV::パーティ人数 - 1; }
				if (no > CV::パーティ人数 - 1) { no = 0; }

				member = パーティ[パーティID].メンバー[no];

				if (member != nullptr)
				{
					return member;
				}
			}


		}

		void 操作_除名(Explorer* メンバー)
		{
			除名(メンバー);
		}

		void 操作_控え移動(int パーティID, int 並びID)
		{
			if (パーティID < 0)
			{
				//控えから削除
				//最後に追加
				for (int a = 0; a < CV::最大控え人数 - 1; a++)
				{
					if (控え探索者[a] == nullptr)
					{
						控え探索者[a] = 控え探索者[並びID];
						break;
					}
				}
				控え探索者[並びID] = nullptr;

				ソート控え();
			}
			else
			{
				//現在パーティから削除
				//最後に追加
				for (int a = 0; a < CV::最大控え人数 - 1; a++)
				{
					if (控え探索者[a] == nullptr)
					{
						控え探索者[a] = パーティ[パーティID].メンバー[並びID];
						break;
					}
				}
				パーティ[パーティID].メンバー[並びID] = nullptr;
			}
		}

		void ソート控え()
		{
			for (int a = 0; a < CV::最大控え人数 - 1; a++)
			{
				if (控え探索者[a] == nullptr)
				{
					控え探索者[a] = 控え探索者[a + 1];
					控え探索者[a + 1] = nullptr;
				}
			}
		}

		//探索関係処理
		void 探索開始()
		{
			装備強化チェック();
			投資予約チェック();

			//エフェクト初期化
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				Effect::アニメ[a].clear();
				Effect::素材[a].clear();
				Effect::文字[a].clear();
			}

			for (int a = 0; a < 最大パーティ数; a++)
			{
				//パーティ人数をチェック
				パーティ[a].探索開始();
			}
		}

		void 探索処理()
		{
			エフェクト更新();

			for (int a = 0; a < 最大パーティ数; a++)
			{
				パーティ[a].探索処理();
			}
		}

		void エフェクト更新()
		{
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				Effect::UpdateAndDelete(Effect::アニメ[a]);
				Effect::UpdateAndDelete(Effect::素材[a]);
				Effect::UpdateAndDelete(Effect::文字[a]);
			}
		}

		void 探索終了()
		{
			//各パーティのレベルアップ処理
			
			//戦利品の回収

			予約スキルチェック();
		}

		void 一日終了()
		{

			装備強化チェック();
			投資予約チェック();
		}

		//
		void 予約スキルチェック()
		{
			//探索後のみ

		}

		void 装備強化チェック()
		{
			//深夜と探索前

		}

		void 投資予約チェック()
		{
			//深夜と探索前


		}

		//クエスト関係
		void クエスト進行(QuestType クエスト種, int id)
		{
			for (auto& it : Quest::data)
			{
				if (it.種類 == クエスト種 && it.進行状況 == QuestState::進行中 ) 
				{
					if (it.達成度計算(id)) { クエスト完了(it); }
				}
			}
		}

		void クエスト完了(Quest &クエスト)
		{
			MSound::効果音[SE::クエスト完了].Play();

			クエスト.進行状況 = QuestState::完了;
		}

		bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}
	};
}