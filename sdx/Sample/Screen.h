//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//初期化を行い何かキーを押すと終了する
#include <SDXFramework.h>

bool SampleScreen()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);
	
	Image image("data/pipo-enemy035.png");
	Image back;
	back.Make(640, 480);

	while (System::Update())
	{
		//背景描画
		back.Draw({ 0, 0 });

		//輝度を変更して描画
		Screen::SetBright(Color::Red);
		image.Draw({ 0, 0 });
		Screen::SetBright(Color::Green);
		image.Draw({ 100, 0 });
		Screen::SetBright(Color::Blue);
		image.Draw({ 200, 0 });

		//描画モード変更
		Screen::SetDrawMode({ 255, 255, 255, 128 }, BlendMode::Alpha);
		image.Draw({ 300, 0 });
		Screen::SetDrawMode({ 255, 255, 255, 128 }, BlendMode::Add);
		image.Draw({ 400, 0 });
		Screen::SetDrawMode({ 255, 255, 255, 128 }, BlendMode::Mula);
		image.Draw({ 500, 0 });
		Screen::SetDrawMode();//引数無しで解除

		//描画範囲制御
		Screen::SetClip({ 0, 100 , 60, 120 });
		image.Draw({ 0, 100 });
		Screen::SetClip();//引数無しで解除

		//描画先変更
		Screen::SetTarget(&back);
		Drawing::Rect({ Rand::Get(590), Rand::Get(430), 50, 50 },Color::Gray);
		Screen::SetTarget();

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}