//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Color.h>
#include <Multimedia/Image.h>
#include <Multimedia/Font.h>
#include <Utility/VariadicStream.h>
#include <Framework/Shape.h>
#include <Framework/Camera.h>

namespace SDX
{
	/** リソースを読み込まずに描画を行う関数群.*/
	/** \include Drawing.h*/
	class Drawing
	{
	private:
		//生成、削除、コピー等を禁止
		Drawing() = default;
		~Drawing() = default;
		void operator =(const Drawing& src){}
		Drawing(const Drawing& src){}

		/**透過状態を計算する.*/
		static void RGBACulculate( const Color &色 )
		{
			if (色.GetAlpha() == 255)
			{
				SDL_SetRenderDrawBlendMode(Screen::GetHandle(), (SDL_BlendMode)Screen::GetRenderer()->blendMode);
			}
			else
			{
				SDL_SetRenderDrawBlendMode(Screen::GetHandle(), (SDL_BlendMode)BlendMode::Alpha);
			}

			SDL_SetRenderDrawColor
				(
				Screen::GetHandle(),
				Screen::GetRenderer()->rgba.GetRed() * 色.GetRed() / 255,
				Screen::GetRenderer()->rgba.GetGreen() * 色.GetGreen() / 255,
				Screen::GetRenderer()->rgba.GetBlue() * 色.GetBlue() / 255,
				Screen::GetRenderer()->rgba.GetAlpha() * 色.GetAlpha() / 255
				);
		}

		/** Rendererに円を描画、処理はかなり重い.*/
		static void MakeCircle(SDL_Renderer* renderer,int x1, int y1,int x2, int y2)
		{
			//実装参考[http://hp.vector.co.jp/authors/VA028002/sdl/]
			//パブリックドメインなのでわりとコピペしてます
			int r;
			int dx, dy;
			int xa, ya, xb, yb;
			int f;

			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer,255,255,255,255);

			dx = x2 - x1 < 0 ? x1 - x2 : x2 - x1;
			dy = y2 - y1 < 0 ? y1 - y2 : y2 - y1;
			
			r = dx / 2;
			xa = r;
			ya = 0;
			f = 3 - 2 * r;
			x1 += dx / 2;
			y1 += dy / 2;
			x2 = x1 + dx % 2;
			y2 = y1 + dy % 2;
			while (xa >= ya){
				xb = (xa * dy) / dx;
				yb = (ya * dy) / dx;
				
				SDL_RenderDrawLine(renderer, xa + x2, -yb + y1,xa + x2, yb + y2); /*A*/
				SDL_RenderDrawLine(renderer, ya + x2, -xb + y1, ya + x2, xb + y2); /*B*/
				SDL_RenderDrawLine(renderer, -ya + x1, -xb + y1, -ya + x1, xb + y2); /*C*/
				SDL_RenderDrawLine(renderer, -xa + x1, -yb + y1, -xa + x1, yb + y2); /*D*/

				if (f >= 0){
					xa--;
					f -= 4 * xa;
				}
				ya++;
				f += 4 * ya + 2;
			}
		}
		
