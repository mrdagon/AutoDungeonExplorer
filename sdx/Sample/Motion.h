//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
#include <SDXFramework.h>

bool SampleMotion()
{
	using namespace SDX;

	System::Initialise("sample", 640, 480);//ウィンドウタイトルを指定して、初期化する

	Line line(100, 50, 0.1, 20, 5);
	Rect rect(100, 100, 10, 10 , 10 , 10);
	Circle circleA(200, 150, 10);
	Circle circleB(400, 400-30, 10);
	Circle circleC(400, 400, 10);

	MOTION::ToFront<SPEED::Wave> toFront({ 5, 0.1, 0 });
	MOTION::Bound<SPEED::Liner> bound({ 5 }, {0,0,640,480},PAI/6);
	MOTION::ToPoint<SPEED::Accel> toPoint({ -1.0, 0.01 }, {400,400});
	MOTION::Orbit<SPEED::AccelLimit> orbit({ 0 , 0.001, 0.2 },50,30);
	MOTION::Vibrate vibrate( 5 );

	IShape* shapeS[5] = {&line,&rect,&circleA,&circleB,&circleC};
	MOTION::IMotion *motionS[5] = {&toFront,&bound,&toPoint,&orbit,&vibrate};

	while (System::Update())//ウィンドウの更新や、入力の更新等を行う
	{
		for (int a = 0; a < 5; ++a)
		{
			motionS[a]->Update(shapeS[a]);
			shapeS[a]->Draw(Color::White);
		}

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();//ライブラリの終了処理を行う
	return true;
}