//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Utility/EnumArray.h>

namespace SDX
{
	/** ファイルの読込書込モード.*/
	enum class FileMode
	{
		Read,//!< 読込のみ
		Write,//!< 書込のみ
		Add,//!< 書込時、末尾に追加
		None,//!< 開かれていない
	};

	/** Androidでの保存先.*/
	enum class SaveMode
	{
		Asset,//!< 各アプリケーションのフォルダ
		Internal,//!< 内部ストレージ
		External,//!< 外部ストレージ(SDカード)
	};

	/** 入出力可能なテキストかバイナリファイルを表すクラス.*/
	/**@todo 配列の保存と読み込みの仕様が分かりにくい？*/
	/** \include File.h*/
	class File
	{
	private:
		SDL_RWops *handle = nullptr;//!<
		bool canRead;//!<
		bool canWrite;//!<
		bool canAdd;//!<
		bool isBinary;//!<
		std::string fileName;//!<
	public:

		/** ファイル名とモードを指定して、ファイルを開く.*/
		File(const char* ファイル名, FileMode 読み書きモード, bool バイナリファイル = false, SaveMode Androidの保存先 = SaveMode::Asset)
		{
			File::Open(ファイル名, 読み書きモード, バイナリファイル, Androidの保存先);
		}

		~File()
		{
			Close();
		}

		/** ファイル名とモードを指定して、ファイルを開く.*/
		bool Open(const char* ファイル名, FileMode 読み書きモード, bool バイナリファイル = false, SaveMode Androidの保存先 = SaveMode::Asset)
		{

#ifdef __ANDROID__
			switch (Androidの保存先)
			{
			case SaveMode::Asset:
				fileName = ファイル名;
				break;
			case SaveMode::External:
				fileName = SDL_AndroidGetExternalStoragePath();
				fileName += ファイル名;
				break;
			case SaveMode::Internal:
				fileName = SDL_AndroidGetInternalStoragePath();
				fileName += ファイル名;
				break;
			}
#else
	#ifdef __WINDOWS__
			fileName = ファイル名;
	#else
			fileName = SDL_GetBasePath();
			fileName += "/";
			fileName += ファイル名;
	#endif
#endif

			isBinary = バイナリファイル;

			switch (読み書きモード)
			{
			case FileMode::Read:
				if (isBinary){ handle = SDL_RWFromFile(fileName.c_str(), "rb"); }
				else{ handle = SDL_RWFromFile(fileName.c_str(), "r"); }

				canRead = true;
				canWrite = false;
				canAdd = false;
				break;
			case FileMode::Write:
				if (isBinary){ handle = SDL_RWFromFile(fileName.c_str(), "wb"); }
				else{ handle = SDL_RWFromFile(fileName.c_str(), "w"); }
				canWrite = true;
				canRead = false;
				canAdd = false;
				break;
			case FileMode::Add:
				if (isBinary){ handle = SDL_RWFromFile(fileName.c_str(), "ab"); }
				else{ handle = SDL_RWFromFile(fileName.c_str(), "a"); }
				canWrite = true;
				canAdd = true;
				canRead = false;
				break;
			case FileMode::None:
				break;
			}

			if (handle == nullptr)
			{
				canRead = false;
				canWrite = false;
				canAdd = false;
				return false;
			}

			return true;
		}

		/** ファイルを閉じる.*/
		void Close()
		{
			if (handle)
			{
				SDL_RWclose(handle);
				handle = nullptr;
			}
			canRead = false;
			canWrite = false;
			canAdd = false;
		}

		/** ファイルモードを取得.*/
		FileMode GetFileMode()
		{
			if (this->canAdd)  return FileMode::Add;
			if (this->canWrite) return FileMode::Write;
			if (this->canRead) return FileMode::Read;
			return FileMode::None;
		}

		/** ファイル名を取得.*/
		const char* GetFileName()
		{
			return this->fileName.c_str();
		}

		template< class T> 
		/** データを読み込む.*/	
		/** FileMode::Readの場合成功*/
		bool Read(T &読み込み先変数)
		{
			if (!canRead) return false;

			SDL_RWread(handle, &読み込み先変数, sizeof(読み込み先変数), 1);

			return true;
		}

		template < class T >
		/** 可変長配列を読み込む.*/
		/** FileMode::Readの場合成功*/
		/** 要素数を最初に読み込む*/
		bool Read(std::vector<T> &読み込み元配列)
		{
			if (!canRead) return false;

			int 要素数;
			SDL_RWread(handle, &要素数, sizeof(int), 1);

			読み込み元配列.clear();

			for (int a = 0; a < 要素数; ++a)
			{
				T 値;
				SDL_RWread(handle, &値, sizeof(T), 1);
				読み込み元配列.push_back(値);
			}

			return true;
		}

