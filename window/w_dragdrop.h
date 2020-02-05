//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*掴み中のものの表示、管理*/
	namespace W_Drag_Drop//クラスじゃないよ
	{
		Dungeon* ダンジョン = nullptr;
		int アイテム = -1;
		Warker* ギルメン = nullptr;
		WindowBox* ウィンドウ = nullptr;
		int 並びID = 0;//配列の位置

		void Draw()
		{
			if (ダンジョン != nullptr)
			{
				MIcon::ダンジョン[ダンジョン->種類].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			if (アイテム != -1)
			{
				MIcon::アイテム[Item::data[アイテム].見た目].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			if (ギルメン != nullptr)
			{
				MUnit::ユニット[ギルメン->見た目][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
			}
		}

		bool 操作()
		{
			if (Input::mouse.Left.off)
			{
				ダンジョン = nullptr;
				ギルメン = nullptr;
				アイテム = -1;
			}

			return false;
		}


		/*製造同士で入れ替え*/
		void 製造to製造(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			if (移動先メンバー == nullptr)
			{
				//最後に移動
				for (int a = 0; a < Guild::P->製造メンバー.size(); a++)
				{
					if (ギルメン == Guild::P->製造メンバー[a])
					{
						Guild::P->製造メンバー.erase(Guild::P->製造メンバー.begin() + a);
						break;
					}
				}
				Guild::P->製造メンバー.emplace_back(ギルメン);
			} else {
				//入れ替え
				Guild::P->製造メンバー[移動先ID] = ギルメン;
				Guild::P->製造メンバー[並びID] = 移動先メンバー;
			}

			移動先->GUI_Init();
		}

		/*パーティ同士で入れ替え*/
		void パーティtoパーティ(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = ギルメン;
			Guild::P->探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			Guild::P->探索パーティ[移動先ID / 5].スキルステ計算();
			Guild::P->探索パーティ[並びID / 5].スキルステ計算();

			移動先->GUI_Init();
		}

		/*移動先=パーティ*/
		void 製造toパーティ(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			if (移動先メンバー == nullptr)
			{
				//移動先が空きなら製造は削除
				Guild::P->製造メンバー.erase(Guild::P->製造メンバー.begin() + 並びID);
			} else {
				//移動先にいるなら入れ替え
				Guild::P->製造メンバー[並びID] = 移動先メンバー;
				移動先メンバー->表示ステ計算();
			}

			Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = ギルメン;
			Guild::P->探索パーティ[移動先ID / 5].スキルステ計算();

			移動先->GUI_Init();
			ウィンドウ->GUI_Init();

		}

		void パーティto製造(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			if (移動先メンバー == nullptr)
			{
				//移動先が空きならパーティは空き
				Guild::P->製造メンバー.push_back(ギルメン);
			}
			else {
				//移動先にいるなら入れ替え
				Guild::P->製造メンバー[移動先ID] = ギルメン;
				ギルメン->表示ステ計算();
			}

			Guild::P->探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			Guild::P->探索パーティ[並びID / 5].スキルステ計算();

			移動先->GUI_Init();
			ウィンドウ->GUI_Init();
		}

		void 求人to製造(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			//製造の最後に追加
			Guild::P->製造メンバー.push_back(ギルメン);

			ギルメン->is内定 = false;
			ギルメン->就活 = -1;
			ギルメン->所属 = Guild::P->id;

			移動先->GUI_Init();
			ウィンドウ->GUI_Init();
		}

		void 求人toパーティ(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			if (移動先メンバー == nullptr)
			{
				//パーティに空きがある場合

				ギルメン->is内定 = false;
				ギルメン->就活 = -1;
				ギルメン->所属 = Guild::P->id;
				Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = ギルメン;
				Guild::P->探索パーティ[移動先ID / 5].スキルステ計算();
			}
		}

		/*求人で入れ替え(未実装)*/
		void 求人to求人()
		{

		}

		void メンバー移動(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			switch (移動先->種類)
			{
			case WindowType::Party:
				switch (ウィンドウ->種類)
				{
				case WindowType::Party:
					パーティtoパーティ(移動先, 移動先メンバー, 移動先ID);
					break;
				case WindowType::Factory:
					製造toパーティ(移動先, 移動先メンバー, 移動先ID);
					break;
				case WindowType::Recruit:
					求人toパーティ(移動先, 移動先メンバー, 移動先ID);
					break;
				}
				break;
			case WindowType::Factory:
				switch (ウィンドウ->種類)
				{
				case WindowType::Party:
					パーティto製造(移動先, 移動先メンバー, 移動先ID);
					break;
				case WindowType::Factory:
					製造to製造(移動先, 移動先メンバー, 移動先ID);
					break;
				case WindowType::Recruit:
					求人to製造(移動先, 移動先メンバー, 移動先ID);
					break;
				}
				break;
			case WindowType::Recruit:
				//とりあえず無し？
				break;
			}

			Guild::P->製造力計算();
		}


	};
}