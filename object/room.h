//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ダンジョンの部屋*/
	class Room
	{
	private:
	public:
		Room()
		{
		}

		RoomType 種類;
		bool is探索[CV::最大ギルド数];//誰かが探索し終わったかどうか

		int 地図;//0以上なら接続先MapIndex
	};
}