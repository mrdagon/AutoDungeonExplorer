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
		inline static std::vector<std::array<int, CV::上限素材ランク>> 必要数;
		static EnumArray<Recipe,ItemType> 素材種;

		CraftType メイン素材;
		CraftType サブ素材;

		static bool LoadRecipeData()
		{
			File file_必要数("file/data/request_number.dat", FileMode::Read, true);
			int data_count = 0;
			file_必要数.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				必要数.emplace_back();

				for (int a = 0; a < CV::上限素材ランク; a++)
				{
					file_必要数.Read(必要数[i][a]);//画像ID
				}			
			}



			File file_素材種("file/data/request_type.dat", FileMode::Read, true);

			file_素材種.Read(data_count);

			for (int i = 0; i < (int)ItemType::COUNT; i++)
			{
				//file_素材種.Read(素材種[(ItemType)i].メイン素材);//画像ID
				//file_素材種.Read(素材種[(ItemType)i].サブ素材);//画像ID
			}


			return true;
		}
	};

	EnumArray<Recipe, ItemType> Recipe::素材種;
}