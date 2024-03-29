﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#include "stdafx.h"

#include "system/_system.h"
#include "object/_object.h"
#include "window/_window.h"

#include "scene/_scene.h"

using namespace SDX;
using namespace SDX_ADE;


void LoadAndInitData()
{
	TX::Load();
	TH::Load();

	auto time_t = time(nullptr);
	Rand::Reset((int)time_t);
	Game::最大解像度W = GetSystemMetrics(SM_CXSCREEN);//Windows依存コード
	Game::最大解像度H = GetSystemMetrics(SM_CYSCREEN);

	Config::SaveLoad(FileMode::Read);
	System::Initialise( TX::タイトル.c_str() , Config::解像度W, Config::解像度H);//ライブラリの初期化
	static Camera camera({ 0,0 }, 1);
	SDX::Camera::Set(&camera);

	//各種リソース読み込み
	LoadAsset();
	Design::Load();
	Config::Update();

	//外部データ読込
	PassiveSkill::LoadData();
	ActiveSkill::LoadData();
	Material::LoadData();
	Item::LoadData();
	MonsterClass::LoadData();
	ExplorerClass::LoadData();
	Management::LoadData();

	Quest::LoadData();
	Dungeon::LoadData();
	Layout::LoadData();

	Recipe::LoadRecipeData();


	SDL_StartTextInput();//デバッグ用、テキスト入力可能に
}

int main(int argc, char* argv[])
{
	CSVInit();
	LoadAndInitData();



	static MainGame game;//読み込み終わってからコンストラクタ呼ぶ
	static MainMenu menu;

	int text_x = 100;

	Layout::Data(LTitle::題字);

	while (System::ProcessMessage())
	{
		if (Game::isゲーム終了) { break; }

		if (menu.セーブ == nullptr)
		{
			game.Init(menu.難易度);
		} else {
			game.Init(menu.セーブ);
		}

		menu.Init();//とりあえずタイトルスキップ
		menu.Main();

		if (Game::isゲーム終了) { break; }

		game.Init();
		game.Main();

	}

	if (CV::isデバッグ)
	{
		CSVEnd("file/layout/layout_data.txt");
		CSVEnd("file/layout/backup.txt");
	}

	Config::SaveLoad(FileMode::Write);

	Layout::SaveData();

	System::End();//ライブラリの終了処理
	return 0;
}
