//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
	/*素材とアイテムウィンドウ*/
	class W_Material: public WindowBox
	{
	private:
		/*素材と数とランク*/
		class GUI_Mat_num :public GUI_Object
		{
		public:
			Material* 素材種 = nullptr;

			void Set(Rect 位置, int 素材種)
			{
				this->位置 = 位置;
				this->素材種 = &Material::data[素材種];
			}

			void Draw派生(double px, double py)
			{
				if (素材種 == nullptr) { return; }

				//枠の描画
				MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 12);

				//素材アイコン
				MIcon::アイコン[素材種->アイコン].DrawRotate({ px + Lp(6), py + Lp(7) }, 1, 0);

				//Lv
				MFont::BSSize.DrawBold({ px + Lp(10) ,py + Lp(11) }, Color::White, Color::Black, { "Lv" , 素材種->Lv }, true);

				//所持数
				MFont::BSSize.DrawBold({ px + Lp(12) ,py + Lp(13) }, Color::White, Color::Black, "x", true);
				MFont::BMSize.DrawBold({ px + Lp(14)  ,py + Lp(15) }, Color::White, Color::Black, Guild::P->素材数[素材種->ID],true);
			}

			void Info派生(Point 座標) override
			{
				//素材情報
				InfoMaterial( 素材種 , 座標 );
			}

		};

	public:
		GUI_Mat_num GUI_素材数[CV::最大素材種];

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

			SetCSVPage(3);

			GUI_init();
		}


		void GUI_init()
		{
			int xx = -Lp(1);
			int yy = -Lp(3);
			int cnt = 0;

			縦内部幅 = 0;

			for (int a = 0 ; a < CV::最大素材種; a++)
			{
				xx += Lp(1);

				if (a % 4 == 0)
				{
					yy += Lp(3);
					xx = 0;
				}

				if (Guild::P->is素材発見[a] == false) 
				{ 
					GUI_素材数[a].is表示 = false;
					continue; 				
				}
				GUI_素材数[a].Set({ Lp(0) + xx , Lp(2) + yy, Lp(4), Lp(5) }, a );
				GUI_素材数[a].is表示 = true;
			}

			縦内部幅 = std::max((int)縦内部幅, yy+20);
			yy = 0;
		}
	};
}