//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
	enum class LogType
	{
		重要,
		経営,
		人事,
		探索,
		製造,
		COUNT
	};

	enum class LogDetailType
	{
		//重要
		クエスト受注,
		//経営
		部門Lv上昇,
		経営戦術使用,
		//人事
		雇用,
		再募集,
		//探索
		地図発見,
		ボス発見,
		ボス討伐,
		//製造
		新装備開発,
		レア装備製造,
		COUNT,
	};

	/*イベントログ*/
	class EventLog
	{
	private:
	public:
		static std::vector<EventLog> logs;

		static void Add(int ギルド, int 日付, LogDetailType 種類 , int 参照ID = 0)
		{
			logs.emplace_back(ギルド, 日付, 種類, 参照ID);
		}

		EventLog(int ギルド, int 日付, LogDetailType 種類, int 参照ID) :
			ギルド(ギルド), 日付(日付), 種類(種類),参照ID(参照ID)
		{
			if ((int)種類 <= (int)LogDetailType::クエスト受注) { 系統 = LogType::重要; }
			else if ((int)種類 <= (int)LogDetailType::経営戦術使用) { 系統 = LogType::経営; }
			else if ((int)種類 <= (int)LogDetailType::再募集) { 系統 = LogType::人事; }
			else if ((int)種類 <= (int)LogDetailType::ボス討伐) { 系統 = LogType::探索; }
			else if ((int)種類 <= (int)LogDetailType::レア装備製造) { 系統 = LogType::製造; }
		}

		int ギルド;
		int 日付;
		int 参照ID;//戦術ID、人材ID、ダンジョンID、アイテムID
		LogType 系統;
		LogDetailType 種類;
	};

	std::vector<EventLog> EventLog::logs;
}