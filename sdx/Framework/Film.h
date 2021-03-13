//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Image.h>
#include <Framework/ImagePack.h>

namespace SDX
{
	/** 次コマの移動先.*/
	/** 0以上の場合は、そのコマにジャンプする*/
	enum class NextFrame
	{
		Normal = -10000,//!< 次のコマに進む
		ToFront,//!< コマの進む向きをプラスにしてから進む
		ToBack,//!< コマの進む向きをマイナスにしてから進む
		End,//!< このコマでアニメーションを停止する
	};

	/** アニメの再生方法.*/
	enum class FilmType
	{
		Normal,//!< 最後まで再生するとまた最初からループ再生
		Reverse,//!< 最後まで再生すると、再生方向を反転
		End//!< 最終フレームで再生を停止
	};

	/** ImagePackにコマ毎の再生時間を追加したクラス.*/
	/** @todo リソース解放周り色々未実装*/
	/** \include Anime.h */
	class Film : public ImagePack
	{
		friend class Anime;
	private:
		std::vector<unsigned int> times;//!< コマのフレーム数
		std::vector<int> nexts;//!< 各コマの次フレーム
	public:
		Film() = default;

		/** 画像ファイルを分割してメモリへ読み込む.*/
		Film(const char *ファイル名, int 総コマ数, int コマ割り横, int コマ割り縦, int １コマの再生時間 = 1) :
			ImagePack(ファイル名, 総コマ数, コマ割り横, コマ割り縦)
		{
			for (int a = 0; a < 総コマ数; ++a)
			{
				times.push_back(１コマの再生時間);
				nexts.push_back((int)NextFrame::Normal);
			}
		}

		/** 連番ファイルを一括して読み込む.*/
		Film(const char* ファイル名, const char *拡張子, int 総コマ数, int １コマの再生時間 = 1, const char* 書式 = "%03d.")
		{
			Load(ファイル名, 拡張子, 総コマ数, １コマの再生時間 ,書式);
		}

		/** 画像ファイルを分割してメモリへ読み込む.*/
		bool Load(const char *ファイル名, int 総コマ数, int コマ割り横, int コマ割り縦, int １コマの再生時間 = 1)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ Load(ファイル名, 総コマ数, コマ割り横, コマ割り縦, １コマの再生時間); });
				return true;
			}

			if (!ImagePack::Load(ファイル名, 総コマ数, コマ割り横, コマ割り縦)) { return false; }

			for (int a = 0; a < 総コマ数; ++a)
			{
				times.push_back(１コマの再生時間);
				nexts.push_back((int)NextFrame::Normal);
			}

			return true;
		}

		/** 連番ファイルを一括して読み込む.*/
		bool Load(const char* ファイル名, const char *拡張子, int 総コマ数, int １コマの再生時間 = 1, const char* 書式 = "%03d.")
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ Load(ファイル名, 拡張子, 総コマ数, １コマの再生時間 , 書式); });
				return true;
			}

			for (int a = 0; a < 総コマ数; ++a)
			{
				char fileBuf[8];
				sprintf_s(fileBuf, 8, 書式, a);
				std::string fileName = ファイル名;
				fileName += fileBuf;
				fileName += 拡張子;

				this->Add(new Image(fileName.c_str()), １コマの再生時間);
			}

			return true;
		}

		/** 末尾にImageを追加する.*/
		void Add(Image *追加イメージ, int 再生フレーム数 = 1)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ Add(追加イメージ, 再生フレーム数); });
				return;
			}

			ImagePack::Add(追加イメージ);
			times.push_back(再生フレーム数);
			nexts.push_back((int)NextFrame::Normal);
		}
		/** 末尾にImageを追加する.*/
		void Add(const char *ファイル名, int 再生フレーム数 = 1)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ Add(ファイル名, 再生フレーム数); });
				return;
			}

			Add(new Image(ファイル名), 再生フレーム数);
		}

		/** Imageを開放し初期化する.*/
		void Release() override
		{
			ImagePack::Release();
			times.clear();
			nexts.clear();
		}

		/** 各コマのフレーム数を設定する.*/
		void SetFrameTime(const std::vector<int> &フレーム時間)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ SetFrameTime(フレーム時間); });
				return;
			}

			for (unsigned int a = 0; a < times.size(); ++a)
			{
				times[a] = フレーム時間[a];
			}
		}

		/** 全体の再生方法を指定する.*/
		/** 初期は全コマNextFrame*/
		void SetType(FilmType 再生方法)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{SetType(再生方法); });
				return;
			}

			switch (再生方法)
			{
			case FilmType::Normal:
				nexts[nexts.size() - 1] = (int)NextFrame::Normal;
				break;
			case FilmType::Reverse:
				nexts[0] = (int)NextFrame::ToFront;
				nexts[nexts.size() - 1] = (int)NextFrame::ToBack;
				break;
			case FilmType::End:
				nexts[nexts.size() - 1] = (int)NextFrame::End;
				break;
			}
		}

		/** 指定コマの次フレームを設定する.*/
		/** 初期は全コマNextFrame*/
		void SetType(int コマ番号, int 次フレーム)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{nexts[コマ番号] = 次フレーム; });
				return;
			}

			nexts[コマ番号] = 次フレーム;
		}

		/** 指定コマの次フレームを設定する.*/
		/** 初期は全コマNextFrame*/
		void SetType(int コマ番号, NextFrame 次フレーム)
		{
			if (Loading::IsLoading())
			{
				Loading::AddLoading([=]{ nexts[コマ番号] = (int)次フレーム; });
				return;
			}

			nexts[コマ番号] = (int)次フレーム;
		}

		/** 全コマの合計フレーム時間を返す.*/
		int GetAnimeTime() const
		{
			int totalTime = 0;

			for (auto it : times)
			{
				totalTime += it;
			}

			return totalTime;
		}
	};
}