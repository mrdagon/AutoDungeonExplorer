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
		void 製造to製造(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID , CraftType 移動部署)
		{
			CraftType 部署A = ギルメン->製造配置;

			//移動先が空き
			if (移動先メンバー == nullptr)
			{
				//最後に移動
				for (int a = 0; a < Guild::P->製造メンバー[部署A].size(); a++)
				{
					if (ギルメン == Guild::P->製造メンバー[部署A][a])
					{
						Guild::P->製造メンバー[部署A].erase(Guild::P->製造メンバー[部署A].begin() + a);
						break;
					}
				}
				Guild::P->製造メンバー[移動部署].emplace_back(ギルメン);
				ギルメン->製造配置 = 移動部署;
			} else {


				//入れ替え
				Guild::P->製造メンバー[移動部署][移動先ID] = ギルメン;
				Guild::P->製造メンバー[部署A][並びID] = 移動先メンバー;

				ギルメン->製造配置 = 移動部署;
				移動先メンバー->製造配置 = 部署A;
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
				//移動先が空きなら製造は削除だけ
				Guild::P->製造メンバー[ギルメン->製造配置].erase(Guild::P->製造メンバー[ギルメン->製造配置].begin() + 並びID);
			} else {
				//移動先にいるなら入れ替え
				Guild::P->製造メンバー[ギルメン->製造配置][並びID] = 移動先メンバー;
				移動先メンバー->製造配置 = ギルメン->製造配置;
				移動先メンバー->表示ステ計算();
			}

			Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = ギルメン;
			Guild::P->探索パーティ[移動先ID / 5].スキルステ計算();

			移動先->GUI_Init();
			ウィンドウ->GUI_Init();

		}

		void パーティto製造(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID, CraftType 製造部署)
		{
			if (移動先メンバー == nullptr)
			{
				//移動先が空きなら最後に追加
				Guild::P->製造メンバー[製造部署].push_back(ギルメン);	
			} else {
				//移動先にいるなら入れ替え
				Guild::P->製造メンバー[製造部署][移動先ID] = ギルメン;
				ギルメン->表示ステ計算();
			}
			ギルメン->製造配置 = 製造部署;

			//移動先メンバーがnullなら空きに居るなら代入処理になる
			Guild::P->探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			Guild::P->探索パーティ[並びID / 5].スキルステ計算();

			移動先->GUI_Init();
			ウィンドウ->GUI_Init();
		}

		void 求人to製造(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID, CraftType 製造部署)
		{
			//人事点を消費
			if (Guild::P->人事ポイント < 2) { return; }
			Guild::P->人事ポイント -= 2;

			//製造の最後に追加
			Guild::P->製造メンバー[製造部署].push_back(ギルメン);

			ギルメン->所属 = Guild::P->id;
			ギルメン->製造配置 = 製造部署;

			移動先->GUI_Init();
			ウィンドウ->GUI_Init();

			EventLog::Add(0, Game::日付, LogDetailType::雇用, ギルメン->ID);
		}

		void 求人toパーティ(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID)
		{
			//人事点を消費
			if (Guild::P->人事ポイント < 2) { return; }

			if (移動先メンバー != nullptr)
			{
				//元メンバーがいるなら鍛造に送る
				Guild::P->製造メンバー[CraftType::鍛造].push_back(移動先メンバー);
				移動先メンバー->製造配置 = CraftType::鍛造;
			}

			Guild::P->人事ポイント -= 2;
			ギルメン->所属 = Guild::P->id;
			Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = ギルメン;
			Guild::P->探索パーティ[移動先ID / 5].スキルステ計算();

			EventLog::Add(0, Game::日付, LogDetailType::雇用, ギルメン->ID);
		}

		/*求人で入れ替え(未実装)*/
		void 求人to求人()
		{

		}

		void メンバー移動(WindowBox* 移動先, Warker* 移動先メンバー, int 移動先ID , CraftType 製造部門 = CraftType::鍛造)
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
					パーティto製造(移動先, 移動先メンバー, 移動先ID,製造部門);
					break;
				case WindowType::Factory:
					製造to製造(移動先, 移動先メンバー, 移動先ID,製造部門);
					break;
				case WindowType::Recruit:
					求人to製造(移動先, 移動先メンバー, 移動先ID,製造部門);
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