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
		/*ランク*/
		class GUI_Mat_left :public GUI_Object
		{
		public:
			int 星数 = 1;

			void Set(Rect 位置, int 星数)
			{
				this->星数 = 星数;
				this->位置 = 位置;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px ,py }, 位置.GetW(), 位置.GetH(), 12);

				MFont::Arial小.DrawBold({ px + LV(14),py + LV(15) }, Color::White, Color::Black, "Rank");
				MFont::BArial大.DrawBold({ px + LV(16),py + LV(17) }, Color::White, Color::Black, 星数);
			}
		};

		class GUI_Mat_top :public GUI_Object
		{
		public:
			MaterialType 素材種;

			void Draw派生(double px, double py)
			{
				//枠の描画
				MSystem::DrawWindow({ px      , py }, 位置.GetW(), 位置.GetH(), 12);

				//アイコン描画
				MIcon::素材[素材種].DrawRotate({ px + LV(18), py + LV(19) }, 1, 0);
			}
		};

		/*素材と数とランク*/
		class GUI_Mat_num :public GUI_Object
		{
		public:
			int ランク;
			MaterialType 素材種;

			void Set(Rect 位置, int ランク, MaterialType 素材種)
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
				//MIcon::アイコン[IconType::星].DrawRotate({ px + LV(8), py + LV(9) }, 1, 0);
				//MFont::BArial小.DrawBold({ px + LV(8) ,py + LV(9) }, Color::White, Color::Black, { "Lv ",ランク }, true);
				//MFont::BArial小.DrawBold({ px + LV(10) ,py + LV(11) }, Color::White, Color::Black, ランク, true);

				//所持数
				MFont::BArial小.DrawBold({ px + LV(12) ,py + LV(13) }, Color::White, Color::Black, "x", true);
				MFont::BArial小.DrawBold({ px + LV(14)  ,py + LV(15) }, Color::White, Color::Black, Guild::P->素材数[ランク],true);

			}
		};

	public:
		//GUI_Mat_left GUI_ランク[CV::最大素材ランク];
		//GUI_Mat_top GUI_素材[CV::素材種];
		GUI_Mat_num GUI_素材数[CV::最大素材ランク];

		void init()
		{
			種類 = WindowType::Material;
			名前 = "素材";
			略記 = "素材";
			アイコン = IconType::素材;
			横幅 = 250;
			縦幅 = 240;
			最小縦 = 240;
			最大縦 = 240;
			縦内部幅 = 480;//120☓ランク数
			スクロール位置 = 0;

			SetHelp("各種素材の在庫");


			for (auto& it : GUI_素材数)
			{
				gui_objects.push_back(&it);
			}

			GUI_init();
		}


		void GUI_init()
		{
			int line = 5;

			for (int a = 0; a < CV::最大素材ランク; a++)
			{
				GUI_素材数[a].Set({ LV(0) + a%line * LV(1), LV(2) + a / line * LV(3), LV(4), LV(5) }, a , MaterialType::金属);
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