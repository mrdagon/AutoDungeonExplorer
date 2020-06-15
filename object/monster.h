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
		MonsterNo 種族;
		int Lv;
		bool isボス;
		double 経験値;

		Monster(MonsterNo 種族, int Lv, bool isボス)
		{
			this->種族 = 種族;
			this->Lv = Lv;
			this->isボス = isボス;
			経験値 = std::pow((double)Lv,1.5) * 10;

			MonsterClass* type = &MonsterClass::data[種族];
			
			//ステータス、パッシブ、アクティブの計算
			//とりあえずアクティブスキルは固定
			this->アクティブスキル[0] = type->ASkill[0];
			this->アクティブスキル[1] = type->ASkill[1];
			this->アクティブスキル[2] = type->ASkill[2];
			//とりあえずパッシブスキル無し

			//基礎ステータス
			this->基礎Str = type->Str * (9.0 + Lv * 1.2) / 10;
			this->基礎Int = type->Int * (9.0 + Lv * 1.2) / 10;
			this->基礎Dex = type->Dex * (9.0 + Lv * 1.2) / 10;
			this->最大HP = 基礎HP;
			
			if (isボス)
			{
				this->最大HP *= 20;
				this->経験値 *= 50;
			}

			this->現在HP = 最大HP;

			基礎回避 = 0;

		}

		void 基礎ステータス計算(std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//とりあえずなし
		}

		void 所持スキル計算(std::vector<Fighter*> &味方)
		{
			//とりあえずスキルなし
		}
	};
}