//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*イベントログ*/
	class EventLog
	{
	private:
	public:
		static std::vector<EventLog> logs;

		static void Add(int ギルド, int 日付, IconType 種類, std::string メッセージ)
		{
			logs.emplace_back(ギルド, 日付, 種類, メッセージ);
		}

		EventLog(int ギルド, int 日付, IconType 種類, std::string メッセージ) :
			ギルド(ギルド), 日付(日付), 種類(種類), メッセージ(メッセージ)
		{}

		int ギルド;
		int 日付;
		std::string メッセージ;
		IconType 種類;
	};

	std::vector<EventLog> EventLog::logs;
}