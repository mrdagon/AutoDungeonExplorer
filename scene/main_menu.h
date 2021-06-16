//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*メインメニュー＆タイトル画面*/
	class MainMenu
	{
	private:
		//サブ呼び出しするウィンドウ
		W_Continue Win_Conitnue;
		W_Newgame Win_NewGame;
		W_Credit Win_Credit;
		W_Config Win_Config;

		std::array<UIButton, 6> ボタン;
	public:
		bool isゲーム開始;

		GameType 難易度;
		SaveData* セーブ;

		//初期化処理
		void Init()
		{
			isゲーム開始 = false;

			ボタン[0].SetUI(LTitle::ボタン, "始めから",  0);
			ボタン[1].SetUI(LTitle::ボタン, "続きから",  1);
			ボタン[2].SetUI(LTitle::ボタン, "設定",  2);
			ボタン[3].SetUI(LTitle::ボタン, "クレジット",  3);
			ボタン[4].SetUI(LTitle::ボタン, "アンケート",  4);
			ボタン[5].SetUI(LTitle::ボタン,"終了", 5);

			ボタン[0].is縁描画 = false;
			ボタン[1].is縁描画 = false;
			ボタン[2].is縁描画 = false;
			ボタン[3].is縁描画 = false;
			ボタン[4].is縁描画 = false;
			ボタン[5].is縁描画 = false;

			ボタン[0].clickEvent = [&]()
			{
				Input::mouse.Left.on = false;
				Win_NewGame.Init();

				if (Win_NewGame.OpenPopup() >= 1)
				{
					セーブ = nullptr;
					難易度 = Win_NewGame.選択中難易度;
					isゲーム開始 = true;
				}
			};

			ボタン[1].clickEvent = [&]()
			{
				Input::mouse.Left.on = false;
				Win_Conitnue.Init();

				if ( Win_Conitnue.OpenPopup() == 1)
				{
					セーブ = Win_Conitnue.GetSave();
					難易度 = GameType::COUNT;
					isゲーム開始 = true;
				}
			};

			ボタン[2].clickEvent = [&]()
			{
				Input::mouse.Left.on = false;
				Win_Config.Init();
				Win_Config.OpenPopup();
			};

			ボタン[3].clickEvent = [&]()
			{
				Input::mouse.Left.on = false;
				Win_Credit.Init();
				Win_Credit.OpenPopup();
			};

			ボタン[4].clickEvent = [&]()
			{
				Input::mouse.Left.on = false;
				ShellExecute(NULL, L"open", TX::アンケURL, NULL, L"", SW_SHOW);
			};

			ボタン[5].clickEvent = [&]()
			{
				Game::isゲーム終了 = true;
			};
		}

		//メインループ処理
		void Main()
		{
			MMusic::BGM[BGMType::タイトル].Play();

			double frame = 0;
			double time = Time::GetNowCount();

			while (System::Update(true, false))
			{
				frame++;

				//座標初期化
				Input();
				if (isゲーム開始 || Game::isゲーム終了)
				{
					break;
				}
				Draw();

				//60fpsの調整
				while (1)
				{
					if (Time::GetNowCount() - time > frame * 50 / 3.0) { break; }
				}

			}
		}

		void Input()
		{
			//ボタンクリックとマウスオーバー判定
			for (auto& it : ボタン)
			{
				it.CheckInput( 0 , 0);//座標補正無し
			}

			//スクショ撮影
			if (Input::key.F10.on == true)
			{
				keybd_event(VK_LWIN, 0, 0, 0);
				keybd_event(VK_LMENU, 0, 0, 0);
				keybd_event(VK_SNAPSHOT, 0, 0, 0);

				keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
				keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
			}

		}

		void Draw()
		{
			Draw背景();

			//タイトル
			static Layout& 題字 = Layout::Data(LTitle::題字);
			MSystem::タイトルロゴ.DrawRotate({ Config::解像度W / 2 , Config::解像度H * 題字.y / 100 }, 2, 0);

			//画面中央になるように計算、画像IDをY代わりに使用
			Layout::Data(LTitle::ボタン).y = Config::解像度H * 40 / 100;//UILayout::Data(UIタイトル::ボタン).画像IDでテスト
			Layout::Data(LTitle::ボタン).x = Config::解像度W / 2 - Layout::Data(LTitle::ボタン).w / 2;

			for (auto& it : ボタン)
			{			
				it.Draw();
			}

			//作者名、著作権表記
			static Layout& ライセンス = Layout::Data(LTitle::ライセンス);

			MFont::L->DrawBoldRotate({ Config::解像度W / 2 , Config::解像度H * ライセンス.y / 100 } , 1 , 0 , Color::White, Color::Black, "(C) 2021/3 (´･@･)だごん", false);

			//デバッグ用
			if (CV::isレイアウト)
			{
				Layout::Draw();
				Layout::Input();
			}
		}

		void Draw背景()
		{
			const int back_w = 384;
			const int back_h = 240;

			int b倍率 = Config::解像度H / back_h;
			int h余り = Config::解像度H % back_h;

			if (h余り > back_h / 2)
			{
				b倍率++;
				h余り -= back_h;
			}
			int 幅 = back_w * b倍率;
			int 高 = back_h * b倍率;

			int w余り = Config::解像度W - back_w * b倍率;
			int x差分 = w余り / 2;
			int y差分 = h余り / 2;

			static int scr_x = 0;

			scr_x--;
			if (scr_x <= -幅) { scr_x = 0; }

			//背景描画
			if (y差分 > 0)
			{
				Drawing::Rect({ 0,0,Config::解像度W , y差分 }, Color(107, 93, 80), true);
				Drawing::Rect({ 0,Config::解像度H - y差分,Config::解像度W , y差分 }, Color(58, 50, 43), true);
			}

			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x - 幅   ,y差分,幅,高 });
			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x        ,y差分,幅,高 });
			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x + 幅   ,y差分,幅,高 });
			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x + 幅 * 2,y差分,幅,高 });

			MSystem::タイトル前景.DrawExtend({ x差分 - 幅,y差分,幅,高 });
			MSystem::タイトル前景.DrawExtend({ x差分     ,y差分,幅,高 });
			MSystem::タイトル前景.DrawExtend({ x差分 + 幅,y差分,幅,高 });
		}
	};
}