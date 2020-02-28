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
			就活 = Rand::Get(-1, CV::最大ギルド数 - 1);
			Lv = Rand::Get(100);			
		}

		void Make(int id , JobNo ジョブ , int Lv , std::string 名前)
		{
			this->ID = id;
			this->Lv = Lv;
			this->ジョブ = ジョブ;

			所属 = -1;
			就活 = 0;//とりあえずプレイヤーギルドに求職

			評価[0] = 50;
			評価[1] = 0;
			評価[2] = 0;
			評価[3] = 0;

			忠誠度 = 50;
			退職率 = 0;
			現在賃金 = 150000;
			要求賃金 = 現在賃金;
			来月賃金 = 現在賃金;
			勤続日数 = 0;
			当月労働日数 = 0;
			貢献度 = 0;

			this->名前 = 名前;

			int job = (int)ジョブ;
			見た目 = WarkerClass::data[job].見た目;

			装備[0] = WarkerClass::data[job].初期装備[0];
			装備[1] = WarkerClass::data[job].初期装備[1];

			スキルポイント = Lv + 10;
			経験値 = 0;

			隊列 = FormationType::前列;
			通常攻撃ステータス = Item::data[装備[0]].依存ステータス;

			アクティブスキル[0] = Item::data[装備[0]].Aスキル[0];
			アクティブスキル[1] = Item::data[装備[0]].Aスキル[1];
			アクティブスキル[2] = 0;

			for (int a = 0; a<6 ;a++)
			{
				パッシブスキル[a] = 0;
				isパッシブスキル習得[a] = false;
			}

			//スキルの抽選
			double total_rate = 0;
			double skill_rate[31];

			for (int a = 0; a < 31; a++)
			{
				total_rate += WarkerClass::data[job].PSkillRate[a];
				skill_rate[a] = WarkerClass::data[job].PSkillRate[a];
			}

			for (int a = 0; a < 6; a++)
			{
				double r = Rand::Get(total_rate);

				for (int b = 0; b < 31; b++)
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
				if (PassiveSkill::data[パッシブスキル[a]].必要SP <= スキルポイント)
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
			アクティブスキル[2] = 0;
		}

		bool is特殊人材;//(解雇不可)

		//●人事関連
		//所属あり、就活中、ニートの３パターン
		int ID;

		int 所属;//-1なら無所属
		int 就活;//-1なら非就活

		double 評価[CV::最大ギルド数];

		double 忠誠度;//0.0～100.0
		double 退職率;
		double 現在賃金;
		double 要求賃金;
		double 来月賃金;//来季待遇予定-0なら解雇

		double 勤続日数;
		double 当月労働日数;
		double 貢献度;//要求賃金に影響

		//●固定ステータス
		std::string 名前;
		UnitImageType 見た目;
		JobNo ジョブ;
		int パッシブスキル[CV::最大Pスキル数];
		bool isパッシブスキル習得[CV::最大Pスキル数];

		//●Lvアップ時等更新ステータス
		int Lv;
		int スキルポイント;
		int 装備[2];//0が武器、1が防具

		double 経験値;
		double 製造力 = 10;

		//●再計算ステータス、戦闘以外
		//経験値増加
		//探索速度補正
		//素材収集補正
		//二重製造

		/*パーティ非所属キャラ用ステータス計算*/
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
			基礎Str = WarkerClass::data[(int)ジョブ].Str * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Str + Item::data[装備[1]].追加Str;
			基礎Dex = WarkerClass::data[(int)ジョブ].Dex * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Dex + Item::data[装備[1]].追加Dex;
			基礎Int = WarkerClass::data[(int)ジョブ].Int * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Int + Item::data[装備[1]].追加Int;
			基礎Vit = WarkerClass::data[(int)ジョブ].Vit * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Vit + Item::data[装備[1]].追加Vit;
			基礎Agi = WarkerClass::data[(int)ジョブ].Agi * (10 + Lv) / 10.0 + Item::data[装備[0]].追加Agi + Item::data[装備[1]].追加Agi;

			//アクティブスキル更新
			アクティブスキル[0] = Item::data[装備[0]].Aスキル[0];
			アクティブスキル[1] = Item::data[装備[0]].Aスキル[1];
			アクティブスキル[2] = 0;

			基礎ブロック = 0;
			基礎回避 = 0;

			Pスキル条件チェック(PSkillTime::基礎計算時, 味方, 敵);

			最大HP = 50 + 基礎Vit * 5;
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
			//装備パッシブ-未実装


			//パッシブを追加
			for (auto& no : ps)
			{
				switch (PassiveSkill::data[no].対象)
				{
				case PSkillTarget::自分:
				case PSkillTarget::行動対象:
				case PSkillTarget::敵単体:
				case PSkillTarget::敵全体:
					発動パッシブ.push_back(no);
					break;
				case PSkillTarget::同じ列:
					for (auto&it : 味方)
					{
						if (it->隊列 == this->隊列)
						{
							it->発動パッシブ.push_back(no);
						}
					}
					break;
				case PSkillTarget::味方全員:
					for (auto&it : 味方)
					{
						it->発動パッシブ.push_back(no);
					}
					break;
				case PSkillTarget::味方前列:
					for (auto&it : 味方)
					{
						if (it->隊列 == FormationType::前列)
						{
							it->発動パッシブ.push_back(no);
						}
					}
					break;
				case PSkillTarget::味方後列:
					for (auto&it : 味方)
					{
						if (it->隊列 == FormationType::後列)
						{
							it->発動パッシブ.push_back(no);
						}
					}
					break;
				case PSkillTarget::味方自分以外:
					for (auto&it : 味方)
					{
						if (it != this)
						{
							it->発動パッシブ.push_back(no);
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
			//経験値の処理

		}
	};

	std::vector<Warker> Warker::data;
}