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

		class GUI_ボタン : public UIButton
		{
		public:

			enum class MenuType
			{
				はじめから,
				つづきから,
				せってい,
				クレジット,
				アンケート,
				おしまい,
				COUNT
			};

			MainMenu* 親;
			MenuType id;

			void Click(double px, double py)
			{
				int 戻り値 = 0;

				switch (id)
				{
				case MenuType::はじめから:
					親->Win_NewGame.Init();

					if (親->Win_NewGame.Openポップアップ() == 1)
					{
						親->セーブ = nullptr;
						親->難易度 = 親->Win_NewGame.選択中難易度;
						親->isゲーム開始 = true;
					}

					break;
				case MenuType::つづきから:
					親->Win_Conitnue.Init();

					if (親->Win_Conitnue.Openポップアップ() == 1)
					{
						親->セーブ = 親->Win_Conitnue.GetSave();
						親->難易度 = GameType::COUNT;
						親->isゲーム開始 = true;
					}

					break;
				case MenuType::せってい:
					親->Win_Config.Init();
					親->Win_Config.Openポップアップ();
					break;
				case MenuType::クレジット:
					親->Win_Credit.Init();
					親->Win_Credit.Openポップアップ();
					break;
				case MenuType::アンケート:
					ShellExecute(NULL, L"open", TX::アンケURL , NULL, L"", SW_SHOW);
					break;
				case MenuType::おしまい:
					Game::isゲーム終了 = true;
					break;
				}
			}
		};

		std::array<GUI_ボタン, 6> ボタン;
	public:
		bool isゲーム開始;

		GameType 難易度;
		SaveData* セーブ;

		//初期化処理
		void Init()
		{
			isゲーム開始 = false;

			for (auto& it : ボタン)
			{
				it.親 = this;
			}

			ボタン[0].id = GUI_ボタン::MenuType::はじめから;
			ボタン[0].SetUI( "始めから", &UIDesign::Brown, UIタイトル::ボタン, 0);

			ボタン[1].id = GUI_ボタン::MenuType::つづきから;
			ボタン[1].SetUI("続きから", &UIDesign::Brown, UIタイトル::ボタン, 1);

			ボタン[2].id = GUI_ボタン::MenuType::せってい;
			ボタン[2].SetUI("設定", &UIDesign::Brown, UIタイトル::ボタン, 2);

			ボタン[3].id = GUI_ボタン::MenuType::クレジット;
			ボタン[3].SetUI("クレジット", &UIDesign::Brown, UIタイトル::ボタン , 3);

			ボタン[4].id = GUI_ボタン::MenuType::アンケート;
			ボタン[4].SetUI("アンケート", &UIDesign::Brown, UIタイトル::ボタン , 4);

			ボタン[5].id = GUI_ボタン::MenuType::おしまい;
			ボタン[5].SetUI("終了", &UIDesign::Brown, UIタイトル::ボタン , 5);
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
				Draw();

				//60fpsの調整
				while (1)
				{
					if (Time::GetNowCount() - time > frame * 50 / 3.0) { break; }
				}

				if (isゲーム開始 || Game::isゲーム終了 )
				{
					break;
				}
			}
		}

		void Input()
		{
			const Point& pt = Input::mouse.GetPoint();

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
			static UILayout& 題字 = UILayout::Data(UIタイトル::題字);
			MSystem::タイトルロゴ.DrawRotate({ Window::GetWidth() / 2 , Window::GetHeight() * 題字.y / 100 }, 2, 0);

			//画面中央になるように計算、画像IDをY代わりに使用
			UILayout::Data(UIタイトル::ボタン).y = Window::GetHeight() * 40 / 100;//UILayout::Data(UIタイトル::ボタン).画像IDでテスト
			UILayout::Data(UIタイトル::ボタン).x = Window::GetWidth() / 2 - UILayout::Data(UIタイトル::ボタン).w / 2;

			for (auto& it : ボタン)
			{			
				it.Draw();
			}

			//作者名、著作権表記
			static UILayout& ライセンス = UILayout::Data(UIタイトル::ライセンス);

			MFont::M->DrawBoldRotate({ Window::GetWidth() / 2 , Window::GetHeight() * ライセンス.y / 100 } , 1 , 0 , Color::White, Color::Black, "(C) 2021/3 (´･@･)だごん", false);

			//デバッグ用
			if (CV::isレイアウト)
			{
				UILayout::Draw();
				UILayout::Input();
			}
		}

		void Draw背景()
		{
			const int back_w = 384;
			const int back_h = 240;

			int b倍率 = Window::GetHeight() / back_h;
			int h余り = Window::GetHeight() % back_h;

			if (h余り > back_h / 2)
			{
				b倍率++;
				h余り -= back_h;
			}
			int 幅 = back_w * b倍率;
			int 高 = back_h * b倍率;

			int w余り = Window::GetWidth() - back_w * b倍率;
			int x差分 = w余り / 2;
			int y差分 = h余り / 2;

			static int scr_x = 0;

			scr_x--;
			if (scr_x <= -幅) { scr_x = 0; }

			//背景描画
			if (y差分 > 0)
			{
				Drawing::Rect({ 0,0,Window::GetWidth() , y差分 }, Color(107, 93, 80), true);
				Drawing::Rect({ 0,Window::GetHeight() - y差分,Window::GetWidth() , y差分 }, Color(58, 50, 43), true);
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