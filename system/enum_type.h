//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
;
namespace SDX_ADE
{
	using namespace SDX;

	//難易度
	enum class GameType
	{
		ノーマル,
		ハードコア,
		デスマーチ,
		COUNT
	};

	//◆画像、音声の管理用
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
		ゴミ箱,
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

		//素材
		木材,
		皮材,
		鉄材,
		骨材,

		//ダンジョン
		城,
		森,
		洞窟,
		砂漠,
		山,
		滝,
		塔,
		廃墟,

		//探索用
		探索_伐採,
		探索_採掘,
		探索_財宝,
		探索_地図,
		探索_石版,

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

	//武器-防具-アクセサリー画像
	enum class ItemImageType
	{
		大剣,
		剣盾,
		大盾,
		円盤,
		斧,
		刀,
		弓,
		神杖,
		錫杖,
		導杖,
		書物,
		水晶,

		重鎧,
		軽鎧,
		軽装,
		外套,

		/*
		鉄の剣,
		鉄の斧,
		木の弓,
		鉄の盾,
		スタッフ,
		ワンド,
		鉄の鎧,
		鎖帷子,
		皮のローブ,
		*/
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
		なし,
		攻撃,
		回復,
		補助,
		異常,
		バフ,
		デバフ,
		自分,
		単体,
		範囲,
		全体,
		多段,
		暗殺,
		物理,
		魔法,
		無属性,
		斬撃,
		打撃,
		射撃,
		火炎,
		氷雪,
		雷撃,
		力,
		技,
		魔,
		COUNT
	};

	//戦闘エフェクト
	enum class EffectAnimeType
	{
		斬,
		打,
		突,
		炎,
		雷,
		氷,
		バフ,
		デバフ,
		回復,
		異常,
		爪,
		牙,
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
	enum class WindowType
	{
		//常時ウィンドウ
		Dungeon,
		EventLog,
		Item,
		Management,
		Material,
		Party,
		Quest,
		//ポップアップウィンドウ
		Recruit,
		Skilltree,
		Config,
		Newgame,
		Continue,
		Credit,
		COUNT
	};

	enum class CraftType
	{
		木材,
		鉄材,
		石材,
		革材,
		骨材,
		魔材,
		COUNT
	};

	//アイテム系統
	enum class ItemType
	{
		//武器
		大剣,
		剣盾,
		大盾,
		円盤,
		斧,
		刀,
		弓,
		神杖,
		錫杖,
		導杖,
		書物,
		水晶,

		//防具
		重鎧,//防御
		軽鎧,//回避
		軽装,//命中
		外套,//Int

		アクセサリー,
		すべて,
		COUNT
	};

	//◆投資系統
	enum class ManagementType//削除予定
	{
		経営,
		人事,
		製造,
		探索,
		COUNT
	};

	enum class MSkillType//削除予定
	{
		ビラ配り,
		薄利多売,
		新人発掘,
		OJT,
		技術研究,
		低コスト化,
		探索術,
		探索許可証,
		探索許可証2,
		COUNT,
	};

	//◆依頼系統
	enum class QuestType
	{
		魔物討伐,//何でもいいからモンスター退治数
		素材売却,
		アクセサリー発見,
		魔物発見,
		ダンジョン発見,//なんでもいいから発見
		ボス討伐,//なんでもいいから討伐
		遺物収集,
		固定ボス討伐,//特定ダンジョンのボス討伐
		COUNT
	};

	//◆探索関係
	//部屋種
	enum class RoomType
	{
		ザコ,
		素材,
		ボス,
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

	enum class OrderType
	{
		探索,
		ボス,
		COUNT
	};

	//◆戦闘関係
	//基本ダメージ属性
	enum DamageType
	{
		物理 = 0,
		魔法 = 1,
		無属性 = 2,
	};

	enum FormationType
	{
		前列 = 0,
		後列 = 1,
		全列 = 2
	};

	enum class StatusType
	{
		HP,
		力,
		技,
		知,
		物防,
		魔防,
		命中,
		回避,
		会心,
		COUNT
	};

	enum class JobType
	{
		ガーディアン,
		グラディエーター,
		パスファインダー,
		メディック,
		ミスティック,
		オカルティスト,
		バーサーカー,
		スレイヤー,
		シノビ,
		デッドアイ,
		エレメンタリスト,
		トリックスター,
		COUNT
	};

	//◆data配列index用変数の型◆
	using ID_Job = unsigned int;
	using ID_Item = unsigned int;
	using ID_Monster = unsigned int;
	using ID_Material = unsigned int;
	using ID_Tactics = unsigned int;
	using ID_ASkill = unsigned int;
	using ID_PSkill = unsigned int;
	using ID_Dungeon = unsigned int;
}
