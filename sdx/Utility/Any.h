//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>

namespace SDX
{
	template< class TBase, int MaxSize >
	/*静的にメモリを確保する動的型.*/
	/*共通基底クラスと最大型サイズをテンプレートに入れる*/
	/*Holderとか実装してない分、メモリ効率は良い*/
	class Any
	{
	private:
		char buff[MaxSize];

	public:
		template < typename T >
		Any(const T& src)
		{
			static_assert(sizeof(T) <= MaxSize, "Any<> MaxSize Over");
			//継承チェック
			//static_assert(std::is_base_of<TBase, T>(), "KEISYOU SITENAI");
			new(buff) T(src);
		}

		~Any()
		{
			((TBase*)this)->~TBase();
		}

		Any& operator = (Any const & src)
		{
			if (this != & src)
			{
				for (int a = 0;a < MaxSize;++a)
				{
					buff[a] = src.buff[a];
				}
			}
			return *this;
		}

		template < typename T >
		Any& operator = (const T& src)
		{
			static_assert(sizeof(T) <= MaxSize, "Any<> MaxSize Over");
			*this = new(buff) T(src);
			return *this;
		}

		TBase* operator->()
		{
			return (TBase*)this;
		}
	};

	template< class TBase , int MaxSize >
	/*静的にメモリを確保する動的型.*/
	/*共通スーパークラスと最大型サイズをテンプレートに入れる*/
	/*Holderとかの分も考えて、MaxSizeを指定する必要がありメモリ効率が下がる*/
	/*色々安全にした分、メモリ効率が若干悪く、速度も若干遅い*/
	class SafeAny
	{
	private:
		char buff[MaxSize];

		class IHolder
		{
		public:
			virtual ~IHolder() {}
			virtual IHolder * clone(char* buff) = 0;
			virtual TBase* Get(void) = 0;
		};

		IHolder* content;

		template < typename T >
		class Holder : public IHolder
		{
		public:

			explicit Holder(T const & src) : 
				held(src)
			{}


			explicit Holder(T const && src) :
				held(src)
			{}

			virtual IHolder *clone( char* buff )
			{
				return new(buff) Holder(held);
			}

			TBase* Get()
			{
				return &held;
			}

		private:
			T held;
		};
		
	public:
		template < typename T >
		SafeAny(T const & src) :
			content(new(buff) Holder<T>(src))
		{
			static_assert(sizeof(Holder<T>) <= MaxSize, "SafeAny<> MaxSize Over");
		}

		SafeAny(SafeAny const & other) :
			content(other.content ? other.content->clone(buff) : 0)
		{ }

		~SafeAny()
		{
			content->~IHolder();
		}

		SafeAny& operator = (SafeAny const & src)
		{
			if (this != &src)
			{
				content = src.content->clone(buff);
			}
			return *this;
		}

		template < typename T >
		SafeAny& operator = ( T const & src)
		{
			static_assert(sizeof(Holder<T>) <= MaxSize, "SafeAny<> MaxSize Over");
			content = new(buff) Holder<T>(src);
			return *this;
		}

		TBase* operator->()
		{
			content->Get();
		}

	};
}