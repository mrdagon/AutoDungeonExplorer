//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	//LayoutValue
	#define LV(a) DV::I[0][a]
	
	
	using namespace SDX;

	/*経営戦略ウィンドウ*/
	class W_Management : public WindowBox
	{
	private:
		class GUI_MLv : public GUI_Object
		{
		public:
			ManagementType 部門;

			void Draw派生(double px, double py)
			{
				double rate = (double)Guild::P->部門経験値[部門]/CV::部門レベルアップ経験値[Guild::P->部門Lv[部門]];

				MSystem::DrawBar({ px,py }, (int)位置.GetW(), (int)位置.GetH(), rate, 1, Color::Blue, Color::White, Color::White, true);

				MFont::Arial小.DrawBold({ px + 43,py - 5 }, Color::White, Color::Black, { "Lv",Guild::P->部門Lv[部門] });

			}
		};

		class GUI_MP : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//ゲージで消費量と現在値、割合を表示

				double rate = 0;
				if (Guild::P->選択戦術 != nullptr)
				{
					rate = Guild::P->現在MP / Guild::P->選択戦術->消費MP;
				}

				MSystem::DrawBar({ px,py }, (int)位置.GetW(), (int)位置.GetH(), rate, 1, Color::Aqua, Color::White, Color::White, true);

				MFont::Arial大.DrawBold({ px + 235,py }, Color::White, Color::Black, { Guild::P->現在MP , " / "}, true);


				if (Guild::P->選択戦術 != nullptr)
				{
					MFont::Arial大.DrawBold({ px + 270,py }, Color::White, Color::Black, { Guild::P->選択戦術->消費MP },true);
				} else {
					MFont::Arial大.DrawBold({ px + 270,py }, Color::White, Color::Black, { "----" }, true);
				}
			}
		};

		class GUI_Gold : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//選択戦術の資金消費を表示、不足している場合赤色
				MSystem::DrawBox({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::Yellow);

				if (Guild::P->選択戦術 != nullptr)
				{
					Color fc = Color::White;
					if (Guild::P->選択戦術->消費資金 > Guild::P->資金) { fc = Color::Red; }
					MFont::Arial中.DrawBold({ px + 270 ,py }, fc, Color::Black, {"- " ,Guild::P->選択戦術->消費資金 , "G"}, true);
				}
			}
		};
		class GUI_Rank : public GUI_Object
		{
		public:
			int ランク = 0;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px ,py }, 位置.GetW(), 位置.GetH(), 7);

				for (int a = 0; a < ランク; a++)
				{
					MIcon::アイコン[IconType::星].Draw({ px + 50 + a * 15 , py + 2 });
				}

				MFont::Arial中.DrawBold({ px + 4,py }, Color::White, Color::Black, "Rank");

			}
		};
		class GUI_Skill : public GUI_Object
		{
		public:
			Management* 参照戦術;

			void Draw派生(double px, double py)
			{
				Color bc = Color::Black;
				if (Guild::P->選択戦術 == 参照戦術) { bc = Color::Red; }

				MSystem::DrawBoxBold({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::White, 1 ,bc);
				MIcon::アイコン[参照戦術->アイコン].DrawRotate({px + (int)位置.GetW()/2,py + (int)位置.GetH()/2 },2,0);

			}
			void Click(double px, double py)
			{
				if (Guild::P->選択戦術 != 参照戦術)
				{
					Guild::P->選択戦術 = 参照戦術;
				} else {
					Guild::P->選択戦術 = nullptr;
				}

			}

			void Info派生(Point 座標) override
			{
				InfoManagement(参照戦術, 座標);
			}

		};

	public:
		std::vector<GUI_Tab> タブ;
		GUI_MP gui_mp;//現在のMP
		GUI_Gold gui_gold;//消費資金
		GUI_MLv gui_mlv[4];//部門LVと経験値バー

		GUI_Rank gui_rank[10];//ランク毎の区切り-10個？
		GUI_Skill gui_skill[100];//各種戦術アイコン、とりあえず最大100

		//消費資金

		int 現在タブ = 0;
		int 戦術数 = 0;

		void init()
		{
			種類 = WindowType::Management;
			名前 = "経営戦略";
			略記 = "戦略";
			アイコン = IconType::戦略;
			横幅 = 320;
			縦幅 = 300;
			最小縦 = 200;
			最大縦 = 600;
			縦内部幅 = 600;//変動する
			固定縦 = 115;
			スクロール位置 = 0;

			ヘルプメッセージ = "経営戦術と残りMP\n";
			ヘルプ横幅 = MFont::メイリオ中.GetDrawStringWidth(ヘルプメッセージ) + 20;
			ヘルプ縦幅 = 40;

			タブ.emplace_back(現在タブ, 0, IconType::星, "経営");
			タブ.emplace_back(現在タブ, 1, IconType::星, "人事");
			タブ.emplace_back(現在タブ, 2, IconType::星, "製造");
			タブ.emplace_back(現在タブ, 3, IconType::星, "探索");

			gui_mlv[0].部門 = ManagementType::経営;
			gui_mlv[1].部門 = ManagementType::人事;
			gui_mlv[2].部門 = ManagementType::製造;
			gui_mlv[3].部門 = ManagementType::探索;

			gui_objects.push_back(&gui_mp);
			gui_objects.push_back(&gui_gold);
			for (int a = 0; a < 4; a++) { gui_objects.push_back(&タブ[a]); }
			for (int a = 0; a < 4; a++) { gui_objects.push_back(&gui_mlv[a]); }
			for (int a = 0; a < 10; a++) { gui_objects.push_back(&gui_rank[a]); }
			for (int a = 0; a < 100; a++) { gui_objects.push_back(&gui_skill[a]); }

			gui_mp.SetHelp("mp");
			gui_gold.SetHelp("gold");
			for (int a = 0; a < 4; a++) { タブ[a].SetHelp("tab"); }
			for (int a = 0; a < 4; a++) { gui_mlv[a].SetHelp("mlv"); }
			for (int a = 0; a < 10; a++) { gui_rank[a].SetHelp("rank"); }
			for (int a = 0; a < 100; a++) { gui_skill[a].SetHelp("skill"); }

			gui_mp.isヘルプ表示 = true;
			gui_gold.isヘルプ表示 = true;
			for (int a = 0; a < 4; a++) { タブ[a].isヘルプ表示 = true; }
			for (int a = 0; a < 4; a++) { gui_mlv[a].isヘルプ表示 = true; }

			gui_mp.is固定 = true;
			gui_gold.is固定 = true;
			for (int a = 0; a < 4; a++) { タブ[a].is固定 = true; }
			for (int a = 0; a < 4; a++) { gui_mlv[a].is固定 = true; }


			GUI_Init();
			Tub_Change();
		}

		void GUI_Init()
		{
			タブ[0].位置 = { LV(0) ,         LV(1) ,LV(2) ,LV(3) };
			タブ[1].位置 = { LV(0) + LV(4)  ,LV(1) ,LV(2) ,LV(3) };
			タブ[2].位置 = { LV(0) + LV(4) * 2,LV(1) ,LV(2) ,LV(3) };
			タブ[3].位置 = { LV(0) + LV(4) * 3,LV(1) ,LV(2) ,LV(3) };

			for (auto&it : タブ)
			{
				it.文字オフセット = -18;
			}

			gui_mp.位置 = { LV(5),LV(6),LV(7),LV(8) };
			gui_gold.位置 = { LV(5),LV(9),LV(7),LV(10) };
			gui_mlv[0].位置 = { LV(5),LV(11),LV(12),LV(13) };
			gui_mlv[1].位置 = { LV(5)+LV(14),LV(11),LV(12),LV(13) };
			gui_mlv[2].位置 = { LV(5) + LV(14)*2,LV(11),LV(12),LV(13) };
			gui_mlv[3].位置 = { LV(5) + LV(14)*3,LV(11),LV(12),LV(13) };

		}

		void Tub_Change()
		{
			int n = 0;
			int r = -1;
			int x = LV(20);
			int y = LV(21);

			for (int a = 0; a < 10; a++)
			{
				gui_rank[a].ランク = a + 1;
				gui_rank[a].位置.x = -1000;
			}

			for (int a = 0; a < 100; a++)
			{
				gui_skill[a].位置.x = -1000;
			}


			for (auto& it : Management::managements)
			{
				if ((int)it.系統 == 現在タブ)
				{
					if (it.Lv != r)
					{
						if (r != -1) { y += LV(25); }
						r = it.Lv;
						gui_rank[r].位置 = { LV(20) , y , LV(26),LV(27) };
						y += LV(28);
						x = LV(20);
					}

					if (x >= LV(20) + LV(24) * 6)
					{
						x = LV(20);
						y += LV(25);
					}

					gui_skill[n].参照戦術 = &it;
					gui_skill[n].位置 = { x , y , LV(22),LV(23) };
					x += LV(24);

					n++;
				}
			}

			戦術数 = n;
			縦内部幅 = y + 50 + 固定縦;
		}


		void 派生Draw()
		{			
			GUI_Init();

			for (auto&it : タブ)
			{
				it.Draw();
			}
			MSystem::DrawWindow({LV(0),LV(1)+45},282,700, 17, 0);

			//固定描画
			gui_mp.Draw();
			gui_gold.Draw();
			for (auto &it : gui_mlv)
			{
				it.Draw();
			}


			//スクロールする
			描画範囲(true);

			for (auto &it : gui_rank)
			{
				it.Draw();
			}

			for (int a = 0; a < 戦術数; a++)
			{
				gui_skill[a].Draw();
			}
		}

		bool 派生操作()
		{
			int tubcheck = 現在タブ;

			for (auto& it : タブ)
			{
				it.操作チェック(座標.x, 座標.y + タイトル枠高さ);
			}

			for (auto& it : gui_skill)
			{
				if (Input::mouse.y - 座標.y - タイトル枠高さ < 固定縦){break;}

				it.操作チェック(相対座標.x, 相対座標.y);
			}


			if (tubcheck != 現在タブ)
			{
				Tub_Change();
			}

			return false;
		}
	};

	#undef LV
	#undef LV2
	#undef LV4
}