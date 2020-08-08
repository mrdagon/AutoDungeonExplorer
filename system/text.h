//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#include <Windows.h>

#undef min
#undef max

namespace SDX_ADE
{
	//各種テキスト
	//各スキル、装備、投資、ジョブ、モンスター、ダンジョン、クエストはエディタでデータ作成

	//各種UIのタイトル、説明文などはここで読込
	namespace TX
	{
		EnumArray<std::string, WindowType> Window_名前;
		EnumArray<std::string, WindowType> Window_略記;
		EnumArray<std::string, WindowType> Window_ヘルプ;

		std::string タイトル = "おーと だんじょん えくすぷろーら ＜仮＞ 0.1 β";
		const wchar_t* アンケURL = L"https://forms.gle/BBBcruGYX8PTRZ9M9";

		////Save data
		const std::string Save_コンフィグファイル名 = "config.sav";
		const std::string Save_システムファイル名 = "system.sav";

		////Config Window
		std::string Config_決定 = "決定";
		std::string Config_キャンセル = "キャンセル";
		std::string Config_音楽 = "音楽";
		std::string Config_効果音 = "効果音";
		std::string Config_解像度 = "解像度";
		std::string Config_ウィンドウモード = "画面モード";
		std::string Config_装備更新 = "自動装備更新";
		std::string Config_ボス戦速度 = "ボス戦時";
		std::string Config_夜間加速 = "夜の時間";
		std::string Config_スキル習得停止 = "スキル習得時";
		std::string Config_超加速 = "速度上限";
		std::string Config_ヘルプ詳細 = "スキル詳細";

		std::string Config_ウィンドウモード設定[4] = { "ウィンドウ" , "等倍フル" , "２倍フル"  , "４倍フル" };

		std::string Config_装備更新_設定[2] = { "ON" , "OFF" };
		std::string Config_ボス戦速度_設定[2] = { "等速" , "そのまま"};
		std::string Config_夜間加速_設定[2] = { "４倍速" , "そのまま" };
		std::string Config_スキル習得停止_設定[2] = { "停止する" , "停止しない" };
		std::string Config_超加速_設定[2] = { "16倍速" , "64倍速" };
		std::string Config_ヘルプ詳細_設定[2] = { "表示する" , "表示しない" };

		////Dungeon Window
		std::string Dungeon_タブ名[5] = { "I層","II層","III層","IV層","V層" };
		std::string Dungeon_タブヘルプ[5];
		std::string Dungeon_捜索 = "捜索中";
		std::string Dungeon_発見 = " 発見";
		std::string Dungeon_討伐 = " 討伐";

		////Log Window
		std::string Log_タブ名[6] = { "全て" , "重要" , "経営" , "人事" , "探索" , "製造"};
		std::string Log_タブヘルプ[6] = { "" , "" , "" , "" , "" , "" };

		std::string Log_日付 = " 日目";
		std::string Log_受注 = "を受注";
		std::string Log_完了 = "を完了";
		std::string Log_部門Lv = "部門がLvUP";
		std::string Log_技術Lv = "技術がLvUP";
		std::string Log_投資 = "を使用";
		std::string Log_雇用 = "が入団";
		std::string Log_募集 = "新たに人員を募集";
		std::string Log_地図 = "を発見";
		std::string Log_ボス発見 = "のボスを発見";
		std::string Log_ボス討伐 = "のボスを討伐";
		std::string Log_初製造 = "を初めて製造";
		std::string Log_レア製造 = "を製造";

		//Factory Window
		EnumArray<std::string, CraftType> Factory_部門名;
		EnumArray<std::string, CraftType> Factory_部門説明;
		std::string Factory_ヘルプ = "製造力と製造人員\nドラッグ＆ドロップで配置転換";

		//Guild Window
		std::string Guild_ギルマス[2] = { "ギルド名","ギルマス名" };
		std::string Guild_項目[10] = { "団員","名声","資金","販売" ,"売上" ,"製造" ,"素材" ,"地図" ,"討伐" ,"全滅" };
		std::string Guild_単位[10] = { "人" ,"点" ,"Ｇ" ,"個" ,"Ｇ" ,"個" ,"個" ,"枚" ,"体" ,"回" };

		//Item Window
		std::string Item_タブヘルプ[10] = {"全装備","剣","槌","槍" , "弓" , "魔杖" , "神杖" , "重鎧" , "軽鎧" , "外套"};

		//Management Window
		std::string Manage_タブヘルプ[4] = { "経営部門の投資Lv" , "人事部門の投資Lv" , "製造部門の投資Lv" , "探索部門の投資Lv"};
		std::string Manage_お金 = "現在の資金と消費資金";

		//Party Window		
		//後で調整
		std::string Party_探索方針 = "クリックでボスと戦うか切り替え";

		std::string Party_ボス回避 = "ボス\n回避";
		std::string Party_ボス討伐 = "ボス\n討伐";

		//スキルツリー
		

