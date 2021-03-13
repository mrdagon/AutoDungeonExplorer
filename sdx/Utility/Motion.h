//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
namespace SDX
{
	namespace MOTION
	{
		
		//コピペ用ひな形
		/*
		template <class TSpeed>
		class Base : public IMotion
		{
		private:
			TSpeed speed;
		public:
		Base(const TSpeed &速度):
		speed(速度)
		{}

		void Update(TShape* 移動対象) override
		{
		移動対象
		}
		};
		*/


		/**その場所で停止.*/
		class Stop : public IMotion
		{
		public:
			Stop()
			{}
		};

		template <class TSpeed>
		/**前方に移動.*/
		/** \include Motion.h */
		class ToFront : public IMotion
		{
		private:
			TSpeed speed;
		public:

			/** 速度を指定.*/
			ToFront(const TSpeed &速度) :
				speed(速度)
			{}

			bool Update(IPosition* 移動対象) override
			{
				移動対象->MoveA(speed.Update(), 移動対象->GetAngle());

				return true;
			}
		};

		template <class TSpeed>
		/**範囲内で跳ね返る.*/
		/** \include Motion.h */
		class Bound : public IMotion
		{
		private:
			TSpeed speed;
			double 進行方向;
			Rect 移動範囲;
		public:

			/** 速度と移動範囲、最初の移動方向を指定.*/
			Bound(const TSpeed &速度, const Rect& 移動範囲, double 進行方向) :
				speed(速度),
				移動範囲(移動範囲),
				進行方向(進行方向)
			{}

			bool Update(IPosition* 移動対象) override
			{
				//範囲外にいる
				if (移動対象->GetX() < 移動範囲.GetLeft())
				{
					if (進行方向 > PAI / 2 && 進行方向 < PAI * 3 / 2)
					{
						進行方向 = -PAI - 進行方向;
					}
				}

				if (移動対象->GetX() > 移動範囲.GetRight())
				{
					if (進行方向 < PAI / 2 || 進行方向 > PAI * 3 / 2)
					{
						進行方向 = PAI - 進行方向;
					}
				}
				else if (移動対象->GetY() < 移動範囲.GetTop())
				{
					if (進行方向 > PAI)
					{
						進行方向 = PAI * 2 - 進行方向;
					}
				}
				else if (移動対象->GetY() > 移動範囲.GetBottom())
				{
					if (進行方向 < PAI)
					{
						進行方向 = -進行方向;
					}
				}

				if (進行方向 < 0) 進行方向 += PAI * 2;
				if (進行方向 > PAI * 2) 進行方向 -= PAI * 2;

				移動対象->MoveA(speed.Update(), 進行方向);

				return true;
			}
		};

		template <class TSpeed>
		/**目標座標に移動.*/
		/** \include Motion.h */
		class ToPoint : public IMotion
		{
		private:
			TSpeed speed;
			Point 目標座標;
		public:
			/** コンストラクタ.*/
			ToPoint(const TSpeed &速度, const Point& 目標座標) :
				speed(速度),
				目標座標(目標座標)
			{}

			bool Update(IPosition* 移動対象) override
			{
				//移動対象
				const double nowSpeed = speed.Update();
				const double lx = 目標座標.GetX() - 移動対象->GetX();
				const double ly = 目標座標.GetY() - 移動対象->GetY();

				if (lx * lx + ly * ly <= nowSpeed * nowSpeed)
				{
					移動対象->SetPos(目標座標.GetX(), 目標座標.GetY());
					return false;
				}
				else
				{
					const double angle = atan2(ly, lx);
					移動対象->MoveA(nowSpeed, angle);
				}

				return true;
			}
		};

		template <class TSpeed>
		/**円周上を移動.*/
		/** \include Motion.h */
		class Orbit : public IMotion
		{
		private:
			TSpeed speed;
			Point 軌道中心;
			double 半径X;
			double 半径Y;
			double 角度;
			double 前移動量X;
			double 前移動量Y;
		public:

			/** コンストラクタ.*/
			Orbit(const TSpeed &角速度 , double 半径X , double 半径Y , double 初期進行方向 = 0.0) :
				speed(角速度),
				半径X(半径X),
				半径Y(半径Y),
				角度(初期進行方向 - PAI / 2),
				前移動量X(cos(初期進行方向 - PAI/2) * 半径X),
				前移動量Y(sin(初期進行方向 - PAI/2) * 半径Y)
			{}

			bool Update(IPosition* 移動対象) override
			{
				//移動対象
				角度 += speed.Update();

				const double nextX = cos(角度) * 半径X;
				const double nextY = sin(角度) * 半径Y;

				移動対象->Move(nextX - 前移動量X, nextY - 前移動量Y);

				前移動量X = nextX;
				前移動量Y = nextY;

				return true;
			}
		};

		/**範囲内で振動.*/
		/** \include Motion.h */
		class  Vibrate : public IMotion
		{
		private:
			double 最大振れ幅;
			double 移動X = 0;
			double 移動Y = 0;
		public:

			/** コンストラクタ.*/
			Vibrate(double 最大振れ幅) :
				最大振れ幅(最大振れ幅)
			{}

			bool Update(IPosition* 移動対象) override
			{
				double randX = Rand::Get(-最大振れ幅, 最大振れ幅);
				double randY = Rand::Get(-最大振れ幅, 最大振れ幅);
				移動対象->Move(randX-移動X, randY-移動Y);				
				移動X = randX;
				移動Y = randY;

				return true;
			}
		};
	}
}