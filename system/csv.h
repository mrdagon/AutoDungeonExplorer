//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <stdexcept>

namespace SDX_ADE
{
	using namespace SDX;
	//レイアウトCSV用変数
	namespace CSV
	{
		static int input_mode = 0;//数値変更モード

		static int line = 0;//現在の行数
		static int page = 0;//現在のページ
		static int page_max = 1;//合計ページ数
		static bool isDebugInput = true;

		static std::vector<std::string> page_name;//各ページの名前
		static std::vector<int> page_count;//各ページの行数
		static std::vector<std::vector<int>> I;
		static std::vector<std::vector<std::string>> memo;//各セルのメモ
	}

	void CSVReadMemo()
	{
		//各行のメモを読み込む
		File file("file/layout/layout_memo.txt", FileMode::Read, true);

		char bom;
		file.Read(bom);
		file.Read(bom);
		file.Read(bom);

		auto strS = file.GetCsvToString2();
		CSV::memo.resize(CSV::page_max);

		for (int a = 0; a < CSV::page_max; a++)
		{
			for (int b = 0; b < CSV::page_count[a]; b++)
			{
				if (strS.size() > a&& strS[a].size() > b)
				{
					CSV::memo[a].push_back(strS[a][b]);
				} else {
					CSV::memo[a].push_back("-");
				}
			}
		}
	}

	void CSVWriteMemo()
	{
		std::string fileName = "file/layout/layout_memo.txt";
		//デバッグ用数値をテキストで保存
		File file(fileName.c_str(), FileMode::Write, true);

		//BOMを最初に入れる
		char bom[3] = { (char)0xEF ,(char)0xBB ,(char)0xBF };
		file.Write(bom[0]);
		file.Write(bom[1]);
		file.Write(bom[2]);

		std::string buffer = "";

		for (int a = 0; a < CSV::page_max; a++)
		{
			buffer = "";
			for (int b = 0; b < CSV::page_count[a]; b++)
			{
				buffer += CSV::memo[a][b];
				buffer += ",";
			}

			file.AddLine(buffer);
		}
	}


	bool CSVInit()
	{
		//ファイル形式
		//1行目selectの値,ページ数,最大ページ数
		//2行目にページ名、
		//3行目に行数
		//4行目以降、最初にページ名、ページの項目数、以降データをカンマ区切りで

		//デバッグ用数値をテキストから読み込む
		File file("file/layout/layout_data.txt", FileMode::Read, true);
		
		char bom;
		file.Read(bom);
		file.Read(bom);
		file.Read(bom);
		
		auto strS = file.GetCsvToString2();

		CSV::line = std::stoi(strS[0][0]);
		CSV::page = std::stoi(strS[0][1]);
		CSV::page_max = std::stoi(strS[0][2]);

		CSV::I.resize(CSV::page_max);

		for (int a = 0; a < CSV::page_max; a++)
		{
			CSV::page_name.push_back(strS[1][a]);
		}
		for (int a = 0; a < CSV::page_max; a++)
		{
			CSV::page_count.push_back(std::stoi(strS[2][a]));
		}
		
		for (int a = 0; a < CSV::page_max; a++)
		{
			for (int b = 0; b < CSV::page_count[a]; b++)
			{
				CSV::I[a].push_back(std::stoi(strS[a+3][b]));
			}
		}

		CSVReadMemo();

		return true;
	}

	void CSVEnd(std::string fileName)
	{
		//デバッグ用数値をテキストで保存
		File file(fileName.c_str(), FileMode::Write, true);

		//BOMを最初に入れる
		char bom[3] = { (char)0xEF ,(char)0xBB ,(char)0xBF };
		file.Write(bom[0]);
		file.Write(bom[1]);
		file.Write(bom[2]);

		file.AddLine({ CSV::line ,",",CSV::page,",",CSV::page_max });

		std::string buffer = "";

		for (int a = 0; a < CSV::page_max; a++)
		{
			buffer += CSV::page_name[a];
			buffer += ",";
		}
		file.AddLine(buffer);

		buffer = "";

		for (int a = 0; a < CSV::page_max; a++)
		{
			buffer += std::to_string(CSV::page_count[a]);
			buffer += ",";
		}
		file.AddLine(buffer);

		
		for (int a = 0; a < CSV::page_max; a++)
		{
			buffer = "";
			for (int b = 0; b < CSV::page_count[a]; b++)
			{
				buffer += std::to_string(CSV::I[a][b]);
				buffer += ",";
			}

			file.AddLine( buffer );
		}

		CSVWriteMemo();
	}

