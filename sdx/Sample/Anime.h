//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//画像をアニメーションさせる
bool SampleAnime()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	//画像を分割して読み込む
	Film filmA("data/number.png", 10, 10, 1,60 );
	Film filmB("data/hone.png", 12, 3, 4, 10);
	Film filmC("data/icon","png",10,12);

	//アニメーション
	Anime animeA(&filmA);
	Anime animeB(&filmB);
	Anime animeC(&filmC);

	//カウントアップ後カウントダウン
	filmA.SetType(FilmType::Reverse);
	//最後のコマで停止する
	filmB.SetType(FilmType::End);
	//各コマの再生時間を設定する
	filmC.SetFrameTime({1,2,3,4,5,6,7,8,9,10});	

	while (System::Update())
	{
		animeA.Update();
		animeB.Update();
		animeC.Update();

		animeA.DrawExtend({ 200, 240 ,30,40});

		animeB.Draw({ 300, 240 });

		animeC.Draw({ 400, 240 });

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}