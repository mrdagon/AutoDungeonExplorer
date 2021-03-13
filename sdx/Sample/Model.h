//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//初期化を行い何かキーを押すと終了する
bool SampleModel()
{
	using namespace SDX;
	System::Initialise("sample", 640, 480);
	
	Image くま("data/pipo-enemy037.png");
	Font フォント(SystemFont::Gothic, 10);
	Film がいこつ("data/hone.png", 12, 3, 4,12);
	ImagePack 枠画像("data/pipo-WindowBase001.png",9,3,3);
	BmpFrame 枠(&枠画像);

	がいこつ.SetType(FilmType::Reverse);

	//各種スプライトと組み合わせたモデル
	Model<Point, SpImage> modelA({ 100, 400 }, &くま);
	Model<Circle, SpAnime> modelB({ 200, 300 ,20}, &がいこつ);
	Model<Rect, SpFont> modelC({ 320, 240 , 100, 10}, { &フォント ,"Hello World"});
	Model<Rect, SpFrame> modelD({ 400, 100, 100, 100 }, &枠);

	//各種モーション
	MOTION::Bound<SPEED::Liner> motionA( 5 , { 0, 0, 640, 480 } , PAI/4);
	MOTION::Bound<SPEED::Liner> motionB( 10 , { 0, 0, 640, 480 }, PAI/3);
	MOTION::Orbit<SPEED::Liner> motionC(0.05, 200, 100, PAI / 4);
	MOTION::ToPoint<SPEED::Liner> motionD(5, { 320, 240 });

	IModel *modelS[4] = {&modelA,&modelB,&modelC,&modelD};
	MOTION::IMotion *motionS[4] = { &motionA, &motionB, &motionC, &motionD};

	while (System::Update())
	{
		for (int a = 0; a < 4; ++a)
		{
			modelS[a]->GetSprite().Update();//SpAnimeは更新が必要
			motionS[a]->Update( modelS[a] );//modelを移動
			modelS[a]->Draw();//modelを描画

			//衝突中のモデルを回転させる
			for (int b = a+1 ; b < 4; ++b)
			{
				if (modelS[a]->Hit(modelS[b]))
				{
					modelS[a]->Rotate(0.1);
					modelS[b]->Rotate(0.1);
					break;
				}
			}
		}

		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	
	return true;
}