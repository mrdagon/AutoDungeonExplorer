//Copyright © 2019 (´･@･)
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
		閉じる,
		星,
		来客,
		迷宮,
		ログ,
		目標,
		情報,
		装備,
		戦略,
		素材,
		団員,
		依頼,
		求人,
		収支,
		ハンマー,

		宝箱,

		日付,
		時間,
		人口,
		順位,
		資金,
		ヘルプ,
		停止,
		速度,
		出口,
		三角,
		設定,

		灰石,

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
		VIT,
		AGI,
		その他,
		COUNT
	};

	//効果音
	enum class SEType
	{
		決定,
		COUNT
	};

	//BGM
	enum class BGMType
	{
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
		Record,
		//一時ウィンドウ
		Treatment,//月末待遇変更
		Config,//設定
		Graf,//折れ線GRAF

	};

	enum class CraftType
	{
		斬撃,
		打撃,
		刺突,
		射撃,
		魔術,
		神秘,
		STR鎧,
		DEX鎧,
		INT鎧,
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
		重鎧,//block
		力鎧,//str
		軽鎧,//dodge
		技鎧,//dex
		隠鎧,//隠密
		知鎧,//int
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

	//依頼系統
	enum class QuestType
	{
		//製造
		//雑魚討伐
		//ボス討伐
		COUNT
	};

	//部屋種
	enum class RoomType
	{
		魔物,
		素材,
		ボス,
		財宝,//お金
		石碑,//部門経験値-名誉-技術レベルなど
		回復,//体力回復
		COUNT
	};

	//探索指示
	enum class OrderType
	{
		COUNT
	};

	//素材種-6種+宝石×ランク

	enum class MaterialType
	{
		金属,
		石材,
		木材,
		皮革,
		羽毛,
		骨牙,
		遺物,
		COUNT
	};


	enum class FormationType
	{
		前列,
		中列,
		後列,
		COUNT
	};

	enum class StatusType
	{
		Str,
		Int,
		Dex,
		Vit,
		Agi,
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

	//依頼人
	enum class ClientS
	{
		COUNT
	};

	//ギルドマスター
	enum class MasterS
	{
		COUNT
	};

}
