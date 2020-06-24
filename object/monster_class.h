//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*魔物の種族*/
	class MonsterClass
	{
	private:
	public:
		static std::vector<MonsterClass> data;

		MonsterClass(int id, std::string 名前, std::string 説明,UnitImageType 見た目)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->見た目 = 見た目;
		}

		void Set(int Hp , int Str, int Dex, int Int, int 物防, int 魔防 , int 回避 , int 命中)
		{
			this->Hp = Hp;
			this->Str = Str;
			this->Int = Int;
			this->Dex = Dex;

			this->防御[DamageType::物理] = 物防;
			this->防御[DamageType::魔法] = 魔防;

			this->回避 = 回避;
			this->命中 = 命中;
		}

		void SetSkill(int askill1, int askill2, int askill3)
		{
			this->ASkill[0] = askill1;
			this->ASkill[1] = askill2;
			this->ASkill[2] = askill3;
			this->ASkill[3] = 0;
		}

		int id;
		MonsterNo 種類;

		std::string 名前;
		std::string 説明;
		UnitImageType 見た目;

		//基礎ステータスーLvでスケーリングする
		int Hp,Str,Int,Dex,回避,命中;
		EnumArray<int, DamageType> 防御;
		
		
		//他ステータス
		bool isボス;

		int ASkill[CV::最大Aスキル数] = { 0 };//最大４個とか
		int ASkillLv[CV::最大Aスキル数] = { 0 };

		int PSkillID[10] = { 0 };//覚えるPスキル
		int PSkillLv[10] = { 0 };//Pスキルの習得レベル
	};

	void LoadMonsterClass()
	{
		MonsterClass::data.emplace_back(0,"スライム","高耐久",UnitImageType::スライム);
		MonsterClass::data.emplace_back(1, "バット", "後列",UnitImageType::三頭犬);
		MonsterClass::data.emplace_back(2, "スケルトン", "バランス",UnitImageType::スケルトン);
		MonsterClass::data.emplace_back(3, "ドラゴン", "ボス",UnitImageType::ドラゴン);

		MonsterClass::data[0].Set(12, 5, 5, 5, 10,10, 0, 0);
		MonsterClass::data[1].Set(5,  7, 7, 7,  0, 0,10,10);
		MonsterClass::data[2].Set(10, 6, 6, 6,  5, 5, 5, 5);
		MonsterClass::data[3].Set(15,15, 15,15,15,15, 0, 0);

		MonsterClass::data[0].SetSkill( 13,14,0 );
		MonsterClass::data[1].SetSkill( 15,16,0 );
		MonsterClass::data[2].SetSkill( 17,18,0 );
		MonsterClass::data[3].SetSkill( 19,20,21);

	}

	std::vector<MonsterClass> MonsterClass::data;
}