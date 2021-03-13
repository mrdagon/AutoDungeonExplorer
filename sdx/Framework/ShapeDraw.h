//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Drawing.h>

//Shape系の描画関数の実装
namespace SDX
{
	void Complex::Draw(const Color &描画色) const
	{
		for (auto it : shapes)
		{
			it->Draw(描画色);
		}
	}

	void Point::Draw(const Color &描画色) const
	{
		Drawing::Pixel({ x, y }, 描画色);
	}

	void Line::Draw(const Color &描画色) const
	{
		Drawing::Line({ xA, yA }, { xB, yB }, 描画色, (int)thick);
		if (thick >= 3)
		{
			Drawing::Circle({ xA, yA, (thick-1)/2 }, 描画色);
			Drawing::Circle({ xB, yB, (thick-1)/2 }, 描画色);
		}
	}

	void Rect::Draw(const Color &描画色) const
	{
		Drawing::Rect({GetLeft(),GetTop(),GetW(),GetH()},描画色,true);
	}

	void Circle::Draw(const Color &描画色) const
	{
		Drawing::Circle({ x, y, radius }, 描画色);
	}
};