		/** 円を作成.*/
		static Image& GetCircle(const Color &描画色, const Rect &矩形 = {0,0,0,0}, int 太さ = 0)
		{
			static Image circleA;
			static Image circleB;
			static Image circleC;
			const int CIRCLE_SIZE = 512;

			if (circleA.GetHandle() == nullptr)
			{
				circleA.Make(CIRCLE_SIZE, CIRCLE_SIZE);
				circleB.Make(CIRCLE_SIZE, CIRCLE_SIZE);
				circleC.Make(CIRCLE_SIZE, CIRCLE_SIZE);

				auto mode = Screen::GetRenderer()->blendMode;
				auto col = Screen::GetRenderer()->rgba;
				int alpha = Screen::GetRenderer()->rgba.GetAlpha();//Alpha値の場合ここの減算率が変化する
				auto cam = Camera::Get();

				Camera::Set();
				Screen::SetDrawMode();
				auto prev = Screen::GetTarget();

				Screen::SetTarget(&circleA);
				MakeCircle(Screen::GetHandle(), 0, 0, CIRCLE_SIZE, CIRCLE_SIZE);
				Screen::SetTarget(&circleB);
	    		SDL_SetRenderDrawColor(Screen::GetHandle(), 0, 0, 0, 0);
    			SDL_RenderClear(Screen::GetHandle());
				Screen::SetTarget(&circleC);
				Drawing::Rect({ 0, 0, CIRCLE_SIZE, CIRCLE_SIZE }, Color::White, true);
				Screen::SetTarget(prev);

				Screen::SetDrawMode(col,mode);
				Camera::Set(cam);
			}

			if (太さ <= 0)
			{
				circleA.SetColor(描画色);
				return circleA;
			}
			else
			{
				太さ = std::max(太さ * CIRCLE_SIZE * 2 / int(矩形.GetW() + 矩形.GetH()), 2);//最低2

				auto prev = Screen::GetTarget();
				auto mode = Screen::GetRenderer()->blendMode;
				auto col = Screen::GetRenderer()->rgba;
				int alpha = Screen::GetRenderer()->rgba.GetAlpha();//Alpha値の場合ここの減算率が変化する
				auto cam = Camera::Get();

				Camera::Set();
				Screen::SetDrawMode();

				Screen::SetTarget(&circleB);
				circleA.SetColor(Color::White);
				circleA.Draw({ 0, 0 });
				circleA.SetColor(Color::Black);
				circleA.DrawExtend({ 太さ, 太さ , CIRCLE_SIZE - 太さ*2 , CIRCLE_SIZE - 太さ*2 });
				Screen::SetTarget(&circleC);
				circleA.SetColor({255-alpha,255-alpha,255-alpha});
				circleA.Draw({ 0, 0 });
				circleA.SetColor(Color::White);
				circleA.DrawExtend({ 太さ, 太さ ,  CIRCLE_SIZE - 太さ*2, CIRCLE_SIZE - 太さ*2 });
				Screen::SetTarget(prev);
				Camera::Set(cam);


				if (mode == BlendMode::Mula)
				{
					Screen::SetDrawMode({255,255,255,alpha},BlendMode::Mula);
					circleB.DrawExtend(矩形);
				}
				else
				{
					if (mode != BlendMode::Add)
					{
						Screen::SetDrawMode({ 255, 255, 255, alpha }, BlendMode::Mula);
						circleC.DrawExtend(矩形);
					}
					Screen::SetDrawMode({ 描画色.GetRed(), 描画色.GetGreen(), 描画色.GetBlue(), alpha }, BlendMode::Add);
					circleB.DrawExtend(矩形);
				}

				Screen::SetDrawMode(col, mode);

				return circleB;
			}
		}

