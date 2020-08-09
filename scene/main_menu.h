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

		W_Scenario Win_Scenario;
		
		class GUI_ボタン : public GUI_Object
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
			std::string 文字;
			bool isOver = false;

			void Draw派生(double px, double py)
			{
				Screen::SetBlendMode(BlendMode::Alpha, 128);
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 10, 0);
				Screen::SetBlendMode();
				MFont::BLSize.DrawBoldRotate({ px + 位置.GetW() / 2 ,py + 位置.GetH() / 2 }, 1 , 0 , isOver ? Color::Aqua : Color::White, Color::Black, 文字, false);
				isOver = false;
			}

			void Click(double px, double py)
			{
				int 戻り値 = 0;

				switch (id)
				{
				case MenuType::はじめから:
					親->Win_NewGame.Init();

					if (親->Win_NewGame.ポップアップ呼び出し() == 1)
					{
						親->セーブ = nullptr;
						親->難易度 = 親->Win_NewGame.選択中難易度;
						親->isゲーム開始 = true;
					}

					break;
				case MenuType::つづきから:
					親->Win_Conitnue.Init();

					if (親->Win_Conitnue.ポップアップ呼び出し() == 1)
					{
						親->セーブ = 親->Win_Conitnue.GetSave();
						親->難易度 = GameType::COUNT;
						親->isゲーム開始 = true;
					}

					break;
				case MenuType::せってい:
					親->Win_Config.Init();
					親->Win_Config.ポップアップ呼び出し();
					break;
				case MenuType::クレジット:
					親->Win_Credit.Init();
					親->Win_Credit.ポップアップ呼び出し();
					break;
				case MenuType::アンケート:
					親->Win_Scenario.Init(0);
					親->Win_Scenario.ポップアップ呼び出し();
					break;
				case MenuType::おしまい:
					Game::isゲーム終了 = true;
					break;
				}
			}

			void Over(double px, double py)
			{
				isOver = true;
			}
		};

		std::array<GUI_ボタン, 6> ボタン;
	public:
		const int csv_page = 24;
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
				it.csv_page = 24;
			}
			ボタン[0].文字 = "はじめから";
			ボタン[0].id = GUI_ボタン::MenuType::はじめから;

			ボタン[1].文字 = "つづきから";
			ボタン[1].id = GUI_ボタン::MenuType::つづきから;

			ボタン[2].文字 = "せってい";
			ボタン[2].id = GUI_ボタン::MenuType::せってい;

			ボタン[3].文字 = "くれじっと";
			ボタン[3].id = GUI_ボタン::MenuType::クレジット;

			ボタン[4].文字 = "あんけーと";
			ボタン[4].id = GUI_ボタン::MenuType::アンケート;

			ボタン[5].文字 = "しゅうりょう";
			ボタン[5].id = GUI_ボタン::MenuType::おしまい;
		}

		void GUI_Init()
		{
			int a = 0, w = 0;
			for (auto& it : ボタン)
			{
				//it.文字
				w = MFont::BLSize.GetDrawStringWidth(it.文字) + Lp(8);
				it.位置 = { Window::GetWidth() / 2  - w / 2 , Window::GetHeight() * (Lp(5) + a * Lp(6))/100 , w , Lp(7) };
				a++;
			}
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
				GUI_Init();
				Input();
				Draw();

				//60fpsの調整
				while (1)
				{
					if (Time::GetNowCount() - time > frame * 50 / 3.0) { break; }
				}

				if (isゲーム開始 || Game::isゲーム終了 ) { break; }
			}
		}

		void Input()
		{
			const Point& pt = Input::mouse.GetPoint();

			//ボタンクリックとマウスオーバー判定
			for (auto& it : ボタン)
			{
				if (it.位置.Hit(&pt))
				{
					it.Over(pt.x, pt.y);
					if (Input::mouse.Left.on) { it.Click(pt.x, pt.y); }
				}
			}
		}

		void Draw()
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

			//RGB 116,112,41
			//RGB  75, 57,22


			static int scr_x = 0;

			//背景描画
			if (y差分 > 0)
			{
				Drawing::Rect({ 0,0,Window::GetWidth() , y差分 }, Color(107, 93, 80), true);
				Drawing::Rect({ 0,Window::GetHeight()-y差分,Window::GetWidth() , y差分 }, Color(58, 50, 43), true);
			}

			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x - 幅   ,y差分,幅,高 });
			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x        ,y差分,幅,高 });
			MSystem::タイトル背景.DrawExtend({ x差分 + scr_x + 幅   ,y差分,幅,高 });
			MSystem::タイトル背景.DrawExtend({ x差分 +scr_x + 幅 * 2,y差分,幅,高 });

			MSystem::タイトル前景.DrawExtend({ x差分 - 幅,y差分,幅,高 });
			MSystem::タイトル前景.DrawExtend({ x差分     ,y差分,幅,高 });
			MSystem::タイトル前景.DrawExtend({ x差分 + 幅,y差分,幅,高 });

			scr_x--;
			if (scr_x <= -幅) { scr_x = 0; }

			//タイトル
			MFont::BLSize.DrawBoldRotate({ Window::GetWidth() / 2 , Window::GetHeight() * Lp(0) / 100 } , 2, 0, Color::White, Color::Black, { "おーとだんじょんえくすぷろーら(仮)" });
			//ボタン５つ表示
			for (auto& it : ボタン)
			{
				it.Draw();
			}
			//作者名、著作権表記？
			MFont::BMSize.DrawBoldRotate({ Window::GetWidth()/2 , Window::GetHeight() * Lp(1) / 100} , 1 , 0 , Color::White, Color::Black, "(C) 2020/8 (´･@･)", false);

			//デバッグ用
			if (CV::isデバッグ)
			{
				CSVDraw();
				CSVCheckInput();
			}
		}

		inline int Lp(int no)
		{
			return CSV::I[csv_page][no];
		}
	};
}