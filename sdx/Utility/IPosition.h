//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#include <algorithm>

namespace SDX
{
	/** 位置と方向を持つクラスのインターフェース.*/
	class IPosition
	{
	protected:
		double zoomX = 1;//!< 図形の拡大率
		double zoomY = 1;//!< 図形の拡大率
	public:
		virtual ~IPosition() = default;

		/** 指定座標に移動.*/
		virtual void SetPos(double X座標, double Y座標) = 0;

		/** 縦横別で拡大率を掛け算する.*/
		virtual void MultiZoom(double X倍率, double Y倍率) = 0;

		/** 拡大率を設定.*/
		virtual void SetZoom(double X拡大率, double Y拡大率)
		{
			MultiZoom(X拡大率 / zoomX, Y拡大率 / zoomY);
		}

		/** 拡大率を掛け算する.*/
		void MultiZoom(double 倍率)
		{
			MultiZoom(倍率, 倍率);
		}

		/** 相対座標で移動.*/
		virtual void Move(double X移動量, double Y移動量) = 0;

		/** 極座標で移動.*/
		void MoveA(double 距離, double 方向 )
		{
			Move(距離 * cos(方向), 距離 * sin(方向));
		}

		/** 回転する.*/
		virtual void Rotate(double 回転する角度) = 0;

		/** 角度を取得する.*/
		virtual double GetAngle() const
		{
			return 0;
		}

		/** 角度を指定する.*/
		virtual void SetAngle(double 指定角度)
		{
			Rotate(指定角度 - GetAngle());
		}

		/** 対象との角度を取得.*/
		double GetDirect(IPosition* 比較対象) const
		{
			return atan2(比較対象->GetY() - this->GetY(), 比較対象->GetX() - this->GetX());
		}

		/** 対象との相対座標を取得.*/
		double GetDistance(IPosition* 比較対象) const
		{
			const double xd = this->GetX() - 比較対象->GetX();
			const double yd = this->GetY() - 比較対象->GetY();

			return sqrt(xd * xd + yd * yd);
		}

		/** 角度の差を計算する*/
		double CompareAngle(double 角度)
		{
			return 0;
		}

		/** X座標を取得.*/
		virtual double GetX() const = 0;

		/** Y座標を取得.*/
		virtual double  GetY() const = 0;

		/** 幅を取得.*/
		virtual double  GetW() const = 0;

		/** 高さを取得.*/
		virtual double  GetH() const = 0;
	};
}