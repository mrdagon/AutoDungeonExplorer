//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//フォントを作成して文字列を描画する
bool SampleFont()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	//フォントの初期化
	Font fontA(SystemFont::Gothic, 9, 4,false);
	Font fontB(SystemFont::Mincho, 20, 4, true);

	//BMPフォントを生成したり読み込む
	//事前にBMPフォントを作っておくと、Android等で読み込みが早い
	fontA.MakeBMPFont("data/jyouyoukannji.txt");
	Image bmpFont("data/bmpfont.png");
	fontA.LoadBMPFont(bmpFont, "data/jyouyoukannji.txt");

	//追加BMPフォントの登録
	ImagePack bmpNumber("data/number.png",10,10,1);
	ImagePack bmpFont2("data/font.png", 30, 10, 3);

	fontA.SetImageS("0", &bmpNumber,10);
	fontA.SetImageS("a", &bmpFont2, 26);
	fontA.SetImageS("A", &bmpFont2, 26);
	fontA.SetImage("×", bmpFont2[26]);
	fontA.SetImage("□", bmpFont2[27]);
	fontA.SetImage("○", bmpFont2[28]);
	fontA.SetImage("☆", bmpFont2[29]);

	double angle = 0;

	Screen::SetBackColor(Color::Silver);

	while (System::Update())
	{
		angle += 0.02;

		fontA.Draw({ 10 , 10 }, Color::White, "Hello○\nこん☆にちは\n今日は1234");
		fontB.Draw({ 10 , 200 }, Color::Blue, "Hello○\nこん☆にちは\n今日は1234");

		fontA.DrawRotate({ 300, 100 }, 1, angle, Color::White, false, "文字の回転□\nてすと1234×");
		fontB.DrawRotate({ 300, 200 }, 1, angle, Color::White, false, "文字の回転□\nてすと1234×");

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}