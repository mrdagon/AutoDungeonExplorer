//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ギルメンのクラス*/
	class Job
	{
	private:
	public:
		inline static std::vector<Job> data;

		Job()
		{}
		//
		ImagePack* ちびimage;
		Image* 立ち絵image;

		Item* 初期装備[CV::装備部位数];
		ActiveSkill* 初期Aスキル[CV::最大Aスキル数];//初期スキル
		std::vector<ActiveSkill*> 習得Aスキル;
		std::vector<PassiveSkill*> 習得Pスキル;

		//
		JobType ID;

		std::string 名前;
		std::string 概説 = "説明文- 未設定";//説明の一行目
		std::string 説明;

		ItemType 武器種;
		ItemType 防具種;
		
		//キャラクリ

		//基礎ステータスーLvでスケーリングする
		EnumArray<int, StatusType> ステ;


		static void LoadData()
		{
			File file_data("file/data/job.dat", FileMode::Read, true);
			File file_csv("file/data/job.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				data.emplace_back();
				auto& it = data.back();

				it.ID = (JobType)i;
				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					int first = strs[i][1].find('\t');
					//最初の行が概説
					it.概説 = strs[i][1].substr(0,first);
					//tabを改行に置き換え
					if (strs[i][1].length() > first)
					{
						it.説明 = strs[i][1].substr(first);
						std::replace(it.説明.begin(), it.説明.end(), '\t', '\n');
					}
				}

				file_data.Read(it.武器種);
				file_data.Read(it.防具種);

				file_data.Read(it.ステ[StatusType::HP]);
				file_data.Read(it.ステ[StatusType::力]);
				file_data.Read(it.ステ[StatusType::技]);
				file_data.Read(it.ステ[StatusType::知]);
				file_data.Read(it.ステ[StatusType::物防]);
				file_data.Read(it.ステ[StatusType::魔防]);
				file_data.Read(it.ステ[StatusType::命中]);
				file_data.Read(it.ステ[StatusType::回避]);
				file_data.Read(it.ステ[StatusType::会心]);

				for (int i = 0; i < ActiveSkill::data.size(); i++)
				{
					bool is習得 = false;
					file_data.Read(is習得);

					if (is習得)
					{
						it.習得Aスキル.emplace_back(&ActiveSkill::data[i]);
					}
				}

				for (int i = 0; i < PassiveSkill::data.size(); i++)
				{
					bool is習得 = false;
					file_data.Read(is習得);

					if (is習得)
					{
						it.習得Pスキル.emplace_back(&PassiveSkill::data[i]);
					}
				}
			}

		}
	};

}