//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ギルメンのクラス*/
	class ExplorerClass
	{
	private:
	public:
		inline static std::vector<ExplorerClass> data;

		ExplorerClass()
		{}
		//
		ImagePack* ちびimage;
		Image* 立ち絵image;

		Item* 初期装備[CV::装備部位数];
		ActiveSkill* 初期Aスキル[CV::最大Aスキル数];//初期スキル
		std::vector<ActiveSkill*> 習得Aスキル;
		std::vector<PassiveSkill*> 習得Pスキル;

		std::vector<PassiveSkill*> 習得キースキル;

		//
		ID_Job ID;

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
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				data.emplace_back();
				auto& it = data.back();

				it.ID = i;
				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					int first = (int)strs[i][1].find('\t');
					//最初の行が概説
					it.概説 = strs[i][1].substr(0,first);
					//tabを改行に置き換え
					if (strs[i][1].length() > first)
					{
						it.説明 = strs[i][1].substr(first);
						std::replace(it.説明.begin(), it.説明.end(), '\t', '\n');
					}
				}

				it.立ち絵image = &MJob::立ち絵[i];
				it.ちびimage = &MJob::ちび[i];

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

				for (int i = 0; i < 3; i++)
				{
					int id;
					file_data.Read(id);
					it.習得キースキル.emplace_back(&PassiveSkill::data[id]);
				}


				//初期装備 - 同じ系統で一番indexが小さいものをとりあえず装備
				for (int i = 0; i < Item::equip_data.size(); i++)
				{
					if (Item::equip_data[i].種類 == it.武器種)
					{
						it.初期装備[0] = &Item::equip_data[i];
						break;
					}
				}
				for (int i = 0; i < Item::equip_data.size(); i++)
				{
					if (Item::equip_data[i].種類 == it.防具種)
					{
						it.初期装備[1] = &Item::equip_data[i];
						break;
					}
				}

				it.初期装備[2] = &Item::accessory_data[0];//アクセサリーは無し

				for (int i = 0; i < 4; i++)
				{
					it.初期Aスキル[i] = it.習得Aスキル[i];
				}


			}

		}
	};

}