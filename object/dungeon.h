//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "room.h"

namespace SDX_BSC
{
	using namespace SDX;


	/*ダンジョン*/
	class Dungeon
	{
	private:

	public:

		static std::vector<Dungeon> data;

		/*暫定自動生成*/
		static void Add(int no,std::string 名前, DungeonType 種類, int 部屋数, int ランク, int Lv, int 地図数 , bool isエリアボス)
		{
			data.emplace_back();

			data[no].Init(no, 名前, 種類, 部屋数, ランク, Lv, 地図数, isエリアボス);
		}

		/*暫定処理*/
		void Init(int no, std::string 名前, DungeonType 種類, int 部屋数, int ランク, int Lv, int 地図数, bool isエリアボス)
		{
			this->名前 = 名前;
			this->部屋数 = 部屋数;
			this->種類 = 種類;
			this->ランク = ランク;
			this->Lv = Lv;

			発見財宝 = 0;
			発見地図 = 0;
			最大財宝 = 3;
			最大地図 = 地図数;

			雑魚モンスター[0] = 0;
			雑魚モンスター[1] = 1;
			雑魚モンスター[2] = 2;
			ボスモンスター = 3;
			//部屋

			//位置-保留

			is発見 = false;


			int buf地図 = 発見地図;
			int buf財宝 = 発見財宝;

			for (int a = 0; a < 部屋数; a++)
			{
				部屋.emplace_back();
				部屋[a].is探索 = false;
				部屋[a].地図 = -1;

				if (a == 0)
				{
					部屋[a].種類 = RoomType::ボス;
					if (isエリアボス)
					{
						部屋[a].地図 = std::min(99, no + 1);
						buf地図--;
					} else {
						buf財宝--;
					}
				}
				else if ( buf地図 > 0)
				{
					部屋[a].種類 = RoomType::地図;
					部屋[a].地図 = std::min(99, no + 1);
					buf地図--;
				}
				else if ( buf財宝 > 0)
				{
					部屋[a].種類 = RoomType::財宝;
				}
				else if (a % 2 == 0)
				{
					部屋[a].種類 = RoomType::ザコ;
				} else {
					部屋[a].種類 = RoomType::素材;
				}
			}
		}

		void 探索率計算()
		{
			double n = 0;

			if (部屋.size() <= 0)
			{
				探索率 = 0;
				return;
			}

			for (int a = 0; a < 部屋.size(); a++)
			{
				if (部屋[a].is探索 == true) { n++; }
			}

			探索率 = n / 部屋.size();
		}

		int ID;
		std::string 名前;
		DungeonType 種類;
		int 部屋数;
		std::vector<Room>部屋;
		int ランク;//0~4
		int Lv;//敵の強さ等
		bool isボス戦中 = false;//同時にボス戦するのを防ぐ
		bool isボス生存 = true;
		bool isボス発見 = false;

		int 発見財宝;
		int 最大財宝;
		int 発見地図;
		int 最大地図;

		MonsterNo ボスモンスター;
		MonsterNo 雑魚モンスター[3];//地形種で固定？

		double 探索率;
		bool is発見;//ダンジョン発見済みフラグ
		bool is新発見;//UI用
	};

	std::vector<Dungeon> Dungeon::data;
}