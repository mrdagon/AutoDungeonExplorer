//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/ImagePack.h>
#include <Framework/IFrame.h>

namespace SDX
{
	/** 描画用枠を表すクラス.*/
	/** \include BmpFrame.h*/
	class BmpFrame : public IFrame
	{
	private:
		ImagePack *frame = nullptr;//!<
	public:

		BmpFrame() = default;

		/** フレームを作成する.*/
		/** フレーム画像は３×３分割した9マスの物が使える*/
		BmpFrame(ImagePack *フレーム画像)
		{
			Make(フレーム画像);
		}

		/** フレームを作成する.*/
		/** フレーム画像は３×３分割した9マスの物が使える*/
		bool Make(ImagePack *フレーム画像)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ Make(フレーム画像); });
				return true;
			}

			if (フレーム画像->GetSize() != 9) return false;
			frame = フレーム画像;

			return true;
		}

		/** 矩形のフレームを描画.*/
		/** 右上座標を指定してフレームを描画する*/
		/** @todo ImagePackにSetColorしていた場合の動作がまだ*/
		void Draw(const Rect &領域 , const Color &描画色 = Color::White) const
		{
			if (frame == nullptr){ return; }

			Color color = Screen::GetRenderer()->rgba;

			if (描画色 != Color::White)
			{
				Screen::GetRenderer()->rgba.SetColor
					(
						color.GetRed() * 描画色.GetRed() / 255,
						color.GetGreen() * 描画色.GetGreen() / 255,
						color.GetBlue() * 描画色.GetBlue() / 255,
						color.GetAlpha() * 描画色.GetAlpha() / 255					
					);
			}

			auto camera = Camera::Get();

			double width = frame->GetWidth();
			double height = frame->GetHeight();
			bool isMin = true;//枠が小さいため部分描画が必要フラグ
			int partW = (int)width;
			int partH = (int)height;
			int partLeft = 0;
			int partTop = 0;

			//外枠
			if ((double)width * 2 > 領域.GetW())
			{
				width = (int)領域.GetW() / 2;
				partW = (int)width;
				partLeft = frame->GetWidth() - (int)width;
				isMin = true;
			}
			if ((double)height * 2 > 領域.GetH())
			{
				height = (int)領域.GetH() / 2;
				partH = (int)height;
				partTop = frame->GetHeight() - (int)height;
				isMin = true;
			}

			if (camera)
			{
				//隙間が出来るのでCameraの機能はここで計算
				Camera::Set();

				width = int(width * camera->zoom);
				height = int(height *camera->zoom);

				//カメラ補正有り
				int xA = (int)camera->TransX(領域.GetLeft());
				int xB = xA + (int)width;
				int xD = (int)camera->TransX(領域.GetRight());
				int xC = xD - (int)width;

				int yA = (int)camera->TransY(領域.GetTop());
				int yB = yA + (int)height;
				int yD = (int)camera->TransY(領域.GetBottom());
				int yC = yD - (int)height;

				//内側
				frame[0][4]->DrawExtend({ xB, yB, xC -xB, yC - yB });

				if (isMin)
				{
					frame[0][3]->DrawPartExtend({ xA, yB, width, yC - yB }, { 0, 0, width, height});//左
					frame[0][5]->DrawPartExtend({ xC, yB, width, yC - yB }, { partLeft, 0, width, height });//右

					frame[0][1]->DrawPartExtend({ xB, yA, xC - xB, height }, { 0, 0, width, height });//上
					frame[0][7]->DrawPartExtend({ xB, yC, xC - xB, height }, { 0, partTop, width, height });//下

					frame[0][0]->DrawPartExtend({ xA, yA, width, height }, { 0, 0, width, height });//左上
					frame[0][2]->DrawPartExtend({ xC, yA, width, height }, { partLeft, 0, width, height });//右上
					frame[0][6]->DrawPartExtend({ xA, yC, width, height }, { 0, partTop, width, height });//左下
					frame[0][8]->DrawPartExtend({ xC, yC, width, height }, { partLeft, partTop, width, height });//右下
				}
				else
				{
					frame[0][3]->DrawExtend({ xA, yB, width, yC - yB });//左
					frame[0][5]->DrawExtend({ xC, yB, width, yC - yB });//右

					frame[0][1]->DrawExtend({ xB, yA, xC - xB, height });//上
					frame[0][7]->DrawExtend({ xB, yC, xC - xB, height });//下

					frame[0][0]->DrawExtend({ xA, yA, width, height });//左上
					frame[0][2]->DrawExtend({ xC, yA, width, height });//右上
					frame[0][6]->DrawExtend({ xA, yC, width, height });//左下
					frame[0][8]->DrawExtend({ xC, yC, width, height });//右下
				}

				Camera::Set(camera);
			}
			else
			{
				//カメラ補正無し
				int xA = (int)領域.GetLeft();
				int xB = (int)領域.GetLeft() + (int)width;
				int xC = (int)領域.GetRight() - (int)width;
				int yA = (int)領域.GetTop();
				int yB = (int)領域.GetTop() + (int)height;
				int yC = (int)領域.GetBottom() - (int)height;

				//内側
				frame[0][4]->DrawExtend({ xB, yB, 領域.GetW() - width * 2, 領域.GetH() - height * 2 });

				if (isMin)
				{
					//外枠
					frame[0][3]->DrawPartExtend({ xA, yB, width, 領域.GetH() - height * 2 }, { 0, 0, width, height });//左
					frame[0][5]->DrawPartExtend({ xC, yB, width, 領域.GetH() - height * 2 }, { partLeft, 0, width, height });//右

					frame[0][1]->DrawPartExtend({ xB, yA, 領域.GetW() - width * 2, height }, { 0, 0, width, height });//上
					frame[0][7]->DrawPartExtend({ xB, yC, 領域.GetW() - width * 2, height }, { 0, partTop, width, height });//下

					frame[0][0]->DrawPartExtend({ xA, yA, width, height }, { 0, 0, width, height });//左上
					frame[0][2]->DrawPartExtend({ xC, yA, width, height }, { partLeft, 0, width, height });//右上
					frame[0][6]->DrawPartExtend({ xA, yC, width, height }, { 0, partTop, width, height });//左下
					frame[0][8]->DrawPartExtend({ xC, yC, width, height }, { partLeft, partTop, width, height });//右下
				}
				else
				{
					//外枠
					frame[0][3]->DrawExtend({ xA, yB, width, 領域.GetH() - height * 2 });//左
					frame[0][5]->DrawExtend({ xC, yB, width, 領域.GetH() - height * 2 });//右

					frame[0][1]->DrawExtend({ xB, yA, 領域.GetW() - width * 2, height });//上
					frame[0][7]->DrawExtend({ xB, yC, 領域.GetW() - width * 2, height });//下

					frame[0][0]->DrawExtend({ xA, yA, width, height });//左上
					frame[0][2]->DrawExtend({ xC, yA, width, height });//右上
					frame[0][6]->DrawExtend({ xA, yC, width, height });//左下
					frame[0][8]->DrawExtend({ xC, yC, width, height });//右下
				}

			}

			Camera::Set(camera);

			if (描画色 != Color::White)
			{
				Screen::GetRenderer()->rgba = color;
			}
		}
	};
}