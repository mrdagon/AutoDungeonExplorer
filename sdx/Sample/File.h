//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/

//ファイルに書き込みと読み込みを行う
bool SampleFile()
{
	using namespace SDX;

	File fileA("test.txt", FileMode::Write, true);
	int a = 100;
	double b = 1.23;
	char c = 123;
	std::string str = "こんにちは";
	fileA.Write(a);
	fileA.Write(b);
	fileA.Write(c);
	fileA.Write(str);
	fileA.Close();

	File fileB("test.txt", FileMode::Read, true);

	int a2;
	double b2;
	char c2;
	std::string str2;
	fileB.Read(a2);
	fileB.Read(b2);
	fileB.Read(c2);
	fileB.Read(str2);
	fileB.Close();

	File fileC("csv.txt", FileMode::Write);
	fileC.Write("1,2,3,4,5");
	fileC.Close();

	File fileD("csv.txt", FileMode::Read);
	std::vector<int> intS = fileD.GetCsvToInt();
	fileD.Close();

	File fileE("csv2.txt", FileMode::Write);
	fileE.Write("1,こんにちは,3,さようなら,5");
	fileE.Close();

	File fileF("csv2.txt", FileMode::Read);
	std::vector<std::string> strS = fileF.GetCsvToString();
	fileF.Close();


	System::Initialise("sample", 640, 480);

	while (System::Update())
	{
		Drawing::String({ 10, 10 }, Color::White, { "書き込みA:", a, " ", b, " ", c, " ", str });
		Drawing::String({ 10, 30 }, Color::White, { "読み込みB:", a2, " ", b2, " ", c2, " ", str2 });

		Drawing::String({ 10, 50 }, Color::White, { "読み込みD:", intS[0], intS[1], intS[2], intS[3], intS[4] });

		Drawing::String({ 10, 70 }, Color::White, { "読み込みF:", strS[0], strS[1], strS[2], strS[3], strS[4], });


		if (Input::key.Return.on){ break;}//Enterで終了
	}

	System::End();
	return true;
}