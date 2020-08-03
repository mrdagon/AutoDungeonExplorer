﻿//Copyright © 2019 (´･@･)
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
			this->Img = &MUnit::ユニット[見た目];
		}

		void Set(int Hp , int Str, int Dex, int Int, int 物防, int 魔防 , int 回避 , int 命中)
		{
			this->ステ[StatusType::Hp] = Hp;
			this->ステ[StatusType::Str] = Str;
			this->ステ[StatusType::Int] = Int;
			this->ステ[StatusType::Dex] = Dex;

			this->ステ[StatusType::物防] = 物防;
			this->ステ[StatusType::魔防] = 魔防;

			this->ステ[StatusType::回避] = 回避;
			this->ステ[StatusType::命中] = 命中;
		}

		void SetSkill(int askill1, int askill2, int askill3)
		{
			this->ASkill[0] = &ActiveSkill::data[askill1];
			this->ASkill[1] = &ActiveSkill::data[askill2];
			this->ASkill[2] = &ActiveSkill::data[askill3];
			this->ASkill[3] = nullptr;
		}

		int id;

		std::string 名前;
		std::string 説明;
		ImagePack *Img;

		ID_Material 通常素材 = 0;
		ID_Material レア素材 = 0;
		double レア素材率 = 0.01;

		//基礎ステータスーLvでスケーリングする
		EnumArray<int, StatusType> ステ;

		ActiveSkill* ASkill[CV::最大Aスキル数] = { 0 };//最大４個とか
		int ASkillLv[CV::最大Aスキル数] = { 0 };//習得レベル[未実装]

		int PSkillID[10] = { 0 };//覚えるPスキル
		int PSkillLv[10] = { 0 };//Pスキルの習得レベル
	};

	void LoadMonsterClass()
	{
		MonsterClass::data.reserve(10);

		MonsterClass::data.emplace_back(0,"スライム","高耐久",UnitImageType::スライム);
		MonsterClass::data.emplace_back(1, "バット", "後列",UnitImageType::三頭犬);
		MonsterClass::data.emplace_back(2, "スケルトン", "バランス",UnitImageType::スケルトン);
		MonsterClass::data.emplace_back(3, "ドラゴン", "ボス",UnitImageType::ドラゴン);

		MonsterClass::data[0].Set(75, 5, 5, 5, 10,10, 0, 0);
		MonsterClass::data[1].Set(30, 10, 10, 10,  0, 0,10,10);
		MonsterClass::data[2].Set(60, 7, 7, 7,  5, 5, 5, 5);
		MonsterClass::data[3].Set(100,40, 40,40,15,15,10,10);

		MonsterClass::data[0].SetSkill( 13,14,0 );
		MonsterClass::data[1].SetSkill( 15,16,0 );
		MonsterClass::data[2].SetSkill( 17,18,0 );
		MonsterClass::data[3].SetSkill( 19,20,21);

		MonsterClass::data[0].通常素材 = 1;
		MonsterClass::data[0].レア素材 = 7;

		MonsterClass::data[1].通常素材 = 3;
		MonsterClass::data[1].レア素材 = 7;

		MonsterClass::data[2].通常素材 = 1;
		MonsterClass::data[2].レア素材 = 5;

		MonsterClass::data[3].通常素材 = 7;
		MonsterClass::data[3].レア素材 = 7;
	}

	std::vector<MonsterClass> MonsterClass::data;
}