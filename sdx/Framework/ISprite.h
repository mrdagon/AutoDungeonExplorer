//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Image.h>
#include <Framework/Camera.h>
#include <Multimedia/Screen.h>
#include <Multimedia/Input.h>
#include <Multimedia/Font.h>
#include <Framework/BmpFrame.h>
#include <memory>

namespace SDX
{
	/** 2Dモデルに貼り付けるスプライトを表す抽象クラス.*/
	/** \include Model.h */
	class ISprite
	{
		friend class IModel;
	protected:
		double zoomX = 1;//!< 描画倍率
		double zoomY = 1;//!< 描画倍率
		double angle = 0;//!< 角度

	public:
		bool isTurn = false;//!< 反転フラグ
		Color color = { 255, 255, 255, 255 };//!< 描画色
		Point gap = {0,0};//!<Shape中心とSpriteとの位置差
		Point axis = {0,0};//!< 回転軸のずれ

		virtual ~ISprite() = default;

		/** ISpriteを描画する.*/
		virtual void Draw(const IShape &図形) const = 0;

		/** 表示倍率を設定.*/
		void SetZoom(double X拡大率, double Y拡大率)
		{
			zoomX = X拡大率;
			zoomY = Y拡大率;
		}

		/** 拡大率を掛け算する.*/
		void MultiZoom(double 倍率)
		{
			MultiZoom(倍率, 倍率);
		}

		/** 縦横別で拡大率を掛け算する.*/
		void MultiZoom(double X倍率, double Y倍率)
		{
			zoomX *= X倍率;
			zoomY *= Y倍率;

			gap.x *= X倍率;
			gap.y *= Y倍率;
		}

		/** 横方向の表示倍率を取得.*/
		double GetZoomX()
		{
			return this->zoomX;
		}

		/** 縦方向の表示倍率を取得.*/
		double GetZoomY()
		{
			return this->zoomY;
		}

		/** 表示角度を取得.*/
		double GetAngle()
		{
			return this->angle;
		}

		/** 表示角度を設定.*/
		void SetAngle(double 角度)
		{
			this->angle = 角度;
		}

		/** 回転させる.*/
		void Rotate(double 回転する角度)
		{
			this->angle += 回転する角度;
		}

		/** Anime等の更新処理.*/
		virtual void Update(){};
	};
}