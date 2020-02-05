//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <stdexcept>

namespace SDX_BSC
{
	using namespace SDX;
	//デバッグ用変数
	namespace DV
	{
		int line = 0;//現在の行数
		int page = 0;//現在のページ
		int page_max = 1;//合計ページ数

		std::vector<std::string> page_name;//各ページの行数
		std::vector<int> page_count;//各ページの行数
		std::vector<std::vector<int>> I;
	}


	bool DebugInit()
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

		DV::line = std::stoi(strS[0][0]);
		DV::page = std::stoi(strS[0][1]);
		DV::page_max = std::stoi(strS[0][2]);

		DV::I.resize(DV::page_max);

		for (int a = 0; a < DV::page_max; a++)
		{
			DV::page_name.push_back(strS[1][a]);
		}
		for (int a = 0; a < DV::page_max; a++)
		{
			DV::page_count.push_back(std::stoi(strS[2][a]));
		}
		
		for (int a = 0; a < DV::page_max; a++)
		{
			for (int b = 0; b < DV::page_count[a]; b++)
			{
				DV::I[a].push_back(std::stoi(strS[a+3][b]));
			}
		}

		return true;
	}

	void DebugEnd(std::string fileName)
	{
		//デバッグ用数値をテキストで保存
		File file(fileName.c_str(), FileMode::Write, true);

		//BOMを最初に入れる
		char bom[3] = { (char)0xEF ,(char)0xBB ,(char)0xBF };


		file.Write(bom[0]);
		file.Write(bom[1]);
		file.Write(bom[2]);

		file.AddLine({ DV::line ,",",DV::page,",",DV::page_max });

		std::string buffer = "";

		for (int a = 0; a < DV::page_max; a++)
		{
			buffer += DV::page_name[a];
			buffer += ",";
		}
		file.AddLine(buffer);

		buffer = "";

		for (int a = 0; a < DV::page_max; a++)
		{
			buffer += std::to_string(DV::page_count[a]);
			buffer += ",";
		}
		file.AddLine(buffer);

		
		for (int a = 0; a < DV::page_max; a++)
		{
			buffer = "";
			for (int b = 0; b < DV::page_count[a]; b++)
			{
				buffer += std::to_string(DV::I[a][b]);
				buffer += ",";
			}

			file.AddLine( buffer );
		}
	}


	void DebugDraw()
	{
		//std::string str =  + System::textComposition;

		MFont::メイリオ大.DrawBold({ 10,75 }, Color::White,Color::Black, System::inputText);
		MFont::メイリオ中.DrawBold({ 10,100 }, Color::White, Color::Black, DV::page_name[DV::page]);

		MFont::メイリオ中.DrawBold({ 110,75 }, Color::White, Color::Black, System::textComposition);

		int p_no = DV::line/30;//30ライン以上ある場合ずらす

		for (int a = 0; a < std::min(30,DV::page_count[DV::page]- p_no*30); a++)
		{
			if (DV::line == a+ p_no *30)
			{
				MFont::メイリオ中.DrawBold({ 10 , a * 20 + 120 }, Color::Red, Color::Black, { a+ p_no * 30 , ":" });
			} else {
				MFont::メイリオ中.DrawBold({ 10 , a * 20 + 120 }, Color::White, Color::Black, { a+ p_no *30, ":" });
			}

			MFont::メイリオ中.DrawBold({ 110 , a * 20 + 120}, Color::White, Color::Black, DV::I[DV::page][a+p_no*30], true);
		}

		return;
	}

	/*変更するテキストの選択、テキスト入力の反映*/
	void DebugCheckInput()
	{
		//ページの移動
		if (Input::key.PageUp.on)
		{
			DV::page++;
			DV::line = 0;
		}
		if (Input::key.PageDown.on)
		{
			DV::page--;
			DV::line = 0;
		}
		if (DV::page < 0) { DV::page = DV::page_max - 1; }
		if (DV::page >= DV::page_max) { DV::page = 0; }

		//項目の追加
		if (Input::key.Insert.on)
		{
			DV::page_count[DV::page]++;
			DV::I[DV::page].push_back(0);
		}


		//直接入力
		if (Input::key.Back.on)
		{
			if (System::inputText.length() > 0)
			{
				System::inputText.pop_back();
			}
		}

		if (Input::key.Return.on)
		{
			try {
				DV::I[DV::page][DV::line] = std::stoi(System::inputText);
			}
			catch (const std::invalid_argument& err) {
				//変換出来ない場合は処理を飛ばす
				err.what();
			}

			System::inputText = "";
		}

		//数値調整
		if(Input::key.Up.on || (Input::key.Up.holdCount > 60 && Input::key.Up.holdCount % 6 == 0))
		{
			DV::line--;
		}

		if (Input::key.Down.on || (Input::key.Down.holdCount > 60 && Input::key.Down.holdCount % 6 == 0))
		{
			DV::line++;
		}

		//行移動
		if (Input::key.Left.on || (Input::key.Left.holdCount > 60 && Input::key.Left.holdCount% 6 == 0))
		{
			DV::I[DV::page][DV::line] -= 1;
		}

		if (Input::key.Right.on || (Input::key.Right.holdCount > 60 && Input::key.Right.holdCount % 6 == 0))
		{
			DV::I[DV::page][DV::line] += 1;
		}
		if (DV::line < 0) { DV::line = DV::page_count[DV::page]-1; }
		if (DV::line >= DV::page_count[DV::page]) { DV::line = 0; }




	}

};