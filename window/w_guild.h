//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

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
				MIcon::アイコン[アイコン].Draw({px+Lp(6),py+Lp(7)});

				double num = 0;
				switch (id)
				{
					case 0:num = Guild::P->総人数; break;//団員 人
					case 1:num = Guild::P->名声; break;//名声 点
					case 2:num = Guild::P->資金; break;//資金 Ｇ
					case 3:num = Guild::P->総販売; break;//販売 個
					case 4:num = Guild::P->総売上; break;//売上 Ｇ
					case 5:num = Guild::P->総製造; break;//製造 個
					//case 6:num = 0; break;//開発 種
					case 7:num = Guild::P->総素材; break;//素材 個
					case 8:num = Guild::P->総地図; break;//地図 枚
					case 9:num = Guild::P->総討伐; break;//討伐 体
					case 10:num = Guild::P->総全滅; break;//撤退 回
				}

				MFont::BMSize.DrawBold({ px + Lp(9) ,py + Lp(8) }, Color::White, Color::Black, 名前, false);
				MFont::BMSize.DrawBold({ px + Lp(10) ,py + Lp(8) }, Color::White, Color::Black, { (long int)num , " " , 単位 }, true);
			}
		};

		class GUI_ギルマス : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);

				MIcon::アイコン[IconType::資金].Draw({ px + Lp(12),py + Lp(13) });
				MUnit::ユニット[UnitImageType::おじいさん][1]->DrawRotate({ px + Lp(14) , py + Lp(15) }, 2, 0);

				MFont::BMSize.DrawBold({ px + Lp(16) ,py + Lp(17) }, Color::White, Color::Black, TX::Guild_ギルマス[0], false);
				MFont::BMSize.DrawBold({ px + Lp(18) ,py + Lp(19) }, Color::White, Color::Black, TX::Guild_ギルマス[1], false);
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
		//GUI_数値 開発数;//種
		GUI_数値 素材在庫;//個

		GUI_数値 地図数;//枚
		GUI_数値 討伐数;//体
		GUI_数値 撤退数;//回

		GUI_数値 名声値;//P
		
		void init()
		{
			種類 = WindowType::Guild;

			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::情報;
			横幅 = 280;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;

			団員数.Set(TX::Guild_項目[0].c_str(), TX::Guild_単位[0].c_str(), IconType::資金, 0);
			名声値.Set(TX::Guild_項目[1].c_str(), TX::Guild_単位[1].c_str(), IconType::名声, 1);

			資金.Set(TX::Guild_項目[2].c_str(), TX::Guild_単位[2].c_str(),IconType::資金,2);
			販売数.Set(TX::Guild_項目[3].c_str(), TX::Guild_単位[3].c_str(), IconType::装備, 3);
			売上.Set(TX::Guild_項目[4].c_str(), TX::Guild_単位[4].c_str(), IconType::資金, 4);

			製造数.Set(TX::Guild_項目[5].c_str(), TX::Guild_単位[5].c_str(), IconType::装備, 5);;//個
			素材在庫.Set(TX::Guild_項目[6].c_str(), TX::Guild_単位[6].c_str(), IconType::素材, 7);

			地図数.Set(TX::Guild_項目[7].c_str(), TX::Guild_単位[7].c_str(), IconType::地図, 8);
			討伐数.Set(TX::Guild_項目[8].c_str(), TX::Guild_単位[8].c_str(), IconType::ボス, 9);
			撤退数.Set(TX::Guild_項目[9].c_str(), TX::Guild_単位[9].c_str(), IconType::撤退, 10);

			gui_objects.push_back(&ギルマス);
			gui_objects.push_back(&名声値);
			gui_objects.push_back(&団員数);

			gui_objects.push_back(&資金);
			gui_objects.push_back(&販売数);
			gui_objects.push_back(&売上);


			gui_objects.push_back(&製造数);
			gui_objects.push_back(&素材在庫);

			gui_objects.push_back(&地図数);
			gui_objects.push_back(&討伐数);
			gui_objects.push_back(&撤退数);

			SetCSVPage(5);
		}

		void GUI_Init()
		{
			ギルマス.位置 = { Lp(0),Lp(1) ,Lp(2),Lp(5)-2 };

			for (int a = 1 ; a < (int)gui_objects.size() ; a++)
			{
				gui_objects[a]->位置 = { Lp(0),Lp(1) + Lp(4) * (a-1) + Lp(5),Lp(2),Lp(3) };
			}
		}
	};
}