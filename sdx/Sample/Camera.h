//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//[未実装]
bool SampleCamera()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	Camera camera({320,240},1);

	Image image("data/pipo-enemy035.png");
	Font font(SystemFont::Mincho, 10);

	ImagePack frameImage("data/pipo-WindowBase001.png", 9, 3, 3);
	BmpFrame bmpFrame(&frameImage);

	while (System::Update())
	{
		Camera::Set(&camera);
	
		Drawing::Rect({ 10, 10, 100, 100 }, Color::White);
		Drawing::Circle({ 200, 200, 100 }, Color::Red, 20);
		Drawing::Line({ 0, 0 }, { 640, 480 }, Color::Lime);
		
		font.Draw({ 200, 10 }, Color::Blue, "Hello World!");

		image.Draw({ 300, 300 });
		
		Camera::Set();//カメラによる位置補正無効化

		bmpFrame.Draw({ 0, 0, 640, 40 });
		font.Draw({ 10, 10 }, Color::White, { "マウスカーソルでカメラ位置変更、ホイールで拡大縮小\n位置 =", Input::mouse.x, ",",Input::mouse.y," 拡大率 = ",camera.zoom });

		//マウスの位置が中心に来る
		camera.position = { Input::mouse.x, Input::mouse.y };

		//ホイールで拡大縮小
		if (Input::mouse.Whell > 0)
		{
			camera.zoom *= 0.9;
		}
		if (Input::mouse.Whell < 0)
		{
			camera.zoom *= 1.1;
		}

		if (Input::key.Return.on){ break; }//Enterで終了
	}

	System::End();
	return true;
}