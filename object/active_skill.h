//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	enum class ASkillTarget
	{
		自分,
		味方弱者,
		味方全員,
		敵ランダム,
		敵前ランダム,
		敵後ランダム,
		敵前,
		敵後,
		敵全,
		敵弱者,
		その他
	};

	enum class ASkillType
	{
		物理,
		魔法,
		回復,
		//バフ系
		バフ,
		デバフ,
		指定なし
	};

	enum class ASkillEffectType
	{
		なし,
		防御無視,
		回避無視,
		デバフ解除,
		デバフ無効,
		攻撃チャージ増加,
		スキルチャージ増加,
		//バフ効果
		物防バフ,
		魔防バフ,
		Strバフ,
		Intバフ,

		//デバフ効果
		挑発,
		隠密,
		即死,
		COUNT
	};

	/*発動中のスキル*/

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

		void Set(ASkillTarget 対象,StatusType 依存ステータス,DamageType 属性,ASkillType スキル種)
		{
			this->対象 = 対象;
			this->属性 = 属性;
			this->依存ステータス = 依存ステータス;
			this->種類 = スキル種;
		}

		void SetEffect(ASkillEffectType 効果種, double 効果量, int 効果時間, double 効果発動率 = 1.0)
		{
			追加効果量[効果種] = 効果量;
			追加確率[効果種] = 効果発動率;
			追加時間[効果種] = 効果時間;
		}

		void SetP(int 効果回数, double 効果量, double ステータス反映率,double 命中, double 効果時間, double 必要チャージ, bool is奥義 = false)
		{
			this->効果回数 = 効果回数;//ランダムだったり単体に多段攻撃
			this->効果量 = 効果量;
			this->ステータス反映率 = ステータス反映率;
			this->効果時間 = 効果時間;

			this->命中 = 命中;

			this->必要チャージ = 必要チャージ;
			this->is奥義 = is奥義;
		}

		int id;
		std::string 名前;
		std::string 説明;

		SkillType 系統;//アイコン

		ASkillTarget 対象;
		int 範囲 = 1;
		StatusType 依存ステータス;
		ASkillType 種類;
		ItemType 装備種 = ItemType::すべて;
		DamageType 属性;

		EnumArray<double, ASkillEffectType> 追加効果量;
		EnumArray<double, ASkillEffectType> 追加確率;
		EnumArray<int, ASkillEffectType> 追加時間;

		bool is奥義;

		int 効果回数;//多段攻撃系
		double 命中 = 1.0;
		double 効果量;//基礎効果量
		double ステータス反映率;
		double 効果時間;
		double 追加効果率 = 1.0;

		double 必要チャージ;
	};

	class ASkillEffect
	{
	public:

		SkillType 系統;
		StatusType 依存ステータス;
		ItemType 装備種;
		DamageType 属性;//物理,魔法
		bool is奥義;

		ASkillTarget 対象;
		int 範囲;

		ASkillType 種類;
		EnumArray<double, ASkillEffectType> 追加効果量;
		EnumArray<double, ASkillEffectType> 追加確率;
		EnumArray<int, ASkillEffectType> 追加時間;
		double 命中;

		ASkillEffect(const ActiveSkill* スキルベース):
			系統(スキルベース->系統),
			依存ステータス(スキルベース->依存ステータス),
			属性(スキルベース->属性),
			対象(スキルベース->対象),
			種類(スキルベース->種類),
			装備種(スキルベース->装備種),
			範囲(スキルベース->範囲),
			命中(スキルベース->命中),
			is奥義(スキルベース->is奥義)
		{
			for (int a = 0; a < (int)ASkillEffectType::COUNT; a++)
			{
				auto s = ASkillEffectType(a);

				追加効果量[s] = スキルベース->追加効果量[s];
				追加時間[s] = スキルベース->追加時間[s];
				追加確率[s] = スキルベース->追加確率[s];
			}
		}
	};

	void LoadActiveSkill()
	{
		//武器７系統✕２＋ジョブ別スキル１０個
		ActiveSkill::data.emplace_back( 0, "なし" , "スキルなし",SkillType::その他);
		ActiveSkill::data[0].Set(ASkillTarget::その他, StatusType::Str, DamageType::物理, ASkillType::指定なし);
		ActiveSkill::data[0].SetP(0, 0, 0, 0, 0, 0, 0);

		ActiveSkill::data.emplace_back( 1, "斬撃" , "先頭に STRx100% 物理ダメージ",SkillType::剣);
		ActiveSkill::data.emplace_back( 2, "スラッシュ", "先頭に STRx300% 物理ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back( 3, "斬撃"  , "先頭に STRx120% 物理ダメージ", SkillType::斧);
		ActiveSkill::data.emplace_back( 4, "兜割り", "先頭に STRx300% 物理ダメージ、防御無視", SkillType::斧);
		ActiveSkill::data.emplace_back( 5, "射撃"  , "ランダムに DEXx120% 物理ダメージ",SkillType::弓);
		ActiveSkill::data.emplace_back( 6, "狙い撃ち", "HPの少ない敵に DEXx300% 物理ダメージ", SkillType::弓);
		ActiveSkill::data.emplace_back( 7, "打撃"  , "先頭に STRx50% 物理ダメージ", SkillType::盾);
		ActiveSkill::data.emplace_back( 8, "挑発"  , "100Tの間 狙われやすくなり、物魔防御+20", SkillType::盾);
		ActiveSkill::data.emplace_back( 9, "魔弾"  , "ランダムに INTx120% 魔法ダメージ",SkillType::魔杖);
		ActiveSkill::data.emplace_back(10, "大爆発", "全体に INTx200% 魔法ダメージ", SkillType::魔杖);
		ActiveSkill::data.emplace_back(11, "打撃"  , "先頭に STRx50% 物理ダメージ",SkillType::神杖);
		ActiveSkill::data.emplace_back(12, "ヒール", "弱った味方一人のHPを INTx150% 回復", SkillType::神杖);

		ActiveSkill::data[1].装備種 = ItemType::剣;
		ActiveSkill::data[2].装備種 = ItemType::剣;
		ActiveSkill::data[3].装備種 = ItemType::斧;
		ActiveSkill::data[4].装備種 = ItemType::斧;
		ActiveSkill::data[5].装備種 = ItemType::弓;
		ActiveSkill::data[6].装備種 = ItemType::弓;
		ActiveSkill::data[7].装備種 = ItemType::盾;
		ActiveSkill::data[8].装備種 = ItemType::盾;
		ActiveSkill::data[9].装備種 = ItemType::魔杖;
		ActiveSkill::data[10].装備種 = ItemType::魔杖;
		ActiveSkill::data[11].装備種 = ItemType::神杖;
		ActiveSkill::data[12].装備種 = ItemType::神杖;

		//敵スキル。雑魚はスキル２種。ボスは必殺含めて３種。
		ActiveSkill::data.emplace_back(13, "体当たり", "先頭にSTRx1.0ダメージ", SkillType::剣);//スライム
		ActiveSkill::data.emplace_back(14, "溶解液"  , "前列にINTx1.0ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(15, "噛みつき", "前列にSTRx1.0ダメージ", SkillType::剣);//こうもり
		ActiveSkill::data.emplace_back(16, "超音波"  , "ランダムにINTx1.5ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(17, "パンチ"  , "先頭にSTRx1.0物理ダメージ", SkillType::剣);//ほね
		ActiveSkill::data.emplace_back(18, "骨投げ"  , "後列にSTRx1.5物理ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(19, "叩きつけ", "先頭にSTRx1.0物理ダメージ", SkillType::剣);//ドラゴン
		ActiveSkill::data.emplace_back(20, "尾撃"    , "前列にSTRx0.6物理ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back(21, "炎ブレス", "全体にINTx2.0魔法ダメージ", SkillType::剣);

		ActiveSkill::data[1].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 ,ASkillType::物理);
		ActiveSkill::data[2].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 , ASkillType::物理);
		ActiveSkill::data[3].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 ,ASkillType::物理);
		ActiveSkill::data[4].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 , ASkillType::物理);
		ActiveSkill::data[5].Set(ASkillTarget::敵ランダム, StatusType::Dex, DamageType::物理 , ASkillType::物理);
		ActiveSkill::data[6].Set(ASkillTarget::敵弱者 , StatusType::Dex, DamageType::物理, ASkillType::物理);
		ActiveSkill::data[7].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理, ASkillType::物理);
		ActiveSkill::data[8].Set(ASkillTarget::自分   , StatusType::Str, DamageType::物理 , ASkillType::バフ);
		ActiveSkill::data[8].SetEffect(ASkillEffectType::物防バフ, 20, 100);
		ActiveSkill::data[8].SetEffect(ASkillEffectType::魔防バフ, 20, 100);
		ActiveSkill::data[8].SetEffect(ASkillEffectType::挑発, 20, 100);

		ActiveSkill::data[9].Set(ASkillTarget::敵ランダム, StatusType::Int, DamageType::魔法, ASkillType::魔法);
		ActiveSkill::data[10].Set(ASkillTarget::敵全, StatusType::Int, DamageType::魔法, ASkillType::魔法);
		ActiveSkill::data[11].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[12].Set(ASkillTarget::味方弱者, StatusType::Int, DamageType::魔法, ASkillType::回復 );
		
		ActiveSkill::data[13].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[14].Set(ASkillTarget::敵前ランダム, StatusType::Int, DamageType::魔法, ASkillType::魔法 );
		ActiveSkill::data[14].範囲 = 3;
		ActiveSkill::data[15].Set(ASkillTarget::敵前ランダム, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[15].範囲 = 3;
		ActiveSkill::data[16].Set(ASkillTarget::敵ランダム, StatusType::Int, DamageType::魔法, ASkillType::魔法 );
		ActiveSkill::data[17].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[18].Set(ASkillTarget::敵後ランダム, StatusType::Dex, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[18].範囲 = 3;
		ActiveSkill::data[19].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[20].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[18].範囲 = 3;
		ActiveSkill::data[21].Set(ASkillTarget::敵全, StatusType::Int, DamageType::魔法, ASkillType::魔法 );

		//////////////////////////効果回数
		ActiveSkill::data[1].SetP( 1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[2].SetP( 1, 0,3.0, 1.0, 0,  300);
		ActiveSkill::data[3].SetP( 1, 0,1.2, 0.8, 0,  100);
		ActiveSkill::data[4].SetP( 1, 0,3.0, 0.9, 0,  500);
		ActiveSkill::data[5].SetP( 1, 0,1.2, 0.9, 0,  80);
		ActiveSkill::data[6].SetP( 1, 0,3.0, 1.5, 0,  500);
		ActiveSkill::data[7].SetP( 1, 0,0.5, 0.8, 0,  100);
		ActiveSkill::data[8].SetP( 1,20,0.0, 1.0,100, 300);
		ActiveSkill::data[9].SetP( 1, 0,1.2, 0.9, 0,  110);
		ActiveSkill::data[10].SetP(1, 0,2.0, 0.8, 0,  550);
		ActiveSkill::data[11].SetP(1, 0,0.5, 0.8, 0,  100);
		ActiveSkill::data[12].SetP(1, 0,1.5, 1.0, 0,  400);

		ActiveSkill::data[13].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[14].SetP(1, 0,1.0, 0.8, 0,  100);
		ActiveSkill::data[15].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[16].SetP(1, 0,1.5, 0.8, 0,  100);
		ActiveSkill::data[17].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[18].SetP(1, 0,1.5, 0.8, 0,  100);
		ActiveSkill::data[19].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[20].SetP(1, 0,0.6, 0.6, 0,  200);
		ActiveSkill::data[21].SetP(1, 0,2.0, 0.7, 0,  600,true);

		//各ジョブのスキル
		//ファイター
		ActiveSkill::data.emplace_back(22, "切り込み", "前列一体に STRx250% 物理ダメージ", SkillType::剣);
		ActiveSkill::data[22].Set(ASkillTarget::敵前ランダム , StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[22].SetP(1, 0, 2.5, 1.0, 0, 400);
		ActiveSkill::data[22].範囲 = 3;
		ActiveSkill::data.emplace_back(23, "回転斬り", "前列3体に STRx400% 物理ダメージ", SkillType::剣);
		ActiveSkill::data[23].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[23].SetP(1, 0, 4.0, 1.1, 0, 1000,true);
		ActiveSkill::data[23].範囲 = 3;

		//ナイト
		ActiveSkill::data.emplace_back(24, "守護", "200Tの間 狙われやすくなり、物魔防御+30",SkillType::盾);
		ActiveSkill::data[24].Set(ASkillTarget::自分, StatusType::Str, DamageType::物理, ASkillType::バフ);
		ActiveSkill::data[24].SetP(1, 30, 0, 1.0, 200, 100);
		ActiveSkill::data[24].SetEffect(ASkillEffectType::物防バフ, 30, 200);
		ActiveSkill::data[24].SetEffect(ASkillEffectType::魔防バフ, 30, 200);
		ActiveSkill::data[24].SetEffect(ASkillEffectType::挑発, 30, 200);

		ActiveSkill::data.emplace_back(25, "大防御", "600Tの間、味方全員の 物/魔防御 + 30 ", SkillType::盾);
		ActiveSkill::data[25].Set(ASkillTarget::味方全員, StatusType::Str, DamageType::物理, ASkillType::バフ);
		ActiveSkill::data[25].SetP(1, 30, 0, 1.0, 600, 1000, true);
		ActiveSkill::data[25].SetEffect(ASkillEffectType::物防バフ, 30, 600);
		ActiveSkill::data[25].SetEffect(ASkillEffectType::魔防バフ, 30, 600);

		//レンジャー
		ActiveSkill::data.emplace_back(26, "二段攻撃", "ランダムに2回 DEXx150% 物理ダメージ", SkillType::弓);
		ActiveSkill::data[26].Set(ASkillTarget::敵ランダム, StatusType::Dex, DamageType::物理, ASkillType::物理);
		ActiveSkill::data[26].SetP(2, 0, 1.5, 0.7, 0, 100);
		ActiveSkill::data.emplace_back(27, "マジカルアロー", "ランダムに6回 DEXx200% 魔法ダメージ", SkillType::弓);
		ActiveSkill::data[27].Set(ASkillTarget::敵ランダム, StatusType::Dex, DamageType::魔法, ASkillType::物理);
		ActiveSkill::data[27].SetP(6, 0, 2.0, 0.6, 0, 1000, true);

		//ウィザード
		ActiveSkill::data.emplace_back(28, "集中", "400Tの間、自身の INT+30% 上昇", SkillType::INT);
		ActiveSkill::data[28].Set(ASkillTarget::自分, StatusType::Int, DamageType::魔法, ASkillType::バフ);
		ActiveSkill::data[28].SetP(1, 0, 0.3, 0.8, 300, 400);
		ActiveSkill::data[28].SetEffect(ASkillEffectType::Intバフ, 30, 400);

		ActiveSkill::data.emplace_back(29, "紅蓮地獄", "敵前列に INTx400% 魔法ダメージ", SkillType::魔杖);
		ActiveSkill::data[29].Set(ASkillTarget::敵全, StatusType::Int, DamageType::魔法 , ASkillType::魔法);
		ActiveSkill::data[29].SetP(1, 0, 4.0, 1.2, 0, 1000, true);

		//クレリック
		ActiveSkill::data.emplace_back(30, "祝福", "弱った味方一人のHPを INTx200% 回復", SkillType::回復);
		ActiveSkill::data[30].Set(ASkillTarget::味方弱者, StatusType::Int, DamageType::魔法, ASkillType::回復);
		ActiveSkill::data[30].SetP(1, 0, 2.0, 1.0, 0, 100);
		ActiveSkill::data.emplace_back(31, "奇跡", "味方全員のHPを INTx150% 回復", SkillType::回復);
		ActiveSkill::data[31].Set(ASkillTarget::味方全員, StatusType::Int, DamageType::魔法, ASkillType::回復);
		ActiveSkill::data[31].SetP(1, 0, 1.5, 1.0, 0, 1000, true);
	}

	std::vector<ActiveSkill> ActiveSkill::data;
}