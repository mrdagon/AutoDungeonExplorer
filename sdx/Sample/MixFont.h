//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
bool SampleMixFont()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	MixFont fontA(SystemFont::Gothic, 20, 10,FontRender::Solid);
	MixFont fontB(SystemFont::Mincho, 20, 10,FontRender::Solid);

	double angle = 0;

	while (System::Update())
	{
		angle += 0.02;

		fontA.Draw({ 10 * angle, 10 }, Color::White, "Hello!\nこんにちは\n今日は");
		fontB.Draw({ 10 * angle, 200 }, Color::Blue, "Hello!\nこんにちは\n今日は");

		fontA.DrawRotate({ 300, 200 }, 1, angle, Color::White, false, "文字の回転\nてすとしますよ~~~");
		fontB.DrawRotate({ 300, 200 }, 1, angle / 2, Color::White, false, "文字の回転\nてすとしますよ~~~");

		if (Input::key.Return.on){ break; }//Enterで終了
	}

	System::End();
	return true;
}