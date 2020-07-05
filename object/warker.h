//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*従業員ベースクラス*/
	class Warker : public Fighter
	{
	private:

	public:

		static std::vector<Warker> data;

		Warker()
		{
			見た目 = UnitImageType(Rand::Get(int(UnitImageType::COUNT) - 1));
			Lv = Rand::Get(100);
			基礎防御[DamageType::物理] = 0;
			基礎防御[DamageType::魔法] = 0;
		}

		void Make(int id , JobNo ジョブ , int Lv , std::string 名前)
		{
			this->ID = id;
			this->Lv = Lv;
			this->ジョブ = ジョブ;

			所属 = -1;

			this->名前 = 名前;

			int job = (int)ジョブ;
			見た目 = Job::data[job].見た目;

			装備[0] = Job::data[job].初期装備[0];
			装備[1] = Job::data[job].初期装備[1];
			装備[2] = 0;

			スキルポイント = Lv + 10;
			経験値 = 0;

			AスキルS[0] = Item::data[装備[0]].Aスキル[0];
			AスキルS[1] = Item::data[装備[0]].Aスキル[1];
			AスキルS[2] = Job::data[job].Aスキル[0];
			AスキルS[3] = Job::data[job].Aスキル[1];

			for (int a = 0; a< CV::最大Pスキル数 ;a++)
			{
				PスキルID[a] = 0;
				isPスキル習得[a] = false;
			}

			//スキルの抽選
			int long total_rate = 0;
			int skill_rate[CV::Pスキル種];

			for (int a = 0; a < CV::Pスキル種; a++)
			{
				total_rate += Job::data[job].PSkillRate[a];
				skill_rate[a] = Job::data[job].PSkillRate[a];
			}

			for (int a = 0; a < CV::最大Pスキル数; a++)
			{
				int r = Rand::Get(total_rate);

				for (int b = 1; b < CV::Pスキル種; b++)
				{
					if (skill_rate[b] <= 0) { continue; }

					r -= skill_rate[b];

					if (r <= 0)
					{
						PスキルID[a] = b;
						total_rate -= skill_rate[b];
						skill_rate[b] = 0;
						break;
					}
				}
			}

			for (int a = 0; a < CV::最大Pスキル数; a++)
			{
				if ( a < 2 || PassiveSkill::data[PスキルID[a]].必要SP <= スキルポイント)
				{
					isPスキル習得[a] = true;
					スキルポイント -= PassiveSkill::data[PスキルID[a]].必要SP;
				} else {
					break;
				}
			}

			static std::vector<Fighter*> 仮メンバー;

			基礎ステータス計算();
			基礎Pスキル補正(仮メンバー,仮メンバー);
		}

		void 装備スキル更新()
		{
			AスキルS[0] = Item::data[装備[0]].Aスキル[0];
			AスキルS[1] = Item::data[装備[0]].Aスキル[1];
		}

		bool is特殊人材;//(解雇不可、イベントに絡む等)

		//●人事関連
		//所属あり、就活中、ニートの３パターン
		int ID;//data配列内のID

		int 所属;//-1なら無所属
		CraftType 製造配置;
		bool is装備更新 = true;

		//●固定ステータス
		std::string 名前;
		UnitImageType 見た目;
		JobNo ジョブ;
		int PスキルID[CV::最大Pスキル数];
		bool isPスキル習得[CV::最大Pスキル数];

		//●Lvアップ時等更新ステータス
		int Lv;
		double 経験値 = 0;
		int スキルポイント;

		int 製造Lv;
		int 製造経験値;

		int 装備[CV::装備部位数];//0が武器、1が防具、2がユニーク

		double 製造力 = 10;


		//UI表示用
		int 探検前Lv;
		int 探検前経験値;
		bool isレベルアップ演出;
		bool isスキル習得演出;

		//●再計算ステータス、戦闘以外

		/*パーティ非所属キャラ用ステータス計算*/
		int Get要求経験値()
		{
			return (2 + Lv * Lv) * CV::要求経験値;
		}

		void レベルアップ判定()
		{
			int 要求exp = Get要求経験値();

			if ( 要求exp >= 経験値){
				return;
			}

			経験値 -= 要求exp;
			Lv += 1;
			スキルポイント += 1;
			isレベルアップ演出 = true;

			//スキル習得チェック
			for (int a = 0; a < CV::最大Pスキル数 ; a++)
			{
				if (isPスキル習得[a] == true){ continue; }

				if (PassiveSkill::data[PスキルID[a]].必要SP <= スキルポイント)
				{
					isスキル習得演出 = true;
					isPスキル習得[a] = true;
					スキルポイント -= PassiveSkill::data[PスキルID[a]].必要SP;
				} else {
					break;
				}
			}

			レベルアップ判定();
		}

		//パッシブ無しの基礎ステータス計算
		void 基礎ステータス計算()
		{
			基礎HP = (int)(Job::data[(int)ジョブ].Hp * (10 + Lv) / 10.0);
			基礎ステ[StatusType::Str] = Job::data[(int)ジョブ].ステ[StatusType::Str] * (10 + Lv) / 10;
			基礎ステ[StatusType::Dex] = Job::data[(int)ジョブ].ステ[StatusType::Dex] * (10 + Lv) / 10;
			基礎ステ[StatusType::Int] = Job::data[(int)ジョブ].ステ[StatusType::Int] * (10 + Lv) / 10;

			基礎防御[DamageType::物理] = Job::data[(int)ジョブ].防御[DamageType::物理];
			基礎防御[DamageType::魔法] = Job::data[(int)ジョブ].防御[DamageType::魔法];

			基礎命中 = Job::data[(int)ジョブ].命中;
			基礎回避 = Job::data[(int)ジョブ].回避;

			Reset補正ステータス();

			for (int a = 0; a < CV::装備部位数; a++)
			{
				最大HP += Item::data[装備[a]].追加Hp;
				補正ステ[StatusType::Str] += Item::data[装備[a]].追加Str;
				補正ステ[StatusType::Dex] += Item::data[装備[a]].追加Dex;
				補正ステ[StatusType::Int] += Item::data[装備[a]].追加Int;

				補正防御[DamageType::物理] += Item::data[装備[a]].防御[DamageType::物理];
				補正防御[DamageType::魔法] += Item::data[装備[a]].防御[DamageType::魔法];

				補正命中 += Item::data[装備[a]].命中;
				補正回避 += Item::data[装備[a]].回避;
			}

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				クールダウン速度[a] = 1;
				合計クールダウン[a] = 0;
			}

			//PスキルSの更新
			PスキルS.clear();
			//習得済みパッシブ
			for (int a = 0; a < CV::最大Pスキル数; a++)
			{
				if ( isPスキル習得[a] == true )
				{
					PスキルS.push_back( &PassiveSkill::data[PスキルID[a]] );
				}
			}

			//装備品パッシブ
			for (int a = 0; a < CV::装備部位数; a++)
			{
				for ( auto& it : Item::data[装備[a]].Pスキル )
				{
					if (it != nullptr && it->id != 0)
					{
						PスキルS.push_back(it);
					}
				}
			}
			
			//製造能力(仮)
			製造力 = 10 + Lv;

			現在HP = 最大HP;

			戦闘後回復 = Game::自動回復;
			素材剥取ランク = 0.0;
			素材収集ランク = 0.0;
			素材剥取量 = 0.0;
			素材収集量 = 0.0;

			//エフェクトとログのリセット
			E速度 = 0;//前出たり、ノックバック
			E反転残り = 0;
			E反転時間 = 0;
			E座標 = 0;
			E光強さ = 0;
			Eダメージ時間 = 0;

			//ログ用
			与ダメージログ = 0;
			受ダメージログ = 0;
			回復ログ = 0;

			//
			探検前Lv = Lv;
			探検前経験値 = (int)経験値;
			isレベルアップ演出 = false;
			isスキル習得演出 = false;
		}

		void 探索終了()
		{
			//経験値の獲得、素材の獲得等の処理

		}

		void 気絶()
		{
			MSound::効果音[SE::味方気絶].Play();
		}
	};

	std::vector<Warker> Warker::data;
}