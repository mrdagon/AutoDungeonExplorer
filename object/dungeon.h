//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "room.h"

namespace SDX_ADE
{
	using namespace SDX;

	/*ダンジョンの部屋*/
	class Room
	{
	public:
		Room() {}

		RoomType 種類;
		bool is探索 = false;//探索し終わったかどうか
		bool is入場 = false;//同時に２パーティ探索するのを防ぐ
		int 地図 = -1;//0以上なら接続先MapIndex
	};

	/*ダンジョン*/
	class Dungeon
	{
	public:
		inline static std::vector<Dungeon> data;

		/*暫定自動生成*/
		static void Add(int no,std::string 名前, IconType 種類, int 部屋数, int ランク, int Lv, int 地図数 , bool isエリアボス)
		{
			data.emplace_back();
			data[no].Init(no, 名前, 種類, 部屋数, ランク, Lv, 地図数, isエリアボス);
		}

		/*暫定処理*/
		void Init(int no, std::string 名前, IconType 種類, int 部屋数, int ランク, int Lv, int 地図数, bool isエリアボス)
		{
			ID = no;
			this->名前 = 名前;
			this->部屋数 = 部屋数;
			this->Img = &MIcon::アイコン[種類];
			this->層 = ランク;
			this->Lv = Lv;

			発見財宝 = 0;
			発見地図 = 0;
			最大財宝 = 3;
			最大地図 = 地図数;

			雑魚モンスター.emplace_back(0, Lv, false);
			雑魚モンスター.emplace_back(1, Lv, false);
			雑魚モンスター.emplace_back(2, Lv, false);
			ボスモンスター.emplace_back(3, Lv, true);

			//位置-保留
			is発見 = false;

			int buf地図 = 最大地図;
			int buf財宝 = 最大財宝;

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
					buf財宝--;
				}
				else if (a % 2 == 0)
				{
					部屋[a].種類 = RoomType::ザコ;
				} else {
					部屋[a].種類 = RoomType::素材;
				}
			}


			for (int a = 0; a < CV::最大収集種; a++)
			{
				伐採素材[a] = 0;
				採掘素材[a] = 2;
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

			for (int a = 0; a < (int)部屋.size(); a++)
			{
				if (部屋[a].is探索 == true) { n++; }
			}

			探索率 = n / 部屋.size();
		}

		ID_Dungeon ID;
		std::string 名前;
		Image* Img;
		int 部屋数;
		std::vector<Room>部屋;

		int Lv;//敵の強さ等
		int 層;//0~4
		bool isボス生存 = true;
		bool isボス発見 = false;

		int 発見財宝;
		int 最大財宝;
		int 発見地図;
		int 最大地図;

		std::vector<Monster> ボスモンスター;
		std::vector<Monster> 雑魚モンスター;

		double 探索率;
		bool is発見;//ダンジョン発見済みフラグ
		bool is新規;//UI用

		int 採掘素材[CV::最大収集種];
		int 伐採素材[CV::最大収集種];

		double レア収集率 = 0.1;

		static bool SaveLoad(File& ファイル , FileMode 読み書きモード)
		{
			//Loadなら再読み込み

			//部屋状態


			//

			//is発見;
			//is新規;
			//isボス生存
			//isボス発見
		}

		static void LoadData()
		{

		}

	};
}