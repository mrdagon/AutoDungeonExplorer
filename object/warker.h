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

			アクティブスキル[0] = Item::data[装備[0]].Aスキル[0];
			アクティブスキル[1] = Item::data[装備[0]].Aスキル[1];
			アクティブスキル[2] = Job::data[job].Aスキル[0];
			アクティブスキル[3] = Job::data[job].Aスキル[1];

			for (int a = 0; a< CV::最大Pスキル数 ;a++)
			{
				パッシブスキル[a] = 0;
				isパッシブスキル習得[a] = false;
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
						パッシブスキル[a] = b;
						total_rate -= skill_rate[b];
						skill_rate[b] = 0;
						break;
					}
				}
			}

			for (int a = 0; a < CV::最大Pスキル数; a++)
			{
				if ( a < 2 || PassiveSkill::data[パッシブスキル[a]].必要SP <= スキルポイント)
				{
					isパッシブスキル習得[a] = true;
					スキルポイント -= PassiveSkill::data[パッシブスキル[a]].必要SP;
				} else {
					break;
				}
			}

			表示ステ計算();
		}

		void 装備アップデート()
		{
			アクティブスキル[0] = Item::data[装備[0]].Aスキル[0];
			アクティブスキル[1] = Item::data[装備[0]].Aスキル[1];
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
		int パッシブスキル[CV::最大Pスキル数];
		bool isパッシブスキル習得[CV::最大Pスキル数];

		//●Lvアップ時等更新ステータス
		int Lv;
		double 経験値;
		int スキルポイント;

		int 製造Lv;
		int 製造経験値;

		int 装備[CV::装備部位数];//0が武器、1が防具、2がユニーク

		double 製造力 = 10;

		//●再計算ステータス、戦闘以外

		/*パーティ非所属キャラ用ステータス計算*/
		double Get経験値獲得率()
		{
			int 要求exp = (2 + this->Lv * this->Lv) * CV::要求経験値;
			return this->経験値 / (要求exp);
		}

		void 表示ステ計算()
		{
			std::vector<Fighter*> 味方;
			std::vector<Fighter*> 敵;

			味方.push_back(this);

			所持スキル計算(味方);		
			基礎ステータス計算(味方, 敵);
		}

		bool レベルアップ()
		{
			int 要求exp = (2 + (Lv * Lv) )* CV::要求経験値;

			if (経験値 < 要求exp){ 
				return false;
			}
			経験値 -= 要求exp;
			Lv += 1;
			スキルポイント += 1;
			//スキル習得チェック
			for (int a = 0; a < CV::最大Pスキル数 ; a++)
			{
				if (isパッシブスキル習得[a] == true){ continue; }

				if (PassiveSkill::data[パッシブスキル[a]].必要SP <= スキルポイント)
				{
					isパッシブスキル習得[a] = true;
					スキルポイント -= PassiveSkill::data[パッシブスキル[a]].必要SP;
				} else {
					break;
				}
			}

			return true;
		}

		void 基礎ステータス計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			基礎HP = Job::data[(int)ジョブ].Hp * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Hp + Item::data[装備[1]].追加Hp;
			基礎Str = Job::data[(int)ジョブ].Str * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Str + Item::data[装備[1]].追加Str;
			基礎Dex = Job::data[(int)ジョブ].Dex * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Dex + Item::data[装備[1]].追加Dex;
			基礎Int = Job::data[(int)ジョブ].Int * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Int + Item::data[装備[1]].追加Int;

			//アクティブスキル更新
			アクティブスキル[0] = Item::data[装備[0]].Aスキル[0];
			アクティブスキル[1] = Item::data[装備[0]].Aスキル[1];

			基礎防御[DamageType::物理] = Job::data[(int)ジョブ].防御[DamageType::物理];
			基礎防御[DamageType::魔法] = Job::data[(int)ジョブ].防御[DamageType::魔法];

			基礎命中 = Job::data[(int)ジョブ].命中;
			基礎回避 = Job::data[(int)ジョブ].回避;

			Pスキル条件チェック(PSkillTime::基礎, 味方, 敵);

			最大HP = 基礎HP;
			現在HP = 最大HP;

			//製造能力(仮)
			製造力 = 10 + Lv;
		}

		void 所持スキル計算(std::vector<Fighter*> &味方)
		{
			std::vector<int> ps;
			//習得スキル
			for (int a = 0; a < CV::最大Pスキル数; a++)
			{
				if (isパッシブスキル習得[a] == true && パッシブスキル[a] > 0)
				{
					ps.push_back(パッシブスキル[a]);
				}
			}

			//パッシブを追加
			for (auto& no : ps)
			{
				switch (PassiveSkill::data[no].対象)
				{
				case PSkillTarget::自分:
				case PSkillTarget::敵単体:
				case PSkillTarget::敵全体:
					発動パッシブ.push_back( &PassiveSkill::data[no] );
					break;
				case PSkillTarget::味方全員:
					for (auto&it : 味方)
					{
						it->発動パッシブ.push_back(&PassiveSkill::data[no]);
					}
					break;
				case PSkillTarget::自分以外:
					for (auto&it : 味方)
					{
						if (it != this)
						{
							it->発動パッシブ.push_back(&PassiveSkill::data[no]);
						}
					}
					break;
				}
			}

		}

		void 探索開始()
		{
			//探索系パッシブ効果の処理

		}

		void 戦闘後処理(std::vector<Warker*> &メンバー, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			Pスキル条件チェック(PSkillTime::戦闘勝利時, 味方, 敵);
		}

		void 素材収集処理(std::vector<Warker*> &メンバー)
		{

		}

		void 探索終了()
		{
			//経験値の獲得、素材の獲得等の処理

		}
	};

	std::vector<Warker> Warker::data;
}