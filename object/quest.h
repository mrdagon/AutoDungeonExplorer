//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*依頼*/
	class Quest
	{
	public:
		inline static std::vector<Quest> data;

		Image* アイコンimage;
		Image* 依頼人image;

		QuestType 種類;
		std::string 名前;
		std::string 説明 = "クエストの説明文を表示するよ[実装中]";

		int ID;
		int 条件数値;//作る装備の数、倒すモンスターの数など

		int 開放フロア = 0;
		bool is受注 = false;
		bool is完了 = false;
		bool is新規 = false;//UI表示用

		int 必要クエスト = -1;//受注に必要なクエスト
		
		ID_Item 報酬アクセサリ = 0;
		int 報酬ゴールド = 0;

		Quest(){}

		static void LoadData()
		{
			File file_data("file/data/quest.dat", FileMode::Read, true);
			File file_csv("file/data/quest.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				data.emplace_back();
				auto& it = data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;

				file_data.Read( it.種類 );//画像ID
				file_data.Read( it.条件数値 );
				file_data.Read( it.開放フロア );
				file_data.Read( it.必要クエスト );
				file_data.Read( it.報酬ゴールド );
				file_data.Read( it.報酬アクセサリ );

				it.アイコンimage = &MIcon::クエスト[it.種類];
				it.依頼人image = MJob::ちび[0][0];
			}
		}

		//クエスト進行情報を初期化
		static void ResetData()
		{
			for (auto& it : data)
			{
				it.is受注 = false;
				it.is完了 = false;
				it.is新規 = false;
			}
		}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//達成度、is受注、is完了
		}

		/*idはボスIDやら倒した敵数やら*/
		bool 達成度計算(int id)
		{
			int 達成度 = 0;

			switch (種類)
			{
			case QuestType::素材売却:
				break;
			case QuestType::アクセサリー発見:
				break;
			case QuestType::遺物収集:
				break;
			case QuestType::魔物発見:
				break;
			case QuestType::ダンジョン発見://なんでもいいから発見
				break;
			case QuestType::ボス討伐://なんでもいいから討伐
				break;
			case QuestType::固定ボス討伐://特定フロアのボス討伐
				break;
			}

			if (達成度 >= 条件数値)
			{
				//EventLog::Add(0, Game::日付, LogType::重要 );
				return true;
			}

			return false;
		}
	};
}