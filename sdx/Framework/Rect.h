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

	/** 矩形を表す図形クラス.*/
	/** \include Shape.h*/
	class Rect : public IShape
	{
	public:
		double x = 0;//!< 起点座標
		double y = 0;//!< 起点座標

		double widthLeft = 0;//!< 起点から左側の幅
		double widthRight = 0;//!< 起点から右側の幅

		double heightUp = 0;//!< 起点から上側の幅
		double heightDown = 0;//!< 起点から下側の幅

		Rect() = default;

		/**座標と大きさを指定.*/
		/**デフォルト引数だと左上座標と大きさを指定*/
		/**横幅A=横幅B,高さA=高さBとすると中心座標指定になる*/
		Rect(double X座標, double Y座標, double 横幅A, double 高さA, double 横幅B = 0, double 高さB = 0) :
			x(X座標),
			y(Y座標),
			heightUp(高さB),
			heightDown(高さA),
			widthLeft(横幅B),
			widthRight(横幅A)
		{}

		template <class T1,class T2,class T3,class T4>
		/**座標と大きさを指定.*/
		/**デフォルト引数だと左上座標と大きさを指定*/
		/**横幅A=横幅B,高さA=高さBとすると中心座標指定になる*/
		Rect(T1 X座標, T2 Y座標, T3 横幅A, T4 高さA, T3 横幅B = 0, T4 高さB = 0) :
			x((double)X座標),
			y((double)Y座標),
			heightUp((double)高さB),
			heightDown((double)高さA),
			widthLeft((double)横幅B),
			widthRight((double)横幅A)
		{}

		virtual IShape* Clone(double X座標, double Y座標) const override
		{
			auto shape = new Rect(X座標, Y座標, widthRight, heightDown, widthLeft, heightUp);
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

		void MultiZoom(double X倍率, double Y倍率) override
		{
			widthLeft *= X倍率;
			widthRight *= X倍率;

			heightUp *= Y倍率;
			heightDown *= Y倍率;
		}

		void Rotate(double 回転する角度) override
		{
		
		}

		void Draw(const Color &描画色) const override;

		inline double GetX() const override
		{
			return x;
		}

		inline double GetY() const override
		{
			return y;
		}

		inline double GetW() const override
		{
			return widthLeft + widthRight;
		}

		inline double GetH() const override
		{
			return heightUp + heightDown;
		}

		/** 左端のX座標を取得.*/
		inline double GetLeft() const
		{
			return x - widthLeft;
		}

		/** 上端のY座標を取得.*/
		inline double GetTop() const
		{
			return y - heightUp;
		}

		/** 右端のX座標を取得.*/
		inline double GetRight() const
		{
			return x + widthRight;
		}

		/** 下端のY座標を取得.*/
		inline double GetBottom() const
		{
			return y + heightDown;
		}

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
			return (
				(
				point->x < this->GetRight()
				) && (
				point->x > this->GetLeft()
				) && (
				point->y < this->GetBottom()
				) && (
				point->y > this->GetTop()
				)
				);
		}
		bool Hit(const Line *line) const override
		{
			//完全に外部にある
			if (				
					line->GetMaxX() + line->GetThickHarf() < this->GetLeft()  ||
					line->GetMinX() - line->GetThickHarf() > this->GetRight() ||
					line->GetMaxY() + line->GetThickHarf() < this->GetTop()   ||
					line->GetMinY() - line->GetThickHarf() > this->GetBottom()	
				)
			{
				return false;
			}

			//四角形の対角線との交差チェック
			//√２/2≒0.7
			if (LineLine(line->GetXA(), line->GetYA(), line->GetXB(), line->GetYB() , this->GetLeft() - int(line->GetThickHarf() * 0.7), this->GetTop() - int(line->GetThickHarf() * 0.7), this->GetRight() + int(line->GetThickHarf() * 0.7), this->GetBottom() + int(line->GetThickHarf() * 0.7)))
			{
				return true;
			}
			if (LineLine(line->GetXA(), line->GetYA(), line->GetXB(), line->GetYB()	, this->GetRight() + int(line->GetThickHarf() * 0.7), this->GetTop() - int(line->GetThickHarf() * 0.7), this->GetLeft() - int(line->GetThickHarf() * 0.7), this->GetBottom() + int(line->GetThickHarf() * 0.7)))
			{
				return true;
			}

			//端が四角内にあるか判定
			if (
				line->GetXA() + line->GetThickHarf() > this->GetLeft() && line->GetXA() - line->GetThickHarf() < this->GetRight() &&
				line->GetYA() + line->GetThickHarf() > this->GetTop() && line->GetYA() - line->GetThickHarf() < this->GetBottom()
				)
			{
				//端の丸い所判定
				if (line->GetXA() < this->GetLeft() && line->GetYA() < this->GetTop())
				{//左上
					if ((line->GetXA() - this->GetLeft()) * (line->GetXA() - this->GetLeft()) +
						(line->GetYA() - this->GetTop()) * (line->GetYA() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXA() > this->GetRight() && line->GetYA() < this->GetTop())
				{//右上
					if ((line->GetXA() - this->GetRight()) * (line->GetXA() - this->GetRight()) +
						(line->GetYA() - this->GetTop()) * (line->GetYA() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXA() < this->GetLeft() && line->GetYA() > this->GetBottom())
				{//左下
					if ((line->GetXA() - this->GetLeft()) * (line->GetXA() - this->GetLeft()) +
						(line->GetYA() - this->GetBottom()) * (line->GetYA() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else if (line->GetXA() > this->GetRight() && line->GetYA() > this->GetBottom())
				{//右下
					if ((line->GetXA() - this->GetRight()) * (line->GetXA() - this->GetRight()) +
						(line->GetYA() - this->GetBottom()) * (line->GetYA() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else
				{
					return true;
				}
			}


			//端が四角内にあるか判定
			if (
				line->GetXB() + line->GetThickHarf() > this->GetLeft() && line->GetXB() - line->GetThickHarf() < this->GetRight() &&
				line->GetYB() + line->GetThickHarf() > this->GetTop() && line->GetYB() - line->GetThickHarf() < this->GetBottom()
				)
			{
				//端の丸い所判定
				if (line->GetXB() < this->GetLeft() && line->GetYB() < this->GetTop())
				{//左上
					if ((line->GetXB() - this->GetLeft()) * (line->GetXB() - this->GetLeft()) +
						(line->GetYB() - this->GetTop()) * (line->GetYB() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXB() > this->GetRight() && line->GetYB() < this->GetTop())
				{//右上
					if ((line->GetXB() - this->GetRight()) * (line->GetXB() - this->GetRight()) +
						(line->GetYB() - this->GetTop()) * (line->GetYB() - this->GetTop()) < line->GetThickPow()) return true;
				}
				else if (line->GetXB() < this->GetLeft() && line->GetYB() > this->GetBottom())
				{//左下
					if ((line->GetXB() - this->GetLeft()) * (line->GetXB() - this->GetLeft()) +
						(line->GetYB() - this->GetBottom()) * (line->GetYB() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else if (line->GetXB() > this->GetRight() && line->GetYB() > this->GetBottom())
				{//右下
					if ((line->GetXB() - this->GetRight()) * (line->GetXB() - this->GetRight()) +
						(line->GetYB() - this->GetBottom()) * (line->GetYB() - this->GetBottom()) < line->GetThickPow()) return true;
				}
				else
				{
					return true;
				}
			}

			return false;
		}
		bool Hit(const Rect *rect) const override
		{
			return !(GetRight() < rect->GetLeft() || GetLeft() > rect->GetRight() || GetBottom() < rect->GetTop() || GetTop() > rect->GetBottom());
		}
		bool Hit(const Circle *circle) const override;

		/** Pointを取得.*/
		Point GetPoint() const
		{
			return { x , y};
		}

		Point GetCenter() const
		{
			return{ x + (widthRight - widthLeft) / 2, y + (heightDown - heightUp) / 2 };
		}

		/** SDL_Rectに型変換.*/
		operator SDL_Rect() const
		{
			return{ (int)GetLeft(), (int)GetTop(), (int)GetW(), (int)GetH() };
		}

		/** 座標に加算.*/
		Rect operator +(Point &加算値) const
		{
			return {this->x + 加算値.x,this->y + 加算値.y ,widthRight , heightDown , widthLeft , heightUp};
		}
	};
}