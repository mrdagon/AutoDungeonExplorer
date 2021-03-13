//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Shape.h>

namespace SDX
{
	/** 描画用枠のインターフェース.*/
	/** \include BmpFrame.h*/
	class IFrame
	{
	public:

		virtual ~IFrame() = default;

		/** 枠を描画.*/
		virtual void Draw(const Rect &領域, const Color& 描画色 = Color::White) const = 0;
	};
}