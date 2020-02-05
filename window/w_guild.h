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
			bool is小数点以下表示 = false;
			int id;
			double* d参照数値 = nullptr;
			double* i参照数値 = nullptr;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), LV(5));
			}
		};

		class GUI_ギルマス : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), LV(5));
			}
		};

	public:

		GUI_数値 ギルド名;
		GUI_ギルマス ギルマス;
		GUI_数値 総資金;
		GUI_数値 集客力;//人/日
		GUI_数値 地図数;//枚
		GUI_数値 開発数;//種
		GUI_数値 討伐数;//体
		GUI_数値 名声値;//P

		void init()
		{
			種類 = WindowType::Guild;

			名前 = "ギルド情報";
			略記 = "情報";
			アイコン = IconType::情報;
			横幅 = 230;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;

			gui_objects.push_back(&ギルド名);
			gui_objects.push_back(&ギルマス);
			gui_objects.push_back(&総資金);
			gui_objects.push_back(&集客力);//人/日
			gui_objects.push_back(&地図数);//枚
			gui_objects.push_back(&開発数);//種
			gui_objects.push_back(&討伐数);//体
			gui_objects.push_back(&名声値);//P
		}


		void GUI_Init()
		{
			ギルド名.位置 = { LV(0),LV(1) + LV(4) * 0,LV(2),LV(3) };
			ギルマス.位置 = { LV(0),LV(1) + LV(4) * 1,LV(2),LV(3) };
			総資金.位置 = { LV(0),LV(1) + LV(4) * 2,LV(2),LV(3) };
			集客力.位置 = { LV(0),LV(1) + LV(4) * 3,LV(2),LV(3) };
			地図数.位置 = { LV(0),LV(1) + LV(4) * 4,LV(2),LV(3) };
			開発数.位置 = { LV(0),LV(1) + LV(4) * 5,LV(2),LV(3) };
			討伐数.位置 = { LV(0),LV(1) + LV(4) * 6,LV(2),LV(3) };
			名声値.位置 = { LV(0),LV(1) + LV(4) * 7,LV(2),LV(3) };
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