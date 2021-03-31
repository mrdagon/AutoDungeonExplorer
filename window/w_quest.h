//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*依頼ウィンドウ*/
	class W_Quest : public UIWindow
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

				MFont::SAlias.DrawBold({ px + Lp(15) ,py + Lp(16) }, Color::White, Color::Black, { "Quest" });

				//クエスト名
				MFont::LAlias.DrawBold({ px + Lp(5) ,py + Lp(6) }, Color::White, Color::Black, { Quest::data[id].名前 });

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
		//新たに発生してチェックしていない
		//完了してチェックしてない
		//未完クエスト
		//完了済みクエスト		
		//の順番で表示？

		//詳細はヘルプポップアップで確認

		void Init()
		{
			Set(WindowType::Quest, IconType::依頼);
			SetPos(LQuest::ウィンドウ, false, true, false);

			/*
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
			*/
		}

		void Update()
		{
			SetPos(LQuest::ウィンドウ, false, true, false);
		}
	};
}