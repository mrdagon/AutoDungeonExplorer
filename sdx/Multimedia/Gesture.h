//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Key.h>
#include <Multimedia/Window.h>

namespace SDX
{
	/** タッチ操作の各種ジェスチャー.*/
	/** \include Gesture.h*/
	class Gesture
	{
		friend class Input;
	private:
		MONO_STATE(Gesture)

		bool press = false;//!<
		double xBuffer = 0;//!<
		double yBuffer = 0;//!<

		void Position(double X座標, double Y座標)
		{
			const double aspA = Window::activeWindow->aspect;
			const double aspB = (double)Window::GetWidth() / Window::GetHeight();

			if (aspA == aspB)
			{
				xBuffer = int(X座標 * Window::GetWidth());
				yBuffer = int(Y座標 * Window::GetHeight());
			}
			else if (aspA > aspB){
				//横が余る
				double rate = aspA / aspB;
				double pos = (X座標 - (rate - 1) / rate / 2) * rate;
				xBuffer = int(pos * Window::GetWidth());
				yBuffer = int(Y座標 * Window::GetHeight());
			}
			else{
				//上が余る
				double rate = aspB / aspA;
				double pos = (Y座標 - (rate - 1) / rate / 2) * rate;
				xBuffer = int(X座標 * Window::GetWidth());
				yBuffer = int(pos * Window::GetHeight());
			}
		}
	public:
		bool on = false;//!< 何らかのジェスチャーが発生した時にtrue

		double rotate = 0;//!< 回転ジェスチャー
		double pinche = 0;//!< ピンチ操作

		double x = 0;//!< ジェスチャー操作の中心点
		double y = 0;//!< ジェスチャー操作の中心点

		int fingerCount = 0;//!< ジェスチャーに使った指の本数

		/** 状態の更新.*/
		void Update()
		{
			on = press;
			press = false;
		}

		/** 状態をリセット.*/
		void Reset()
		{
			press = false;
			on = false;
			rotate = 0;
			pinche = 0;
			x = 0;
			y = 0;
			fingerCount = 0;
		}
	};
}