//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License:return ; version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Key.h>
#include <Utility/EnumArray.h>

namespace SDX
{
	/** キーボードコード.*/
	enum class KeyCode
	{
		Back,
		Tab,
		Return,
		LShift,
		RShift,
		LControl,
		RControl,
		Escape,
		Space,
		PageUp,
		PageDown,
		End,
		Home,
		Left,
		Up,
		Right,
		Down,
		Insert,
		Delete,
		Minus,
		Yen,
		PrevTrack,
		Period,
		Slash,
		LAlt,
		RAlt,
		Scroll,
		Semicolon,
		Colon,
		LBracket,
		RBracket,
		At,
		Backslash,
		Comma,
		Capslock,
		Pause,
		Numpad0,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad4,
		Numpad5,
		Numpad6,
		Numpad7,
		Numpad8,
		Numpad9,
		Multiply,
		Add,
		Subtract,
		Decimal,
		Divide,
		NUMPADEnter,

		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		_0,
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,

		COUNT,
	};

	/** キーボードの状態を表すクラス.*/
	/** \include Input.h*/
	class Keyboard
	{
		friend class Input;
	private:
		MONO_STATE(Keyboard)

		EnumArray<bool, KeyCode> press;
	public:
		//とりあえずDoxygenのエラーを消すためのコメント
		Key Back;//!< キー
		Key Tab;//!< キー
		Key Return;//!< キー
		Key LShift;//!< キー
		Key RShift;//!< キー
		Key LControl;//!< キー
		Key RControl;//!< キー
		Key Escape;//!< キー
		Key Space;//!< キー
		Key PageUp;//!< キー
		Key PageDown;//!< キー
		Key End;//!< キー
		Key Home;//!< キー
		Key Left;//!< キー
		Key Up;//!< キー
		Key Right;//!< キー
		Key Down;//!< キー
		Key Insert;//!< キー
		Key Delete;//!< キー

		Key Minus;//!< キー
		Key Yen;//!< キー
		Key PrevTrack;//!< キー
		Key Period;//!< キー
		Key Slash;//!< キー
		Key LAlt;//!< キー
		Key RAlt;//!< キー
		Key Scroll;//!< キー
		Key Semicolon;//!< キー
		Key Colon;//!< キー
		Key LBracket;//!< キー
		Key RBracket;//!< キー
		Key At;//!< キー
		Key Backslash;//!< キー
		Key Comma;//!< キー
		Key Capslock;//!< キー
		Key Pause;//!< キー

		Key Numpad0;//!< キー
		Key Numpad1;//!< キー
		Key Numpad2;//!< キー
		Key Numpad3;//!< キー
		Key Numpad4;//!< キー
		Key Numpad5;//!< キー
		Key Numpad6;//!< キー
		Key Numpad7;//!< キー
		Key Numpad8;//!< キー
		Key Numpad9;//!< キー
		Key Multiply;//!< キー
		Key Add;//!< キー
		Key Subtract;//!< キー
		Key Decimal;//!< キー
		Key Divide;//!< キー
		Key NUMPADEnter;//!< キー

		Key F1;//!< キー
		Key F2;//!< キー
		Key F3;//!< キー
		Key F4;//!< キー
		Key F5;//!< キー
		Key F6;//!< キー
		Key F7;//!< キー
		Key F8;//!< キー
		Key F9;//!< キー
		Key F10;//!< キー
		Key F11;//!< キー
		Key F12;//!< キー

		Key A;//!< キー
		Key B;//!< キー
		Key C;//!< キー
		Key D;//!< キー
		Key E;//!< キー
		Key F;//!< キー
		Key G;//!< キー
		Key H;//!< キー
		Key I;//!< キー
		Key J;//!< キー
		Key K;//!< キー
		Key L;//!< キー
		Key M;//!< キー
		Key N;//!< キー
		Key O;//!< キー
		Key P;//!< キー
		Key Q;//!< キー
		Key R;//!< キー
		Key S;//!< キー
		Key T;//!< キー
		Key U;//!< キー
		Key V;//!< キー
		Key W;//!< キー
		Key X;//!< キー
		Key Y;//!< キー
		Key Z;//!< キー
		Key _0;//!< キー
		Key _1;//!< キー
		Key _2;//!< キー
		Key _3;//!< キー
		Key _4;//!< キー
		Key _5;//!< キー
		Key _6;//!< キー
		Key _7;//!< キー
		Key _8;//!< キー
		Key _9;//!< キー

