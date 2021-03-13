//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

namespace SDX
{
	/** 変化する数値のポリシー.*/
	namespace SPEED
	{
		/** 速度のインターフェース.*/
		/// \include Speed.h
		class ISpeed
		{
		public:
			virtual ~ISpeed(){};

			/** 現在の速度を取得.*/
			virtual double Get() const = 0;

			/** 速度を更新.*/
			virtual double Update() = 0;
		};
	}
}