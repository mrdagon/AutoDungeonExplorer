namespace SDX_BSC
{
	using namespace SDX;

	namespace Save
	{
		bool SaveAndLoad(FileMode 保存or読み込み)
		{
			//バイナリ形式で保存
			File file("file/save/save.dat", 保存or読み込み, false);

			//ファイルが無いのに読み込もうとしたら初期データにする
			if (file.GetFileMode() == FileMode::None)
			{
				return false;
			}

			return true;
		}

	}
}

