﻿//Copyright © 2019 (´･@･)
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

			//連結
			次ダンジョン[0] = no + 10;
			次ダンジョン[1] = no + 1;
			次ダンジョン[2] = 0;

			for (int a = 0; a < CV::最大ギルド数; a++)
			{
				is発見[a] = false;
			}

			for (int a = 0; a < 3; a++)
			{
				if (次ダンジョン[a] >= 100)
				{
					次ダンジョン[a] = 99;
				}
			}

			for (int a = 0; a < 部屋数; a++)
			{
				部屋.emplace_back();
				部屋[a].is探索[0] = false;
				部屋[a].地図 = -1;

				if (a == 部屋数 - 1)
				{
					部屋[a].種類 = RoomType::ボス;
					部屋[a].地図 = 次ダンジョン[0];
					部屋[a].素材種 = MaterialType::宝石;
				}
				else if (a == 部屋数 - 2)
				{
					部屋[a].地図 = 次ダンジョン[1];
					部屋[a].種類 = RoomType::素材;

					switch (Rand::Get(2))
					{
					case 0:部屋[a].素材種 = MaterialType::金属; break;
					case 1:部屋[a].素材種 = MaterialType::石材; break;
					case 2:部屋[a].素材種 = MaterialType::木材; break;
					}
				}
				else if (a % 2 == 0)
				{
					部屋[a].種類 = RoomType::魔物;
					switch (Rand::Get(2))
					{
					case 0:部屋[a].素材種 = MaterialType::羽毛;break;
					case 1:部屋[a].素材種 = MaterialType::骨牙;break;
					case 2:部屋[a].素材種 = MaterialType::皮革;break;
					}
				}
				else
				{
					部屋[a].種類 = RoomType::素材;

					switch (Rand::Get(2))
					{
					case 0:部屋[a].素材種 = MaterialType::金属;break;
					case 1:部屋[a].素材種 = MaterialType::石材;break;
					case 2:部屋[a].素材種 = MaterialType::木材;break;
					}
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
		bool isボス戦中 = false;
		bool isボス生存 = true;
		int ボス痕跡 = 0;

		MonsterNo ボスモンスター;
		MonsterNo 雑魚モンスター[3];//地形種で固定？
		MaterialType 獲得素材[2];//地形種で固定？
		int 次ダンジョン[3];//要らない？

		double 探索率[CV::最大ギルド数];
		bool is発見[CV::最大ギルド数];//ダンジョン発見済みフラグ

		bool is新発見[CV::最大ギルド数];//UI用
	};

	std::vector<Dungeon> Dungeon::data;
}