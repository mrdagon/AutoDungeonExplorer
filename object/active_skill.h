//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	//スキル対象
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
		その他,
		COUNT
	};

	//スキルタグ
	enum class ASkillType
	{
		物理,
		魔法,
		回復,
		//バフ系
		バフ,
		デバフ,
		指定なし,
		COUNT
	};

	enum class BuffType
	{
		与ダメ増減,//割合増減
		被ダメ軽減,//割合増減
		物防,//+数値
		魔防,//+数値
		Str,//+数値
		Dex,//+数値
		Int,//+数値
		命中,//+数値
		回避,//+数値
		挑発,//ターゲットになる
		隠密,//ターゲットから外れる
		速度,//CT速度割合増減
		かばわれ,//数値の隊列の味方にかばわれる、一回かばうと残り時間０
		異常バリア,//状態異常を無効化する、一回無効化すると残り時間０
		両方バリア,//物理/魔法両方に対するバリア
		物理バリア,//物理ダメージを数値分吸収
		魔法バリア,//魔法ダメージを数値分吸収
		再生,//時間経過で回復
		祝福,//回復効果低減 or 増加
		復活,//気絶しても回復する
		分身,//スキルのHit数が増加、攻撃を受けると回避して分身消滅

		//デメリットのみのやつ
		出血,//行動時ダメージ
		猛毒,//一定時間毎にダメージ
		スタン,//一時行動不能、回避減少
		麻痺,//物理スキルの速度低下、回避減少？
		沈黙,//魔法スキルの速度低下
		暗闇,//物理スキルの命中低下、回避減少
		混乱,//攻撃対象が敵味方ランダムに
		石化,//行動不能、回復が遅い、回避０
		睡眠,//行動不能、ダメージで回復、回避０
		宣告,//時間経過で気絶
		COUNT
	};

	//追加効果
	enum class ASkillSubType
	{
		//実質bool値
		必中,
		隠れる無視,
		挑発無視,
		異常回復,

		//double値
		防御貫通,//1で完全無視
		回避貫通,
		超過回復,//最大HPを超えた分バリアを貼る
		ダメージ幅,//1で0～2.0倍
		バフ延長,//-1で解除、1で持続倍増
		デバフ延長,//-1で解除、1で持続倍増
		バフ強化,//-0.5で半減、1で倍増
		デバフ強化,//-0.5で半減、1で倍増
		先制,//1で戦闘開始時100%
		吸収,//1で与えたダメージと同じだけ回復
		コスト,//1で残りHPの100%消費
		全力,//自分のHPが100%なら威力増加
		窮地,//自分のHPが30%以下なら威力増加
		反撃,//ダメージを受けるスキルを食らった時数値分CTが貯まる
		COUNT
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
			this->ID = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->Img = &MIcon::スキル[系統];
		}

		void Set(ASkillTarget 対象,StatusType 依存ステータス,DamageType 属性,ASkillType スキル種)
		{
			this->対象 = 対象;
			this->属性 = 属性;
			this->依存ステータス = 依存ステータス;
			this->種類 = スキル種;

			for (auto& it : バフ反映率)
			{
				it = 0;
			}
			for (auto& it : バフ確率)
			{
				it = 0;
			}
			for (auto& it : バフ持続)
			{
				it = 0;
			}
			for (auto& it : 追加効果)
			{
				it = 0;
			}

		}

		void SetEffect(BuffType 効果種, double 効果量, int 効果時間, double 効果発動率 = 1.0)
		{
			バフ反映率[効果種] = 効果量;
			バフ確率[効果種] = 効果発動率;
			バフ持続[効果種] = 効果時間;
		}

		void SetP(int 効果回数, double 効果量, double ステータス反映率,double 命中, double 効果時間, double 必要チャージ, bool is奥義 = false)
		{
			this->Hit数 = 効果回数;//ランダムだったり単体に多段攻撃
			this->基礎効果 = 効果量;
			this->反映率 = ステータス反映率;
			//効果時間は未使用
			this->命中 = 命中;

			this->必要クールタイム = 必要チャージ;
		}

		ID_ASkill ID;
		std::string 名前;
		std::string 説明;

		Image* Img;//スキルアイコン

		EffectAnimeType 戦闘エフェクト = EffectAnimeType::斬;

		ASkillTarget 対象;
		int 範囲 = 1;

		StatusType 依存ステータス;
		FormationType 適正隊列;
		ASkillType 種類;

		DamageType 属性;
		DamageSubType サブ属性;

		ItemType 装備種 = ItemType::すべて;

		ID_ASkill 連続スキル;

		int Hit数 = 1;//多段ヒット数
		double 命中 = 1.0;

		double 基礎効果 = 0;//固定ダメージ
		double 反映率 = 0;

		double 会心率 = 0.05;
		double 会心倍率 = 1.5;

		double 必要クールタイム;

		//バフ効果
		EnumArray<double, BuffType> バフ基礎値;
		EnumArray<double, BuffType> バフ反映率;
		EnumArray<double, BuffType> バフ確率;
		EnumArray<int, BuffType> バフ持続;

		//追加効果など
		EnumArray<double, ASkillSubType> 追加効果;
		bool is自己バフ = false;//バフ効果の対象が命中した相手でなく自分になる
		double 減衰率 = 1.0;//2番目以降のターゲットへのダメージ倍率

		int 必要SP = 5;
	};

	/*ダメージ計算用*/
	class ASkillEffect
	{
	public:
		EffectAnimeType 戦闘エフェクト;

		ASkillTarget 対象;
		int 範囲 = 1;

		StatusType 依存ステータス;
		FormationType 適正隊列;
		ASkillType 種類;

		DamageType 属性;
		DamageSubType サブ属性;

		ItemType 装備種 = ItemType::すべて;

		int Hit数 = 1;//多段ヒット数
		double 命中 = 1.0;

		double 基礎効果 = 0;//固定ダメージ
		double 反映率 = 0;

		double 会心率 = 0.05;
		double 会心倍率 = 1.5;

		//バフ効果
		EnumArray<double, BuffType> バフ基礎値;
		EnumArray<double, BuffType> バフ反映率;
		EnumArray<double, BuffType> バフ確率;
		EnumArray<int, BuffType> バフ持続;

		//追加効果など
		EnumArray<double, ASkillSubType> 追加効果;
		bool is自己バフ = false;//バフ効果の対象が命中した相手でなく自分になる
		double 減衰率 = 1.0;//2番目以降のターゲットへのダメージ倍率

		//ASkillにないやつ
		double バフ効果補正 = 1.0;
		double バフ持続補正 = 1.0;

		ASkillEffect(const ActiveSkill* スキルベース) :
			戦闘エフェクト(スキルベース->戦闘エフェクト),
			対象(スキルベース->対象),
			範囲(スキルベース->範囲),
			依存ステータス(スキルベース->依存ステータス),
			適正隊列(スキルベース->適正隊列),
			種類(スキルベース->種類),
			属性(スキルベース->属性),
			サブ属性(スキルベース->サブ属性),
			装備種(スキルベース->装備種),
			Hit数(スキルベース->Hit数),
			命中(スキルベース->命中),
			基礎効果(スキルベース->基礎効果),
			反映率(スキルベース->反映率),
			会心率(スキルベース->会心率),
			会心倍率(スキルベース->会心倍率),
			is自己バフ(スキルベース->is自己バフ),
			減衰率(スキルベース->減衰率)
		{
			for (int a = 0; a < (int)BuffType::COUNT; a++)
			{
				auto s = BuffType(a);
				バフ基礎値[s] = スキルベース->バフ基礎値[s];
				バフ反映率[s] = スキルベース->バフ反映率[s];
				バフ持続[s] = スキルベース->バフ持続[s];
				バフ確率[s] = スキルベース->バフ確率[s];
			}

			for (int a = 0; a < (int)ASkillSubType::COUNT; a++)
			{
				追加効果[ASkillSubType(a)] = スキルベース->追加効果[ASkillSubType(a)];
			}


			//回復とバフは必中(暫定)
			if (種類 == ASkillType::回復 || 種類 == ASkillType::バフ)
			{
				命中 = 10.0;
			}
		}
	};

	void LoadActiveSkill()
	{
		//武器７系統✕２＋ジョブ別スキル１０個
		ActiveSkill::data.emplace_back( 0, "なし" , "スキルなし",SkillType::その他);
		ActiveSkill::data[0].Set(ASkillTarget::その他, StatusType::Str, DamageType::物理, ASkillType::指定なし);
		ActiveSkill::data[0].SetP(1, 0, 0, 0, 0, 999999);

		ActiveSkill::data.emplace_back( 1, "斬撃" , "先頭に STRx100% 物理ダメージ",SkillType::剣);
		ActiveSkill::data.emplace_back( 2, "スラッシュ", "先頭に STRx300% 物理ダメージ", SkillType::剣);
		ActiveSkill::data.emplace_back( 3, "斬撃"  , "先頭に STRx120% 物理ダメージ", SkillType::斧);
		ActiveSkill::data.emplace_back( 4, "兜割り", "先頭に STRx300% 物理ダメージ、防御無視", SkillType::斧);
		ActiveSkill::data.emplace_back( 5, "射撃"  , "ランダムに DEXx120% 物理ダメージ",SkillType::弓);
		ActiveSkill::data.emplace_back( 6, "狙い撃ち", "HPの少ない敵に DEXx300% 物理ダメージ", SkillType::弓);
		ActiveSkill::data.emplace_back( 7, "打撃"  , "先頭に STRx80% 物理ダメージ", SkillType::盾);
		ActiveSkill::data.emplace_back( 8, "挑発"  , "150Tの間 狙われやすくなり、物魔防御+20", SkillType::盾);
		ActiveSkill::data.emplace_back( 9, "魔弾"  , "ランダムに INTx120% 魔法ダメージ",SkillType::魔杖);
		ActiveSkill::data.emplace_back(10, "大爆発", "全体に INTx200% 魔法ダメージ", SkillType::魔杖);
		ActiveSkill::data.emplace_back(11, "打撃"  , "先頭に STRx80% 物理ダメージ",SkillType::神杖);
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
		ActiveSkill::data.emplace_back(21, "炎ブレス", "全体にINTx1.8魔法ダメージ", SkillType::剣);

		ActiveSkill::data[1].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 ,ASkillType::物理);
		ActiveSkill::data[2].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 , ASkillType::物理);
		ActiveSkill::data[3].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 ,ASkillType::物理);
		ActiveSkill::data[4].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理 , ASkillType::物理);
		ActiveSkill::data[5].Set(ASkillTarget::敵ランダム, StatusType::Dex, DamageType::物理 , ASkillType::物理);
		ActiveSkill::data[6].Set(ASkillTarget::敵弱者 , StatusType::Dex, DamageType::物理, ASkillType::物理);
		ActiveSkill::data[7].Set(ASkillTarget::敵前 , StatusType::Str, DamageType::物理, ASkillType::物理);
		ActiveSkill::data[8].Set(ASkillTarget::自分   , StatusType::Str, DamageType::物理 , ASkillType::バフ);
		ActiveSkill::data[8].SetEffect(BuffType::物防, 20, 150);
		ActiveSkill::data[8].SetEffect(BuffType::魔防, 20, 150);
		ActiveSkill::data[8].SetEffect(BuffType::挑発, 20, 150);

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
		ActiveSkill::data[18].範囲 = 2;
		ActiveSkill::data[19].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[20].Set(ASkillTarget::敵前, StatusType::Str, DamageType::物理, ASkillType::物理 );
		ActiveSkill::data[20].範囲 = 3;
		ActiveSkill::data[21].Set(ASkillTarget::敵全, StatusType::Int, DamageType::魔法, ASkillType::魔法 );

		//////////////////////////
		ActiveSkill::data[1].SetP( 1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[2].SetP( 1, 0,3.0, 1.0, 0,  300);
		ActiveSkill::data[3].SetP( 1, 0,1.2, 0.8, 0,  100);
		ActiveSkill::data[4].SetP( 1, 0,3.0, 0.9, 0,  400);
		ActiveSkill::data[5].SetP( 1, 0,1.2, 0.9, 0,  100);
		ActiveSkill::data[6].SetP( 1, 0,3.0, 1.5, 0,  400);
		ActiveSkill::data[7].SetP( 1, 0,0.8, 0.8, 0,  100);
		ActiveSkill::data[8].SetP( 1, 0,0.0, 1.0,100, 300);
		ActiveSkill::data[9].SetP( 1, 0,1.2, 0.9, 0,  110);
		ActiveSkill::data[10].SetP(1, 0,2.0, 0.8, 0,  500);
		ActiveSkill::data[11].SetP(1, 0,0.8, 0.8, 0,  100);
		ActiveSkill::data[12].SetP(1, 0,1.5, 1.0, 0,  400);

		ActiveSkill::data[13].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[14].SetP(1, 0,1.0, 0.8, 0,  100);
		ActiveSkill::data[15].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[16].SetP(1, 0,1.5, 0.8, 0,  100);
		ActiveSkill::data[17].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[18].SetP(1, 0,1.5, 0.8, 0,  100);
		ActiveSkill::data[19].SetP(1, 0,1.0, 0.9, 0,  100);
		ActiveSkill::data[20].SetP(1, 0,0.6, 0.6, 0,  200);
		ActiveSkill::data[21].SetP(1, 0,1.8, 0.7, 0,  700,true);

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
		ActiveSkill::data[24].SetP(1, 0, 0, 1.0, 200, 400);
		ActiveSkill::data[24].SetEffect(BuffType::物防, 30, 200);
		ActiveSkill::data[24].SetEffect(BuffType::魔防, 30, 200);
		ActiveSkill::data[24].SetEffect(BuffType::挑発, 30, 200);

		ActiveSkill::data.emplace_back(25, "大防御", "600Tの間、味方全員の 物/魔防御 + 30 ", SkillType::盾);
		ActiveSkill::data[25].Set(ASkillTarget::味方全員, StatusType::Str, DamageType::物理, ASkillType::バフ);
		ActiveSkill::data[25].SetP(1, 0, 0, 1.0, 600, 1000, true);
		ActiveSkill::data[25].SetEffect(BuffType::物防, 30, 600);
		ActiveSkill::data[25].SetEffect(BuffType::魔防, 30, 600);

		//レンジャー
		ActiveSkill::data.emplace_back(26, "二段攻撃", "ランダムに2回 DEXx150% 物理ダメージ", SkillType::弓);
		ActiveSkill::data[26].Set(ASkillTarget::敵ランダム, StatusType::Dex, DamageType::物理, ASkillType::物理);
		ActiveSkill::data[26].SetP(2, 0, 1.5, 0.7, 0, 400);
		ActiveSkill::data.emplace_back(27, "マジカルアロー", "ランダムに6回 DEXx200% 魔法ダメージ", SkillType::弓);
		ActiveSkill::data[27].Set(ASkillTarget::敵ランダム, StatusType::Dex, DamageType::魔法, ASkillType::物理);
		ActiveSkill::data[27].SetP(6, 0, 2.0, 0.6, 0, 1000, true);

		//ウィザード
		ActiveSkill::data.emplace_back(28, "集中", "400Tの間、自身の INT+30% 上昇", SkillType::INT);
		ActiveSkill::data[28].Set(ASkillTarget::自分, StatusType::Int, DamageType::魔法, ASkillType::バフ);
		ActiveSkill::data[28].SetP(1, 0, 0.3, 0.8, 300, 400);
		ActiveSkill::data[28].SetEffect(BuffType::Int, 0.3, 400);

		ActiveSkill::data.emplace_back(29, "紅蓮地獄", "敵全体に INTx400% 魔法ダメージ", SkillType::魔杖);
		ActiveSkill::data[29].Set(ASkillTarget::敵全, StatusType::Int, DamageType::魔法 , ASkillType::魔法);
		ActiveSkill::data[29].SetP(1, 0, 4.0, 1.2, 0, 1000, true);

		//クレリック
		ActiveSkill::data.emplace_back(30, "祝福", "弱った味方一人のHPを INTx200% 回復", SkillType::回復);
		ActiveSkill::data[30].Set(ASkillTarget::味方弱者, StatusType::Int, DamageType::魔法, ASkillType::回復);
		ActiveSkill::data[30].SetP(1, 0, 2.0, 1.0, 0, 400);
		ActiveSkill::data.emplace_back(31, "奇跡", "味方全員のHPを INTx150% 回復", SkillType::回復);
		ActiveSkill::data[31].Set(ASkillTarget::味方全員, StatusType::Int, DamageType::魔法, ASkillType::回復);
		ActiveSkill::data[31].SetP(1, 0, 1.5, 1.0, 0, 1000, true);
	}

	std::vector<ActiveSkill> ActiveSkill::data;
}