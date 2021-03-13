//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
#include <SDXFramework.h>

bool SampleSprite()
{
	using namespace SDX;

	System::Initialise("sample", 640, 480);//ウィンドウタイトルを指定して、初期化する

	while (System::Update())//ウィンドウの更新や、入力の更新等を行う
	{
		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();//ライブラリの終了処理を行う
	return true;
}