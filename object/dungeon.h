//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;



	/*ダンジョン*/
	class Dungeon
	{
	public:
		/*ダンジョンの部屋*/
		class Room
		{
		public:
			Room() {}
			Room(RoomType 種類) { this->種類 = 種類; }

			RoomType 種類;
			bool is探索 = false;//探索し終わったかどうか
			bool is入場 = false;//同時に２パーティ探索するのを防ぐ - お宝探索用
		};

		inline static std::vector<Dungeon> data;//Guild等から参照するので、static

		Image* image;

		ID_Dungeon ID;//0～階層と共用
		int 層 = 0;
		std::string 名前;
		std::string 説明;

		std::vector<Room>部屋;

		int ボスLv[CV::最大魔物出現数];
		int 雑魚Lv[CV::最大魔物出現数];

		bool isボス発見 = false;
		bool isボス戦闘中 = false;
		bool isボス生存 = true;

		int 発見財宝数 = 0;
		int 最大財宝数;
		bool is地図発見[CV::最大地図数] = { false,false };

		std::vector<Item*> 財宝;

		std::vector<MonsterClass*> ボスモンスター;
		std::vector<MonsterClass*> 雑魚モンスター;

		double 探索率 = 0;

		bool is発見 = false;//ダンジョン発見済みフラグ
		bool is新規 = false;//UI用

		int ボス地図ID;//0ならボス地図なし
		int ボス発見探索率;

		int 探索地図ID[CV::最大地図数];//0なら地図なし
		int 地図発見探索率[CV::最大地図数];

		/*暫定処理*/
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

		bool Isボス戦闘可能(int 探索部屋数)
		{
			return 探索部屋数 == 0 &&
				isボス発見 &&
				isボス生存 &&
				部屋[CV::ボス部屋ID].is入場 == false;
		}

		int Is階段発見可能()
		{
			for (int i = 0; i < CV::最大地図数; i++)
			{
				if ( is地図発見[i] == false &&
					 地図発見探索率[i] <= 探索率 * 100
					)
				{
					return i;
				}
			}

			return -1;
		}

		static void LoadData()
		{
			File file_data("file/data/dungeon.dat", FileMode::Read, true);
			File file_csv("file/data/dungeon.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			data.clear();

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				data.emplace_back();
				auto& it = data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;
				it.層 = i / 10;
				it.image = &MIcon::ダンジョン[i/10];


				for (int b = 0; b < CV::最大魔物出現数 ; b++)
				{
					file_data.Read(dummy);
					it.ボスモンスター.emplace_back(&MonsterClass::data[dummy]);
					file_data.Read(it.ボスLv[b]);

					file_data.Read(dummy);
					it.雑魚モンスター.emplace_back(&MonsterClass::data[dummy]);
					file_data.Read(it.雑魚Lv[b]);
				}
				
				file_data.Read(it.ボス地図ID);

				for (int b = 0; b < CV::最大地図数; b++)
				{
					file_data.Read(it.探索地図ID[b]);//探索地図番号
				}

				for (int b = 0; b < CV::最大財宝配置数; b++)
				{
					file_data.Read(dummy);
					if (dummy > 0)
					{
						it.財宝.emplace_back(&Item::accessory_data[dummy]);
					}
				}
				it.最大財宝数 = (int)it.財宝.size();

				file_data.Read(dummy);//部屋数


				file_data.Read(it.ボス発見探索率);
				if (it.ボス発見探索率 == 0)
				{
					it.ボス発見探索率 = 9999;
					it.isボス生存 = false;
				}

				for (int b = 0; b < CV::最大地図数; b++)
				{
					file_data.Read(it.地図発見探索率[b]);
					if (it.地図発見探索率[b] == 0 || b == 1)
					{
						it.地図発見探索率[b] = 9999;
					}
				}

				//部屋の設定//
				for (int i = 0; i < dummy; i++)
				{
					it.部屋.emplace_back( i % 2==0 ? RoomType::ザコ : RoomType::素材 );
				}

				for (int i = 10; i < it.財宝.size()+10; i++)
				{
					it.部屋[i].種類 = RoomType::財宝;
				}

				for (int b = 0 ; b < CV::最大地図数; b++)
				{
					if (it.地図発見探索率[b] < 100)
					{
						it.部屋[b].種類 = RoomType::階段;
					}
				}

				if (it.ボス発見探索率 < 100)
				{
					it.部屋[CV::ボス部屋ID].種類 = RoomType::ボス;
				}

			}
		}

		static void ResetData()
		{
			LoadData();

			for (auto& it : data)
			{
				it.isボス生存 = true;
				it.isボス発見 = false;

				for (int b = 0; b < CV::最大地図数; b++)
				{
					it.is地図発見[b] = false;
				}
				it.is新規 = false;
				it.is発見 = false;
				it.探索率 = 0;

				for (auto& it2 : it.部屋)
				{
					it2.is入場 = false;
					it2.is探索 = false;
				}
			}
			data[0].is発見 = true;

		}

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



	};
}