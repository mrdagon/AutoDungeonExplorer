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

		/*素材と数*/
		class GUI_Mat_num :public GUI_Object
		{
		public:
			int ランク;
			MaterialType 素材種;

			void Set(Rect 位置, int ランク , MaterialType 素材種)
			{
				this->位置 = 位置;
				this->ランク = ランク;
				this->素材種 = 素材種;
			}

			void Draw派生(double px, double py)
			{
				//枠の描画
				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 12);

				//素材数-獲得数-消費数
				int len = MFont::BArial中.GetDrawStringWidth(Guild::P->素材数[ランク][素材種]) / 2;

				MFont::BArial中.DrawBold({ px + LV(20) + len ,py + LV(21) }, Color::White, Color::Black, Guild::P->素材数[ランク][素材種],true);

				//獲得量と消費量
				//Screen::SetBright({128,255,128});
				//MFont::BArial小.DrawBold({ px + LV(22) ,py + LV(23) }, Color::White, Color::Black, { Guild::P->素材数[ランク][素材種] }, true);
				//Screen::SetBright({ 255,128,128 });
				//MFont::BArial小.DrawBold({ px + LV(24) ,py + LV(25) }, Color::White, Color::Black, { Guild::P->素材数[ランク][素材種] }, true);
				//Screen::SetBright();
			}
		};

	public:
		GUI_Mat_left GUI_ランク[CV::最大素材ランク];
		GUI_Mat_top GUI_素材[CV::素材種];
		GUI_Mat_num GUI_素材数[CV::素材種 * CV::最大素材ランク];

		void init()
		{
			種類 = WindowType::Material;
			名前 = "素材";
			略記 = "素材";
			アイコン = IconType::素材;
			横幅 = 365;
			縦幅 = 240;
			最小縦 = 240;
			最大縦 = 240;
			縦内部幅 = 240;//120☓ランク数
			スクロール位置 = 0;

			SetHelp("各種素材の在庫");

			for (auto& it : GUI_ランク)
			{
				gui_objects.push_back(&it);
			}

			for (auto& it : GUI_素材数)
			{
				gui_objects.push_back(&it);
			}

			for (int a = 0; a < CV::素材種; a++)
			{
				gui_objects.push_back(&GUI_素材[a]);
				GUI_素材[a].素材種 = MaterialType(a);
			}


			GUI_init();
		}


		void GUI_init()
		{
			for (int a = 0; a < CV::最大素材ランク; a++)
			{
				GUI_ランク[a].Set({ LV(0) , LV(1) + LV(2) * a, LV(3), LV(4) }, a+1);
			}

			for (int a = 0; a < CV::素材種; a++)
			{
				GUI_素材[a].位置 = {LV(5)+LV(6) * a ,LV(7),LV(8),LV(9)};
			}

			for (int a = 0; a < CV::最大素材ランク; a++)
			{

				for (int b = 0; b < CV::素材種; b++)
				{
					GUI_素材数[a + b * CV::最大素材ランク].Set({ LV(10) + b * LV(11), LV(12) + a * LV(13), LV(8), LV(4) }, a , MaterialType(b));
				}
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