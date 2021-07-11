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

		bool isボス = false;

		int 消滅中 = 255;//死亡アニメーション用
	
		Monster(const Monster& コピー元):
			種族(コピー元.種族),
			isボス(コピー元.isボス),
			Lv(コピー元.Lv)
		{
			image = this->種族->image;
			基礎ステータス計算();
		}

		Monster(Monster* コピー元) :
			種族(コピー元->種族),
			isボス(コピー元->isボス),
			Lv(コピー元->Lv)
		{
			image = this->種族->image;
			基礎ステータス計算();
		}

		Monster(MonsterClass* 種族, int Lv)
		{
			this->種族 = 種族;
			this->Lv = Lv;			
			this->isボス = 種族->isボス;

			image = this->種族->image;

			//基礎ステータス
			基礎ステータス計算();
		}

		void 基礎ステータス計算()
		{
			this->基礎ステ[StatusType::HP] = int(種族->ステ[StatusType::HP] * (8.8 + Lv * 1.2) / 5);

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
			}

			Reset一時補正ステータス();

			Aスキル.clear();
			for (int a = 0; a < 種族->Aスキル.size() ; a++)
			{
				if ( 種族->Aスキル[a]->ID == 0)
				{
					continue;
				}

				Aスキル.push_back( 種族->Aスキル[a]);
				AスキルLv.push_back(種族->AスキルLv[a]);
				必要クールダウン.push_back(Aスキル[a]->クールタイム);
			}

			Pスキル.clear();
			for (int a = 0; a < 種族->Pスキル.size(); a++)
			{
				Pスキル.push_back(種族->Pスキル[a]);
				PスキルLv.push_back(種族->PスキルLv[a]);
			}

			現在HP = 補正ステ[StatusType::HP];
		}

		int Get経験値()
		{
			return 3 * Lv + Lv * Lv / 4;
		}
	};
}