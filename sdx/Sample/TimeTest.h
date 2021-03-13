//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <vector>

//コンテナ比較用のコードあれこれ
namespace SDX
{
	class IUnion
	{
	public:
		virtual ~IUnion(){}

		virtual int Get() = 0;
	};

	class Int :public IUnion
	{
		int num;
	public:
		int Get() {	return 1; }
	};

	class Double :public IUnion
	{
		double num;
	public:
		int Get() { return 2; }
	};

	class Float :public IUnion
	{
		float num;
	public:
		int Get() { return 3; }
	};

	/**共用体サンプル.*/
	/**メモリプール使う方が基本的に楽*/
	class SampleUnion
	{
#define U_TYPE(name) mutable name uni_##name; Union(const name &shot , Type& type ) : uni_##name(shot) { type = Type::name; }
#define U_DEST(name) case Type::name : uni.uni_##name.~name();break;
#define U_CONST(name) case Type::name : new(&uni.uni_##name) name(src.uni.uni_##name);break;
#define U_GET(name) case Type::name: return &uni.uni_##name;
	public:
		//列挙子名 = 型名にする
		enum class Type
		{
			Int,Double,Float
		} typeNo;

		union Union
		{
		public:
			U_TYPE(Int)
			U_TYPE(Double)
			U_TYPE(Float)

			Union() {}
			~Union() {};
		}uni;

		void Destoract()
		{
			switch (typeNo)
			{
				U_DEST(Int)
				U_DEST(Double)
				U_DEST(Float)
			default:break;
			}
		}

		void Constract(const SampleUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
				U_CONST(Int)
				U_CONST(Double)
			default:break;
			}
		}

		IUnion* Get() const
		{
			switch (typeNo)
			{
				U_GET(Int)
				U_GET(Double)
			}
			return nullptr;
		}

		//以下はunionの型数によらない
		template< class T>
		SampleUnion(const T &src) : uni(src, typeNo) {}

		SampleUnion(const SampleUnion& src)
		{
			Constract(src);
		}
		//同じ型になる場合も再構成する
		SampleUnion& operator=(const SampleUnion& src)
		{
			Destoract();
			Constract(src);
			return *this;
		}
		~SampleUnion() { Destoract(); }
#undef U_TYPE
#undef U_DEST
#undef U_CONST
#undef U_GET
	};

	/**共用体サンプルその2.*/
	/**メモリプール使う方が効率は良い*/
	template<class TInterface,class T0, class T1>
	class TempUnion
	{
	public:
		enum class Type
		{
			T0,
			T1
		} typeNo;

		union Union
		{
		public:
			mutable T0 value_0; Union(const T0 &t0, Type& type) : value_0(t0){ type = Type::T0; }
			mutable T1 value_1; Union(const T1 &t1, Type& type) : value_1(t1){ type = Type::T1; }
			Union() {}
			~Union() {};
		}uni;


		void Constract(const TempUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
			case Type::T0: new(&uni.value_0) T0(src.uni.value_0); break;
			case Type::T1: new(&uni.value_1) T1(src.uni.value_1); break;
			default:break;
			}
		}

		void Destoract()
		{
			switch (typeNo)
			{
			case Type::T0: uni.value_0.~T0(); break;
			case Type::T1: uni.value_1.~T1(); break;
			default:break;
			}
		}


		TInterface* Get() const
		{
			switch (typeNo)
			{
				case Type::T0: return &uni.value_0;
				case Type::T1: return &uni.value_1;
			}
			return nullptr;
		}

		//以下はunionの型数によらない
		template< class T>
		TempUnion(const T &src) : uni(src, typeNo) {}

		TempUnion(const TempUnion& src)
		{
			Constract(src);
		}
		//同じ型になる場合はコピー、それ以外は再確保
		TempUnion& operator=(const TempUnion& src)
		{
			if (typeNo == src.typeNo )
			{
				switch (typeNo) {
				case Type::T0:
					uni.value_0 = src.uni.value_0;
					break;
				case Type::T1:
					uni.value_1 = src.uni.value_1;
					break;
				default:
					break;
				}
				return *this;
			}

			Destoract();
			Constract(src);
			return *this;
		}
		~TempUnion() { Destoract(); }
	};

	/**共用体サンプルその3.*/
	/**なんか中途半端*/
	template<class TInterface, class T0, class T1>
	class AnyUnion
	{
	public:
		enum class Type
		{
			T0,
			T1
		} typeNo;

		TInterface* ptr;

		char buff[100];//placement new用の領域

		void Constract(const AnyUnion &src)
		{
			typeNo = src.typeNo;

			switch (typeNo)
			{
			case Type::T0: ptr = new(buff) T0(src.uni.value_0); break;
			case Type::T1: ptr = new(buff) T1(src.uni.value_1); break;
			default:break;
			}
		}

		void Destoract()
		{
			switch (typeNo)
			{
			case Type::T0: (T0)buff->~T0(); break;
			case Type::T1: (T1)buff->~T1(); break;
			default:break;
			}
		}

		TInterface* Get() const
		{
			return ptr;
		}

		//以下はunionの型数によらない
		template< class T>
		AnyUnion(const T &src , Type type)
		{
			typeNo = type;
			ptr = new(buff) T(src); break;
		}

		AnyUnion(const TempUnion& src)
		{
			Constract(src);
		}
		//同じ型になる場合も再確保
		AnyUnion& operator=(const AnyUnion& src)
		{
			Destoract();
			Constract(src);
			return *this;
		}
		~AnyUnion() { Destoract(); }
	};
}