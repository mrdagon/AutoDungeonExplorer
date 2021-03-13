//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Color.h>
#include <Utility/VariadicStream.h>

namespace SDX
{
	/** Fontのインターフェース.*/
	/** \include Font.h*/
	class IFont
	{
	public:
		virtual ~IFont() = default;

		/** 文字を描画.*/
		virtual bool Draw(const Point &座標, const Color &描画色, const VariadicStream &描画する文字列 , bool 反転フラグ = false) const = 0;

		/** 文字を回転して描画.*/
		virtual bool DrawRotate(const Point &座標, double 拡大率, double 角度, const Color &描画色, const VariadicStream &描画する文字列, bool 反転フラグ = false) const = 0;

		/** 拡大率を指定して文字を描画.*/
		virtual bool DrawExtend(const Point &座標, double X軸拡大率, double Y軸拡大率, const Color &描画色, const VariadicStream &描画する文字列 , bool 反転フラグ = false) const = 0;
	};
}