//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/


//EnumArrayの使用例
bool SampleEnumArray()
{
	using namespace SDX;

	System::Initialise("sample", 640, 480);//ウィンドウタイトルを指定して、初期化する

	enum class ANIMAL
	{
		ねずみ,
		ひよこ,
		くま,
		にわとり,
		COUNT,
	};

	EnumArray<Image, ANIMAL> 画像;

	画像[ANIMAL::ねずみ].Load("data/pipo-enemy034.png");
	画像[ANIMAL::ひよこ].Load("data/pipo-enemy035.png");
	画像[ANIMAL::にわとり].Load("data/pipo-enemy036.png");
	画像[ANIMAL::くま].Load("data/pipo-enemy037.png");

	ANIMAL type = ANIMAL::ねずみ;

	while (System::Update())//ウィンドウの更新や、入力の更新等を行う
	{
		画像[type].Draw({ 300, 200 });

		if (Input::key._1.on) type = ANIMAL::ねずみ;
		if (Input::key._2.on) type = ANIMAL::ひよこ;
		if (Input::key._3.on) type = ANIMAL::にわとり;
		if (Input::key._4.on) type = ANIMAL::くま;

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();//ライブラリの終了処理を行う
	return true;
}