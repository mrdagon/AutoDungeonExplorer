//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include<Multimedia/SDX.h>
#include<Multimedia/Image.h>

namespace SDX
{
	/** Image同士の合成処理を行う関数群[未実装].*/ 
	/** 合成元のImageと入力Imageを合成し、画像編集ソフトにあるような合成処理を施す。\n*/
	/**	合成率は0.0～1.0の範囲で指定し、率が高い程入力の影響が強くなる。\n*/
	/**	\include Blend.h*/
	/** @todo 実装が面倒なので後回し*/
	class Blend
	{
	private:
		MONO_STATE(Blend)

		/** 同じ大きさでないと合成失敗.*/
		static bool CheckSize(const Image *A, const Image *B)
		{
			return (A->GetHeight() == B->GetWidth() && A->GetWidth() == B->GetWidth());
		}
	public:
		/** 加算合成.*/
		/** 合成イメージに入力イメージの色を足す。*/
		static bool Add(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			if (!CheckSize(合成元, 入力)){ return false; }

			return false;
		}

		/** 焼き込み合成.*/
		/** 合成して暗くする。\n*/
		/**	[計算方法]\n*/
		/**	合成後の色 = 1.0 - ( 1.0 -  合成元の色 ) / 入力の色\n*/
		/**	※入力の色が0.0の時、合成後の色は0.0*/
		static bool Burn(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 比較合成(暗).*/
		/** 合成と入力の暗い方を合成後の色にする。*/
		static bool Darken(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 減算合成.*/
		/** 合成イメージから、入力イメージを減算する。*/
		static bool Difference(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 覆い焼き合成.*/
		/** 合成後、明るくする。\n*/
		/**	[計算方法]\n*/
		/**	合成後の色 = 合成元の色 / (1.0 - 入力の色)\n*/
		/**	※入力の色が1.0の場合、合成後の色は1.0*/
		static bool Dodge(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 除外合成.*/
		/** 合成後、暗くする。\n*/
		/**	[計算方法]\n*/
		/**	合成後 = 合成元 + 入力 - 2.0 * 合成元 * 入力*/
		static bool Exclusion(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** ハードライト合成.*/
		/** オーバーレイ合成の条件を、合成元から入力に変更して計算。*/
		static bool HardLight(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 比較合成(明).*/
		/** 合成と入力の明るい方を合成後の色にする。*/
		static bool Lighten(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 乗算合成.*/
		/** 二つのイメージの色を乗算する。\n*/
		/**	各成分は0.0～1.0の値に見立てて乗算を行うので、\n*/
		/**	元の色より暗くなる事はあっても明るくなることはない。*/
		static bool Multiple(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** 通常合成.*/
		/** 特殊な効果を付けずに合成\n*/
		/**	合成率が1に近いほど、入力画像の不透明度が高くなる。*/
		static bool Normal(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** オーバーレイ合成.*/
		/** 合成イメージの色が0.5以下の部分は暗く、それ以外は明るくする合成。\n*/
		/**	[計算方法]\n*/
		/**	GrHandleの色が0.5以下:\n*/
		/**	合成後の色 = 合成元の色 * 入力の色 * 2.0\n*/
		/**	それ以外:\n*/
		/**	合成後の色 = 2.0 * ( 合成元の色 + 入力の色 - 合成元の色 * 入力の色 ) - 1.0*/
		static bool OverLay(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** RGBAの要素を選択して合成.*/
		/** 合成後の画像として赤・緑・青・αの各成分を 合成元、入力のどちらのどの要素から取るかを指定する。\n*/
		/** どの色要素を使うかはRGBAのアルファベット4文字で指定し、大文字なら合成元、小文字なら入力から取る.*/
		/**	例えば『gBAr』とした場合、赤=入力の緑、緑=合成元の青、青=合成元のα、α=入力のαとなる。*/
		static bool RgbaSelectMix(Image* 合成元, const Image *入力, std::string 色要素指定, double 合成率 = 1.0)
		{
			return false;
		}

		/** スクリーン合成.*/
		/** 加算合成のように明るくする。\n*/
		/**	[計算方法]\n*/
		/**	合成後の色 = 1.0f - ( ( 1.0f - 合成イメージの色 ) * ( 1.0f - 入力イメージの色 ) )*/
		static bool Screen(Image* 合成元, const Image *入力, double 合成率 = 1.0)
		{
			return false;
		}

		/** ソフトライト合成.*/
		/** 合成イメージの色が0.5以下の部分は暗く、それ以外は明るくする合成。\n*/
		/**	[計算方法]\n*/
		/**	GrHandleの色が0.5以下:\n*/
		/**	合成後の色 = pow( 合成元, ( 1.0f - 入力 ) * 2.0 )\n*/
		/**	それ以外:\n*/
		/**	合成後の色 = pow( 合成元, 0.5 / 入力 )*/
		static bool SoftLight(Image* 合成元, const Image *入力, double 合成率)
		{
			return false;
		}

	};
}