		/** 状態のリセット.*/
		void Reset()
		{
			Back.Reset();
			Tab.Reset();
			Return.Reset();
			LShift.Reset();
			RShift.Reset();
			LControl.Reset();
			RControl.Reset();
			Escape.Reset();
			Space.Reset();
			PageUp.Reset();
			PageDown.Reset();
			End.Reset();
			Home.Reset();
			Left.Reset();
			Up.Reset();
			Right.Reset();
			Down.Reset();
			Insert.Reset();
			Delete.Reset();

			Minus.Reset();
			Yen.Reset();
			PrevTrack.Reset();
			Period.Reset();
			Slash.Reset();
			LAlt.Reset();
			RAlt.Reset();
			Scroll.Reset();
			Semicolon.Reset();
			Colon.Reset();
			LBracket.Reset();
			RBracket.Reset();
			At.Reset();
			Backslash.Reset();
			Comma.Reset();
			Capslock.Reset();
			Pause.Reset();

			Numpad0.Reset();
			Numpad1.Reset();
			Numpad2.Reset();
			Numpad3.Reset();
			Numpad4.Reset();
			Numpad5.Reset();
			Numpad6.Reset();
			Numpad7.Reset();
			Numpad8.Reset();
			Numpad9.Reset();
			Multiply.Reset();
			Add.Reset();
			Subtract.Reset();
			Decimal.Reset();
			Divide.Reset();
			NUMPADEnter.Reset();

			F1.Reset();
			F2.Reset();
			F3.Reset();
			F4.Reset();
			F5.Reset();
			F6.Reset();
			F7.Reset();
			F8.Reset();
			F9.Reset();
			F10.Reset();
			F11.Reset();
			F12.Reset();

			A.Reset();
			B.Reset();
			C.Reset();
			D.Reset();
			E.Reset();
			F.Reset();
			G.Reset();
			H.Reset();
			I.Reset();
			J.Reset();
			K.Reset();
			L.Reset();
			M.Reset();
			N.Reset();
			O.Reset();
			P.Reset();
			Q.Reset();
			R.Reset();
			S.Reset();
			T.Reset();
			U.Reset();
			V.Reset();
			W.Reset();
			X.Reset();
			Y.Reset();
			Z.Reset();
			_0.Reset();
			_1.Reset();
			_2.Reset();
			_3.Reset();
			_4.Reset();
			_5.Reset();
			_6.Reset();
			_7.Reset();
			_8.Reset();
			_9.Reset();
		}

