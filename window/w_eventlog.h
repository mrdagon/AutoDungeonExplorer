//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*イベントログウィンドウ*/
	class W_EventLog : public UIWindow
	{
		class UILog : public UIObject
		{
			public:
			void Draw派生() override
			{
				//該当するログを表示する
			}
		};


	public:	
		//タブ
		UITab タブ[5];
		UITextFrame 枠;
		UILog ログ;

		int 現在タブ = 0;

		void Init()
		{
			Set( WindowType::EventLog , IconType::ログ );
			SetPos(LLog::ウィンドウ, false, true, false);

			//●初期化
			枠.SetUI("", LLog::内枠);
			タブ[0].SetUI(&現在タブ, &MIcon::UI[IconType::ランク], "全て", LLog::タブ, 0);
			タブ[1].SetUI(&現在タブ, &MIcon::UI[IconType::情報], "依頼", LLog::タブ, 1);
			タブ[2].SetUI(&現在タブ, &MIcon::UI[IconType::ボス], "ボス", LLog::タブ, 2);
			タブ[3].SetUI(&現在タブ, &MIcon::UI[IconType::宝箱], "財宝", LLog::タブ, 3);
			タブ[4].SetUI(&現在タブ, &MIcon::UI[IconType::迷宮], "探索", LLog::タブ, 4);

			ログ.SetUI( LLog::ログ枠 );

			//●登録
			AddItem(枠,true);
			AddItem(タブ, 5, true);

			AddItem(ログ);
		}

		void Update()
		{
			SetPos(LLog::ウィンドウ, false, true, false);
		}
	};
}