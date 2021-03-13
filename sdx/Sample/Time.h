//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//時間を取得したり計測する
#include <SDXFramework.h>
//#include <Sample/TimeTest.h>//MSVC 2013以前非対応
#include <Utility/Any.h>
#include <Utility/Pool.h>
#include <array>

class ITest
{
public:
	int num;
	virtual ~ITest() {}
};

class Test: public ITest
{
public:
	Test& operator=(int value)
	{
		num = value;
		return *this;
	}
};

std::vector<int> a;
std::vector<int> b;
std::vector<int> c;

std::array<std::vector<int>*, 3> vecS = { &a,&b,&c };

bool SampleTime()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Time::ResetFPS();
	Time::ResetCount();

	int count = 0;

	const int n1 = (int)std::ceil(std::log2(8));
	const int n2 = (int)std::ceil(std::log2(9));
	const int n3 = (int)std::ceil(std::log2(17));

	Pool pool;
	std::vector<Test> vecA(1000);
	std::vector<Any<ITest,sizeof(Test)+4>> vecB;
	std::vector<std::shared_ptr<Test> > vecC;
	std::vector<ITest*> vecD;

	vecA.reserve(1000000);
	vecB.reserve(1000000);
	vecC.reserve(1000000);
	vecD.reserve(1000000);

	while (System::Update())
	{
		if (Input::key.Return.on){ break;}//Enterで終了
		count++;
		Time::CheckFPS();//FramePerSecondを更新
		Drawing::String({ 10, 10 }, Color::White, { "FPS:", Time::GetFPS(), "\nNow:", Time::GetNowCount() });

		tm date;
		Time::GetDate(&date);
		Drawing::String({ 10, 100 }, Color::White, { date.tm_year + 1900, "年 ", date.tm_mon + 1, "月 ", date.tm_mday, "日" });

		Time::StartWatch();//処理時間の計測開始

		for (int a = 0; a < 100; ++a)
		{
			Drawing::Circle({ 200, 100, 20 }, Color::White , 5);
		}

		Time::DrawWatch({ 10, 220 }, "○描画100回の処理時間:");

		for (int a = 0; a < 100; ++a)
		{
			Drawing::Rect({ 210, 110, 40 ,40}, Color::White,true);
		}

		Time::DrawWatch({ 10, 240 }, "□描画100回の処理時間:");

		for (int a = 0; a < 100000; ++a)
		{
			auto b = new Test();
			delete b;
		}

		Time::DrawWatch({ 10, 260 }, "new delete 十万回の処理時間:");

		char c[1000000];//大きすぎるとエラーになるので注意
		for (int a = 0; a < 1000000; ++a)
		{
			vecD.push_back(new(c + a / 100 * sizeof(Test)) Test());
		}
		vecD.clear();

		Time::DrawWatch({ 10, 280 }, "placement new 100万回の処理時間:");

		Time::StartWatch();
		for (int a = 0; a < 1000000; ++a)
		{
			vecD.push_back(pool.Get<Test>());
		}
		//shared_ptrと組み合わせるとさらに遅いので自力でDestroy
		for (int a = 0; a < 1000000; ++a)
		{
			pool.Destroy( vecD[a] );
		}

		vecD.clear();

		Time::DrawWatch({ 10, 300 }, "Pool 100万回の処理時間:");
		
		for (int a = 0; a < 1000000; ++a)
		{
			vecA.emplace_back();
		}
		vecA.clear();

		Time::DrawWatch({ 10, 320 }, "vector<Test> 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			vecC.push_back( std::make_shared<Test>() );
		}
		vecC.clear();
		Time::DrawWatch({ 10, 340 }, "shared_ptr 100万回の処理時間:");

		for (int a = 0; a < 1000000; ++a)
		{
			vecB.emplace_back( Test());
		}
		vecB.clear();
		Time::DrawWatch({ 10, 360 }, "Any 100万回の処理時間:");




	}

	System::End();
	return true;
}