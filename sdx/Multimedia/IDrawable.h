//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
	class Point;
	class Rect;

	/** 描画可能なクラスのインターフェース.*/
	/** \include Image.h*/
	/** @todo 例えばDrawPartに回転可能な関数等を追加するかもしれない*/
	class IDrawable
	{
	public:
		virtual ~IDrawable() = default;

		/** 指定座標に描画.*/
		virtual bool Draw(const Point &座標, bool 反転フラグ = false) const = 0;
		/** 指定矩形内に拡大/縮小描画.*/
		virtual bool DrawExtend(const Rect &描画範囲 ,bool 反転フラグ = false) const = 0;
		/** 角度、拡大率を指定して描画.*/
		virtual bool DrawRotate(const Point &座標, double 拡大率, double 角度, bool 反転フラグ = false) const = 0;
		/** 回転軸、角度、拡大率を指定して描画.*/
		virtual bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率, double 角度, bool 反転フラグ = false) const = 0;
		/** 回転軸、角度、拡大率を縦横別に指定して描画.*/
		virtual bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率X, double 拡大率Y, double 角度, bool 反転フラグ = false) const = 0;
		/** 一部を指定して描画.*/
		virtual bool DrawPart(const Point &描画先座標, const Rect &描画元領域, bool 反転フラグ = false) const = 0;
	};
}