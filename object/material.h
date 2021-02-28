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
			Lv(Lv)
		{
		}

		int ID = 0;

		std::string 名前 = "素材(仮)";
		std::string 説明 = "説明(仮)";
		IconType アイコン = IconType::資金;
		CraftType 製造部門 = CraftType::木材;

		int 価格 = 10;
		int Lv = 0;

		static void LoadData()
		{
			Material::data.emplace_back(0, IconType::木材, CraftType::木材, 1);
			Material::data.emplace_back(1, IconType::骨材, CraftType::石材, 1);
			Material::data.emplace_back(2, IconType::鉄材, CraftType::鉄材, 1);
			Material::data.emplace_back(3, IconType::皮材, CraftType::革材, 1);
			Material::data.emplace_back(4, IconType::木材, CraftType::骨材, 2);
			Material::data.emplace_back(5, IconType::骨材, CraftType::魔材, 2);
		}

	};


	std::vector<Material> Material::data;
}