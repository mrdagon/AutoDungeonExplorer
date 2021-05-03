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
		EnumArray<std::string, WindowType> Window_名前;//ウィンドウタイトル
		EnumArray<std::string, WindowType> Window_略記;//ボタン用の略記
		EnumArray<std::string, WindowType> Window_ヘルプ;//ウィンドウのヘルプとポップアップ時のテキスト

		EnumArray<std::string, StatusType> ステータス;

		std::string タイトル = "だいじぇすと　ダンジョン　 0.2β";
		const wchar_t* アンケURL = L"https://forms.gle/BBBcruGYX8PTRZ9M9";

		////Save data
		const std::string Save_コンフィグファイル名 = "config.sav";
		const std::string Save_システムファイル名 = "system.sav";

		std::string 難易度[3] = { "ノーマル" , "ハードコア" , "デスマーチ" };

		////Config Window
		std::string Config_決定 = "決定";
		std::string Config_キャンセル = "キャンセル";
		std::string Config_ウィンドウモード = "画面モード";
		std::string Config_解像度 = "解像度";
		std::string Config_解像度X倍 = "4Kモード";

		std::string Config_音楽 = "音楽";
		std::string Config_効果音 = "効果音";

		std::string Config_ボス戦速度 = "ボス戦時";
		std::string Config_夜間加速 = "夜の時間";
		std::string Config_超加速 = "速度上限";
		std::string Config_フォント種 = "フォント";

		std::string Config_ウィンドウモード設定[2] = { "フル" , "ウィンドウ" };
		std::string Config_4Kモード[3] = { "" , "通常" , "表示２倍" };
		std::string Config_ボス戦速度_設定[2] = { "等速で見る" , "倍速のまま" , };
		std::string Config_夜間加速_設定[2] = { "４倍速" , "そのまま" };
		std::string Config_超加速_設定[2] = { "64倍速" , "16倍速" };
		std::string Config_フォント設定[2] = { "ドット" , "なめらか" };

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

		std::string Party_スキル未予約 = "スキル";
		std::string Party_スキル予約 = "予約済み";


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
		std::string Help_ステータス[(int)StatusType::COUNT] = {"生命","筋力","技力","知力","物防","魔防","命中","回避" , "会心" };
		//dungeonHelp、ASkillSubまだ

		//tool barのヘルプ色々

		//テキストデータ読み込み
		bool Load()
		{
			Window_名前[WindowType::Dungeon] = "ダンジョン一覧";
			Window_略記[WindowType::Dungeon] = "迷宮";
			Window_ヘルプ[WindowType::Dungeon] = "ダンジョン一覧：\nパーティにドラッグ＆ドロップで探索先を変更";

			Window_名前[WindowType::EventLog] = "ログ";
			Window_略記[WindowType::EventLog] = "ログ";
			Window_ヘルプ[WindowType::EventLog] = "ログ一覧：\n探索記録の確認";

			Window_名前[WindowType::Item] = "遺物一覧";
			Window_略記[WindowType::Item] = "遺物";
			Window_ヘルプ[WindowType::Item] = "遺物一覧：\n探索者にドラッグ＆ドロップで装備変更";

			Window_名前[WindowType::Management] = "設備投資";
			Window_略記[WindowType::Management] = "設備";
			Window_ヘルプ[WindowType::Management] = "設備投資：\n資金を消費して街の施設を改良\n様々なボーナスを獲得";

			Window_名前[WindowType::Material] = "素材一覧";
			Window_略記[WindowType::Material] = "素材";
			Window_ヘルプ[WindowType::Material] = "素材一覧：\n装備強化に必要な素材の所持数";

			Window_名前[WindowType::Party] = "探索者/パーティ編成";
			Window_略記[WindowType::Party] = "編成";
			Window_ヘルプ[WindowType::Party] = "パーティ編成：\n探索パーティを編成\n装備やスキルの変更\n探索指示や探索先の変更";

			Window_名前[WindowType::Quest] = "クエスト一覧";
			Window_略記[WindowType::Quest] = "依頼";
			Window_ヘルプ[WindowType::Quest] = "クエスト一覧：\nクエストの達成状況や報酬の確認";

			Window_名前[WindowType::Recruit] = "求人";
			Window_略記[WindowType::Recruit] = "求人";
			Window_ヘルプ[WindowType::Recruit] = "";

			Window_名前[WindowType::Config] = "設定変更";
			Window_略記[WindowType::Config] = "設定";
			Window_ヘルプ[WindowType::Config] = "各種設定を変更";

			Window_名前[WindowType::Skilltree] = "スキル";
			Window_略記[WindowType::Skilltree] = "技術";
			Window_ヘルプ[WindowType::Skilltree] = "スキルの習得と確認";

			Window_名前[WindowType::Recruit] = "探索者の登録";
			Window_略記[WindowType::Recruit] = "登録";
			Window_ヘルプ[WindowType::Recruit] = "";

			Window_名前[WindowType::Skilltree] = "アクティブスキル／パッシブスキル";
			Window_略記[WindowType::Skilltree] = "スキル";
			Window_ヘルプ[WindowType::Skilltree] = "";

			Window_名前[WindowType::Newgame] = "難易度選択";
			Window_略記[WindowType::Newgame] = "";
			Window_ヘルプ[WindowType::Newgame] = "";

			Window_名前[WindowType::Continue] = "記録を選択して下さい";
			Window_略記[WindowType::Continue] = "";
			Window_ヘルプ[WindowType::Continue] = "";

			Window_名前[WindowType::Credit] = "クレジット";
			Window_略記[WindowType::Credit] = "";
			Window_ヘルプ[WindowType::Credit] = "";

			Window_名前[WindowType::Title] = "保存して終了";
			Window_略記[WindowType::Title] = "";
			Window_ヘルプ[WindowType::Title] = "タイトル画面に戻りますか？";

			Window_名前[WindowType::Help] = "ヘルプ";
			Window_略記[WindowType::Help] = "";
			Window_ヘルプ[WindowType::Help] = "未実装です";

			Window_名前[WindowType::Popup] = "確認";
			Window_略記[WindowType::Popup] = "";
			Window_ヘルプ[WindowType::Popup] = "";

			Window_名前[WindowType::Delete] = "除名";
			Window_略記[WindowType::Delete] = "";
			Window_ヘルプ[WindowType::Delete] = "本当に除名しますか？\n※除名した探索者は戻せません";

			ステータス[StatusType::HP] = "HP";
			ステータス[StatusType::力] = "力";
			ステータス[StatusType::技] = "技";
			ステータス[StatusType::知] = "知";
			ステータス[StatusType::物防] = "防御";
			ステータス[StatusType::魔防] = "抵抗";
			ステータス[StatusType::命中] = "命中";
			ステータス[StatusType::回避] = "回避";
			ステータス[StatusType::会心] = "会心";

			return true;
		}

	}

	//ポップアップヘルプのテキスト
	namespace TH
	{
		//各ウィンドウのヘルプ
		namespace Bar
		{
			std::string 日付 = "経過日数と現在時刻";
			std::string 停止 = "一時停止ON/OFF\n右クリックでショートカット操作";
			std::string 速度変更 = "時間経過スピードを変更";
			std::string ヘルプ = "ヘルプを閲覧する(未実装)";
			std::string 設定 = "各種設定の変更";
			std::string 終了 = "タイトルへ戻る";
		}


		namespace Party
		{
			std::string 空きメンバー = "探索者をドロップで配置";
			std::string 登録 = "探索者を無料で登録";
			std::string 除名 = "ドロップで探索者を除名";
			std::string スキルボタン = "使用スキルの変更\nスキル習得と習得予約";
			EnumArray<std::string, OrderType> 探索指示;
		}

		namespace Dungeon
		{
			std::string ボス表示切り替え = "ボス/雑魚 表示切り替え";
			std::string 未発見フロア = "未発見フロア";
		}

		namespace Management
		{
			std::string 街Lv = "街Lvが上昇すると投資プランの種類と上限Lvが増加\n投資を実行すると街Lvが上昇";
			std::string 資金 = "所持資金/消費資金";
		}

		namespace Quest
		{
			std::string 表示ボタン[3];//無し？
		}

		namespace Log
		{
			std::string 表示ボタン[4];//無し？
		}

		//スキル：

		bool Load()
		{
			Party::探索指示[OrderType::なし] = "探索指示：\n探索先を自分で指定";
			Party::探索指示[OrderType::お宝探して] = "探索指示：\n未発見の財宝がある階層を探索";
			Party::探索指示[OrderType::ガンガン進め] = "探索指示：\n一番深い階層を探索";
			Party::探索指示[OrderType::命大事に] = "探索指示：\n全滅したら一つ下のフロアを探索";
			Party::探索指示[OrderType::強敵探して] = "探索指示：\n未討伐のボスがいるフロアを探索";

			Quest::表示ボタン[0] = "";
			Quest::表示ボタン[1] = "";
			Quest::表示ボタン[2] = "";

			Log::表示ボタン[0] = "";
			Log::表示ボタン[1] = "";
			Log::表示ボタン[2] = "";
			Log::表示ボタン[3] = "";
			

			return true;
		}
	}

}