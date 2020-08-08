//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*掴み中のもの、マウスオーバー中の物の表示、管理*/
	namespace W_Drag
	{
		//ドラッグ中の物
		static Dungeon* ダンジョン = nullptr;

		static Item* アイテム = nullptr;

		Hunter* 探索メン = nullptr;
		Crafter* 製造メン = nullptr;
		int 並びID = 0;//パーティと製造部門での位置

		ActiveSkill* Aスキル = nullptr;

		struct equipItem
		{
			int 部位 = 0;
			Hunter* メンバー = nullptr;
		} ギルメン装備;

		//マウスオーバー中の物
		Management* Over戦術 = nullptr;

		void Draw()
		{
			if (ダンジョン != nullptr)
			{
				ダンジョン->Img->DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if (アイテム != nullptr)
			{
				MIcon::アイテム[アイテム->見た目].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if (探索メン != nullptr)
			{
				探索メン->Img[0][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
			}
			else if (製造メン != nullptr)
			{
				製造メン->Img[0][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
				
			}
			else if (ギルメン装備.メンバー != nullptr)
			{
				MIcon::アイテム[ギルメン装備.メンバー->装備[ギルメン装備.部位]->見た目].DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}			
			else if ( Aスキル != nullptr)
			{
				MSystem::DrawSkill(Aスキル->Img, { Input::mouse.x - 12 ,Input::mouse.y - 12 }, Color(200, 64, 64));

			}
		}

		bool Drop()
		{
			if (Input::mouse.Left.off)
			{
				ダンジョン = nullptr;
				探索メン = nullptr;
				アイテム = nullptr;
				ギルメン装備.メンバー = nullptr;
				製造メン = nullptr;
				Aスキル = nullptr;
			}

			return false;
		}
	};
}