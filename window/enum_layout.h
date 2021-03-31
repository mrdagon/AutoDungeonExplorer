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
		COUNT,
		PAGE = (int)UIPage::アイテム
	};

	enum class LDungeon
	{
		ウィンドウ,
		タブ,
		内枠,
		COUNT,
		PAGE = (int)UIPage::ダンジョン
	};

	enum class LParty
	{
		ウィンドウ,//全体ウィンドウ幅
		パーティ_ウィンドウ,
		控え枠_ウィンドウ,
		控え枠_控え探索者,//除名は登録と除名も
		COUNT,
		PAGE = (int)UIPage::パーティ編成
	};

	enum class LBattle
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::パーティ探索
	};

	enum class LManagement
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::投資
	};

	enum class LMaterial
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::素材
	};

	enum class LQuest
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::クエスト
	};

	enum class LLog
	{
		ウィンドウ,
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

		COUNT,
		PAGE = (int)UIPage::求人
	};

	enum class LSkill
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::スキルツリー
	};

	enum class LHExplorer
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::Helpエクスプローラ
	};

	enum class LHMonster
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::Helpモンスター
	};

	enum class LHSkill
	{
		ウィンドウ,
		COUNT,
		PAGE = (int)UIPage::Helpスキル
	};


}