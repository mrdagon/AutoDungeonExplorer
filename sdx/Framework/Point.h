//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <Framework/IShape.h>
#include <SDL.h>

namespace SDX
{
	class Complex;
	class Point;
	class Line;
	class Circle;
	class Rect;

	class Camera;
	class Color;

	/** 点を表す図形クラス.*/
	/** \include Shape.h*/
	class Point : public IShape
	{
	public:
		double x = 0;//!< 座標
		double y = 0;//!< 座標

		Point(){}

		/**コンストラクタ.*/
		Point(double X座標, double Y座標) :
			x(X座標),
			y(Y座標)
		{}

		template<class TA, class TB>
		/**コンストラクタ.*/
		Point(TA X座標, TB Y座標) :
			x(X座標),
			y(Y座標)
		{}

		IShape* Clone(double X座標, double Y座標) const override
		{
			auto shape = new Point(X座標, Y座標);
			shape->zoomX = this->zoomX;
			shape->zoomY = this->zoomY;
			return shape;
		}

		void SetPos(double X座標, double Y座標) override
		{
			this->x = X座標;
			this->y = Y座標;
		}

		void Move(double X移動量, double Y移動量) override
		{
			this->x += X移動量;
			this->y += Y移動量;
		}

		double GetX() const override
		{
			return x;
		}

		double GetY() const override
		{
			return y;
		}

		double GetW() const override
		{
			return 1;
		}

		double GetH() const override
		{
			return 1;
		}

		void MultiZoom(double X倍率, double Y倍率) override
		{
			zoomX *= X倍率;
			zoomY *= Y倍率;
		}

		void Rotate(double 回転する角度) override
		{
		}

		void Draw(const Color &描画色) const override;

		bool Hit(const IShape *shape) const override
		{
			return shape->Hit(this);
		}
		bool Hit(const Complex *complex) const override
		{
			for (auto it : complex->shapes)
			{
				if (it->Hit(this)) return true;
			}
			return false;
		}
		bool Hit(const Point *point) const override
		{
			return (point->x == this->x && point->y == this->y);
		}
		bool Hit(const Line *line) const override;
		bool Hit(const Rect *rect) const override;
		bool Hit(const Circle *circle) const override;

		/** SDL_Pointに型変換.*/
		operator SDL_Point() const
		{
			return{ (int)x, (int)y };
		}

		/** 座標の加算.*/
		Point operator +(const Point &加算値) const
		{
			return {this->x + 加算値.x , this->y + 加算値.y};
		}

		Point operator -(const Point &加算値) const
		{
			return{ this->x - 加算値.x, this->y - 加算値.y };
		}
	};
}