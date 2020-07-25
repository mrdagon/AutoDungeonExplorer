//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*掴み中のものの表示、管理*/
	namespace W_Drag_Drop
	{
		Dungeon* ダンジョン = nullptr;

		int アイテム = -1;

		Hunter* 探索メン = nullptr;
		Crafter* 製造メン = nullptr;
		int 並びID = 0;//パーティと製造部門での位置

		ActiveSkill* Aスキル = nullptr;

		struct equipItem
		{
			int 部位 = 0;
			Hunter* メンバー = nullptr;
		} ギルメン装備;

		void Draw()
		{
			if (ダンジョン != nullptr)
			{
				MIcon::アイコン[ダンジョン->アイコン].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if (アイテム != -1)
			{
				MIcon::アイテム[Item::data[アイテム].見た目].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if (探索メン != nullptr)
			{
				MUnit::ユニット[探索メン->見た目][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
			}
			else if (製造メン != nullptr)
			{
				MUnit::ユニット[製造メン->見た目][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
			}
			else if (ギルメン装備.メンバー != nullptr)
			{
				MIcon::アイテム[Item::data[ギルメン装備.メンバー->装備[ギルメン装備.部位]].見た目].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}			
			else if ( Aスキル != nullptr)
			{
				MSystem::DrawSkill(Aスキル->アイコン, { Input::mouse.x - 12 ,Input::mouse.y - 12 }, Color(200, 64, 64));

			}
		}

		bool 操作()
		{
			if (Input::mouse.Left.off)
			{
				ダンジョン = nullptr;
				探索メン = nullptr;
				アイテム = -1;
				ギルメン装備.メンバー = nullptr;
				製造メン = nullptr;
				Aスキル = nullptr;
			}

			return false;
		}

		void パーティ移動(Hunter* 移動先メンバー, int 移動先ID)
		{
			//控え枠へドロップ
			if (移動先メンバー == nullptr && 移動先ID == -100)
			{
				if (並びID >= 0)
				{
					//パーティから控え
					Guild::P->探索パーティ[並びID / 5].メンバー[並びID % 5] = nullptr;
					Guild::P->ギルメン控え.push_back(探索メン);
				} else {
					//控えから控え最後までバブルソート
					for (int a = 0; a < Guild::P->ギルメン控え.size() - 1; a++)
					{
						if (Guild::P->ギルメン控え[a] == 探索メン)
						{
							Guild::P->ギルメン控え[a] = Guild::P->ギルメン控え[a+1];
							Guild::P->ギルメン控え[a+1] = 探索メン;
						}
					}
				}


			}
			else if (移動先ID >= 0 && 並びID >= 0)
			{
				//両方パーティ
				Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = 探索メン;
				Guild::P->探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			} else if(移動先ID < 0 && 並びID < 0){
				//両方控え
				Guild::P->ギルメン控え[(-移動先ID-1)] = 探索メン;
				Guild::P->ギルメン控え[(-並びID-1)] = 移動先メンバー;
			}
			else if (移動先ID < 0) {
				//移動先が控え
				Guild::P->ギルメン控え[(-移動先ID-1)] = 探索メン;
				Guild::P->探索パーティ[並びID / 5].メンバー[並びID % 5] = 移動先メンバー;
			} else {
				//控えからパーティ
				Guild::P->探索パーティ[移動先ID / 5].メンバー[移動先ID % 5] = 探索メン;
				Guild::P->ギルメン控え[(-並びID-1)] = 移動先メンバー;
				Guild::P->ギルメン控え.erase(std::remove(Guild::P->ギルメン控え.begin(), Guild::P->ギルメン控え.end(), nullptr), Guild::P->ギルメン控え.end());
			}

			//控えメンバーは
			for (auto& it : Guild::P->ギルメン控え)
			{
				it->基礎ステータス計算();
			}

			//全パーティメンバーの基礎ステ再計算
			for (auto& it : Guild::P->探索パーティ)
			{
				it.基礎ステ再計算();
			}

			MSound::効果音[SE::配置換え].Play();
		}

		void 製造移動(Crafter* 移動先製造メンバー, CraftType 移動先部門, int 移動先ID = 0)
		{
			CraftType 部署 = 製造メン->配置部門;

			//移動先が空き
			if (移動先製造メンバー == nullptr)
			{
				//現在の部署から削除して、新部署の最後に移動
				for (int a = 0; a < (int)Guild::P->製造メンバー[部署].size(); a++)
				{
					if (製造メン == Guild::P->製造メンバー[部署][a])
					{
						Guild::P->製造メンバー[部署].erase(Guild::P->製造メンバー[部署].begin() + a);
						break;
					}
				}
				Guild::P->製造メンバー[移動先部門].emplace_back(製造メン);
				製造メン->配置部門 = 移動先部門;
			} else {
				//移動先と入れ替え
				Guild::P->製造メンバー[移動先部門][移動先ID] = 製造メン;
				Guild::P->製造メンバー[部署][並びID] = 移動先製造メンバー;

				製造メン->配置部門 = 移動先部門;
				移動先製造メンバー->配置部門 = 部署;
			}

			MSound::効果音[SE::配置換え].Play();
		}


	};
}