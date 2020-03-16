//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルドとパーティ相互参照可能にするためのインターフェース*/
	class I_Guild
	{
	private:

	public:
		int id = 0;

		EnumArray<int[CV::最大素材ランク], CraftType> 素材数;
		EnumArray<bool[CV::最大素材ランク], CraftType> is素材発見;

		double 資金 = 123456789;
		//double 現在MP = 100;
		Management* 選択戦術 = 0;
		int 人事ポイント = 10;

		//従業員一覧
		std::vector<Warker*> ギルメン;

		EnumArray<std::vector<Warker*>, CraftType> 製造メンバー;

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 部門Lv;
		EnumArray<double, ManagementType> 部門経験値;

		double 集客力;
		double 集客待ち;

		//製造関連
		EnumArray<double, CraftType> 必要製造力;
		EnumArray<double, CraftType> 合計製造力;
		EnumArray<double, CraftType> 製造進行度;

		EnumArray<int, CraftType> 完成品;
		EnumArray<bool, CraftType> is装備修復;

		EnumArray<int, CraftType> 壊れた装備;

		EnumArray<int, CraftType> 製造Lv;
		EnumArray<double, CraftType> 製造経験;

		EnumArray<bool, CraftType> 製造ゲージ色;
		//--製造特殊効果とか(未実装)

		//装備品
		bool is装備開発[CV::装備種];
		bool is新規[CV::装備種];
		int 装備所持数[CV::装備種];

		EnumArray < bool,ItemType> is新開発タブ;
	};
}