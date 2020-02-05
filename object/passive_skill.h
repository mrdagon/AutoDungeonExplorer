//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../system/enum_type.h"

namespace SDX_BSC
{
	using namespace SDX;

	//タイミング
	enum class PSkillTime
	{
		常時,
		基礎計算時,//探索開始時や編成変更時のみ処理
		戦闘開始時,
		ボス戦開始時,
		戦闘勝利時,
		自分が攻撃を受けた時,
		味方が攻撃を受けた時,
		味方が狙われた時,
		全体攻撃をされた時,
		通常攻撃時,
		スキル使用時,
		回復した時,
		回復する時,
		敵を倒した時,
		回避時,
		製造開始時,
		探索時,
		自分がHP0になった時,
		味方がHP0になった時,
		全滅時
	};

	//条件
	enum class PSkillIf
	{
		条件無し,
		HP一定以上,
		HP一定以下,
		//味方が一定以下,
		//味方が一定以上,
		敵の数が一定以下,
		敵の数が一定以上,
		ターン数が一定以下,//未実装
		ターン数が一定以上//未実装
	};

	enum class PSkillTarget
	{
		自分,
		味方自分以外,
		同じ列,
		味方全員,
		味方前列,
		味方後列,
		行動対象,
		敵単体,//敵対象パッシブは戦闘開始時とリアクション系のみ
		敵全体,
		その他
	};

	enum class PSkillEffect
	{
		//●アクティブスキル、通常攻撃強化
		ダメージ増加,
		行動値増減,
		スキル効果増加,
		スキルチャージ増減,
		スキル効果時間増減,
		アクティブスキルが追加発動,
		対象変更,
		対象を追加,
		攻撃属性変化,
		軽減無視,
		回避無視,
		HP上限超え回復,
		デバフ解除,
		後列ペナルティ無し,
		//●バフ、特殊ステータス増加
		与ダメージ増加,
		ブロック率増加,
		ブロック軽減率増加,
		//●耐久上昇
		ダメージ軽減,
		回避,
		魔法防御,
		狙われやすさ増減,
		HP1で耐える,
		デバフ無効,
		//●リアクション系
		身代わり生成,
		攻撃チャージ獲得,
		スキルチャージ獲得,
		HP回復,
		//●製造
		製造力増加,
		技術経験増加,
		素材使用減少,
		複数製造,
		//●探索
		ボス回避,
		未探索発見率増加,
		罠回避,
		解錠,
		高速探索,
		素材獲得量増加,//ここ６種類にする
		素材ランク増加,
		//●その他
		基礎ステ上昇,
		経験値増加,
		忠誠度補正,
		全滅ペナルティ軽減
	};

	/*パッシブスキル*/
	class PassiveSkill
	{
	private:
	public:
		static std::vector<PassiveSkill> data;

		PassiveSkill(int id, std::string 名前, std::string 説明 , SkillType 系統, ItemType 装備種, ASkillType Aスキル種)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->系統 = 系統;

			this->装備種 = 装備種;//武器種条件
			this->Aスキル種 = Aスキル種;//Aスキル条件
		}

		void SetName(int id,std::string 名前, std::string 説明, SkillType 系統, ItemType 装備種, ASkillType Aスキル種)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->系統 = 系統;

