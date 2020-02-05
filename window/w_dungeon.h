//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[1][a]

	/*ダンジョン一覧ウィンドウ*/
	class W_Dungeon : public WindowBox
	{
	private:
		class GUI_Dun : public GUI_Object
		{
		public:
			Dungeon* 参照先;

			void Draw派生(double px, double py)
			{
				MSystem::DrawBoxBold({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::White, 0, Color::Black);
				MIcon::ダンジョン[参照先->種類].DrawRotate({ px + LV(14),py + LV(15) },1,0);
				MFont::BArial小.DrawBold({ px + LV(16), py + LV(17) }, Color::White, Color::Black, { (int)(参照先->探索率[Guild::P->id]*100) , "%"}, true);
				MFont::BArial小.DrawBold({ px + LV(18), py + LV(19) }, Color::White, Color::Black, { "Lv",参照先->Lv }, false);
			}

			void Click(double px, double py)
			{
				//ダンジョンを掴む
				W_Drag_Drop::ダンジョン = 参照先;
			}

			void Info派生(Point 座標) override
			{
				InfoDungeon(参照先, 座標);
			}

		};

	public:
		std::vector<GUI_Tab> タブ;
		GUI_Dun ダンジョン[50];//とりあえず要素数50

		int 現在タブ = 0;


		void init()
		{
			種類 = WindowType::Dungeon;
			名前 = "ダンジョン";
			略記 = "迷宮";
			アイコン = IconType::迷宮;
			横幅 = 320;
			縦幅 = 300;
			最小縦 = 200;
			最大縦 = 600;
			縦内部幅 = 600;//変動する
			固定縦 = 50;
			スクロール位置 = 0;

			ヘルプメッセージ = "発見済みダンジョン\n";
			ヘルプ横幅 = 200;
			ヘルプ縦幅 = 100;

			タブ.emplace_back(現在タブ, 0, IconType::星, "R1");
			タブ.emplace_back(現在タブ, 1, IconType::星, "R2");
			タブ.emplace_back(現在タブ, 2, IconType::星, "R3");
			タブ.emplace_back(現在タブ, 3, IconType::星, "R4");
			タブ.emplace_back(現在タブ, 4, IconType::星, "R5");

			タブ[0].SetHelp("rank1");
			タブ[1].SetHelp("rank2");
			タブ[2].SetHelp("rank3");
			タブ[3].SetHelp("rank4");
			タブ[4].SetHelp("rank5");

			for (int a = 0; a < 50; a++)
			{
				gui_objects.push_back(&ダンジョン[a]);
			}

			for (auto& it : タブ)
			{
				gui_objects.push_back(&it);
			}

		}

		void GUI_Init()
		{
			タブ[0].位置 = { LV(0) ,         LV(1) ,LV(2) ,LV(3) };
			タブ[1].位置 = { LV(0) + LV(4)  ,LV(1) ,LV(2) ,LV(3) };
			タブ[2].位置 = { LV(0) + LV(4) * 2,LV(1) ,LV(2) ,LV(3) };
			タブ[3].位置 = { LV(0) + LV(4) * 3,LV(1) ,LV(2) ,LV(3) };
			タブ[4].位置 = { LV(0) + LV(4) * 4,LV(1) ,LV(2) ,LV(3) };

			for (int a = 0; a < 50; a++)
			{
				ダンジョン[a].位置 = { LV(9) + a % 6 * LV(13) ,LV(10) + a / 6 * LV(13) ,LV(11),LV(12) };
			}


			for (int a = 0; a < 50; a++)
			{
				ダンジョン[a].参照先 = nullptr;
				ダンジョン[a].isヘルプ表示 = false;
			}
			
			int n = 0;

			for (auto& it : Dungeon::data)
			{
				if (it.is発見[0] && it.ランク == 現在タブ)
				{
					ダンジョン[n].参照先 = &it;
					ダンジョン[n].isヘルプ表示 = true;
					n++;
				}
			}
		}

		void 派生Draw()
		{
			int xx = LV(0);
			int yy = LV(1);
			int ww = LV(2);
			int hh = LV(3);
			int fno = 17;


			GUI_Init();

			//タブ部分
			for (auto& it : タブ)
			{
				it.Draw();
			}

			MSystem::DrawWindow({ LV(5) , LV(6) } ,LV(7) , LV(8), 12);

			//スクロールする
			描画範囲(true);
			for (auto& it : ダンジョン)
			{
				if (it.参照先 == nullptr) { break; }
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

				if (it.参照先 == nullptr) { break; }
				it.操作チェック(相対座標.x, 相対座標.y);
			}


			return false;
		}
	};
#undef LV
#undef LV2
#undef LV4
}