//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[5][a]



	/*来客ウィンドウ*/
	class W_Customer: public WindowBox
	{
	private:
		class GUI_Now : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//現在客数,ピーク客数,合計客数
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 17);


				MFont::Arial中.DrawBold({ px + LV(10),py + LV(11) }, Color::White, Color::Black, "now");
			}
		};
		class GUI_Peek : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//現在客数,ピーク客数,合計客数
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 17);

				MFont::Arial中.DrawBold({ px + LV(14),py + LV(15) }, Color::White, Color::Black, "peek");
			}
		};

		class GUI_Count : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//現在客数,ピーク客数,合計客数
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(),17);

				MFont::Arial中.DrawBold({ px + LV(18),py + LV(19) }, Color::White, Color::Black, "total");

			}
		};

		class GUI_Customer : public GUI_Object
		{
		public:
			Customer* 参照;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 17);

				//ふきだし、キャラ絵、残り時間ゲージ
				int xd = 0;
				int yd = 0;
				int count = 0;

				for (auto& it : Customer::my_customers)
				{
					if (it.来店ギルド == 0)
					{
						MUnit::ユニット[it.見た目][1]->DrawRotate({ px+xd + LV(24),py+yd + LV(25) },2,0);

						double rate = (double)it.待ち時間 / it.待機限界;

						if (rate < 1.0)
						{
							MSystem::DrawBar({ px + xd + LV(26) ,py + yd + LV(27) }, LV(28), LV(29), rate, 1, Color::Blue, { 192,192,255 }, { 192,192,255 }, true);
						} else {
							MSystem::DrawBar({ px + xd + LV(26) ,py + yd + LV(27) }, LV(28), LV(29), rate, 1, Color::Red, { 255,192,192 }, { 255,192,192 }, true);
						}

						if (it.接客待ち == false)
						{
							MIcon::エモート[EmoteType::音符].Draw({ px + xd + LV(22),py + yd + LV(23) });
						}
						if (rate < 0.25)
						{
							MIcon::エモート[EmoteType::３点].Draw({ px + xd + LV(22),py + yd + LV(23) });
						}
						else if (rate < 0.5)
						{
							MIcon::エモート[EmoteType::２点].Draw({ px + xd + LV(22),py + yd + LV(23) });

						}
						else if (rate < 0.75)
						{
							MIcon::エモート[EmoteType::１点].Draw({ px + xd + LV(22),py + yd + LV(23) });

						}
						else
						{
							MIcon::エモート[EmoteType::怒り].Draw({ px + xd + LV(22),py + yd + LV(23) });
						}

					
						if (count % 6 == 5)
						{
							xd = 0;
							yd += LV(30);
						}
						else {
							xd += LV(31);
						}
						count++;
					}
				}

			}
		};


	public:
		GUI_Now gui_now;
		GUI_Peek gui_peek;
		GUI_Count gui_count;//客数表示
		GUI_Customer gui_customer;//客表示

		void init()
		{
			種類 = WindowType::Customer;

			名前 = "来客";
			略記 = "来客";
			アイコン = IconType::来客;
			横幅 = 280;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			固定縦 = 60;
			スクロール位置 = 0;
		}

		void GUI_Init()
		{

			gui_now.位置 = { LV(0),LV(1) ,LV(2),LV(3) };
			gui_peek.位置 = { LV(4),LV(1) ,LV(2),LV(3) };
			gui_count.位置 = { LV(5),LV(1) ,LV(2),LV(3) };

			gui_customer.位置 = { LV(6),LV(7),LV(8),LV(9) };

			gui_now.is固定 = true;
			gui_peek.is固定 = true;
			gui_count.is固定 = true;

			gui_objects.push_back(&gui_now);
			gui_objects.push_back(&gui_peek);
			gui_objects.push_back(&gui_count);
			gui_objects.push_back(&gui_customer);


			gui_now.SetHelp("現在来客数");
			gui_peek.SetHelp("ピーク時来客数");
			gui_count.SetHelp("合計来客数");

			gui_customer.SetHelp("客一覧");
		}

		void 派生Draw()
		{
			GUI_Init();
			//固定描画
			gui_count.Draw();
			gui_now.Draw();
			gui_peek.Draw();
			描画範囲(true);
			//スクロール可
			
			gui_customer.Draw();
		}

		bool 派生操作()
		{
			//操作無し
			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}