	void CSVDraw()
	{
		MFont::LSize.DrawBold({ 10,75 }, Color::White,Color::Black, System::inputText + System::textComposition);
		MFont::MSize.DrawBold({ 10,100 }, Color::White, Color::Black, CSV::page_name[CSV::page]);

		MFont::MSize.DrawBold({ 110,75 }, Color::White, Color::Black, System::textComposition);

		int p_no = CSV::line/30;//30ライン以上ある場合ずらす

		if (CSV::input_mode == 0)
		{
			MFont::SSize.DrawBold({ 10,50 }, Color::White, Color::Black, "数値入力モード");
		} else {
			MFont::SSize.DrawBold({ 10,50 }, Color::White, Color::Black, "メモ入力モード");
		}

		for (int a = 0; a < std::min(30,CSV::page_count[CSV::page]- p_no*30); a++)
		{
			if (CSV::line == a+ p_no *30)
			{
				MFont::MSize.DrawBold({ 10 , a * 20 + 120 }, Color::Red, Color::Black, { a+ p_no * 30 , ":" });
			} else {
				MFont::MSize.DrawBold({ 10 , a * 20 + 120 }, Color::White, Color::Black, { a + p_no * 30, ":" });
			}

			MFont::MSize.DrawBold({ 110 , a * 20 + 120}, Color::White, Color::Black, CSV::I[CSV::page][a+p_no*30], true);
			MFont::MSize.DrawBold({ 130 , a * 20 + 120 }, Color::White, Color::Black, CSV::memo[CSV::page][a + p_no * 30], false);
		}

		return;
	}

	/*変更するテキストの選択、テキスト入力の反映*/
	void CSVCheckInput()
	{
		if ( !CSV::isDebugInput ) { return; }

		//ページの移動
		if (Input::key.PageUp.on)
		{
			CSV::page++;
			CSV::line = 0;
		}
		if (Input::key.PageDown.on)
		{
			CSV::page--;
			CSV::line = 0;
		}
		if (CSV::page < 0) { CSV::page = CSV::page_max - 1; }
		if (CSV::page >= CSV::page_max) { CSV::page = 0; }

		//項目の追加
		if (Input::key.Insert.on)
		{
			CSV::page_count[CSV::page]++;
			CSV::I[CSV::page].push_back(0);
			CSV::memo[CSV::page].push_back("-");
		}


		//直接入力
		if (Input::key.Back.on)
		{
			if (System::inputText.length() > 0)
			{
				System::inputText = "";
			}
		}
		if (Input::key.Return.on )
		{
			try {
				if(CSV::input_mode == 0 ) CSV::I[CSV::page][CSV::line] = std::stoi(System::inputText);
				if(CSV::input_mode == 1 ) CSV::memo[CSV::page][CSV::line] = System::inputText;
			}
			catch (const std::invalid_argument& err) {
				//変換出来ない場合は処理を飛ばす
				System::inputText = err.what();
			}

			System::inputText = "";
		}

		//数値とメモの切り替え
		if (Input::key.Tab.on) {
			CSV::input_mode = 1 - CSV::input_mode;
		}

		//数値調整
		if(Input::key.Up.on || (Input::key.Up.holdCount > 30 && Input::key.Up.holdCount % 2 == 0))
		{
			CSV::line--;
		}
		if (Input::key.Down.on || (Input::key.Down.holdCount > 30 && Input::key.Down.holdCount % 2 == 0))
		{
			CSV::line++;
		}
		//行移動
		if (Input::key.Left.on || (Input::key.Left.holdCount > 30 && Input::key.Left.holdCount% 1 == 0))
		{
			CSV::I[CSV::page][CSV::line] -= 1;
		}

		if (Input::key.Right.on || (Input::key.Right.holdCount > 30 && Input::key.Right.holdCount % 1 == 0))
		{
			CSV::I[CSV::page][CSV::line] += 1;
		}
		if (CSV::line < 0) { CSV::line = CSV::page_count[CSV::page]-1; }
		if (CSV::line >= CSV::page_count[CSV::page]) { CSV::line = 0; }
	}

};