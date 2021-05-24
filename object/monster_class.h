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

		MonsterClass(){}
		ImagePack* image;

		ID_Monster ID;

		std::string 名前;
		std::string 説明;

		CraftType 素材種;

		int レア素材率 = 0;
		int ボスドロップ[2] = {};
		bool isボス;

		//基礎ステータスーLvでスケーリングする
		int 隊列;//0～4

		EnumArray<int, StatusType> ステ;

		std::vector<ActiveSkill*> Aスキル;//最大８個
		std::vector<int> AスキルLv;

		std::vector<PassiveSkill*> Pスキル;//最大８個
		std::vector<int> PスキルLv;

		static void LoadData()
		{
			File file_data("file/data/monster.dat", FileMode::Read, true);
			File file_csv("file/data/monster.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummyA;
				int dummyB;

				data.emplace_back();
				auto& it = data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;

				file_data.Read( dummyA );//画像ID

				it.image = &MUnit::モンスター[dummyA];

				file_data.Read(it.素材種);
				file_data.Read(it.隊列);
				file_data.Read(it.isボス);
				file_data.Read(it.ボスドロップ[0]);
				file_data.Read(it.ボスドロップ[1]);
				file_data.Read(it.レア素材率);

				file_data.Read(it.ステ[StatusType::HP]);
				file_data.Read(it.ステ[StatusType::力]);
				file_data.Read(it.ステ[StatusType::技]);
				file_data.Read(it.ステ[StatusType::知]);
				file_data.Read(it.ステ[StatusType::物防]);
				file_data.Read(it.ステ[StatusType::魔防]);
				file_data.Read(it.ステ[StatusType::命中]);
				file_data.Read(it.ステ[StatusType::回避]);
				file_data.Read(it.ステ[StatusType::会心]);

				for (int b = 0; b < CV::最大敵Aスキル数; b++)
				{
					file_data.Read(dummyA);
					file_data.Read(dummyB);//スキルLv
					it.Aスキル.emplace_back(&ActiveSkill::data[dummyA]);	
				}
				for (int b = 0; b < CV::最大敵Pスキル数; b++)
				{

					file_data.Read(dummyA);
					file_data.Read(dummyB);//スキルLv
					it.Pスキル.emplace_back(&PassiveSkill::data[dummyA]);
					it.PスキルLv.emplace_back(dummyB);
				}

			}
		}
	};
}