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
			Quest* quest;

			void Draw派生() override
			{
				//全体の枠
				DrawUI(UIType::平ボタン);

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
		UIQuest 依頼[CV::上限依頼数];
		UITextFrame 内枠;

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

			//●初期化
			for (int i = 0; i < Quest::data.size(); i++)
			{
				依頼[i].SetUI(LQuest::依頼枠, i);
				依頼[i].quest = &Quest::data[i];
			}
			内枠.SetUI("", LQuest::内枠);

			//●登録
			AddItem(依頼, Quest::data.size() );
			AddItem(内枠);

			Update();
		}

		void Update()
		{
			SetPos(LQuest::ウィンドウ, false, true, false);

			int cnt = 0;
			for (int i = 0; i < Quest::data.size(); i++)
			{
				if (依頼[i].quest->is受注 == false)
				{
					依頼[i].lineID = cnt;
					依頼[i].is表示 = true;
					cnt++;
				}
			}
		}
	};
}