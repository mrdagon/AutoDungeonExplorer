//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*従業員ベースクラス*/
	class Fighter
	{
	private:

	public:
		//●固定、基礎ステータス
		ActiveSkill* アクティブスキル[CV::最大Aスキル数] = {nullptr};
		std::vector<PassiveSkill*> 発動パッシブ;//本人のパッシブ、装備、パーティパッシブを格納

		ItemType 武器種;

		//●基礎ステータス
		double 基礎HP;
		double 基礎Str, 基礎Dex, 基礎Int;
		EnumArray<double,DamageType> 基礎防御;
		double 基礎命中 = 0;
		double 基礎回避 = 0;
		//●装備とパッシブ補正後
		double 最大HP = 100;
		double 補正Str, 補正Dex, 補正Int;
		EnumArray<double, DamageType> 補正防御;
		double 補正命中 = 0;
		double 補正回避 = 0;
		//●計算後ステータス、戦闘中ステータス、パッシブ計算
		double 現在HP;
		//通常攻撃、スキルチャージ
		double スキルチャージ[CV::最大Aスキル数];
		double チャージ量[CV::最大Aスキル数];
		//常時パッシブ補正
		double チャージ量補正;
		double スキルダメージ補正;
		double 通常ダメージ補正;

		//バフ、デバフ、効果量、効果時間
		double ダメージバフ;
		int ダメージバフ残ターン;
		double バフ効果Int, バフ時間Int;
		double バフ効果Str, バフ時間Str;
		double バフ効果Dex, バフ時間Dex;
		int 挑発時間;//

		//-スキル効果の一時的変化
		double ダメージバフ付与率;

		//エフェクト用数値
		double E速度 = 0;//出る
		bool E反転 = false;
		double 座標 = 0;
		int E光[3] = { 0,0,0 };//ダメージ赤、回復緑、補助青


		int Eダメージ;//+ダメージ、-回復
		int Eダメージ時間;

		//ログ用
		double 与ダメージログ;
		double 受ダメージログ;
		double 回復ログ;


		virtual void 基礎ステータス計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵) = 0;
		//戦闘開始時、攻撃,スキル使用後、ダメージ受けた時に処理する
		void ステータス再計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{

		}

		void エフェクト更新()
		{
			if (E速度 != 0)
			{
				座標 += E速度;
				if (座標 > 10 || 座標 < 0)
				{
					if (E反転)
					{
						E速度 *= -1;
						E反転 = false;
					} else {
						座標 = 0;
						E速度 = 0;
					}
				}
			}

			int r = 255;
			int g = 255;
			int b = 255;

			for (int a = 0; a < 3; a++)
			{
				if (E光[a] > 0)
				{
					E光[a] -= 5;
					if (E光[a] < 0) { E光[a] = 0; }
				}
			}
		}

		void 行動値計算()
		{
			;

		}

		bool 戦闘行動(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//各種スキル
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if (アクティブスキル[a] <= 0) { continue; }

				if (スキルチャージ[a] > アクティブスキル[a]->必要チャージ)
				{
					Aスキル使用(アクティブスキル[a], 味方, 敵);
					スキルチャージ[a] = 0;
					return true;
				}
			}

			return true;
		}

		Fighter* 敵選択(std::vector<Fighter*> &敵)
		{
			//攻撃対象を選択

			return 敵[0];
		}

		void Aスキル使用(const ActiveSkill* スキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//攻撃エフェクト
			

			//スキル処理

			//ステータス再計算
		}

		/*戦闘開始時の初期化処理、パッシブ*/
		void 戦闘開始(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//共通初期化
			ステータス再計算(味方,敵);

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				スキルチャージ[a] = 0;
			}

			//パッシブ効果の計算
			Pスキル条件チェック(PSkillTime::戦闘開始時, 味方, 敵);
			ステータス再計算(味方, 敵);
		}

		/*攻撃オブジェクトを引数に取る*/
		void 防御行動(double ダメージ値, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{

		}

		void 回復行動(double 回復値,double バフ付与率, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			現在HP += 回復値;
			if (現在HP > 最大HP) { 現在HP = 最大HP; }

			E光[1] = 125;//緑

			if (バフ付与率 > 0)
			{
				ダメージバフ = std::max(ダメージバフ, バフ付与率);
				ダメージバフ残ターン = std::max(ダメージバフ残ターン, 3);
			}

			ステータス再計算(味方, 敵);
		}

		/*パッシブ処理*/
		virtual void 所持スキル計算(std::vector<Fighter*> &味方) = 0;

		void Pスキル条件チェック(PSkillTime タイミング, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵, ASkillType スキル種 = ASkillType::指定なし)
		{
			for (auto &it : 発動パッシブ)
			{
				PassiveSkill* ps = it;

				if (ps->タイミング == タイミング &&
					(ps->Aスキル種 == スキル種 || スキル種 == ASkillType::指定なし) &&
					(ps->装備種 == 武器種 || ps->装備種 == ItemType::すべて) &&
					(ps->発動率 >= 1.0 || Rand::Coin(ps->発動率) == true)
					)
				{
					int num = (int)敵.size();

					switch (ps->条件)
					{
					case PSkillIf::条件無し:
						Pスキル処理(ps, 味方, 敵);
						break;
					case PSkillIf::HP一定以上:
						if (現在HP / 最大HP >= ps->条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::HP一定以下:
						if (現在HP / 最大HP <= ps->条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::敵の数が一定以下:
						for (int a = 0; a < 敵.size(); a++)
						{
							if (敵[a]->現在HP <= 0) { num--; }
						}
						if (num <= ps->条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::敵の数が一定以上:
						for (int a = 0; a < 敵.size(); a++)
						{
							if (敵[a]->現在HP <= 0) { num--; }
						}
						if (num >= ps->条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					}
				}
			}
		}

		void Pスキル処理(PassiveSkill* スキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			switch (スキル->効果)
			{
				//●アクティブスキル、通常攻撃強化
			case PSkillEffect::ダメージ増加:
				break;
			//case PSkillEffect::スキル効果増加:
				スキルダメージ補正 += スキル->効果量;
				break;
			//case PSkillEffect::スキルチャージ増減:
				チャージ量補正 += スキル->効果量;
				break;
			//case PSkillEffect::スキル効果時間増減:
			case PSkillEffect::アクティブスキルが追加発動:
			case PSkillEffect::対象変更:
			case PSkillEffect::対象を追加:
			case PSkillEffect::攻撃属性変化:
			case PSkillEffect::軽減無視:
			case PSkillEffect::回避無視:
			case PSkillEffect::HP上限超え回復:
			case PSkillEffect::デバフ解除:
				//未実装
				break;
			case PSkillEffect::後列ペナルティ無し:
				//●バフ、特殊ステータス増加
			//case PSkillEffect::与ダメージ増加:
				if (スキル->対象 == PSkillTarget::自分)
				{
					ダメージバフ = std::max(ダメージバフ, スキル->効果量);
					ダメージバフ残ターン = std::max(ダメージバフ残ターン, 3);
				}
				break;
				//●耐久上昇
				break;
			case PSkillEffect::HP1で耐える:
			case PSkillEffect::デバフ無効:
				//●リアクション系
			case PSkillEffect::スキルチャージ獲得:
				for (int a = 0; a < CV::最大Aスキル数; a++)
				{
					スキルチャージ[a] += スキル->効果量;
				}
				break;
			case PSkillEffect::HP回復:
				現在HP += 最大HP * スキル->効果量;
				if (現在HP > 最大HP) { 現在HP = 最大HP; }
				break;
				//●製造
			case PSkillEffect::製造力増加:
			case PSkillEffect::技術経験増加:
			case PSkillEffect::素材使用減少:
			case PSkillEffect::複数製造:
				//●探索
			case PSkillEffect::素材獲得量増加://ここ６種類にする
			case PSkillEffect::素材ランク増加:
				break;
				//●その他
				if (スキル->系統 == SkillType::STR) { 基礎Str += スキル->効果量; }
				if (スキル->系統 == SkillType::DEX) { 基礎Dex += スキル->効果量; }
				if (スキル->系統 == SkillType::INT) { 基礎Int += スキル->効果量; }
				break;
			case PSkillEffect::経験値増加:
			case PSkillEffect::全滅ペナルティ軽減:
				break;
			}
		}

	};
}