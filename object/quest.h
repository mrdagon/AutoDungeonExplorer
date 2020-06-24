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

		int id;
		bool isメイン = false;//main or sub
		int 達成度 = 0;
		int 条件数値;//作る装備の数、倒すモンスターの数など
		int 条件番号;//攻略対象があるクエスト用、ダンジョンIDやらボスIDやら
		bool is受注;
		bool is完了 = false;

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
			Quest::Add("武器を供給せよ", QuestType::装備販売, 3, 100, true);

			Quest::data[0].報酬金 = 1000;
			Quest::data[1].報酬金 = 10000;
			Quest::data[2].報酬金 = 100000;

		}


		static void Add(std::string 名前, QuestType 種類, int 条件番号, int 条件数値, bool is受注)
		{
			EventLog::Add(0, Game::日付, LogDetailType::クエスト受注, (int)data.size() );
			data.emplace_back(名前,種類, 条件番号, 条件数値, is受注);
		}

		/*idはボスIDやら倒した敵数やら*/
		static void 進行処理(QuestType クエスト種,int id )
		{
			for (auto& it : Quest::data)
			{
				if( it.種類 == クエスト種 && !it.is完了 && it.is受注 ) { it.達成度計算(id); }
			}
		}


		void 達成度計算(int id)
		{
			switch (種類)
			{
			case QuestType::装備販売:
				達成度 += id;
				break;
			case QuestType::装備製造:
				達成度 += id;
				break;
			case QuestType::雑魚討伐:
				達成度 += id;
				break;
			case QuestType::ダンジョン発見://なんでもいいから発見
				達成度++;
				break;
			case QuestType::ボス討伐://なんでもいいから討伐
				達成度++;
				break;
			case QuestType::固定ボス討伐://特定ダンジョンのボス討伐
				if (id == 条件数値)
				{
					達成度++;
				}
				break;
			}

			if (達成度 >= 条件数値)
			{
				達成処理();
			}

			return ;
		}

		void 達成処理()
		{
			MSound::効果音[SE::クエスト完了].Play();

			達成度 = 条件数値;
			is完了 = true;
			Guild::P->名声 += 報酬名誉;
			Guild::P->資金 += 報酬金;

			for (auto& it : 次依頼)
			{
				if (it >= 0)
				{
					data[it].is受注 = true;
				}
			}
			
			if (isメイン)
			{
				Game::isメインクエスト = true;
			}
		}


	};

	std::vector<Quest> Quest::data;
}