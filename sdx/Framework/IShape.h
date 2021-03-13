//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/IPosition.h>
#include <vector>
#include <algorithm>

namespace SDX
{
	class Complex;
	class Point;
	class Line;
	class Circle;
	class Rect;

	class Camera;
	class Color;
	/** 衝突判定可能な図形の抽象クラス.*/
	/** \include Shape.h */
	class IShape : public IPosition
	{
	protected:
		/** 矩形の交差判定.*/
		static bool RectRect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
		{
			//x座標をラフチェック
			if (x1 >= x2)
			{
				if ((x1 < x3 && x1 < x4) || (x2 > x3 && x2 > x4))
				{
					return false;
				}
			}
			else
			{
				if ((x2 < x3 && x2 < x4) || (x1 > x3 && x1 > x4))
				{
					return false;
				}
			}
			//y座標をラフチェック
			if (y1 >= y2)
			{
				if ((y1 < y3 && y1 < y4) || (y2 > y3 && y2 > y4))
				{
					return false;
				}
			}
			else
			{
				if ((y2 < y3 && y2 < y4) || (y1 > y3 && y1 > y4))
				{
					return false;
				}
			}

			return true;
		}

		/** 線分の交差判定.*/
		static bool LineLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
		{
			//交差判定
			if ((double(x1 - x2) * (y3 - y1) + (y1 - y2) * (x1 - x3)) *
				(double(x1 - x2) * (y4 - y1) + (y1 - y2) * (x1 - x4)) > 0)
			{
				return false;
			}

			if ((double(x3 - x4) * (y1 - y3) + (y3 - y4) * (x3 - x1)) *
				(double(x3 - x4) * (y2 - y3) + (y3 - y4) * (x3 - x2)) > 0)
			{
				return false;
			}
			return true;
		}

		/** 二点間の距離を計算.*/
		static int PointPoint(double x1, double y1, double x2, double y2)
		{
			return int((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		}

	public:

		virtual ~IShape() = default;

		/** 同じ形の図形を作る.*/
		virtual IShape* Clone(double x, double y) const = 0;

		/** 衝突判定.*/
		virtual bool Hit(const IShape *iShape) const = 0;
		/** 衝突判定.*/
		virtual bool Hit(const Complex *complex) const = 0;
		/** 衝突判定.*/
		virtual bool Hit(const Point *point) const = 0;
		/** 衝突判定.*/
		virtual bool Hit(const Line *line) const = 0;
		/** 衝突判定.*/
		virtual bool Hit(const Rect *rect) const = 0;
		/** 衝突判定.*/
		virtual bool Hit(const Circle *circle) const = 0;

		/** 描画する.*/
		virtual void Draw(const Color &描画色) const = 0;
	};
}