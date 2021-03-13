//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//図形を異なる色で描画
bool SampleColor()
{
	using namespace SDX;
	System::Initialise("Color", 640, 480);

	while (System::Update())
	{
		//赤い線を描画、普通に指定する
		Drawing::Line({ 10, 10 }, { 200, 10 }, Color(255, 0, 0), 3);

		//緑の四角を描画、省略してみる
		Drawing::Rect({ 10, 100, 200, 200 }, { 0, 255, 0 }, true);

		//半透明の青い●を描画、塗りつぶし有り
		Drawing::Circle({ 110, 300, 50 }, {0,0,255,128});

		if (Input::key.Return.on){ break;}//Enterで終了
	}
	System::End();
	return true;
}