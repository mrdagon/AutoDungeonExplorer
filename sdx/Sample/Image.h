//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//画像を描画する
bool SampleImage()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Image ねずみ("data/pipo-enemy034.png");
	Image ひよこ("data/pipo-enemy035.png");
	Image にわとり("data/pipo-enemy036.png");
	Image くま("data/pipo-enemy037.png");

	にわとり.SetColor(Color::Red);//赤くする
	くま.SetColor({255,255,255,128});//半透明にする

	double angle = 0;

	while (System::Update())
	{
		angle += 0.1;

		ねずみ.Draw({ 100, 100 }, true);//反転して描画

		ひよこ.DrawExtend({ 200, 100 , 200, 100 });//指定矩形に描画

		にわとり.DrawRotate({ 100, 200 }, 0.5, angle);//角度と拡大率を指定して描画

		くま.DrawPart({ 200, 200 }, {0,0,90,90});//一部分を描画

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}
