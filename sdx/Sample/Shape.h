//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//図形の当たり判定をする
#include <SDXFramework.h>

bool SampleShape()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	//図形を宣言する
	Circle circle(10, 10, 100);
	Rect rect(60, 60, 100, 100);
	Line line(200, 100, PAI / 4, 600, 5);

	//共通のインターフェースを持っている
	IShape* shapes[3];
	shapes[0] = &circle;
	shapes[1] = &rect;
	shapes[2] = &line;

	while (System::Update())
	{
		circle.SetPos(Input::mouse.x, Input::mouse.y);

		//Lineは回転可能
		line.Rotate(0.01);

		//ダブルディスパッチによる当たり判定
		for (int a = 0; a < 3; ++a)
		{
			int hit = 0;

			for (int b = 0; b < 3; ++b)
			{
				if (a == b){ continue; }
					
				hit += shapes[a]->Hit(shapes[b]);
			}

			if ( hit == 0)
			{
				shapes[a]->Draw(Color::White);
			}
			else if (hit == 1)
			{
				shapes[a]->Draw(Color::Red);
			}
			else
			{
				shapes[a]->Draw(Color::Blue);
			}
		}

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}