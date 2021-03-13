//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>

//BMPFontOutPuterのコード
using namespace SDX;
int main(int argc, char* argv[])
{
	using namespace SDX;
	System::Initialise("BmpFontOutputer", 640, 480);

	//設定ファイルの読み込み
	File file("config.txt", FileMode::Read);
	auto strS = file.GetLineS();

	int size = strS.size();
	Screen::Clear();

	int y = 0;

	//フォントの初期化
	for (unsigned int a = 2; a < strS.size(); ++a)
	{
		Font fontA(strS[1].c_str(), std::atoi(strS[a].c_str()), 0, false);
		if (a == 2)
		{
			fontA.Draw({ 0, y }, Color::White, { "フォント名:", strS[1], "\n文字リスト:", strS[0] });
			y += std::atoi(strS[a].c_str());
		}
		Screen::Flip();
		System::ProcessMessage();
		fontA.MakeBMPFont(strS[0]);
		y += std::atoi(strS[a].c_str());
		fontA.Draw({ 0, y }, Color::White, { "Size = ", std::atoi(strS[a].c_str()), "作成完了" });

		Screen::Flip();
	}

	return 0;
}