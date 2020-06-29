﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
;
namespace SDX_BSC
{
	using namespace SDX;

	//◆画像、音声等
	//ユニット
	enum class UnitImageType
	{
		ゴブリン,
		青ゴブリン,
		犬,
		青犬,
		白猫,
		黒猫,
		兵士,
		赤兵士,
		青兵士,
		メイド,
		ハゲ,
		執事,
		王,
		青王,
		王妃,
		青王妃,
		赤王妃,
		小王子,
		小姫,
		王子,
		姫,
		ドワーフ,
		子ドワーフ,
		茶女性,
		青女性,
		金女性,
		緑女性,
		茶村人,
		金村人,
		金子供,
		三つ編み,
		少年,
		少女,
		緑防止,
		おっさん,
		半裸,
		青オーク,
		赤オーク,
		おばさん,
		おばあさん,
		おじいさん,
		勇者,
		闘士,
		弓士,
		剣聖,
		武術家,
		魔女,
		精霊,
		くの一,
		盗賊,
		レンジャー,
		妖術師,
		大魔導師,
		族長,
		空手家,
		戦士,
		戦士2,
		重装,
		柔術家,
		呪術師,
		暗殺者,
		傭兵,
		老兵,
		戦士3,
		騎士,
		司祭,
		スライム,
		赤スライム,
		狼,
		青狼,
		三頭犬,
		スケルトン,
		サハギン,
		トレント,
		グリフィン,
		ドラゴン,
		インプ,
		COUNT
	};

	//アイコン
	enum class IconType
	{
		//UI汎用
		閉じる,
		資金,
		三角,
		製造力,
		完了,
		ランク,
		//各種ウィンドウアイコン
		装備,
		製造,
		迷宮,
		編成,
		求人,
		戦略,
		素材,
		依頼,
		情報,
		ログ,

		全て,
		ボス,
		地図,
		宝箱,
		更新,

		再募集,

		//経営部,//情報と同じ
		//人事部,//求人と同じ
		//製造部,//製造と同じ
		//探索部,//迷宮と同じ

		メインクエ,
		サブクエ,
		名声,

		集客,
		開発,
		撤退,

		解像度,
		BGM,
		効果音,

		New,

		//上部分バー
		日付,
		時間,
		人口,
		ヘルプ,
		停止,
		速度,
		設定,
		終了,

		COUNT
	};

	//武器-防具画像
	enum class ItemImageType
	{
		鉄の剣,
		鉄の斧,
		木の弓,
		鉄の盾,
		スタッフ,
		ワンド,
		鉄の鎧,
		鎖帷子,
		皮のローブ,
		アクセサリ,
		COUNT
	};

	//吹き出し
	enum class EmoteType
	{
		ビックリ,
		音符,
		困惑,
		はてな,
		汗,
		眠り,
		怒り,
		ハート,
		ドクロ,
		３点,
		２点,
		１点,
		COUNT
	};

	//アクティブ&パッシブスキル種
	enum class SkillType
	{
		剣,//斬
		斧,
		盾,//打
		槌,
		刺剣,//突
		槍,
		弓,//射撃
		銃,
		魔杖,//魔術-攻撃
		骨杖,//魔術-補助
		神杖,//神聖-回復
		祝杖,//神聖-補助

		鎧,
		革鎧,
		ローブ,

		挑発,
		隠密,
		防御,
		回避,
		魔防,
		回復,
		攻撃,
		バフ,
		デバフ,
		探索,
		製造,
		素材,
		STR,
		DEX,
		INT,
		その他,
		COUNT
	};

	//効果音
	enum class SEType
	{
		//UI効果音
		決定,
		キャンセル,
		ボタン押,
		タブ押,
		掴む,
		装着,
		投資,
		//内政効果音
		クエスト完了,
		製造,
		新製造,
		販売,
		内政Lv,


		//戦闘探索効果音
		地図発見,
		ボス発見,
		探索開始,
		探索終了,

		攻撃,
		回復,
		補助,

		味方気絶,
		敵気絶,
		全滅,

		COUNT
	};

	//BGM
	enum class BGMType
	{
		準備中,
		探検中,
		通常ボス,
		エリアボス,
		タイトル,
		COUNT
	};

	//◆系統定義用
	//ゲームモード、複雑さ、難易度
	enum class GameType
	{
		ノーマル,
		ハード,
		デスマーチ,
		COUNT
	};

	enum class WindowType
	{
		//常時ウィンドウ
		Dungeon,
		EventLog,
		Factory,
		Guild,
		Item,
		Management,
		Material,
		Party,
		Quest,
		Recruit,
		//一時ウィンドウ
		Config,//設定
		COUNT,
	};

	enum class CraftType
	{
		鍛造,
		木工,
		裁縫,
		魔術,
		COUNT
	};

	//褒章
	enum class RewardType
	{
		COUNT
	};

	//ダンジョンの見た目
	enum class DungeonType
	{
		城,
		森,
		洞窟,
		砂漠,
		山,
		滝,
		塔,
		廃墟,
		COUNT
	};

	//アイテム系統
	enum class ItemType
	{
		//武器
		剣,//斬
		斧,
		盾,//打
		槌,
		刺剣,//突
		槍,
		弓,//射撃
		銃,
		魔杖,//魔術-攻撃
		骨杖,//魔術-補助
		神杖,//神聖-回復
		祝杖,//神聖-補助

		//防具
		重鎧,//block
		力鎧,//str
		軽鎧,//dodge
		技鎧,//dex
		隠鎧,//隠密
		知鎧,//int

		アクセサリー,
		すべて,
		COUNT
	};

	//経営戦術系統
	enum class ManagementType
	{
		経営,
		人事,
		製造,
		探索,
		COUNT
	};

	enum class MSkillType
	{
		ビラ配り,
		薄利多売,
		新人発掘,
		OJT,
		技術研究,
		低コスト化,
		探索術,
		探索許可証,
		COUNT,
	};

	//依頼系統
	enum class QuestType
	{
		装備販売,
		装備製造,
		雑魚討伐,
		ダンジョン発見,//なんでもいいから発見
		ボス討伐,//なんでもいいから討伐
		固定ボス討伐,//特定ダンジョンのボス討伐
		COUNT
	};

	//部屋種
	enum class RoomType
	{
		ザコ,
		素材,
		ボス,
		大ボス,
		財宝,//お金や名誉
		地図,
		COUNT
	};

	enum class ExplorerType
	{
		編成中,
		戦闘中,
		移動中,
		収集中,
		撤退中,
		全滅中,
		リザルト中,

		//宝箱開封、地図発見、戦闘後ドロップ、ボス演出などは未実装

	};

	//探索指示
	enum class OrderType
	{
		探索,
		ボス,
		COUNT
	};

	//ダメージ属性
	enum class DamageType
	{
		物理,
		魔法,
		COUNT
	};

	//素材種-6種+宝石×ランク
	//enum class MaterialType
	//{
	//	金属,
	//	石材,
	//	木材,
	//	皮革,
	//	羽毛,
	//	骨牙,
	//	遺物,
	//	COUNT
	//};

	enum class FormationType
	{
		前列,
		中列,//未使用
		後列,
		全列,
		COUNT
	};

	enum class StatusType
	{
		Str,
		Int,
		Dex,
		COUNT
	};

	//◆全種類列挙◆
	typedef unsigned int ItemNo;
	typedef unsigned int JobNo;
	typedef unsigned int MonsterNo;
	typedef unsigned int TacticsNo;


	//経営戦術
	enum class mentS
	{
		COUNT
	};

	//ギルドマスター
	enum class MasterS
	{
		COUNT
	};

}
