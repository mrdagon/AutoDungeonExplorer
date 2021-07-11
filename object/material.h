//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*素材*/
	class Material
	{
	private:
	public:
		//inline static std::vector<Material> data;
		static EnumArray<Material[CV::上限素材ランク], CraftType> data;

		Material()
		{}

		Image* image;
		ID_Material ID = 0;

		std::string 名前 = "素材(仮)";
		std::string 説明 = "説明(仮)";

		CraftType 種類 = CraftType::木材;
		int ランク = 0;
		int 価格 = 10;

		static void LoadData()
		{
			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				auto ct = CraftType(a);
				for (int b = 0; b < CV::上限素材ランク; b++)
				{
					data[ct][b].種類 = ct;
					data[ct][b].ランク = b;
					data[ct][b].image = &MIcon::素材[ct];
				}
			}


			File file_data("file/data/material.dat", FileMode::Read, true);
			File file_csv("file/data/material.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				CraftType 種類;
				int ランク;
				int 価格;

				file_data.Read(種類);
				file_data.Read(ランク);
				ランク--;
				file_data.Read(価格);
				
				if ((int)種類 < 0 || ランク < 0 || ランク >= CV::上限素材ランク)
				{
					種類 = CraftType::木材;
					ランク = 0;
					continue;
				}

				data[種類][ランク].ID = i;
				data[種類][ランク].種類 = 種類;
				data[種類][ランク].ランク = ランク;
				data[種類][ランク].価格 = 価格;
				data[種類][ランク].image = &MIcon::素材[種類];

				data[種類][ランク].名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					data[種類][ランク].説明 = strs[i][1];
				}

			}
		}
	};

	EnumArray<Material[CV::上限素材ランク], CraftType> Material::data;

}