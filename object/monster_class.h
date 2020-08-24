//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*魔物の種族*/
	class MonsterClass
	{
	private:
	public:
		inline static std::vector<MonsterClass> data;

		MonsterClass(int id, std::string 名前, std::string 説明,UnitImageType 見た目)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->Img = &MUnit::ユニット[見た目];
		}

		void Set(int Hp , int Str, int Dex, int Int, int 物防, int 魔防 , int 回避 , int 命中)
		{
			this->ステ[StatusType::生命] = Hp;
			this->ステ[StatusType::筋力] = Str;
			this->ステ[StatusType::知力] = Int;
			this->ステ[StatusType::技力] = Dex;

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

		ID_Material 素材 = 0;
		double レア素材率 = 0.01;

		//基礎ステータスーLvでスケーリングする
		EnumArray<int, StatusType> ステ;

		ActiveSkill* ASkill[CV::最大Aスキル数] = { 0 };//最大４個とか
		int ASkillLv[CV::最大Aスキル数] = { 0 };//習得レベル[未実装]

		int PSkillID[10] = { 0 };//覚えるPスキル
		int PSkillLv[10] = { 0 };//Pスキルの習得レベル

		static void LoadData()
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

			MonsterClass::data[0].素材 = 1;

			MonsterClass::data[1].素材 = 3;

			MonsterClass::data[2].素材 = 1;

			MonsterClass::data[3].素材 = 7;
		}
	};
}