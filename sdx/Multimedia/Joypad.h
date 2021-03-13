//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Utility/EnumArray.h>

namespace SDX
{
	/** ゲームパッドの種類.*/
	enum class PadType
	{
		KeyAndPad1,
		Pad1,
		Pad2,
		Pad3,
		Pad4,
		KeyBord
	};

	/** ゲームパッドコード.*/
	enum class PadCode :unsigned int
	{
		Button1,
		Button2,
		Button3,
		Button4,
		Button5,
		Button6,
		Button7,
		Button8,
		Button9,
		Button10,
		Button11,
		Button12,
		Button13,
		Button14,
		Button15,
		Button16,
		Button17,
		Button18,
		Button19,
		Button20,
		Button21,
		Button22,
		Button23,
		Button24,
		Button25,
		Button26,
		Button27,
		Button28,
		Down,
		Left,
		Right,
		Up,
		COUNT,
	};

	/** ジョイパッドの状態を表すクラス.*/
	/** @todo 2つ目以降のjoypad対応未実装*/
	/** \include Input.h*/
	class Joypad
	{
		friend class Input;
	private:
		PadType inputType = PadType::KeyAndPad1;//!<
		SDL_Joystick* handle = nullptr;//!<

		EnumArray<bool, PadCode> press;

		Joypad(const Joypad &joypad)
		{};

		Joypad operator =(const Joypad &joypad) = delete;
	public:
		int StickX = 0;//!< ジョイスティックの横方向入力
		int StickY = 0;//!< ジョイスティックの縦方向入力 

		Key Down;//!< キー
		Key Left;//!< キー
		Key Right;//!< キー
		Key Up;//!< キー
		Key Button1;//!< キー
		Key Button2;//!< キー
		Key Button3;//!< キー
		Key Button4;//!< キー
		Key Button5;//!< キー
		Key Button6;//!< キー
		Key Button7;//!< キー
		Key Button8;//!< キー
		Key Button9;//!< キー
		Key Button10;//!< キー
		Key Button11;//!< キー
		Key Button12;//!< キー
		Key Button13;//!< キー
		Key Button14;//!< キー
		Key Button15;//!< キー
		Key Button16;//!< キー
		Key Button17;//!< キー
		Key Button18;//!< キー
		Key Button19;//!< キー
		Key Button20;//!< キー
		Key Button21;//!< キー
		Key Button22;//!< キー
		Key Button23;//!< キー
		Key Button24;//!< キー
		Key Button25;//!< キー
		Key Button26;//!< キー
		Key Button27;//!< キー
		Key Button28;//!< キー
		
		Joypad(){}

		/** ジョイパッドを起動.*/
		void Open()
		{
			handle = SDL_JoystickOpen(0);
		}

		/** パッドの作成.*/
		void Make(PadType パッドタイプ)
		{
			inputType = パッドタイプ;
		}

		/** 状態のリセット.*/
		void Reset()
		{
			Up.Reset();
			Down.Reset();
			Left.Reset();
			Right.Reset();
			Button1.Reset();
			Button2.Reset();
			Button3.Reset();
			Button4.Reset();
			Button5.Reset();
			Button6.Reset();
			Button7.Reset();
			Button8.Reset();
			Button9.Reset();
			Button10.Reset();
			Button11.Reset();
			Button12.Reset();
			Button13.Reset();
			Button14.Reset();
			Button15.Reset();
			Button16.Reset();
			Button17.Reset();
			Button18.Reset();
			Button19.Reset();
			Button20.Reset();
			Button21.Reset();
			Button22.Reset();
			Button23.Reset();
			Button24.Reset();
			Button25.Reset();
			Button26.Reset();
			Button27.Reset();
			Button28.Reset();

			StickX = 0;
			StickY = 0;
		}

		/** 状態の更新.*/
		void Update()
		{
			Down.Update(press[PadCode::Down]);
			Left.Update(press[PadCode::Left]);
			Right.Update(press[PadCode::Right]);
			Up.Update(press[PadCode::Up]);
			Button1.Update(press[PadCode::Button1]);
			Button2.Update(press[PadCode::Button2]);
			Button3.Update(press[PadCode::Button3]);
			Button4.Update(press[PadCode::Button4]);
			Button5.Update(press[PadCode::Button5]);
			Button6.Update(press[PadCode::Button6]);
			Button7.Update(press[PadCode::Button7]);
			Button8.Update(press[PadCode::Button8]);
			Button9.Update(press[PadCode::Button9]);
			Button10.Update(press[PadCode::Button10]);
			Button11.Update(press[PadCode::Button11]);
			Button12.Update(press[PadCode::Button12]);
			Button13.Update(press[PadCode::Button13]);
			Button14.Update(press[PadCode::Button14]);
			Button15.Update(press[PadCode::Button15]);
			Button16.Update(press[PadCode::Button16]);
			Button17.Update(press[PadCode::Button17]);
			Button18.Update(press[PadCode::Button18]);
			Button19.Update(press[PadCode::Button19]);
			Button20.Update(press[PadCode::Button20]);
			Button21.Update(press[PadCode::Button21]);
			Button22.Update(press[PadCode::Button22]);
			Button23.Update(press[PadCode::Button23]);
			Button24.Update(press[PadCode::Button24]);
			Button25.Update(press[PadCode::Button25]);
			Button26.Update(press[PadCode::Button26]);
			Button27.Update(press[PadCode::Button27]);
			Button28.Update(press[PadCode::Button28]);
		}

		/** パッドタイプの取得.*/
		PadType GetInputType()
		{
			return inputType;
		}

		/** パッドタイプの設定.*/
		void SetInputType(PadType 入力タイプ)
		{
			inputType = 入力タイプ;
		}

		/** 接続中のパッド数を取得.*/
		static int GetCount()
		{
			return SDL_NumJoysticks();
		}

		/** PadCodeでアクセス.*/
		/** PadCode::COUNTや範囲外の場合Button1を返す*/
		Key& operator[](PadCode index)
		{
			switch (index)
			{
			case PadCode::Button1:return Button1;
			case PadCode::Button2: return Button2;
			case PadCode::Button3: return Button3;
			case PadCode::Button4: return Button4;
			case PadCode::Button5: return Button5;
			case PadCode::Button6: return Button6;
			case PadCode::Button7: return Button7;
			case PadCode::Button8: return Button8;
			case PadCode::Button9: return Button9;
			case PadCode::Button10: return Button10;
			case PadCode::Button11: return Button11;
			case PadCode::Button12: return Button12;
			case PadCode::Button13: return Button13;
			case PadCode::Button14: return Button14;
			case PadCode::Button15: return Button15;
			case PadCode::Button16: return Button16;
			case PadCode::Button17: return Button17;
			case PadCode::Button18: return Button18;
			case PadCode::Button19: return Button19;
			case PadCode::Button20: return Button20;
			case PadCode::Button21: return Button21;
			case PadCode::Button22: return Button22;
			case PadCode::Button23: return Button23;
			case PadCode::Button24: return Button24;
			case PadCode::Button25: return Button25;
			case PadCode::Button26: return Button26;
			case PadCode::Button27: return Button27;
			case PadCode::Button28: return Button28;
			case PadCode::Down: return Down;
			case PadCode::Left: return Left;
			case PadCode::Right: return Right;
			case PadCode::Up: return Up;
			default: return Button1;
			}
		}
	};
}