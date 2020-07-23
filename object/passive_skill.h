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
		常時,//探索開始時や編成変更時のみ処理
		戦闘開始時,
		//スキル使用時
		スキル使用時,
		攻撃スキル使用時,
		回復スキル使用時,
		補助スキル使用時,
		//スキル受け時
		攻撃スキル受ける前,
		回復スキル受ける前,
		補助スキル受ける前,
		//トリガー系パッシブ
		攻撃を受けた時,
		回復を受けた時,
		回避した時,
		自分が気絶した時,
		味方が気絶した時,
		自分が撃破した時,
		味方が撃破した時,//自分も含む
	};

	//条件
	enum class PSkillIf
	{
		条件無し,
		//状況条件
		HP一定以上,
		HP一定以下,
		敵の数が一定以下,
		敵の数が一定以上,
		戦闘時間が一定以下,//未実装
		戦闘時間が一定以上//未実装
		//敵や自分の状態異常
	};

	enum class PSkillTarget
	{
		自分,
		味方全員,
		スキル対象,
		敵単体,//敵対象パッシブは戦闘開始時とリアクション系のみ
		敵全体,
		その他
	};

	enum class PSkillEffect
	{
		//●アクティブスキル、通常攻撃強化
		ダメージ増加,
		スキル威力増減,
		スキル効果増減,
		スキルCT増減,
		スキル持続増減,
		アクティブスキルが追加発動,
		対象変更,
		対象を追加,
		攻撃属性変化,
		軽減無視,
		回避無視,
		HP上限超え回復,
		デバフ解除,
		//●バフ、特殊ステータス増加
		与ダメージバフ,
		受ダメージバフ,
		//●耐久上昇
		HP1で耐える,
		デバフ無効,
		//●リアクション系
		スキルチャージ獲得,
		HP回復,
		//●製造
		製造力増加,
		技術経験増加,
		素材使用減少,
		複数製造,
		//●探索
		未探索発見率増加,
		戦闘後回復,
		収集量増加,
		収集ランク増加,
		剥取量増加,
		剥取ランク増加,
		//●その他
		HP増加,
		STR増加,
		INT増加,
		DEX増加,
		物防増加,
		魔防増加,
		命中増加,
		回避増加,

		経験値増加,
		全滅ペナルティ軽減
	};

	/*パッシブスキル*/
	class PassiveSkill
	{
	private:
	public:
		static std::vector<PassiveSkill> data;

		PassiveSkill(int id , std::string 名前, std::string 説明 , SkillType 系統, ItemType 装備種, ASkillType Aスキル種)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->アイコン = 系統;

			this->装備種 = 装備種;//武器種条件
			this->Aスキル種 = Aスキル種;//Aスキル条件
		}

		void SetName(int id,std::string 名前, std::string 説明, SkillType 系統, ItemType 装備種, ASkillType Aスキル種)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->アイコン = 系統;

			this->装備種 = 装備種;//武器種条件
			this->Aスキル種 = Aスキル種;//Aスキル条件
		}

		void Set(int 必要SP, double 効果量, double 発動率,PSkillTime タイミング,PSkillIf 条件,PSkillTarget 対象,PSkillEffect 効果)
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
		SkillType アイコン;
		int 必要SP;
		double 効果量;

		//-条件
		ASkillType Aスキル種;
		ItemType 装備種;
		bool is奥義 = false;

		PSkillTime タイミング;
		double 発動率;

		PSkillIf 条件;
		double 条件値;
		int 持続時間 = 0;//一時バフ系効果

		PSkillTarget 対象;
		PSkillEffect 効果;
	};

	void LoadPassiveSkill()
	{
		PassiveSkill::data.emplace_back(0,"無し", "パッシブ無し",SkillType::その他, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[0].Set(0, 0, 0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::HP増加);

		PassiveSkill::data.emplace_back(1, "体力", "HPが20上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(2, "体力+", "HPが30上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(3, "体力++", "HPが40上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[1].Set(3, 20, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::HP増加);
		PassiveSkill::data[2].Set(5, 30, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::HP増加);
		PassiveSkill::data[3].Set(8, 40, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::HP増加);

		PassiveSkill::data.emplace_back(4, "腕力", "STRが5上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(5, "腕力+", "STRが7上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(6, "腕力++", "STRが10上昇する", SkillType::STR, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[4].Set(3, 5, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::STR増加);
		PassiveSkill::data[5].Set(5, 7, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::STR増加);
		PassiveSkill::data[6].Set(8, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::STR増加);

		PassiveSkill::data.emplace_back(7, "機敏", "DEXが5上昇する", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(8, "機敏+", "DEXが7上昇する", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(9, "機敏++", "DEXが10上昇する", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[7].Set(3, 5, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::DEX増加);
		PassiveSkill::data[8].Set(5, 7, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::DEX増加);
		PassiveSkill::data[9].Set(8, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::DEX増加);

		PassiveSkill::data.emplace_back(10, "知力", "INTが5上昇する", SkillType::INT, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(11, "知力+", "INTが7上昇する", SkillType::INT, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(12, "知力++", "INTが10上昇する", SkillType::INT, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[10].Set(3, 5, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::INT増加);
		PassiveSkill::data[11].Set(5, 7, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::INT増加);
		PassiveSkill::data[12].Set(8, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::INT増加);

		PassiveSkill::data.emplace_back(13, "剣技", "剣スキル 威力+15%", SkillType::剣, ItemType::剣, ASkillType::指定なし );
		PassiveSkill::data.emplace_back(14, "剣術", "剣スキル CT+10%"  , SkillType::剣, ItemType::剣, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(15, "斧技", "斧スキル 威力+15%", SkillType::斧, ItemType::剣, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(16, "斧術", "斧スキル CT+10%", SkillType::斧, ItemType::剣, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(17, "弓技", "弓スキル 威力+15%", SkillType::弓, ItemType::弓, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(18, "弓術", "弓スキル CT+10%", SkillType::弓, ItemType::弓, ASkillType::指定なし	);
		PassiveSkill::data.emplace_back(19, "魔技", "魔杖スキル 威力+15%", SkillType::魔杖, ItemType::魔杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(20, "魔術", "魔杖スキル CT+10%", SkillType::魔杖, ItemType::魔杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(21, "神技", "神杖スキル 威力+15%", SkillType::神杖, ItemType::神杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(22, "神術", "神杖スキル CT+10%", SkillType::神杖, ItemType::神杖, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(23, "盾技", "盾スキル 効果+15%", SkillType::盾, ItemType::盾, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(24, "盾術", "盾スキル CT+10%", SkillType::盾, ItemType::盾, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(25, "盾術", "盾スキル 持続+15%", SkillType::盾, ItemType::盾, ASkillType::指定なし);

		PassiveSkill::data[13].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[14].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[15].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[16].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[17].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[18].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[19].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[20].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[21].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[22].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[23].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル効果増減);
		PassiveSkill::data[24].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[25].Set(5, 0.15, 1.0, PSkillTime::スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル持続増減);

		PassiveSkill::data.emplace_back(26, "ガード", "物防+10", SkillType::防御, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(27, "ガード+", "物防+15", SkillType::防御, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(28, "レジスト", "魔防+10", SkillType::魔防, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(29, "レジスト+", "魔防+15", SkillType::魔防, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(30, "ステップ", "回避+10", SkillType::回避, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(31, "ステップ+", "回避+15", SkillType::回避, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(32, "正確性", "命中+10", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(33, "正確性+", "命中+15", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[26].Set(4, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::物防増加);
		PassiveSkill::data[27].Set(7, 15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::物防増加);
		PassiveSkill::data[28].Set(4, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::魔防増加);
		PassiveSkill::data[29].Set(7, 15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::魔防増加);
		PassiveSkill::data[30].Set(4, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::回避増加);
		PassiveSkill::data[31].Set(7, 15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::回避増加);
		PassiveSkill::data[32].Set(4, 10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::命中増加);
		PassiveSkill::data[33].Set(7, 15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::命中増加);

		//攻撃スキル強化、威力、CT
		PassiveSkill::data.emplace_back(34, "会心", "物理スキル 威力+10%", SkillType::攻撃, ItemType::すべて, ASkillType::物理);
		PassiveSkill::data.emplace_back(35, "会心+", "物理スキル 威力+15%", SkillType::攻撃, ItemType::すべて, ASkillType::物理);
		PassiveSkill::data.emplace_back(36, "敏捷性", "物理スキル CT-7%", SkillType::DEX, ItemType::すべて, ASkillType::物理);
		PassiveSkill::data.emplace_back(37, "敏捷性+", "物理スキル CT-10%", SkillType::DEX, ItemType::すべて, ASkillType::物理);
		PassiveSkill::data[34].Set(5, 0.10, 1.0, PSkillTime::攻撃スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[35].Set(5, 0.15, 1.0, PSkillTime::攻撃スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[36].Set(5, 0.07, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[37].Set(5, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		//魔法スキル強化、威力、CT
		PassiveSkill::data.emplace_back(38, "魔導", "魔法スキル 威力+10%", SkillType::INT, ItemType::すべて, ASkillType::魔法);
		PassiveSkill::data.emplace_back(39, "魔導+", "魔法スキル 威力+15%", SkillType::INT, ItemType::すべて, ASkillType::魔法);
		PassiveSkill::data.emplace_back(40, "詠唱", "魔法スキル CT-7%", SkillType::INT, ItemType::すべて, ASkillType::魔法);
		PassiveSkill::data.emplace_back(41, "詠唱+", "魔法スキル CT-10%", SkillType::INT, ItemType::すべて, ASkillType::魔法);
		PassiveSkill::data[38].Set(5, 0.10, 1.0, PSkillTime::攻撃スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[39].Set(8, 0.15, 1.0, PSkillTime::攻撃スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[40].Set(5, 0.07, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[41].Set(8, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);

		//回復スキル強化、威力、CT
		PassiveSkill::data.emplace_back(42, "治癒", "回復スキル 威力+10%", SkillType::回復, ItemType::すべて, ASkillType::回復);
		PassiveSkill::data.emplace_back(43, "治癒+", "回復スキル 威力+15%", SkillType::回復, ItemType::すべて, ASkillType::回復);
		PassiveSkill::data.emplace_back(44, "祈り", "回復スキル CT-7%", SkillType::回復, ItemType::すべて, ASkillType::回復);
		PassiveSkill::data.emplace_back(45, "祈り+", "回復スキル CT-10%", SkillType::回復, ItemType::すべて, ASkillType::回復);
		PassiveSkill::data[42].Set(4, 0.10, 1.0, PSkillTime::回復スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[43].Set(7, 0.15, 1.0, PSkillTime::回復スキル使用時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキル威力増減);
		PassiveSkill::data[44].Set(4, 0.07, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[45].Set(7, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);

		//必殺スキルの溜まりやすさ+10%
		PassiveSkill::data.emplace_back(46, "必殺", "奥義スキル CT-10%", SkillType::バフ, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(47, "必殺+", "奥義スキル CT-15%", SkillType::バフ, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[46].Set(4, 0.10, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[47].Set(7, 0.15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルCT増減);
		PassiveSkill::data[46].is奥義 = true;
		PassiveSkill::data[47].is奥義 = true;

		//戦闘後味方全員のHP回復
		PassiveSkill::data.emplace_back(48, "手当", "戦闘終了時、味方全員のHP4%回復", SkillType::回復, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(49, "手当", "戦闘終了時、味方全員のHP6%回復", SkillType::回復, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[48].Set(4, 0.04, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::味方全員, PSkillEffect::戦闘後回復);
		PassiveSkill::data[49].Set(7, 0.06, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::味方全員, PSkillEffect::戦闘後回復);


		//戦闘後自身のHP回復
		PassiveSkill::data.emplace_back(50, "タフガイ", "戦闘終了時、自身のHP15%回復", SkillType::回復, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[50].Set(4, 0.15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::戦闘後回復);

		//素材量+
		PassiveSkill::data.emplace_back(51, "保存術", "剥取素材数+10%", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(52, "保存術+", "剥取素材数+15%", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[51].Set(3, 0.1, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::剥取量増加);
		PassiveSkill::data[52].Set(5, 0.15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::剥取量増加);

		//素材ランク+
		PassiveSkill::data.emplace_back(53, "解剖学", "3%の確率で、剥取素材ランク+1", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(54, "解剖学+", "5%の確率で、剥取素材ランク+1", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[53].Set(3, 0.03, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::剥取ランク増加);
		PassiveSkill::data[54].Set(5, 0.05, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::剥取ランク増加);

		//収穫量+
		PassiveSkill::data.emplace_back(55, "採取術", "収集素材数+10%", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(56, "採取術+", "収集素材数+15%", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[55].Set(3, 0.1, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::収集量増加);
		PassiveSkill::data[56].Set(5, 0.15, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::収集量増加);

		//収穫ランク+
		PassiveSkill::data.emplace_back(57, "自然学", "3%の確率で、収集素材ランク+1", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(58, "自然学+", "5%の確率で、収集素材ランク+1", SkillType::素材, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data[57].Set(3, 0.03, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::収集ランク増加);
		PassiveSkill::data[58].Set(5, 0.05, 1.0, PSkillTime::常時, PSkillIf::条件無し, PSkillTarget::その他, PSkillEffect::収集ランク増加);

		//特殊効果系
		PassiveSkill::data.emplace_back(59, "咆哮", "開戦後300T、与ダメージ+20%", SkillType::バフ, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(60, "守護者", "開戦後300T、受けるダメージ-20%", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(61, "先駆け", "開戦時、全スキル CT+30", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(62, "一点集中", "敵が一体の時、スキル威力+25%", SkillType::DEX, ItemType::すべて, ASkillType::指定なし);
		PassiveSkill::data.emplace_back(63, "活力付与", "100Tの間 回復した味方が 与ダメージ+10%", SkillType::回復, ItemType::すべて, ASkillType::回復);

		PassiveSkill::data[59].Set(5, 0.2, 1.0, PSkillTime::戦闘開始時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::与ダメージバフ);
		PassiveSkill::data[60].Set(5, 0.2, 1.0, PSkillTime::戦闘開始時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::受ダメージバフ);
		PassiveSkill::data[61].Set(5, 30, 1.0, PSkillTime::戦闘開始時, PSkillIf::条件無し, PSkillTarget::自分, PSkillEffect::スキルチャージ獲得);
		PassiveSkill::data[62].Set(5, 0.25, 1.0, PSkillTime::攻撃スキル使用時, PSkillIf::敵の数が一定以下, PSkillTarget::スキル対象, PSkillEffect::スキル威力増減);
		PassiveSkill::data[63].Set(5, 0.1, 1.0, PSkillTime::回復スキル使用時, PSkillIf::条件無し, PSkillTarget::スキル対象, PSkillEffect::与ダメージバフ);

		PassiveSkill::data[62].条件値 = 1;

		PassiveSkill::data[59].持続時間 = 300;
		PassiveSkill::data[60].持続時間 = 300;
		PassiveSkill::data[63].持続時間 = 100;
	}

	std::vector<PassiveSkill> PassiveSkill::data;

	//Pスキル処理の流れ
	//複数人パッシブや装備パッシブを探索開始時に代入処理する

	//無条件基礎ステ系CT変化系パッシブを探索開始時に処理

	//スキル使用時に、威力:命中変化

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