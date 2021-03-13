//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

/** OS標準の日本語フォント.*/
/** SystemFont::GothicとSystemFont::Mincho以外はプラットフォーム依存*/
/** 参考外部リンク:http://rinrin.saiin.net/~aor/fonts/fonts */
namespace SDX
{
	namespace SystemFont
	{
#ifdef __WINDOWS__
		static const char* Gothic = "C:/Windows/Fonts/msgothic.ttc";//!< 各OS標準の日本語フォント
		static const char* Mincho = "C:/Windows/Fonts/msmincho.ttc";//!< 各OS標準の日本語フォント

		static const char* UI_Gothic = "C:/Windows/Fonts/msgothic.ttc";
		static const char* Ｐゴシック = "C:/Windows/Fonts/msgothic.ttc";
		static const char* Ｐ明朝 = "C:/Windows/Fonts/msmincho.ttc";
		static const char* メイリオ = "C:/Windows/Fonts/meiryo.ttc";
		static const char* Meiryo_UI = "C:/Windows/Fonts/meiryo.ttc";
		//win8.1以降
		//static const char* 游ゴシック			= "C:/Windows/Fonts/";
		//static const char* 游ゴシック_Light	= "C:/Windows/Fonts/";
		//static const char* 游ゴシック_Bold	= "C:/Windows/Fonts/";
		//static const char* 游明朝				= "C:/Windows/Fonts/";
		//static const char* 游明朝_Demibold	= "C:/Windows/Fonts/";

#elif defined(__MACOSX__)
		const char* Gothic = "/System/Library/Fonts/ヒラギノ角ゴ ProN W3.otf";//!< 各OS標準の日本語フォント
		const char* Mincho = "/System/Library/Fonts/ヒラギノ明朝 ProN W3.otf";//!< 各OS標準の日本語フォント

		const char* ヒラギノ角ゴPro_W3 = "/Library/Fonts/ヒラギノ角ゴ Pro W3.otf";
		const char* ヒラギノ角ゴProN_W3 = "/System/Library/Fonts/ヒラギノ角ゴ ProN W3.otf";
		const char* ヒラギノ角ゴPro_W6 = "/Library/Fonts/ヒラギノ角ゴ Pro W6.otf";
		const char* ヒラギノ角ゴProN_W6 = "/System/Library/Fonts/ヒラギノ角ゴ ProN W6.otf";
		const char* ヒラギノ角ゴStd_W8 = "/Library/Fonts/ヒラギノ角ゴ Std W8.otf";
		const char* ヒラギノ角ゴStdN_W8 = "/Library/Fonts/ヒラギノ角ゴ StdN W8.otf";
		const char* ヒラギノ丸ゴPro_W4 = "/Library/Fonts/ヒラギノ丸ゴ ProN W4.otf";
		const char* ヒラギノ丸ゴProN_W4 = "/Library/Fonts/ヒラギノ丸ゴ ProN W4.otf";
		const char* ヒラギノ明朝Pro_W3 = "/Library/Fonts/ヒラギノ明朝 Pro W3.otf";
		const char* ヒラギノ明朝ProN_W3 = "/System/Library/Fonts/ヒラギノ明朝 ProN W3.otf";
		const char* ヒラギノ明朝Pro_W6 = "/Library/Fonts/ヒラギノ明朝 Pro W6.otf";
		const char* ヒラギノ明朝ProN_W6 = "/System/Library/Fonts/ヒラギノ明朝 ProN W6.otf";
		const char* 游明朝体 = "/Library/Fonts/Yu Mincho Demibold.otf";
		const char* 游ゴシック体 = "/Library/Fonts/Yu Gothic Medium.otf";
		const char* Osaka = "/Library/Fonts/Osaka.ttf";
		const char* Osaka等幅 = "/Library/Fonts/OsakaMono.ttf";
#elif defined(__LINUX__)
		static const char* Gothic = "/usr/share/fonts/";//!< 各OS標準の日本語フォント
		static const char* Mincho = "/usr/share/fonts/";//!< 各OS標準の日本語フォント

		static const char* TakaoGothic;
		static const char* TakaoExGothic;

		static const char* TakaoMincho;
		static const char* TakaoPMincho;
		static const char* TakaoEXMincho;

		static const char* Monospace;
		static const char* sans;
		static const char* serif;
#elif defined(__ANDROID__)
		static const char* Gothic = "/system/fonts/TBGothicMed_213.ttf";//!< 各OS標準の日本語フォント
		static const char* Mincho = "/system/fonts/TBGothicMed_213.ttf";//!< 各OS標準の日本語フォント
#elif defined(__IPHONEOS__)
		static const char* Gothic;//!< 各OS標準の日本語フォント
		static const char* Mincho;//!< 各OS標準の日本語フォント
#endif
	}
}