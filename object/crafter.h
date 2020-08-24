//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class CraftSkill
	{
	public:
		inline static std::vector<CraftSkill> data;

		enum class CraftSkillType
		{
			素材消費減少,
			品質経験増加,
			製造速度増加,
			レア製造増加,
			COUNT
		};

		int ID;
		std::string 名前;
		std::string 説明;
		CraftType 部門;
		double 効果値;

		static void LoadData()
		{

		}
	};

	/*従業員ベースクラス*/
	class Crafter
	{
	public:
		void Make(int id, int Lv , CraftType 配属 , std::string 名前)
		{
			this->ID = id;
			this->Lv = Lv;
			this->名前 = 名前;
			配置部門 = 配属;
			Img = &MUnit::ユニット[UnitImageType(0)];
		}

		void 基礎ステータス計算()
		{

		}

		//●人事関連
		//所属あり、就活中、ニートの３パターン
		int ID;

		int 所属;//-1なら無所属
		CraftType 配置部門;

		//●固定ステータス
		std::string 名前;
		ImagePack* Img;

		//●Lvアップ時等更新ステータス
		int Lv;
		double 経験値 = 0;
		double 製造力 = 10;

		int スキルID[CV::最大製造スキル数];
		int スキル習得Lv[CV::最大製造スキル数];

		//UI表示用
		bool isレベルアップ演出 = false;
	};
}