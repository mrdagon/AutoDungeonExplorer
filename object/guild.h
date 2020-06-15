//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルド*/
	class Guild : public I_Guild
	{
	private:

	public:
		static Guild* P;//プレイヤーのギルド
		static Guild data[CV::最大ギルド数];

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
					素材数[種類][a]-= 要求数;
					総素材 -= 要求数;
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

			//所持数だけ追加して販売可能数は+しない
			装備所持数[itemID]++;
			if ( is装備開発[itemID] == false )
			{
				is装備開発[itemID] = true;
				EventLog::Add(0, Game::日付, LogDetailType::新装備開発, itemID);
			}
			総製造++;

			製造経験[種類] += 必要製造力[種類];


			//LvUP判定
			if (製造経験[種類] >= (製造Lv[種類]*2 + 1) * 100000)
			{
				製造経験[種類] -= (製造Lv[種類]*2 + 1) * 100000;
				製造Lv[種類] ++;
				EventLog::Add(0, Game::日付, LogDetailType::技術Lv上昇, (int)種類);
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
			if (集客力 < Rand::Get( (Game::終業時間 - Game::始業時間)*10 )) { return; }


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
	Guild Guild::data[CV::最大ギルド数];
}