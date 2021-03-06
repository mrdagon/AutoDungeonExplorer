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

		int 画像ID;

		CraftType 素材種;

		int レア素材率 = 0;
		int ボスドロップ = 0;
		bool isボス;

		//基礎ステータスーLvでスケーリングする
		int 隊列;//0～4

		EnumArray<int, StatusType> ステ;

		ActiveSkill* ASkill[CV::最大Aスキル数] = { 0 };//最大４個

		int PSkillID[CV::最大敵Pスキル数] = { 0 };//覚えるPスキル
		int PSkillLv[CV::最大敵Pスキル数] = { 0 };//Pスキルの習得レベル

		static void LoadData()
		{
			File file_data("file/data/monster.dat", FileMode::Read, true);
			File file_csv("file/data/monster.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				data.emplace_back();
				auto& it = data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;
			}
		}
	};
}