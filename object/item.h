//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class Recipe
	{
	public:
		ID_Material ID;
		int 必要数;
	};

	/*装備品、アイテム*/
	class Item
	{
	private:
	public:
		inline static std::vector<Item> equip_data;
		inline static std::vector<Item> accessory_data;

		Image* image;

		ID_Item ID = 0;
		std::string 名前;
		std::string 説明;

		int ランク;

		ItemType 種類;

		PassiveSkill* Pスキル[1] = { nullptr };//最大１個まで
		int PスキルLv = 0;

		//攻撃力等のステータス、追加されるスキル等
		EnumArray<int, StatusType> ステ;

		std::vector<Recipe> レシピ;

		Item(){}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//品質と経験値を読込
		}



		//外部データ読込
		static void LoadData()
		{
			//装備品の読み込み
			LoadEquipData();
			LoadAccessoryData();
		}
	private:
		static void LoadEquipData()
		{
			//装備品の読み込み
			File file_data("file/data/item.dat", FileMode::Read, true);
			File file_csv("file/data/item.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				accessory_data.emplace_back();
				auto& it = accessory_data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;
				file_data.Read(it.種類);

				file_data.Read(dummy);
				if (dummy < 0) { dummy = 0; }
				it.Pスキル[0] = &PassiveSkill::data[dummy];

				file_data.Read(it.PスキルLv);

				file_data.Read(it.ランク);

				file_data.Read(it.ステ[StatusType::HP]);
				file_data.Read(it.ステ[StatusType::力]);
				file_data.Read(it.ステ[StatusType::技]);
				file_data.Read(it.ステ[StatusType::知]);
				file_data.Read(it.ステ[StatusType::物防]);
				file_data.Read(it.ステ[StatusType::魔防]);
				file_data.Read(it.ステ[StatusType::命中]);
				file_data.Read(it.ステ[StatusType::回避]);
				file_data.Read(it.ステ[StatusType::会心]);

			}
		}

		static void LoadAccessoryData()
		{
			//装備品の読み込み
			File file_data("file/data/accessory.dat", FileMode::Read, true);
			File file_csv("file/data/accessory.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				accessory_data.emplace_back();
				auto& it = accessory_data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;
				file_data.Read( dummy);//画像ID
				it.種類 = ItemType::アクセサリー;

				file_data.Read( dummy );
				if (dummy < 0) { dummy = 0; }
				it.Pスキル[0] = &PassiveSkill::data[dummy];

				file_data.Read(it.PスキルLv);

				file_data.Read(it.ランク);

				file_data.Read(it.ステ[StatusType::HP]);
				file_data.Read(it.ステ[StatusType::力]);
				file_data.Read(it.ステ[StatusType::技]);
				file_data.Read(it.ステ[StatusType::知]);
				file_data.Read(it.ステ[StatusType::物防]);
				file_data.Read(it.ステ[StatusType::魔防]);
				file_data.Read(it.ステ[StatusType::命中]);
				file_data.Read(it.ステ[StatusType::回避]);
				file_data.Read(it.ステ[StatusType::会心]);

			}
		}

	};



}