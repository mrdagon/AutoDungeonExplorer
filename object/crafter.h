//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*従業員ベースクラス*/
	class Crafter
	{
	private:

	public:

		Crafter(){}

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

		bool is特殊人材;//(解雇不可、イベントに絡む等)

		//●人事関連
		//所属あり、就活中、ニートの３パターン
		int ID;//data配列内のID

		int 所属;//-1なら無所属
		CraftType 配置部門;

		//●固定ステータス
		std::string 名前;
		ImagePack* Img;

		//int PスキルID[CV::最大Pスキル数];
		//bool isPスキル習得[CV::最大Pスキル数];

		//●Lvアップ時等更新ステータス
		int Lv;
		double 経験値 = 0;
		double 製造力 = 10;

		//UI表示用
		bool isレベルアップ演出 = false;
	};
}