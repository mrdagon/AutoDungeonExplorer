//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*上部ツールバー*/
	class W_ToolBar : public UIWindow
	{
	private:
		class UITime : public UIObject
		{
		public:
			Design** UIデザイン = &Design::No1;

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
					DrawUI(UIType::グループ明, *UIデザイン );
					break;
					break;
				case 1:
					DrawUI(UIType::グループ中, *UIデザイン );
					break;
					break;
				default:
					DrawUI(UIType::グループ暗, *UIデザイン );
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


				if (lineID == 4) { is押下 = Game::is停止; }
				if (lineID == 3) { is押下 = (Game::ゲームスピード == 1); }
				if (lineID == 2) { is押下 = (Game::ゲームスピード == 4); }
				if (lineID == 1) { is押下 = (Game::ゲームスピード == 16); }
				if (lineID == 0) { is押下 = (Game::ゲームスピード == 64); }


				UIButton::Draw派生();
			}

			void Click() override
			{
				switch (lineID)
				{
				case 4:
					Game::is停止 = !Game::is停止;
					break;
				case 3:
					Game::ゲームスピード = 1;
					break;
				case 2://x4
					Game::ゲームスピード = 4;
					break;
				case 1://x16
					Game::ゲームスピード = 16;
					break;
				case 0://x64
					Game::ゲームスピード = 64;
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
		UISpeedButton 速度ボタンD;//左右でクリック時の処理が異なる仕様
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

			停止ボタン.SetUI( LToolBar::ツールバー_速度ボタン, "＝",4);//一時停止時凹む仕様
			速度ボタンA.SetUI(  LToolBar::ツールバー_速度ボタン, "x 1" ,3);//左右でクリック時の処理が異なる仕様
			速度ボタンB.SetUI(  LToolBar::ツールバー_速度ボタン , "x 4", 2);//左右でクリック時の処理が異なる仕様
			速度ボタンC.SetUI(  LToolBar::ツールバー_速度ボタン , "x16", 1);//左右でクリック時の処理が異なる仕様
			速度ボタンD.SetUI( LToolBar::ツールバー_速度ボタン, "x64", 0);//左右でクリック時の処理が異なる仕様

			ヘルプボタン.SetUI(LToolBar::ツールバー_その他ボタン, &MIcon::UI[IconType::BGM], "ヘルプ",  2);
			コンフィグボタン.SetUI(LToolBar::ツールバー_その他ボタン , &MIcon::UI[IconType::BGM], "設定"  , 1);
			タイトルボタン.SetUI(LToolBar::ツールバー_その他ボタン, &MIcon::UI[IconType::BGM], "終了",  0);

			//基準座標を左上にする
			停止ボタン.isLeftDock = false;
			速度ボタンA.isLeftDock = false;
			速度ボタンB.isLeftDock = false;
			速度ボタンC.isLeftDock = false;
			速度ボタンD.isLeftDock = false;
			ヘルプボタン.isLeftDock = false;
			コンフィグボタン.isLeftDock = false;
			タイトルボタン.isLeftDock = false;

			//ポップアップ設定
			コンフィグボタン.isポップアップ = true;
			ヘルプボタン.isポップアップ = true;
			タイトルボタン.isポップアップ = true;

			タイトルボタン.clickEvent = []() { Game::isゲーム終了 = true; };

			//オブジェクト登録
			item.clear();
			for (int i = 0; i < CV::ウィンドウ数; i++)
			{
				AddItem(ウィンドウボタン[i]);
			}

			AddItem(日付表示);
			AddItem(停止ボタン);
			AddItem(速度ボタンA);
			AddItem(速度ボタンB);
			AddItem(速度ボタンC);
			AddItem(速度ボタンD);
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
			Design::No1->Draw(UIType::ウィンドウ, Layout::Data(LToolBar::ツールバー_全体));

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

	};
}