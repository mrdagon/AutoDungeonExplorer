//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Image.h>
#include <Multimedia/Loading.h>
#include <Tiled/GetTag.h>
#include <Multimedia/File.h>
#include <string>

namespace SDX
{
	/** 複数のImageをまとめるクラス.*/
	/** @todo リソース解放周り色々未実装*/
	/** \include ImagePack.h*/
	class ImagePack
	{
	protected:
		std::vector<Image*> imageS;//!< 保持するImage
		int widthMax = 0;//!< 最大幅
		int heightMax = 0;//!< 最大高さ
	public:
		ImagePack() = default;

		/** １つの画像を分割して読み込む.*/
		ImagePack(const char *ファイル名, int 総コマ数, int コマ割り横, int コマ割り縦)
		{
			ImagePack::Load(ファイル名, 総コマ数, コマ割り横, コマ割り縦);
		}

		/** 連番ファイルを一括して読み込む.*/
		/** ファイル名の後に三桁の連番が付いたファイルを連続して読み込む\n*/
		/**	例:「ファイル名***.拡張子」*/
		ImagePack(const char *ファイル名, const char *拡張子, int 総コマ数, const char* 書式 = "%03d.")
		{
			Load(ファイル名, 拡張子, 総コマ数, 書式);
		}

		/** １つの画像を分割して読み込む.*/
		/** 総コマ数=14,コマ割り横=4,コマ割り縦=4の場合\n*/
		/**	[ 0][ 1][ 2][ 3]\n*/
		/**	[ 4][ 5][ 6][ 7]\n*/
		/**	[ 8][ 9][10][11]\n*/
		/**	[12][13][  ][  ]\n*/
		/**	のように分割して、ImagePackのサイズは14になる */
		bool Load(const char *ファイル名, int 総コマ数, int コマ割り横, int コマ割り縦)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(ファイル名,総コマ数,コマ割り横,コマ割り縦); });
				return true;
			}

			int x = 0, y = 0, count = 0;
			Image image(ファイル名);

			const int width = image.GetWidth() / コマ割り横;
			const int height = image.GetHeight() / コマ割り縦;

			for (int a = 0; a < コマ割り縦; ++a)
			{
				x = 0;
				for (int b = 0; b < コマ割り横; ++b)
				{
					if (count >= 総コマ数) break;
					this->Add(new Image(image, { x, y, width, height }));
					x += width;
					count++;
				}
				y += height;
			}

			return true;
		}

		/** 連番ファイルを一括して読み込む.*/
		/** ファイル名の後に三桁の連番が付いたファイルを000から連続して読み込む\n*/
		/**	例:「ファイル名***.拡張子」*/
		bool Load(const char *ファイル名, const char *拡張子, int 総コマ数, const char* 書式 = "%03d.")
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(ファイル名, 拡張子 ,総コマ数, 書式); });
				return true;
			}

			for (int a = 0; a < 総コマ数; ++a)
			{
				char fileBuf[8];
				sprintf_s(fileBuf, 8, 書式, a);

				std::string fileName = ファイル名;
				fileName += fileBuf;
				fileName += 拡張子;

				this->Add(new Image(fileName.c_str()));
			}
			return true;
		}

		/** tmxファイルのタイルセット情報を元に画像を読み込む.*/
		bool LoadTmx(const char *tmxファイル名)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ LoadTmx(tmxファイル名); });
				return true;
			}


			if (imageS.size() != 0)
			{
				return false;
			}

			File file(tmxファイル名, FileMode::Read);
			if (file.GetFileMode() != FileMode::Read)
			{
				return false;
			}

			auto strS = file.GetLineS();//全文字読み込むのでわりと効率無視してる

			int tileW;
			int tileH;

			//0番目はgidで無視されるので空データを入れる	
			imageS.push_back(new Image());

			for (auto & str : strS)
			{
				if (str.find("<objectgroup") != std::string::npos)
				{
					//以降オブジェクト情報なので終了
					break;
				}
				else if (str.find("<tileset") != std::string::npos)
				{
					tileW = std::atoi(GetTag(str, "tilewidth=").c_str());
					tileH = std::atoi(GetTag(str, "tileheight=").c_str());
				}
				else if (str.find("<image width") != std::string::npos)
				{
					std::string sttt = GetTag(str, "source=");

					imageS.push_back(new Image(GetTag(str,"source=").c_str()) );
				}
				else if (str.find("<image source") != std::string::npos)
				{
					int w = std::atoi(GetTag(str, "width=").c_str()) / tileW;
					int h = std::atoi(GetTag(str, "height=").c_str()) / tileH;

					Load(GetTag(str, "source=").c_str(), w*h, w, h);
				}
			}
			
			return true;
		}

		/** Imageを末尾に追加.*/
		void Add(Image *追加イメージ)
		{
			imageS.push_back(追加イメージ);
			this->widthMax = std::max(this->widthMax, 追加イメージ->GetWidth());
			this->heightMax = std::max(this->heightMax, 追加イメージ->GetHeight());
		}
		/** Imageを末尾に追加.*/
		void Add(const char *ファイル名)
		{
			Add(new Image(ファイル名));
		}

		/** Imageをメモリから開放.*/
		virtual void Release()
		{
			for (auto it : imageS)
			{
				it->Release();
			}

			imageS.clear();
		}

		/** 要素数を取得.*/
		int GetSize() const
		{
			return (int)imageS.size();
		}

		/** 最大幅を取得.*/
		int GetWidth() const
		{
			return this->widthMax;
		}

		/** 最大高さを取得.*/
		int GetHeight() const
		{
			return this->heightMax;
		}
		
		/** 描画色をまとめて変更.*/
		void SetColor(const Color &描画色)
		{
			for (auto && it : imageS)
			{
				it->SetColor(描画色);
			}
		}

		/** 先頭からimageの幅を差分修正.*/
		/** BMPフォント用の画像を文字幅を調整する時に使う*/
		/** 分割読み込み時*/
		void AdjustWidth(std::vector<int> 幅)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{  AdjustWidth(幅); });
				return;
			}

			for (unsigned int a = 0; a < 幅.size();++a)
			{ 
				imageS[a]->part.w -= 幅[a];
			}
		}

		/** オペレータ.*/
		Image* operator[](int index)
		{
			return imageS[index];
		}

		/** オペレータ.*/
		Image* operator[](int index) const
		{
			return imageS[index];
		}

		/** イテレータ用.*/
		auto begin() ->decltype(imageS.begin())
		{
			return imageS.begin();
		}

		/** イテレータ用.*/
		auto end() ->decltype(imageS.end())
		{
			return imageS.end();
		}

		/** イテレータ用.*/
		auto begin() const ->decltype(imageS.begin())
		{
			return imageS.begin();
		}

		/** イテレータ用.*/
		auto end() const ->decltype(imageS.end())
		{
			return imageS.end();
		}


	};
}