			this->装備種 = 装備種;//武器種条件
			this->Aスキル種 = Aスキル種;//Aスキル条件
		}

		void Set(int 必要SP, double 効果量, double 発動率,double 条件値,PSkillTime タイミング,PSkillIf 条件,PSkillTarget 対象,PSkillEffect 効果)
		{
			this->必要SP = 必要SP;
			this->効果量 = 効果量;
			this->発動率 = 発動率;

			this->タイミング = タイミング;
			this->条件 = 条件;
			this->対象 = 対象;
			this->効果 = 効果;
		}

		//-基本情報
		int id;
		std::string 名前;
		std::string 説明;
		SkillType 系統;//アイコン
		int 必要SP;
		double 効果量;

		//-条件
		ItemType 装備種;
		ASkillType Aスキル種;//アクティブスキルタイプ

		FormationType 隊列;//隊列条件-未実装

		PSkillTime タイミング;
		double 発動率;

		PSkillIf 条件;
		double 条件値;

		PSkillTarget 対象;
		PSkillEffect 効果;
	};

	void LoadPassiveSkill()
	{
		PassiveSkill::data.emplace_back(0, "無し", "パッシブ無し",SkillType::その他, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(1, "STR+", "STRが5上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(2, "DEX+", "DEXが5上昇する", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(3, "INT+", "INTが5上昇する", SkillType::INT, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(4, "VIT+", "VITが5上昇する", SkillType::VIT, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(5, "AGI+", "AGIが5上昇する", SkillType::AGI, ItemType::すべて, ASkillType::指定なし);

		PassiveSkill::data.emplace_back(6, "剣技", "剣スキルの効果+20%", SkillType::剣, ItemType::剣, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(7, "剣術", "剣スキルのチャージ+20%", SkillType::剣, ItemType::剣, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(8, "弓技", "弓スキルの効果+20%", SkillType::弓, ItemType::弓, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(9, "弓術", "弓スキルのチャージ+20%", SkillType::弓, ItemType::弓, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(10, "杖技", "杖スキルの効果+20%", SkillType::魔杖, ItemType::魔杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(11, "杖術", "杖スキルのチャージ+20%", SkillType::魔杖, ItemType::魔杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(12, "盾技", "盾スキルの効果+20%", SkillType::盾, ItemType::盾, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(13, "盾術", "盾スキルのチャージ+20%", SkillType::盾, ItemType::盾, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(14, "棒技", "棒スキルの効果+20%", SkillType::神杖, ItemType::神杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(15, "棒術", "棒スキルのチャージ+20%", SkillType::神杖, ItemType::神杖, ASkillType::指定なし);

		PassiveSkill::data.emplace_back(16, "切り込み", "開戦時、自分に+20%火力強化", SkillType::バフ, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(17, "必殺技", "攻撃スキルの効果+10%", SkillType::STR, ItemType::すべて, ASkillType::ダメージ);
		PassiveSkill::data.emplace_back(18, "連撃", "通常攻撃時、10%の確率で連続攻撃", SkillType::攻撃, ItemType::すべて, ASkillType::指定なし);

		PassiveSkill::data.emplace_back(19, "ガード", "ブロック+10%", SkillType::防御, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(20, "パリィ", "回避+10%", SkillType::防御, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(21, "挑発", "狙われやすさx1.2", SkillType::挑発, ItemType::すべて, ASkillType::指定なし);

		PassiveSkill::data.emplace_back(22, "先駆け", "開戦時、スキルチャージ+20", SkillType::AGI, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(23, "隠密", "狙われやすさx0.8", SkillType::隠密, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(24, "採取", "素材収集数+10%", SkillType::素材, ItemType::すべて, ASkillType::指定なし);

		PassiveSkill::data.emplace_back(25, "魔法障壁", "ブロック+10%", SkillType::魔防, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(26, "集中砲火", "敵が1体の場合全体スキルダメ+50%", SkillType::攻撃, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(27, "解剖学", "素材剥取数+10%", SkillType::素材, ItemType::すべて, ASkillType::指定なし);

		PassiveSkill::data.emplace_back(28, "手当", "戦闘終了時、パーティのHP5%回復", SkillType::回復, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(29, "治癒", "回復スキルの効果+10%", SkillType::回復, ItemType::すべて, ASkillType::回復);
		PassiveSkill::data.emplace_back(30, "祝福", "回復した味方に10%火力強化", SkillType::回復, ItemType::すべて, ASkillType::回復);
		//                        SP  量  率  閾
		PassiveSkill::data[0].Set(0 ,  0,   0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::HP回復);
		PassiveSkill::data[1].Set(5 ,  5, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::基礎ステ上昇);
		PassiveSkill::data[2].Set(5 ,  5, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::基礎ステ上昇);
		PassiveSkill::data[3].Set(5 ,  5, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::基礎ステ上昇);
		PassiveSkill::data[4].Set(5 ,  5, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::基礎ステ上昇);
		PassiveSkill::data[5].Set(5 ,  5, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::基礎ステ上昇);
		PassiveSkill::data[6].Set(5 ,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキル効果増加 );
		PassiveSkill::data[7].Set(5 ,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキルチャージ増減);
		PassiveSkill::data[8].Set(5 ,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキル効果増加);
		PassiveSkill::data[9].Set(5 ,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキルチャージ増減);
		PassiveSkill::data[10].Set(5,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキル効果増加);
		PassiveSkill::data[11].Set(5,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキルチャージ増減);
		PassiveSkill::data[12].Set(5,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキル効果増加);
		PassiveSkill::data[13].Set(5,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキルチャージ増減);
		PassiveSkill::data[14].Set(5,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキル効果増加);
		PassiveSkill::data[15].Set(5,0.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキルチャージ増減);
		PassiveSkill::data[16].Set(5,0.2, 1.0, 0, PSkillTime::戦闘開始時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::与ダメージ増加 );
		PassiveSkill::data[17].Set(5,0.1, 1.0, 0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキル効果増加 );
		PassiveSkill::data[18].Set(5,1000, 0.1, 0, PSkillTime::通常攻撃時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::行動値増減 );
		PassiveSkill::data[19].Set(5,0.1, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::ブロック率増加 );
		PassiveSkill::data[20].Set(5,0.1, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::回避 );
		PassiveSkill::data[21].Set(5,1.2, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::狙われやすさ増減 );
		PassiveSkill::data[22].Set(5, 10, 1.0, 0, PSkillTime::戦闘開始時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::スキルチャージ獲得 );
		PassiveSkill::data[23].Set(5,0.8, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::狙われやすさ増減 );
		PassiveSkill::data[24].Set(5, 10, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::素材獲得量増加 );
		PassiveSkill::data[25].Set(5,0.1, 1.0, 0, PSkillTime::基礎計算時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::ブロック率増加 );
		PassiveSkill::data[26].Set(5,0.5, 1.0, 1, PSkillTime::常時, PSkillIf::敵の数が一定以下, PSkillTarget::自分 , PSkillEffect::スキル効果増加 );
		PassiveSkill::data[27].Set(5, 10, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分 , PSkillEffect::素材獲得量増加 );
		PassiveSkill::data[28].Set(5,0.05,1.0, 0, PSkillTime::戦闘勝利時, PSkillIf::条件無し, PSkillTarget::味方全員 , PSkillEffect::HP回復 );
		PassiveSkill::data[29].Set(5,0.1, 1.0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::行動対象 , PSkillEffect::スキル効果増加 );
		PassiveSkill::data[30].Set(5,0.1, 1.0, 0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::行動対象 , PSkillEffect::与ダメージ増加 );
	}

	std::vector<PassiveSkill> PassiveSkill::data;

	//Pスキル処理の流れ
	//複数人パッシブを探索開始時に代入処理
	//各関数でTime条件があってるかチェック
	//IF条件、Aスキル条件、装備条件、発動確率をチェック、しきい値付きの条件をチェック
	//パッシブ効果の処理は一箇所にまとめる

	//パッシブ処理してる関数
	//常時○開始時、攻撃スキル防御回復時
	//戦闘勝利時○
	//基礎計算時○

	//スキル使用時
	//通常攻撃時

}