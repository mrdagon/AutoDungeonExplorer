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

	enum class LogDetailType
	{
		//重要
		クエスト受注,//○
		クエスト完了,
		//経営
		部門Lv上昇,
		経営戦術使用,
		//人事
		雇用,//
		除名,//
		スキル習得,//
		//探索
		地図発見,
		ボス発見,
		ボス討伐,
		完全探索,
		石版発見,
		//製造
		技術Lv上昇,//○
		新装備開発,//○
		装備Lv上昇,
		レア装備製造,
		COUNT,
	};

	/*イベントログ*/
	class EventLog
	{
	private:
	public:
		inline static std::vector<EventLog> logs;

		static void Add(int ギルド, int 日付, LogDetailType 種類 , int 参照ID = 0)
		{
			logs.emplace_back(ギルド, 日付 , 種類, 参照ID);
		}

		EventLog(int ギルド, int 日付, LogDetailType 種類, int 参照ID) :
			ギルド(ギルド), 日付(日付), 種類(種類),参照ID(参照ID)
		{
			if ((int)種類 <= (int)LogDetailType::クエスト受注) { 系統 = LogType::重要; }
			else if ((int)種類 <= (int)LogDetailType::経営戦術使用) { 系統 = LogType::経営; }
			else if ((int)種類 <= (int)LogDetailType::スキル習得) { 系統 = LogType::人事; }
			else if ((int)種類 <= (int)LogDetailType::ボス討伐) { 系統 = LogType::探索; }
			else if ((int)種類 <= (int)LogDetailType::レア装備製造) { 系統 = LogType::製造; }
		}

		static void SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}

		int ギルド;
		int 日付;
		int 参照ID;//戦術ID、人材ID、ダンジョンID、アイテムID、スキルIDなど
		LogType 系統;
		LogDetailType 種類;
	};
}