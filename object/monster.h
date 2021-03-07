﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*魔物*/
	class Monster : public Battler
	{
	private:
	public:
		//固定ステータス
		MonsterClass* 種族;
		int Lv = 0;
		double 経験値 = 0;

		bool isボス = false;

		int 消滅中 = 255;//死亡アニメーション用
	
		Monster(const Monster& コピー元):
			種族(コピー元.種族),
			isボス(コピー元.isボス),
			Lv(コピー元.Lv),
			経験値(コピー元.経験値)
		{
			image = this->種族->image;
			基礎ステータス計算();
		}

		Monster(ID_Monster 種族, int Lv, bool isボス)
		{
			this->種族 = &MonsterClass::data[種族];
			this->Lv = Lv;
			this->isボス = isボス;
			経験値 = std::pow((double)Lv,1.5) * 10;

			image = this->種族->image;

			//基礎ステータス
			基礎ステータス計算();
		}

		void 基礎ステータス計算()
		{
			MonsterClass* type = 種族;

			this->基礎ステ[StatusType::HP] = (int)(type->ステ[StatusType::HP] * (10.0 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::力] = (int)(type->ステ[StatusType::力] * (10.0 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::知] = (int)(type->ステ[StatusType::知] * (10.0 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::技] = (int)(type->ステ[StatusType::技] * (10.0 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::物防] = type->ステ[StatusType::物防];
			this->基礎ステ[StatusType::魔防] = type->ステ[StatusType::魔防];

			this->基礎ステ[StatusType::命中] = type->ステ[StatusType::命中];
			this->基礎ステ[StatusType::回避] = type->ステ[StatusType::回避];

			this->基礎ステ[StatusType::会心] = type->ステ[StatusType::会心];

			Reset補正ステータス();

			if (isボス)
			{
				this->補正ステ[StatusType::HP] *= 20;
				this->経験値 *= 50;
			}

			this->現在HP = 補正ステ[StatusType::HP];

			//とりあえずアクティブスキルは固定
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				this->アクティブスキル[a] = type->ASkill[a];
				if (this->アクティブスキル[a] != nullptr)
				{
				} else {
				}

			}
			//とりあえずパッシブスキル無し

			パッシブスキル.clear();
		}
	};
}