		/** 正三角形を作成.*/
		static void GetTriangle(const Color &描画色, const Point &中心座標 = {0,0}, int 辺の長さ = 0, double 角度 = 0, int 太さ = 0)
		{
			static Image imageA;
			static Image imageB;
			static Image imageC;

			const int WSIZE = 173*2;
			const int HSIZE = 200*2;

			if (imageA.GetHandle() == nullptr)
			{
				imageA.Make(WSIZE, HSIZE);//高さ=√3の近似
				imageB.Make(WSIZE, HSIZE);
				imageC.Make(WSIZE, HSIZE);

				auto prev = Screen::GetTarget();
				auto mode = Screen::GetRenderer()->blendMode;
				auto col = Screen::GetRenderer()->rgba;
				auto cam = Camera::Get();

				Camera::Set();
				Screen::SetDrawMode();

				Screen::SetTarget(&imageA);
				//横向きの三角形を描画
	    		SDL_SetRenderDrawColor(Screen::GetHandle(), 0, 0, 0, 0);
    			SDL_RenderClear(Screen::GetHandle());
				SDL_SetRenderDrawBlendMode(Screen::GetHandle(), SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(Screen::GetHandle(), 255, 255, 255, 255);
				for (int y = 0; y < HSIZE/2; ++y)
				{
					int x = WSIZE * y * 2 / HSIZE;
					SDL_RenderDrawLine(Screen::GetHandle(), 0, y, x, y);
					SDL_RenderDrawLine(Screen::GetHandle(), 0, HSIZE-y-1, x, HSIZE-y-1);
				}
				Screen::SetTarget(&imageB);
				SDL_SetRenderDrawColor(Screen::GetHandle(), 0, 0, 0, 0);
				SDL_RenderClear(Screen::GetHandle());
				Screen::SetTarget(&imageC);
				Drawing::Rect({ 0, 0, WSIZE, HSIZE }, Color::White, true);
				Screen::SetTarget(prev);

				Screen::SetDrawMode(col, mode);
				Camera::Set(cam);
			}

			const double 拡大率 = double(辺の長さ) / HSIZE;
			
			if (太さ <= 0)
			{
				imageA.SetColor(描画色);
				imageA.DrawRotateAxis({ 中心座標.x ,中心座標.y}, { WSIZE/3, HSIZE/2 }, 拡大率, 角度);
			}
			else
			{
				太さ = std::max(太さ * WSIZE* 2  / (辺の長さ), 2);//最低2

				auto prev = Screen::GetTarget();
				int alpha = Screen::GetRenderer()->rgba.GetAlpha();//Alpha値によりここの減算率が変化する
				auto mode = Screen::GetRenderer()->blendMode;
				auto col = Screen::GetRenderer()->rgba;
				auto cam = Camera::Get();

				Camera::Set();
				Screen::SetDrawMode();

				Screen::SetTarget(&imageB);
				imageA.SetColor(Color::White);
				imageA.Draw({ 0, 0 });
				imageA.SetColor(Color::Black);
				imageA.DrawExtend({ 太さ/2, 太さ ,  WSIZE - 太さ*3/2, HSIZE - 太さ*2 });
				Screen::SetTarget(&imageC);
				imageA.SetColor({ 255 - alpha, 255 - alpha, 255 - alpha });
				imageA.Draw({ 0, 0 });
				imageA.SetColor(Color::White);
				imageA.DrawExtend({ 太さ/2, 太さ ,  WSIZE - 太さ*3/2, HSIZE - 太さ*2 });
				Screen::SetTarget(prev);
				Camera::Set(cam);

				if (mode == BlendMode::Mula)
				{
					Screen::SetDrawMode({ 255, 255, 255, alpha }, BlendMode::Mula);
					imageB.DrawRotateAxis({ 中心座標.x, 中心座標.y }, { WSIZE / 3, HSIZE / 2 }, 拡大率, 角度);
				}
				else
				{
					if ( mode != BlendMode::Add)
					{
						Screen::SetDrawMode({ 255, 255, 255, alpha }, BlendMode::Mula);
						imageC.DrawRotateAxis({ 中心座標.x, 中心座標.y }, { WSIZE / 3, HSIZE / 2 }, 拡大率, 角度);
					}
					
					Screen::SetDrawMode({ 描画色.GetRed(), 描画色.GetGreen(), 描画色.GetBlue(), alpha }, BlendMode::Add);
					imageB.DrawRotateAxis({ 中心座標.x, 中心座標.y }, { WSIZE / 3, HSIZE / 2 }, 拡大率, 角度);
				}

				Screen::SetDrawMode(col, mode);
			}
		}
public:
		/** デフォルトのフォントを取得する.*/
		static Font& GetFont()
		{
			static Font defaultFont;
			return defaultFont;
		}

		/** デフォルトのフォントを設定する.*/
		static void SetDefaultFont(const char* フォント名, int 大きさ,int 行間 = 0 , bool 高品質レンダリング = true)
		{
			GetFont().Load(フォント名, 大きさ, 行間, 高品質レンダリング);
		}

		/** 始点と終点を結ぶ直線を描画.*/
		static void Line(const Point &始点, const Point &終点, const Color &色, int 太さ = 1)
		{
			if (太さ <= 1)
			{
				int xA,xB,yA,yB;
				RGBACulculate(色);
				if (Camera::Get())
				{
					xA = (int)Camera::Get()->TransX(始点.x);
					xB = (int)Camera::Get()->TransX(終点.x);
					yA = (int)Camera::Get()->TransY(始点.y);
					yB = (int)Camera::Get()->TransY(終点.y);
				}
				else
				{
					xA = (int)始点.x;
					xB = (int)終点.x;
					yA = (int)始点.y;
					yB = (int)終点.y;
				}

				SDL_RenderDrawLine(Screen::GetHandle(), xA, yA, xB, yB);
			}
			else
			{
				static Image image;
				if (image.GetHandle() == nullptr)
				{
					auto prev = Screen::GetRenderer()->target;
					auto mode = Screen::GetRenderer()->blendMode;
					auto col = Screen::GetRenderer()->rgba;
					auto cam = Camera::Get();

					image.Make(256, 256);
					Camera::Set();
					Screen::SetDrawMode();
					Screen::SetTarget(&image);
					Drawing::Rect({ 0, 0, 256, 256 }, Color::White, true);
					Screen::SetTarget(prev);
					Screen::SetDrawMode(col,mode);
					Camera::Set(cam);
				}

				double rateX = std::sqrt((終点.x - 始点.x)*(終点.x - 始点.x) + (終点.y - 始点.y) * (終点.y - 始点.y));//太さ
				double rateY = 太さ;//長さ
				double angle = std::atan2( 終点.y - 始点.y , 終点.x - 始点.x);

				image.SetColor(色);
				image.DrawRotateAxis({ (始点.x + 終点.x)/2, (始点.y + 終点.y)/2 }, { 128, 128 }, rateX/256, rateY/256, angle);
			}
		}

		/** 左上の座標と大きさを指定して矩形を描画.*/
		static void Rect(const Rect &領域, const Color &色, bool 塗りつぶしフラグ = true)
		{
			SDL_Rect buf = { (int)領域.GetLeft(), (int)領域.GetTop(), (int)領域.GetW(), (int)領域.GetH() };

			if (Camera::Get())
			{
				buf = Camera::Get()->TransRect(buf);
			}

			RGBACulculate(色);
			if (塗りつぶしフラグ)
			{
				SDL_RenderFillRect(Screen::GetHandle(), &buf);
			}
			else
			{
				SDL_RenderDrawRect(Screen::GetHandle(), &buf);
			}
		}

		/** 中心と半径を指定して円を描画.*/
		/** 太さに0を指定した場合塗りつぶし.*/
		/** ※太さが1以上の場合処理が重い*/
		static void Circle(const Circle &円形, const Color& 色, int 太さ = 0)
		{
			if (円形.radius <= 0){ return; }

			if (太さ <= 0)
			{
				GetCircle(色).DrawExtend({ 円形.x - 円形.radius, 円形.y - 円形.radius , 円形.radius*2, 円形.radius*2 });
			} 
			else
			{
				GetCircle(色, { 円形.x - 円形.radius, 円形.y - 円形.radius, 円形.radius * 2, 円形.radius * 2 }, 太さ);
			}
		}

		/** 中心と外接する四角形の大きさを指定して楕円を描画.*/
		/** 太さに0を指定した場合塗りつぶし.*/
		/** ※太さが1以上の場合処理が重い*/
		static void Oval(const Point &中心, int 幅, int 高さ, const Color& 色, int 太さ = 0)
		{
			if (太さ <= 0)
			{
				GetCircle(色).DrawExtend({ 中心.x - 幅 / 2, 中心.y - 高さ / 2, (double)幅, (double)高さ });
			}
			else
			{
				GetCircle(色, { 中心.x - 幅 / 2, 中心.y - 高さ / 2, 幅, 高さ }, 太さ);
			}
		}

		/** 頂点を指定して多角形を描画.*/
		static void Polygon(std::vector<Point> 頂点, const Color &色 ,int 太さ = 1)
		{
			for (unsigned int a = 0; a < 頂点.size() ; ++a)
			{
				if (a == 頂点.size() - 1)
				{
					//最後の辺
					Drawing::Line(頂点[a],頂点[0],色,太さ);
				}
				else
				{
					Drawing::Line(頂点[a], 頂点[a+1], 色, 太さ);
				}

			}
		}

		/** 正三角形を描画.*/
		/** 太さに0を指定した場合塗りつぶし.*/
		/** ※太さが1以上の場合処理が重い*/
		static void Triangle(const Point &中心座標,int 辺の長さ , double 角度 , const Color &描画色 , int 太さ = 0)
		{
			if (太さ <= 0)
			{
				GetTriangle(描画色, 中心座標, 辺の長さ, 角度);
			}
			else
			{
				GetTriangle(描画色, 中心座標, 辺の長さ, 角度, 太さ);
			}
		}

		/** 指定座標に点を描画.*/
		static void Pixel(const Point &座標, const Color &色)
		{
			RGBACulculate(色);

			double x = 座標.x;
			double y = 座標.y;

			if (Camera::Get())
			{
				x = Camera::Get()->TransX(x);
				y = Camera::Get()->TransY(y);
			}

			SDL_RenderDrawPoint(Screen::GetHandle(), (int)x, (int)y);
		}

		/** 画像を一時的にメモリに読み込んで描画.*/
		/** この処理は重いので、通常はImageクラスを利用する*/
		static void ImageFile(const Point &座標, const char *ファイル名, bool 透過フラグ = true)
		{
			Image buf(ファイル名);
			buf.Draw(座標, false);
			buf.Release();
		}

		/** 文字を描画.*/
		/** フォントはデフォルトでゴシック体*/
		static void String(const Point &座標, const Color &色, const VariadicStream &描画する文字列)
		{
			GetFont().Draw(座標, 色, 描画する文字列);
		}
	};
}