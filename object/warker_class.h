//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルメンのクラス*/
	class WarkerClass
	{
	private:
	public:
		static std::vector<WarkerClass> data;

		WarkerClass(JobNo 職種,std::string 名前,std::string 説明,UnitImageType 見た目)
		{
			this->職種 = 職種;
			this->名前 = 名前;
			this->説明 = 説明;
			this->見た目 = 見た目;
		}

		void Set(int Str,int Dex,int Int,int Vit,int Agi)
		{
			this->Str = Str;
			this->Int = Int;
			this->Dex = Dex;
			this->Vit = Vit;
			this->Agi = Agi;
		}

		void SetSkill(std::vector<int> rate)
		{
			for (int a = 0; a < 31; a++)
			{
				this->PSkillRate[a] = rate[a];
			}
		}

		JobNo 職種;

		std::string 名前;
		std::string 説明;
		UnitImageType 見た目;
		int 初期装備[2];

		//基礎ステータスーLvでスケーリングする
		int Str, Int, Dex, Vit, Agi;

		//他ステータス
		int PSkillRate[31];//各スキルの習得確率
	};


	void LoadWarkerClass()
	{
		WarkerClass::data.emplace_back(0, "ファイター", "STR物理職",UnitImageType::傭兵);//90
		WarkerClass::data.emplace_back(1, "ナイト", "VIT前衛職",UnitImageType::重装);//78
		WarkerClass::data.emplace_back(2, "レンジャー", "DEX物理職",UnitImageType::レンジャー);//66
		WarkerClass::data.emplace_back(3, "ウィザード", "INT魔法職",UnitImageType::魔女);//59
		WarkerClass::data.emplace_back(4, "クレリック", "INT回復職",UnitImageType::司祭);//99

		WarkerClass::data[0].Set(14, 10, 5, 12, 10);
		WarkerClass::data[1].Set(11, 10, 7, 15,  9);
		WarkerClass::data[2].Set( 8, 13,10,  8, 12);
		WarkerClass::data[3].Set( 5,  9,15,  7,  8);
		WarkerClass::data[4].Set(10,  7,12, 11,  9);

		for (int a = 0; a < 5; a++)
		{
			WarkerClass::data[a].PSkillRate[0] = 0;
			WarkerClass::data[a].PSkillRate[1] = 1;
			WarkerClass::data[a].PSkillRate[2] = 1;
			WarkerClass::data[a].PSkillRate[3] = 1;
			WarkerClass::data[a].PSkillRate[4] = 1;
			WarkerClass::data[a].PSkillRate[5] = 1;

			for (int b = 6; b < 31; b++)
			{
				WarkerClass::data[a].PSkillRate[b] = 0;
			}
		}

		WarkerClass::data[0].PSkillRate[6] = 2;
		WarkerClass::data[0].PSkillRate[7] = 2;
		WarkerClass::data[0].PSkillRate[16] = 2;
		WarkerClass::data[0].PSkillRate[17] = 2;
		WarkerClass::data[0].PSkillRate[18] = 2;

		WarkerClass::data[1].PSkillRate[12] = 2;
		WarkerClass::data[1].PSkillRate[13] = 2;
		WarkerClass::data[1].PSkillRate[19] = 2;
		WarkerClass::data[1].PSkillRate[20] = 2;
		WarkerClass::data[1].PSkillRate[21] = 2;

		WarkerClass::data[2].PSkillRate[8] = 2;
		WarkerClass::data[2].PSkillRate[9] = 2;
		WarkerClass::data[2].PSkillRate[22] = 2;
		WarkerClass::data[2].PSkillRate[23] = 2;
		WarkerClass::data[2].PSkillRate[24] = 2;

		WarkerClass::data[3].PSkillRate[10] = 2;
		WarkerClass::data[3].PSkillRate[11] = 2;
		WarkerClass::data[3].PSkillRate[25] = 2;
		WarkerClass::data[3].PSkillRate[26] = 2;
		WarkerClass::data[3].PSkillRate[27] = 2;

		WarkerClass::data[4].PSkillRate[14] = 2;
		WarkerClass::data[4].PSkillRate[15] = 2;
		WarkerClass::data[4].PSkillRate[28] = 2;
		WarkerClass::data[4].PSkillRate[29] = 2;
		WarkerClass::data[4].PSkillRate[30] = 2;

		WarkerClass::data[0].初期装備[0] = 1;
		WarkerClass::data[0].初期装備[1] = 6;

		WarkerClass::data[1].初期装備[0] = 3;
		WarkerClass::data[1].初期装備[1] = 6;

		WarkerClass::data[2].初期装備[0] = 2;
		WarkerClass::data[2].初期装備[1] = 7;

		WarkerClass::data[3].初期装備[0] = 5;
		WarkerClass::data[3].初期装備[1] = 8;

		WarkerClass::data[4].初期装備[0] = 4;
		WarkerClass::data[4].初期装備[1] = 7;
		
	}

	std::vector<WarkerClass> WarkerClass::data;
}