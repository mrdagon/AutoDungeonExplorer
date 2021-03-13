//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Sprite.h>
#include <Framework/Shape.h>

namespace SDX
{
	/** ShapeとSpriteをまとめて、2Dモデルを表すクラス.*/
	/** GetShapeとGetSpriteをオーバーライドして使用する*/
	/** \include Model.h*/
	class IModel : public IPosition
	{
	private:
		double angle = 0;//!<
		double shadowSize = 1;//!<
	protected:
		bool isRemove = false;//!< 消滅フラグ
	public:

		virtual const IShape& GetShape() const = 0;
		virtual const ISprite& GetSprite() const
		{
			static SpNull noSprite;
			return noSprite;
		}

		ISprite& GetSprite()
		{
			return const_cast<ISprite&>(static_cast<const IModel&>(*this).GetSprite());
		}

		IShape& GetShape()
		{
			return const_cast<IShape&>(static_cast<const IModel&>(*this).GetShape());
		}

		/*コピペ用
		const IShape& GetShape() const { return shape; }
		const ISprite& GetSprite() const { return sprite; }
		*/

		virtual ~IModel() = default;

		/** 消滅フラグの取得.*/
		bool GetRemoveFlag() const
		{
			return isRemove;
		}

		/** 更新処理を行う.*/
		virtual void Update(){}

		/** 影の大きさを設定.*/
		void SetShadowSize(double 影の表示倍率)
		{
			shadowSize = 影の表示倍率;
		}

		/** 描画する.*/
		virtual void Draw() const
		{
			GetSprite().Draw( GetShape() );

			//当たり判定を表示するならコメントアウト解除
			//iShape.Draw({255,0,0,128} );
		}

		/** 影を描画する.*/
		void DrawShadow(double X座標ずれ, double Y座標ずれ)
		{
			if (shadowSize <= 0) return;

			X座標ずれ *= shadowSize;
			Y座標ずれ *= shadowSize;

			double zoomX = GetSprite().zoomX;
			double zoomY = GetSprite().zoomY;
			GetSprite().zoomX *= shadowSize;
			GetSprite().zoomY *= shadowSize;

			GetSprite().gap.Move(X座標ずれ,Y座標ずれ);
			GetSprite().Draw(GetShape());
			GetSprite().gap.Move(-X座標ずれ, -Y座標ずれ);

			GetSprite().zoomX = zoomX;
			GetSprite().zoomY = zoomY;
		}

		/** 指定座標に移動.*/
		void SetPos(double X座標, double Y座標) override
		{
			GetShape().SetPos(X座標, Y座標);
		}

		/** 縦横別で拡大率を掛ける.*/
		void MultiZoom(double X倍率, double Y倍率) override
		{
			zoomX *= X倍率;
			zoomY *= Y倍率;

			GetShape().MultiZoom(X倍率, Y倍率);
			GetSprite().MultiZoom(X倍率, Y倍率);
		}
		
		/** 相対座標で移動.*/
		void Move(double X移動量, double Y移動量) override
		{
			GetShape().Move(X移動量, Y移動量);
		}

		/** 回転させる.*/
		void Rotate(double 回転角度) override
		{
			angle += 回転角度;
			GetSprite().Rotate(回転角度);
			GetShape().Rotate(回転角度);
		}

		/** 角度を取得する.*/
		double GetAngle() const override
		{
			return angle;
		}

		/** X座標を取得.*/
		double GetX() const override
		{
			return GetShape().GetX();
		}

		/** Y座標を取得.*/
		double GetY() const override
		{
			return GetShape().GetY();
		}

		/** X座標を取得.*/
		double GetW() const override
		{
			return GetShape().GetW();
		}

		/** Y座標を取得.*/
		double GetH() const override
		{
			return GetShape().GetH();
		}

		/** 色をまとめて変更する、透明度も含む.*/
		void SetColor(const Color &描画色)
		{
			GetSprite().color = 描画色;
		}

		/** 横方向の拡大率を取得.*/
		double GetZoomX() const
		{
			return zoomX;
		}

		/** 縦方向の拡大率を取得.*/
		double GetZoomY() const
		{
			return zoomY;
		}

		/** Modelとの衝突判定.*/
		bool Hit(const IModel *判定を行うModel) const
		{
			return GetShape().Hit(&判定を行うModel->GetShape());
		}

		/** Shapeとの衝突判定.*/
		bool Hit(const IShape *判定を行うShape) const
		{
			return GetShape().Hit(判定を行うShape);
		}
	};
}