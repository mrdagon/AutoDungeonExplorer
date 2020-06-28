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
		class GUI_メンバーゾーン : public GUI_Object
		{
		public:
			CraftType 部門;
			W_Factory* 親ウィンドウ;

			void Draw派生(double px, double py)
			{
				//todo-完成時のポップアップなどの演出、初製造装備の表示変更

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				MSystem::DrawWindow({ px+LV(23),py+LV(24) }, LV(25), LV(26), LV(41));
				//作業台
				MSystem::クラフト台[部門].DrawRotate({ px + LV(15) ,py + LV(16) }, 2, 0);

				//技術レベルとEXP
				double rate = Guild::P->製造経験[部門] / Guild::P->必要技術経験(部門);
				MSystem::DrawBar({ px + LV(19),py + LV(20) }, LV(21), LV(22), rate, 1, Color::Blue, Color::White, Color::White, true);
				MFont::BMSize.DrawBold({ px + LV(17) ,py + LV(18) }, Color::White, Color::Black, { "Lv" , Guild::P->製造Lv[部門] });

				//製造アイコンと製造進行度合い
				//craft種アイコン
				int id = Guild::P->完成品[部門];
				MSystem::DrawBox({ px + LV(29) , py + LV(30) }, LV(31), LV(32), Color::White);
				if (id >= 0)
				{
					MIcon::アイテム[Item::data[id].見た目].Draw({ px + LV(27) , py + LV(28) });
					MFont::BMSize.DrawBold({ px + LV(42) , py + LV(43) }, Color::Yellow, Color::Black, {Item::data[id].ランク},true);
				}
				
				//製造進捗ゲージ
				if (Guild::P->必要製造力[部門] > 0)
				{
					rate = Guild::P->製造進行度[部門] / Guild::P->必要製造力[部門];
				} else {
					rate = 0;
				}

				Color ca, cb;

				if (Guild::P->製造ゲージ色[部門])
				{
					ca.SetColor(255, 128, 128);
					cb.SetColor(64, 64, 255);
				} else {
					cb.SetColor(255, 128, 128);
					ca.SetColor(64, 64, 255);
				}

				MSystem::DrawCircleBar({ px + LV(29) , py + LV(30) , LV(31) , LV(32) }, rate, ca , cb , 4 , 4);
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
					W_Drag_Drop::メンバー移動(親ウィンドウ, nullptr, 0,部門);
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
				//todo-製造中はアニメーションさせる
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				if (Game::is仕事中 == true)
				{
					//製造中
					int n = Game::アニメーション時間 / 10  %  4 ;
					if (n == 3) { n = 1; }
					n += 6;

					MUnit::ユニット[ギルメン->見た目][n]->DrawRotate({ px + LV(35) , py + LV(36) }, 2, 0);
				} else {
					//休み中
					MUnit::ユニット[ギルメン->見た目][1]->DrawRotate({ px + LV(35) , py + LV(36) }, 2, 0);
				}

				MFont::BSSize.DrawBold({ px + LV(37) ,py + LV(38) }, Color::White, Color::Black, ギルメン->製造力 , true);
				MIcon::アイコン[IconType::製造力].Draw({ px + LV(39) , py + LV(40) });
			}

			void Click(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }
				//ギルメン掴む
				W_Drag_Drop::ギルメン = ギルメン;
				W_Drag_Drop::ウィンドウ = 親ウィンドウ;
				W_Drag_Drop::並びID = 並びID;
				MSound::効果音[SE::ドラッグ].Play();
			}

			void Drop(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }

				//ギルメン入れ替え
				if (W_Drag_Drop::ギルメン != nullptr)
				{
					W_Drag_Drop::メンバー移動(親ウィンドウ, ギルメン, 並びID,ギルメン->製造配置);
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
			gui_objects.reserve(256);

			種類 = WindowType::Factory;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::製造;
			横幅 = 344;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				メンバーゾーン[CraftType(a)].部門 = CraftType(a);
				メンバーゾーン[CraftType(a)].SetHelp(TX::Factory_部門説明[CraftType(a)]);
			}

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
				}
			}

			//座標初期化
			int n = 0;
			int y = 0;
			const int 列数 = 6;
			int 段数 = 0;

			横幅 = LV(0);

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				CraftType t = CraftType(b);
				段数 = (int)製造メンバー[t].size() / 列数 + 1;
				if (段数 < 2) { 段数 = 2; }

				//人数に応じてメンバーゾーンのサイズは変動
				メンバーゾーン[t].位置 = { LV(1) , LV(2)+y , LV(0) - LV(3) , LV(4) + 段数 * LV(5) };
				
				for (int a = 0; a < 製造メンバー[t].size(); a++)
				{
					製造メンバー[t][a].位置 = { LV(1) + LV(8) + LV(9) * (a % 列数) , LV(2) + LV(10) + LV(11) * (a / 列数) + y ,LV(12),LV(13) };
				}

				y += LV(4) + LV(7) + 段数 * LV(6);
			}

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				CraftType t = (CraftType)b;

				for (int a = 0; a < 製造メンバー[t].size(); a++)
				{
					gui_objects.push_back(&製造メンバー[t][a]);
				}
			}

			gui_objects.push_back(&メンバーゾーン[CraftType::鍛造]);
			gui_objects.push_back(&メンバーゾーン[CraftType::裁縫]);
			gui_objects.push_back(&メンバーゾーン[CraftType::魔術]);
			gui_objects.push_back(&メンバーゾーン[CraftType::木工]);


			//
			縦内部幅 = y + LV(14);
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