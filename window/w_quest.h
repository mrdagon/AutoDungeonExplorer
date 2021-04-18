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
				auto& LA = LData(LQuest::依頼者);
				auto& LB = LData(LQuest::クエスト名);
				auto& LC = LData(LQuest::フロア);
				auto& LD = LData(LQuest::ステータス);

				//全体の枠
				DrawUI(UIType::グループ明);//完了したら暗くする、クリア後未チェック

				//依頼者見た目
				quest->依頼人image->DrawRotate(GetPos( LA ), 2, 0);

				//クリア済み、New表示
				MFont::S->DrawBold(GetPos(LD), Design::明字, Design::暗字, { "Clear" });

				//クエスト名
				MFont::M->DrawBold(GetPos( LB ), Design::明字, Design::暗字, {quest->名前});

				//対象フロア(無い場合は表示しない)
				MFont::M->DrawBold(GetPos(LC), Design::明字, Design::暗字, { "10F" } , true);
			}
		};


	public:
		UIQuest 依頼[CV::上限依頼数];
		UIButton 表示ボタン[3];

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

			表示ボタン[0].SetUI(LQuest::表示ボタン, "未達成" , 0);
			表示ボタン[1].SetUI(LQuest::表示ボタン, "完了" , 1);
			表示ボタン[2].SetUI(LQuest::表示ボタン, "未発見" , 2);

			//●登録
			AddItem(依頼, Quest::data.size() );
			AddItem(表示ボタン, 3 , true);

			Update();
		}

		void Update()
		{
			SetPos(LQuest::ウィンドウ, false, true, false);
			固定縦 = 40;

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