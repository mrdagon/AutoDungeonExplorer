//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Multimedia/Loading.h>
#include <Multimedia/IDrawable.h>
#include <Framework/Shape.h>
#include <Framework/Camera.h>

namespace SDX
{
	/** 画像データを表すクラス.*/
	/** デストラクタでリソース解放周りは調整中*/
	/** \include Image.h*/
	class Image : public IDrawable
	{
		friend class Drawing;
		friend class ImagePack;//AdjustWidthで必要
	private:
		SDL_Rect part;//!<
		SDL_Texture* handle = nullptr;//!<
		Color color = { 255, 255, 255 ,255};//!<

		/** 透過状態を計算する.*/
		void RGBACulculate() const
		{
			if (Screen::GetRenderer()->blendMode == BlendMode::NoBlend)
			{
				//pngの透過部分があるのでNoBlendで描画はしない
				SDL_SetTextureBlendMode(handle, (SDL_BlendMode)BlendMode::Alpha);
				SDL_SetTextureAlphaMod(handle, color.GetAlpha());
			}
			else
			{
				SDL_SetTextureBlendMode(handle, (SDL_BlendMode)Screen::GetRenderer()->blendMode);
				SDL_SetTextureAlphaMod(handle, Screen::GetRenderer()->rgba.GetAlpha() * color.GetAlpha() / 255);
			}

			SDL_SetTextureColorMod
				(
				handle,
				Screen::GetRenderer()->rgba.GetRed() * color.GetRed() / 255,
				Screen::GetRenderer()->rgba.GetGreen() * color.GetGreen() / 255,
				Screen::GetRenderer()->rgba.GetBlue() * color.GetBlue() / 255
				);
		}
	public:

		Image()
		{};

		~Image(){};

		/** 画像をメモリへ読み込む.*/
		Image(const char *ファイル名)
		{
			Load(ファイル名);
		}

		/** 別のImageの一部をコピーして、Imageを初期化.*/
		/** handleは同一*/
		Image(const Image& コピー元, const Rect& コピー領域)
		{
			Copy(コピー元, コピー領域);
		}

		/** SDL_TextureからImageを作成.*/
		Image(SDL_Texture* 画像ハンドル,int 幅,int 高さ):
			handle(画像ハンドル),
			part({0,0,幅,高さ})
		{
			return;//何か書いておかないとDoxygenが不具合を起こす
		}

		/** 空のイメージを作成.*/
		Image(int 幅, int 高さ)
		{
			Make(幅, 高さ);
		}

