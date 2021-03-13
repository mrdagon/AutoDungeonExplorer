//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//メインウィンドウとサブウィンドウを作成
//メインウィンドウを閉じると終了
#include <SDXFramework.h>

bool SampleWindow()
{
	using namespace SDX;

	System::Initialise("MainWindow", 320, 240);
	SubWindow sub("SubWindow",200,200);

	//SetLogicalSizeしておくと、ウィンドウの解像度を上げても描画される解像度はそのままになる
	//Windowサイズを変えた後に呼び出しても良い
	Window::SetLogicalSize(320, 240);

	while (System::Update())
	{
		Window::SetIcon("data/icon000.png");
		sub.SetIcon("data/icon009.png");

		Drawing::String({ 10, 100 }, Color::White, { "Windowクラスのテスト:Enterで終了" ,Input::mouse.x," ",Input::mouse.y});
		Screen::SetRenderer(sub.GetRenderer());
		Drawing::String({ 10, 100 }, Color::White, { "SubWindowクラスのテスト:Enterで終了", Input::mouse.x," ", Input::mouse.y });

		if (Input::key._1.on){ Window::SetTitle("Mainタイトルを変えたよ！"); }//ウィンドウタイトルを変更
		if (Input::key._2.on){Window::SetSize(640, 480);}//ウィンドウの大きさを変更
		if (Input::key._3.on) { Window::SetFullscreen(true); }
		if (Input::key._4.on) { Window::SetFullscreen(false); }
		if (Input::key._5.on) { Window::SetIcon("icon.png"); }

		if (Input::key._6.on){ sub.SetTitle("Subタイトルを変えたよ！"); }//ウィンドウタイトルを変更
		if (Input::key._7.on) { sub.SetSize(400, 400); }//ウィンドウの大きさを変更
		if (Input::key._8.on) { sub.SetFullscreen(true); }
		if (Input::key._9.on) { sub.SetFullscreen(false); }
		if (Input::key._0.on) { sub.SetIcon("icon.png"); }

		if (Input::key.Return.on){ break; }//Enterで終了

		Screen::SetRenderer();
		sub.Update();
	}

	System::End();
	return true;
}