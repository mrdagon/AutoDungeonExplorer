//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Multimedia/Renderer.h>
#include <Framework/Shape.h>

namespace SDX
{
	class Image;
	/** アクティブなRendererを操作するクラス.*/
	/** ScreenにあってRendereに無い関数は[Screen専用]と表記.*/
	/** \include Screen.h*/
	class Screen
	{
	private:
		MONO_STATE(Screen)

		static Renderer *activeRenderer;//!<アクティブなRenderer
	public:

		/** スクリーンハンドルを取得.*/
		/** [Screen専用]*/
		static SDL_Renderer* GetHandle()
		{
			return activeRenderer->GetHandle();
		}

		/** アクティブなRendererを取得.*/
		/** [Screen専用]*/
		static Renderer* GetRenderer()
		{
			return activeRenderer;
		}

		/** アクティブなRendererを設定.*/
		/** [Screen専用]*/
		static void SetRenderer(Renderer &描画先Renderer = Renderer::mainRenderer)
		{
			activeRenderer = &描画先Renderer;
		}

		/** 描画先を変更.*/
		/** 引数がnullptrの場合、デフォルトに戻す*/
		/** Image::Makeで作成したTextureのみ有効.*/
		static bool SetTarget(Image *描画対象 = nullptr)
		{		
			return activeRenderer->SetTarget(描画対象);
		}

		/** 描画先Imageを取得.*/
		/** 返り値がnullptrの場合、デフォルトの描画先*/
		static Image* GetTarget()
		{
			return activeRenderer->GetTarget();
		}

		/** 描画内容を反映.*/
		/** [Screen専用]*/
		static bool Flip()
		{
			SDL_RenderPresent(GetHandle());
			return true;
		}

		/** 画面を消去する.*/
		static bool Clear()
		{
			return activeRenderer->Clear();
		}

		/** 描画領域を設定する、設定範囲外には描画されない.*/
		/** Rectの幅を0にするとクリップ領域が解除される.*/
		static bool SetClip(const Rect &非描画領域 = {0,0,0,0})
		{
			return activeRenderer->SetClip(非描画領域);
		}

		/** Screen::Clear後の色を設定.*/
		static void SetBackColor(const Color &背景色)
		{
			activeRenderer->SetBackColor(背景色);
		}

		/** 描画輝度を設定.*/
		static void SetBright(const Color &輝度 = Color::White)
		{
			activeRenderer->SetBright(輝度);
		}

		/** ブレンド描画のモードを設定.*/
		static void SetBlendMode(BlendMode ブレンドモード = BlendMode::NoBlend, int 設定値 = 255)
		{
			activeRenderer->SetBlendMode(ブレンドモード,設定値);
		}

		/** 描画輝度と描画モードをまとめて設定*/
		static void SetDrawMode(const Color &輝度＋α値 = Color::White, BlendMode ブレンドモード = BlendMode::Alpha)
		{
			activeRenderer->SetDrawMode(輝度＋α値,ブレンドモード);
		}
	};
}