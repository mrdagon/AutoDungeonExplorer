//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ビットマップフォントを使った描画を行う
bool SampleBmpFont()
{
	using namespace SDX;
	System::Initialise("sample", 600, 400);

	//BmpFont用の画像を読み込む
	ImagePack no("image.bmp", 10, 10, 1);
	ImagePack engBic("image.bmp", 26, 26, 1);
	ImagePack engSmall("image.bmp", 26, 26, 1);

	//BmpFontを設定する
	BmpFont bmpFont;
	bmpFont.SetNumber(&no);
	bmpFont.SetAlphabetCapital(&engBic);
	bmpFont.SetAlphabetLow(&engSmall);

	//インターフェースはFontと共通
	Font font("明朝", 10, 10);

	IFont* ifont[2];
	ifont[0] = &font;
	ifont[1] = &bmpFont;

	while (System::Update())
	{
		ifont[0]->Draw({ 10, 10 }, Color::White, { "Hello World!\n", 1928374650 });
		ifont[1]->Draw({ 10, 100 }, Color::White, { "Hello World!\n", 1928374650 });
		if (Input::key.Return.on){ break; }//Enterで終了
	}

	System::End();
	return true;
}