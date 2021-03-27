//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;
	enum class LToolBar
	{
		ツールバー_全体,
		ツールバー_ウィンドウボタン,
		ツールバー_速度ボタン,
		ツールバー_その他ボタン,
		ツールバー_日付,
		ツールバー_日付文字,
		COUNT,
		PAGE = (int)UIPage::メイン画面
	};


	/*上部ツールバー*/
	class W_ToolBar : public UIWindow
	{
	private:
		static const int 表示枠 = 11;
		static const int ボタン枠 = 1;
		static const int ボタン押 = 3;

		class UITime : public UIObject
		{
		public:
			DesignType UIデザイン;

			template<class T>
			void SetUI( T レイアウト)
			{
				layout = &Layout::Data(レイアウト);
			}

			void Draw派生()
			{
				int 日 = Game::日付 + 1;
				int 時 = Game::時間 / CV::一時間フレーム数;
				int 分 = (Game::時間 / (CV::一時間フレーム数 / 60)) % 60;

				switch (layout->画像ID)
				{
				case 0:
					DrawUI(UIType::背景, Design::data[UIデザイン]);
					break;
					break;
				case 1:
					DrawUI(UIType::グループ明, Design::data[UIデザイン]);
					break;
					break;
				default:
					DrawUI(UIType::グループ暗, Design::data[UIデザイン]);
					break;
				}

				auto& it = Layout::Data(LToolBar::ツールバー_日付文字);

				MFont::F[layout->フォントID]->Draw({ GetX() + it.x, GetY() + it.y }, Design::Blue.暗字 , { 日 , "日" }, true);
				MFont::F[layout->フォントID]->Draw({ GetX() + it.x + it.並べx, GetY() + it.y + it.並べy }, Design::Blue.暗字, { 時 , ":" , 分 }, true);
			}
		};

		class UIWindowButton : public UIButton
		{
		public:
			//対象ウィンドウが閉じてると出っ張る仕様
			UIWindow* 対象ウィンドウ;
			bool isポップアップ = false;

			void Draw派生() override
			{
				//対象ウィンドウが表示中は凹み状態になる
				is押下 = (対象ウィンドウ->is表示 == true);

				UIButton::Draw派生();
			}

			void Click() override
			{
				if (isポップアップ)
				{
					対象ウィンドウ->OpenPopup();

					if (対象ウィンドウ->ポップアップリザルト > 0)
					{
						clickEvent();
					}
				}
				else
				{
					対象ウィンドウ->is表示 = !対象ウィンドウ->is表示;
					対象ウィンドウ->is最前面へ移動 = true;
				}
			}
		};

		class UISpeedButton : public UIButton
		{
		public:
			void Draw派生() override
			{
				//倍速値、アイコン、現在設定と同じなら凹ませる

				if (Config::is超加速 == true)
				{
					if (lineID == 3) { is押下 = Game::is停止; }
					if (lineID == 2) { is押下 = (Game::ゲームスピード == 1); }
					if (lineID == 1) { is押下 = (Game::ゲームスピード == 8); }
					if (lineID == 0) { is押下 = (Game::ゲームスピード == 64); }
				}
				else
				{
					if (lineID == 3) { is押下 = Game::is停止; }
					if (lineID == 2) { is押下 = (Game::ゲームスピード == 1); }
					if (lineID == 1) { is押下 = (Game::ゲームスピード == 4); }
					if (lineID == 0) { is押下 = (Game::ゲームスピード == 16); }
				}

				UIButton::Draw派生();
			}

			void Click() override
			{
				switch (lineID)
				{
				case 3:
					Game::is停止 = !Game::is停止;
					break;
				case 2://x1
					Game::ゲームスピード = Config::is超加速 ? 1 : 1;
					break;
				case 1://x4/8
					Game::ゲームスピード = Config::is超加速 ? 8 : 4;
					break;
				case 0://x16/64
					Game::ゲームスピード = Config::is超加速 ? 64 : 16;
					break;
				}
			}
		};

	public:
		UITime 日付表示;

		UIWindowButton ウィンドウボタン[CV::ウィンドウ数];

		UISpeedButton 停止ボタン;//一時停止時凹む仕様
		UISpeedButton 速度ボタンA;//左右でクリック時の処理が異なる仕様
		UISpeedButton 速度ボタンB;//左右でクリック時の処理が異なる仕様
		UISpeedButton 速度ボタンC;//左右でクリック時の処理が異なる仕様
		UIWindowButton ヘルプボタン;
		UIWindowButton コンフィグボタン;
		UIWindowButton タイトルボタン;

		void Init()
		{
			Update();
			//UI基礎パラメータ設定
			日付表示.SetUI(LToolBar::ツールバー_日付);

			for(int i=0;i<CV::ウィンドウ数;i++)
			{ 
				ウィンドウボタン[i].SetUI( LToolBar::ツールバー_ウィンドウボタン,i);
				ウィンドウボタン[i].layout->改行値 = 100;
				ウィンドウボタン[i].画像位置 = 8;
				ウィンドウボタン[i].テキスト位置 = 2;
			}

			停止ボタン.SetUI( "＝", LToolBar::ツールバー_速度ボタン,3);//一時停止時凹む仕様
			速度ボタンA.SetUI( "＞", LToolBar::ツールバー_速度ボタン,2);//左右でクリック時の処理が異なる仕様
			速度ボタンB.SetUI( ">>", LToolBar::ツールバー_速度ボタン,1);//左右でクリック時の処理が異なる仕様
			速度ボタンC.SetUI( ">>>", LToolBar::ツールバー_速度ボタン,0);//左右でクリック時の処理が異なる仕様

			ヘルプボタン.SetUI(&MIcon::UI[IconType::BGM], "ヘルプ", LToolBar::ツールバー_その他ボタン, 2);
			コンフィグボタン.SetUI(&MIcon::UI[IconType::BGM], "設定", LToolBar::ツールバー_その他ボタン , 1);
			タイトルボタン.SetUI(&MIcon::UI[IconType::BGM], "終了", LToolBar::ツールバー_その他ボタン , 0);

			//基準座標を左上にする
			停止ボタン.isLeftPos = false;
			速度ボタンA.isLeftPos = false;
			速度ボタンB.isLeftPos = false;
			速度ボタンC.isLeftPos = false;
			ヘルプボタン.isLeftPos = false;
			コンフィグボタン.isLeftPos = false;
			タイトルボタン.isLeftPos = false;

			//ポップアップ設定
			コンフィグボタン.isポップアップ = true;
			ヘルプボタン.isポップアップ = true;
			タイトルボタン.isポップアップ = true;

			タイトルボタン.clickEvent = []() { Game::isゲーム終了 = true; };

			//オブジェクト登録
			for (int i = 0; i < CV::ウィンドウ数; i++)
			{
				AddItem(ウィンドウボタン[i]);
			}

			AddItem(日付表示);
			AddItem(停止ボタン);
			AddItem(速度ボタンA);
			AddItem(速度ボタンB);
			AddItem(速度ボタンC);
			AddItem(コンフィグボタン);
			AddItem(ヘルプボタン);
			AddItem(タイトルボタン);

			//描画とクリック時のイベントを登録

		}

		void SetWindow(std::vector<UIWindow*> &windows , UIWindow* help , UIWindow* config, UIWindow* title)
		{
			for (int a = 0; a < CV::ウィンドウ数; a++)
			{
				ウィンドウボタン[a].対象ウィンドウ = windows[a];
				ウィンドウボタン[a].テキスト = TX::Window_略記[windows[a]->種類];
				ウィンドウボタン[a].画像 = &MIcon::UI[ウィンドウボタン[a].対象ウィンドウ->アイコン];
			}

			ヘルプボタン.対象ウィンドウ = help;
			コンフィグボタン.対象ウィンドウ = config;
			タイトルボタン.対象ウィンドウ = title;
		}


		void Draw()
		{
			//枠無しウィンドウ
			Design::data[DesignType::セット1]->Draw(UIType::ウィンドウ, Layout::Data(LToolBar::ツールバー_全体));

			//日付と時刻、各種ボタンの表示
			for (int a = (int)item.size() - 1; a >= 0; a--)
			{
				if (item[a]->is表示) { item[a]->Draw(); }
			}
		}

		void Update()
		{
			//画面サイズに合わせてツールバー大きさ変更
			auto& it = Layout::Data(LToolBar::ツールバー_全体);
			it.x = 0;
			it.y = 0;
			it.w = Config::解像度W;
			UIWindow::ツールバー高さ = it.h;
		}

		bool CheckInfo()
		{
			return false;
		}
	};
}