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
		{}


		int ID;
		int Lv;//習得レベル
		std::string 名前;
		std::string 説明文;
		ManagementType 系統;
		int 消費資金;
		int 増加資金;
		int 使用回数;
		IconType アイコン = IconType::資金;
		bool is永続;//単発効果 or 永続効果

		/*戦術実行効果*/
		void Active()
		{

		}

		static void Load()
		{
			//仮データ作成
			data.emplace_back(0, 1, ManagementType::経営, 100000, false);
			data.emplace_back(1, 1, ManagementType::経営, 100000, true);
			data.emplace_back(2, 1, ManagementType::人事, 100000, false);
			data.emplace_back(3, 1, ManagementType::人事, 100000, true);
			data.emplace_back(4, 1, ManagementType::製造, 100000, false);
			data.emplace_back(5, 1, ManagementType::製造, 100000, true);
			data.emplace_back(6, 1, ManagementType::探索, 100000, false);
			data.emplace_back(7, 1, ManagementType::探索, 100000, true);

			data[0].アイコン = IconType::資金;
			data[1].アイコン = IconType::資金;
			data[2].アイコン = IconType::求人;
			data[3].アイコン = IconType::求人;
			data[4].アイコン = IconType::製造;
			data[5].アイコン = IconType::製造;
			data[6].アイコン = IconType::迷宮;
			data[7].アイコン = IconType::迷宮;

			data[0].名前 = "ビラ配り";
			data[1].名前 = "薄利多売";
			data[2].名前 = "新人発掘";
			data[3].名前 = "OJT";
			data[4].名前 = "技術研究";
			data[5].名前 = "低コスト化";
			data[6].名前 = "探索術";
			data[7].名前 = "探索許可＋";

			data[0].説明文 = "集客力が0.5人/day増加";
			data[1].説明文 = "販売価格を一割引にする、来客が二割増";
			data[2].説明文 = "雇用ポイント+1";
			data[3].説明文 = "戦闘経験+10%";
			data[4].説明文 = "ランダムで技術経験値+20%";
			data[5].説明文 = "10%の確率で素材消費半分";
			data[6].説明文 = "未発見部屋を探索する確率が+5%";
			data[7].説明文 = "最大パーティ編成数+1";


			//経営、集客力上昇が何回でも使える。販売価格低下、客数増加
			//人事、人事ポイント＋１が何回でも使える。志願者数＋１が一回だけ。
			//製造、全部門技術Lv上昇が何回でも、素材消費減少が一回だけ。
			//探索、未探索部屋発見率＋が何回でも使える。探索パーティ＋１が一回だけ。
		}
	};

	std::vector<Management> Management::data;

}