		/** 文字列を読み込む.*/
		/** 1byte目が文字数、残り部分が文字データになっていれば読み込める*/
		/** FileMode::Readの場合成功*/
		bool Read(std::string &読み込み先変数)
		{
			if (!canRead) return false;

			int 文字数 = 0;
			SDL_RWread(handle, &文字数, sizeof(int), 1);

			if (文字数 == 0)
			{
				読み込み先変数 = "";
				return true;
			}

			読み込み先変数.resize(文字数);
			SDL_RWread(handle, (char*)読み込み先変数.c_str(), 文字数, 1);

			return true;
		}

		template< class T > 
		/** データを読み込む.*/
		bool Read(T *読み込み先配列, int 要素数)
		{
			if (!canRead) return false;

			for (int a = 0; a < 要素数; ++a)
			{
				SDL_RWread(handle, &読み込み先配列[a], sizeof(T), 1);
			}

			return true;
		}

		template <class TSaveType, class TOutput>
		/**型変換をしつつ配列に読み込む.*/
		/**ファイルにはint型で保存してあって、double型の値に代入したい時等に使う.*/
		bool Read(TOutput *読み込み先配列, int 要素数, int 分母)
		{
			if (!canRead) return false;

			TSaveType buff;

			for (int a = 0; a < 要素数; ++a)
			{
				SDL_RWread(handle, &buff, sizeof(TSaveType), 1);
				読み込み先配列[a] = TOutput(buff) / 分母;
			}

			return true;
		}
		
		template< class TSaveType, class TOutput>
		/**型変換をしつつ読み込む.*/
		bool Read(TOutput &読み込み先変数)
		{
			if (!canRead) return false;

			TSaveType buff;
			SDL_RWread(handle, &buff, sizeof(TSaveType), 1);

			読み込み先変数 = TOutput(buff);

			return true;
		}

		/*
		template< class TType , class TEnum >
		bool Read(EnumArray<TType,TEnum>& 読み込み先配列 )
		{
			if (!canRead) return false;

			for (int a = 0; a < TEnum::COUNT ; ++a)
			{
				SDL_RWread(handle, &読み込み先配列[a], sizeof(TType), 1);
			}

			return true;
		}
		*/

		template< class T> 
		/** データを書き込む.*/
		/** FileModeがWriteかAddの場合成功。\n*/
		/**	書込元変数をファイルに書き込む。*/	
		bool Write(T& 書込み元変数)
		{
			if (!canWrite) return false;

			SDL_RWwrite(handle, &書込み元変数, sizeof(書込み元変数), 1);

			return canWrite;
		}
		
		/** 文字列を書き込む.*/
		/** FileModeがWriteかAddの場合成功。\n*/
		/**	書込元変数をファイルに書き込む。*/
		/** 文字列の長さを文字列自身の前に書き込むかを選択出来る*/
		bool Write(const std::string &書込み元変数 , bool is文字数 = true)
		{
			if (!canWrite) return false;

			const int 文字数 = (int)書込み元変数.size();

			if (is文字数)
			{
				SDL_RWwrite(handle, &文字数, sizeof(int), 1);
			}

			if (文字数 == 0){ return canWrite; }

			SDL_RWwrite(handle, 書込み元変数.c_str(), 文字数, 1);

			return canWrite;
		}

		bool Write(std::string &書込み元変数, bool is文字数 = true)
		{
			if (!canWrite) return false;

			const int 文字数 = (int)書込み元変数.size();

			if (is文字数)
			{
				SDL_RWwrite(handle, &文字数, sizeof(int), 1);
			}

			if (文字数 == 0){ return canWrite; }

			SDL_RWwrite(handle, 書込み元変数.c_str(), 文字数, 1);

			return canWrite;
		}

		template < class T >
		/** 可変長配列を読み込む.*/
		/** FileMode::Wirteの場合成功*/
		/** 要素数を最初に書き込む*/
		bool Write(std::vector<T> &書込み元配列)
		{
			if (!canWrite) return false;

			int 要素数 = 書込み元配列.size();
			SDL_RWwrite(handle, &要素数, sizeof(int), 1);

			for (int a = 0; a < 要素数; ++a)
			{
				SDL_RWwrite(handle, &書込み元配列[a], sizeof(T), 1);
			}

			return true;
		}

		template <class TSaveType, class TInput>
		/**型変換をして書き込む.*/
		/**double型をfloatに変換して保存する時用*/
		bool Write(TInput *書き込み元配列, int 要素数)
		{
			if (!canWrite) return false;

			for (int a = 0; a < 要素数; ++a)
			{
				TSaveType buff = (TSaveType)書き込み元配列[a];

				SDL_RWwrite(handle, &buff, sizeof(TSaveType), 1);
			}

			return true;
		}

		template< class T>
		/** 変数を読み書きする.*/
		/** FileModeがReadの場合Read、WriteかAddの場合Writeを行う*/
		bool ReadWrite(T &読み書き変数)
		{
			if (canRead)
			{
				return Read(読み書き変数);
			}
			else if (canWrite){
				return Write(読み書き変数);
			}
			return false;
		}

