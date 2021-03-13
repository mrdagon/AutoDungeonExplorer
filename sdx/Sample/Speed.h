//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//速度オブジェクトを使う
#include <SDXFramework.h>

bool SampleSpeed()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	//位置と形を持った型
	std::vector<std::shared_ptr<IShape>> shapes;
	shapes.emplace_back(new Circle(0, 50, 10));
	shapes.emplace_back(new Rect(0, 150, 20, 20));
	shapes.emplace_back(new Line(0, 250, PAI / 2, 20, 5));

	//変化する数値を表す型
	std::vector<std::shared_ptr<SPEED::ISpeed>> speeds;
	speeds.emplace_back(new SPEED::Liner(1));//等速
	speeds.emplace_back(new SPEED::Accel(0, 0.01));//加速する
	speeds.emplace_back(new SPEED::Wave(2, 0.1, 0));//平均√2で進む

	while (System::Update())
	{
		for (int a = 0; a < 3; ++a)
		{
			//速度を更新する
			speeds[a]->Update();

			//図形を移動させる
			shapes[a]->MoveA(speeds[a]->Get(), 0);

			//描画する
			shapes[a]->Draw(Color::White);
		}

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}