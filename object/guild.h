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
			Party()
			{
				メンバー.resize(CV::パーティ人数);

				for (int a = 0; a < CV::パーティ人数; a++)
				{
					メンバー[a] = nullptr;
				}
			}

			int ギルドID;

			Dungeon* 探索先;
			OrderType 探索指示;

			EnumArray<int[CV::最大素材ランク], CraftType> 獲得素材;
			std::vector<Monster> 魔物;

			std::vector<Warker*> メンバー;
			std::vector<Fighter*> 味方;
			std::vector<Fighter*> 敵;
			int 戦闘待ち;

			double 経験値;
			bool is探索中;
			bool is移動中;
			bool is全滅;
			bool is戦闘;
			bool isボス戦;

			int 部屋ID;
			int 残り移動時間;
			int 残り待機時間;

			//パーティ補正
			double 戦闘後回復 = 1.0;
			double 素材剥取ランク = 0.0;
			double 素材収集ランク = 0.0;
			double 素材剥取量 = 1.0;
			double 素材収集量 = 1.0;


			void スキルステ計算()
			{
				味方.clear();
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] != nullptr) { 味方.push_back(メンバー[a]); }
					メンバー[a]->探索開始();
				}
				for (int a = 0; a < 味方.size(); a++)
				{
					味方[a]->発動パッシブ.clear();
				}
				for (int a = 0; a < 味方.size(); a++)
				{
					味方[a]->所持スキル計算(味方);
				}
				for (int a = 0; a < 味方.size(); a++)
				{
					味方[a]->基礎ステータス計算(味方, 敵);
				}
			}

			void 探索開始()
			{
				is探索中 = true;
				is移動中 = true;
				is戦闘 = false;
				isボス戦 = false;
				残り移動時間 = 100000;//とりあえず探索しなくする
				残り待機時間 = 0;
				//パーティメンバーの体力回復、ステータス計算
				味方.clear();
				スキルステ計算();

				if (味方.size() == 0) { is全滅 = true; }
				else { is全滅 = false; }
			}

			void 探索終了(Guild* 親)
			{
				//素材獲得
				for (int b = 0; b < (int)CraftType::COUNT; b++)
				{
					for (int a = 0; a < CV::最大素材ランク; a++)
					{
						親->素材数[CraftType(b)][a] += 獲得素材[CraftType(b)][a];
						獲得素材[CraftType(b)][a] = 0;
					}
				}
				//レベルアップ
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					while (メンバー[a]->レベルアップ()) {}
				}

				スキルステ計算();
			}

			void 探索処理(Guild* 親)
			{
				//探索終了判定
				if (is探索中 == false){ return; }

				if ( Game::時間 >= Game::終業時間 )
				{
					探索終了(親);
					is探索中 = false;
					return;
				}

				//戦闘等のエフェクト更新
				for (auto& it : 味方)
				{
					it->エフェクト更新();
				}
				for (auto& it : 敵)
				{
					it->エフェクト更新();
				}

				//待機中(収集中、戦闘後待機、宝部屋etc)
				if (残り待機時間 > 0)
				{
					残り待機時間--;
					if (残り待機時間 == 0)
					{
						残り移動時間 = 100;
						is移動中 = true;
					}
					return;
				}

				//移動中
				if (残り移動時間 > 0)
				{
					残り移動時間--;
					if (残り移動時間 == 0)
					{
						is移動中 = false;
						部屋選び();
					}
					return;
				}

				//戦闘中処理
				if (is戦闘)
				{
					戦闘処理();
				}
			}

			//部屋選択関係の処理
			void 部屋選び()
			{
				std::vector<int> room_deck;

				switch (探索指示)
				{
				case OrderType::探索://50%で未探索から探索	
					ランダム部屋選び(room_deck);
					break;
				case OrderType::ボス://発見済みならボス戦へ
					ランダム部屋選び(room_deck);
					break;
				}

				//抽選
				部屋ID = room_deck[Rand::Get((int)room_deck.size() - 1)];
				部屋選択後処理();
			}

			void ランダム部屋選び(std::vector<int>& room_deck)
			{
				for (int a = 0; a < 探索先->部屋数; a++)
				{
					if (探索先->部屋[a].種類 != RoomType::ボス)
					{
						room_deck.push_back(a);
					}
				}
			}

			//部屋選択後の処理
			void 部屋選択後処理()
			{
				switch (探索先->部屋[部屋ID].種類)
				{
				case RoomType::ザコ:
					is戦闘 = true;
					戦闘開始(false);
					break;
				case RoomType::財宝:
				case RoomType::地図:
					財宝処理();
					break;
				case RoomType::ボス:
					is戦闘 = true;
					戦闘開始(true);
					break;
				}

			}

			void 素材処理()
			{
				残り待機時間 = 600;
				//素材獲得処理
				獲得素材[CraftType::木工][探索先->ランク]++;
				獲得素材[CraftType::鍛造][探索先->ランク]++;

				地図発見処理();
			}

			void 財宝処理()
			{
				残り待機時間 = 600;

				//レア素材を獲得

				//素材部屋に変化
				探索先->部屋[部屋ID].種類 = RoomType::ザコ;

				地図発見処理();
			}

			void 戦闘開始(bool isボス)
			{
				敵.clear();
				魔物.clear();

				//敵の生成
				int num = 5;
				if (isボス == true)
				{
					探索先->isボス戦中 = true;
					isボス戦 = true;
					num = 1;
					敵.resize(num);

					魔物.emplace_back(探索先->ボスモンスター, 探索先->Lv, true);
				}
				else
				{
					敵.resize(num);

					for (int a = 0; a < num; a++)
					{
						int mn = Rand::Get(2);
						魔物.emplace_back(探索先->雑魚モンスター[mn], 探索先->Lv, false);
					}
				}

				for (int a = 0; a < num; a++)
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

				//
				戦闘待ち = 30;
			}

			void 戦闘処理()
			{
				if (戦闘待ち > 0)
				{
					戦闘待ち--;
					return;
				}

				//全員の全スキルのCT計算、


				戦闘待ち = 12;

				戦闘終了判定();
			}

			bool 戦闘終了判定()
			{
				//味方全滅or逃走
				int 死者数 = 0;
				for (auto& it : 味方)
				{
					if (it->現在HP <= 0)
					{
						死者数++;
					}
				}

				if (死者数 == 味方.size())
				{
					戦闘敗北();
					return true;
				}
				//敵全滅
				死者数 = 0;
				for (auto& it : 敵)
				{
					if (it->現在HP <= 0)
					{
						死者数++;
					}
				}

				if (死者数 == 敵.size())
				{
					戦闘勝利();
					return true;
				}

				return false;
			}

			void 戦闘勝利()
			{
				if (isボス戦 == true)
				{
					探索先->isボス生存 = false;
					探索先->isボス戦中 = false;
					探索先->部屋[部屋ID].種類 = RoomType::ザコ;
				}

				//戦闘後のパッシブ処理
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] != nullptr)
					{
						メンバー[a]->戦闘後処理(メンバー, 味方, 敵);
					}
				}

				//経験値獲得
				double 経験値 = 0;
				for (auto& it : 魔物)
				{
					経験値 += it.経験値;
				}

				//経験値獲得
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] != nullptr && メンバー[a]->現在HP > 0)
					{
						メンバー[a]->経験値 += 経験値;
					}
				}

				//体力小回復
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] != nullptr)
					{
						メンバー[a]->現在HP += 1;
					}
				}

				獲得素材[CraftType::裁縫][探索先->ランク]++;
				獲得素材[CraftType::魔術][探索先->ランク]++;

				is移動中 = true;
				残り移動時間 = 100;

				地図発見処理();
			}

			void 戦闘敗北()
			{
				if (isボス戦 == true)
				{
					探索先->isボス戦中 = false;
				}

				is全滅 = true;
				is探索中 = false;
			}

			void 地図発見処理()
			{
				int cid = 探索先->部屋[部屋ID].地図;
				if (探索先->部屋[部屋ID].is探索 == false && cid >= 0)
				{
					Dungeon::data[cid].is発見 = true;
				}

				探索先->部屋[部屋ID].is探索 = true;
				探索先->探索率計算();
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

		double 集客補正 = 1.0;
		double 価格補正 = 1.0;

		double 戦闘経験補正 = 1.0;
		double 技術経験補正 = 1.0;

		double 素材節約 = 0.0;//確率

		double 未開探索 = 0;//未探索部屋抽選補正

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
					it->表示ステ計算();
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

			for (int a = 製造Lv[種類]; a >= 0; a--)
			{
				if (素材数[種類][a] >= 要求数)
				{
					必要製造力[種類] = 10000 + 素材ランク * 2000;
					素材ランク = a + 1;

					if (Rand::Get(1.0) >= Guild::P->素材節約)
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
				if (探索パーティ[a].味方.size() > 0 && 探索パーティ[a].is全滅 == false){探索パーティ[a].探索処理(this);}
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
						資金 += Item::data[a].値段;
						総売上 += Item::data[a].値段;
						総販売++;
						break;
					}
				}
			}

		}
	};

	Guild* Guild::P;
	Guild Guild::data;
}