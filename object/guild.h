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

			for (int a = CV::最大素材ランク-1; a >= 0; a--)
			{
				if (素材数[種類][a] >= 要求数)
				{
					必要製造力[種類] = 10000;
					素材ランク = a;
					素材数[種類][a]-= 要求数;
					break;
				}
			}
			if (素材ランク < 0) { return false; }

			//何を作るか？必要製造力がいくつかを計算
			int 完成ランク = 素材ランク + 製造Lv[種類];
			std::vector<int> 抽選リスト;
			int 抽選数 = 0;

			for (auto& it : Item::data)
			{
				if (Game::対応レシピ[it.種類] == 種類 && it.ランク <= 完成ランク)
				{
					抽選リスト.emplace_back(it.id);
					抽選数++;
				}
			}

			完成品[種類] = 抽選リスト[Rand::Get(抽選数-1)];
			必要製造力[種類] = Item::data[完成品[種類]].必要製造力;
			製造進行度[種類] = 0;

			return true;
		}

		void 装備完成処理(CraftType 種類)
		{
			int itemID = 完成品[種類];

			装備所持数[itemID]++;
			is装備開発[itemID] = true;

			製造経験[種類] += 必要製造力[種類];


			//LvUP判定
			if (製造経験[種類] >= (製造Lv[種類]*2 + 1) * 100000)
			{
				製造経験[種類] -= (製造Lv[種類]*2 + 1) * 100000;
				製造Lv[種類] ++;
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
	};


	Guild* Guild::P;
	Guild Guild::data[CV::最大ギルド数];
}