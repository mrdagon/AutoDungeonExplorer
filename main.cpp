#include "stdafx.h"
//#include "struct/data.h"
//#include "scene/scene.h"
#include "system/system.h"

using namespace SDX;
int main(int argc, char* argv[])
{
	System::Initialise("sample", 640, 480);//ライブラリの初期化
	int x = 320;
	int y = 240;
	while (System::Update())
	{
		if (Input::pad.Down.hold) y += 5;
		if (Input::pad.Up.hold) y -= 5;
		if (Input::pad.Right.hold) x += 5;
		if (Input::pad.Left.hold) x -= 5;
		Drawing::Rect({ x - 10, y - 10, 20, 20 }, Color::White, true);
	}

	System::End();//ライブラリの終了処理
	return 0;
}