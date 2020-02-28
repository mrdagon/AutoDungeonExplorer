//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*メインゲームで使う変数*/
	namespace Game
	{
		static int 日付 = 0;//一月28日、一年336日
		static int 時間 = CV::一時間フレーム数 *6;
		static int 人口 = 123;
		static int ゲームスピード = 1;
		static bool is停止 = false;
		static int アニメーション時間 = 0;
		static bool isヘルプ = true;

		static bool is翌日スキップ = false;
		
		//コンフィグ項目
		static double BGM音量 = 0.3;//
		static double SE音量 = 0.3;//
		static bool isフルスクリーン = false;
		static int 解像度W = 1600 , 解像度H = 900;
		static int 最大解像度W = 1600, 最大解像度H = 900;

		static int BGM設定 = 5, SE設定 =5 ,解像度設定 = 9;

		static bool is夜間加速 = true;

		//60F = 10分、360= 1時間
		static int 起床時間 = CV::一時間フレーム数 * 6;//6時
		static int 始業時間 = CV::一時間フレーム数 * 8;//8時
		static int 終業時間 = CV::一時間フレーム数 * 18;//18時
		static int 就寝時間 = CV::一時間フレーム数 * 22;//22時

		static bool is仕事中;
	};
}