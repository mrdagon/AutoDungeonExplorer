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

		void Set(int Str, int Dex, int Int, int Vit, int Agi)
		{
			this->Str = Str;
			this->Int = Int;
			this->Dex = Dex;
			this->Vit = Vit;
			this->Agi = Agi;
		}

		void SetSkill(int askill1, int askill2, int askill3)
		{
			this->ASkill[0] = askill1;
			this->ASkill[1] = askill2;
			this->ASkill[2] = askill3;
		}

		int id;
		MonsterNo 種類;

		std::string 名前;
		std::string 説明;
		UnitImageType 見た目;

		//基礎ステータスーLvでスケーリングする
		int Hp,Str,Int,Dex,Vit,Agi;
		
		//他ステータス
		bool isボス;

		int ASkill[CV::最大Aスキル数] = { 0 };//最大３個とか、レベルで増える？
		int ASkillLv[CV::最大Aスキル数] = { 0 };

		int PSkill習得率[31] = {0};//最大３１個、レベルで増える？
	};

	void LoadMonsterClass()
	{
		MonsterClass::data.emplace_back(0,"スライム","高耐久",UnitImageType::スライム);
		MonsterClass::data.emplace_back(1, "ケルベロス", "高火力",UnitImageType::三頭犬);
		MonsterClass::data.emplace_back(2, "スケルトン", "バランス",UnitImageType::スケルトン);
		MonsterClass::data.emplace_back(3, "ドラゴン", "ボス",UnitImageType::ドラゴン);

		MonsterClass::data[0].Set(5, 5, 5, 10, 5);
		MonsterClass::data[1].Set(10, 5, 5, 5, 7);
		MonsterClass::data[2].Set(7, 7, 7, 7, 7);
		MonsterClass::data[3].Set(15, 15, 15, 15, 15);

		MonsterClass::data[0].SetSkill( 6,0,0 );
		MonsterClass::data[1].SetSkill( 7,0,0 );
		MonsterClass::data[2].SetSkill( 8,0,0 );
		MonsterClass::data[3].SetSkill( 9,0,0 );

	}

	std::vector<MonsterClass> MonsterClass::data;
}