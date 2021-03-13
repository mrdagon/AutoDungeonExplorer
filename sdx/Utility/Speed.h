//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Utility/ISpeed.h>

namespace SDX
{
	namespace SPEED
	{
		/** 常に同じ速度.*/
		/** \include Speed.h */
		class Liner : public ISpeed
		{
		private:
			double speed;//速度
		public:

			/** 速度を指定する.*/
			Liner(double 速度) :
				speed(速度)
			{}

			double Get() const override
			{
				return speed;
			}

			double Update() override
			{
				return Get();
			}
		};

		/** 加速する.*/
		/** \include Speed.h */
		class Accel : public ISpeed
		{
		private:
			double speed;//!< 現在の速度
			double accel;//!< 加速度
		public:

			/** 初速と加速度を指定.*/
			Accel(double 初速, double 加速度) :
				speed(初速),
				accel(加速度)
			{}

			double Get() const override
			{
				return speed;
			}

			double Update() override
			{
				speed += accel;
				return Get();
			}
		};

		/** 0～速度で周期的に変化.*/
		/** \include Speed.h */
		class Wave : public ISpeed
		{
		private:
			double speed;
			double 角度;
			double 角速度;
		public:

			/** 速度を大きくすると最大値が変化し、角速度により周期が変化する.*/
			Wave(double 速度, double 角速度, double 初角 = 0) :
				speed(速度),
				角速度(角速度),
				角度(初角)
			{}

			double Get() const override
			{
				return std::abs(std::sin(角度) * speed);
			}

			double Update() override
			{
				角度 += 角速度;
				return Get();
			}
		};

		/** 一定速度まで加速.*/
		/** \include Speed.h */
		class AccelLimit : public ISpeed
		{
		private:
			double speed;
			double 加速度;
			double 限界速度;
		public:

			/** 初期状態を設定.*/
			AccelLimit(double 初速, double 加速度, double 限界速度) :
				speed(初速),
				加速度(加速度),
				限界速度(限界速度)
			{}

			double Get() const  override
			{
				return speed;
			}

			double Update() override
			{
				speed += 加速度;
				if (speed > 限界速度 && 加速度 > 0) speed = 限界速度;
				if (speed < 限界速度 && 加速度 < 0) speed = 限界速度;
				return Get();
			}
		};
	}
}