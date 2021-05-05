//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*経営戦術*/
	class Management
	{
	private:
	public:
		inline static std::vector<Management> data;
		inline static const int 必要経験値[CV::最大投資Lv] =
		{
			500000,
			1000000,
			2000000,
			4000000,
			8000000,
		   15000000,
		   25000000,
		   35000000,
		   50000000,
		   70000000,
		};

		Management()
		{}

		Image* image = nullptr;
		int ID = 0;
		int ランク;//習得レベル

		std::string 名前;
		std::string 説明;

		int 消費資金;

		int 投資Lv = 0;
		int 最大投資Lv = 10;
		bool is使用可 = false;

		int 実行予約 = 0;

		/*戦術実行効果*/
		void Active(Guild* guild)
		{
			//資金消費
			guild->資金 -= 消費資金;
			//ログ
			//EventLog::Add(0, Game::日付, LogType::経営);

			//部門Lv上昇判定
			if (!Lv上昇判定()){

				MSound::効果音[SE::投資実行].Play();
			}
		}

		bool Lv上昇判定()
		{

			MSound::効果音[SE::投資実行].Play();
			return false;
		}

		int Get費用()
		{
			return 消費資金;
		}

		static void LoadData()
		{
			File file_data("file/data/invest.dat", FileMode::Read, true);
			File file_csv("file/data/invest.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

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
				}

				it.ID = i;

				file_data.Read( dummy );//アイコンID
				it.image = &MIcon::投資[dummy];

				file_data.Read(it.ランク);
				file_data.Read(it.消費資金);
				bool dumyy_b;
				file_data.Read(dumyy_b);
			}
		}

		//投資状況を初期化
		static void ResetData()
		{
			for (auto& it : data)
			{
				it.投資Lv = 0;
				it.is使用可 = false;
			}
		}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//増加資金と使用回数
		}

		void 実行予約設定(int 部位)
		{

		}

		void 実行予約解除(int 部位)
		{

		}
	};

}