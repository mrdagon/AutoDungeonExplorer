//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>
#include <Multimedia/SubWindow.h>

namespace SDX
{
	/** アクティブなSubWindowを操作するクラス.*/
	/** WindowにあってSubWindowに無い関数は[Window専用]と表記.*/
	/** \include Window.h*/
	class Window
	{
		friend class System;
		friend class Mouse;
		friend class Gesture;
		friend class Touch;
	private:
		MONO_STATE(Window)
	public:

		static SubWindow *activeWindow;//!< 現在アクティブなウィンドウ

		/** アクティブなWindowのハンドルを取得.*/
		static SDL_Window* GetHandle()
		{
			return activeWindow->GetHandle();
		}

		/** SubWindowをアクティブにする.*/
		/**[Window専用]*/
		static void SetWindow(SubWindow &アクティブにするSubWindow = SubWindow::mainWindow)
		{
			activeWindow = &アクティブにするSubWindow;
		}

		/** スクリーンモードを設定する.*/
		static bool SetFullscreen(bool フルスクリーンフラグ)
		{
			return activeWindow->SetFullscreen( フルスクリーンフラグ );
		}

		/** ウィンドウタイトルを設定.*/
		static bool SetTitle(const char *タイトル名)
		{
			return activeWindow->SetTitle(タイトル名);
		}

		/** ウィンドウサイズの設定.*/
		static void SetSize(int 幅, int 高さ)
		{
			activeWindow->SetSize(幅,高さ);
		}

		/** 描画領域の大きさを設定する.*/
		/** 例えばSetSizeの半分にすると2倍表示になる*/
		static void SetLogicalSize(int 幅, int 高さ)
		{
			activeWindow->SetLogicalSize(幅,高さ);
		}

		/** ウィンドウ幅の取得.*/
		static int GetWidth()
		{
			return activeWindow->width;
		}

		/** ウィンドウ高さの取得.*/
		static int GetHeight()
		{
			return activeWindow->height;
		}

		/** ウィンドウの位置と座標を取得.*/
		static Rect GetSize()
		{
			return activeWindow->GetSize();
		}

		/** ウィンドウのアイコンを設定.*/
		static bool SetIcon(const char *ファイル名)
		{
			return activeWindow->SetIcon(ファイル名);
		}

	};
}