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
		
		static bool is停止 = false;
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

		//UI関連の変数
		static EnumArray<CraftType, ItemType> 対応レシピ;

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}
	};

	namespace Config
	{
		//コンフィグ項目
		static int BGM設定 = 1, SE設定 = 1;
		static double BGM音量;//設定値の２乗/100になる
		static double SE音量;//

		static int 解像度設定 = 9;
		static int 解像度W = 1600, 解像度H = 900;

		enum class WindowmodeType
		{
			ウィンドウ,
			等倍フルスクリーン,
			二倍フルスクリーン,
			四倍フルスクリーン,
			COUNT
		};

		static WindowmodeType ウィンドウモード = WindowmodeType::ウィンドウ;

		static bool is装備自動更新 = true;
		static bool isボス戦時等速 = true;
		static bool is夜間加速 = true;

		static bool isスキル習得時停止 = false;

		static bool is超加速モード = false;
		static int ゲーム速度変更倍率 = 4;

		static bool isヘルプ詳細 = false;
	}
}