//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[3][a]

	/*素材とアイテムウィンドウ*/
	class W_Material: public WindowBox
	{
	private:
		/*素材と数とランク*/
		class GUI_Mat_num :public GUI_Object
		{
		public:
			int ランク;
			CraftType 素材種;

			void Set(Rect 位置, int ランク, CraftType 素材種)
			{
				this->位置 = 位置;
				this->ランク = ランク;
				this->素材種 = 素材種;
			}

			void Draw派生(double px, double py)
			{
				//枠の描画
				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 12);

				//素材アイコン
				MIcon::素材[素材種].DrawRotate({ px + LV(6), py + LV(7) }, 1, 0);

				//ランク
				MIcon::アイコン[IconType::ランク].DrawRotate({ px + LV(8), py + LV(9) }, 1, 0);
				MFont::BArial小.DrawBold({ px + LV(10) ,py + LV(11) }, Color::White, Color::Black, ランク+1, true);

				//所持数
				MFont::BArial小.DrawBold({ px + LV(12) ,py + LV(13) }, Color::White, Color::Black, "x", true);
				MFont::BArial中.DrawBold({ px + LV(14)  ,py + LV(15) }, Color::White, Color::Black, Guild::P->素材数[素材種][ランク],true);
			}
		};

	public:
		std::vector<GUI_Mat_num> GUI_素材数;

		void init()
		{
			種類 = WindowType::Material;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::素材;
			横幅 = 250;
			縦幅 = 240;
			最小縦 = 240;
			最大縦 = 800;
			縦内部幅 = 480;//120☓ランク数
			スクロール位置 = 0;

			for (auto& it : GUI_素材数)
			{
				gui_objects.push_back(&it);
			}

			GUI_init();
		}


		void GUI_init()
		{
			int xx = 0;
			int n = 0;
			int yy = 0;

			GUI_素材数.clear();
			gui_objects.clear();
			縦内部幅 = 0;

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				for (int a = CV::最大素材ランク - 1; a >= 0; a--)
				{
					if (Guild::P->is素材発見[CraftType(b)][a] == false) { continue; }
					GUI_素材数.emplace_back();
					GUI_素材数[n].Set({ LV(0) + xx , LV(2) + yy, LV(4), LV(5) }, a, CraftType(b));
					gui_objects.push_back(&GUI_素材数[n]);
					n++;
					yy += LV(3);
				}

				縦内部幅 = std::max((int)縦内部幅, yy+20);
				xx += LV(1);
				yy = 0;
			}
		}

		void 派生Draw()			
		{
			GUI_init();

			for (auto &it : gui_objects)
			{
				it->Draw();
			}
		}

		bool 派生操作()
		{
			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}