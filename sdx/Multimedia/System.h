//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/Window.h>
#include <Multimedia/Input.h>
#include <Multimedia/Font.h>

namespace SDX
{
	enum class Platform
	{
		Windows,
		MacOSX,
		GNU_Linux,
		iOS,
		Android,
		Unknown,
	};

	/** ライブラリの初期化やシステム的な処理を行う関数群.*/
	/** \include System.h*/
	class System
	{
		friend class Window;

	private:
		MONO_STATE(System)

		/** シングルトンなインスタンスを取得.*/
		static bool& IsEnd()
		{
			static bool isEnd;
			return isEnd;
		}
	public:
		static std::string inputText;
		static std::string textComposition;
		static int textCursor;
		static int textSelection_len;

		/** ライブラリの初期化.*/
		/** 初期化に失敗した場合、ソフトを強制的に終了する。\n*/
		/**	一部の設定関数は初期化前に呼び出す必要がある。*/
		static void Initialise(const char* ウィンドウ名, int 幅, int 高さ, bool フルスクリーンフラグ = false)
		{
			if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
			{
				exit(1);
				return;
			}

#ifndef TABLET
			SDL_JoystickEventState(SDL_ENABLE);

			if (SDL_NumJoysticks() > 0)
			{
				Input::pad.Open();
			}
#endif

			SubWindow::mainWindow.Create(ウィンドウ名,幅,高さ,フルスクリーンフラグ);
			Screen::SetRenderer(Renderer::mainRenderer);
			Window::SetWindow(SubWindow::mainWindow);

			//タブレットと画面サイズを合わせる
#ifdef TABLET
			int dpiX;
			int dpiY;
			SDL_GetWindowSize(SubWindow::mainWindow.handle, &dpiX, &dpiY);
			SubWindow::mainWindow.aspect = (double)dpiX / dpiY;
			SDL_RenderSetLogicalSize(Screen::GetHandle(), 幅, 高さ);
#endif
			//デフォルトフォントの設定
			setlocale(LC_CTYPE, "jpn");//文字コードを日本語に

#ifndef OMIT_SDL2_TTF
			TTF_Init();
#endif
			Drawing::SetDefaultFont(SystemFont::Gothic, 16 , 2 );
			SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVERYTHING);

			//音声関連の初期化
			Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
			//Mix_OpenAudio(44100, AUDIO_S16, 2, 1024);
			Mix_OpenAudio(AUDIO_F32, MIX_DEFAULT_FORMAT, 2, 4096);

			Mix_AllocateChannels(16);
			Mix_HookMusicFinished(Music::Finished);

			SDL_StopTextInput();

			IsEnd() = false;
		}

		/** ライブラリの終了処理.*/
		/** この関数を使用した後は速やかにプログラムを終了させなければならない。*/
		static bool End()
		{
#ifndef OMIT_SDL2_TTF
			TTF_Quit();
#endif
			Mix_CloseAudio();
			Mix_Quit();
			Window::activeWindow->Destroy();
			SDL_Quit();
			IsEnd() = true;
			return true;
		}

		/** 各種更新処理をまとめて行う.*/
		static bool Update(bool 描画更新フラグ = true,bool 画面消去フラグ = true)
		{
			if (描画更新フラグ)
			{
				Screen::Flip();
			}
			if (画面消去フラグ)
			{
				Screen::Clear();
			}

			Input::Update();
			bool result = System::ProcessMessage();

			Music::Update();

			return result;
		}

		/** OSのメッセージ処理を行う.*/
		/** 目安として1/60秒に一回程度、この関数を呼び出す必要があり。*/
		/**	falseを返した場合、速やかにプログラムを終了させなければならない。*/
		/** @todo タブレット版専用の処理色々*/
		static bool ProcessMessage()
		{
			SDL_Event event;

			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
					case SDL_WINDOWEVENT:
						switch (event.window.event)
						{
						case SDL_WINDOWEVENT_CLOSE:
#ifndef TABLET
							//ここでIDに応じてDestroy等する
							SubWindow::CheckWindowID(event.window.windowID);
							if (SubWindow::mainWindow.handle == nullptr)
							{
								IsEnd() = true;
								for (auto it : SubWindow::windowS)
								{
									it->Destroy();
								}
							}
#endif
							break;
#ifdef TABLET
						case SDL_WINDOWEVENT_MINIMIZED:
							//スリープに入った時、再生中ならBGMを停止する
							if (Music::Check())
							{
								Mix_PauseMusic();
							}
							break;
						case SDL_WINDOWEVENT_RESTORED:
							//BGMを止めていたら、再開する
							Mix_ResumeMusic();
							break;
#endif
						}
						break;
					case SDL_QUIT:
						IsEnd() = true;
						break;
					case SDL_TEXTINPUT:						
						inputText += event.text.text;
						break;
					case SDL_TEXTEDITING:
						//変換中文字
						textComposition = event.edit.text;
						textCursor = event.edit.start;
						textSelection_len = event.edit.length;
						break;
					default:
						Input::GetState(event);
						break;
				}
			}

			return !IsEnd();
		}

		/** 指定ミリ秒処理を停止する.*/
		static void Wait(int 停止ミリ秒)
		{
			SDL_Delay(停止ミリ秒);
		}

		/** なんらかのキーが入力されるまで処理を停止する.*/
		static void WaitKey()
		{
			while (!Keyboard::HoldAnyKey() && System::ProcessMessage()){}
		}

		/** プラットフォームを取得する.*/
		static Platform GetPlatform()
		{
#ifdef __WINDOWS__
			return Platform::Windows;
#elif defined(__MACOSX__)
			return Platform::MacOSX;
#elif defined(__LINUX__)
			return Platform::GNU_Linux;
#elif defined(__ANDROID__)
			return Platform::Android;
#elif defined(__IPHONEOS__)
			return Platform::iOS;
#endif
			return Platform::Unknown;
		}
		
		/** タブレット端末かどうかを取得.*/
		/** @todo Windowsタブレットだとfalseになる*/
		static bool IsTablet()
		{
#ifdef __WINDOWS__
			return false;
#elif defined(__MACOSX__)
			return false;
#elif defined(__LINUX__)
			return false;
#elif defined(__ANDROID__)
			return true;
#elif defined(__IPHONEOS__)
			return true;
#endif
			return false;
		}

	};
}
