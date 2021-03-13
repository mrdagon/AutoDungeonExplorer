//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/ISprite.h>
#include <Framework/Anime.h>

namespace SDX
{
	/** Imageスプライト.*/
	/** \include Model.h*/
	class SpImage : public ISprite
	{
	private:
		const Image *image;//!<

	public:
		/** コンストラクタ.*/
		SpImage(const Image *描画Image) :
			image(描画Image)
		{}

		void Draw(const IShape &座標) const override
		{
			const Point pos = { 座標.GetX() + gap.x, 座標.GetY() + gap.x };
			const Point center = { axis.x + image->GetHeight() / 2, axis.y + image->GetHeight() / 2 };
			image->DrawRotateAxis(pos, center, zoomX, zoomY, angle, isTurn);
		}
	};

	/** ImagePackスプライト.*/
	/** \include Model.h*/
	class SpImageS : public ISprite
	{
	private:
		const ImagePack *imageS;//!<
		int index = 0;//!<
	public:

		/** コンストラクタ.*/
		SpImageS(const ImagePack *描画ImagePack) :
			imageS(描画ImagePack)
		{}

		/** 表示するindexの切り替え.*/
		void SetIndex(int コマ番号)
		{
			index = コマ番号;
		}

		/** 現在のindexを取得.*/
		int GetIndex()
		{
			return index;
		}

		void Draw(const IShape &座標) const override
		{
			const auto image = imageS->operator[](index);

			const Point pos = { 座標.GetX() + gap.x, 座標.GetY() + gap.y };
			const Point center = { axis.x + image->GetHeight() / 2, axis.y + image->GetHeight() / 2 };

			image->DrawRotateAxis(pos, center, zoomX, zoomY, angle, isTurn);
		}
	};

	/** Animeスプライト.*/
	/** \include Model.h*/
	class SpAnime : public ISprite
	{
	private:
		const Film *film;//!<
		Anime anime;//!<
		double aniSpeed;//!<

	public:
		/** コンストラクタ.*/
		SpAnime(const Film *再生対象, double 再生速度 = 1) :
			film(再生対象),
			anime(再生対象),
			aniSpeed(再生速度)
		{}

		/** アニメの更新.*/
		void Update() override
		{
			anime.Update(aniSpeed);
		}

		void Draw(const IShape &座標) const override
		{
			const Point pos = { 座標.GetX() + gap.x, 座標.GetY() + gap.y };
			const Point center = { axis.x + film->GetHeight() / 2, axis.y + film->GetHeight() / 2 };

			anime.DrawRotateAxis(pos, center, zoomX, zoomY, angle, isTurn);
		}
	};

	/** Fontスプライト.*/
	/** \include Model.h*/
	class SpFont : public ISprite
	{
	private:
		const IFont *font;//!<
		std::string str;//!<

	public:
		/**コンストラクタ.*/
		SpFont(const IFont *フォント, const char* 描画する文字列) :
			font(フォント),
			str(描画する文字列)
		{}

		void Draw(const IShape &座標) const override
		{
			font->DrawRotate({ 座標.GetX() + gap.x, 座標.GetY() + gap.y }, zoomX, angle, color, str, isTurn);

			//font->DrawExtend({ 座標.GetX() + gap.x, 座標.GetY() + gap.y }, zoomX, zoomY, color, str );
		}

		/**描画する文字列を変更.*/
		void SetText(const char* 表示する文字)
		{
			str = 表示する文字;
		}
	};

	/** IFrameスプライト.*/
	/** \include Model.h*/
	class SpFrame : public ISprite
	{
	private:
		const IFrame *bmpFrame;//!<

	public:
		/**コンストラクタ.*/
		SpFrame(const IFrame *描画する枠) :
			bmpFrame(描画する枠)
		{}

		void Draw(const IShape &座標) const override
		{
			bmpFrame->Draw({ 座標.GetX() + gap.x, 座標.GetY() + gap.y, 座標.GetW() * zoomX, 座標.GetH() * zoomY });
		}
	};

	/** マップチップスプライト.*/
	/** \include Model.h*/
	class SpMap : public ISprite
	{
	private:
		ImagePack &chip;//!<
		int width;//!<
		int height;//!<
		int rotate;//!<
		std::vector< std::vector<int> > data;//!<
	public:

		/**コンストラクタ.*/
		SpMap(ImagePack& マップチップ, const char* ファイル名, int 幅, int 高さ, int 角度) :
			width(幅),
			height(高さ),
			rotate(角度),
			chip(マップチップ)
		{
			File csvFile(ファイル名, FileMode::Read);

			data.resize(幅);

			for (int a = 0; a < 幅; ++a)
			{
				data[a].resize(高さ);
			}

			auto lineS = csvFile.GetCsvToInt2();

			for (int a = 0; a < 高さ; ++a)
			{
				for (int b = 0; b < 幅; ++b)
				{
					data[b][a] = lineS[a][b];
				}
			}
		}

		void Draw(const IShape &座標) const override
		{
			const int chipW = chip.GetWidth();
			const int chipH = chip.GetHeight();

			if (Camera::Get())
			{
				//隙間が出来るのを防ぐためCameraを一旦切って処理
				const int baseY = int(Camera::Get()->TransY(座標.GetY()) );
				const int baseX = int(Camera::Get()->TransX(座標.GetX()));

				double posXA;
				double posYA;
				double posXB;
				double posYB;
				double cam_zoom = Camera::Get()->zoom;

				auto camera = Camera::Get();
				Camera::Set();

				for (int a = 0; a < width; ++a)
				{
					posXA = baseX + chipW * a * cam_zoom;
					posXB = baseX + chipW * (a + 1) * cam_zoom;

					for (int b = 0; b < height; ++b)
					{
						posYA = baseY + chipH * b * cam_zoom;
						posYB = baseY + chipH * (b + 1) * cam_zoom;
						const int no = data[a][b];
						if (no == 0) continue;
						chip[no]->DrawExtend({ posXA, posYA, posXB - posXA, posYB - posYA });
					}
				}

				Camera::Set(camera);
			}
			else{
				for (int a = 0; a < width; ++a)
				{
					for (int b = 0; b < height; ++b)
					{
						const int no = data[a][b];
						if (no == 0) continue;
						chip[no]->Draw({ 座標.GetX() + a*chipW, 座標.GetY() + b*chipH });
					}
				}
			}
		}
	};

	/** 描画しないNullスプライト.*/
	/** \include Model.h*/
	class SpNull : public ISprite
	{
	public:

		/**コンストラクタ.*/
		SpNull()
		{}

		void Draw(const IShape &座標) const override
		{}
	};
}