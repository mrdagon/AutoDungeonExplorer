//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*依頼*/
	class Quest
	{
	private:
	public:
		static std::vector<Quest> data;

		QuestType 種類;
		std::string 名前;
		std::string 説明 = "クエストの説明文を表示するよ[実装中]";

		bool isメイン;//main or sub
		int id;
		int 達成度 = 0;
		int 条件数値;//作る装備の数、倒すモンスターの数など
		int 条件番号;//ダンジョンIDやら
		bool is受注;//受注前かどうか
		bool is完了 = false;//完了したかどうか

		int 次依頼[3] = {-1,-1,-1};//完了したら受注される依頼
		
		int 報酬金 = 0;
		int 報酬名誉 = 0;

		Quest(std::string 名前, QuestType 種類, int 条件番号, int 条件数値, bool is受注):
			名前(名前),種類(種類),条件数値(条件数値),条件番号(条件番号),is受注(is受注)
		{
			id = (int)data.size();
		}

		static void BetaQuest()
		{
			Quest::Add("洞窟の主を倒せ", QuestType::ボス討伐, 3, 1, true);
			Quest::Add("町の安全確保", QuestType::雑魚討伐, 3, 1000, true);
			Quest::Add("武器を供給せよ", QuestType::装備製造, 3, 100, true);

			Quest::data[0].報酬金 = 1000;
			Quest::data[1].報酬金 = 10000;
			Quest::data[2].報酬金 = 100000;

		}


		static void Add(std::string 名前, QuestType 種類, int 条件番号, int 条件数値, bool is受注)
		{
			EventLog::Add(0, Game::日付, LogDetailType::クエスト受注, (int)data.size() );
			data.emplace_back(名前,種類, 条件番号, 条件数値, is受注);
		}

		int 達成度計算()
		{
			return 1;
		}

	};

	std::vector<Quest> Quest::data;
}