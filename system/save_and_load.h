//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

#include <filesystem>

namespace SDX_ADE
{
	using namespace SDX;

	class SaveData
	{
	public:
		//見出し部分の読み込み
		int id;
		std::string ファイル名;

		bool isクリア;
		double プレイ時間;//単位は分
		int 日数;
		int 最深フロア;
		GameType 難易度;
		ID_Job メインパーティ職業[CV::パーティ人数];

		//保存読込はMainGameClassの関数で実装

		SaveData()
		{}

		SaveData(int id, std::string& ファイル名)
		{
			Loadヘッダー(id , ファイル名);
		}

		static bool Getセーブデータinフォルダ(std::vector<std::string>&ファイル名)
		{
			//フォルダ内のセーブデータファイルをチェック
			const std::string save_folder = "./file/save";

			for (const std::filesystem::directory_entry& it : std::filesystem::directory_iterator( save_folder)) {

				//システムとコンフィグセーブデータはスキップ
				if (it.path().filename().string() == TX::Save_コンフィグファイル名 || it.path().filename().string() == TX::Save_システムファイル名 )
				{
					continue;
				}

				ファイル名.push_back( it.path().filename().string() );
			}

			return true;
		}

		//
		bool Loadヘッダー(int id , std::string& ファイル名)
		{
			//セーブデータ先頭の見出しデータだけ読み込む
			this->id = id;
			this->ファイル名 = ファイル名;
			プレイ時間 = 1000;
			日数 = 100;
			最深フロア = 99;
			難易度 = GameType::ノーマル;
			isクリア = true;

			for (int a = 0; a < CV::パーティ人数; a++)
			{
				メインパーティ職業[a] = a;
			}

			return true;
		}

		//各種累計記録など
		static bool SystemSaveAndLoad(FileMode 保存or読み込み)
		{
			std::string fname = "file/save/";
			fname += TX::Save_システムファイル名;

			File file( fname.c_str() , 保存or読み込み, false);

			return true;
		}
	};	
}