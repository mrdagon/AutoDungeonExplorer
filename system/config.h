//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	namespace Config
	{
		//コンフィグ項目
		static bool isウィンドウ = true;
		static int BGM設定 = 1, SE設定 = 1;
		static int 解像度設定 = 9;
		static int 解像度X倍 = 1;

		static bool isボス戦時等速 = true;
		static bool is夜加速 = true;
		static bool is超加速 = false;
		static int フォントID = 0;

		//設定値から計算するやつ
		static double BGM音量;//設定値の２乗/100になる
		static double SE音量;//
		static int 解像度W = 1600, 解像度H = 900;

		static int ゲーム速度変更倍率 = 2;
		static int 最大ゲーム倍速 = 16;

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
			file.ReadWrite(Config::isウィンドウ);
			file.ReadWrite(Config::BGM設定);
			file.ReadWrite(Config::SE設定);
			file.ReadWrite(Config::解像度設定);
			file.ReadWrite(Config::解像度X倍);

			file.ReadWrite(Config::isボス戦時等速);
			file.ReadWrite(Config::is夜加速);
			file.ReadWrite(Config::is超加速);
			file.ReadWrite(Config::フォントID);

			return true;
		}

		static void Update()
		{
			//音量と解像度設定反映

			if (isウィンドウ)
			{
				if (Config::解像度W * 解像度X倍 > Game::最大解像度W || Config::解像度H * 解像度X倍 > Game::最大解像度H)
				{
					解像度X倍 = 1;
				}

				Config::解像度W = std::min(Config::解像度設定 * 160, Game::最大解像度W);
				Config::解像度H = std::min(Config::解像度設定 * 90, Game::最大解像度H);
				Window::SetSize(Config::解像度W * 解像度X倍 , Config::解像度H * 解像度X倍 );
				Window::SetFullscreen(Config::解像度W == Game::最大解像度W && Config::解像度H == Game::最大解像度H);
			}
			else
			{

				Config::解像度W = Game::最大解像度W / 解像度X倍;
				Config::解像度H = Game::最大解像度H / 解像度X倍;
				if (Config::解像度W < 920)
				{
					解像度X倍 = 1;
					Config::解像度W = Game::最大解像度W;
					Config::解像度H = Game::最大解像度H;
				}

				Window::SetSize(Config::解像度W * 解像度X倍, Config::解像度H * 解像度X倍);
				Window::SetFullscreen(true);
			}

			//解像度X倍 = 1;
			Camera::Get()->zoom = 解像度X倍;

			Config::BGM音量 = Config::BGM設定 * Config::BGM設定 / 100.0;
			Config::SE音量 = Config::SE設定 * Config::SE設定 / 100.0;

			Sound::SetMainVolume(Config::SE音量);
			Music::SetMainVolume(Config::BGM音量);

			if (Config::is超加速 == true)
			{
				Config::ゲーム速度変更倍率 = 4;
				Config::最大ゲーム倍速 = 64;
				Game::ゲームスピード = 1;
			} else {
				Config::ゲーム速度変更倍率 = 2;
				Config::最大ゲーム倍速 = 16;
				Game::ゲームスピード = 1;
			}

			switch (Config::フォントID)
			{
			default:
				MFont::S = &MFont::SDot;
				MFont::M = &MFont::MDot;
				MFont::L = &MFont::LDot;
				break;
			case 1:
				MFont::S = &MFont::SAlias;
				MFont::M = &MFont::MAlias;
				MFont::L = &MFont::LAlias;
				break;
			}

			MFont::F[0] = MFont::S;
			MFont::F[1] = MFont::M;
			MFont::F[2] = MFont::L;

			if (Config::is超加速 == true)
			{
				Config::ゲーム速度変更倍率 = 4;
				Config::最大ゲーム倍速 = 64;
			} else {
				Config::ゲーム速度変更倍率 = 2;
				Config::最大ゲーム倍速 = 16;
			}
			
		}

	}
}