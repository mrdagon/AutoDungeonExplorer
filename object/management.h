//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*経営戦術*/
	class Management
	{
	private:
	public:
		static std::vector<Management> data;

		Management(int ID,int Lv,ManagementType 系統, int 資金 , bool is永続):
			ID(ID),Lv(Lv),系統(系統),消費資金(資金),is永続(is永続)
		{

		}


		int ID;
		int Lv;//習得レベル
		std::string 名前;
		std::string 説明文;
		ManagementType 系統;
		int 消費資金;//基礎値
		IconType アイコン = IconType::資金;
		bool is永続;//単発効果 or 永続効果

		/*戦術実行効果*/
		void Active()
		{

		}

		static void Load()
		{
			//仮データ作成
			data.emplace_back(0, 0, ManagementType::経営, 10000, false);
			data.emplace_back(1, 0, ManagementType::経営, 100000, true);
			data.emplace_back(2, 0, ManagementType::人事, 10000, false);
			data.emplace_back(3, 0, ManagementType::人事, 100000, true);
			data.emplace_back(4, 0, ManagementType::製造, 10000, false);
			data.emplace_back(5, 0, ManagementType::製造, 100000, true);
			data.emplace_back(6, 0, ManagementType::探索, 10000, false);
			data.emplace_back(7, 0, ManagementType::探索, 100000, true);

			data[2].アイコン = IconType::求人;
			data[3].アイコン = IconType::求人;
			data[4].アイコン = IconType::製造;
			data[5].アイコン = IconType::製造;
			data[6].アイコン = IconType::迷宮;
			data[7].アイコン = IconType::迷宮;


			//経営、集客力上昇が何回でも使える。名誉点獲得を１回。
			//探索、未探索部屋発見率＋が何回でも使える。探索パーティ＋１が一回だけ。
			//製造、全部門技術Lv上昇が何回でも、素材消費減少が一回だけ。
			//人事、人事ポイント＋１が何回でも使える。志願者数＋１が一回だけ。
		}
	};

	std::vector<Management> Management::data;

}