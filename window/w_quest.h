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
		class UIQuest : public UIObject
		{
		public:
			void Draw派生() override
			{
				//全体の枠
				//MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);

				//Main or Subをアイコン？文字？

				//クリア済みマーク
				//Newマーク
				//依頼者見た目

				//MFont::SAlias.DrawBold({ px + Lp(15) ,py + Lp(16) }, Color::White, Color::Black, { "Quest" });

				//クエスト名
				//MFont::LAlias.DrawBold({ px + Lp(5) ,py + Lp(6) }, Color::White, Color::Black, { Quest::data[id].名前 });
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