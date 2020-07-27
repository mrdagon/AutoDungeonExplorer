//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	bool ConfigSaveAndLoad(FileMode 保存or読み込み)
	{
		//バイナリ形式で保存
		File file("file/save/config.sav", 保存or読み込み, false);

		file.ReadWrite(Config::BGM設定);
		file.ReadWrite(Config::SE設定);
		file.ReadWrite(Config::解像度設定);

		return false;
	}


	bool SaveAndLoad(FileMode 保存or読み込み, int 読み込みスロット番号)
	{
		//バイナリ形式で保存
		File file("file/save/save.dat", 保存or読み込み, false);

		//ファイルが無いのに読み込もうとしたら初期データにする
		if (file.GetFileMode() == FileMode::None)
		{
			return false;
		}

		//古いバージョンのセーブデータを読み込む時のなんちゃら用
		double version = CV::バージョン;
		file.ReadWrite(version);

		//version 0.01以下は無効
		if (version < CV::バージョン)
		{
			return false;
		}

		return true;
	}
}