		//Recruit Window
		std::string Recruit_採用 = "！採用！";
		std::string Recruit_抽選 = "ランダム";

		//Tool Bar
		std::string Tool_日付 = " 日";
		std::string Tool_人口 = " 人/日";
		std::string Tool_ヘルプ = "ヘルプ";
		std::string Tool_停止 = "停止";
		std::string Tool_速度 = "速度";
		std::string Tool_設定 = "設定";

		std::string Tool_タイトル = "終了";

		std::string Tool_待機中 = "準備中…";
		std::string TooL_活動中 = "活動中！";

		std::string Tool_Help日付 = "クエスト開始からの日数";
		std::string Tool_Help時刻 = "現在の時刻";
		std::string Tool_Help人口 = "一日の客数";
		std::string Tool_Help資金 = "現在の総資金";
		std::string Tool_Helpヘルプ = "操作やゲームのヘルプ[実装中]";
		std::string Tool_Help停止 = "クリックで一時停止/再開";
		std::string Tool_Help速度 = "クリックでゲーム速度を変更";
		std::string Tool_Help設定 = "クリックで設定ウィンドウを開く";
		std::string Tool_Helpタイトル = "アンケートページを開く";

		//Help Window
		std::string Help_ステータス[8] = {"HP","STR","DEX","INT","物防","魔防","命中","回避"};
		//dungeonHelp、ASkillSubまだ

		//tool barのヘルプ色々

		//テキストデータ読み込み
		bool Load()
		{
			Window_名前[WindowType::Dungeon] = "ダンジョン";
			Window_略記[WindowType::Dungeon] = "迷宮";
			Window_ヘルプ[WindowType::Dungeon] = "発見済みのダンジョンです\nパーティにドラッグ＆ドロップで探索先を変更する";

			Window_名前[WindowType::EventLog] = "イベントログ";
			Window_略記[WindowType::EventLog] = "ログ";
			Window_ヘルプ[WindowType::EventLog] = "ゲームのログを確認";

			Window_名前[WindowType::Factory] = "装備製造";
			Window_略記[WindowType::Factory] = "製造";
			Window_ヘルプ[WindowType::Factory] = "各部門にギルメンをドロップ配置\n素材から装備品を作る";

			Window_名前[WindowType::Guild] = "ギルド情報";
			Window_略記[WindowType::Guild] = "情報";
			Window_ヘルプ[WindowType::Guild] = "ギルドの各種データを確認";

			Window_名前[WindowType::Item] = "装備品";
			Window_略記[WindowType::Item] = "装備";
			Window_ヘルプ[WindowType::Item] = "装備品の在庫表示\nギルメンにドラッグ＆ドロップで装備変更";

			Window_名前[WindowType::Management] = "部門投資";
			Window_略記[WindowType::Management] = "投資";
			Window_ヘルプ[WindowType::Management] = "Gを消費して様々なボーナスを獲得";

			Window_名前[WindowType::Material] = "素材";
			Window_略記[WindowType::Material] = "素材";
			Window_ヘルプ[WindowType::Material] = "装備製造に必要な素材の在庫を確認";

			Window_名前[WindowType::Party] = "ギルメン/探索パーティ";
			Window_略記[WindowType::Party] = "編成";
			Window_ヘルプ[WindowType::Party] = "ダンジョンを探索するパーティを編成\nドラッグ＆ドロップで入れ替え\n探索指示をクリックで変更";

			Window_名前[WindowType::Quest] = "クエスト";
			Window_略記[WindowType::Quest] = "依頼";
			Window_ヘルプ[WindowType::Quest] = "依頼と報酬を確認";

			Window_名前[WindowType::Recruit] = "求人";
			Window_略記[WindowType::Recruit] = "求人";
			Window_ヘルプ[WindowType::Recruit] = "入団志願者一覧\nパーティか製造にドラッグ＆ドロップで採用\nリロールクリックで再募集\n採用とリロールで人事ポイントを消費";

			Window_名前[WindowType::Config] = "設定変更";
			Window_略記[WindowType::Config] = "設定";
			Window_ヘルプ[WindowType::Config] = "各種設定を変更";

			Window_名前[WindowType::Skilltree] = "スキル";
			Window_略記[WindowType::Skilltree] = "技術";
			Window_ヘルプ[WindowType::Skilltree] = "スキルの習得と確認";

			Factory_部門名[CraftType::裁縫] = "裁縫";
			Factory_部門名[CraftType::鍛造] = "鍛造";
			Factory_部門名[CraftType::魔術] = "魔術";
			Factory_部門名[CraftType::木工] = "木工";

			Factory_部門説明[CraftType::裁縫] = "皮革を加工\n軽鎧、ローブを製造";
			Factory_部門説明[CraftType::鍛造] = "金属を加工\n斧、剣、重鎧を製造";
			Factory_部門説明[CraftType::魔術] = "骨材を加工\n魔杖、神杖を製造";
			Factory_部門説明[CraftType::木工] = "木材を加工\n盾、弓を製造";

			return true;
		}

	}
}