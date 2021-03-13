//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Key.h>
#include <Multimedia/Window.h>

namespace SDX
{
	/** タッチ操作.*/
	/** \include Touch.h*/
	class Touch
	{
		friend class Input;
	private:
		MONO_STATE(Touch)

		bool press = false;
		double xBuffer;
		double yBuffer;

		void Position(double X座標, double Y座標)
		{
			//event.tfinger.x等は0.0~1.0の範囲になるので、押した位置を画面の解像度に合わせて計算する
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
		double x = 0;//!< タッチしている座標
		double y = 0;//!< タッチしている座標 

		double moveX = 0;//!< 前回更新時からの移動量
		double moveY = 0;//!< 前回更新時からの移動量

		bool on = false;//!< タッチされた直後は true
		bool off = false;//!< 指を離した直後は true
		bool hold = false;//!< タッチしている間は true

		unsigned int  holdCount = 0;//!<押されている時間

		/** 状態の更新.*/
		void Update()
		{
			on = (!hold && press);
			off = (hold && !press);

			hold = press;
			if (press)
			{
				++holdCount;
			}
			else
			{
				holdCount = 0;
			}

			if (!on)
			{
				moveX = xBuffer - x;
				moveY = yBuffer - y;
			}
			else
			{
				moveX = 0;
				moveY = 0;
			}

			x = xBuffer;
			y = yBuffer;
		}

		/** 状態のリセット.*/
		void Reset()
		{
			x = 0;
			y = 0;

			moveX = 0;
			moveY = 0;

			press = false;

			on = false;
			off = false;
			hold = false;
			holdCount = 0;
		}

	};
}