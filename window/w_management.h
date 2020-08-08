//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	//LayoutValue
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
				double rate = (double)Guild::P->投資経験値[部門] / Management::必要経験値[Guild::P->投資Lv[部門]];

				MSystem::DrawBar({ px,py }, (int)位置.GetW(), (int)位置.GetH(), rate, 1, Color::Blue, Color::White, Color::White, true);

				MFont::SSize.DrawBold({ px + Lp(30) ,py + Lp(31) }, Color::White, Color::Black, { "Lv",Guild::P->投資Lv[部門] });
			}
		};

		class GUI_Gold : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//選択戦術の資金消費を表示、不足している場合赤色
				MSystem::DrawWindow({ px ,py }, 位置.GetW(), 位置.GetH(), 11);

				//現在の資金
				MIcon::アイコン[IconType::資金].Draw({ px + Lp(34) , py + Lp(35) });
				MFont::BMSize.DrawBold({ px + Lp(32) ,py + Lp(33) }, Color::White, Color::Black, { (long long)Guild::P->資金 , " G" }, true);
				//消費する資金
				if (W_Drag::Over戦術 != nullptr)
				{
					Color fc = { 255,128,128 };
					if (W_Drag::Over戦術->消費資金 <= Guild::P->資金) { fc = Color(128,255,128); }
					MFont::BMSize.DrawBold({ px + Lp(36) ,py + Lp(37) }, fc, Color::Black, { "- " ,W_Drag::Over戦術->消費資金 , " G" }, true);
					W_Drag::Over戦術 = nullptr;
				}
				else if (Guild::P->選択戦術 != MSkillType::COUNT )
				{
					Color fc = {255,128,128};
					//if (Guild::P->選択戦術->消費資金 > Guild::P->資金) { fc = Color::Red; }
					MFont::BMSize.DrawBold({ px + Lp(36) ,py + Lp(37) }, fc, Color::Black, {"- " , Management::data[(int)Guild::P->選択戦術].消費資金 , " G"}, true);
				}

			}
		};
		class GUI_Rank : public GUI_Object
		{
		public:
			int ランク = 0;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px ,py }, 位置.GetW(), 位置.GetH(), 11);

				MFont::BMSize.DrawBold({ px + Lp(41),py + Lp(42) }, Color::White, Color::Black, { "Lv " , ランク });

			}
		};
		class GUI_Skill : public GUI_Object
		{
		public:
			Management* 参照戦術;
			int クリック時間 = 0;

			void Draw派生(double px, double py)
			{
				Color bc = Color::Black;
				bool can使用 = 参照戦術->can使用 && (参照戦術->消費資金 <= Guild::P->資金);
				bool isLv = (参照戦術->Lv <= Guild::P->投資Lv[参照戦術->系統]);
				bool is選択中 = (Guild::P->選択戦術 == 参照戦術->MID);

				int 枠No = 1;
				int 凹凸 = 0;
				if (参照戦術->is永続 && 参照戦術->使用回数 > 0)
				{
					//使用済み、永続
					枠No = 5;
				}
				else if (!isLv)
				{
					//Lv不足は灰色
					枠No = 15;
				}
				else if (is選択中 || クリック時間 > 0)
				{
					//選択中は凹み
					枠No = 4;
					凹凸 = -2;
				}
				else if (can使用)
				{
					//使用可能で盛り上がり
					枠No = 1;
					凹凸 = 2;
				}
				else
				{
					//資金不足
					枠No = 3;
				}

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(),枠No,凹凸);
				MIcon::アイコン[参照戦術->アイコン].DrawRotate({px + (int)位置.GetW()/2 - 凹凸,py + (int)位置.GetH()/2 - 凹凸 },2,0);

				クリック時間--;

			}
			void Click(double px, double py)
			{
				//お金足りてたら使用、不足してたら予約状態にする
				if (!参照戦術->can使用)
				{
					return;
				}


				if (Guild::P->選択戦術 != 参照戦術->MID)
				{
					Guild::P->選択戦術 = 参照戦術->MID;
					if (Guild::P->資金 >= 参照戦術->消費資金)
					{
						MSound::効果音[SE::投資実行].Play();
					} else {
						MSound::効果音[SE::投資予約].Play();
					}
				} else {
					Guild::P->選択戦術 = MSkillType::COUNT;
					MSound::効果音[SE::投資解除].Play();
				}

				クリック時間 = 5;
			}

			void Info派生(Point 座標) override
			{
				InfoManagement(参照戦術, 座標);
			}

		};

	public:
		std::vector<GUI_Tab> タブ;
		GUI_Gold gui_gold;//消費資金
		GUI_MLv gui_mlv[4];//部門Lpと経験値バー
		GUI_Frame 枠;

		GUI_Rank gui_rank[10];//ランク毎の区切り-10個？
		GUI_Skill gui_skill[100];//各種戦術アイコン、とりあえず最大100

		//消費資金

		int 現在タブ = 0;
		int 戦術数 = 0;

		void Init()
		{
			gui_objects.clear();
			種類 = WindowType::Management;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::戦略;
			横幅 = 320;
			縦幅 = 300;
			最小縦 = 200;
			最大縦 = 600;
			縦内部幅 = 600;//変動する
			固定縦 = 85;
			スクロール位置 = 0;

			タブ.emplace_back(現在タブ, 0, IconType::情報, "");//経営
			タブ.emplace_back(現在タブ, 1, IconType::求人, "");//人事
			タブ.emplace_back(現在タブ, 2, IconType::製造, "");//製造
			タブ.emplace_back(現在タブ, 3, IconType::迷宮, "");//探索

			for (int a = 0; a < 4; a++)
			{
				タブ[a].SetHelp(TX::Manage_タブヘルプ[a]);
			}

			gui_mlv[0].部門 = ManagementType::経営;
			gui_mlv[1].部門 = ManagementType::人事;
			gui_mlv[2].部門 = ManagementType::製造;
			gui_mlv[3].部門 = ManagementType::探索;

			gui_objects.push_back(&gui_gold);
			for (int a = 0; a < 4; a++) { gui_objects.push_back(&タブ[a]); }
			for (int a = 0; a < 4; a++) { gui_objects.push_back(&gui_mlv[a]); }
			for (int a = 0; a < 10; a++) { gui_objects.push_back(&gui_rank[a]); }
			for (int a = 0; a < 100; a++) { gui_objects.push_back(&gui_skill[a]); }
			gui_objects.push_back(&枠);

			SetCSVPage(0);

			gui_gold.SetHelp( TX::Manage_お金 );

			gui_gold.isヘルプ表示 = true;
			for (int a = 0; a < 4; a++) { タブ[a].isヘルプ表示 = true; }
			for (int a = 0; a < 4; a++) { gui_mlv[a].isヘルプ表示 = true; }

			gui_gold.is固定 = true;
			for (int a = 0; a < 4; a++) { タブ[a].is固定 = true; }
			for (int a = 0; a < 4; a++) { gui_mlv[a].is固定 = true; }

			GUI_Update();
			Tub_Change();
		}

		void GUI_Update()
		{
			タブ[0].位置 = { Lp(0) ,         Lp(1) ,Lp(2) ,Lp(3) };
			タブ[1].位置 = { Lp(0) + Lp(4)  ,Lp(1) ,Lp(2) ,Lp(3) };
			タブ[2].位置 = { Lp(0) + Lp(4) * 2,Lp(1) ,Lp(2) ,Lp(3) };
			タブ[3].位置 = { Lp(0) + Lp(4) * 3,Lp(1) ,Lp(2) ,Lp(3) };

			for (auto& it : タブ)
			{
				it.文字オフセット = -18;
			}

			枠.位置 = { Lp(0),Lp(1) + 45 , 282, 700 };
			枠.枠No = 12;

			gui_gold.位置 = { Lp(5),Lp(9),Lp(7),Lp(10) };
			gui_mlv[0].位置 = { Lp(5),Lp(11),Lp(12),Lp(13) };
			gui_mlv[1].位置 = { Lp(5)+Lp(14),Lp(11),Lp(12),Lp(13) };
			gui_mlv[2].位置 = { Lp(5) + Lp(14)*2,Lp(11),Lp(12),Lp(13) };
			gui_mlv[3].位置 = { Lp(5) + Lp(14)*3,Lp(11),Lp(12),Lp(13) };
		}

		void Tub_Change()
		{
			int n = 0;
			int r = -1;
			int x = Lp(20);
			int y = Lp(21);

			for (int a = 0; a < 10; a++)
			{
				gui_rank[a].ランク = a + 1;
				gui_rank[a].位置.x = -1000;
			}

			for (int a = 0; a < 100; a++)
			{
				gui_skill[a].位置.x = -1000;
			}


			for (auto& it : Management::data)
			{
				if ((int)it.系統 == 現在タブ)
				{
					if (it.Lv != r)
					{
						if (r != -1) { y += Lp(25); }
						r = it.Lv;
						gui_rank[r-1].位置 = { Lp(20) , y , Lp(26),Lp(27) };
						y += Lp(28);
						x = Lp(20);
					}

					if (x >= Lp(20) + Lp(24) * 6)
					{
						x = Lp(20);
						y += Lp(25);
					}

					gui_skill[n].参照戦術 = &it;
					gui_skill[n].位置 = { x , y , Lp(22),Lp(23) };
					x += Lp(24);

					n++;
				}
			}

			戦術数 = n;
			縦内部幅 = y + 50 + 固定縦;
		}

		void 派生Draw()
		{			
			GUI_Update();

			//固定描画
			for (auto&it : タブ)
			{
				it.Draw();
			}

			枠.Draw();


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
}