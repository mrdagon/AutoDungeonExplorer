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
				DrawUI(UIType::丸フレーム);//完了したら暗くする、クリア後未チェック

				//依頼者見た目
				quest->依頼人image->DrawRotate(GetPos( LA ), 2, 0);

				//クエスト名
				MFont::L->DrawEdge(GetPos( LB ), Design::暗字, {quest->名前});

				//対象フロア(無い場合は表示しない)
				MFont::L->DrawEdge(GetPos(LC), Design::暗字, { "10F" } , true);

				//クリア済み、New表示
				MFont::M->DrawEdge(GetPos(LD), Design::明字, { "Clear" });
			}

			void DrawHelp() override
			{
				UIHelp::Quest(quest);
			}
		};


	public:
		UIQuest 依頼[CV::上限依頼数];
		UIButton 表示ボタン[3];
		bool is表示受注前 = true;
		bool is表示進行中 = true;
		bool is表示完了 = true;

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

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化
			for (int i = 0; i < Quest::data.size(); i++)
			{
				依頼[i].SetUI(LQuest::依頼枠, i);
				依頼[i].quest = &Quest::data[i];
			}

			表示ボタン[0].SetUI(LQuest::表示ボタン, "完了" , 0);
			表示ボタン[1].SetUI(LQuest::表示ボタン, "進行中" , 1);
			表示ボタン[2].SetUI(LQuest::表示ボタン, "受注前" , 2);
			表示ボタン[0].is押下 = true;
			表示ボタン[1].is押下 = true;
			表示ボタン[2].is押下 = true;

			//●登録
			AddItem(依頼, Quest::data.size() );
			AddItem(表示ボタン, 3 , true);

			//●イベント
			表示ボタン[0].clickEvent = [&]()
			{
				表示ボタン[0].is押下 = !表示ボタン[0].is押下;
				is表示完了 = 表示ボタン[1].is押下;
				表示ボタン[0].押下アニメ = 0;
			};
			表示ボタン[1].clickEvent = [&]()
			{
				表示ボタン[1].is押下 = !表示ボタン[1].is押下;
				is表示進行中 = 表示ボタン[0].is押下;
				表示ボタン[1].押下アニメ = 0;
			};
			表示ボタン[2].clickEvent = [&]()
			{
				表示ボタン[2].is押下 = !表示ボタン[2].is押下;
				is表示受注前 = 表示ボタン[2].is押下;
				表示ボタン[2].押下アニメ = 0;
			};

			Update();
		}

		void Update()
		{
			SetPos(LQuest::ウィンドウ, false, true, false);
			固定縦 = 40;

			縦内部幅 = 56;

			int cnt = 0;
			for (int i = 0; i < Quest::data.size(); i++)
			{
				if (
						(依頼[i].quest->進行状況 == QuestState::受注前 && is表示受注前 == true ) ||
						(依頼[i].quest->進行状況 == QuestState::進行中 && is表示進行中 == true)	||
						(依頼[i].quest->進行状況 == QuestState::完了 && is表示完了 == true)
					)
				{
					依頼[i].lineID = cnt;
					依頼[i].is表示 = true;
					縦内部幅 += 54;
					cnt++;
				} else {
					依頼[i].is表示 = false;
				}
			}
		}
	};
}