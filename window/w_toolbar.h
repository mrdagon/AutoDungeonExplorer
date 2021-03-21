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
		static const int 表示枠 = 11;
		static const int ボタン枠 = 1;
		static const int ボタン押 = 3;

		class G_日付 : public GUI_Object
		{
		public:
			void Draw派生(double px,double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::UI[IconType::日付].DrawRotate({ px+16,py + 14 }, 2, 0);
				MFont::LDot.DrawBold({ px + 150,py - 3 }, Color::White, Color::Black, { Game::日付 + 1 , TX::Tool_日付 }, true);
			}
		};
		class G_時刻 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				int jikan = Game::時間 / CV::一時間フレーム数;
				int hun = (Game::時間 / (CV::一時間フレーム数 / 60) )% 60;
				Color 文字色 = Color::White;
				if (Game::時間 > Game::就寝時間 || Game::時間 < Game::起床時間) { 文字色 = Color::Blue; }
				else if (Game::is仕事中 == true) { 文字色 = {255,128,128}; }

				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::UI[IconType::時間].DrawRotate({ px + 14,py + 14 },2,0);
				MFont::LDot.DrawBold({ px + 94,py - 3 }, 文字色, Color::Black, { jikan ,":",hun/10,hun%10}, true);

				if (Game::時間 < Game::始業時間 || Game::時間 > Game::終業時間)
				{
					MFont::LDot.DrawBold({ px + Lp(34),py - 3 }, Color::White, Color::Black, { TX::Tool_待機中 }, true);
				} else {
					MFont::LDot.DrawBold({ px + Lp(34),py - 3 }, Color::White, Color::Black, { TX::TooL_活動中 }, true);
				}
			}
		};
		class G_人口 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::UI[IconType::人口].DrawRotate({ px + 14,py + 14 }, 2, 0);
			}
		};

		class G_資金 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::UI[IconType::資金].DrawRotate({ px + 14,py + 14 }, 2, 0);

				std::string str = "G";
				double g = Guild::P->資金;
				while (1)
				{
					str = std::to_string((int)g%1000) + str;

					if (g < 1000) { break; }
					if ((int)g%1000 < 10)
					{
						str = "00" + str;
					}
					else if ((int)g % 1000 < 100)
					{
						str = "0" + str;
					}

					g /= 1000;
					str = "," + str;
				}

				MFont::LDot.DrawBold({ px+位置.GetW()-5,py-3 }, Color::White, Color::Black, str,true);

			}
		};
		class G_ウィンドウ : public GUI_Object
		{
		public:
			UIWindow* 対象ウィンドウ;

			void Draw派生(double px, double py)
			{
				//対象ウィンドウ->アイコン
				if (対象ウィンドウ->is表示)
				{
					MSystem::DrawWindow({px,py  },位置.GetW(),位置.GetH(), ボタン押, -1);
				} else {
					MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				}
				MIcon::UI[対象ウィンドウ->アイコン].DrawRotate({px+Lp(22),py+ Lp(23)}, 2, 0);
				MFont::SAlias.DrawBold({px + Lp(24),py + Lp(25) }, Color::White, Color::Black, TX::Window_略記[対象ウィンドウ->種類]);
			}

			void Click(double px, double py)
			{
				対象ウィンドウ->is表示 = !対象ウィンドウ->is表示;
				対象ウィンドウ->is最前面へ移動 = 対象ウィンドウ->is表示;

				if (対象ウィンドウ->is表示)
				{
					MSound::効果音[SE::ウィンドウ開く].Play();
				} else {
					MSound::効果音[SE::ウィンドウ閉じ].Play();
				}

			}

		};
		class G_ヘルプ : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::UI[IconType::ヘルプ].DrawRotate({ px + Lp(22),py + Lp(23) }, 2, 0);
				MFont::SAlias.DrawBold({ px + Lp(24)-7,py + Lp(25) }, Color::White, Color::Black, TX::Tool_ヘルプ );

			}
		};
		class G_停止 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				if (Game::is停止)
				{
					MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン押, -1);

				} else {
					MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				}

				MIcon::UI[IconType::停止].DrawRotate({ px + Lp(22),py + Lp(23) }, 2, 0);
				MFont::SAlias.DrawBold({ px + Lp(24),py + Lp(25) }, Color::White, Color::Black, TX::Tool_停止);
			}

			void Click(double px, double py)
			{
				Game::is停止 = !Game::is停止;
				MSound::効果音[SE::ボタンクリック].Play();
			}
		};
		class G_速度 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::UI[IconType::速度].DrawRotate({ px + Lp(22) + Lp(26),py + Lp(23) }, 2, 0);
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(22) + Lp(26) - 25,py + Lp(23) }, 2, 0);
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(22) + Lp(26) + 25,py + Lp(23) }, 2, 0,true);

				MFont::SAlias.DrawBold({ px + Lp(24)+Lp(26),py + Lp(25) }, Color::White, Color::Black, TX::Tool_速度);
				MFont::MDot.DrawBold({ px + Lp(24) + Lp(26) + 5,py + Lp(25) - 20 }, Color::White, Color::Black, "x", true);
				MFont::MDot.DrawBold({ px + Lp(24) + Lp(26) + 28,py + Lp(25) - 20 }, Color::White, Color::Black, Game::ゲームスピード,true);

			}

			void Click(double px, double py)
			{
				if (px < 位置.GetW() / 2)
				{
					Game::ゲームスピード = std::max(1, Game::ゲームスピード / Config::ゲーム速度変更倍率);
				}else {
					Game::ゲームスピード = std::min(Config::最大ゲーム倍速, Game::ゲームスピード * Config::ゲーム速度変更倍率);
				}
				MSound::効果音[SE::ボタンクリック].Play();
			}

		};
		class G_設定 : public GUI_Object
		{
		public:
			UIWindow* 対象ウィンドウ;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::UI[IconType::設定].DrawRotate({ px + Lp(22),py + Lp(23) }, 2, 0);
				MFont::SAlias.DrawBold({ px + Lp(24),py + Lp(25) }, Color::White, Color::Black, TX::Tool_設定);
			}

			void Click(double px, double py)
			{
				//設定ウィンドウ開く
				MSound::効果音[SE::ボタンクリック].Play();
				対象ウィンドウ->is表示 = true;
				対象ウィンドウ->is最前面へ移動 = true;
				対象ウィンドウ->Openポップアップ();
			}

		};

		class G_タイトル : public GUI_Object
		{
		public:
			UIWindow* 対象ウィンドウ;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::UI[IconType::終了].DrawRotate({ px + Lp(22),py + Lp(23) }, 2, 0);
				MFont::SAlias.DrawBold({ px + Lp(24),py + Lp(25) }, Color::White, Color::Black, TX::Tool_タイトル);
			}

			void Click(double px, double py)
			{
				//確認ウィンドウを出す
				MSound::効果音[SE::ボタンクリック].Play();
				対象ウィンドウ->is表示 = true;
				対象ウィンドウ->is最前面へ移動 = true;
				int id = 対象ウィンドウ->Openポップアップ();

				if (id == 1)//はい
				{
					Game::isゲーム終了 = true;
				}
			}
		};
	public:
		G_日付 日付;
		G_時刻 時刻;
		G_人口 人口;
		G_資金 資金;
		G_ウィンドウ ウィンドウ[CV::ウィンドウ数];
		G_ヘルプ ヘルプ;
		G_停止 停止;
		G_速度 速度;
		G_設定 設定;
		G_タイトル タイトル;

		GUI_Frame 枠;

		void SetWindow(std::vector<UIWindow*> &windows)
		{
			for (int a = 0; a < CV::ウィンドウ数; a++)
			{
				ウィンドウ[a].対象ウィンドウ = windows[a];
			}
		}

		void SetConfig(UIWindow* config, UIWindow* title)
		{
			設定.対象ウィンドウ = config;
			タイトル.対象ウィンドウ = title;
		}

		void Init()
		{
		}

		void GUI_Update()
		{

		}

		void Draw()
		{
		}

		bool 操作()
		{
			return false;
		}

		bool CheckInfo()
		{
			return false;
		}
	};
}