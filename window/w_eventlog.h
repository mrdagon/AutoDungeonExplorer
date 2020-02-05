//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[4][a]

	/*イベントログウィンドウ*/
	class W_EventLog : public WindowBox
	{
	public:

		std::vector<GUI_Tab> タブ;
		
		int 現在タブ = 0;

		void init()
		{
			種類 = WindowType::EventLog;
			名前 = "ログ";
			略記 = "ログ";
			アイコン = IconType::ログ;
			横幅 = 300;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
			固定縦 = 50;


			タブ.emplace_back(現在タブ, 0,IconType::ヘルプ, "a" );
			タブ.emplace_back(現在タブ, 1, IconType::ヘルプ, "b");
			タブ.emplace_back(現在タブ, 2, IconType::ヘルプ, "c");
			タブ.emplace_back(現在タブ, 3, IconType::ヘルプ, "d");

			タブ[0].SetHelp( "全部表示");
			タブ[1].SetHelp("ギルドA");
			タブ[2].SetHelp("ギルドB");
			タブ[3].SetHelp("ギルドC");

			for (int a = 0; a < 4; a++)
			{
				gui_objects.push_back(&タブ[a]);
			}

			//EventLog
			EventLog::Add(1, 1, IconType::ヘルプ, "てすとだよ～");
			EventLog::Add(2, 13, IconType::ログ, "てすとだよ～");
			EventLog::Add(2, 113, IconType::依頼, "てすとだよ～");
			EventLog::Add(3, 113, IconType::求人, "てすとだよ～");
			EventLog::Add(2, 113, IconType::依頼, "てすとだよ～");
			EventLog::Add(3, 113, IconType::求人, "てすとだよ～");
			EventLog::Add(2, 113, IconType::依頼, "てすとだよ～");
			EventLog::Add(3, 113, IconType::求人, "てすとだよ～");
			EventLog::Add(2, 113, IconType::依頼, "てすとだよ～");
			EventLog::Add(3, 113, IconType::求人, "てすとだよ～");
			EventLog::Add(2, 113, IconType::依頼, "てすとだよ～");
			EventLog::Add(3, 113, IconType::求人, "てすとだよ～");
			EventLog::Add(2, 113, IconType::依頼, "てすとだよ～");
			EventLog::Add(3, 113, IconType::求人, "てすとだよ～");

		}

		void GUI_init()
		{
			タブ[0].位置 = { LV(0) ,         LV(1) ,LV(2) ,LV(3) };
			タブ[1].位置 = { LV(0) + LV(4)  ,LV(1) ,LV(2) ,LV(3) };
			タブ[2].位置 = { LV(0) + LV(4)*2,LV(1) ,LV(2) ,LV(3) };
			タブ[3].位置 = { LV(0) + LV(4)*3,LV(1) ,LV(2) ,LV(3) };
		}

		void 派生Draw()
		{
			GUI_init();

			for (auto& it : タブ)
			{
				it.Draw();
			}

			MSystem::DrawWindow({ LV(0), LV(5) }, LV(6), LV(7),12);

			描画範囲(true);//以下非固定

			int yy = 0;
			int scr_max = 0;
			int day = -1;
			for (int a = (int)EventLog::logs.size()-1; a >= 0 ; a--)
			{
				if (現在タブ != 0 && EventLog::logs[a].ギルド != 現在タブ) { continue; }

				if (EventLog::logs[a].日付 != day)
				{
					//日付
					MSystem::DrawBox({ LV(10),LV(11) + yy }, LV(12), LV(13), { LV(26),LV(27),LV(28) });
					MFont::メイリオ小.DrawBold({ LV(14),LV(15) + yy }, Color::White, Color::Black, { EventLog::logs[a].日付/336+1,"年 ",(EventLog::logs[a].日付/28)%12+1,"月 ",EventLog::logs[a].日付%28+1,"日" });
					yy += LV(16);					
				}
				day = EventLog::logs[a].日付;

				//メッセージ
				MSystem::DrawBox({LV(17),LV(18)+yy},LV(19),LV(20), { LV(29),LV(30),LV(30) });
				MIcon::アイコン[EventLog::logs[a].種類].DrawRotate({ LV(21),LV(22)+yy }, 2, 0);
				MFont::メイリオ小.DrawBold({ LV(23),LV(24) + yy }, Color::White, Color::Black, EventLog::logs[a].メッセージ);
				yy += LV(25);
			}
			scr_max = yy;

			縦内部幅 = std::max(100, scr_max + 固定縦 + 10);

		}

		bool 派生操作()
		{
			for (auto& it : タブ)
			{
				it.操作チェック(座標.x,座標.y + タイトル枠高さ);
			}

			//固定にかかってる部分は操作等不可
			//if (Input::mouse.y - 座標.y - タイトル枠高さ < 固定縦)
			//{
			//	break;
			//}

			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}