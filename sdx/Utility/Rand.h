//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <random>

namespace SDX
{
	/** 乱数生成関数群.*/
	/** \include Rand.h*/
	class Rand
	{
	private:
		MONO_STATE(Rand)

		static std::mt19937& Engine()
		{
			static std::mt19937 engine;//!<
			return engine;
		}
	public:
		/** 乱数を初期化する.*/
		static void Reset(int 初期化子)
		{
			Engine().seed(初期化子);
		}
		
		/** 0～最大値の乱数を取得.*/
		static double Get(double 最大値)
		{
			std::uniform_real_distribution<double> range(0.0, 最大値);
			return range(Engine());
		}
		/** 0～最大値の乱数を取得.*/
		/** 得られる値の種類は最大値+1になるので注意*/
		static int Get(int 最大値)
		{
			std::uniform_int_distribution<int> range(0, 最大値);
			return range(Engine());
		}

		/** 範囲を指定して乱数を取得.*/
		static double Get(double 最小値, double 最大値)
		{
			std::uniform_real_distribution<double> range(最小値, 最大値);
			return range(Engine());
		}
		/** 範囲を指定して乱数を取得.*/
		static int Get(int 最小値, int 最大値)
		{
			std::uniform_int_distribution<int> range(最小値, 最大値);
			return range(Engine());
		}

		/** 範囲を指定して乱数を取得.*/
		/** 1.0の場合100%の確率でtrueを返す*/
		static bool Coin(double trueになる確率)
		{
			if (trueになる確率 >= 1.0) { return true; }
			if (trueになる確率 <= 0) { return false; }

			std::bernoulli_distribution coin(std::min(trueになる確率, 1.0));

			return coin(Engine());
		}
	};
}