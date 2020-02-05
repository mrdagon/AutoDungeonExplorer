﻿//Copyright © 2019 (´･@･)
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
		int アクティブスキル[CV::最大Aスキル数];
		std::vector<int> 発動パッシブ;//本人のパッシブ、装備、パーティパッシブを格納

		ItemType 武器種;
		StatusType 通常攻撃ステータス;
		FormationType 隊列 = FormationType::前列;

		double 最大HP;
		double 基礎Str, 基礎Dex, 基礎Int, 基礎Vit, 基礎Agi;
		double 基礎ブロック, 基礎回避;
		//●再計算ステータス、戦闘中ステータス、パッシブ計算
		double 現在HP;
		double 補正Str, 補正Dex, 補正Int, 補正Vit, 補正Agi;
		double ブロック;
		double 回避;
		double 敵視;
		//通常攻撃、スキルチャージ
		double 行動値;
		double スキル値[CV::最大Aスキル数];
		//常時パッシブ補正
		double チャージ量補正;
		double スキルダメージ補正;
		double 通常ダメージ補正;

		int 残り行動数;

		//バフ、デバフ、効果量、効果時間
		double ダメージバフ;
		int ダメージバフ残ターン;

		//-スキル効果の一時的変化
		double ダメージバフ付与率;

		//エフェクト用数値
		Color E色 = Color::White;//
		double E攻撃 = 0;//体当たり的モーション
		double E前進 = 0;
		int E光[3] = { 0,0,0 };//赤


		virtual void 基礎ステータス計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵) = 0;
		//戦闘開始時、攻撃,スキル使用後、ダメージ受けた時に処理する
		void ステータス再計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//補正基礎ステ計算
			補正Str = 基礎Str;
			補正Dex = 補正Dex;
			補正Int = 補正Int;
			補正Vit = 補正Vit;
			補正Agi = 補正Agi;

			//敵視計算
			if (隊列 == FormationType::前列) { 敵視 = 1.5; }
			else { 敵視 = 1.0; }

			//ブロック-回避率
			ブロック = 基礎ブロック;
			回避 = 基礎回避;

			//バフ適用
			チャージ量補正 = 1.0;
			スキルダメージ補正 = 1.0;
			通常ダメージ補正 = 1.0;

			if ( ダメージバフ残ターン > 0)
			{
				通常ダメージ補正 += ダメージバフ;
				スキルダメージ補正 += ダメージバフ;
			}

			Pスキル条件チェック(PSkillTime::常時,味方,敵);
		}

		void エフェクト更新()
		{
			if (E攻撃 > 0)
			{
				E前進 += E攻撃;
				if (E前進 > 10) { E攻撃 *= -1; }
			}
			else if (E攻撃 < 0) {
				E前進 += E攻撃;

				if (E前進 < 0)
				{
					E前進 = 0;
					E攻撃 = 0;
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

			E色 = Color(255 - E光[1] - E光[2], 255 - E光[0] - E光[2], 255 - E光[0] - E光[1]);
		}

		void 行動値計算()
		{
			行動値 += 基礎Agi;

		}

		bool 戦闘行動(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//各種スキル
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if (アクティブスキル[a] <= 0) { continue; }

				if (スキル値[a] > ActiveSkill::data[アクティブスキル[a]].必要チャージ)
				{
					Aスキル使用(ActiveSkill::data[アクティブスキル[a]], 味方, 敵);
					スキル値[a] = 0;
					return true;
				}
			}

			通常攻撃(味方, 敵);
			行動値 = 0;
			return true;
		}

		void 通常攻撃(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//パッシブチェック
			Pスキル条件チェック(PSkillTime::通常攻撃時, 味方, 敵);

			//攻撃エフェクト
			E攻撃 = 1.0;
			E攻撃 *= 通常ダメージ補正;

			//攻撃対象を選択
			敵選択(敵)->防御行動((int)std::max(std::max(基礎Str, 基礎Dex), 基礎Int),味方,敵);

			//スキルチャージ
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				スキル値[a] += 10 * チャージ量補正;
			}

			//バフ効果時間減少
			if (ダメージバフ残ターン > 0)
			{
				ダメージバフ残ターン--;
				ダメージバフ = 0;
			}

			//ステータス再計算
			ステータス再計算(味方,敵);
		}

		Fighter* 敵選択(std::vector<Fighter*> &敵)
		{
			//攻撃対象を選択
			double 合計敵視 = 0;
			for (auto& it : 敵)
			{
				if (it->現在HP > 0)
				{
					合計敵視 += it->敵視;
				}
			}

			double rng = Rand::Get(合計敵視);
			for (Fighter* it : 敵)
			{
				if (it->現在HP <= 0) { continue; }

				rng -= it->敵視;
				if (rng <= 0)
				{
					//攻撃
					return it;
				}
			}

			return 敵[0];
		}

		void Aスキル使用(const ActiveSkill& スキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//攻撃エフェクト
			E攻撃 = 1.0;
			E光[2] = 255;//緑

			double スキル威力 = スキル.効果量;
			スキル威力 *= スキルダメージ補正;

			Pスキル条件チェック(PSkillTime::スキル使用時, 味方, 敵, スキル.効果);
			//対象、スキル種、サブ効果により処理色々


			//効果量の計算
			switch (スキル.依存ステータス)
			{
			case StatusType::Str:スキル威力 += 基礎Str * スキル.ステータス反映率; break;
			case StatusType::Dex:スキル威力 += 基礎Dex * スキル.ステータス反映率; break;
			case StatusType::Int:スキル威力 += 基礎Int * スキル.ステータス反映率; break;
			case StatusType::Vit:スキル威力 += 基礎Vit * スキル.ステータス反映率; break;
			case StatusType::Agi:スキル威力 += 基礎Agi * スキル.ステータス反映率; break;
			}

			//対象の計算
			std::vector<Fighter*> 対象;
			Fighter* 弱者 = this;

			switch (スキル.対象)
			{
			case ASkillTarget::自分:
				対象.push_back(this);
				break;
			case ASkillTarget::同じ列:
				break;
			case ASkillTarget::味方弱者:
				for (auto& it : 味方)
				{
					if (it->現在HP > 0 && it->現在HP / it->現在HP < 弱者->現在HP / it->現在HP)
					{
						弱者 = it;
					}
				}
				対象.push_back(弱者);
				break;
			case ASkillTarget::味方一列:
				break;
			case ASkillTarget::味方全員:
				break;
			case ASkillTarget::行動対象:
				break;
			case ASkillTarget::敵単体:
				for (int a = 0; a < スキル.効果回数; a++)
				{
					対象.push_back(敵選択(敵));
				}
				break;
			case ASkillTarget::敵弱者:
				break;
			case ASkillTarget::敵全体:
				for (auto& it : 敵)
				{
					対象.push_back(it);
				}
				break;
			}

			//スキル処理
			for (auto& it : 対象)
			{
				switch (スキル.効果)
				{
				case ASkillType::ダメージ:
					it->防御行動(スキル威力,味方,敵);
					break;
				case ASkillType::回復:
					it->回復行動(スキル威力,ダメージバフ付与率, 味方, 敵);
					break;
				}
			}

			ステータス再計算(味方, 敵);
		}

		/*戦闘開始時の初期化処理、パッシブ*/
		void 戦闘開始(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//共通初期化
			ステータス再計算(味方,敵);

			行動値 = 0;
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				スキル値[a] = 0;
			}

			//パッシブ効果の計算
			Pスキル条件チェック(PSkillTime::戦闘開始時, 味方, 敵);
			ステータス再計算(味方, 敵);
		}

		/*攻撃オブジェクトを引数に取る*/
		void 防御行動(double ダメージ値, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//ブロックによる軽減
			if (ブロック > 0)
			{
				ダメージ値 = ダメージ値 * (1 - ブロック);
			}

			//回避
			if (回避 <= 0 || Rand::Coin(回避) == false)
			{
				現在HP -= ダメージ値;
				E光[0] = 125;//赤色
			}

			//スキルチャージ
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				スキル値[a] += 10 * チャージ量補正;
			}

			ステータス再計算(味方, 敵);
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
				PassiveSkill &ps = PassiveSkill::data[it];

				if (ps.タイミング == タイミング &&
					(ps.Aスキル種 == スキル種 || スキル種 == ASkillType::指定なし) &&
					(ps.装備種 == 武器種 || ps.装備種 == ItemType::すべて) &&
					(ps.発動率 >= 1.0 || Rand::Coin(ps.発動率) == true)
					)
				{
					int num = (int)敵.size();

					switch (ps.条件)
					{
					case PSkillIf::条件無し:
						Pスキル処理(ps, 味方, 敵);
						break;
					case PSkillIf::HP一定以上:
						if (現在HP / 最大HP >= ps.条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::HP一定以下:
						if (現在HP / 最大HP <= ps.条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::敵の数が一定以下:
						for (int a = 0; a < 敵.size(); a++)
						{
							if (敵[a]->現在HP <= 0) { num--; }
						}
						if (num <= ps.条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::敵の数が一定以上:
						for (int a = 0; a < 敵.size(); a++)
						{
							if (敵[a]->現在HP <= 0) { num--; }
						}
						if (num >= ps.条件値) { Pスキル処理(ps, 味方, 敵); }
						break;
					case PSkillIf::ターン数が一定以下:
						break;
					case PSkillIf::ターン数が一定以上:
						break;
					}
				}
			}
		}

		void Pスキル処理(PassiveSkill& スキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			switch (スキル.効果)
			{
				//●アクティブスキル、通常攻撃強化
			case PSkillEffect::ダメージ増加:
			case PSkillEffect::行動値増減:
				行動値 += スキル.効果量;
				break;
			case PSkillEffect::スキル効果増加:
				スキルダメージ補正 += スキル.効果量;
				break;
			case PSkillEffect::スキルチャージ増減:
				チャージ量補正 += スキル.効果量;
				break;
			case PSkillEffect::スキル効果時間増減:
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
			case PSkillEffect::与ダメージ増加:
				if (スキル.対象 == PSkillTarget::自分)
				{
					ダメージバフ = std::max(ダメージバフ, スキル.効果量);
					ダメージバフ残ターン = std::max(ダメージバフ残ターン, 3);
				}
				if (スキル.対象 == PSkillTarget::行動対象)
				{
					ダメージバフ付与率 = スキル.効果量;
				}
				break;
			case PSkillEffect::ブロック率増加:
				基礎ブロック += スキル.効果量;
				break;
			case PSkillEffect::ブロック軽減率増加:
				//●耐久上昇
			case PSkillEffect::ダメージ軽減:
			case PSkillEffect::回避:
				基礎回避 += スキル.効果量;
				break;
			case PSkillEffect::魔法防御:
			case PSkillEffect::狙われやすさ増減:
				敵視 *= スキル.効果量;
				break;
			case PSkillEffect::HP1で耐える:
			case PSkillEffect::デバフ無効:
				//●リアクション系
			case PSkillEffect::身代わり生成:
			case PSkillEffect::攻撃チャージ獲得:
			case PSkillEffect::スキルチャージ獲得:
				for (int a = 0; a < CV::最大Aスキル数; a++)
				{
					スキル値[a] += スキル.効果量;
				}
				break;
			case PSkillEffect::HP回復:
				現在HP += 最大HP * スキル.効果量;
				if (現在HP > 最大HP) { 現在HP = 最大HP; }
				break;
				//●製造
			case PSkillEffect::製造力増加:
			case PSkillEffect::技術経験増加:
			case PSkillEffect::素材使用減少:
			case PSkillEffect::複数製造:
				//●探索
			case PSkillEffect::ボス回避:
			case PSkillEffect::未探索発見率増加:
			case PSkillEffect::罠回避:
			case PSkillEffect::解錠:
			case PSkillEffect::高速探索:
			case PSkillEffect::素材獲得量増加://ここ６種類にする
			case PSkillEffect::素材ランク増加:
				break;
				//●その他
			case PSkillEffect::基礎ステ上昇:
				if (スキル.系統 == SkillType::STR) { 基礎Str += スキル.効果量; }
				if (スキル.系統 == SkillType::DEX) { 基礎Dex += スキル.効果量; }
				if (スキル.系統 == SkillType::INT) { 基礎Int += スキル.効果量; }
				if (スキル.系統 == SkillType::VIT) { 基礎Vit += スキル.効果量; }
				if (スキル.系統 == SkillType::AGI) { 基礎Agi += スキル.効果量; }
				break;
			case PSkillEffect::経験値増加:
			case PSkillEffect::忠誠度補正:
			case PSkillEffect::全滅ペナルティ軽減:
				break;
			}
		}

	};
}