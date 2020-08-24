//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*魔物*/
	class Monster : public Fighter
	{
	private:
	public:
		//固定ステータス
		MonsterClass* 種族;
		int Lv = 0;
		bool isボス = false;
		double 経験値 = 0;
		bool is死亡 = false;//素材獲得判定用
		int 消滅中 = 255;
	
		Monster(const Monster& コピー元):
			種族(コピー元.種族),
			isボス(コピー元.isボス),
			Lv(コピー元.Lv),
			経験値(コピー元.経験値)
		{
			Img = this->種族->Img;
			基礎ステータス計算();
		}


		Monster(ID_Monster 種族, int Lv, bool isボス)
		{
			this->種族 = &MonsterClass::data[種族];
			this->Lv = Lv;
			this->isボス = isボス;
			経験値 = std::pow((double)Lv,1.5) * 10;

			Img = this->種族->Img;

			//基礎ステータス
			基礎ステータス計算();
		}

		void 基礎ステータス計算()
		{
			MonsterClass* type = 種族;

			this->基礎ステ[StatusType::生命] = (int)(type->ステ[StatusType::生命] * (10.0 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::筋力] = (int)(type->ステ[StatusType::筋力] * (10.0 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::知力] = (int)(type->ステ[StatusType::知力] * (10.0 + Lv * 1.2) / 10);
			this->基礎ステ[StatusType::技力] = (int)(type->ステ[StatusType::技力] * (10.0 + Lv * 1.2) / 10);

			this->基礎ステ[StatusType::物防] = type->ステ[StatusType::物防];
			this->基礎ステ[StatusType::魔防] = type->ステ[StatusType::魔防];

			this->基礎ステ[StatusType::命中] = type->ステ[StatusType::命中];
			this->基礎ステ[StatusType::回避] = type->ステ[StatusType::回避];

			this->基礎ステ[StatusType::会心] = type->ステ[StatusType::会心];

			Reset補正ステータス();

			if (isボス)
			{
				this->補正ステ[StatusType::生命] *= 20;
				this->経験値 *= 50;
			}

			this->現在HP = 補正ステ[StatusType::生命];

			//とりあえずアクティブスキルは固定
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				this->アクティブスキル[a] = type->ASkill[a];
				if (this->アクティブスキル[a] != nullptr && this->アクティブスキル[a]->ID > 0)
				{
					クールダウン速度[a] = 1;
				} else {
					クールダウン速度[a] = 0;
				}
				合計クールダウン[a] = 0;

			}
			//とりあえずパッシブスキル無し

			パッシブスキル.clear();
		}
	};
}