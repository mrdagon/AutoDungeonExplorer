//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#include "stdafx.h"
#include "system/_system.h"
#include "object/_object.h"
#include "window/_window.h"
#include "scene/_scene.h"

#include "system/save_and_load.h"

using namespace SDX;
using namespace SDX_BSC;

int main(int argc, char* argv[])
{
	System::Initialise("ギルドマスターマインド(仮) ver.demo", 16*100, 9*100);//ライブラリの初期化
	
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

	System::End();//ライブラリの終了処理
	return 0;
}