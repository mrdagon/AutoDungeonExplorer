//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[15][a]



	/*依頼ウィンドウ*/
	class W_Quest : public WindowBox
	{
	private:
		class GUI_依頼 : public GUI_Object
		{
		public:
			int id;

			void Draw派生(double px, double py)
			{

				//全体の枠
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);

				//Main or Subをアイコン？文字？

				if (Quest::data[id].isメイン)
				{
					MFont::BArial小.DrawBold({ px + LV(15) ,py + LV(16) }, Color::White, Color::Black, { "Main Quest" });
				} else {
					MFont::BArial小.DrawBold({ px + LV(15) ,py + LV(16) }, Color::White, Color::Black, { "Sub Quest" });
				}

				//クエスト名
				MFont::BArial大.DrawBold({ px + LV(5) ,py + LV(6) }, Color::White, Color::Black, { Quest::data[id].名前 });

				//達成条件と達成率＿complete表示
				MFont::BArial中.DrawBold({ px + LV(7) ,py + LV(8) }, Color::White, Color::Black, {  Quest::data[id].達成度 , " / " , Quest::data[id] .条件数値} , true );

				//報酬、名誉
				MIcon::アイコン[IconType::名声].Draw({ px + LV(9), py + LV(10) });
				MFont::BArial中.DrawBold({ px + LV(11) ,py + LV(12) }, Color::White, Color::Black, { Quest::data[id].報酬名誉 } , true);
				//報酬、資金
				MIcon::アイコン[IconType::資金].Draw({ px + LV(13), py + LV(10) });
				MFont::BArial中.DrawBold({ px + LV(14) ,py + LV(12) }, Color::White, Color::Black, { Quest::data[id].報酬金 } );

			}
		};


	public:

		std::vector<GUI_依頼> 依頼;

		void init()
		{
			種類 = WindowType::Quest;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::依頼;
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
		}

		void GUI_Init()
		{
			gui_objects.clear();
			依頼.clear();

			for (int a= 0 ; a < Quest::data.size() ; a++ )
			{
				依頼.emplace_back();
				依頼[a].位置 = { LV(0) , LV(1) + (LV(3) + LV(4)) * a , LV(2) , LV(3) };
				依頼[a].id = a;
				依頼[a].SetHelp(Quest::data[a].説明);
			}

			for (int a = 0; a < 依頼.size(); a++)
			{
				gui_objects.push_back(&依頼[a]);
			}


			縦内部幅 = double(LV(0)*2 + (LV(3) + LV(4)) * Quest::data.size());
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