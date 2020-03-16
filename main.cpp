//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#include "stdafx.h"

#include "system/_system.h"
#include "object/_object.h"
#include "window/_window.h"
#include "scene/_scene.h"

#include <windows.h>

using namespace SDX;
using namespace SDX_BSC;

int main(int argc, char* argv[])
{

	//アンケートURL
	//HINSTANCE ret = ShellExecute(nullptr, L"open", L"http://www.gesource.jp/programming/bcb/", NULL, NULL, SW_SHOW);

	ConfigSaveAndLoad(FileMode::Read);

	Game::解像度W = Game::解像度設定 * 160;
	Game::解像度H = Game::解像度設定 * 90;

	Game::最大解像度W = GetSystemMetrics(SM_CXSCREEN);
	Game::最大解像度H = GetSystemMetrics(SM_CYSCREEN);

	Game::解像度W = min(Game::解像度W, Game::最大解像度W);
	Game::解像度H = min(Game::解像度H, Game::最大解像度H);

	System::Initialise("ギルドマスターマインド(仮) デモ0.2a", Game::解像度W, Game::解像度H);//ライブラリの初期化
	
	Game::BGM音量 = double(Game::BGM設定 * Game::BGM設定) / 100;
	Game::SE音量 = double(Game::SE設定 * Game::SE設定) / 100;

	Music::SetMainVolume(Game::BGM音量);
	Sound::SetMainVolume(Game::SE音量);

	Game::ローマ数字.resize(100);

	Game::ローマ数字[0] = "N";
	Game::ローマ数字[1] = "I";
	Game::ローマ数字[2] = "II";
	Game::ローマ数字[3] = "III";
	Game::ローマ数字[4] = "IV";
	Game::ローマ数字[5] = "V";
	Game::ローマ数字[6] = "VI";
	Game::ローマ数字[7] = "VII";
	Game::ローマ数字[8] = "VIII";
	Game::ローマ数字[9] = "IXI";
	Game::ローマ数字[10] = "X";


	//各種リソース読み込み
	LoadMaterial();

	LoadWarkerClass();
	LoadPassiveSkill();
	LoadActiveSkill();
	LoadMonsterClass();
	LoadItem();

	SDL_StartTextInput();//デバッグ用、テキスト入力可能に

	/*未返還テキスト位置*/
	SDL_Rect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 300;
	srcrect.h = 300;
	SDL_SetTextInputRect(&srcrect);

	DebugInit();
	
	Camera camera({0,0},1);
	SDX::Camera::Set(&camera);

	MainGame game;

	game.Init();
	game.Main();

	ConfigSaveAndLoad(FileMode::Write);

	System::End();//ライブラリの終了処理
	return 0;
}