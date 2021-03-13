//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//色々描画してみる
bool SampleDrawing()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	double angle = 0;
	
	while (System::Update())
	{
		Drawing::String({ 10, 10 }, Color::White, "こんにちは");

		Drawing::Line({ 10, 100 }, { 100, 150 }, Color::Blue, 3);
		Drawing::Line({ 210, 100 }, { 100, 150 }, Color::Blue);

		Drawing::Rect({ 50, 200, 50, 50 }, Color::Green,false);
		Drawing::Rect({ 75, 225, 50, 50 }, Color::Green, true);

		Screen::SetDrawMode({ 255, 255, 255, 128 } , BlendMode::Alpha);

		Drawing::Circle({ 150, 200, 50 }, Color::Red );
		Drawing::Circle({ 100, 200, 50 }, Color::Blue, 5);
		Drawing::Triangle({ 200, 200 }, 50, angle, Color::White);
		Drawing::Triangle({ 150, 200 }, 100, angle, Color::Green, 5);
		
		Screen::SetDrawMode();

		angle += 0.1;
		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}