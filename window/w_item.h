//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

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
				//アイコン
				//MIcon::アイテム[Item::data[id].見た目].Draw({ px + Lp(11),py+Lp(12) });
				//在庫数
				MFont::BMSize.DrawBold({ px + Lp(13) ,py+Lp(14) }, Color::White, Color::Black, { "" , zaiko }, true);
				//ランク表示
				//MFont::BSSize.DrawBold({ px + Lp(17) ,py + Lp(18) }, Color::White, Color::Black, { "Lv" , Item::data[id].Lv }, true);
				//new表示

			}
			void Click(double px, double py)
			{
				//掴む
				if (Guild::P->装備所持数[id] > 0)
				{
					//W_Drag::アイテム = &Item::data[id];
					MSound::効果音[SE::ドラッグ].Play();
				}
			}

			void Info派生(Point 座標) override
			{
				//InfoItem(&Item::data[id], 座標);
			}

		};
	public:
		std::vector<GUI_Tab> タブ;//レシピ9種 + 全て
		GUI_Item アイテム[CV::装備種];
		GUI_Frame 枠;

		int 装備数 = 0;
		int 現在タブ = 0;

		void Init()
		{
			gui_objects.clear();
			タブ.clear();
			種類 = WindowType::Item;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::装備;
			横幅 = 371;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			固定縦 = 43;
			スクロール位置 = 0;

			for (int a = 0; a < 10; a++)
			{
				タブ.emplace_back(現在タブ, a, IconType::全て, "");
				タブ[a].SetHelp(TX::Item_タブヘルプ[a]);
			}

			タブ[1].スキルアイコン = SkillType::力;
			タブ[2].スキルアイコン = SkillType::力;
			タブ[3].スキルアイコン = SkillType::力;
			タブ[4].スキルアイコン = SkillType::力;
			タブ[5].スキルアイコン = SkillType::力;
			タブ[6].スキルアイコン = SkillType::力;
			タブ[7].スキルアイコン = SkillType::力;
			タブ[8].スキルアイコン = SkillType::力;
			タブ[9].スキルアイコン = SkillType::力;

			for (auto&it : タブ)
			{
				it.アイコンオフセット = 5;
				gui_objects.push_back(&it);
			}

			for (auto&it : アイテム)
			{
				gui_objects.push_back(&it);			
			}

			gui_objects.push_back(&枠);


			SetCSVPage(7);
		}

		void GUI_Update()
		{
			for (int a = 0; a < (int)タブ.size() ; a++)
			{
				if (a == 0)
				{
					タブ[a].位置 = { Lp(0) ,Lp(1) ,Lp(2) + 3,Lp(3) };
				} else {
					タブ[a].位置 = { Lp(0) + Lp(4) * a + 3,Lp(1) ,Lp(2) ,Lp(3) };
				}
			}

			枠.位置 = { Lp(0), Lp(1) + 35, 333, 700 };
			枠.枠No = 12;

			int cnt = 0;
			const int per_line = 8;
			for (auto&it : アイテム)
			{
				it.位置 = { Lp(5) + Lp(9) *(cnt%per_line),Lp(6) + Lp(10) * (cnt /per_line),Lp(7),Lp(8) };
				cnt++;
			}

			Tub_Change();
		}

		void Tub_Change()
		{
			装備数 = 0;

			for (int a = 0; a < CV::装備種; a++)
			{

			}

			for (int a = 装備数; a < CV::装備種; a++)
			{
				アイテム[a].isヘルプ表示 = false;
			}
		}

		void 派生Draw()
		{
			GUI_Update();

			for (auto&it : タブ)
			{
				it.Draw();
			}

			枠.Draw();
			
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
}