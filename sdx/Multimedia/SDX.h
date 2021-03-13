//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <vector>
#include <string>
#include <memory>
#include <math.h>
#include <algorithm>
#include <list>
#include <iomanip>

#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <thread>
#include <mutex>
#include <cmath>

/** SDXFramework共通の名前空間.*/
namespace SDX
{
	const double PAI = 3.1415926535897931;//!< 円周率
	const double DEG = PAI / 180;//!< ラジアンにおける1℃
	/**Aから見たBの角度差を-PAI～+PAIで返す.*/
	double CompAngle(double 角度A, double 角度B);
}

//モノステートパターン実現のために暫定的に、マクロ使用。変えるかも
#define MONO_STATE(a) \
a() = default;\
~a() = default;\
void operator =(const a& src) = delete;\
a(const a& src) = delete;\
void operator =(const a&& src) = delete;\
a(const a&& src) = delete;

//Windowsのみ有効なコード
#pragma comment(lib, "SDL2.lib")

#if _MSC_VER > 1800
	#ifdef _DEBUG
		#pragma comment(lib, "SDL2main_2015.lib")
	#else
		#pragma comment(lib, "SDL2main_2015_MT.lib")
	#endif
#else
	#ifdef _DEBUG
		#pragma comment(lib, "SDL2main.lib")
	#else
		#pragma comment(lib, "SDL2main_MT.lib")
	#endif
#endif

#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_mixer.lib")

#ifndef OMIT_SDL2_TTF
	#pragma comment(lib, "SDL2_ttf.lib")
#endif

#pragma execution_character_set("utf-8")//charの文字コードをUTF-8に変更

#ifdef _DEBUG
	#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#ifdef __ANDROID__
#define TABLET
#elif defined(__IPHONEOS__)
#define TABLET
#endif

#ifdef __WINDOWS__
#include<xutility>
#else
#include <locale.h>
#define sprintf_s(a,b,c,d) sprintf(a,c,d)
#define localtime_s(a,b) a = localtime(b)
#endif