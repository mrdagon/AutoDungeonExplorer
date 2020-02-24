//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[2][a]


#define LVRect(a) {LV(a),LV(a+1),LV(a+2),LV(a+3)}


	/*上部ツールバー*/
	class W_ToolBar
	{
	private:
		static const int 表示枠 = 1;
		static const int ボタン枠 = 1;
		static const int ボタン押 = 3;

		class G_日付 : public GUI_Object
		{
		public:
			void Draw派生(double px,double py)
			{
				int y = Game::日付 / 336 + 1;
				int m = (Game::日付 / 28)%12 + 1;
				int d = Game::日付 % 28 + 1;

				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::アイコン[IconType::日付].DrawRotate({ px+14,py + 14 }, 2, 0);
				MFont::Arial大.DrawBold({ px + 150,py - 3 }, Color::White, Color::Black, { y,"/", m/10, m%10 , "/" , d/10, d%10 }, true);
				MFont::Arial大.DrawBold({ px + 210,py - 3 }, Color::White, Color::Black, "Sun", true);
			}
		};
		class G_時刻 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				int jikan = Game::時間 / 360;
				int hun = (Game::時間 / 6 )% 60;
				Color 文字色 = Color::White;
				if (Game::時間 > Game::就寝時間 || Game::時間 < Game::起床時間) { 文字色 = Color::Blue; }
				else if (Game::is仕事中 == true) { 文字色 = {255,128,128}; }

				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::アイコン[IconType::時間].DrawRotate({ px + 14,py + 14 },2,0);
				MFont::Arial大.DrawBold({ px + 94,py - 3 }, 文字色, Color::Black, { jikan ,":",hun/10,hun%10}, true);
			}
		};
		class G_人口 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::アイコン[IconType::人口].DrawRotate({ px + 14,py + 14 }, 2, 0);
				MFont::Arial大.DrawBold({ px+位置.GetW() - 5,py - 3 }, Color::White, Color::Black, {Game::人口},true);
			}
		};

		class G_資金 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), 表示枠, 0);
				MIcon::アイコン[IconType::資金].DrawRotate({ px + 14,py + 14 }, 2, 0);

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

				MFont::Arial大.DrawBold({ px+位置.GetW()-5,py-3 }, Color::White, Color::Black, str,true);

			}
		};
		class G_ウィンドウ : public GUI_Object
		{
		public:
			WindowBox* 対象ウィンドウ;


			void Draw派生(double px, double py)
			{
				//対象ウィンドウ->アイコン
				if (対象ウィンドウ->is表示)
				{
					MSystem::DrawWindow({px,py  },位置.GetW(),位置.GetH(), ボタン押, -1);
				} else {
					MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				}
				MIcon::アイコン[対象ウィンドウ->アイコン].DrawRotate({px+LV(22),py+ LV(23)}, 2, 0);
				MFont::Bメイリオ小.DrawBold({px + LV(24),py + LV(25) }, Color::White, Color::Black, 対象ウィンドウ->略記);
			}

			void Click(double px, double py)
			{
				対象ウィンドウ->is表示 = !対象ウィンドウ->is表示;
				対象ウィンドウ->is最前面 = 対象ウィンドウ->is表示;
			}

		};
		class G_ヘルプ : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::アイコン[IconType::ヘルプ].DrawRotate({ px + LV(22),py + LV(23) }, 2, 0);
				MFont::Bメイリオ小.DrawBold({ px + LV(24)-7,py + LV(25) }, Color::White, Color::Black, "ヘルプ");

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

				MIcon::アイコン[IconType::停止].DrawRotate({ px + LV(22),py + LV(23) }, 2, 0);
				MFont::Bメイリオ小.DrawBold({ px + LV(24),py + LV(25) }, Color::White, Color::Black, "停止");
			}

			void Click(double px, double py)
			{
				Game::is停止 = !Game::is停止;
			}
		};
		class G_速度 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::アイコン[IconType::速度].DrawRotate({ px + LV(22) + LV(26),py + LV(23) }, 2, 0);
				MIcon::アイコン[IconType::三角].DrawRotate({ px + LV(22) + LV(26) - 25,py + LV(23) }, 2, 0);
				MIcon::アイコン[IconType::三角].DrawRotate({ px + LV(22) + LV(26) + 25,py + LV(23) }, 2, 0,true);

				MFont::Bメイリオ小.DrawBold({ px + LV(24)+LV(26),py + LV(25) }, Color::White, Color::Black, "速度");
				MFont::Arial中.DrawBold({ px + LV(24) + LV(26) + 5,py + LV(25) - 20 }, Color::White, Color::Black, "x", true);
				MFont::Arial中.DrawBold({ px + LV(24) + LV(26) + 28,py + LV(25) - 20 }, Color::White, Color::Black, Game::ゲームスピード,true);

			}

			void Click(double px, double py)
			{
				if (px < 位置.GetW() / 2)
				{
					Game::ゲームスピード = std::max(1, Game::ゲームスピード / 2);
				}else {
					Game::ゲームスピード = std::min(64, Game::ゲームスピード * 2);
				}
			}

		};
		class G_設定 : public GUI_Object
		{
		public:
			WindowBox* 対象ウィンドウ;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::アイコン[IconType::設定].DrawRotate({ px + LV(22),py + LV(23) }, 2, 0);
				MFont::Bメイリオ小.DrawBold({ px + LV(24),py + LV(25) }, Color::White, Color::Black, "設定");
			}

			void Click(double px, double py)
			{
				//設定ウィンドウ開く
				対象ウィンドウ->is表示 = true;
				対象ウィンドウ->is最前面 = true;
				対象ウィンドウ->サブ呼び出し();
			}

		};

		class G_タイトル : public GUI_Object
		{
		public:
			WindowBox* 対象ウィンドウ;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH(), ボタン枠, 1);
				MIcon::アイコン[IconType::出口].DrawRotate({ px + LV(22),py + LV(23) }, 2, 0);
				MFont::Bメイリオ小.DrawBold({ px + LV(24),py + LV(25) }, Color::White, Color::Black, "終了");
			}

			void Click(double px, double py)
			{
				//確認ウィンドウを出す
				対象ウィンドウ->is表示 = true;
				対象ウィンドウ->is最前面 = true;
				対象ウィンドウ->サブ呼び出し();
			}
		};
	public:
		std::vector <GUI_Object*> gui_objects;

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

		void SetWindow(std::vector<WindowBox*> &windows)
		{
			for (int a = 0; a < CV::ウィンドウ数; a++)
			{
				ウィンドウ[a].対象ウィンドウ = windows[a];
			}
		}

		void SetConfig(WindowBox* config, WindowBox* title)
		{
			設定.対象ウィンドウ = config;
			タイトル.対象ウィンドウ = title;
		}

		void init()
		{
			gui_objects.push_back(&日付);
			gui_objects.push_back(&時刻);
			gui_objects.push_back(&人口);
			gui_objects.push_back(&資金);
			for (int a = 0; a < CV::ウィンドウ数; a++)
			{
				gui_objects.push_back(&ウィンドウ[a]);
			}
			gui_objects.push_back(&ヘルプ);
			gui_objects.push_back(&停止);
			gui_objects.push_back(&速度);
			gui_objects.push_back(&設定);
			gui_objects.push_back(&タイトル);			
		}

		void GUI_init()
		{
			for (int a = 0; a < CV::ウィンドウ数; a++)
			{
				ウィンドウ[a].位置 = {LV(0) +LV(4)*a,LV(1),LV(2),LV(3)};
			}
			日付.位置 = { LV(5),LV(6),LV(7),LV(8)};
			時刻.位置 = { LV(9),LV(6),LV(10),LV(8) };
			人口.位置 = { Window::GetWidth() - LV(13),LV(6),LV(14),LV(8) };
			資金.位置 = { Window::GetWidth() - LV(15),LV(6),LV(16),LV(8) };

			ヘルプ.位置 = { Window::GetWidth() - LV(17),LV(1),LV(2),LV(3)};
			停止.位置 = { Window::GetWidth() - LV(18),LV(1),LV(2),LV(3) };
			速度.位置 = { Window::GetWidth() - LV(19),LV(1),LV(21),LV(3) };
			設定.位置 = { Window::GetWidth() - LV(27),LV(1),LV(2),LV(3) };
			タイトル.位置 = { Window::GetWidth() - LV(20),LV(1),LV(2),LV(3) };

		}

		void Draw()
		{
			GUI_init();

			//MSystem::DrawWindow({0,0}, Window::GetWidth(),40,8);
			MSystem::DrawWindow({0,0},Window::GetWidth(), WindowBox::ツールバー高さ,7);

			for (auto& it : gui_objects)
			{
				it->Draw();
			}
		}

		bool 操作()
		{
			for (auto& it : gui_objects)
			{
				it->操作チェック(0,0);
			}
			return false;
		}

		bool CheckInformation()
		{
			for (auto& it : gui_objects)
			{

				if (it->位置.Hit(&Input::mouse.GetPoint()))
				{
					it->Info();
					return true;
				}
			}

			return false;
		}

#undef LV
#undef LV2
#undef LV4
	};
}