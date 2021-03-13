//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <Framework/IShape.h>
namespace SDX
{
	class Complex;
	class Point;
	class Line;
	class Circle;
	class Rect;

	class Camera;
	class Color;

	/** 複合図形を表すクラス.*/
	/** \include Shape.h*/
	class Complex : public IShape
	{
	public:
		std::vector<IShape*> shapes;//!< 保持するShape

		Complex() = default;

		/**コンストラクタ.*/
		Complex(IShape *shape)
		{
			shapes.push_back(shape);
		}

		IShape* Clone(double x, double y) const override
		{
			Complex *buf = new Complex();

			for (auto it : shapes)
			{
				buf->shapes.push_back(it);
			}

			return buf;
		}

		void SetPos(double X座標, double Y座標) override
		{
			for (auto it : shapes)
			{
				it->SetPos(X座標, Y座標);
			}
		}

		void Move(double X移動量, double Y移動量) override
		{
			for (auto it : shapes)
			{
				it->Move(X移動量, Y移動量);
			}
		}

		double GetX() const override
		{
			return shapes[0]->GetX();
		}

		double GetY() const override
		{
			return shapes[0]->GetY();
		}

		double GetW() const override
		{
			return shapes[0]->GetW();
		}

		double GetH() const override
		{
			return shapes[0]->GetH();
		}

		void MultiZoom(double X倍率, double Y倍率) override
		{
			for (auto it : shapes)
			{
				it->MultiZoom(X倍率, Y倍率);
			}
			zoomX *= X倍率;
			zoomY *= Y倍率;
		}

		void Rotate(double 回転する角度) override
		{
			for (auto it : shapes)
			{
				it->Rotate(回転する角度);
			}
		}

		void Draw(const Color &描画色) const override;

		bool Hit(const IShape *shape) const override
		{
			return shape->Hit(this);
		}
		bool Hit(const Complex *complex) const override
		{
			for (auto itA : this->shapes)
			{
				for (auto itB : complex->shapes)
				{
					if (itA->Hit(itB)) return true;
				}
			}
			return false;
		}
		bool Hit(const Point *point) const override;
		bool Hit(const Line *line) const override;
		bool Hit(const Rect *rect) const override;
		bool Hit(const Circle *circle) const override;
	};
}