		/** 状態の更新.*/
		void Update()
		{
			Back.Update(press[KeyCode::Back]);
			Tab.Update(press[KeyCode::Tab]);
			Return.Update(press[KeyCode::Return]);
			LShift.Update(press[KeyCode::LShift]);
			RShift.Update(press[KeyCode::RShift]);
			LControl.Update(press[KeyCode::LControl]);
			RControl.Update(press[KeyCode::RControl]);
			Escape.Update(press[KeyCode::Escape]);
			Space.Update(press[KeyCode::Space]);
			PageUp.Update(press[KeyCode::PageUp]);
			PageDown.Update(press[KeyCode::PageDown]);
			End.Update(press[KeyCode::End]);
			Home.Update(press[KeyCode::Home]);
			Left.Update(press[KeyCode::Left]);
			Up.Update(press[KeyCode::Up]);
			Right.Update(press[KeyCode::Right]);
			Down.Update(press[KeyCode::Down]);
			Insert.Update(press[KeyCode::Insert]);
			Delete.Update(press[KeyCode::Delete]);

			Minus.Update(press[KeyCode::Minus]);
			Yen.Update(press[KeyCode::Yen]);
			PrevTrack.Update(press[KeyCode::PrevTrack]);
			Period.Update(press[KeyCode::Period]);
			Slash.Update(press[KeyCode::Slash]);
			LAlt.Update(press[KeyCode::LAlt]);
			RAlt.Update(press[KeyCode::RAlt]);
			Scroll.Update(press[KeyCode::Scroll]);
			Semicolon.Update(press[KeyCode::Semicolon]);
			Colon.Update(press[KeyCode::Colon]);
			LBracket.Update(press[KeyCode::LBracket]);
			RBracket.Update(press[KeyCode::RBracket]);
			At.Update(press[KeyCode::At]);
			Backslash.Update(press[KeyCode::Backslash]);
			Comma.Update(press[KeyCode::Comma]);
			Capslock.Update(press[KeyCode::Capslock]);
			Pause.Update(press[KeyCode::Pause]);

			Numpad0.Update(press[KeyCode::Numpad0]);
			Numpad1.Update(press[KeyCode::Numpad1]);
			Numpad2.Update(press[KeyCode::Numpad2]);
			Numpad3.Update(press[KeyCode::Numpad3]);
			Numpad4.Update(press[KeyCode::Numpad4]);
			Numpad5.Update(press[KeyCode::Numpad5]);
			Numpad6.Update(press[KeyCode::Numpad6]);
			Numpad7.Update(press[KeyCode::Numpad7]);
			Numpad8.Update(press[KeyCode::Numpad8]);
			Numpad9.Update(press[KeyCode::Numpad9]);
			Multiply.Update(press[KeyCode::Multiply]);
			Add.Update(press[KeyCode::Add]);
			Subtract.Update(press[KeyCode::Subtract]);
			Decimal.Update(press[KeyCode::Decimal]);
			Divide.Update(press[KeyCode::Divide]);
			NUMPADEnter.Update(press[KeyCode::NUMPADEnter]);

			F1.Update(press[KeyCode::F1]);
			F2.Update(press[KeyCode::F2]);
			F3.Update(press[KeyCode::F3]);
			F4.Update(press[KeyCode::F4]);
			F5.Update(press[KeyCode::F5]);
			F6.Update(press[KeyCode::F6]);
			F7.Update(press[KeyCode::F7]);
			F8.Update(press[KeyCode::F8]);
			F9.Update(press[KeyCode::F9]);
			F10.Update(press[KeyCode::F10]);
			F11.Update(press[KeyCode::F11]);
			F12.Update(press[KeyCode::F12]);

			A.Update(press[KeyCode::A]);
			B.Update(press[KeyCode::B]);
			C.Update(press[KeyCode::C]);
			D.Update(press[KeyCode::D]);
			E.Update(press[KeyCode::E]);
			F.Update(press[KeyCode::F]);
			G.Update(press[KeyCode::G]);
			H.Update(press[KeyCode::H]);
			I.Update(press[KeyCode::I]);
			J.Update(press[KeyCode::J]);
			K.Update(press[KeyCode::K]);
			L.Update(press[KeyCode::L]);
			M.Update(press[KeyCode::M]);
			N.Update(press[KeyCode::N]);
			O.Update(press[KeyCode::O]);
			P.Update(press[KeyCode::P]);
			Q.Update(press[KeyCode::Q]);
			R.Update(press[KeyCode::R]);
			S.Update(press[KeyCode::S]);
			T.Update(press[KeyCode::T]);
			U.Update(press[KeyCode::U]);
			V.Update(press[KeyCode::V]);
			W.Update(press[KeyCode::W]);
			X.Update(press[KeyCode::X]);
			Y.Update(press[KeyCode::Y]);
			Z.Update(press[KeyCode::Z]);
			_0.Update(press[KeyCode::_0]);
			_1.Update(press[KeyCode::_1]);
			_2.Update(press[KeyCode::_2]);
			_3.Update(press[KeyCode::_3]);
			_4.Update(press[KeyCode::_4]);
			_5.Update(press[KeyCode::_5]);
			_6.Update(press[KeyCode::_6]);
			_7.Update(press[KeyCode::_7]);
			_8.Update(press[KeyCode::_8]);
			_9.Update(press[KeyCode::_9]);
		}

		/** いずれかのキーが押されているか取得.*/
		static bool HoldAnyKey()
		{
			int size;
			const Uint8 *press = SDL_GetKeyboardState(&size);

			for (int a = 0; a < size; ++a)
			{
				if (press[a]) return true;
			}

			return false;
		}

