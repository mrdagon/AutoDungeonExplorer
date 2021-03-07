//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

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

				MFont::BSSize.DrawBold({ px + Lp(15) ,py + Lp(16) }, Color::White, Color::Black, { "Quest" });

				//クエスト名
				MFont::BLSize.DrawBold({ px + Lp(5) ,py + Lp(6) }, Color::White, Color::Black, { Quest::data[id].名前 });

				//達成条件と達成率＿complete表示
				//MFont::BMSize.DrawBold({ px + Lp(7) ,py + Lp(8) }, Color::White, Color::Black, {  Quest::data[id].達成度 , " / " , Quest::data[id] .条件数値} , true );

				//報酬、名誉
				MIcon::UI[IconType::名声].Draw({ px + Lp(9), py + Lp(10) });
				//MFont::BMSize.DrawBold({ px + Lp(11) ,py + Lp(12) }, Color::White, Color::Black, { Quest::data[id].報酬名誉 } , true);
				//報酬、資金
				MIcon::UI[IconType::資金].Draw({ px + Lp(13), py + Lp(10) });
				//MFont::BMSize.DrawBold({ px + Lp(14) ,py + Lp(12) }, Color::White, Color::Black, { Quest::data[id].報酬金 } );

			}
		};


	public:

		std::vector<GUI_依頼> 依頼;

		void Init()
		{
			gui_objects.clear();
			依頼.clear();
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

			for (int a = 0; a < (int)Quest::data.size(); a++)
			{
				依頼.emplace_back();
				依頼[a].id = a;
				依頼[a].SetHelp(Quest::data[a].説明);
			}

			for (int a = 0; a < (int)依頼.size(); a++)
			{
				gui_objects.push_back(&依頼[a]);
			}

			SetCSVPage(15);
		}

		void GUI_Update()
		{

			for (int a= 0 ; a < (int)Quest::data.size() ; a++ )
			{
				//未受注依頼は表示しない、完了依頼は後ろに回す

				依頼[a].位置 = { Lp(0) , Lp(1) + (Lp(3) + Lp(4)) * a , Lp(2) , Lp(3) };
			}

			縦内部幅 = double(Lp(0)*2 + (Lp(3) + Lp(4)) * Quest::data.size());
		}

		void 派生Draw()
		{
			GUI_Update();

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
}