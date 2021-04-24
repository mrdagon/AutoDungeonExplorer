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
				auto& LA = LData(LLog::ログ枠);
				auto& LB = LData(LLog::ログアイコン);
				auto& LC = LData(LLog::ログ文章);
				auto& LD = LData(LLog::ログ日付);

				//該当するログを表示する
				//後から追加された物を上に表示
				int y差分 = 0;
				for (int i = EventLog::logs.size() - 1; i >= 0; i--)
				{
					auto& it = EventLog::logs[i];

					if ( W_EventLog::is分類表示[(int)it.種類] == false)
					{
						continue;
					}
					//枠
					Design::No1->Draw(UIType::丸フレーム, LA.x, LA.y + y差分, LA.w, LA.h);

					//アイコン
					switch ( it.種類)
					{
					default:
						MIcon::UI[IconType::ボス].Draw({ LB.x, LB.y + y差分 });
						break;
					}
					//日付
					MFont::L->Draw({ LD.x,LD.y + y差分 }, Design::暗字, { it.日付 , "日" },true);

					//文章
					MFont::L->Draw({ LC.x,LC.y + y差分 }, Design::暗字, { it.テキスト });
					
					y差分 += LA.並べy;
				}
			}
		};


	public:	
		//タブ
		static inline bool is分類表示[4];
		UIButton 表示ボタン[4];
		UILog ログ;

		int 現在タブ = 0;

		void Init()
		{
			Set( WindowType::EventLog , IconType::ログ );
			SetPos(LLog::ウィンドウ, false, true, false);

			//●初期化
			表示ボタン[0].SetUI(LLog::表示ボタン, &MIcon::UI[IconType::情報], "依頼", 0);
			表示ボタン[1].SetUI(LLog::表示ボタン, &MIcon::UI[IconType::ボス], "ボス", 1);
			表示ボタン[2].SetUI(LLog::表示ボタン, &MIcon::UI[IconType::迷宮], "探索", 2);
			表示ボタン[3].SetUI(LLog::表示ボタン, &MIcon::UI[IconType::資金], "投資", 3);

			ログ.SetUI( LLog::ログ枠 );

			for ( int i =0 ;i < 4;i++)
			{
				表示ボタン[i].is押下 = true;
				is分類表示[i] = true;
			}

			表示ボタン[0].clickEvent = [&]()
			{
				is分類表示[0] = ! is分類表示[0];
				表示ボタン[0].is押下 = is分類表示[0];
			};
			表示ボタン[1].clickEvent = [&]()
			{
				is分類表示[1] = !is分類表示[1];
				表示ボタン[1].is押下 = is分類表示[1];
			};
			表示ボタン[2].clickEvent = [&]()
			{
				is分類表示[2] = !is分類表示[2];
				表示ボタン[2].is押下 = is分類表示[2];
			};
			表示ボタン[3].clickEvent = [&]()
			{
				is分類表示[3] = !is分類表示[3];
				表示ボタン[3].is押下 = is分類表示[3];
			};

			//●登録
			item.clear();
			AddItem(表示ボタン, 4, true);
			AddItem(ログ);

			EventLog::Add("Test1", 1, LogType::ボス);
			EventLog::Add("Test2", 2, LogType::依頼);
			EventLog::Add("Test3", 3, LogType::投資);
			EventLog::Add("Test4", 4, LogType::探索);
			EventLog::Add("Test5", 15, LogType::探索);
			EventLog::Add("Test6", 126, LogType::探索);
		}

		void Update()
		{
			SetPos(LLog::ウィンドウ, false, true, false);
			固定縦 = 40;
		}
	};
}