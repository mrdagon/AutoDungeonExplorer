//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
#include <SDXFramework.h>

bool SampleSystem()
{
	using namespace SDX;

	System::Initialise("sample", 640, 480);//ウィンドウタイトルを指定して、初期化する

	Drawing::String({ 10, 10 }, Color::White, "３秒待ちます");
	Screen::Flip();
	System::Wait(3000);

	Drawing::String({ 10, 50 }, Color::White, "何かキーを押したら終了します");
	Screen::Flip();
	System::WaitKey();

	System::End();//ライブラリの終了処理を行う
	return true;
}