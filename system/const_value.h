//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	//各種定数
	namespace CV
	{
		constexpr double バージョン = 0.001;
		constexpr bool isデバッグ = true;

		constexpr int パーティ人数 = 5;
		constexpr int 最大パーティ数 = 5;

		constexpr int 最大控え人数 = 36;

		constexpr int 最大素材種 = 100;
		constexpr int 最大素材レシピ = 10;

		constexpr int 最大収集種 = 10;//1ダンジョンに設定可能な収集アイテム最大数

		constexpr int 職業数 = 5;

		constexpr int 装備種 = 240;
		constexpr int Pスキル種 = 64;
		constexpr int Aスキル種 = 32;

		constexpr int 最大装備ランク = 4;//0普通、1良い、2輝く、3伝説

		constexpr int 最大投資Lv = 10;
		constexpr int 最大技術Lv = 10;

		constexpr int 最大ゲーム倍速 = 64;

		constexpr int 最大Aスキル数 = 4;//一人が覚えるスキル数
		constexpr int 最大Pスキル数 = 7;

		constexpr int 最大Pスキル習得リスト = 48;
		constexpr int 最大Aスキル習得リスト = 8;
		constexpr int 最大キーPスキル習得リスト = 3;

		constexpr int ジョブAスキル数 = 2;
		constexpr int 最大装備Aスキル数 = 2;
		constexpr int 最大装備Pスキル数 = 2;
		constexpr int 装備部位数 = 3;


		constexpr int ウィンドウ数 = 10;

		constexpr int 要求経験値 = 200;

		constexpr int 一時間フレーム数 = 360;

		constexpr int 戦闘基本ウェイト = 20;
	}
}