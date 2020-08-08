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

		Material(int ID, IconType アイコン, CraftType 製造部門, int Lv):
			ID(ID),
			アイコン(アイコン),
			製造部門(製造部門),
			Lv(Lv),
			品質(Lv-1)
		{
			for (auto& it : レシピ)
			{
				it.id = 0;
				it.製造確率 = 100;
			}
		}

		int ID = 0;

		std::string 名前 = "素材(仮)";
		std::string 説明 = "説明(仮)";
		IconType アイコン = IconType::資金;
		CraftType 製造部門 = CraftType::裁縫;

		int 品質 = 0;//高品質製造確率に影響

		int 消費数 = 5;//装備１個作るのに消費する数
		bool isレア = false;
		int Lv = 0;

		struct Recipe
		{
			ID_Item id;
			int 製造確率;
		};

		int 合計確率 = 200;

		Recipe レシピ[CV::最大素材レシピ];
	};

	void LoadMaterialClass()
	{
		Material::data.emplace_back(0, IconType::木材, CraftType::木工, 1);
		Material::data.emplace_back(1, IconType::骨材, CraftType::魔術, 1);
		Material::data.emplace_back(2, IconType::鉄材, CraftType::鍛造, 1);
		Material::data.emplace_back(3, IconType::皮材, CraftType::裁縫, 1);
		Material::data.emplace_back(4, IconType::木材, CraftType::木工, 2);
		Material::data.emplace_back(5, IconType::骨材, CraftType::魔術, 2);
		Material::data.emplace_back(6, IconType::鉄材, CraftType::鍛造, 2);
		Material::data.emplace_back(7, IconType::皮材, CraftType::裁縫, 2);

		Material::data[0].レシピ[0].id = 3;//盾弓
		Material::data[0].レシピ[1].id = 4;
		Material::data[4].レシピ[0].id = 3;
		Material::data[4].レシピ[1].id = 4;

		Material::data[1].レシピ[0].id = 5;//杖２種
		Material::data[1].レシピ[1].id = 6;
		Material::data[5].レシピ[0].id = 5;
		Material::data[5].レシピ[1].id = 6;

		Material::data[2].レシピ[0].id = 1;//剣、斧、鎧
		Material::data[2].レシピ[1].id = 2;
		Material::data[2].レシピ[2].id = 7;
		Material::data[6].レシピ[0].id = 1;
		Material::data[6].レシピ[1].id = 2;
		Material::data[6].レシピ[2].id = 7;
		Material::data[2].合計確率 = 300;
		Material::data[6].合計確率 = 300;

		Material::data[3].レシピ[0].id = 8;//帷子、ローブ
		Material::data[3].レシピ[1].id = 9;
		Material::data[7].レシピ[0].id = 8;
		Material::data[7].レシピ[1].id = 9;

	}

	std::vector<Material> Material::data;
}