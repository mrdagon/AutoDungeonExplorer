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
		//掴めるのは４種類
		static Dungeon* ダンジョン = nullptr;

		static Item* 所持装備 = nullptr;

		struct Member
		{
			int 並びID;
			int パーティID;//0以上パーティ、-1控え
			Explorer* メンバー = nullptr;

			void Set(Explorer* メンバー,int パーティID , int 並びID)
			{
				this->並びID = 並びID;
				this->パーティID = パーティID;
				this->メンバー = メンバー;
			}
		};

		static Member 探索者;


		struct EquipItem
		{
			Explorer* メンバー = nullptr;
			int 部位 = 0;
		};
		
		static EquipItem ギルメン装備;

		/*ドラッグ中の物を表示*/
		void Draw()
		{
			if ( ダンジョン != nullptr )
			{
				ダンジョン->image->DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if ( 所持装備 != nullptr )
			{
				所持装備->image->DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}
			else if ( 探索者.メンバー != nullptr )
			{
				探索者.メンバー->image[0][1]->DrawRotate({ Input::mouse.x,Input::mouse.y }, 2, 0);
			}

			else if ( ギルメン装備.メンバー != nullptr )
			{
				ギルメン装備.メンバー->装備[ギルメン装備.部位]->image->DrawRotate({ Input::mouse.x,Input::mouse.y }, 1, 0);
			}			
		}

		/*非ドラッグ状態にする*/
		bool Drop()
		{
			if (Input::mouse.Left.off)
			{
				ダンジョン = nullptr;
				探索者.メンバー = nullptr;
				所持装備 = nullptr;
				ギルメン装備.メンバー = nullptr;
			}

			return false;
		}

		void Reset()
		{
			ダンジョン = nullptr;
			所持装備 = nullptr;
			ギルメン装備.メンバー = nullptr;
			探索者.メンバー = nullptr;
		}
	};
}