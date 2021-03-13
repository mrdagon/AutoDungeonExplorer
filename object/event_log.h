//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
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

	/*イベントログ*/
	class EventLog
	{
	private:
	public:
		inline static std::vector<EventLog> logs;

		int 日付;
		LogType 種類;
		std::string テキスト;

		static void Add(const char* テキスト, int 日付, LogType 種類 )
		{
			logs.emplace_back(テキスト, 日付 , 種類);
		}

		EventLog(const char* テキスト, int 日付, LogType 種類) :
			テキスト(テキスト), 日付(日付), 種類(種類)
		{

		}

		static void SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}

	};
}