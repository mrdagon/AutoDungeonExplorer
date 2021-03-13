//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//リソースを非同期で読み込む
bool SampleLoading()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);

	//他ImagePackとFilmクラスも有効
	Image imageS[100];
	Sound soundS[100];
	Music musicS[100];
	Font  fontS[100];

	//Loadingが完了していない時に新しい文字を出すとエラーがたまに発生するため
	//事前に使いそうな文字を生成しておく
	Drawing::GetFont().GetDrawStringWidth("読み込み完了数/0123456789");

	Loading::Start();//非同期読み込み開始

	//それぞれ100回読み込み
	for (int a = 0; a < 100;++a)
	{
		imageS[a].Load("data/icon000.png");
	}
	for (int a = 0; a < 100; ++a)
	{
		soundS[a].Load("se_maoudamashii_onepoint14.wav");
	}
	for (int a = 0; a < 100; ++a)
	{
		musicS[a].Load("data/bgm_maoudamashii_piano14.ogg");
	}
	for (int a = 0; a < 100; ++a)
	{
		fontS[a].Load(SystemFont::Gothic,10);
	}

	Loading::End();//非同期読み込み終了
	
	while (System::Update())
	{
		//読み込み中のリソースの数を表示
		Drawing::String({ 10, 10 }, Color::White, { "読み込み完了数", Loading::GetSuccesCount() ,"/",Loading::GetLoadingCount()});
		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}