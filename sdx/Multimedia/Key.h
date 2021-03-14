//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>

namespace SDX
{
	/** 各ボタンとキーを表すクラス.*/
	/** \include Input.h*/
	class Key
	{
	public:
		bool on = false;//!< 押した瞬間
		bool off = false;//!< 離した瞬間
		bool hold = false;//!< 押されている
		unsigned int  holdCount = 0;//!< 押されている時間

		/** キーのリセット.*/
		void Reset()
		{
			on = false;
			off = false;
			hold = false;
			holdCount = 0;
		}

		/** 押下状態の更新.*/
		void Update(bool 押下フラグ)
		{
			on = (!hold && 押下フラグ);
			off = (hold && !押下フラグ);

			hold = 押下フラグ;

			if (押下フラグ)
			{
				holdCount++;
			}
			else
			{
				holdCount = 0;
			}
		}

		bool IsPush(int 連打開始時間, int 連打間隔)
		{
			if (on == true) { return true; }
			if (holdCount > 連打開始時間 && (holdCount - 連打開始時間) % 連打間隔)
			{
				return true;
			}

			return false;
		}
	};
}