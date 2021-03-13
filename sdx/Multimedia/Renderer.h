//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Multimedia/Renderer.h>
#include <Framework/Shape.h>
#include <Framework/Camera.h>

namespace SDX
{
	/** ブレンドモード.*/
	enum class BlendMode
	{
		NoBlend = SDL_BLENDMODE_NONE,//!< ブレンドしない
		Alpha = SDL_BLENDMODE_BLEND,//!< αブレンド
		Add = SDL_BLENDMODE_ADD,//!< 加算ブレンド
		Mula = SDL_BLENDMODE_MOD,//!< 積算ブレンド
	};

	class Image;

	/** 描画先を表すクラス.*/
	/** Screenに無くてRendereにある関数は[Renderer専用]と表記.*/
	/** \include Screen.h.*/
	class Renderer
	{
		friend class SubWindow;
		friend class Drawing;
	private:
		SDL_Renderer* handle = nullptr; 
		SDL_Surface* surface = nullptr;
		Image* target = nullptr;//!< 描画先Imageのハンドル、nullptrならデフォルト
		bool isWindow = true;//!< ウィンドウに対応しているかどうか

		/*Windowに対応した、Rendererを生成.*/
		bool Create(SDL_Window* 元Window)
		{
			if (handle != nullptr){ return false ;}

			isWindow = true;
			//handle = SDL_CreateRenderer(元Window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
			handle = SDL_CreateRenderer(元Window, -1, SDL_RENDERER_PRESENTVSYNC);
			surface = SDL_GetWindowSurface(元Window);
			return true;
		}
	public:
		static Renderer &mainRenderer;//!< メインウィンドウのレンダラー

		BlendMode blendMode = BlendMode::NoBlend;//!< 描画モード
		Color clearColor = Color(0, 0, 0);//!< 消去時の色
		Color rgba = Color(255, 255, 255, 255);//!< 描画輝度とα値

		Renderer(){};

		~Renderer()
		{
			Destroy();
		}

		/**コンストラクタ.*/
		Renderer(int 幅, int 高さ)
		{
			Create(幅,高さ);
		}

		/**描画ハンドルを取得.*/
		SDL_Renderer* GetHandle()
		{
			return handle;
		}

		/** Windowと独立した、Rendererを生成.*/
		/** [Renderer専用]*/
		bool Create(int 幅, int 高さ)
		{
			if (handle != nullptr) return false;

			isWindow = false;
			surface = SDL_CreateRGBSurface(0, 幅, 高さ, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
			
			handle = SDL_CreateSoftwareRenderer(surface);
			return true;
		}

		/** Rendererを削除.*/
		/** Windowに対応して生成したRendererは削除不可.*/
		/** [Renderer専用]*/
		bool Destroy()
		{
			if ( isWindow){ return false; }
			if (handle == 0){ return false; }
			if (surface != nullptr)
			{
				SDL_FreeSurface(surface);
			}

			SDL_DestroyRenderer(handle);


			surface = nullptr;
			handle = nullptr;

			return true;
		}

		/** 透過色を設定.*/
		/** [Renderer専用]*/
		bool SetTransColor(const Color &透過色)
		{
			if (!surface){ return false; }
			return !SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 透過色.GetRed(), 透過色.GetBlue(), 透過色.GetGreen()));
		}

		/** 透過色を解除.*/
		/** [Renderer専用]*/
		bool ResetTransColor()
		{
			if (!surface){ return false; }
			return !SDL_SetColorKey(surface, false, 0);
		}

		/**対象RenderHandleにコピー.*/
		/** 処理が重い、Cameraの影響を受けない*/
		/** [Renderer専用]*/
		bool Draw(const Rect& 領域, Renderer& コピー先 = Renderer::mainRenderer)
		{
			if (!surface){ return false; }

			SDL_Texture* image;
			image = SDL_CreateTextureFromSurface(コピー先.GetHandle(), surface);

			SDL_Rect srcrect = { 0, 0, (int)領域.GetW(), (int)領域.GetH() };
			SDL_Rect dsrect = { (int)領域.GetX(), (int)領域.GetY(), (int)領域.GetW(), (int)領域.GetH() };
			SDL_RenderCopy(コピー先.GetHandle(), image, &srcrect, &dsrect);
			SDL_DestroyTexture(image);

			return true;
		}

