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

		constexpr int 最大ギルド数 = 4;
		constexpr int パーティ人数 = 5;
		constexpr int 最大パーティ数 = 10;
		constexpr int 最大素材ランク = 5;
		constexpr int 素材種 = 7;
		constexpr int 装備種 = 45;

		constexpr int 月日数 = 20;

		constexpr int 最大Aスキル数 = 3;
		constexpr int 最大Pスキル数 = 6;
		
		constexpr bool isデバッグ = true;

		constexpr int ウィンドウ数 = 11;

		constexpr int 要求経験値 = 200;

		constexpr int 一時間フレーム数 = 360;

		constexpr int 戦闘基本ウェイト = 20;
		//システム

		constexpr int 部門レベルアップ経験値[5] =
		{
			100,
			200,
			300,
			400,
			500
		};
		
	}
	//各種変数
	namespace SV
	{
		bool gui_check = false;
	}

}