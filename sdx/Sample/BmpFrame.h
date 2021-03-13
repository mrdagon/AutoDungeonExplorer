//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//初期化を行い何かキーを押すと終了する
bool SampleBmpFrame()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);
	Screen::SetBackColor(Color::White);

	//BmpFrame用の画像を読み込む
	ImagePack frameImageA("data/pipo-WindowBase001.png", 9, 3, 3);
	ImagePack frameImageB("data/pipo-WindowBase004.png", 9, 3, 3);

	//BmpFrameを作成
	BmpFrame bmpFrameA(&frameImageA);
	BmpFrame bmpFrameB(&frameImageB);

	Rect 四角(220,140,200,200);
	double 大きさ = 1.0;

	while (System::Update())
	{
		bmpFrameA.Draw({ 0, 0, Input::mouse.x, Input::mouse.y });

		bmpFrameB.Draw(四角);

		if (Input::key.Up.hold){ 四角.Move(0, -5); }
		if (Input::key.Down.hold){ 四角.Move(0, 5); }
		if (Input::key.Left.hold){ 四角.Move(-5, 0); }
		if (Input::key.Right.hold){ 四角.Move(5, 0); }

		if (Input::key.Return.on){ break; }//Enterで終了
	}

	System::End();
	return true;
}