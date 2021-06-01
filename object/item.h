//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

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
		int PスキルLv[1] = { 0 };

		//攻撃力等のステータス、追加されるスキル等
		EnumArray<int, StatusType> ステ;

		int レアリティ;
		int 開放ポイント;
		int 目標日数;
		int 持越ポイント;

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

		CraftType GetMainRecipe(std::array<int, CV::上限素材ランク>& 必要数)
		{
			for (int i = 0; i < CV::上限素材ランク; i++)
			{
				必要数[i] = Recipe::必要数[ランク][i];
			}
			return Recipe::素材種[種類].メイン素材;
		}

		CraftType GetSubRecipe(std::array<int, CV::上限素材ランク>& 必要数)
		{

			for (int i = 0; i < CV::上限素材ランク; i++)
			{
				必要数[i] = Recipe::必要数[std::min(ランク - 1, 0)][i];
			}
			return Recipe::素材種[種類].サブ素材;
		}
	private:
		static void LoadEquipData()
		{
			//装備品の読み込み
			File file_data("file/data/item.dat", FileMode::Read, true);
			File file_csv("file/data/item.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				equip_data.emplace_back();
				auto& it = equip_data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;
				file_data.Read(it.種類);

				it.image = &MIcon::装備品[(int)it.種類];

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


				CraftType mct = CraftType::木材;
				CraftType sct = CraftType::木材;
				switch (it.種類)
				{
					//武器
					case ItemType::大剣:mct = CraftType::鉄材; sct = CraftType::骨材;
						break;
					case ItemType::剣盾:mct = CraftType::木材; sct = CraftType::鉄材;
						break;
					case ItemType::大盾:mct = CraftType::鉄材; sct = CraftType::革材;
						break;
					case ItemType::円盤:mct = CraftType::骨材; sct = CraftType::石材;
						break;
					case ItemType::斧:mct = CraftType::鉄材; sct = CraftType::木材;
						break;
					case ItemType::刀:mct = CraftType::鉄材; sct = CraftType::石材;
						break;
					case ItemType::弓:mct = CraftType::木材; sct = CraftType::革材;
						break;
					case ItemType::神杖:mct = CraftType::魔材; sct = CraftType::骨材;
						break;
					case ItemType::錫杖:mct = CraftType::石材; sct = CraftType::骨材;
						break;
					case ItemType::導杖:mct = CraftType::魔材; sct = CraftType::木材;
						break;
					case ItemType::書物:mct = CraftType::木材; sct = CraftType::魔材;
						break;
					case ItemType::水晶:mct = CraftType::石材; sct = CraftType::魔材;
						break;
					//防具
					case ItemType::重鎧:mct = CraftType::鉄材; sct = CraftType::石材;
						break;
					case ItemType::軽鎧:mct = CraftType::革材; sct = CraftType::鉄材;
						break;
					case ItemType::軽装:mct = CraftType::革材; sct = CraftType::石材;
						break;
					case ItemType::外套:mct = CraftType::革材; sct = CraftType::魔材;
						break;
				}
			}
		}

		static void LoadAccessoryData()
		{
			//装備品の読み込み
			File file_data("file/data/accessory.dat", FileMode::Read, true);
			File file_csv("file/data/accessory.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

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
				it.image = &MIcon::装備品[(int)it.種類];

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

				file_data.Read(it.レアリティ);
				file_data.Read(it.開放ポイント);
				file_data.Read(it.目標日数);
				file_data.Read(it.持越ポイント);
				//アクセサリーはレシピ無し
			}
		}

	};



}