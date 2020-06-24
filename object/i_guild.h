//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルドとパーティ相互参照可能にするためのインターフェース*/
	//素材、投資効果、ギルマス効果などを参照する必要があるのは一部
	class I_Guild
	{
	private:

	public:
		int id = 0;

		EnumArray<int[CV::最大素材ランク], CraftType> 素材数;
		EnumArray<bool[CV::最大素材ランク], CraftType> is素材発見;

		double 資金 = 123456789;
		MSkillType 選択戦術 = MSkillType::COUNT;
		int 人事ポイント = 10;
		int 名声 = 100;

		//従業員一覧
		std::vector<Warker*> ギルメン;

		EnumArray<std::vector<Warker*>, CraftType> 製造メンバー;

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 投資Lv;
		EnumArray<double, ManagementType> 投資経験値;

		int 集客力 = 100;//10で割った数値が一日の来客期待値

		double 集客補正 = 1.0;
		double 価格補正 = 1.0;

		double 戦闘経験補正 = 1.0;
		double 技術経験補正 = 1.0;
		
		double 素材節約 = 0.0;//確率

		double 未開探索 = 0;//未探索部屋抽選補正

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
		int 販売可能数[CV::装備種];

		EnumArray < bool,ItemType> is新開発タブ;

		//各種記録_Record
		int 総販売;
		double 総売上;
		int 総製造;
		int 総素材;//探索後増加
		int 総地図;//発見時増加
		int 総討伐;//討伐時増加
		int 総全滅;//全滅時増加

		//日別記録
		std::vector<int> R団員;
		std::vector<double> R資金;
		std::vector<int> R販売;
		std::vector<int> R製造;
		std::vector<int> R素材在庫;
		std::vector<int> R地図数;
		std::vector<int> R討伐数;
		std::vector<int> R全滅数;
		std::vector<int> R名声;
	};
}