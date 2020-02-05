//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#include <Windows.h>
#include <windowsx.h>
#include <imm.h>
//imm32.libが必要

//SDLのアプデで不要になった

#undef min
#undef max
LRESULT CALLBACK MyEditProc(HWND, UINT, WPARAM, LPARAM);

//#using "Windows.UI.Text.Core.dll"

class TextInput
{
public:

	SDX::File file;

	static HWND hWnd;
	static HIMC hImc;

	static HMODULE hModule;
	static HWND hEdit;

	static void EInit()
	{
		hWnd = GetActiveWindow();

		auto hundle = GetModuleHandle(NULL);

		hEdit = CreateWindow(
			TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
			0, 0, 200, 30, hWnd, (HMENU)1,
			hundle, NULL
		);

		std::string str = "あいうえお";

		SetWindowTextW(TextInput::hEdit, L"あいうえお");

		LPWSTR cmpStr[30];

		GetWindowTextW(TextInput::hEdit, cmpStr[0], 30 );


		//SetFocus(hEdit);//入力ボックスをフォーカス

		//日本語入力をON
		//hImc = ImmGetContext(hWnd);
		//ImmSetOpenStatus(hImc, TRUE);

		//auto f = SetWindowLongPtr(hEdit, -4 , (LONG)MyEditProc);
	}

	static void Update()
	{
		hImc = ImmGetContext(hWnd);
		ImmSetOpenStatus(hImc, TRUE);
	}

	static void Init()
	{
		hWnd = GetActiveWindow();
		hImc = ImmGetContext(hWnd);

		hModule = LoadLibrary(L"Windows.UI.Text.Core.dll");
	}

	static void Release()
	{
		ImmReleaseContext(hWnd, hImc);
	}

	static std::string GetComposition()
	{
		Init();

		char buffer[1028];
		int size = ImmGetCompositionStringA(hImc, GCS_COMPSTR, NULL, 0);

		ImmGetCompositionStringA(hImc, GCS_COMPSTR, buffer, size);
		buffer[size] = '\0';
		
		std::string str = buffer;

		if (size > 0)
		{
			str = buffer;
		}

		Release();

		return str;
	}

	static std::string GetEnteredString()
	{
		Init();
		//とりあえず512文字？まで
		char buffer[1028];
		int size = ImmGetCompositionStringA(hImc, GCS_COMPSTR, NULL, 0);

		ImmGetCompositionStringA(hImc, GCS_COMPSTR, buffer, size);
		buffer[size] = '\0';
		ImmReleaseContext(hWnd, hImc);

		std::string str;

		if (size > 0)
		{
			str = buffer;
		}

		Release();

		return str;
	}

	static void SetCompositionString()
	{
		Init();
		char cmpStr[] = "てすとあばばばば！";

		ImmSetCompositionStringA(hImc, SCS_SETSTR, cmpStr, sizeof(cmpStr), NULL, 0);
		ImmNotifyIME(hImc, NI_COMPOSITIONSTR, CPS_CONVERT, 0);

		Release();
	}

	static void SetSetConversionStatus(bool is日本語入力)
	{
		if (is日本語入力)
		{
			DWORD dwConv, dwSent;
			ImmGetConversionStatus(hImc, &dwConv, &dwSent);
			ImmSetConversionStatus(hImc, IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE, dwSent);
		} else {
			ImmSetConversionStatus(hImc, IME_CMODE_CHARCODE, IME_SMODE_NONE);
		}

	}

	static bool IsOpenIME()
	{
		return ImmGetOpenStatus(hImc);
	}

};

HWND TextInput::hWnd;
HIMC TextInput::hImc;
HMODULE TextInput::hModule;
HWND TextInput::hEdit;

WNDPROC OrgEditProc;
LRESULT CALLBACK MyEditProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	char szBuf[1024], szStr[1024], szAll[1024 * 64];
	HIMC hImc;

	switch (msg) {
	case WM_CHAR:
		if (wp == (WPARAM)0x1b) {
			hImc = ImmGetContext(hWnd);
			if (ImmGetOpenStatus(hImc)) {
				ImmSetOpenStatus(hImc, FALSE);
			}
			else {
				ImmSetOpenStatus(hImc, TRUE);
			}
		}
		break;
	case WM_IME_COMPOSITION:
		hImc = ImmGetContext(hWnd);
		if (lp & GCS_RESULTSTR) {
			memset(szBuf, '\0', 1024);
			ImmGetCompositionString(hImc, GCS_RESULTSTR, szBuf, 1024);
			//「%s」を確定しました\r\n", szBuf);
			//Edit_GetText(TextInput::hEdit, szAll, 1024 * 64 - 1);
			//strcat(szAll, szStr);
			//Edit_SetText(TextInput::hEdit, szAll);
			//MyScroll();
		}
		if (lp & GCS_COMPSTR) {
			memset(szBuf, '\0', 1024);
			ImmGetCompositionString(hImc, GCS_COMPSTR, szBuf, 1024);
			//編集文字列は「%s」です。\r\n", szBuf);
			//Edit_GetText(TextInput::hEdit, szAll, 1024 * 64 - 1);
			//strcat(szAll, szStr);
			//Edit_SetText(TextInput::hEdit, szAll);
			//MyScroll();
		}

		ImmReleaseContext(hWnd, hImc);
		break;
	case WM_IME_NOTIFY:
		switch (wp) {
		case IMN_CHANGECANDIDATE:
			//Edit_GetText(TextInput::hEdit, szAll, 1024 * 64 - 1);
			//"選択候補が変化しました
			//Edit_SetText(TextInput::hEdit, szAll);
			//MyScroll();
			break;
		}
		break;
	default:
		break;
	}
	return CallWindowProc(OrgEditProc, hWnd, msg, wp, lp);
}
