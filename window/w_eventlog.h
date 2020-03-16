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
		EnumArray<IconType,LogType> 種類アイコン;
		
		int 現在タブ = 0;

		void init()
		{
			種類 = WindowType::EventLog;
			名前 = "ログ";
			略記 = "ログ";
			アイコン = IconType::ログ;
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
			固定縦 = 50;

			種類アイコン[LogType::重要] = IconType::星;
			種類アイコン[LogType::経営] = IconType::戦略;
			種類アイコン[LogType::人事] = IconType::求人;
			種類アイコン[LogType::製造] = IconType::ハンマー;
			種類アイコン[LogType::探索] = IconType::迷宮;


			タブ.emplace_back(現在タブ, 0, IconType::ログ, "全て" );
			タブ.emplace_back(現在タブ, 1, 種類アイコン[LogType::重要], "重要");
			タブ.emplace_back(現在タブ, 2, 種類アイコン[LogType::経営], "経営");
			タブ.emplace_back(現在タブ, 3, 種類アイコン[LogType::人事], "人事");
			タブ.emplace_back(現在タブ, 4, 種類アイコン[LogType::探索], "探索");
			タブ.emplace_back(現在タブ, 5, 種類アイコン[LogType::製造], "鍛冶");

			タブ[0].SetHelp("全ログ");
			タブ[1].SetHelp("重要なログ");
			タブ[2].SetHelp("経営関連のログ");//雇用、経営戦術使用
			タブ[3].SetHelp("冒険関連のログ");//ボス討伐/発見、地図発見

			for (int a = 0; a < 4; a++)
			{
				gui_objects.push_back(&タブ[a]);
			}

			//EventLog
			EventLog::Add(0, 0, LogDetailType::クエスト受注);
			EventLog::Add(0, 1, LogDetailType::部門Lv上昇, 0);
			EventLog::Add(0, 2, LogDetailType::経営戦術使用, 0);
			EventLog::Add(0, 2, LogDetailType::雇用, 0);
			EventLog::Add(0, 2, LogDetailType::再募集);
			EventLog::Add(0, 5, LogDetailType::地図発見, 0);
			EventLog::Add(0, 6, LogDetailType::ボス発見, 0);
			EventLog::Add(0, 6, LogDetailType::ボス討伐, 0);
			EventLog::Add(0, 8, LogDetailType::新装備開発, 0);
			EventLog::Add(0, 100, LogDetailType::レア装備製造, 0);
		}

		void GUI_init()
		{
			タブ[0].位置 = { LV(0) ,         LV(1) ,LV(2) ,LV(3) };
			タブ[1].位置 = { LV(0) + LV(4)  ,LV(1) ,LV(2) ,LV(3) };
			タブ[2].位置 = { LV(0) + LV(4)*2,LV(1) ,LV(2) ,LV(3) };
			タブ[3].位置 = { LV(0) + LV(4)*3,LV(1) ,LV(2) ,LV(3) };
			タブ[4].位置 = { LV(0) + LV(4)*4,LV(1) ,LV(2) ,LV(3) };
			タブ[5].位置 = { LV(0) + LV(4)*5,LV(1) ,LV(2) ,LV(3) };
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

			int xx = 0;
			int yy = 5;
			int scr_max = 0;
			int day = -1;

			for (int a = (int)EventLog::logs.size()-1; a >= 0 ; a--)
			{
				//タブ0なら全て表示
				if (現在タブ != 0 && (int)EventLog::logs[a].系統 + 1 != 現在タブ) { continue; }

				if (EventLog::logs[a].日付 != day)
				{
					//日付
					MSystem::DrawWindow({ LV(10),LV(11) + yy }, LV(12), LV(13), LV(26));
					//MSystem::DrawBox({ LV(10),LV(11) + yy }, LV(12), LV(13), { LV(26),LV(27),LV(28) });
					MFont::Bメイリオ小.DrawBold({ LV(14),LV(15) + yy }, Color::White, Color::Black, { EventLog::logs[a].日付 + 1," 日目" },true);
					yy += LV(16);					
				}
				day = EventLog::logs[a].日付;

				//メッセージ
				MSystem::DrawWindow({ LV(17),LV(18) + yy }, LV(19), LV(20), LV(26));
				MIcon::アイコン[種類アイコン[EventLog::logs[a].系統]].DrawRotate({ LV(21),LV(22) + yy }, 1, 0);

				int id = EventLog::logs[a].参照ID;
				std::string str;

				switch (EventLog::logs[a].種類)
				{
				case LogDetailType::クエスト受注:
					str = "クエストを受注しました";
					break;
				case LogDetailType::部門Lv上昇:
					MIcon::アイコン[IconType::依頼].DrawRotate({ LV(30),LV(31) + yy }, 2, 0);
					str = "部門がレベルアップ";
					xx = LV(32);
					break;
				case LogDetailType::経営戦術使用:
					//経営戦術名
					MIcon::アイコン[Management::data[id].アイコン].DrawRotate({LV(30),LV(31) + yy }, 2, 0);
					str = Management::data[id].名前;
					str += "を使用";
					xx = LV(32);
					break;
				case LogDetailType::雇用:
					//キャラアイコン
					MUnit::ユニット[Warker::data[id].見た目][1]->DrawRotate({ LV(30) , LV(31) + yy }, 2, 0);
					str = Warker::data[id].名前;
					str += "を雇用";
					xx = LV(32);
					break;
				case LogDetailType::再募集:
					str = "新たな人員を募集";
					break;
				case LogDetailType::地図発見:
					//ダンジョンアイコンと名前
					MIcon::ダンジョン[Dungeon::data[id].種類].DrawRotate({LV(30),LV(31) + yy },1,0);
					str = Dungeon::data[id].名前;
					str += "を発見";
					xx = LV(32);
					break;
				case LogDetailType::ボス発見:
					//魔物アイコン
					MIcon::ダンジョン[Dungeon::data[id].種類].DrawRotate({ LV(30),LV(31) + yy }, 1, 0);
					str = Dungeon::data[id].名前;
					str += "の主を発見";
					xx = LV(32);
					break;
				case LogDetailType::ボス討伐:
					//魔物アイコン
					MIcon::ダンジョン[Dungeon::data[id].種類].DrawRotate({ LV(30),LV(31) + yy }, 1, 0);
					str = Dungeon::data[id].名前;
					str += "の主を討伐";
					xx = LV(32);
					break;
				case LogDetailType::新装備開発:
					//装備品のアイコン
					MIcon::アイテム[Item::data[id].見た目].DrawRotate({ LV(30) , LV(31) + yy }, 1, 0);
					str = Item::data[id].名前;
					str += "を初めて製造";
					xx = LV(32);
					break;
				case LogDetailType::レア装備製造:
					//装備アイコン
					MIcon::アイテム[Item::data[id].見た目].DrawRotate({ LV(30) , LV(31) +yy},1,0);
					str = Item::data[id].名前;
					str += "を製造";
					xx = LV(32);
					break;
				}

				MFont::Bメイリオ中.DrawBold({ LV(23) + xx ,LV(24) + yy }, Color::White, Color::Black, str);
				yy += LV(25);
				xx = 0;
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
#undef LV
#undef LV2
#undef LV4
}