//Copyright © 2019 (´･@･)
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
			this->基礎ステ[StatusType::HP] = int(種族->ステ[StatusType::HP] * (8.8 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::力] = int(種族->ステ[StatusType::力] * (8.8 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::知] = int(種族->ステ[StatusType::知] * (8.8 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::技] = int(種族->ステ[StatusType::技] * (8.8 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::物防] = int(種族->ステ[StatusType::物防] * (28.8 + Lv * 1.2) / 30);
			this->基礎ステ[StatusType::魔防] = int(種族->ステ[StatusType::魔防] * (28.8 + Lv * 1.2) / 30);

			this->基礎ステ[StatusType::命中] = int(種族->ステ[StatusType::命中] * (48.8 + Lv * 1.2) / 50);
			this->基礎ステ[StatusType::回避] = int(種族->ステ[StatusType::回避] * (48.8 + Lv * 1.2) / 50);

			this->基礎ステ[StatusType::会心] = 種族->ステ[StatusType::会心];

			if (isボス)
			{
				基礎ステ[StatusType::HP] *= 20;
				経験値 *= 50;
			}

			Reset一時補正ステータス();

			//とりあえずアクティブスキルは固定
			Aスキル数 = 0;

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if ( 種族->Aスキル[a]->ID == 0)
				{
					continue;
				}

				Aスキル[a] = 種族->Aスキル[a];
				AスキルLv[a] = 種族->AスキルLv[a];

				必要クールダウン[a] = Aスキル[a]->クールタイム;

				Aスキル数++;
			}

			Pスキル.clear();
			for (int a = 0; a < 種族->Pスキル.size(); a++)
			{
				Pスキル.push_back(種族->Pスキル[a]);
				PスキルLv.push_back(種族->PスキルLv[a]);
			}

			現在HP = 補正ステ[StatusType::HP];
		}
	};
}