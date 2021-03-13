//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Screen.h>

namespace SDX
{
	/** ウィンドウを表すクラス.*/
	/** Windowに無くてSubWindowにある関数は[SubWindow専用]と表記.*/
	/** @todo 複数ウィンドウの動作確認は不完全*/
	/** \include Window.h*/
	class SubWindow
	{
		friend class System;
		friend class Mouse;
		friend class Gesture;
		friend class Touch;
		friend class Window;
		friend class Renderer;
	private:
		SDL_Window* handle = nullptr;//!<
		Renderer renderer;//!< 対応するRenderer
		bool isFullScreen = false;//!<フルスクリーン状態のフラグ
		int width;//!<ウィンドウの幅
		int height;//!<ウィンドウの高さ
		int logicWidth = -1;
		int logicheight = -1;
		double aspect;//!<タッチ用の画面の縦横比
		static std::list<SubWindow*> windowS;

		static void CheckWindowID(int 削除するWindowのID)
		{
			for (auto it : windowS)
			{
				if (SDL_GetWindowID(it->handle) == 削除するWindowのID)
				{
					it->Destroy();
					break;
				}
			}
		}
	public:

		static SubWindow mainWindow;//!< 現在アクティブなウィンドウ

		SubWindow() = default;

		~SubWindow()
		{
			Destroy();
		}

		/** Windowの初期化と生成.*/
		SubWindow(const char* ウィンドウ名, int 幅, int 高さ, bool フルスクリーンフラグ = false)
		{
			Create(ウィンドウ名, 幅, 高さ, フルスクリーンフラグ);
		}

		/** Windowハンドルの取得.*/
		/** [SubWindow専用]*/
		SDL_Window* GetHandle()
		{
			return handle;
		}

		/** 対応Rendererの取得.*/
		/** [SubWindow専用]*/
		Renderer& GetRenderer()
		{
			return renderer;
		}

		/** Windowの初期化と生成.*/
		/** [SubWindow専用]*/
		bool Create(const char* ウィンドウ名, int 幅, int 高さ, bool フルスクリーンフラグ = false)
		{
			if (handle != nullptr){ return false; }

			width = 幅;
			height = 高さ;
			isFullScreen = フルスクリーンフラグ;

			int flag = 0;
			if ( isFullScreen )
			{
				flag = SDL_WINDOW_FULLSCREEN;
			}

			handle = SDL_CreateWindow(ウィンドウ名, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 幅, 高さ, flag);

			renderer.Create(handle);

			windowS.push_back(this);

			return true;
		}

		/** SubWindowを削除.*/
		/** [SubWindow専用]*/
		bool Destroy()
		{
			if (handle == nullptr){ return false; }

			renderer.isWindow = false;//ウィンドウ対応フラグを折らないと削除出来ない
			renderer.Destroy();
			SDL_DestroyWindow(handle);

			if (windowS.size() >= 2)
			{
				windowS.remove(this);
			}
			handle = nullptr;

			return true;
		}

		/** ウィンドウの表示/非表示設定.*/
		/** [SubWindow専用]*/
		bool SetShowFlag(bool 表示フラグ)
		{
			if (handle == nullptr){ return false; }

			if (表示フラグ)
			{
				SDL_ShowWindow(handle);
			}
			else
			{
				SDL_HideWindow(handle);
			}

			return true;
		}

		/** スクリーンモードを設定する.*/
		bool SetFullscreen(bool フルスクリーンフラグ)
		{
			if (handle == nullptr){ return false; }

			isFullScreen = フルスクリーンフラグ;

			if ( isFullScreen)
			{
				SDL_RenderSetLogicalSize(Screen::GetHandle(), GetWidth(), GetHeight());
				SDL_SetWindowFullscreen( handle, SDL_WINDOW_FULLSCREEN_DESKTOP);
			}
			else
			{
				SDL_SetWindowFullscreen( handle, 0);
				SDL_SetWindowSize( handle, GetWidth(), GetHeight());
			}
			return true;
		}

		bool GetFullscreen()
		{
			return isFullScreen;
		}

		/** タイトルを設定.*/
		bool SetTitle(const char *タイトル名)
		{
#ifdef TABLET
			return false;
#endif
			if (handle == nullptr){ return false; }

			SDL_SetWindowTitle(handle, タイトル名);
			return true;
		}

		/** ウィンドウサイズの設定.*/
		bool SetSize(int 幅, int 高さ)
		{
			if (handle == nullptr){ return false; }

			width = 幅;
			height = 高さ;

			SDL_RenderSetLogicalSize(renderer.GetHandle(), 幅, 高さ);
			SDL_SetWindowSize(handle, 幅, 高さ);

			if (logicWidth != -1)
			{
				SDL_RenderSetLogicalSize(renderer.GetHandle(), logicWidth, logicheight);
			}

			return true;
		}

		/** 幅の取得.*/
		int GetWidth()
		{
			return width;
		}

		/** 高さの取得.*/
		int GetHeight()
		{
			return height;
		}

		/** ウィンドウの位置と座標を取得.*/
		Rect GetSize()
		{
			if (handle == nullptr){ return{ 0, 0, 0, 0 }; }

			int x, y;
			SDL_GetWindowPosition(handle, &x, &y);

			return{ x, y, width, height };
		}
		
		/** ウィンドウのアイコンを設定.*/
		bool SetIcon(const char *ファイル名)
		{
#ifdef TABLET
			return false;
#endif
			if (handle == nullptr){ return false; }

			SDL_Surface* icon = IMG_Load(ファイル名);
			if (icon == nullptr){ return false; }

			SDL_SetWindowIcon(handle, icon);
			SDL_FreeSurface(icon);

			return true;
		}

		/** 描画処理を反映する.*/
		void Update()
		{
			SDL_RenderPresent(renderer.GetHandle());
			renderer.Clear();
		}

		/** 描画領域の大きさを設定する.*/
		/** 例えばSetSizeの半分にすると2倍表示になる*/
		void SetLogicalSize(int 幅, int 高さ)
		{
			logicWidth = 幅;
			logicheight = 高さ;
			SDL_RenderSetLogicalSize(renderer.GetHandle(), 幅, 高さ);
		}
	};
}