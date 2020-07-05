//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*魔物*/
	class Monster : public Fighter
	{
	private:
	public:
		//固定ステータス
		MonsterNo 種族 = 0;
		int Lv = 0;
		bool isボス = false;
		double 経験値 = 0;

		Monster(MonsterNo 種族, int Lv, bool isボス)
		{
			this->種族 = 種族;
			this->Lv = Lv;
			this->isボス = isボス;
			経験値 = std::pow((double)Lv,1.5) * 10;

			//基礎ステータス
			基礎ステータス計算();
		}

		void 基礎ステータス計算()
		{
			MonsterClass* type = &MonsterClass::data[種族];

			this->基礎HP = (int)(type->Hp * (10.0 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::Str] = (int)(type->ステ[StatusType::Str] * (10.0 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::Int] = (int)(type->ステ[StatusType::Int] * (10.0 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::Dex] = (int)(type->ステ[StatusType::Dex] * (10.0 + Lv * 1.2) / 10);

			this->基礎防御[DamageType::物理] = type->防御[DamageType::物理];
			this->基礎防御[DamageType::魔法] = type->防御[DamageType::魔法];

			this->基礎命中 = type->命中;
			this->基礎回避 = type->回避;

			Reset補正ステータス();

			if (isボス)
			{
				this->最大HP *= 20;
				this->経験値 *= 50;
			}

			this->現在HP = 最大HP;

			//とりあえずアクティブスキルは固定
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				this->AスキルS[a] = type->ASkill[a];
				if (this->AスキルS[a] != nullptr && this->AスキルS[a]->id > 0)
				{
					クールダウン速度[a] = 1;
				} else {
					クールダウン速度[a] = 0;
				}
				合計クールダウン[a] = 0;

			}
			//とりあえずパッシブスキル無し

			PスキルS.clear();
		}

		void 気絶()
		{
			MSound::効果音[SE::敵気絶].Play();
		}
	};
}