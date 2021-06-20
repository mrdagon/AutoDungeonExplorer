//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*色んな所で使う変数*/
	namespace Game
	{
		static GameType 難易度;

		static int 日付 = 0;
		static int 時間 = CV::一時間フレーム数 *6;//初回は6時スタート(仮)
		static int ゲームスピード = 1;
		
		static bool is停止予約 = false;
		static int アニメーション時間 = 0;
		static bool isヘルプ = true;
		static bool isゲーム終了 = false;

		static double 自動回復 = 0.1;//自動回復基準値(仮)
		static double 地図発見探索率 = 0.5;
		static double ボス発見探索率 = 0.7;
		static double 基礎未探索部屋発見率 = 0.1;

		static int 最大解像度W = 1600, 最大解像度H = 900;
		//
		static bool isメインクエスト = false;//メインクエスト終了フラグ

		//60F = 10分、360= 1時間
		static int 起床時間 = CV::一時間フレーム数 * 6;//6時
		static int 始業時間 = CV::一時間フレーム数 * 8;//8時
		static int 終業時間 = CV::一時間フレーム数 * 20;//18時
		static int 就寝時間 = CV::一時間フレーム数 * 22;//22時
		static int 日没時間 = CV::一時間フレーム数 * 24;//22時

		static bool is仕事中;

		static bool isデバッグ大きさ表示 = false;

		static bool is直前スキル自動習得 = false;

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}
	};
}