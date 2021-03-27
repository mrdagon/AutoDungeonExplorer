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

		static Item* アイテム = nullptr;//装備中の場合、探索メンをnullptrにしない

		Explorer* 探索メン = nullptr;
		int 並びID = 0;//パーティでの位置-キャラに持たせる

		ActiveSkill* Aスキル = nullptr;//消す

		struct equipItem
		{
			int 部位 = 0;
			Explorer* メンバー = nullptr;
		} ギルメン装備;

		//マウスオーバー中の物
		Management* Over戦術 = nullptr;

		void Draw()
		{
			if (ダンジョン != nullptr)
			{
				ダンジョン->image->DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if (アイテム != nullptr)
			{
				//アイテム->画像.DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if (探索メン != nullptr)
			{
				探索メン->image[0][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
			}

			else if (ギルメン装備.メンバー != nullptr)
			{
				//ギルメン装備.メンバー->装備[ギルメン装備.部位]->画像.DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}			
			else if ( Aスキル != nullptr)
			{
				MSystem::DrawSkill(Aスキル->image, { Input::mouse.x - 12 ,Input::mouse.y - 12 }, Color(200, 64, 64));

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
				Aスキル = nullptr;
			}

			return false;
		}
	};
}