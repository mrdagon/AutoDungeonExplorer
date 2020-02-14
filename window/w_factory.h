//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[13][a]



	/*パーティウィンドウ*/
	class W_Factory: public WindowBox
	{
	private:
		class GUI_割当ゾーン : public GUI_Object
		{
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 15);
			}
		};

		class GUI_製造割当 : public GUI_Object
		{
		public:
			CraftType id;
			Recipe* レシピ;

			void Set(CraftType id)
			{
				this->id = id;
				this->レシピ = &Recipe::data[id];
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				//craft種アイコン
				//MSystem::DrawSkill(レシピ->種類, { px + LV(31) , py + LV(32) }, { 128,255,128 });
				Drawing::Rect({ px + LV(31), py + LV(32) ,27,27 }, Color::White);
				Screen::SetBright(Color::Black);
				MIcon::スキル[レシピ->種類].Draw({ px + LV(31) , py + LV(32) });
				Screen::SetBright();

				//製造割当と矢印
				MIcon::アイコン[IconType::団員].Draw({ px + LV(45), py + LV(46) });
				MFont::BArial中.DrawBold({ px + LV(43) ,py + LV(44) }, Color::White, Color::Black, Guild::P->製造割当[id]);

				if (Game::is仕事中 == false)
				{
					MIcon::アイコン[IconType::三角].Draw({ px + LV(35),py + LV(37) });
					MIcon::アイコン[IconType::三角].Draw({ px + LV(36),py + LV(37) }, true);
				}
				//ダイア使用ON/OFF
				int total_c = 0;
				for (auto& it : Guild::P->製造割当)
				{
					total_c += it;
				}
				if (total_c == 0) { total_c = 1; }

				double 実製造 = std::round(Guild::P->合計製造力 * Guild::P->製造割当[id] / total_c);

				MIcon::アイコン[IconType::ハンマー].DrawRotate({ px + LV(33), py + LV(34) }, 1, 0);
				MFont::BArial小.DrawBold({ px + LV(47) ,py + LV(49) }, Color::White, Color::Black, 実製造,true);
				

				//製造進捗ゲージ
				double rate = Guild::P->製造進行度[id] / Guild::P->必要製造力;
				//50~53
				Point p1, p2, p3, p4 , p5;
				p1.SetPos(px + LV(50) , py + LV(52));
				p2.SetPos(px + LV(50) + LV(51) , py + LV(52));
				p3.SetPos(px + LV(50) + LV(51), py + LV(52) + LV(53));
				p4.SetPos(px + LV(50) , py + LV(52) + LV(53));
				p5 = p1;

				//裏色
				Drawing::Line( p1 , p2 , Color::Blue, 2);
				Drawing::Line( p2 , p3 , Color::Blue, 2);
				Drawing::Line( p3 , p4 , Color::Blue, 2);
				Drawing::Line( p4 , p1 , Color::Blue, 2);
				//表
				if (rate < 0.25)
				{
					p2.x = px + LV(50) + LV(51) * rate * 4;
					Drawing::Line(p1, p2, Color::Red, 2);				
				}
				else
				if (rate < 0.5)
				{
					p3.y = py + LV(52) + LV(53) * (rate-0.25) * 4;
					Drawing::Line(p1, p2, Color::Red, 2);
					Drawing::Line(p2, p3, Color::Red, 2);
				
				}
				else if (rate < 0.75)
				{
					p4.x = px + LV(50) + LV(51) * (0.75-rate) * 4;
					Drawing::Line(p1, p2, Color::Red, 2);
					Drawing::Line(p2, p3, Color::Red, 2);
					Drawing::Line(p3, p4, Color::Red, 2);
				}
				else
				{
					p5.y = py + LV(52) + LV(53) * (1.0 - rate) * 4;
					Drawing::Line(p1, p2, Color::Red, 2);
					Drawing::Line(p2, p3, Color::Red, 2);
					Drawing::Line(p3, p4, Color::Red, 2);
					Drawing::Line(p4, p5, Color::Red, 2);
				}


				//技術レベルと経験値
				rate = 0.5;
				MFont::BArial中.DrawBold({ px + LV(58) ,py + LV(59) }, Color::White, Color::Black, "Lv10");
				MSystem::DrawBar({ px + LV(54),py + LV(55) }, LV(56), LV(57), rate, 1, Color::Blue, Color::White, Color::White, true);

			}

			void Click(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }

				//製造割当の増減
				if (py > LV(37) && py < LV(37) + 20)
				{
					if (px > LV(35) - 5 && px < LV(35) + 15)
					{
						Guild::P->製造割当[id]--;
						if (Guild::P->製造割当[id] < 0) { Guild::P->製造割当[id] = 9; }
					}
					if (px > LV(36) - 5 && px < LV(36) + 15)
					{
						Guild::P->製造割当[id]++;
						if (Guild::P->製造割当[id] > 9) { Guild::P->製造割当[id] = 0; }
					}
				}
			}

			//Drop操作無し
		};

		class GUI_メンバーゾーン : public GUI_Object
		{
		public:
			W_Factory* 親ウィンドウ;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				//合計製造力
				MSystem::DrawBox({ px + LV(25) , py + LV(26) }, 70, 18, Color::White);
				MIcon::アイコン[IconType::ハンマー].Draw({ px + LV(27), py + LV(28) });
				MFont::Arial中.DrawBold({ px + LV(29) ,py + LV(30) }, Color::White, Color::Black, (int)Guild::P->合計製造力,true);
			}

			void Click(double px, double py)
			{
				//操作無し
			}

			void Drop(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }

				//ギルメン移動して最後に追加
				if (W_Drag_Drop::ギルメン != nullptr)
				{
					W_Drag_Drop::メンバー移動(親ウィンドウ, nullptr, 0);
					W_Drag_Drop::ギルメン = nullptr;
				}
			}
		};

		class GUI_製造メンバー : public GUI_Object
		{
		public:
			Warker* ギルメン;
			W_Factory* 親ウィンドウ;
			int 並びID;

			GUI_製造メンバー(Warker* ギルメン)
			{
				this->ギルメン = ギルメン;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawBox({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::White);
				MUnit::ユニット[ギルメン->見た目][1]->DrawRotate({ px + LV(19) , py + LV(20) }, 2, 0);
				MFont::BArial小.DrawBold({ px + LV(21) ,py + LV(22) }, Color::White, Color::Black, ギルメン->製造力 , true);
				MIcon::アイコン[IconType::ハンマー].Draw({ px + LV(23) , py + LV(24) });
				//MFont::BArial中.DrawBold({ px + LV(60) ,py + LV(61) }, Color::White, Color::Black, ギルメン->Lv, true);
				//MFont::BArial小.DrawBold({ px + LV(62) ,py + LV(63) }, Color::White, Color::Black, "Lv", true);
			}

			void Click(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }
				//ギルメン掴む
				W_Drag_Drop::ギルメン = ギルメン;
				W_Drag_Drop::ウィンドウ = 親ウィンドウ;
				W_Drag_Drop::並びID = 並びID;
			}

			void Drop(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }

				//ギルメン入れ替え
				if (W_Drag_Drop::ギルメン != nullptr)
				{
					W_Drag_Drop::メンバー移動(親ウィンドウ, ギルメン, 並びID);
					W_Drag_Drop::ギルメン = nullptr;
				}
			}

			void Info派生(Point 座標) override
			{
				ヘルプ横幅 = DV::I[11][0];
				ヘルプ縦幅 = DV::I[11][1];
				InfoHunter(ギルメン, 座標);
			}
		};

	public:
		//生産割り当て、武器６系統、防具３系統
		GUI_割当ゾーン 割当ゾーン;
		std::vector<GUI_製造割当> 製造割当;

		GUI_メンバーゾーン メンバーゾーン;//製造メンバーの表示領域
		std::vector<GUI_製造メンバー> 製造メンバー;

		void init()
		{
			//名前 = "ギルド員/\\cff00ff仕事\\cffffff割当";
			gui_objects.reserve(256);

			種類 = WindowType::Factory;
			名前 = "製造";
			略記 = "製造";
			アイコン = IconType::ハンマー;
			横幅 = 344;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;

			製造割当.resize(9);

			製造割当[0].Set(CraftType::斬撃);
			製造割当[1].Set(CraftType::打撃);
			製造割当[2].Set(CraftType::刺突);
			製造割当[3].Set(CraftType::射撃);
			製造割当[4].Set(CraftType::魔術);
			製造割当[5].Set(CraftType::神秘);
			製造割当[6].Set(CraftType::STR鎧);
			製造割当[7].Set(CraftType::DEX鎧);
			製造割当[8].Set(CraftType::INT鎧);
		}

		void GUI_Init()
		{
			//オブジェクト初期化
			製造メンバー.clear();
			gui_objects.clear();

			メンバーゾーン.SetHelp("製造力と製造人員\nドラッグ＆ドロップで配置転換",80);
			メンバーゾーン.親ウィンドウ = this;

			for (int a = 0; a < Guild::P->製造メンバー.size(); a++)
			{
				if (Guild::P->製造メンバー[a] == nullptr) { break; }

				製造メンバー.emplace_back(Guild::P->製造メンバー[a]);
				製造メンバー[a].並びID = a;
				製造メンバー[a].親ウィンドウ = this;
			}


			for (int a = 0; a < 製造メンバー.size(); a++)
			{
				gui_objects.push_back(&製造メンバー[a]);
				製造メンバー[a].親ウィンドウ = this;
			}

			gui_objects.push_back(&メンバーゾーン);

			for (int a = 0; a < 製造割当.size(); a++)
			{
				gui_objects.push_back(&製造割当[a]);
			}
			
			gui_objects.push_back(&割当ゾーン);

			//座標初期化
			int n = 0;

			横幅 = LV(0);

			//割当ゾーン.位置 = { LV(1),LV(3),LV(2),LV(4) };

			メンバーゾーン.位置 = { LV(1) , LV(4) + LV(5) , LV(2) , LV(6) + ((int)製造メンバー.size()+7) / 7 * LV(7) };

			for (int a = 0; a < 製造割当.size(); a++)
			{
				製造割当[a].位置 = { LV(8) , LV(9) + LV(12) * a , LV(10) , LV(11) };
			}

			製造割当[0].位置 = { LV(8) , LV(9) , LV(10) , LV(11) };
			製造割当[1].位置 = { LV(8) + 100 , LV(9) , LV(10) , LV(11) };
			製造割当[2].位置 = { LV(8) , LV(9) + LV(12) * 1 , LV(10) , LV(11) };
			製造割当[3].位置 = { LV(8) + 100 , LV(9) + LV(12) * 1 , LV(10) , LV(11) };
			製造割当[4].位置 = { LV(8) , LV(9) + LV(12) * 2 , LV(10) , LV(11) };
			製造割当[5].位置 = { LV(8) + 100 , LV(9) + LV(12) * 2 , LV(10) , LV(11) };
			製造割当[6].位置 = { LV(8) + 100 *2, LV(9) + LV(12) * 0 , LV(10) , LV(11) };
			製造割当[7].位置 = { LV(8) + 100 * 2, LV(9) + LV(12) * 1 , LV(10) , LV(11) };
			製造割当[8].位置 = { LV(8) + 100 * 2, LV(9) + LV(12) * 2 , LV(10) , LV(11) };

			for (int a = 0; a < Guild::P->製造メンバー.size(); a++)
			{
				if (Guild::P->製造メンバー[a] == nullptr) { break; }
				n++;
				製造メンバー[a].位置 = { LV(1) + LV(13) + LV(14) * (a % 7) , LV(4) + LV(5) + LV(15) + LV(16) * (a / 7) ,LV(17),LV(18) };
			}

			縦内部幅 = 300 + (((int)製造メンバー.size() + 7) / 7 )* LV(16);
		}

		void 派生Draw()
		{
			GUI_Init();

			割当ゾーン.Draw();

			for (int a = 0; a < 製造割当.size(); a++)
			{
				製造割当[a].Draw();
			}

			メンバーゾーン.Draw();

			for (int a = 0; a < 製造メンバー.size(); a++)
			{
				製造メンバー[a].Draw();
			}
		}

		bool 派生操作()
		{
			for (int a = 0; a < 製造メンバー.size(); a++)
			{
				製造メンバー[a].操作チェック(相対座標.x, 相対座標.y);
			}

			メンバーゾーン.操作チェック(相対座標.x, 相対座標.y);

			for (int a = 0; a < 製造割当.size(); a++)
			{
				製造割当[a].操作チェック(相対座標.x, 相対座標.y);
			}

			return false;
		}
	};
#undef LV
#undef LV2
#undef LV4
}