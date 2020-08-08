//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ダンジョンの部屋*/
	class Room
	{
	private:
	public:
		Room(){}

		RoomType 種類;
		bool is探索 = false;//探索し終わったかどうか
		bool is入場 = false;//同時に２パーティ探索するのを防ぐ
		int 地図 = -1;//0以上なら接続先MapIndex
	};
}