		/** 画像をメモリへ読み込む.*/
		bool Load(const char *ファイル名)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(ファイル名);});
				return true;
			}

			if (this->handle != nullptr){ return false; }
			
			SDL_Surface* temp = IMG_Load(ファイル名);

			if (temp == nullptr) return false;

			handle = SDL_CreateTextureFromSurface(Screen::GetHandle(), temp);

			part.x = 0;
			part.y = 0;
			part.w = temp->w;
			part.h = temp->h;

			SDL_FreeSurface(temp);
			return (handle != nullptr);
		}

		/** イメージをメモリから開放.*/
		bool Release()
		{
			if (this->handle != nullptr)
			{
				SDL_DestroyTexture(handle);
				return true;
			}
			return false;
		}

		/** 空のイメージを作成.*/
		SDL_Texture* Make(int 幅, int 高さ)
		{
			Release();

			handle = SDL_CreateTexture(Screen::GetHandle(), 0, SDL_TEXTUREACCESS_TARGET, 幅, 高さ);
			part.x = 0;
			part.y = 0;
			part.w = 幅;
			part.h = 高さ;

			return handle;
		}

		/** 別のImageの一部をコピーして、Imageを初期化.*/
		/** handleは同一*/
		SDL_Texture* Copy(const Image& 元イメージ, const Rect& コピー領域)
		{
			this->handle = 元イメージ.handle;
			part.x = (int)コピー領域.x;
			part.y = (int)コピー領域.y;
			part.w = (int)コピー領域.GetW();
			part.h = (int)コピー領域.GetH();

			return handle;
		}

		/** 同じImageを作成.*/
		/** handleは別、Screen::SetTargetに指定可能*/
		Image Clone(bool is反転 = false) const
		{
			return Clone({part.x,part.y,part.w,part.h}, is反転);
		}

		/** Imageの一部から別Imageを作成.*/
		/** handleは別、Screen::SetTargetに指定可能*/
		Image Clone(const Rect& コピー領域 , bool is反転 = false) const
		{
			Image image((int)コピー領域.GetW(), (int)コピー領域.GetH());
			auto prev = Screen::GetTarget();
			auto mode = Screen::GetRenderer()->blendMode;
			auto rgba = Screen::GetRenderer()->rgba;
			auto cam = Camera::Get();

			Screen::SetTarget(&image);
			Screen::SetDrawMode();
			Camera::Set();
			DrawPart({ 0, 0 }, コピー領域, is反転);			
			Screen::SetTarget(prev);
			Screen::SetDrawMode(rgba,mode);
			Camera::Set(cam);

			return image;
		}

		/** ハンドルを取得.*/
		SDL_Texture* GetHandle() const
		{
			return handle;
		}

		/** 指定座標に描画.*/
		bool Draw(const Point &座標, bool 反転フラグ = false) const override
		{
			SDL_Rect temp = { (int)座標.x, (int)座標.y, part.w, part.h };

			if (Camera::Get())
			{
				temp = Camera::Get()->TransRect(temp);
			}

			RGBACulculate();
			if (反転フラグ)
			{
				return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 0, nullptr, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
			}
			else{
				return !SDL_RenderCopy(Screen::GetHandle(), handle, &part, &temp);
			}
		}

		/** 指定矩形内に描画.*/
		bool DrawExtend(const Rect &描画領域 , bool 反転フラグ = false) const override
		{
			SDL_Rect temp = { (int)描画領域.x, (int)描画領域.y, (int)描画領域.GetW(), (int)描画領域.GetH() };

			if (Camera::Get())
			{
				temp = Camera::Get()->TransRect(temp);
			}

			//サイズがマイナスなら描画しない
			if (temp.w < 0 || temp.h < 0)
			{
				return false;
			}

			RGBACulculate();
			if (反転フラグ)
			{
				static SDL_Point point = { 0, 0 };
				return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 0, &point, SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
			} 
			else
			{
				return !SDL_RenderCopy(Screen::GetHandle(), handle, &part, &temp);
			}
		}

		/** 角度、拡大率を指定して描画.*/
		bool DrawRotate(const Point &座標, double 拡大率, double 角度, bool 反転フラグ = false) const override
		{
			const int wbuf = int(part.w*拡大率);
			const int hbuf = int(part.h*拡大率);
			SDL_Rect temp = { (int)座標.x - wbuf / 2, (int)座標.y - hbuf / 2, wbuf, hbuf };

			if (Camera::Get())
			{
				temp = Camera::Get()->TransRect(temp);
			}

			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 角度 * 180 / PAI, nullptr, SDL_RendererFlip(反転フラグ));
		}
		/** 回転軸、角度、拡大率を指定して描画.*/
		bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率, double 角度, bool 反転フラグ = false) const override
		{
			return DrawRotateAxis(座標, 回転軸座標, 拡大率, 拡大率, 角度, 反転フラグ);
		}
		/** 回転軸、角度、拡大率を縦横別に指定して描画.*/
		bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率X, double 拡大率Y, double 角度, bool 反転フラグ = false) const override
		{
			const int wbuf = int(part.w*拡大率X);
			const int hbuf = int(part.h*拡大率Y);
			SDL_Rect temp = { (int)座標.x - wbuf / 2, (int)座標.y - hbuf / 2, wbuf, hbuf };
			SDL_Point point = { int(回転軸座標.x*拡大率X), int(回転軸座標.y*拡大率Y) };

			if (Camera::Get())
			{
				temp = Camera::Get()->TransRect(temp);
				point.x = int(point.x * Camera::Get()->zoom);
				point.y = int(point.y * Camera::Get()->zoom);
			}

			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 角度 * 180 / PAI, &point, SDL_RendererFlip(反転フラグ));
		}

		/** 指定した一部分を描画.*/
		bool DrawPart(const Point &描画先座標, const Rect &描画元領域, bool 反転フラグ = false) const override
		{
			SDL_Rect temp = { (int)描画先座標.x, (int)描画先座標.y, (int)描画元領域.GetW(), (int)描画元領域.GetH() };
			SDL_Rect part = { (int)描画元領域.x + this->part.x, (int)描画元領域.y + this->part.y, (int)描画元領域.GetW(), (int)描画元領域.GetH() };

			if (Camera::Get())
			{
				temp = Camera::Get()->TransRect(temp);
			}

			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 0, nullptr, SDL_RendererFlip(反転フラグ));
		}

		/** 指定した一部分を描画.*/
		bool DrawPartExtend(const Rect &描画先領域, const Rect &描画元領域, bool 反転フラグ = false) const
		{
			SDL_Rect temp = { (int)描画先領域.x, (int)描画先領域.y, (int)描画先領域.GetW(), (int)描画先領域.GetH() };
			SDL_Rect part = { (int)描画元領域.x + this->part.x, (int)描画元領域.y + this->part.y, (int)描画元領域.GetW(), (int)描画元領域.GetH() };

			if (Camera::Get())
			{
				temp = Camera::Get()->TransRect(temp);
			}

			//サイズがマイナスなら描画しない
			if (temp.w < 0 || temp.h < 0)
			{
				return false;
			}

			RGBACulculate();
			return !SDL_RenderCopyEx(Screen::GetHandle(), handle, &part, &temp, 0, nullptr, SDL_RendererFlip(反転フラグ));
		}

		/** 幅を取得.*/
		int GetWidth() const
		{
			return part.w;
		}

		/** 高さを取得.*/
		int GetHeight() const
		{
			return part.h;
		}

		/** 描画色を指定.*/
		void SetColor(const Color &描画色)
		{
			color.SetColor(描画色.GetRed(), 描画色.GetGreen(), 描画色.GetBlue(), 描画色.GetAlpha());
		}
	};
}