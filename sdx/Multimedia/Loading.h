//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once

#include <Multimedia/SDX.h>
#include <functional>

namespace SDX
{
	/** リソースの非同期読み込み支援関数.*/
	/** Image,Font,Sound,Music,ImagePack,Filmで有効\n*/
	/** Loading::End()後は、全リソースの読み込みが終わるまでリソースの読み込み等を行ってはいけない*/
	/** 特にFont::DrawやDrawing::Fontで新しい文字を出すとたまにエラーが出るので注意が必要*/
	/** @todo Windows以外ではエラーが出る*/
	/** \include Loading.h*/
	class Loading
	{
		friend class Image;
		friend class ImagePack;
		friend class Font;
		friend class MixFont;
		friend class Sound;
		friend class Music;
		friend class Movie;
	private:
		Loading(void) = default;
		~Loading(void) = default;
		//void operator =(const Loading& src){}
		//Loading(const Loading& src){}

		static bool isLoading;
		static int loadingCount;
		static int succesCount;
		static std::mutex mtx;

		static std::vector<std::function<void(void)>> funcS;

	public:

		/** 非同期読み込みするResorceを登録開始.*/
		static void Start()
		{
			//Windowsのみ有効
#ifndef __WINDOWS__
			return;
#endif
			loadingCount = 0;
			succesCount = 0;
			isLoading = true;
		}

		/** 非同期読み込みするResorceの読込開始.*/
		static void End()
		{
			if ( !isLoading )
			{
				return;
			}

			isLoading = false;

			std::thread
			(
				[&]
				{
					for (auto it : funcS)
					{
						it();
						++succesCount;
					}
					funcS.clear();
				}
			).detach();
		}

		/** 読み込み中と読み込んだリソース数を取得.*/
		static int GetLoadingCount()
		{
			return loadingCount;
		}

		/** 読み込んだリソース数を取得.*/
		static int GetSuccesCount()
		{
			std::lock_guard<std::mutex> lock(mtx);
			return succesCount;
		}

		/** 非同期読み込み登録中かどうか.*/
		static bool IsLoading()
		{
			return isLoading;
		}

		/** 非同期読み込み処理に追加.*/
		static void AddLoading(std::function<void(void)> &&読み込み関数)
		{
			std::lock_guard<std::mutex> lock(mtx);
			funcS.push_back(読み込み関数);
			++loadingCount;
		}
	};
}