//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#include "stdafx.h"

#include "system/_system.h"
#include "object/_object.h"
#include "window/_window.h"

#include "scene/_scene.h"
#include "save.h"

#include <windows.h>


using namespace SDX;
using namespace SDX_BSC;


void LoadAndInitData()
{
	TX::Load();

	auto time_t = time(nullptr);
	Rand::Reset((int)time_t);

	ConfigSaveAndLoad(FileMode::Read);

	Config::解像度W = Config::解像度設定 * 160;
	Config::解像度H = Config::解像度設定 * 90;

	Game::最大解像度W = GetSystemMetrics(SM_CXSCREEN);//Windows依存コード
	Game::最大解像度H = GetSystemMetrics(SM_CYSCREEN);

	Config::解像度W = std::min( Config::解像度W , Game::最大解像度W);
	Config::解像度H = std::min( Config::解像度H , Game::最大解像度H);

	System::Initialise( TX::タイトル.c_str() , Config::解像度W, Config::解像度H);//ライブラリの初期化

	Config::BGM音量 = double(Config::BGM設定 * Config::BGM設定) / 100;
	Config::SE音量 = double(Config::SE設定 * Config::SE設定) / 100;

	Music::SetMainVolume(Config::BGM音量);
	Sound::SetMainVolume(Config::SE音量);

	//各種リソース読み込み
	LoadAsset();

	LoadPassiveSkill();
	LoadActiveSkill();
	LoadItem();
	LoadMonsterClass();
	LoadHunterClass();
	LoadMaterialClass();

	SDL_StartTextInput();//デバッグ用、テキスト入力可能に
}

int main(int argc, char* argv[])
{
	CSVInit();
	LoadAndInitData();

	/*未返還テキスト位置*/
	/*
	SDL_Rect srcrect;
	srcrect.x = 0;
	srcrect.y = 0;
	srcrect.w = 300;
	srcrect.h = 300;
	SDL_SetTextInputRect(&srcrect);
	*/
	Camera camera({0,0},1);
	SDX::Camera::Set(&camera);

	MainGame game;

	game.Init();
	game.Main();

	ConfigSaveAndLoad(FileMode::Write);

	System::End();//ライブラリの終了処理
	return 0;
}
