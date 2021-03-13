//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
bool SampleImagePack()
{
	using namespace SDX;

	System::Initialise("sample", 640, 480);//ウィンドウタイトルを指定して、初期化する

	ImagePack imageA("data/number.png", 10, 10, 1);//分割読み込み
	ImagePack imageB("data/icon", "png", 10);//連番ファイル読み込み
	ImagePack imageC("data/dekakabocha.png", 12, 3, 4);//分割読み込み

	Point pos(300,240);	
	int count = 0;
	int direct = 0;

	while (System::Update())
	{
		++count;

		imageA[count / 60 % 10]->DrawExtend({ 200, 240, 30, 40 });
		imageB[count / 5  % 10]->Draw({ 400, 240 });

		int no = direct * 3 + (count / 12) % 2;
		imageC[no]->Draw( pos );

		//キーで移動
		if (Input::key.Up.hold)
		{ 
			pos.Move(0, -5); 
			direct = 3;
		}
		if (Input::key.Down.hold)
		{
			pos.Move(0, 5);
			direct = 0;
		}
		if (Input::key.Left.hold)
		{
			pos.Move(-5, 0);
			direct = 1;
		}
		if (Input::key.Right.hold)
		{
			pos.Move(5, 0);
			direct = 2;
		}

		if (Input::key.Return.on){ break; }//Enterで終了
	}

	System::End();//ライブラリの終了処理を行う
	return true;
}