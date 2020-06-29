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
		EnumArray<double, StatusType> 基礎ステ;
		EnumArray<double,DamageType> 基礎防御;
		double 基礎命中 = 0;
		double 基礎回避 = 0;
		//●装備とパッシブ補正後
		double 最大HP = 100;
		EnumArray<double, StatusType> 補正ステ;
		EnumArray<double, DamageType> 補正防御;
		double 補正命中 = 0;
		double 補正回避 = 0;
		//●計算後ステータス、戦闘中ステータス、パッシブ計算
		double 現在HP;
		//スキルクールダウン
		double 合計クールダウン[CV::最大Aスキル数];
		double クールダウン速度[CV::最大Aスキル数];

		//一時的なバフ兼デバフ、効果量、効果時間
		double ダメージバフ効果;
		int ダメージバフ時間;
		EnumArray<double, DamageType> 防御バフ効果;
		EnumArray<int, DamageType> 防御バフ時間;
		EnumArray<double, StatusType> ステバフ効果;
		EnumArray<int, StatusType> ステバフ時間;
		double 命中バフ効果, 回避バフ効果;
		int 挑発時間, 命中バフ時間,回避バフ時間;

		//状態異常
		int スキル待機 = 0;

		//エフェクト用数値
		double E速度 = 0;//前出たり、ノックバック
		bool E反転 = false;
		double E座標 = 0;
		int E光[3] = { 0,0,0 };//ダメージ赤、回復緑、補助青

		int Eダメージ;//+ダメージ、-回復
		int Eダメージ時間;

		//ログ用
		double 与ダメージログ;
		double 受ダメージログ;
		double 回復ログ;

		//探索スキル効果
		double 戦闘後回復 = 0.0;
		double 素材剥取ランク = 0.0;
		double 素材収集ランク = 0.0;
		double 素材剥取量 = 0.0;
		double 素材収集量 = 0.0;

		virtual void 基礎ステータス計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵) = 0;

		//一時バフ補正後ステータス取得
		double Getステ(StatusType ステータス種)
		{
			return (ステバフ時間[ステータス種] > 0) ? 補正ステ[ステータス種] * ステバフ効果[ステータス種] : 補正ステ[ステータス種];
		}

		double Get防御(DamageType ダメージ種)
		{
			return (防御バフ時間[ダメージ種] > 0) ? 補正防御[ダメージ種] * 防御バフ効果[ダメージ種] : 補正防御[ダメージ種];
		}

		double Get命中()
		{
			return (命中バフ時間 > 0) ? 補正命中 + 命中バフ効果 : 補正命中;
		}

		double Get回避()
		{
			return (回避バフ時間 > 0) ? 補正回避 + 回避バフ効果 : 補正回避;
		}

		double Getダメージ()
		{
			return (ダメージバフ時間 > 0) ? ダメージバフ効果 : 1.0;
		}

		//探索開始時や装備更新時の処理
		void ステータス再計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{

		}

		void エフェクト更新()
		{
			if (E速度 != 0)
			{
				E座標 += E速度;
				if (E座標 > 10 || E座標 < 0)
				{
					if (E反転)
					{
						E速度 *= -1;
						E反転 = false;
					} else {
						E座標 = 0;
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

		//スキルクールダウン処理と発動処理
		void 戦闘中処理(std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{
			if (現在HP <= 0) { return; }

			//スキル発動チェック
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if (アクティブスキル[a] == nullptr) { continue; }

				合計クールダウン[a] += クールダウン速度[a];
				if (スキル待機 <= 0 && 合計クールダウン[a] > アクティブスキル[a]->必要チャージ)
				{
					Aスキル使用(アクティブスキル[a], 味方, 敵);
					合計クールダウン[a] -= アクティブスキル[a]->必要チャージ;
				}
			}
			//バフ時間減少等
			ダメージバフ時間--;
			挑発時間--;
			スキル待機--;
			for (auto& it : ステバフ時間){ it--; }
			for (auto& it : 防御バフ時間) { it--; }

			//エフェクト更新は戦闘中以外も処理してるのでここではやらない
		}

		/*戦闘開始時の初期化処理、パッシブ*/
		void 戦闘開始(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//初期化
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				合計クールダウン[a] = Rand::Get(100);
			}

			//バフ時間減少等
			ダメージバフ時間 = 0;
			挑発時間 = 0;
			スキル待機 = 0;
			for (auto& it : ステバフ時間) { it = 0; }
			for (auto& it : 防御バフ時間) { it = 0; }

			//パッシブ効果の計算
			Pスキル条件チェック(PSkillTime::戦闘開始時, nullptr, 味方, 敵);
		}

		/*戦闘後処理、パッシブ*/
		void 戦闘終了(std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{

		}


		std::vector<Fighter*> 対象選択(const ASkillEffect Aスキル, std::vector<Fighter*>&味方,std::vector<Fighter*> &敵)
		{
			std::vector<Fighter*> 対象;
			//攻撃or回復対象を選択

			return 対象;
		}

		void Aスキル使用(const ActiveSkill* スキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//攻撃エフェクト
			E速度 = 10;
			E座標 = 0;
			E反転 = false;

			//スキル処理
			ASkillEffect ase(スキル);
			//パッシブ補正、威力命中補正、追加効果追加等
			Pスキル条件チェック(PSkillTime::スキル使用時, &ase, 味方, 敵);

			//対象選択
			std::vector<Fighter*> 対象 = 対象選択(ase, 味方, 敵);

			//効果発動
			for (auto& it : 対象)
			{
				it->スキル受け(ase, this , 味方 , 敵);
			}

			スキル待機 = 10;
		}


		/*攻撃オブジェクトを引数に取る、攻撃や回復を受けた側の処理*/
		void スキル受け(ASkillEffect& Aスキル,Fighter* スキル使用者,std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{
			//威力マイナスなら回復、+なら攻撃スキル

			//Pスキル処理
			Pスキル条件チェック(PSkillTime::回復した時, &Aスキル, 味方, 敵);
			Pスキル条件チェック(PSkillTime::攻撃を受けた時, &Aスキル, 味方, 敵);
			Pスキル条件チェック(PSkillTime::回避した時, &Aスキル, 味方, 敵);

			//上限下限、超過HPチェック

			//気絶チェック

			//ダメージ or 回復 or 回避エフェクト

		}

		/*パッシブ処理*/
		virtual void 所持スキル計算(std::vector<Fighter*> &味方) = 0;

		void Pスキル条件チェック(PSkillTime タイミング,ASkillEffect* Aスキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			for (auto &it : 発動パッシブ)
			{
				if (it->タイミング != タイミング) { return; }
				if (Aスキル != nullptr)
				{
					if( it->Aスキル種 != Aスキル->種類) { return; }
					if ( it->装備種 != ItemType::すべて && it->装備種 != Aスキル->装備種) { return; }
					if (it->is奥義 == true && Aスキル->is奥義 == false) { return; }
					if (it->系統 != Aスキル->系統) { return; }
					if (it->発動率 <= 0.0 || !Rand::Coin(it->発動率)) { return; }
				}

				int num = (int)敵.size();

				switch (it->条件)
				{
				case PSkillIf::HP一定以上:
					if (現在HP / 最大HP < it->条件値) { return; }
					break;
				case PSkillIf::HP一定以下:
					if (現在HP / 最大HP > it->条件値) { return; }
					break;
				case PSkillIf::敵の数が一定以下:
					for (int a = 0; a < 敵.size(); a++)
					{
						if (敵[a]->現在HP <= 0) { num--; }
					}
					if (num > it->条件値) { return; }
					break;
				case PSkillIf::敵の数が一定以上:
					for (int a = 0; a < 敵.size(); a++)
					{
						if (敵[a]->現在HP <= 0) { num--; }
					}
					if (num < it->条件値) { return; }
					break;
				}
	
				Pスキル処理(it, Aスキル, 味方, 敵);
			}
		}

		void Pスキル処理(PassiveSkill* スキル,ASkillEffect* Aスキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//とりあえずβのだけ実装
			switch (スキル->効果)
			{
			case PSkillEffect::HP増加:
			case PSkillEffect::STR増加:
			case PSkillEffect::INT増加:
			case PSkillEffect::DEX増加:
			case PSkillEffect::物防増加:
			case PSkillEffect::魔防増加:
			case PSkillEffect::命中増加:
			case PSkillEffect::回避増加:

			case PSkillEffect::収集量増加:
			case PSkillEffect::収集ランク増加:
			case PSkillEffect::剥取量増加:
			case PSkillEffect::剥取ランク増加:

			case PSkillEffect::スキル威力増減:
			case PSkillEffect::スキル効果増減:
			case PSkillEffect::スキルCT増減:
			case PSkillEffect::スキル持続増減:
			case PSkillEffect::戦闘後回復:

			case PSkillEffect::与ダメージバフ:
			case PSkillEffect::受ダメージバフ:
			case PSkillEffect::スキルチャージ獲得:
				break;
			}
		}

	};
}