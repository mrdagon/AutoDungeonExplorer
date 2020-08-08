//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class W_Dungeon : public WindowBox
	{
	private:
		class GUI_Dun : public GUI_Object
		{
		public:
			Dungeon* 参照 = nullptr;
			W_Dungeon* 親ウィンドウ = nullptr;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				参照->Img->DrawRotate({ px + Lp(15),py + Lp(16) },1,0);
				MFont::BSSize.DrawBold({ px + Lp(17), py + Lp(18) }, Color::White, Color::Black, { (int)(参照->探索率*100) , "%"}, true);
				MFont::BSSize.DrawBold({ px + Lp(19), py + Lp(20) }, Color::White, Color::Black, { "Lv",参照->Lv }, false);

				//ボス
				参照->ボスモンスター[0].Img[0][1]->DrawRotate({ px + Lp(21), py + Lp(22) }, 3, 0);
				MFont::BSSize.DrawBold({ px + Lp(23), py + Lp(24) }, Color::White, Color::Black, "Boss");

				//ザコ
				for (int a = 0; a < (int)参照->雑魚モンスター.size() ; a++)
				{
					参照->雑魚モンスター[a].Img[0][1]->DrawRotate({ px + Lp(25) + Lp(26) * a, py + Lp(27) }, 2, 0);
				}
			}

			void Click(double px, double py)
			{
				//ダンジョンを掴む
				W_Drag::ダンジョン = 参照;
				MSound::効果音[SE::ドラッグ].Play();
			}

			void Info派生(Point 座標) override
			{
				double px = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;

				if ( px > Lp(21) - 20 && px < Lp(21) + 20)
				{
					//ボスモンスターヘルプ
					InfoMonster( &参照->ボスモンスター[0], 参照->Lv, true, 座標);
					return;
				}

				for (int a = 0; a < (int)参照->雑魚モンスター.size(); a++)
				{
					if (px > Lp(25) + Lp(26) * a - 20 && px < Lp(25) + Lp(26) * a + 20)
					{
						//ザコモンスターヘルプ
						InfoMonster( &参照->雑魚モンスター[a],参照->Lv,false,座標);
						
						return;
					}
				}

				//モンスター以外
				InfoDungeon(参照, 座標);
			}

		};

	public:
		std::vector<GUI_Tab> タブ;
		GUI_Dun ダンジョン[50];//とりあえず要素数50
		GUI_Frame 枠;

		int 現在タブ = 0;


		void Init()
		{
			gui_objects.clear();
			タブ.clear();

			種類 = WindowType::Dungeon;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::迷宮;
			横幅 = 320;
			縦幅 = 300;
			最小縦 = 200;
			最大縦 = 600;
			縦内部幅 = 600;//変動する
			固定縦 = 50;
			スクロール位置 = 0;

			for (int a = 0; a < 5; a++)
			{
				タブ.emplace_back(現在タブ, a, IconType::BGM, TX::Dungeon_タブ名[a]);
				タブ[a].SetHelp( TX::Dungeon_タブヘルプ[a]);
			}
			タブ[0].アイコン = IconType::森;
			タブ[1].アイコン = IconType::洞窟;
			タブ[2].アイコン = IconType::砂漠;
			タブ[3].アイコン = IconType::滝;
			タブ[4].アイコン = IconType::城;

			for (int a = 0; a < 50; a++)
			{
				ダンジョン[a].親ウィンドウ = this;
				gui_objects.push_back(&ダンジョン[a]);
			}

			for (auto& it : タブ)
			{
				gui_objects.push_back(&it);
			}

			gui_objects.push_back(&枠);

			SetCSVPage(1);
		}

		void GUI_Update()
		{
			枠.位置 = { Lp(5) , Lp(6) ,Lp(7) , Lp(8) };
			枠.枠No = 12;

			タブ[0].位置 = { Lp(0) ,         Lp(1) ,Lp(2) ,Lp(3) };
			タブ[1].位置 = { Lp(0) + Lp(4)  ,Lp(1) ,Lp(2) ,Lp(3) };
			タブ[2].位置 = { Lp(0) + Lp(4) * 2,Lp(1) ,Lp(2) ,Lp(3) };
			タブ[3].位置 = { Lp(0) + Lp(4) * 3,Lp(1) ,Lp(2) ,Lp(3) };
			タブ[4].位置 = { Lp(0) + Lp(4) * 4,Lp(1) ,Lp(2) ,Lp(3) };

			for (int a = 0; a < 50; a++)
			{
				ダンジョン[a].位置 = { Lp(9) ,Lp(10) + a * Lp(14) ,Lp(11),Lp(12) };
			}

			for (int a = 0; a < 50; a++)
			{
				ダンジョン[a].参照 = nullptr;
				ダンジョン[a].isヘルプ表示 = false;
			}
			
			int n = 0;

			for (auto& it : Dungeon::data)
			{
				if (it.is発見 && it.層 == 現在タブ)
				{
					ダンジョン[n].参照 = &it;
					ダンジョン[n].isヘルプ表示 = true;
					n++;
					if (n == 50) { break; }
				}
			}
		}

		void 派生Draw()
		{
			GUI_Update();

			//タブ部分
			for (auto& it : タブ)
			{
				it.Draw();
			}

			枠.Draw();

			//スクロールする
			描画範囲(true);
			for (auto& it : ダンジョン)
			{
				if (it.参照 == nullptr) { break; }
				it.Draw();
			}

		}

		bool 派生操作()
		{
			for (auto& it : タブ)
			{
				it.操作チェック(座標.x, 座標.y + タイトル枠高さ);
			}
			for (auto& it : ダンジョン)
			{
				if (Input::mouse.y - 座標.y - タイトル枠高さ < 固定縦)
				{
					break;
				}

				if (it.参照 == nullptr) { break; }
				it.操作チェック(相対座標.x, 相対座標.y);
			}

			return false;
		}
	};
}