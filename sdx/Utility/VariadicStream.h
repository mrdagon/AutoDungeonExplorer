//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <sstream>
#include <iostream>

namespace SDX
{
	//メモ、よく使うiomanip
	//参考:http://www.booran.com/menu/cplus/manipulator.html
	//dec	:10進数
	//hex	:16進数
	//oct	:8進数
	//left	:左寄せ
	//right	:右寄せ
	//setfill:setwで充填する文字を指定、初期は半角space
	//showpoint:浮動小数点数｢.0｣を必ず表示
	//setw:フィールド幅を指定
	//setprecision:小数点以下の桁数を指定
	//showpos:正の値なら+を表示

	/**可変数引数な文字列を処理するクラス、パフォーマンスはあまり良くない.*/
	/** \include Font.h */
	class VariadicStream
	{
	private:
		template < typename ... TRest>
		std::string Change(TRest... 残りの要素)
		{
			std::ostringstream os;

			Change(os, 残りの要素...);

			return os.str();
		}

		template < class TFirst, typename ... TRest>
		void Change(std::ostringstream& 文字列, TFirst 最初の要素, TRest... 残りの要素)
		{
			文字列 << 最初の要素;
			Change(文字列, 残りの要素...);
		}

		template < class TFirst>
		void Change(std::ostringstream& 文字列, TFirst 最初の要素)
		{
			文字列 << 最初の要素;
		}

	public:
		/** 一行ずつの文字列.*/
		std::vector<std::string> StringS; 

		template < typename ... TStream>
		/** コンストラクタ.*/
		/** 書式指定にはiomanipを使う*/
		VariadicStream(TStream... 文字列ストリーム)
		{
			std::string 分割する文字列 = Change(文字列ストリーム...);

			size_t 開始位置 = 0;
			size_t 終了位置 = 0;

			//改行コードで区切る
			while (終了位置 != std::string::npos)
			{
				終了位置 = 分割する文字列.find("\n", 開始位置);

				StringS.push_back(分割する文字列.substr(開始位置, 終了位置 - 開始位置));

				開始位置 = 終了位置 + 1;
			}
		}
	};
}