//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class Management
	{
	private:
	public:
		inline static std::vector<Management> data;

		Management()
		{}

		Image* image = nullptr;
		int ID = 0;
		int ランク;//習得レベル

		std::string 名前;
		std::string 説明;

		int 消費資金;

		class Cost
		{
		public:
			CraftType 必要素材種;
			int 必要素材ランク;
			int 必要素材数;
		};

		Cost コスト[CV::投資コスト最大枠数];

		bool is使用可 = false;
		bool is使用済み = false;
		
		/*戦術実行効果*/

		void Active()
		{
			//素材消費
			for (int i = 0; i < CV::投資コスト最大枠数; i++)
			{
				Guild::P->素材数[コスト[i].必要素材種][コスト[i].必要素材ランク] -= コスト[i].必要素材数;
				Guild::P->街経験値 += コスト[i].必要素材数 * (10 + コスト[i].必要素材ランク * 5);
			}

			//ログ
			std::string text = "";
			text = 名前;
			text += "を実行";

			EventLog::Add(text.c_str(), Game::日付, LogType::投資);

			is使用済み = true;
			switch (ID)
			{
			default:
				break;
			case 1:
				Guild::P->最大パーティ数++;
				break;
			case 2:
				Guild::P->経験値倍率 += 0.1;
				break;
			case 3:
				Guild::P->戦闘後回復 += 0.01;
				break;
			}



			//部門Lv上昇判定
			if (!Lv上昇判定()) {

				MSound::効果音[SE::投資実行].Play();
			}
		}

		bool 素材チェック()
		{
			for (int i = 0; i < CV::投資コスト最大枠数; i++)
			{
				if (Guild::P->素材数[コスト[i].必要素材種][コスト[i].必要素材ランク] < コスト[i].必要素材数)
				{
					return false;
				}
			}
			return true;
		}

		bool Lv上昇判定()
		{

			MSound::効果音[SE::投資実行].Play();
			return false;
		}

		static void LoadData()
		{
			File file_data("file/data/invest.dat", FileMode::Read, true);
			File file_csv("file/data/invest.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				data.emplace_back();
				auto& it = data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
					std::replace(it.説明.begin(), it.説明.end(), '$', '\n');
				}

				it.ID = i;

				file_data.Read(dummy);//アイコンID
				it.image = &MIcon::投資[dummy];

				file_data.Read(it.ランク);

				for (int i = 0; i < CV::投資コスト最大枠数; i++)
				{
					file_data.Read(dummy);
					it.コスト[i].必要素材種 = CraftType(dummy);
					file_data.Read(it.コスト[i].必要素材数);
					file_data.Read(it.コスト[i].必要素材ランク);
					it.コスト[i].必要素材ランク--;
				}
			}
		}

		//投資状況を初期化
		static void ResetData()
		{
			for (auto& it : data)
			{
				it.is使用可 = false;
			}
		}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//増加資金と使用回数
		}

		void 操作_クリック()
		{
			//資金足りていたら即実行
			if (素材チェック() == true)
			{
				Active();
			}
		}
	};
}