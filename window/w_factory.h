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

		class GUI_メンバーゾーン : public GUI_Object
		{
		public:
			CraftType 部門;
			W_Factory* 親ウィンドウ;

			void Draw派生(double px, double py)
			{
				//Screen::SetDrawMode(Color(255, 255, 255, 128), BlendMode::Alpha);
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				//Screen::SetDrawMode();
				//合計製造力
				MSystem::DrawWindow({ px + LV(25) , py + LV(26) }, 70, 18, 11);
				MIcon::アイコン[IconType::ハンマー].Draw({ px + LV(27), py + LV(28) });
				//MFont::BArial中.DrawBold({ px + LV(29) ,py + LV(30) }, Color::White, Color::Black, (int)Guild::P->合計製造力,true);
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
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				MUnit::ユニット[ギルメン->見た目][1]->DrawRotate({ px + LV(19) , py + LV(20) }, 2, 0);
				MFont::BArial小.DrawBold({ px + LV(21) ,py + LV(22) }, Color::White, Color::Black, ギルメン->製造力 , true);
				MIcon::アイコン[IconType::ハンマー].Draw({ px + LV(23) , py + LV(24) });
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
		EnumArray<GUI_メンバーゾーン,CraftType> メンバーゾーン;//製造メンバーの表示領域

		EnumArray < std::vector<GUI_製造メンバー>, CraftType> 製造メンバー;

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
		}

		void GUI_Init()
		{
			//オブジェクト初期化
			for (auto& it : 製造メンバー)
			{
				it.clear();
			}
			//製造メンバー.clear();
			gui_objects.clear();

			for (auto& it : メンバーゾーン)
			{
				it.SetHelp("製造力と製造人員\nドラッグ＆ドロップで配置転換", 80);
				it.親ウィンドウ = this;
			}

			for (int b = 0; b < (int)CraftType::COUNT;b++)
			{
				CraftType t = (CraftType)b;

				for (int a = 0; a < Guild::P->製造メンバー[t].size(); a++)
				{
					if (Guild::P->製造メンバー[t][a] == nullptr) { break; }

					製造メンバー[t].emplace_back(Guild::P->製造メンバー[t][a]);
					製造メンバー[t][a].並びID = a;
					製造メンバー[t][a].親ウィンドウ = this;
					gui_objects.push_back(&製造メンバー[t][a]);
				}
			}

			gui_objects.push_back(&メンバーゾーン[CraftType::鍛造]);
			gui_objects.push_back(&メンバーゾーン[CraftType::裁縫]);
			gui_objects.push_back(&メンバーゾーン[CraftType::魔術]);
			gui_objects.push_back(&メンバーゾーン[CraftType::木工]);

			//座標初期化
			int n = 0;
			int y = 0;
			const int 列数 = 6;

			横幅 = LV(0);

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				CraftType t = CraftType(b);				
				//人数に応じてメンバーゾーンのサイズは変動
				メンバーゾーン[t].位置 = { LV(1) , LV(2)+y , LV(0) - LV(3) , LV(4) + ((int)製造メンバー[t].size() + 列数) / 列数 * LV(5) };
				
				for (int a = 0; a < 製造メンバー[t].size(); a++)
				{
					製造メンバー[t][a].位置 = { LV(1) + LV(8) + LV(9) * (a % 列数) , LV(2) + LV(10) + LV(11) * (a / 列数) + y ,LV(12),LV(13) };
				}

				y += LV(4) + LV(7) + ((int)製造メンバー[t].size() + 列数) / 列数 * LV(6);
			}

			//
			縦内部幅 = 300 + y + (((int)製造メンバー.size() + 7) / 7 )* LV(14);
		}

		void 派生Draw()
		{
			GUI_Init();


			for (auto& it : メンバーゾーン)
			{
				it.Draw();
			}


			for (auto& it : 製造メンバー)
			{
				for(int a = 0; a < it.size(); a++)
				{
					it[a].Draw();
				}	
			}
		}

		bool 派生操作()
		{
			return false;

			for ( auto& it : gui_objects )
			{
				it->操作チェック(相対座標.x, 相対座標.y);
			}
			return false;
		}
	};
#undef LV
#undef LV2
#undef LV4
}