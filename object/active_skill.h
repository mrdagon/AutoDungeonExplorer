//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	enum class ASkillMode
	{
		通常,
		スキル,
		必殺
	};

	enum class ASkillTarget
	{
		自分,
		同じ列,
		味方弱者,
		味方一列,
		味方全員,
		行動対象,
		敵単体,
		敵弱者,
		敵全体,
		その他
	};

	enum class ASkillType
	{
		ダメージ,
		回復,
		//バフ色々
		与ダメージ増加,
		与ダメージ減少,
		被ダメージ減少,
		被ダメージ増加,

		ブロック率増加,
		回避上昇,
		命中低下,
		
		通常攻撃,
		指定なし,
	};

	enum class ASkillSubeffect
	{
		なし,
		防御無視,
		回避無視,
		クリティカル,
		デバフ解除,
		デバフ無効,
		攻撃チャージ増加,
		スキルチャージ増加,
		//バフ効果
		リジェネ,
		バリア,

		//デバフ効果
		挑発,
		隠密,
		即死,
	};


	/*アクティブスキル*/
	class ActiveSkill
	{
	private:
	public:
		static std::vector<ActiveSkill> data;

		ActiveSkill() {}

		ActiveSkill(int id, std::string 名前, std::string 説明, SkillType 系統)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->系統 = 系統;
		}

		void Set(ASkillTarget 対象,StatusType 依存ステータス,ASkillType 効果,ASkillSubeffect 追加効果,int 効果回数,double 効果量,double ステータス反映率,double 効果時間,double 追加効果率,double 必要チャージ)
		{
			this->対象 = 対象;
			this->依存ステータス = 依存ステータス;
			this->効果 = 効果;
			this->追加効果 = 追加効果;

			this->効果回数 = 効果回数;//ランダムだったり単体に多段攻撃
			this->効果量 = 効果量;
			this->ステータス反映率 = ステータス反映率;
			this->効果時間 = 効果時間;
			this->追加効果率 = 追加効果率;

			this->必要チャージ = 必要チャージ;
		}

		int id;
		std::string 名前;
		std::string 説明;
		FormationType 隊列;
		ASkillMode 区分;

		SkillType 系統;//アイコン

		ASkillTarget 対象;
		StatusType 依存ステータス;
		ASkillType 効果;
		ASkillSubeffect 追加効果;
		DamageType 属性;

		bool is奥義;

		int 効果回数;//多段攻撃系
		double 効果量;
		double 命中 = 1.0;
		double ステータス反映率;
		double 効果時間;
		double 追加効果率;

		double 必要チャージ;
	};

	void LoadActiveSkill()
	{
		//武器７系統✕２＋ジョブ別スキル１０個


		ActiveSkill::data.emplace_back(0, "なし", "スキルなし",SkillType::その他);
		ActiveSkill::data.emplace_back(1, "スラッシュ", "単体にSTRx3.0ダメージ",SkillType::剣);
		ActiveSkill::data.emplace_back(2, "乱れ撃ち", "単体にDEXx1.0ダメージを３回",SkillType::弓);
		ActiveSkill::data.emplace_back(3, "エクスプロード", "全体にINTx1.5ダメージ",SkillType::魔杖);
		ActiveSkill::data.emplace_back(4, "叩きつけ", "単体にVITx2.5ダメージ",SkillType::盾);
		ActiveSkill::data.emplace_back(5, "ヒール", "味方一人のHPをINTx2.0回復",SkillType::神杖);

		//敵スキル、通常は共通。どのスキルも全列。雑魚はスキル１種。ボスは必殺含めて４種。
		ActiveSkill::data.emplace_back(6, "体当たり", "単体にSTRx2.0ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(7, "噛みつき", "単体にSTRx2.5ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(8, "スラム", "単体にSTRx2.0ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(9, "炎ブレス", "単体にINTx3.0ダメージ", SkillType::魔杖);

		ActiveSkill::data[0].Set(ASkillTarget::その他  , StatusType::Str, ASkillType::ダメージ		, ASkillSubeffect::なし, 0, 0,  0, 0, 0,  0);
		ActiveSkill::data[1].Set(ASkillTarget::敵単体  , StatusType::Str, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,3.0, 0, 0,60);
		ActiveSkill::data[2].Set(ASkillTarget::敵単体  , StatusType::Dex, ASkillType::ダメージ		, ASkillSubeffect::なし, 3, 0,1.0, 0, 0,60);
		ActiveSkill::data[3].Set(ASkillTarget::敵全体  , StatusType::Int, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,1.5, 0, 0,60);
		ActiveSkill::data[4].Set(ASkillTarget::敵単体  , StatusType::Str, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,2.5, 0, 0,60);
		ActiveSkill::data[5].Set(ASkillTarget::味方弱者, StatusType::Int, ASkillType::回復			, ASkillSubeffect::なし, 1, 0,2.0, 0, 0,60);
		ActiveSkill::data[6].Set(ASkillTarget::敵単体  , StatusType::Str, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,2.0, 0, 0,60);
		ActiveSkill::data[7].Set(ASkillTarget::敵単体  , StatusType::Str, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,2.5, 0, 0,60);
		ActiveSkill::data[8].Set(ASkillTarget::敵単体  , StatusType::Str, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,2.0, 0, 0,60);
		ActiveSkill::data[9].Set(ASkillTarget::敵単体  , StatusType::Int, ASkillType::ダメージ		, ASkillSubeffect::なし, 1, 0,3.0, 0, 0,60);

	}

	std::vector<ActiveSkill> ActiveSkill::data;
}