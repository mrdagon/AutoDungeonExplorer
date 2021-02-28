//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../system/enum_type.h"

namespace SDX_ADE
{
	using namespace SDX;

	//実装メモ
	//http://tacoika.blog87.fc2.com/blog-entry-590.html

	//タイミング
	enum class PSkillTime
	{
		常時,//探索開始時や編成変更時のみ処理
		戦闘開始時,
		スキル使用時,
		スキル受ける前,
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
		自身が状態異常,
		自身が隠密,
		自身が挑発,
		前列,
		後列
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
		＠スキル強化,
		ダメージ増加,
		スキル威力増減,
		スキル効果増減,
		スキルCT増減,
		アクティブスキル発動,
		物理化,
		魔法化,
		隊列無視,
		必中,
		隠れる無視,
		挑発無視,
		異常回復,
		気絶回復,
		防御貫通,//1で完全無視
		魔防貫通,
		回避貫通,
		超過回復,//最大HPを超えた分バリアを貼る
		バフ固定値,
		バフ反映率,
		バフ延長,
		デバフ延長,
		バフ強化,//-1で解除、1で効果倍増
		デバフ強化,//-1で解除、1で効果倍増
		先制,//1で戦闘開始時100%
		むらっけ,
		吸収,//1で与えたダメージと同じだけ回復
		処刑,
		異常追撃,
		挑発追撃,
		//●バフ、特殊ステータス増加
		与ダメージバフ,
		受ダメージバフ,
		HP1で耐える,
		異常無効,
		デバフ無効,
		身代わり,
		CT減少,
		HP回復,
		未探索発見率増加,
		戦闘後回復,
		剥取増加,
		レア剥取増加,
		採取増加,
		レア採取増加,
		魔物部屋率上昇,
		素材部屋率上昇,
		移動速度上昇,
		//●その他
		HP増加,
		STR増加,
		INT増加,
		DEX増加,
		物防増加,
		魔防増加,
		命中増加,
		回避増加,
		HP割合増加,
		STR割合増加,
		INT割合増加,
		DEX割合増加,
		物防割合増加,
		魔防割合増加,
		経験値増加,
		キーパッシブ,
	};

	/*パッシブスキル*/
	class PassiveSkill
	{
	private:
	public:
		inline static std::vector<PassiveSkill> data;

		PassiveSkill(int id , std::string 名前, std::string 説明 , SkillType 系統, ItemType 装備種, ASkillType Aスキル種)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->Img = &MIcon::スキル[系統];

			this->装備種 = 装備種;//武器種条件
			this->Aスキル種 = Aスキル種;//Aスキル条件
		}

		void SetName(int id,std::string 名前, std::string 説明, SkillType 系統, ItemType 装備種, ASkillType Aスキル種)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->Img = &MIcon::スキル[系統];

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
		ID_PSkill id;
		std::string 名前;
		std::string 説明;
		Image* Img;
		int 必要SP;
		double 効果量;
		bool isキースキル = false;

		//-条件
		ASkillType Aスキル種;//タグ-複数可
		ItemType 装備種;

		PSkillTime タイミング;
		double 発動率;

		PSkillIf 条件;
		double 条件値;
		int 持続時間 = 0;//一時バフ系効果

		PSkillTarget 対象;
		PSkillEffect 効果;

		static void LoadData()
		{

		}
	};

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