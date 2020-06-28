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

void LoadAndInitData()
{
	TX::Load();

	auto time_t = time(nullptr);
	Rand::Reset((int)time_t);

	ConfigSaveAndLoad(FileMode::Read);

	Game::解像度W = Game::解像度設定 * 160;
	Game::解像度H = Game::解像度設定 * 90;

	Game::最大解像度W = GetSystemMetrics(SM_CXSCREEN);
	Game::最大解像度H = GetSystemMetrics(SM_CYSCREEN);

	Game::解像度W = std::min(Game::解像度W, Game::最大解像度W);
	Game::解像度H = std::min(Game::解像度H, Game::最大解像度H);

	System::Initialise( TX::タイトル.c_str() , Game::解像度W, Game::解像度H);//ライブラリの初期化

	Game::BGM音量 = double(Game::BGM設定 * Game::BGM設定) / 100;
	Game::SE音量 = double(Game::SE設定 * Game::SE設定) / 100;

	Music::SetMainVolume(Game::BGM音量);
	Sound::SetMainVolume(Game::SE音量);

	//各種リソース読み込み


	LoadMaterial();

	LoadPassiveSkill();
	LoadActiveSkill();
	LoadWarkerClass();
	LoadMonsterClass();
	LoadItem();

	SDL_StartTextInput();//デバッグ用、テキスト入力可能に
}

int main(int argc, char* argv[])
{

	//アンケートURL
	//HINSTANCE ret = ShellExecute(nullptr, L"open", L"http://www.gesource.jp/programming/bcb/", NULL, NULL, SW_SHOW);

	LoadAndInitData();

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
