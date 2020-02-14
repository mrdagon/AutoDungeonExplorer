//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[6][a]



	/*求人ウィンドウ*/
	class W_Recruit: public WindowBox
	{
	private:
		class GUI_Req : public GUI_Object
		{
		public:
			W_Recruit *親ウィンドウ;
			Warker* 参照先;
			int 並びID;

			GUI_Req(Warker* 参照先) :
				参照先(参照先)
			{
			}


			void Draw派生(double px, double py)
			{
				//現在客数,ピーク客数,合計客数
				
				//キャラアイコン,レベル,雇用予定表示
				if (参照先->is内定 == true)
				{
					MSystem::DrawBoxBold({ px,py }, (int)位置.GetW(), (int)位置.GetH(), {255,128,128}, 2, Color::Red);

				} else {
					MSystem::DrawBoxBold({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::White, 2, Color::White);
				}

				MUnit::ユニット[参照先->見た目][1]->DrawRotate({ px + LV(9) ,py + LV(9) }, 2, 0);
				MFont::BArial小.DrawBold({ px + LV(6) ,py + LV(8) }, Color::White, Color::Black, 参照先->Lv, true);

				MFont::BArial小.DrawBold({ px + LV(7) ,py + LV(8) }, Color::White, Color::Black, "Lv", true);

			}

			void Click(double px, double py)
			{
				W_Drag_Drop::ギルメン = 参照先;
				W_Drag_Drop::ウィンドウ = 親ウィンドウ;
				W_Drag_Drop::並びID = 並びID;
			}


			void Info派生(Point 座標) override
			{
				InfoHunter(参照先,座標);
			}

		};


	public:
		std::vector<GUI_Req> 求職者;//求職者

		void init()
		{
			種類 = WindowType::Recruit;
			名前 = "求人";
			略記 = "求人";
			アイコン = IconType::求人;
			横幅 = 280;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 180;
			縦内部幅 = 180;//120☓ランク数
			スクロール位置 = 0;
		}

		void GUI_init()
		{
			求職者.clear();
			gui_objects.clear();

			for (auto &it : Warker::data)
			{
				if (it.就活 == Guild::P->id)
				{
					求職者.emplace_back(&it);
				}
			}

			for (auto &it : 求職者)
			{
				gui_objects.push_back(&it);
				it.親ウィンドウ = this;
			}

			if (求職者.size() > 18)
			{
				最大縦 = int(求職者.size()+5) / 6 * LV(5)+15;
				縦内部幅 = 最大縦;
			}

			int n = 0;
			for (auto &it : 求職者)
			{
				it.位置 = { LV(0) + n%6 * LV(4) ,LV(1) + n / 6 *LV(5) ,LV(2),LV(3) };
				it.isヘルプ表示 = true;
				n++;
			}
		}

		void 派生Draw()
		{
			GUI_init();


			for (auto &it : 求職者)
			{
				it.Draw();
			}

		}

		bool 派生操作()
		{
			for (auto& it : 求職者)
			{
				it.操作チェック(相対座標.x, 相対座標.y);
			}


			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}