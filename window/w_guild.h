//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[5][a]



	/*ギルドの情報*/
	class W_Guild : public WindowBox
	{
	private:
		class GUI_数値 : public GUI_Object
		{
		public:
			std::string 名前;
			std::string 単位;
			IconType アイコン;
			int id;

			void Set(const char* 名前, const char* 単位, IconType アイコン, int id)
			{
				this->名前 = 名前;
				this->単位 = 単位;
				this->アイコン = アイコン;
				this->id = id;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				MIcon::アイコン[アイコン].Draw({px+LV(6),py+LV(7)});

				MFont::BArial中.DrawBold({ px + LV(9) ,py + LV(8) }, Color::White, Color::Black, 名前, false);
				MFont::BArial中.DrawBold({ px + LV(10) ,py + LV(8) }, Color::White, Color::Black, { "1234 ", 単位 }, true);
				//MFont::BArial中.DrawBold({ px + LV(11) ,py + LV(8) }, Color::White, Color::Black, 単位, true);

			}
		};

		class GUI_ギルマス : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);

				MIcon::アイコン[IconType::資金].Draw({ px + LV(12),py + LV(13) });
				MUnit::ユニット[UnitImageType::おじいさん][1]->DrawRotate({ px + LV(14) , py + LV(15) }, 2, 0);

				MFont::BArial中.DrawBold({ px + LV(16) ,py + LV(17) }, Color::White, Color::Black, "ギルド名", false);
				MFont::BArial中.DrawBold({ px + LV(18) ,py + LV(19) }, Color::White, Color::Black, "ギルマス名", false);
			}
		};

	public:

		GUI_ギルマス ギルマス;//+ギルド名
		GUI_数値 団員数;//ギルド人数

		GUI_数値 資金;//G
		GUI_数値 販売数;//販売数
		GUI_数値 売上;//売上
		GUI_数値 集客力;//人/日


		GUI_数値 製造数;//個
		GUI_数値 開発数;//種
		GUI_数値 素材在庫;//個

		GUI_数値 地図数;//枚
		GUI_数値 討伐数;//体
		GUI_数値 撤退数;//回

		GUI_数値 名声値;//P


		
		void init()
		{
			種類 = WindowType::Guild;

			名前 = "ギルド情報";
			略記 = "情報";
			アイコン = IconType::情報;
			横幅 = 280;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;

			団員数.Set("団員", "人", IconType::資金, 4);
			名声値.Set("名声", "点", IconType::資金, 5);

			資金.Set( "資金","Ｇ",IconType::資金,0);
			販売数.Set("討伐", "体", IconType::資金, 4);
			売上.Set("売上", "Ｇ", IconType::資金, 4);
			集客力.Set( "集客","人", IconType::資金, 1);

			製造数.Set("製造", "種", IconType::資金, 3);;//個
			開発数.Set("開発", "種", IconType::資金, 3);
			素材在庫.Set("素材", "個", IconType::資金, 4);

			地図数.Set( "地図","枚", IconType::資金, 2);
			討伐数.Set( "討伐","体", IconType::資金, 4);
			撤退数.Set("撤退", "回", IconType::資金, 4);

			gui_objects.push_back(&ギルマス);
			gui_objects.push_back(&団員数);

			gui_objects.push_back(&資金);
			gui_objects.push_back(&販売数);
			gui_objects.push_back(&売上);
			gui_objects.push_back(&集客力);


			gui_objects.push_back(&製造数);
			gui_objects.push_back(&開発数);
			gui_objects.push_back(&素材在庫);

			gui_objects.push_back(&地図数);
			gui_objects.push_back(&討伐数);
			gui_objects.push_back(&撤退数);

			gui_objects.push_back(&名声値);
		}

		void GUI_Init()
		{
			ギルマス.位置 = { LV(0),LV(1) ,LV(2),LV(5)-2 };

			for (int a = 1 ; a < gui_objects.size() ; a++)
			{
				gui_objects[a]->位置 = { LV(0),LV(1) + LV(4) * (a-1) + LV(5),LV(2),LV(3) };
			}

		}

		void 派生Draw()
		{
			GUI_Init();

			for (auto& it : gui_objects)
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