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

		constexpr int 最大ギルド数 = 1;
		constexpr int パーティ人数 = 5;
		constexpr int 最大パーティ数 = 5;
		constexpr int 最大素材ランク = 20;


		constexpr int 装備種 = 240;
		constexpr int Pスキル種 = 64;
		constexpr int Aスキル種 = 32;

		constexpr int 最大装備ランク = 10;

		constexpr int 最大投資Lv = 10;
		constexpr int 最大技術Lv = 10;

		constexpr int 最大ゲーム倍速 = 64;

		constexpr int 最大Aスキル数 = 4;//一人が覚えるスキル数
		constexpr int 最大Pスキル数 = 7;
		
		constexpr bool isデバッグ = true;

		constexpr int ウィンドウ数 = 10;

		constexpr int 要求経験値 = 200;

		constexpr int 一時間フレーム数 = 360;

		constexpr int 戦闘基本ウェイト = 20;
	}
	//各種変数
	namespace SV
	{
		bool gui_check = false;
	}

}