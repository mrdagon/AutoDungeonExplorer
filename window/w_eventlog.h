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
		};


	public:
		std::vector<GUI_Tab> タブ;
		EnumArray<IconType,LogType> 種類アイコン;
		
		//タブ

		int 現在タブ = 0;

		void Init()
		{
			タブ.clear();
			Set( WindowType::EventLog , IconType::ログ );
			SetPos(LLog::ウィンドウ, false, true, false);

			/*
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
			固定縦 = 50;
			*/

			種類アイコン[LogType::重要] = IconType::ランク;
			種類アイコン[LogType::経営] = IconType::情報;
			種類アイコン[LogType::人事] = IconType::求人;
			種類アイコン[LogType::製造] = IconType::製造;
			種類アイコン[LogType::探索] = IconType::迷宮;

			タブ.emplace_back(現在タブ, 0, IconType::ログ, TX::Log_タブ名[0] );
			タブ.emplace_back(現在タブ, 1, 種類アイコン[LogType::重要], TX::Log_タブ名[1] );
			タブ.emplace_back(現在タブ, 2, 種類アイコン[LogType::経営], TX::Log_タブ名[2] );
			タブ.emplace_back(現在タブ, 3, 種類アイコン[LogType::人事], TX::Log_タブ名[3] );
			タブ.emplace_back(現在タブ, 4, 種類アイコン[LogType::探索], TX::Log_タブ名[4] );
			タブ.emplace_back(現在タブ, 5, 種類アイコン[LogType::製造], TX::Log_タブ名[5] );

			for (int a = 0; a < 6; a++)
			{
				タブ[a].SetHelp( TX::Log_タブヘルプ[a]);
			}

			for (int a = 0; a < 6; a++)
			{
			}
		}

		void GUI_Update()
		{
		}

		void 派生Draw()
		{
			GUI_Update();

			for (auto& it : タブ)
			{
				it.Draw();
			}

			Reset描画範囲(true);//以下非固定

			int yy = 5;
			int scr_max = 0;
			int day = -1;

			for (int a = (int)EventLog::logs.size()-1; a >= 0 ; a--)
			{
				//タブ0なら全て表示
				if (現在タブ != 0 && (int)EventLog::logs[a].種類 + 1 != 現在タブ) { continue; }

				if (EventLog::logs[a].日付 != day)
				{
					//日付
					//MSystem::DrawWindow({ Lp(10),Lp(11) + yy }, Lp(12), Lp(13), Lp(26));
					//MFont::BSSize.DrawBold({ Lp(14),Lp(15) + yy }, Color::White, Color::Black, { EventLog::logs[a].日付 + 1, TX::Log_日付 },true);
					//yy += Lp(16);					
				}
				day = EventLog::logs[a].日付;

				//メッセージ
				//MSystem::DrawWindow({ Lp(17),Lp(18) + yy }, Lp(19), Lp(20), Lp(26));
				
				std::string str;

				switch (EventLog::logs[a].種類)
				{
				case LogType::人事:
					//ログタイプに合わせたアイコンで表示
					//テキストを表示
					break;
				}

				//MFont::BMSize.DrawBold({ Lp(23) + Lp(32) ,Lp(24) + yy }, Color::White, Color::Black, str);
				//yy += Lp(25);
			}
			scr_max = yy;

			縦内部幅 = std::max(100, scr_max + 固定縦 + 10);


		}

		bool 派生操作()
		{
			for (auto& it : タブ)
			{
				if (it.is表示 == true)
				{
					it.操作チェック(座標.x, 座標.y + タイトル枠高さ);
				}
			}

			return false;
		}

	};
}