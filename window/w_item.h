//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[7][a]



	/*アイテムウィンドウ*/
	class W_Item: public WindowBox
	{
	private:
		class GUI_Item : public GUI_Object
		{
		public:
			int id;

			void Draw派生(double px, double py)
			{
				const int w = (int)位置.GetW();
				const int h = (int)位置.GetH();
				const int zaiko = Guild::P->装備所持数[id];

				//外枠
				MSystem::DrawWindow({ px,py }, w, h, 1);
				//MSystem::DrawBoxBold({ px,py }, w, h, Color::White, 0, Color::Black);
				//アイコン
				MIcon::アイテム[Item::data[id].見た目].Draw({ px + LV(11),py+LV(12) });
				//在庫数
				//MFont::Arial小.DrawBold({ px + LV(19) ,py + LV(20) }, Color::White, Color::Black, { "x" }, true);
				MFont::BArial中.DrawBold({ px + LV(13) ,py+LV(14) }, Color::White, Color::Black, { "x" , zaiko }, true);
				//ランク表示
				//MIcon::アイコン[IconType::星].DrawRotate({ px + LV(15) ,py + LV(16) }, 1, 0);
				//MFont::Arial小.DrawBold({ px + LV(15) ,py + LV(16) }, Color::White, Color::Black, { "Lv " }, true);
				MFont::BArial小.DrawBold({ px + LV(17) ,py + LV(18) }, Color::White, Color::Black, { "Lv" , Item::data[id].ランク+1 }, true);
				//MFont::BArial小.DrawBold({ px + LV(17) ,py + LV(18) }, {255,64,64}, Color::Black, { Item::data[id].ランク+1 }, true);
				//new表示

			}
			void Click(double px, double py)
			{
				//掴む
				if (Guild::P->装備所持数[id] > 0)
				{
						W_Drag_Drop::アイテム = id;
				}
			}

			void Info派生(Point 座標) override
			{
				InfoItem(id, 座標);
			}

		};
	public:
		std::vector<GUI_Tab> タブ;//レシピ9種 + 全て
		GUI_Item アイテム[CV::装備種];

		int 装備数 = 0;
		int 現在タブ = 0;

		void init()
		{
			種類 = WindowType::Item;
			名前 = "装備品";
			略記 = "装備";
			アイコン = IconType::装備;
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			固定縦 = 43;
			スクロール位置 = 0;

			タブ.emplace_back(現在タブ, 0, IconType::星, "");
			タブ.emplace_back(現在タブ, 1, IconType::星, "");
			タブ.emplace_back(現在タブ, 2, IconType::星, "");
			タブ.emplace_back(現在タブ, 3, IconType::星, "");
			タブ.emplace_back(現在タブ, 4, IconType::星, "");
			タブ.emplace_back(現在タブ, 5, IconType::星, "");
			タブ.emplace_back(現在タブ, 6, IconType::星, "");
			タブ.emplace_back(現在タブ, 7, IconType::星, "");
			タブ.emplace_back(現在タブ, 8, IconType::星, "");
			タブ.emplace_back(現在タブ, 9, IconType::星, "");

			タブ[0].SetHelp("1");
			タブ[1].SetHelp("2");
			タブ[2].SetHelp("3");
			タブ[3].SetHelp("4");
			タブ[4].SetHelp("5");
			タブ[5].SetHelp("6");
			タブ[6].SetHelp("7");
			タブ[7].SetHelp("8");
			タブ[8].SetHelp("9");
			タブ[9].SetHelp("A");

			タブ[1].スキルアイコン = SkillType::剣;
			タブ[2].スキルアイコン = SkillType::槌;
			タブ[3].スキルアイコン = SkillType::槍;
			タブ[4].スキルアイコン = SkillType::弓;
			タブ[5].スキルアイコン = SkillType::魔杖;
			タブ[6].スキルアイコン = SkillType::神杖;
			タブ[7].スキルアイコン = SkillType::鎧;
			タブ[8].スキルアイコン = SkillType::革鎧;
			タブ[9].スキルアイコン = SkillType::ローブ;

			for (auto&it : タブ)
			{
				it.アイコンオフセット = 5;
				gui_objects.push_back(&it);
			}
			
			for (auto&it : アイテム)
			{
				gui_objects.push_back(&it);
			}

		}

		void GUI_Init()
		{
			for (int a = 0; a < 10; a++)
			{
				if (a == 0)
				{
					タブ[a].位置 = { LV(0) ,LV(1) ,LV(2) + 3,LV(3) };
				} else {
					タブ[a].位置 = { LV(0) + LV(4) * a + 3,LV(1) ,LV(2) ,LV(3) };
				}
			}

			int cnt = 0;
			const int per_line = 7;
			for (auto&it : アイテム)
			{
				it.位置 = { LV(5) + LV(9) *(cnt%per_line),LV(6) + LV(10) * (cnt /per_line),LV(7),LV(8) };
				cnt++;
			}

			Tub_Change();
		}

		void Tub_Change()
		{
			装備数 = 0;

			for (int a = 0; a < CV::装備種; a++)
			{
				if (Guild::P->is装備開発[a] == false) { continue; }

				//全タブかタブ種とあってたら表示
				if (現在タブ == 0 || int(Item::data[a].種類)/2+1 == 現在タブ)
				{
					アイテム[装備数].id = a;
					アイテム[装備数].isヘルプ表示 = true;
					装備数++;
				}
			}

			for (int a = 装備数; a < CV::装備種; a++)
			{
				アイテム[a].isヘルプ表示 = false;
			}

		}

		void 派生Draw()
		{
			GUI_Init();

			for (auto&it : タブ)
			{
				it.Draw();
			}

			MSystem::DrawWindow({ LV(0),LV(1) + 35 }, 292, 700, 12);

			//スクロールする
			描画範囲(true);
			for (int a=0;a<装備数;a++)
			{
				アイテム[a].Draw();
			}
		}

		bool 派生操作()
		{
			int tubcheck = 現在タブ;

			for (auto&it : タブ)
			{
				it.操作チェック(座標.x, 座標.y + タイトル枠高さ);
			}

			for (int a = 0; a < 装備数; a++)
			{
				if (Input::mouse.y - 座標.y - タイトル枠高さ < 固定縦)
				{
					break;
				}

				アイテム[a].操作チェック(相対座標.x, 相対座標.y);
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