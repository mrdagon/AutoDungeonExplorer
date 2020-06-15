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
		static void Add(int no,std::string 名前, DungeonType 種類, int 部屋数, int ランク, int Lv)
		{
			data.emplace_back();

			data[no].Init(no, 名前, 種類, 部屋数, ランク, Lv);		
		}

		void Init(int no, std::string 名前, DungeonType 種類, int 部屋数, int ランク, int Lv)
		{
			this->名前 = 名前;
			this->部屋数 = 部屋数;
			this->種類 = 種類;
			this->ランク = ランク;
			this->Lv = Lv;

			雑魚モンスター[0] = 0;
			雑魚モンスター[1] = 1;
			雑魚モンスター[2] = 2;
			ボスモンスター = 3;
			//部屋

			//位置-保留

			for (int a = 0; a < CV::最大ギルド数; a++)
			{
				is発見[a] = false;
			}


			for (int a = 0; a < 部屋数; a++)
			{
				部屋.emplace_back();
				部屋[a].is探索[0] = false;
				部屋[a].地図 = -1;

				if (a == 部屋数 - 1)
				{
					部屋[a].種類 = RoomType::ボス;
					部屋[a].地図 = std::min(99,no + 10);
				}
				else if (a == 部屋数 - 2)
				{
					部屋[a].地図 = std::min(99, no + 1);
					部屋[a].種類 = RoomType::地図;
				}
				else if (a % 2 == 0)
				{
					部屋[a].種類 = RoomType::魔物;
				}
			}
		}

		void 探索率計算(int ギルドID)
		{
			double n = 0;

			if (部屋.size() <= 0)
			{
				探索率[ギルドID] = 0;
				return;
			}

			for (int a = 0; a < 部屋.size(); a++)
			{
				if (部屋[a].is探索[ギルドID] == true) { n++; }
			}

			探索率[ギルドID] = n / 部屋.size();
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

		int 残り財宝;
		int 最大財宝;
		int 残り地図;
		int 最大地図;

		MonsterNo ボスモンスター;
		MonsterNo 雑魚モンスター[3];//地形種で固定？

		double 探索率[CV::最大ギルド数];
		bool is発見[CV::最大ギルド数];//ダンジョン発見済みフラグ
		bool is新発見[CV::最大ギルド数];//UI用
	};

	std::vector<Dungeon> Dungeon::data;
}