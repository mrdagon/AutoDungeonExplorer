//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Keyboard.h>
#include <Multimedia/Mouse.h>
#include <Multimedia/Joypad.h>
#include <Multimedia/Touch.h>
#include <Multimedia/Gesture.h>
#include <Multimedia/Window.h>

namespace SDX
{
	/** キーやマウスによる入力をまとめて管理するクラス.*/
	/** \include Input.h*/
	class Input
	{
	private:
		MONO_STATE(Input)
	public:
		static Joypad pad;//!< ジョイパッド
		static Mouse mouse;//!< マウス 
		static Keyboard key;//!< キーボード
		static Touch touch[10];//!< タッチ
		static Gesture gesture;//!< タッチジェスチャー

		/** 入力状態をリセット.*/
		static void Reset()
		{
			pad.Reset();
			mouse.Reset();
			key.Reset();
			for (auto && it : touch)
			{
				it.Reset();
			}
			gesture.Reset();
		}

		/** 入力状態を更新.*/
		static void Update()
		{
			//押下状態が変化無い場合Update出来ないので必要な処理
			SDL_JoystickUpdate();
			pad.Update();
			mouse.Update();
			key.Update();

			for (auto && it : touch)
			{
				it.Update();
			}

			gesture.Update();
		}

		/** 入力の状態変化を取得.*/
		static void GetState(SDL_Event &event)
		{
			bool isPush = true;

			switch (event.type)
			{
			case SDL_KEYUP:
				isPush = false;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_BACKSPACE: key.press[KeyCode::Back] = isPush; break;
				case SDLK_TAB: key.press[KeyCode::Tab] = isPush; break;
				case SDLK_RETURN: key.press[KeyCode::Return] = isPush; break;
				case SDLK_LSHIFT: key.press[KeyCode::LShift] = isPush; break;
				case SDLK_RSHIFT: key.press[KeyCode::RShift] = isPush; break;
				case SDLK_LCTRL: key.press[KeyCode::LControl] = isPush; break;
				case SDLK_RCTRL: key.press[KeyCode::RControl] = isPush; break;
				case SDLK_ESCAPE: key.press[KeyCode::Escape] = isPush; break;
				case SDLK_SPACE: key.press[KeyCode::Space] = isPush; break;
				case SDLK_PAGEUP: key.press[KeyCode::PageUp] = isPush; break;
				case SDLK_PAGEDOWN: key.press[KeyCode::PageDown] = isPush; break;
				case SDLK_END: key.press[KeyCode::End] = isPush; break;
				case SDLK_HOME: key.press[KeyCode::Home] = isPush; break;
				case SDLK_LEFT:
					key.press[KeyCode::Left] = isPush;
					pad.press[PadCode::Left] = isPush;
					break;
				case SDLK_UP:
					key.press[KeyCode::Up] = isPush;
					pad.press[PadCode::Up] = isPush;
					break;
				case SDLK_RIGHT:
					key.press[KeyCode::Right] = isPush;
					pad.press[PadCode::Right] = isPush;
					break;
				case SDLK_DOWN:
					key.press[KeyCode::Down] = isPush;
					pad.press[PadCode::Down] = isPush;
					break;
				case SDLK_INSERT: key.press[KeyCode::Insert] = isPush; break;
				case SDLK_DELETE: key.press[KeyCode::Delete] = isPush; break;

				case SDLK_MINUS: key.press[KeyCode::Minus] = isPush; break;
					//case Yen = SDLK_YEN,
					//case PrevTrack = SDLK_PREVTRACK,
				case SDLK_PERIOD: key.press[KeyCode::Period] = isPush; break;
				case SDLK_SLASH: key.press[KeyCode::Slash] = isPush; break;
				case SDLK_LALT: key.press[KeyCode::LAlt] = isPush; break;
				case SDLK_RALT: key.press[KeyCode::RAlt] = isPush; break;
				case SDLK_SCROLLLOCK: key.press[KeyCode::Scroll] = isPush; break;
				case SDLK_SEMICOLON: key.press[KeyCode::Semicolon] = isPush; break;
				case SDLK_COLON: key.press[KeyCode::Colon] = isPush; break;
				case SDLK_LEFTBRACKET: key.press[KeyCode::LBracket] = isPush; break;
				case SDLK_RIGHTBRACKET: key.press[KeyCode::RBracket] = isPush; break;
				case SDLK_AT: key.press[KeyCode::At] = isPush; break;
				case SDLK_BACKSLASH: key.press[KeyCode::Backslash] = isPush; break;
				case SDLK_COMMA: key.press[KeyCode::Comma] = isPush; break;
				case SDLK_CAPSLOCK: key.press[KeyCode::Capslock] = isPush; break;
				case SDLK_PAUSE: key.press[KeyCode::Pause] = isPush; break;

				case SDLK_KP_0: key.press[KeyCode::Numpad0] = isPush; break;
				case SDLK_KP_1: key.press[KeyCode::Numpad1] = isPush; break;
				case SDLK_KP_2: key.press[KeyCode::Numpad2] = isPush; break;
				case SDLK_KP_3: key.press[KeyCode::Numpad3] = isPush; break;
				case SDLK_KP_4: key.press[KeyCode::Numpad4] = isPush; break;
				case SDLK_KP_5: key.press[KeyCode::Numpad5] = isPush; break;
				case SDLK_KP_6: key.press[KeyCode::Numpad6] = isPush; break;
				case SDLK_KP_7: key.press[KeyCode::Numpad7] = isPush; break;
				case SDLK_KP_8: key.press[KeyCode::Numpad8] = isPush; break;
				case SDLK_KP_9: key.press[KeyCode::Numpad9] = isPush; break;
				case SDLK_ASTERISK: key.press[KeyCode::Multiply] = isPush; break;
				case SDLK_KP_PLUS: key.press[KeyCode::Add] = isPush; break;
				case SDLK_KP_MINUS: key.press[KeyCode::Subtract] = isPush; break;
				case SDLK_KP_PERIOD: key.press[KeyCode::Decimal] = isPush; break;
				case SDLK_KP_DIVIDE: key.press[KeyCode::Divide] = isPush; break;
				case SDLK_KP_ENTER: key.press[KeyCode::NUMPADEnter] = isPush; break;

				case SDLK_F1: key.press[KeyCode::F1] = isPush; break;
				case SDLK_F2: key.press[KeyCode::F2] = isPush; break;
				case SDLK_F3: key.press[KeyCode::F3] = isPush; break;
				case SDLK_F4: key.press[KeyCode::F4] = isPush; break;
				case SDLK_F5: key.press[KeyCode::F5] = isPush; break;
				case SDLK_F6: key.press[KeyCode::F6] = isPush; break;
				case SDLK_F7: key.press[KeyCode::F7] = isPush; break;
				case SDLK_F8: key.press[KeyCode::F8] = isPush; break;
				case SDLK_F9: key.press[KeyCode::F9] = isPush; break;
				case SDLK_F10: key.press[KeyCode::F10] = isPush; break;
				case SDLK_F11: key.press[KeyCode::F11] = isPush; break;
				case SDLK_F12: key.press[KeyCode::F12] = isPush; break;

				case SDLK_a:
					key.press[KeyCode::A] = isPush;
					pad.press[PadCode::Button5] = isPush;
					break;
				case SDLK_b: key.press[KeyCode::B] = isPush; break;
				case SDLK_c:
					key.press[KeyCode::C] = isPush;
					pad.press[PadCode::Button3] = isPush;
					break;
				case SDLK_d:
					key.press[KeyCode::D] = isPush;
					pad.press[PadCode::Button7] = isPush;
					break;
				case SDLK_e: key.press[KeyCode::E] = isPush; break;
				case SDLK_f:
					key.press[KeyCode::F] = isPush;
					pad.press[PadCode::Button8] = isPush;
					break;
				case SDLK_g: key.press[KeyCode::G] = isPush; break;
				case SDLK_h: key.press[KeyCode::H] = isPush; break;
				case SDLK_i: key.press[KeyCode::I] = isPush; break;
				case SDLK_j: key.press[KeyCode::J] = isPush; break;
				case SDLK_k: key.press[KeyCode::K] = isPush; break;
				case SDLK_l: key.press[KeyCode::L] = isPush; break;
				case SDLK_m: key.press[KeyCode::M] = isPush; break;
				case SDLK_n:
					key.press[KeyCode::N] = isPush;
					break;
				case SDLK_o: key.press[KeyCode::O] = isPush; break;
				case SDLK_p: key.press[KeyCode::P] = isPush; break;
				case SDLK_q: key.press[KeyCode::Q] = isPush; break;
				case SDLK_r: key.press[KeyCode::R] = isPush; break;
				case SDLK_s:
					key.press[KeyCode::S] = isPush;
					pad.press[PadCode::Button6] = isPush;
					break;
				case SDLK_t: key.press[KeyCode::T] = isPush; break;
				case SDLK_u: key.press[KeyCode::U] = isPush; break;
				case SDLK_v:
					key.press[KeyCode::V] = isPush;
					pad.press[PadCode::Button4] = isPush;
					break;
				case SDLK_w: key.press[KeyCode::W] = isPush; break;
				case SDLK_x:
					key.press[KeyCode::X] = isPush;
					pad.press[PadCode::Button2] = isPush;
					break;
				case SDLK_y: key.press[KeyCode::Y] = isPush; break;
				case SDLK_z:
					key.press[KeyCode::Z] = isPush;
					pad.press[PadCode::Button1] = isPush;
					break;
				case SDLK_0: key.press[KeyCode::_0] = isPush; break;
				case SDLK_1: key.press[KeyCode::_1] = isPush; break;
				case SDLK_2: key.press[KeyCode::_2] = isPush; break;
				case SDLK_3: key.press[KeyCode::_3] = isPush; break;
				case SDLK_4: key.press[KeyCode::_4] = isPush; break;
				case SDLK_5: key.press[KeyCode::_5] = isPush; break;
				case SDLK_6: key.press[KeyCode::_6] = isPush; break;
				case SDLK_7: key.press[KeyCode::_7] = isPush; break;
				case SDLK_8: key.press[KeyCode::_8] = isPush; break;
				case SDLK_9: key.press[KeyCode::_9] = isPush; break;
				}
				break;
			case SDL_JOYAXISMOTION:
				//左右の動き
				if (event.jaxis.axis == 0)
				{
					pad.StickX = event.jaxis.value;
					//pad.press[PadCode::Left] = (event.jaxis.value < -0x7000);//左右ボタンは兼ねない
					//pad.press[PadCode::Right] = (event.jaxis.value > 0x7000);
				}
				//上下の動き
				if (event.jaxis.axis == 1)
				{
					pad.StickY = event.jaxis.value;
					//if (event.jaxis.value < -0x7000) pad.press[PadCode::Up] = true;//上下ボタンは兼ねない
					//if (event.jaxis.value > 0x7000) pad.press[PadCode::Down] = true;
				}
				break;
			case SDL_JOYHATMOTION:
				pad.press[PadCode::Up] = false;
				pad.press[PadCode::Left] = false;
				pad.press[PadCode::Down] = false;
				pad.press[PadCode::Right] = false;

				switch (event.jhat.value)
				{
				case SDL_HAT_UP:pad.press[PadCode::Up] = true; break;
				case SDL_HAT_LEFT:pad.press[PadCode::Left] = true; break;
				case SDL_HAT_DOWN:pad.press[PadCode::Down] = true; break;
				case SDL_HAT_RIGHT:pad.press[PadCode::Right] = true; break;
				case SDL_HAT_LEFTUP:pad.press[PadCode::Up] = true; pad.press[PadCode::Left] = true; break;
				case SDL_HAT_RIGHTUP:pad.press[PadCode::Up] = true; pad.press[PadCode::Right] = true; break;
				case SDL_HAT_RIGHTDOWN:pad.press[PadCode::Down] = true; pad.press[PadCode::Right] = true; break;
				case SDL_HAT_LEFTDOWN:pad.press[PadCode::Down] = true; pad.press[PadCode::Left] = true; break;
				}
				break;
			case SDL_JOYBUTTONUP:
				isPush = false;
			case SDL_JOYBUTTONDOWN:
				pad.press[(PadCode)event.jbutton.button] = isPush;
				break;
			case SDL_MOUSEMOTION:
				mouse.xBuffer = event.motion.x;
				mouse.yBuffer = event.motion.y;
				break;
			case SDL_MOUSEBUTTONUP:
				isPush = false;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:mouse.press[MouseCode::Left] = isPush; break;
				case SDL_BUTTON_RIGHT:mouse.press[MouseCode::Right] = isPush; break;
				case SDL_BUTTON_MIDDLE:mouse.press[MouseCode::Middle] = isPush; break;
				case SDL_BUTTON_X1:mouse.press[MouseCode::_4] = isPush; break;
				case SDL_BUTTON_X2:mouse.press[MouseCode::_5] = isPush; break;
				}
				break;
			case SDL_MOUSEWHEEL:
				mouse.Whell = event.button.x;
				break;
			case SDL_FINGERUP:
				isPush = false;
			case SDL_FINGERDOWN:
				if (event.tfinger.fingerId >= 10) break;
				touch[(int)event.tfinger.fingerId].press = isPush;
				if (event.tfinger.fingerId == 0) mouse.press[MouseCode::Left] = isPush;
				if (event.tfinger.fingerId == 1) mouse.press[MouseCode::Right] = isPush;
			case SDL_FINGERMOTION:
				if (event.tfinger.fingerId >= 10) break;
				//Positon関数で座標を計算
				touch[(int)event.tfinger.fingerId].Position(event.tfinger.x, event.tfinger.y);
				mouse.xBuffer = (int)touch[(int)event.tfinger.fingerId].xBuffer;
				mouse.yBuffer = (int)touch[(int)event.tfinger.fingerId].yBuffer;
				break;
			case SDL_MULTIGESTURE:
				gesture.press = true;
				gesture.fingerCount = event.mgesture.numFingers;
				gesture.pinche = event.mgesture.dDist;
				gesture.rotate = event.mgesture.dTheta;
				gesture.Position(event.mgesture.x, event.mgesture.y);
				break;
			}
		}
	};
}