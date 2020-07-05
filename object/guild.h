//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルド*/
	class Guild
	{
	private:
	public:

		class Party
		{
		private:

		public:
			Party():
				isボス戦(false)
			{
				メンバー.resize(CV::パーティ人数);

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
			OrderType 探索指示 = OrderType::探索;

			std::vector<Monster> 魔物;
			std::vector<Warker*> メンバー;

			std::vector<Fighter*> 味方;
			std::vector<Fighter*> 敵;

			EnumArray<int[CV::最大素材ランク], CraftType> 獲得素材;
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
			Image* 発見物 = nullptr;//地図、宝箱、鉱脈、木
			int 発見物X座標 = 0;

			void 基礎ステ再計算()
			{
				味方.clear();
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					味方.push_back(メンバー[a]);
					メンバー[a]->PスキルS.clear();
				}

				//パーティスキルや装備品スキル等の計算
				for (int a = 0; a < (int)味方.size(); a++)
				{
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
				for (auto& itA : 獲得素材){	for (auto& itB : itA){itB = 0;}}
				獲得財宝数 = 0;
				獲得地図数 = 0;
				撃破ボス数 = 0;

				//パーティメンバーの体力回復、ステータス計算
				基礎ステ再計算();

				//０人パーティは全滅扱いにする
				if (味方.size() == 0) { 探索状態 = ExplorerType::全滅中; }
			}

			void 探索終了()
			{
				//素材獲得
				for( int b = 0; b < (int)CraftType::COUNT; b++)
				{
					for (int a = 0; a < CV::最大素材ランク; a++)
					{
						Guild::P->素材数[CraftType(b)][a] += 獲得素材[CraftType(b)][a];
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
						移動量 += 2;
						if (待ち時間 == 0){ 部屋選び(); }
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

			//部屋選択関係の処理
			void 部屋選び()
			{
				std::vector<int> room_deck;
				room_deck.clear();

				switch (探索指示)
				{
				case OrderType::探索:
					Set部屋抽選リスト(room_deck,false);
					break;
				case OrderType::ボス://発見済みならボス戦へ
					Set部屋抽選リスト(room_deck,true);
					break;
				}

				//抽選
				部屋ID = room_deck[Rand::Get((int)room_deck.size() - 1)];
				部屋選択後処理();
			}

			void Set部屋抽選リスト(std::vector<int>& room_deck , bool isボス戦)
			{
				if ( 探索先->isボス発見 && 探索先->部屋[0].種類 == RoomType::ボス && isボス戦 && !探索先->部屋[0].is入場 )
				{
					room_deck.push_back(0);
					return;
				}

				//未探索部屋から抽選
				if ( Rand::Coin(Guild::P->未開探索) )
				{
					for (int a = 1; a < 探索先->部屋数; a++)
					{
						if (探索先->部屋[a].is入場 || 探索先->部屋[a].is探索 ){ continue; }
						room_deck.push_back(a);
					}
				}

				if (room_deck.size() > 0) { return; }


				for (int a = 1; a < 探索先->部屋数; a++)
				{
					if ( 探索先->部屋[a].is入場 )
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
				int 素材数 = 1;
				int ランク = 探索先->ID / 4 + 探索先->ランク;

				double 高ランク率 = 0;
				double 素材数増加率 = 0;

				for (auto& it : 味方)
				{
					高ランク率 += it->素材収集ランク;
					素材数増加率 += it->素材収集量;
				}

				if (Rand::Coin(素材数増加率))
				{
					素材数++;
				}

				if (Rand::Coin(0.5))
				{
					素材獲得(CraftType::木工, 素材数, ランク, 高ランク率);
				} else {
					素材獲得(CraftType::鍛造, 素材数, ランク, 高ランク率);
				}

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
					発見物X座標-= 2;
				}

				待ち時間--;
				if (待ち時間 == 0)
				{
					発見物 = nullptr;
					探索状態 = ExplorerType::移動中;
					待ち時間 = 60;
				}
			}

			void 素材獲得(CraftType 素材種,int 素材数,int ランク,double ランク上昇率)
			{
				int 基礎ランク = ランク;

				for (int a = 0; a < 素材数; a++)
				{
					if (Rand::Coin(double(探索先->ID % 4) / 4.0))
					{
						ランク++;
					}
					if (Rand::Coin(ランク上昇率))
					{
						ランク++;
					}
					ランク = std::min(ランク, CV::最大素材ランク - 1);

					獲得素材[素材種][ランク]++;
					Guild::P->is素材発見[素材種][ランク] = true;

					ランク = 基礎ランク;
				}

				if (発見物 == nullptr) { 発見物 = &MIcon::素材[素材種]; }
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
					魔物.emplace_back(探索先->ボスモンスター, 探索先->Lv, true);
				}
				else
				{
					for (int a = 0; a < 敵数; a++)
					{
						int mn = Rand::Get(2);
						魔物.emplace_back(探索先->雑魚モンスター[mn], 探索先->Lv, false);
					}
				}

				敵.resize(敵数);

				for (int a = 0; a < 敵数; a++)
				{
					敵[a] = &魔物[a];
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

				for (auto& it : 味方)
				{
					if (it->戦闘中処理(味方, 敵) == true)
					{
						戦闘終了判定();
						return;
					}
				}

				for (auto& it : 敵)
				{
					if (it->戦闘中処理(敵, 味方) == true)
					{
						戦闘終了判定();
						return;
					}
				}

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

				if ( !is生存 )
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

				if ( !is生存 )
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

				//経験値獲得
				for (auto& it : 魔物)
				{
					獲得経験値 += it.経験値;
				}

				//体力回復
				for (int a = 0; a < (int)味方.size(); a++)
				{
					味方[a]->現在HP += (int)(味方[a]->戦闘後回復 * 味方[a]->最大HP);
					味方[a]->現在HP = std::min(味方[a]->現在HP , 味方[a]->最大HP);
					味方[a]->Eダメージ = -(int)(味方[a]->戦闘後回復 * 味方[a]->最大HP);
					味方[a]->Eダメージ時間 = 16;
				}

				//素材獲得処理
				int 素材数 = 1;
				int ランク = 探索先->ID / 4 + 探索先->ランク;//Lvx 10%でランク+1

				double 高ランク率 = 0;
				double 素材数増加率 = 0;

				for (auto& it : 味方)
				{
					高ランク率 += it->素材剥取ランク;
					素材数増加率 += it->素材剥取量;
				}

				if (Rand::Coin(素材数増加率))
				{
					素材数++;
				}

				if (Rand::Coin(0.5))
				{
					素材獲得(CraftType::裁縫, 素材数, ランク, 高ランク率);
				} else {			
					素材獲得(CraftType::魔術, 素材数, ランク, 高ランク率);
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

					Guild::P->クエスト進行(QuestType::雑魚討伐, ザコ討伐数);

					//倒した敵の分だけ素材獲得
				} else {
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

		int id = 0;

		EnumArray<int[CV::最大素材ランク], CraftType> 素材数;
		EnumArray<bool[CV::最大素材ランク], CraftType> is素材発見;

		double 資金 = 123456789;
		MSkillType 選択戦術 = MSkillType::COUNT;
		int 人事ポイント = 10;
		int 名声 = 100;

		//従業員一覧
		std::vector<Warker*> ギルメン;

		EnumArray<std::vector<Warker*>, CraftType> 製造メンバー;

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 投資Lv;
		EnumArray<double, ManagementType> 投資経験値;

		int 集客力 = 100;//10で割った数値が一日の来客期待値

		//経営戦術効果
		double 集客補正 = 1.0;
		double 価格補正 = 1.0;

		double 戦闘経験補正 = 1.0;
		double 技術経験補正 = 1.0;

		double 素材節約 = 0.0;//確率で素材消費0

		double 未開探索 = 0.5;//未探索部屋抽選補正

		//製造関連
		EnumArray<double, CraftType> 必要製造力;
		EnumArray<double, CraftType> 合計製造力;
		EnumArray<double, CraftType> 製造進行度;

		EnumArray<int, CraftType> 完成品;
		EnumArray<bool, CraftType> is装備修復;

		EnumArray<int, CraftType> 壊れた装備;

		EnumArray<int, CraftType> 製造Lv;
		EnumArray<double, CraftType> 製造経験;

		EnumArray<bool, CraftType> 製造ゲージ色;
		//--製造特殊効果とか(未実装)

		//装備品
		bool is装備開発[CV::装備種];
		bool is新規[CV::装備種];
		int 装備所持数[CV::装備種];
		int 販売可能数[CV::装備種];

		EnumArray < bool, ItemType> is新開発タブ;

		//各種記録_Record
		int 総販売;
		double 総売上;
		int 総製造;
		int 総素材;//探索後増加
		int 総地図;//発見時増加
		int 総討伐;//討伐時増加
		int 総全滅;//全滅時増加

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


		static Guild* P;//プレイヤーのギルド
		static Guild data;

		Party 探索パーティ[CV::最大パーティ数];

		void Init()
		{

		}

		void 求人リロール()
		{
			//人事点があるかチェックして-1する
			if (人事ポイント <= 0)
			{
				return;
			}

			//志願者のリロール、とりあえず5人
			int count = 0;
			for (auto& it : Warker::data)
			{
				if (it.所属 == -1)
				{
					//再生成する
					it.Make(it.ID, Rand::Get(4), 1, "ナナーシ");
					count++;
				}
			}

			//足りてない部分は新規作成
			for (; count < 6; count++)
			{
				Warker::data.emplace_back();
				Warker::data.back().Make((int)Warker::data.size() - 1, Rand::Get(4), 1, "シンキー");
			}

			人事ポイント--;
			EventLog::Add(0, Game::日付, LogDetailType::再募集);
		}

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
				if (製造進行度[n] == 0 && 合計製造力[n] > 0)
				{
					if (製造開始(n) == false) { continue; }
				}

				製造進行度[n] += 合計製造力[n];

				if (製造進行度[n] >= 必要製造力[n])
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
			int 要求数 = 1;
			int 素材ランク = 0;

			//技術力以下で一番ランクが高い素材を選択

			for (int a = 製造Lv[種類]-1; a >= 0; a--)
			{
				if (素材数[種類][a] >= 要求数)
				{
					必要製造力[種類] = 10000 + 素材ランク * 2000;
					素材ランク = a + 1;

					if ( !Rand::Coin( 素材節約 ) )
					{
						素材数[種類][a] -= 要求数;
						総素材 -= 要求数;
					}
					break;
				}
			}
			if (素材ランク <= 0) { return false; }

			//何を作るか？必要製造力がいくつかを計算
			int 完成ランク = 素材ランク;

			//スキルや制度によるランク変動

			std::vector<int> 抽選リスト;
			int 抽選数 = 0;

			for (auto& it : Item::data)
			{
				if (Game::対応レシピ[it.種類] == 種類 && it.ランク == 完成ランク)
				{
					抽選リスト.emplace_back(it.id);
					抽選数++;
				}
			}

			完成品[種類] = 抽選リスト[Rand::Get(抽選数-1)];
			製造進行度[種類] = 0;

			return true;
		}

		void 装備完成処理(CraftType 種類)
		{
			int itemID = 完成品[種類];
			bool 効果音優先 = false;

			//所持数だけ追加して販売可能数は+しない
			装備所持数[itemID]++;
			総製造++;
			製造経験[種類] += 必要製造力[種類] * Guild::P->技術経験補正;

			//LvUP判定
			if (製造Lv[種類] < CV::最大技術Lv && 製造経験[種類] >= 必要技術経験(種類) )
			{
				製造経験[種類] -= (製造Lv[種類]*2 + 1) * 100000;
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
			}
			else {
				if (効果音優先 == false) { MSound::効果音[SE::装備作成].Play(); }
			}

			//非製造状態にする
			完成品[種類] = -1;
			製造進行度[種類] = 0;
			製造ゲージ色[種類] = !製造ゲージ色[種類];

			クエスト進行(QuestType::装備製造, 1);
		}

		void 探索開始()
		{
			for (int a = 0; a < 最大パーティ数; a++)
			{
				//パーティ人数をチェック
				探索パーティ[a].探索開始();
			}
		}

		void 探索処理()
		{
			for (int a = 0; a < 最大パーティ数; a++)
			{
				探索パーティ[a].探索処理();
			}
		}

		void 装備取置解除()
		{
			for (int a = 0; a < CV::装備種; a++)
			{
				販売可能数[a] = 装備所持数[a];
			}
		}

		void 装備自動更新()
		{
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
		void 個別装備更新(Warker* ギルメン , int no)
		{
			if (ギルメン == nullptr) { return; }
			if (ギルメン->is装備更新 == false) { return; }

			//同じ系統でランク上の装備があったら交換
			auto item = Item::data[ギルメン->装備[no]];

			if (item.isレア == true) { return; }

			for (int b = CV::装備種 - 1; b >= 0; b--)
			{
				if ( 装備所持数[b] <= 0) { continue; }
					
				if ( Item::data[b].種類 == item.種類 &&
					 Item::data[b].ランク > item.ランク&&
					 Item::data[b].isレア == false )
				{
					装備所持数[ギルメン->装備[no]]++;
					装備所持数[b]--;
					ギルメン->装備[no] = b;
					ギルメン->装備スキル更新();
					break;
				}
			}
		}

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
					total_wait += Item::data[a].ランク;
				}			
			}

			int 乱数 = Rand::Get(total_wait);

			for (int a = 0; a < CV::装備種; a++)
			{
				if (販売可能数[a] > 0 && 装備所持数[a] > 1)
				{
					乱数 -= Item::data[a].ランク;
					if (乱数 <= 0)
					{
						販売可能数[a]--;
						装備所持数[a]--;
						資金 += Item::data[a].値段 * 価格補正;
						総売上 += Item::data[a].値段;
						総販売++;
						クエスト進行(QuestType::装備販売, 1);
						break;
					}
				}
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

	};

	Guild* Guild::P;
	Guild Guild::data;
}