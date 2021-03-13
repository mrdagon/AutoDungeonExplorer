//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//乱数で取得して表示する
#include <SDXFramework.h>

bool SampleRand()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	while (System::Update())
	{
		//乱数を初期化する
		Rand::Reset(0);
		int a = Rand::Get(100);
		double b = Rand::Get(100.0);

		//現在時間で初期化して取得
		Rand::Reset(int(Time::GetNowCount() / 1000));
		int c = Rand::Get(100);
		double d = Rand::Get(100.0);

		//a,bは初期化子が同じなので常に同じ、cdは一秒毎に変化
		Drawing::String({ 10, 10 }, Color::White, { "a:", a });
		Drawing::String({ 10, 50 }, Color::White, { "b:", b });
		Drawing::String({ 10, 90 }, Color::White, { "c:", c });
		Drawing::String({ 10, 130 }, Color::White, { "d:", d });

		if (Input::key.Return.on){ break; }//Enterで終了
	}

	System::End();
	return true;
}