		template< class T>
		/** 配列に読み書きする.*/
		/** FileModeがReadの場合Read、WriteかAddの場合Writeを行う*/
		bool ReadWrite(T *読み書き変数 , int 要素数)
		{
			if (canRead)
			{
				return Read(読み書き変数 , 要素数);
			}
			else if (canWrite){
				return Write(読み書き変数);
			}
			return false;
		}

		/** 改行付きの文字列を一行書き込む.*/
		bool AddLine(VariadicStream 文字列)
		{
			if (!canWrite) return false;

			文字列.StringS[0] += "\r\n";

			const int 文字数 = (int)文字列.StringS[0].size();

			if (文字数 == 0)
			{
				return false;
			}
			SDL_RWwrite(handle, 文字列.StringS[0].c_str(), 文字数, 1);

			return true;
		}

		/** ファイルを改行区切りで一括して読み込む.*/
		std::vector<std::string> GetLineS()
		{
			std::vector<std::string> lineS;

			if (canRead)
			{
				std::string all;
				unsigned int fileSize = (unsigned int)handle->size(handle);
				all.resize(fileSize);
				SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

				std::string buf;
				std::istringstream iss(all);
				int numA,numB;

				while (std::getline(iss, buf, '\n'))
				{
					numA = (int)buf.find_first_of('\r');
					numB = (int)buf.find_first_of('\n');
					if (numA < numB){ numA = numB; };

					if (numA != std::string::npos)
					{
						buf = buf.substr(0, numA);
					}

					lineS.push_back(buf.substr());
				}
			}
			return lineS;
		}

		/** カンマ区切りのCSVファイルを配列に文字列として一括読込.*/
		std::vector<std::string> GetCsvToString()
		{
			std::vector<std::string> lineS;

			if (canRead)
			{
				std::string all;
				unsigned int fileSize = (unsigned int)handle->size(handle);
				all.resize(fileSize);
				SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

				int lineNo = 0;
				std::string buf;
				std::string buf2;
				std::istringstream iss(all);

				while (std::getline(iss, buf, '\n'))
				{
					//\rがあれば消す
					if (buf.find("\r") != std::string::npos)
					{
						buf.replace(buf.find("\r"), 1, "");
					}

					std::istringstream iss2(buf);
					while (std::getline(iss2, buf2, ','))
					{
						lineS.push_back(buf2);
					}
					++lineNo;
				}
			}
			return lineS;
		}

		/** カンマ区切りのCSVファイルを二次元配列に文字列として一括読込.*/
		std::vector<std::vector<std::string>> GetCsvToString2()
		{
			std::vector<std::vector<std::string>> lineS;

			if (canRead)
			{
				std::string all;
				unsigned int fileSize = (unsigned int)handle->size(handle);
				all.resize(fileSize);
				SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

				int lineNo = 0;
				std::string buf;
				std::string buf2;
				std::istringstream iss(all);

				while (std::getline(iss, buf, '\n'))
				{
					//\rがあれば消す
					if (buf.find("\r") != std::string::npos)
					{
						buf.replace(buf.find("\r"), 1, "");
					}
					
					std::istringstream iss2(buf);					
					lineS.push_back(std::vector<std::string>());

					while (std::getline(iss2, buf2, ','))
					{
						lineS[lineNo].push_back(buf2);
					}
					++lineNo;
				}
			}
			return lineS;
		}

		/** カンマ区切りのCSVファイルを配列に整数として一括読込.*/
		std::vector<int> GetCsvToInt()
		{
			std::vector<int> lineS;

			if (canRead)
			{
				std::string all;
				unsigned int fileSize = (unsigned int)handle->size(handle);
				all.resize(fileSize);
				SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

				int lineNo = 0;
				std::string buf;
				std::string buf2;
				std::istringstream iss(all);

				while (std::getline(iss, buf, '\n'))
				{
					std::istringstream iss2(buf);

					while (std::getline(iss2, buf2, ','))
					{
						lineS.push_back(atoi(buf2.c_str()));
					}
					++lineNo;
				}
			}
			return lineS;
		}

		/** カンマ区切りのCSVファイルを二次元配列に整数として一括読込.*/
		std::vector<std::vector<int>> GetCsvToInt2()
		{
			std::vector<std::vector<int>> lineS;

			if (canRead)
			{
				std::string all;
				unsigned int fileSize = (unsigned int)handle->size(handle);
				all.resize(fileSize);
				SDL_RWread(handle, (char*)all.c_str(), fileSize, 1);

				int lineNo = 0;
				std::string buf;
				std::string buf2;
				std::istringstream iss(all);

				while (std::getline(iss, buf, '\n'))
				{
					std::istringstream iss2(buf);
					lineS.push_back(std::vector<int>());

					while (std::getline(iss2, buf2, ','))
					{
						lineS[lineNo].push_back(atoi(buf2.c_str()));
					}
					++lineNo;
				}
			}
			return lineS;
		}

		/** ファイルの終端判定.*/
		bool CheckEOF()
		{
			return (SDL_RWtell(handle) == RW_SEEK_END);
		}
	};
}