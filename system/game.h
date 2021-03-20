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

		static bool is直前スキル自動習得 = false;

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
		static int ゲーム速度変更倍率 = 2;
		static int 最大ゲーム倍速 = 16;

		static bool isヘルプ詳細 = false;

		static bool SaveLoad(FileMode 保存or読み込み)
		{
			//バイナリ形式で保存
			std::string fname = "file/save/";
			fname += TX::Save_コンフィグファイル名;

			File file(fname.c_str(), 保存or読み込み, false);


			if (file.GetFileMode() == FileMode::None)
			{
				return false;
			}

			file.ReadWrite(Config::BGM設定);
			file.ReadWrite(Config::SE設定);
			file.ReadWrite(Config::解像度設定);

			file.ReadWrite(Config::isスキル習得時停止);
			file.ReadWrite(Config::isヘルプ詳細);
			file.ReadWrite(Config::isボス戦時等速);

			file.ReadWrite(Config::ウィンドウモード);

			file.ReadWrite(Config::is夜間加速);
			file.ReadWrite(Config::is装備自動更新);
			file.ReadWrite(Config::is超加速モード);

			file.ReadWrite(Config::ゲーム速度変更倍率);
			file.ReadWrite(Config::最大ゲーム倍速);

			return true;
		}

		static bool isFontDot = true;
		static Font* SFont;
		static Font* LFont;
		static Font* MFont;

		static void Update()
		{
			//音量と解像度設定反映
			int full_rate = 0;

			switch (Config::ウィンドウモード)
			{
			case Config::WindowmodeType::ウィンドウ:
				Config::解像度W = std::min(Config::解像度設定 * 160, Game::最大解像度W);
				Config::解像度H = std::min(Config::解像度設定 * 90, Game::最大解像度H);
				Window::SetSize(Config::解像度W, Config::解像度H);
				Window::SetFullscreen(Config::解像度W == Game::最大解像度W && Config::解像度H == Game::最大解像度H);
				break;
			case Config::WindowmodeType::等倍フルスクリーン:
				full_rate = 1;
				break;
			case Config::WindowmodeType::二倍フルスクリーン:
				if (Game::最大解像度H >= 1080) {
					full_rate = 2;
				}
				else {
					full_rate = 1;
					Config::ウィンドウモード = Config::WindowmodeType::等倍フルスクリーン;
				}
				break;
			case Config::WindowmodeType::四倍フルスクリーン:
				if (Game::最大解像度H >= 2160)
				{
					full_rate = 4;
				}
				else if (Game::最大解像度H >= 1080) {
					full_rate = 2;
					Config::ウィンドウモード = Config::WindowmodeType::二倍フルスクリーン;
				}
				else {
					full_rate = 1;
					Config::ウィンドウモード = Config::WindowmodeType::等倍フルスクリーン;
				}
				break;
			}

			if (full_rate > 0)
			{
				Config::解像度W = Game::最大解像度W / full_rate;
				Config::解像度H = Game::最大解像度H / full_rate;
				Window::SetSize(Config::解像度W, Config::解像度H);
				Window::SetFullscreen(true);
			}

			Config::BGM音量 = Config::BGM設定 * Config::BGM設定 / 100.0;
			Config::SE音量 = Config::SE設定 * Config::SE設定 / 100.0;

			Sound::SetMainVolume(Config::SE音量);
			Music::SetMainVolume(Config::BGM音量);
		}

	}
}