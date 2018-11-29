//Copyright © 2017 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>

namespace SDX_BSC
{
	using namespace SDX;

	/*画面ベースクラス*/
	class Scene
	{
	private:

	public:
		virtual bool Init() = 0;//初期化
		virtual bool Close() = 0;//終了処理
		virtual bool Run() = 0;//実行

		virtual bool Update() = 0;//更新
		virtual bool Draw() = 0;//描画
	};
}

#include "config.h"
#include "game_option.h"
#include "main_game.h"
#include "main_menu.h"