		/** KeyCodeでアクセス.*/
		/** KeyCode::COUNTや範囲外の場合Returnを返す*/
		Key& operator[](KeyCode index)
		{
			switch (index)
			{
			case KeyCode::Back:return Back;
			case KeyCode::Tab:return Tab;
			case KeyCode::Return:return Return;
			case KeyCode::LShift:return LShift;
			case KeyCode::RShift:return RShift;
			case KeyCode::LControl:return LControl;
			case KeyCode::RControl:return RControl;
			case KeyCode::Escape:return Escape;
			case KeyCode::Space:return Space;
			case KeyCode::PageUp:return PageUp;
			case KeyCode::PageDown:return PageDown;
			case KeyCode::End:return End;
			case KeyCode::Home:return Home;
			case KeyCode::Left:return Left;
			case KeyCode::Up:return Up;
			case KeyCode::Right:return Right;
			case KeyCode::Down:return Down;
			case KeyCode::Insert:return Insert;
			case KeyCode::Delete:return Delete;
			case KeyCode::Minus:return Minus;
			case KeyCode::Yen:return Yen;
			case KeyCode::PrevTrack:return PrevTrack;
			case KeyCode::Period:return Period;
			case KeyCode::Slash:return Slash;
			case KeyCode::LAlt:return LAlt;
			case KeyCode::RAlt:return RAlt;
			case KeyCode::Scroll:return Scroll;
			case KeyCode::Semicolon:return Semicolon;
			case KeyCode::Colon:return Colon;
			case KeyCode::LBracket:return LBracket;
			case KeyCode::RBracket:return RBracket;
			case KeyCode::At:return At;
			case KeyCode::Backslash:return Backslash;
			case KeyCode::Comma:return Comma;
			case KeyCode::Capslock:return Capslock;
			case KeyCode::Pause:return Pause;
			case KeyCode::Numpad0:return Numpad0;
			case KeyCode::Numpad1:return Numpad1;
			case KeyCode::Numpad2:return Numpad2;
			case KeyCode::Numpad3:return Numpad3;
			case KeyCode::Numpad4:return Numpad4;
			case KeyCode::Numpad5:return Numpad5;
			case KeyCode::Numpad6:return Numpad6;
			case KeyCode::Numpad7:return Numpad7;
			case KeyCode::Numpad8:return Numpad8;
			case KeyCode::Numpad9:return Numpad9;
			case KeyCode::Multiply:return Multiply;
			case KeyCode::Add:return Add;
			case KeyCode::Subtract:return Subtract;
			case KeyCode::Decimal:return Decimal;
			case KeyCode::Divide:return Divide;
			case KeyCode::NUMPADEnter:return NUMPADEnter;

			case KeyCode::F1:return F1;
			case KeyCode::F2:return F2;
			case KeyCode::F3:return F3;
			case KeyCode::F4:return F4;
			case KeyCode::F5:return F5;
			case KeyCode::F6:return F6;
			case KeyCode::F7:return F7;
			case KeyCode::F8:return F8;
			case KeyCode::F9:return F9;
			case KeyCode::F10:return F10;
			case KeyCode::F11:return F11;
			case KeyCode::F12:return F12;
			case KeyCode::A:return A;
			case KeyCode::B:return B;
			case KeyCode::C:return C;
			case KeyCode::D:return D;
			case KeyCode::E:return E;
			case KeyCode::F:return F;
			case KeyCode::G:return G;
			case KeyCode::H:return H;
			case KeyCode::I:return I;
			case KeyCode::J:return J;
			case KeyCode::K:return K;
			case KeyCode::L:return L;
			case KeyCode::M:return M;
			case KeyCode::N:return N;
			case KeyCode::O:return O;
			case KeyCode::P:return P;
			case KeyCode::Q:return Q;
			case KeyCode::R:return R;
			case KeyCode::S:return S;
			case KeyCode::T:return T;
			case KeyCode::U:return U;
			case KeyCode::V:return V;
			case KeyCode::W:return W;
			case KeyCode::X:return X;
			case KeyCode::Y:return Y;
			case KeyCode::Z:return Z;
			case KeyCode::_0:return _0;
			case KeyCode::_1:return _1;
			case KeyCode::_2:return _2;
			case KeyCode::_3:return _3;
			case KeyCode::_4:return _4;
			case KeyCode::_5:return _5;
			case KeyCode::_6:return _6;
			case KeyCode::_7:return _7;
			case KeyCode::_8:return _8;
			case KeyCode::_9:return _9;
			default: return Return;
			}
		}

	};
}