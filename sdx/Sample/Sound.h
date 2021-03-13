//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ライブラリの初期化等を行う
#include <SDXFramework.h>

bool SampleSound()
{
	using namespace SDX;

	System::Initialise("sample", 640, 480);//ウィンドウタイトルを指定して、初期化する

	Sound seA("data/se_maoudamashii_onepoint14.wav");
	Sound seB("data/se_maoudamashii_onepoint15.wav");

	Sound *nowSE = &seA;
	double distance = 0.0;
	double angle = 0.0;

	while (System::Update())//ウィンドウの更新や、入力の更新等を行う
	{
		Drawing::String({ 10, 10 }, Color::White, "AとBでSEの種類変更\nZXで音量変更、RLでパン設定、カーソルキーで3D効果");
		Drawing::String({ 10, 50 }, Color::White, { "音量 = ", nowSE->GetVolume(),"\n角度 = ",angle,"\n距離 = " , distance });

		//AとBで再生対象変更
		if (Input::key.A.on)
		{
			nowSE = &seA;
			nowSE->Play();
		}
		if (Input::key.B.on)
		{
			nowSE = &seB;
			nowSE->Play();
		}

		//ZとXで音量変更
		if (Input::key.Z.on)
		{
			nowSE->SetVolume(nowSE->GetVolume() - 0.1);
			nowSE->Play();
		}
		if (Input::key.X.on)
		{
			nowSE->Set3DEffect();
			nowSE->SetVolume(nowSE->GetVolume() + 0.1);
			nowSE->Play();
		}

		//RとLでパニング
		if (Input::key.R.on)
		{
			nowSE->Set3DEffect();
			nowSE->SetPanning(0.5, 1.0);
			nowSE->Play();
			nowSE->SetPanning();
		}
		if (Input::key.L.on)
		{
			nowSE->Set3DEffect();
			nowSE->SetPanning(1.0, 0.5);
			nowSE->Play();
			nowSE->SetPanning();
		}

		//上下左右カーソルで3D効果
		if (Input::key.Left.on)
		{
			angle -= 0.1;
			nowSE->Set3DEffect(distance, angle);
			nowSE->Play();
		}
		if (Input::key.Right.on)
		{
			angle += 0.1;
			nowSE->Set3DEffect(distance, angle);
			nowSE->Play();
		}
		if (Input::key.Up.on)
		{
			distance += 0.1;
			if (distance >= 1){ distance = 1; }
			nowSE->Set3DEffect(distance,angle);
			nowSE->Play();
		}
		if (Input::key.Down.on)
		{
			distance -= 0.1;
			if (distance <= 0){ distance = 0; }
			nowSE->Set3DEffect(distance, angle);
			nowSE->Play();
		}


		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();//ライブラリの終了処理を行う
	return true;
}