		SDL_Texture* GetTexture()
		{
			const Uint32 format = SDL_PIXELFORMAT_ARGB8888;

			int w, h;
			SDL_GetRendererOutputSize(handle, &w, &h);

			SDL_Surface* sshot = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, format);
			//SDL_Surface* sshot = SDL_CreateRGBSurface(0, 幅 , 高さ, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
			SDL_RenderReadPixels(GetHandle(), NULL, format, sshot->pixels, sshot->pitch);
			SDL_Texture* image = SDL_CreateTextureFromSurface(GetHandle(), sshot);
			SDL_FreeSurface(sshot);
			return image;
		}

		/** 対象RenderHandleにコピー.*/
		/** 処理が重い、Cameraの影響を受けない*/
		/** [Renderer専用]*/
		bool DrawExtend(const Rect& 元範囲, const Rect& コピー先範囲, Renderer& コピー先 = Renderer::mainRenderer)
		{
			if (!surface){ return false; }

			SDL_Texture* image = SDL_CreateTextureFromSurface(コピー先.GetHandle(), surface);

			SDL_Rect srcrect = { (int)元範囲.GetX(), (int)元範囲.GetY(), (int)元範囲.GetW(), (int)元範囲.GetH() };
			SDL_Rect dsrect = { (int)コピー先範囲.GetX(), (int)コピー先範囲.GetY(), (int)コピー先範囲.GetW(), (int)コピー先範囲.GetH() };

			SDL_BlitScaled(surface, &srcrect, コピー先.surface, &dsrect);
			SDL_RenderCopy(コピー先.GetHandle(), image, &srcrect, &dsrect);
			SDL_DestroyTexture(image);

			return true;
		}

		/** 画面を消去する.*/
		bool Clear()
		{
			if (handle == nullptr){ return false; }

			SDL_SetRenderDrawColor
				(
				handle,
				clearColor.GetRed(),
				clearColor.GetGreen(),
				clearColor.GetBlue(),
				clearColor.GetAlpha()
				);
			SDL_RenderClear(handle);
			return true;
		}

		/** 描画先を変更.*/
		/** 引数がnullptrの場合、デフォルトに戻す*/
		/** Image::Makeで作成したTextureのみ有効.*/
		bool SetTarget(Image *描画対象 = nullptr);

		/** 現在の描画先を取得する.*/
		/** デフォルトの場合nullptrを返す*/
		Image* GetTarget()
		{
			return target;
		}

		/** 描画領域を設定する、範囲外には描画されない.*/
		/** 幅を0にするとクリップ領域を解除する.*/
		bool SetClip(const Rect &描画領域 = {0,0,0,0})
		{
			if (handle == nullptr){ return false; }

			if (描画領域.GetW() == 0)
			{
				return !SDL_RenderSetClipRect(handle, 0);
			}

			SDL_Rect rect;
			if (Camera::Get())
			{
				rect = Camera::Get()->TransRect(描画領域);
			}
			else
			{
				rect = 描画領域;
			}

			return !SDL_RenderSetClipRect(handle, &rect);
		}

		/** Screen::Clear後の色を設定.*/
		void SetBackColor(const Color &背景色)
		{
			clearColor.SetColor(背景色.GetRed(), 背景色.GetGreen(), 背景色.GetBlue() );
		}

		/** 描画輝度を設定.*/
		/** α値は変更しない*/
		void SetBright(const Color &輝度)
		{
			rgba.SetColor(輝度.GetRed(), 輝度.GetGreen(), 輝度.GetBlue());
		}

		/** 描画モードを設定.*/
		void SetBlendMode(BlendMode ブレンドモード, int α値)
		{
			blendMode = ブレンドモード;
			if (α値 > 255 || ブレンドモード == BlendMode::NoBlend){ α値 = 255; }
			else if (α値 < 0){ α値 = 0; }

			rgba.SetColor(rgba.GetRed(),rgba.GetGreen(),rgba.GetBlue(),α値);
		}

		/** 描画輝度と描画モードをまとめて設定*/
		void SetDrawMode(const Color &輝度＋α値 = Color::White, BlendMode ブレンドモード = BlendMode::NoBlend)
		{
			SetBright(輝度＋α値);
			SetBlendMode(ブレンドモード, 輝度＋α値.GetAlpha());
		}
	};
}