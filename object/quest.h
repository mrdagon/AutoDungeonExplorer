//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	enum class QuestState
	{
		未発見,		
		受注前,
		進行中,
		完了
	};

	
	/*依頼*/
	class Quest
	{
	public:
		inline static std::vector<Quest> data;

		Image* image;
		Image* 依頼人image;

		QuestType 種類;
		std::string 名前;
		std::string 依頼人名前;
		std::string 説明 = "クエストの説明文を表示するよ[実装中]";

		int ID;
		int 条件数値;//作る装備の数、倒すモンスターの数など

		int 開放フロア = 0;
		QuestState 進行状況 = QuestState::未発見;

		bool is新規 = false;//UI表示用 カーソル合わせたら消える

		int 必要クエスト = -1;//受注に必要なクエスト
		
		ID_Item 報酬アクセサリ = 0;
		int 報酬ゴールド = 0;

		bool is重要クエスト;
		int 対象フロア;
		int 目標日数;
		int 獲得ポイント;

		Quest(){}

		static void LoadData()
		{
			File file_data("file/data/quest.dat", FileMode::Read, true);
			File file_csv("file/data/quest.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

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


				file_data.Read(it.is重要クエスト);
				file_data.Read(it.対象フロア);
				file_data.Read(it.目標日数);
				file_data.Read(it.獲得ポイント);

				int 依頼人ID;
				file_data.Read(依頼人ID);
				it.image = &MIcon::クエスト[it.種類];
				it.依頼人image = MJob::ちび[依頼人ID][0];
				if (it.開放フロア <= 1)
				{
					it.進行状況 = QuestState::進行中;
				} else {
					it.進行状況 = QuestState::未発見;
				}
			}
		}

		//クエスト進行情報を初期化
		static void ResetData()
		{
			for (auto& it : data)
			{
				if (it.進行状況 != QuestState::未発見)
				{
					if (it.開放フロア <= 1)
					{
						it.進行状況 = QuestState::進行中;
					} else {
						it.進行状況 = QuestState::受注前;
					}
				}
				it.is新規 = false;
			}
		}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//達成度、is受注、is完了
		}

		static bool 達成チェック(QuestType 判定種, int id , std::array<int, CV::上限アクセサリ種類> &アクセ所持数 )
		{
			bool isClear = false;

			for (auto& it : data)
			{
				if (it.達成判定(判定種, id ,アクセ所持数) == true)
				{
					isClear = true;
				}
			}

			return isClear;
		}

		static void 開始チェック(int 階層)
		{
			std::string text = "";

			for (int i = 0; i < data.size(); i++)
			{
				if (data[i].開放フロア == 階層)
				{
					data[i].進行状況 = QuestState::進行中;
					text = data[i].名前;
					text += "が開始";
					EventLog::Add(text.c_str(), Game::日付, LogType::依頼);
				}
			}

		}

		void 報酬獲得(std::array<int, CV::上限アクセサリ種類>& アクセ所持数)
		{
			進行状況 = QuestState::完了;
			if (報酬アクセサリ > 0)
			{
				アクセ所持数[報酬アクセサリ]++;
			}
		}

		/*idはボスIDやら倒した敵数やら*/
		bool 達成判定(QuestType 判定種 ,int id , std::array<int, CV::上限アクセサリ種類>& アクセ所持数)
		{
			int 達成度 = 0;

			if (進行状況 != QuestState::進行中)
			{
				return false;
			}

			if (種類 != 判定種)
			{
				return false;
			}

			std::string text = "";
			text = 名前;
			text += "を完了";
			EventLog::Add(text.c_str(), Game::日付, LogType::依頼);


			switch (種類)
			{
			case QuestType::ダンジョン発見://特定階層到達
				if (id != 条件数値)
				{
					return false;
				}
				報酬獲得(アクセ所持数);
				break;
			case QuestType::累計FOE討伐://FOEを累計、X体討伐
				if (id < 条件数値)
				{
					return false;
				}
				報酬獲得(アクセ所持数);
				break;
			case QuestType::固定FOE討伐://特定フロアのボス討伐
				if (id != 条件数値)
				{
					return false;
				}
				Game::isClear = true;
				報酬獲得(アクセ所持数);
				break;
			}

			return true;
		}
	};
}