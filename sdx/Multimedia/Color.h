//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
	/** 色を表すクラス.*/
	/** \include Color.h*/
	class Color
	{
	private:
		SDL_Color data;//!<
	public:
		Color()
		{
			SetColor(255, 255, 255, 255);
		}


		/** RGB値から色に変換.*/
		/** 赤、緑、青の各要素は0～255で指定する*/
		Color(int 赤, int 緑, int 青, int α値 = 255)
		{
			SetColor(赤, 緑, 青, α値);
		}

		/** 16進数6桁から色に変換.*/
		/** 0～16の6乗で指定する*/
		Color(int RGB , int α値 = 255)
		{
			SetColor(RGB /65536 % 256, RGB / 256 % 256,  RGB % 256, α値);

		}

		/** 色の各要素を設定.*/
		void SetColor(int 赤, int 緑, int 青, int α値 = 255)
		{
			data = { (Uint8)赤, (Uint8)緑, (Uint8)青, (Uint8)α値 };
		}

		/** 赤の要素を取得.*/
		int GetRed() const
		{
			return data.r;
		}

		/** 緑の要素を取得.*/
		int GetGreen() const
		{
			return data.g;
		}

		/** 青の要素を取得.*/
		int GetBlue() const
		{
			return data.b;
		}

		/** 透明度を取得.*/
		int GetAlpha() const
		{
			return data.a;
		}

		/** 型変換.*/
		operator SDL_Color() const
		{
			return data;
		}

		/** 比較オペレータ.*/
		bool operator == (const Color &比較色) const
		{
			return (
				GetRed() == 比較色.GetRed() &&
				GetBlue() == 比較色.GetBlue() &&
				GetGreen() == 比較色.GetGreen() &&
				GetAlpha() == 比較色.GetAlpha()
				);
		}

		/** 比較オペレータ.*/
		bool operator != (const Color &比較色) const
		{
			return !(比較色 == *this);
		}



		static const Color Black;//!< 黒 [RGB]0,0,0
		static const Color Silver;//!< 銀 [R]192,192,192
		static const Color Gray;//!< 灰 [RGB]128,128,128
		static const Color White;//!< 白 [RGB]255,255,255
		static const Color Maroon;//!< 栗 [RGB]128,0,0
		static const Color Red;//!< 赤 [RGB]255,0,0
		static const Color Purple;//!< 紫 [RGB]128,0,128
		static const Color Fuchsia;//!< 赤紫 [RGB]255,0,255
		static const Color Green;//!< 濃緑 [RGB]0,128,0
		static const Color Lime;//!< 明緑 [RGB]0,255,0
		static const Color Olive;//!< 暗黄 [RGB]128,128,0
		static const Color Yellow;//!< 黄 [[RGB]255,255,0
		static const Color Navy;//!< 濃青 [RGB]0,0,128
		static const Color Blue;//!< 青 [RGB]0,0,255
		static const Color Teal;//!< 青緑 [RGB]0,128,128
		static const Color Aqua;//!< 水 [RGB]0,255,255
	};
}