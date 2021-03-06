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
		static std::vector<Material> data;

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
			File file_data("file/data/quest.dat", FileMode::Read, true);
			File file_csv("file/data/quest.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

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
			}

		}

	};


	std::vector<Material> Material::data;
}