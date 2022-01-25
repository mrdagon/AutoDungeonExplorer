//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	enum class UIPage
	{
		基本,//common
		タイトル,//title
		コンフィグ,//config
		ツールバー,//main
		//●Window
		アイテム,//item
		ダンジョン,//dungeon
		パーティ編成,//party_town
		パーティ探索,//party_dungeon
		投資,//invest
		素材,//material
		クエスト,//quest
		ログ,//log
		//●サブウィンドウ
		求人,//recruit
		スキルツリー,//skill
		//●ヘルプ専用
		Helpエクスプローラ,//h_explorer
		Helpモンスター,//h_monster
		Helpスキル,//h_skill
		COUNT
	};

	//各種レイアウト参照用の列挙型

	enum class L基本
	{
		ポップアップ_ウィンドウ,
		ポップアップ_説明,
		ポップアップ_はい,
		ポップアップ_いいえ,
		COUNT,
		PAGE = (int)UIPage::基本
	};
	
	enum class LTitle
	{
		題字,
		ボタン,
		ライセンス,

		始めから_ウィンドウ,
		始めから_ボタン,
		始めから_説明枠,
		始めから_開始ボタン,

		続きから_ウィンドウ,
		続きから_セーブデータ枠,
		続きから_階層,
		続きから_日数,
		続きから_難易度,
		続きから_パーティ,
		続きから_削除,

		クレジット_ウィンドウ,
		クレジット_説明枠,
		COUNT,
		PAGE = (int)UIPage::タイトル
	};

	enum class LConfig
	{
		ウィンドウ,
		決定_キャンセル,
		設定ボタン,
		設定アイコン,//子項目４つ
		設定項目名,
		設定数値,
		設定増減,
		COUNT,
		PAGE = (int)UIPage::コンフィグ
	};

	enum class LToolBar
	{
		ツールバー_全体,
		ツールバー_ウィンドウボタン,
		ツールバー_速度ボタン,
		ツールバー_その他ボタン,
		ツールバー_日付,
		ツールバー_日付文字,
		ツールバー_時刻,
		ツールバー_時刻文字,
		COUNT,
		PAGE = (int)UIPage::ツールバー
	};

	enum class LItem
	{
		ウィンドウ,
		内枠,
		タブ,
		アイテム,
		アイテム数,
		アイテムレア度,
		ヘルプ枠,
		Hアイコン,
		H名前,
		H説明,
		Hステータス,
		Hパッシブ,
		Hレシピ枠,
		Hレシピアイコン,
		Hレシピ数,
		HレシピLv,
		COUNT,
		PAGE = (int)UIPage::アイテム
	};

	enum class LDungeon
	{
		ウィンドウ,
		タブ,
		内枠,
		フロア枠,
		フロアアイコン,
		魔物Lv,
		探索率,
		雑魚ボスボタン,
		モンスター,
		財宝,
		ヘルプ枠,
		Hアイコン,
		H名前,
		H説明,
		H探索率,
		Hモンスター,
		H財宝,
		地図ボスマーカー,
		種別テキスト,
		COUNT,
		PAGE = (int)UIPage::ダンジョン
	};

	enum class LParty
	{
		ウィンドウ,//全体ウィンドウ幅
		パーティ枠,
		控え枠,
		控え探索者,//除名は登録と除名も
		探索先枠,
		探索者枠,

		控えドット,
		控えLv,

		探索者ドット,
		探索者Lv,
		探索者経験値,
		探索者装備,
		探索者スキル,

		探索先変更三角,
		探索先フロア,
		探索先探索度,
		探索先ボス,
		探索先指示,
		探索先財宝数,
		探索先階数,

		探索者スキルボタン,
		探索先内枠,

		ボス地図マーカー,

		COUNT,
		PAGE = (int)UIPage::パーティ編成
	};

	enum class LBattle
	{
		背景,
		味方A,
		味方B,
		味方C,
		味方D,
		味方E,
		敵A,
		敵B,
		敵C,
		敵D,
		敵E,
		敵F,
		ボス,
		ライフバー,
		行動バー,
		オブジェ,
		リザルト枠,
		リザルトキャラ,
		リザルト経験値バー,
		リザルト演出文字,
		リザルト入手品,
		リザルト入手品文字,

		ヘルプ枠,
		Hメンバー,
		H項目名,
		H数値,

		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::パーティ探索
	};

	enum class LManagement
	{
		ウィンドウ,
		素材アイコン,
		素材ランク,
		素材必要数,
		素材枠,
		街Lv枠,
		街Lv数値,
		街グループ枠,
		プラン枠,
		プランアイコン,
		プランLv,
		プラン名前,
		プラン費用,
		ヘルプ枠,
		Hアイコン,
		H名前,
		H説明,
		H消費資金,
		HLv,

		COUNT,
		PAGE = (int)UIPage::投資
	};

	enum class LMaterial
	{
		ウィンドウ,
		素材枠,
		素材ランク,
		素材所持数,
		内枠,
		ヘルプ枠,
		Hアイコン,
		Hランク,
		H名前,
		H説明,
		H価格,
		H所持数,
		H必要メンバー,
		素材ランク文字,
		COUNT,
		PAGE = (int)UIPage::素材
	};

	enum class LQuest
	{
		ウィンドウ,
		依頼枠,
		依頼者,
		クエスト名,
		フロア,
		ステータス,
		表示ボタン,
		ヘルプ枠,
		Hアイコン,
		H名前,
		H依頼人,
		H依頼人名前,
		H説明,
		H受注状況,
		H報酬説明,
		H受注条件,
		COUNT,
		PAGE = (int)UIPage::クエスト
	};

	enum class LLog
	{
		ウィンドウ,
		表示ボタン,
		ログ枠,
		ログアイコン,
		ログ文章,
		ログ日付,
		COUNT,
		PAGE = (int)UIPage::ログ
	};

	enum class LReqruit
	{
		ウィンドウ,
		職一覧枠,
		説明枠,
		名前変更ボタン,
		ランダムボタン,
		登録ボタン,

		名前枠,

		職業名,
		装備アイコン,
		職業概要,
		分割線,
		職業説明文,
		職業イラスト,

		職一覧,
		職一覧アイコン,
		職一覧名前,

		種族一覧,
		種族説明文,

		ステータス,
		ステータス職業,
		ステータス種族,

		COUNT,
		PAGE = (int)UIPage::求人
	};

	enum class LSkill
	{
		ウィンドウ,
		探索者,
		習得スキル枠,
		装備スキル枠,
		装備Aスキル,
		予約スキル枠,
		キースキル,
		Pスキル,
		Aスキル,
		確定ボタン,
		キャンセルボタン,
		リセットボタン,
		予約スキル,

		探索者ドット,
		探索者立ち絵,
		探索者名前,
		探索者Lv,
		探索者スキルP,
		スキルLv,
		キースキル名前,
		装備スキルLv,
		装備スキルスロット,

		探索者職業名,
		スキルコンボボックス,
		スキルコンボアイテム,
		前後ボタン,

		COUNT,
		PAGE = (int)UIPage::スキルツリー
	};

	enum class LHExplorer
	{
		ヘルプ枠,
		ドット,
		名前,
		経験値バー,
		Lv,
		装備,
		Aスキル,
		習得キースキル,
		習得Aスキル,
		習得Pスキル,
		職業,
		基礎ステータス,
		COUNT,
		PAGE = (int)UIPage::Helpエクスプローラ
	};

	enum class LHMonster
	{
		ヘルプ枠,
		ドット,
		名前,
		素材,
		ボスマーク,
		ボスドロップ,
		基礎ステータス,
		アクティブスキル,
		パッシブスキル,
		Lv,
		COUNT,
		PAGE = (int)UIPage::Helpモンスター
	};

	enum class LHSkill
	{
		Aヘルプ枠,
		Pヘルプ枠,
		Cアイコン,
		C名前,
		ACクールタイム,
		AC説明,
		PCタイミング,
		PC説明,
		Aアイコン,
		A名前,
		A説明,
		Aクールタイム,
		A隊列,
		Pアイコン,
		P名前,
		P説明,
		Pタイミング,
		COUNT,
		PAGE = (int)UIPage::Helpスキル
	};

}