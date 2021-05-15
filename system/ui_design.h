//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;
	
	//後でライブラリに追加する候補の描画関数
	namespace MSystem
	{
		static void DrawVLine(const Point& 始点, int 縦高さ , const Color& 色, int 太さ = 1)
		{
			点.SetColor(色);
			if (縦高さ < 0)
			{
				縦高さ *= -1;
				点.DrawExtend({ 始点.x,始点.y - 縦高さ,太さ,縦高さ });
			} else {

				点.DrawExtend({ 始点.x,始点.y,太さ,縦高さ });
			}

		}

		static void DrawHLine(const Point& 始点, int 横長さ, const Color& 色, int 太さ = 1)
		{
			点.SetColor(色);

			if (横長さ < 0)
			{
				横長さ *= -1;
				点.DrawExtend({ 始点.x - 横長さ , 始点.y , 横長さ , 太さ });
			} else {
				点.DrawExtend({ 始点.x,始点.y,横長さ,太さ });
			}

		}

		static void DrawCircle(const Circle& 円形, const Color& 色)
		{
			円.SetColor(色);
			円.DrawExtend({ 円形.x - 円形.radius, 円形.y - 円形.radius , 円形.radius * 2, 円形.radius * 2 });
		}

		/*立体が＋なら飛び出す、マイナスならへこむ*/
		static void DrawWindow(Point 座標, double 横幅, double 縦幅, int 枠No, int 立体 = 0 , int 透過率 = 255)
		{
			if (立体 != 0)
			{
				Drawing::Rect({ 座標.x,座標.y,横幅 ,縦幅 }, Color::Black);
				if (立体 < 0)
				{

					座標.x -= 立体;
					座標.y -= 立体;
					横幅 += 立体;
					縦幅 += 立体;

				}
				else {
					横幅 -= 立体;
					縦幅 -= 立体;
					//Drawing::Rect({ 座標.x+立体,座標.y + 立体,横幅,縦幅 }, Color::Black);
				}
			}

			if (透過率 < 255)
			{
				Screen::SetBlendMode(BlendMode::Alpha, 透過率);
			}

			ウィンドウ枠[枠No]->DrawPart(座標, { 0,0,10,10 });//左上
			ウィンドウ枠[枠No]->DrawPart({ 座標.x + 横幅 - 10 , 座標.y }, { 20, 0,10,10 });//右上
			ウィンドウ枠[枠No]->DrawPart({ 座標.x , 座標.y + 縦幅 - 10 }, { 0,20,10,10 });//左下
			ウィンドウ枠[枠No]->DrawPart({ 座標.x + 横幅 - 10 , 座標.y + 縦幅 - 10 }, { 20,20,10,10 });//右下

			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y             , 横幅 - 20 , 10 }, { 10,0,10,10 });//上
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y + 縦幅 - 10 , 横幅 - 20 , 10 }, { 10,20,10,10 });//下
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x      , 座標.y + 10        , 10 , 縦幅 - 20 }, { 0,10,10,10 });//左
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 横幅 - 10 , 座標.y + 10 , 10 , 縦幅 - 20 }, { 20,10,10,10 });//右

			//内部
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y + 10 , 横幅 - 20 , 縦幅 - 20 }, { 10,10,10,10 });//右

			if (透過率 < 255)
			{
				Screen::SetBlendMode(BlendMode::NoBlend);
			}
		}

		static void DrawBox(const Point& 座標, const int 横幅, const int 縦幅, const Color& 色)
		{
			Drawing::Rect(Rect(座標.x + 1, 座標.y, 横幅 - 2, 縦幅), 色);
			Drawing::Rect(Rect(座標.x, 座標.y + 1, 横幅, 縦幅 - 2), 色);
		}

		static void DrawBoxBold(const Point& 座標, const int 横幅, const int 縦幅, const Color& 色, int 枠太さ, const Color& 枠色)
		{
			Drawing::Rect(Rect(座標.x + 1, 座標.y, 横幅 - 2, 縦幅), 枠色);
			Drawing::Rect(Rect(座標.x, 座標.y + 1, 横幅, 縦幅 - 2), 枠色);
			Drawing::Rect(Rect(座標.x + 1 + 枠太さ, 座標.y + 枠太さ, 横幅 - 2 - 枠太さ * 2, 縦幅 - 枠太さ * 2), 色);
			Drawing::Rect(Rect(座標.x + 枠太さ, 座標.y + 1 + 枠太さ, 横幅 - 枠太さ * 2, 縦幅 - 2 - 枠太さ * 2), 色);
		}

		static void DrawBar(const Point& 座標, const int 横幅, const int 縦幅, double 割合, int 枠太さ, const Color& 色, const Color& 枠色, const Color& 中色, bool is左側)
		{
			割合 = std::max(0.0, 割合);
			割合 = std::min(1.0, 割合);

			DrawBoxBold(座標, 横幅, 縦幅, 中色, 枠太さ, 枠色);
			int ww = int((横幅 - 枠太さ * 2) * 割合);
			int hh = 縦幅 - 枠太さ * 2;

			if (割合 <= 0.0 || ww < 1)
			{
				return;
			}

			if (is左側)
			{
				DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 色);
			}
			else {
				DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 色);
			}
		}

		//バー２色
		static void DrawBarTwo(const Point& 座標, const int 横幅, const int 縦幅, double 前割合 , double 後割合, int 枠太さ, const Color& 前色 , const Color& 後色, const Color& 枠色, const Color& 中色, bool is左側)
		{
			前割合 = std::max(0.0, 前割合);
			前割合 = std::min(1.0, 前割合);

			後割合 = std::max(0.0, 後割合);
			後割合 = std::min(1.0, 後割合);

			DrawBoxBold(座標, 横幅, 縦幅, 中色, 枠太さ, 枠色);

			int ww = int((横幅 - 枠太さ * 2) * 後割合);
			int hh = 縦幅 - 枠太さ * 2;

			if ( ww > 0 )
			{
				if (is左側)
				{
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 後色);
				} else {
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 後色);
				}
			}

			ww = int((横幅 - 枠太さ * 2) * 前割合);

			if (ww > 0)
			{
				if (is左側)
				{
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 前色);
				} else {
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 前色);
				}
			}
		}


		static void DrawSkill(Image* スキル種, const Point& 座標, Color 色, std::string messe = "")
		{
			Drawing::Rect({ 座標.x ,座標.y ,29,29 }, 色, true);
			Drawing::Rect({ 座標.x + 1,座標.y + 1,27,27 }, Color::White, true);
			Drawing::Rect({ 座標.x + 2,座標.y + 2 ,25,25 }, 色, true);

			スキル種->Draw({ 座標.x + 2,座標.y + 2 });
			MFont::SAlias.DrawBold({ 座標.x + 2 , 座標.y + 12 }, Color::White, Color::Black, messe);
		}

		static void DrawCircleBar(Rect 座標, double ゲージ率, Color 表色, Color 裏色, double 太さ, double 裏太さ)
		{
			Point p1, p2, p3, p4, p5;
			p1.SetPos(座標.x, 座標.y);
			p2.SetPos(座標.x + 座標.GetW(), 座標.y);
			p3.SetPos(座標.x + 座標.GetW(), 座標.y + 座標.GetH());
			p4.SetPos(座標.x, 座標.y + 座標.GetH());
			p5 = p1;

			//裏色
			Drawing::Line(p1, p2, 裏色, (int)裏太さ);
			Drawing::Line(p2, p3, 裏色, (int)裏太さ);
			Drawing::Line(p3, p4, 裏色, (int)裏太さ);
			Drawing::Line(p4, p1, 裏色, (int)裏太さ);

			DrawCircle({ p1.x, p1.y, 裏太さ / 2 }, 裏色);
			DrawCircle({ p2.x, p2.y, 裏太さ / 2 }, 裏色);
			DrawCircle({ p3.x, p3.y, 裏太さ / 2 }, 裏色);
			DrawCircle({ p4.x, p4.y, 裏太さ / 2 }, 裏色);

			//表
			if (ゲージ率 == 0) { return; }

			if (ゲージ率 < 0.25)
			{
				p2.x = 座標.x + 座標.GetW() * ゲージ率 * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				MSystem::DrawCircle({ p1.x, p1.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p2.x, p2.y, 太さ / 2 }, 表色);
			}
			else if (ゲージ率 < 0.5)
			{
				p3.y = 座標.y + 座標.GetH() * (ゲージ率 - 0.25) * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Line(p2, p3, 表色, (int)太さ);
				MSystem::DrawCircle({ p1.x, p1.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p2.x, p2.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p3.x, p3.y, 太さ / 2 }, 表色);
			}
			else if (ゲージ率 < 0.75)
			{
				p4.x = 座標.x + 座標.GetW() - 座標.GetW() * (ゲージ率 - 0.5) * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Line(p2, p3, 表色, (int)太さ);
				Drawing::Line(p3, p4, 表色, (int)太さ);
				MSystem::DrawCircle({ p1.x, p1.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p2.x, p2.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p3.x, p3.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p4.x, p4.y, 太さ / 2 }, 表色);
			}
			else
			{
				p5.y = 座標.y + 座標.GetH() - 座標.GetH() * (ゲージ率 - 0.75) * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Line(p2, p3, 表色, (int)太さ);
				Drawing::Line(p3, p4, 表色, (int)太さ);
				Drawing::Line(p4, p5, 表色, (int)太さ);
				MSystem::DrawCircle({ p1.x, p1.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p2.x, p2.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p3.x, p3.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p4.x, p4.y, 太さ / 2 }, 表色);
				MSystem::DrawCircle({ p5.x, p5.y, 太さ / 2 }, 表色);
			}
		}
	}

	enum class UIType
	{
		明ボタン,
		平ボタン,
		凸ボタン,
		凸ハイライト,
		凹ボタン,
		グループ明,
		グループ中,
		グループ暗,
		タイトル,
		ウィンドウ,
		フレーム,
		ゲージ,
		丸フレーム,
		選択丸フレーム,
	};

	//これを継承して、画像素材利用UIに後から差し替えも可能にしておく
	class IDesign
	{
	public:
		virtual void Draw(UIType type, int x, int y, int w, int h) = 0;

		virtual void DrawGauge(int x, int y, int w, int h, double rate) = 0;
	};

	class Design : public IDesign
	{
	private:
		void DrawRoundColor(int x, int y, int w, int h , Color& color)
		{
			if (w > h)
			{
				int xa = x + h / 2;
				int xb = x + w - h / 2;

				MSystem::DrawCircle({ (double)xa,(double)(y + h / 2), (double)h / 2 }, color);
				MSystem::DrawCircle({ (double)xb,(double)(y + h / 2), (double)h / 2 }, color);


				Drawing::Rect({ xa , y , w - h , h }, color);
			}
			else
			{
				int ya = y + w / 2;
				int yb = y + h - w / 2;

				MSystem::DrawCircle({ (double)(x + w / 2),(double)ya, (double)w / 2 }, color);
				MSystem::DrawCircle({ (double)(x + w / 2),(double)yb, (double)w / 2 }, color);
				Drawing::Rect({ x , ya , w  , h - w }, color);
			}
		}

	public:
		static Design* No1;//基本的なやつ

		static Design* UI;//操作可能なUI用
		static Design* Help;//ヘルプ用

		static Design Green;
		static Design Blue;
		static Design Brown;
		static Design Wood;
		static Design BlueGrey;

		Color 影色;//ほぼ黒色

		Color エッジ色;//濃色
		Color 濃色;
		Color 凹色;//やや暗い、凹みボタン、非選択タブ、タイトル色
		Color グループ;//やや濃色
		Color 凸色;//やや明るい
		Color 背景色;//ほぼ白色
		Color ハイライト;//明るい色

		inline static Color 暗字;
		inline static Color 灰字;
		inline static Color 明字;

		template<class TLayout>
		void Draw(UIType type, TLayout &it )
		{
			Draw( type, it.x, it.y, it.w, it.h);			
		}

		template<class TLayout>
		void Draw(UIType type, TLayout& it , int lineID)
		{
			Draw(type, it.x + it.並べx * (lineID % it.改行値) , it.y + it.並べy * (lineID / it.改行値), it.w, it.h);
		}

		void Draw(UIType type , int x, int y, int w, int h)
		{

			switch ( type )
			{
				case UIType::明ボタン: DrawButton(x, y, w, h , 凸色); break;
				case UIType::平ボタン: DrawButton(x,y,w,h , 背景色); break;
				case UIType::凸ボタン: DrawButton凸(x, y, w, h,背景色); break;
				case UIType::凸ハイライト: DrawButton凸(x, y, w, h,凸色); break;
				case UIType::凹ボタン: DrawButton凹(x, y, w, h); break;
				case UIType::グループ明: DrawBack(x, y, w, h, ハイライト); break;
				case UIType::グループ暗: DrawBack(x, y, w, h, グループ); break;
				case UIType::グループ中: DrawBack(x, y, w, h,背景色); break;
				case UIType::タイトル: DrawTitle(x, y, w, h); break;
				case UIType::ウィンドウ: DrawWindow(x, y, w, h); break;
				case UIType::フレーム: DrawFrame(x, y, w, h); break;
				case UIType::ゲージ: DrawGauge(x, y, w, h , 1.0 ); break;
				case UIType::丸フレーム: DrawRound(x, y, w, h); break;
				case UIType::選択丸フレーム: DrawSelectRound(x, y, w, h); break;
			default:
				break;
			}
		}

		//縁有りで凸ったボタン
		void DrawButton凸(int x, int y, int w, int h , Color 色)
		{
			Drawing::Rect({ x,y,w,h - 4 }, エッジ色);
			Drawing::Rect({ x + 1,y + 1,w - 2,h - 4 }, 色);
			MSystem::DrawHLine({ x + 1 , y + h - 5 }, w - 2, グループ);
			Drawing::Rect({ x,y + h - 4,w,4 }, 影色);
		}

		//縁有りで凹んだボタン
		void DrawButton凹(int x, int y, int w, int h)
		{
			Drawing::Rect({ x,y,w,h }, エッジ色);
			Drawing::Rect({ x + 1,y + 1, w - 2, 4 }, 影色);
			Drawing::Rect({ x + 1,y + 5,w - 2,h - 6 }, 凹色);
			MSystem::DrawHLine({ x + 1 , y + h - 2 }, w - 1, 濃色);
		}

		//平面ボタン
		void DrawButton(int x, int y, int w, int h ,Color& ボタン色)
		{
			Drawing::Rect({ x,y,w,h }, エッジ色);
			Drawing::Rect({ x + 1,y + 1,w - 2,h - 2 }, ボタン色);
			MSystem::DrawHLine({ x + 1 , y + h - 2 }, w - 2, 凹色);
		}

		//背景色の四角を描画
		void DrawBack(int x, int y, int w, int h , Color& 色)
		{
			Drawing::Rect({ x  , y + 1 , w , h - 2 }, 色);
			MSystem::DrawHLine({ x + 1 , y }, w - 2, 色);
			MSystem::DrawHLine({ x + 1 , y + h - 1 }, w - 2, 色);
		}

		//ウィンドウのタイトル部
		void DrawTitle(int x, int y, int w, int h)
		{
			Drawing::Rect({ x,y,w,h }, エッジ色, false);
			Drawing::Rect({ x + 1,y + 1,w - 2,h - 2 }, グループ);
			MSystem::DrawHLine({ x + 1 , y + h - 1 }, w - 2, 凹色);
		}

		//タイトル下のウィンドウ部分
		void DrawWindow(int x, int y, int w, int h)
		{
			Drawing::Rect({ x,y,w,h }, エッジ色, false);
			Drawing::Rect({ x + 1,y + 1,w - 2,h - 2 }, 背景色);
			MSystem::DrawHLine({ x + 1 , y + h - 2 }, w - 1, 凸色);
			Drawing::Rect({ x + 1,y + h,w - 1 , 2 }, 影色);
		}

		//ヘルプウィンドウ用描画
		void DrawFrame(int x, int y, int w, int h)
		{
			Drawing::Rect({ x , y , w  , h }, 凹色);
		}
		
		//両端が丸い明るい枠を描画
		void DrawRound(int x , int y , int w , int h )
		{
			DrawRoundColor(x, y, w, h, 凸色);
			DrawRoundColor(x+1, y+1, w-2, h-2, ハイライト);
		}

		void DrawSelectRound(int x, int y, int w, int h)
		{
			DrawRoundColor(x, y, w, h, 凹色);
			DrawRoundColor(x + 1, y + 1, w - 2, h - 2, 凸色);
		}

		void DrawGauge(int x, int y, int w, int h, double rate)
		{
			DrawRoundColor(x, y, w, h , ハイライト);

			if (rate > 0)
			{
				if (w > h)
				{
					int wr = std::max(int(w * rate), h);
					DrawRoundColor(x + 1, y + 1, wr - 2, h - 2, 凹色);
				}else{
					int hr = std::max(w , int(h * rate));
					DrawRoundColor(x + 1, y + 1, w - 2, hr - 2, 凹色);
				}

			}
		}

		static void Load()
		{
			Green.影色 = { 0x424242 };//Gray 800
			Green.エッジ色 = { 0x616161 };//Gray 600
			Green.濃色 = { 0x2E7D32 };//Green 800
			Green.凹色 = { 0x43A047 };//Green 600
			Green.グループ = { 0x66bb6a };//Green 400
			Green.背景色 = { 0xa5d6a7 };//Green 200
			Green.凸色 = { 0xc8e6c9 };//Green 100
			Green.ハイライト = { 0xE8F5E9 };////Green 50

			Blue.影色 = { 0x424242 };//Gray 800
			Blue.エッジ色 = { 0x616161 };//Gray 600
			Blue.濃色 = { 0x0d47a1 };//900
			Blue.凹色 = { 0x1565c0 };//800
			Blue.グループ = { 0x42A5F5 };//400
			Blue.背景色 = { 0x90CAF9 };//200
			Blue.凸色 = { 0xBBDEFB };//100
			Blue.ハイライト = { 0xE3F2FD };////50

			Brown.影色 = { 0x424242 };//Gray 800
			Brown.エッジ色 = { 0x616161 };//Gray 600
			Brown.濃色 = { 0x6D4C41 };//600
			Brown.凹色 = { 0x8D6E63 };//400
			Brown.グループ = { 0xA1887F };//300
			Brown.背景色 = { 0xBCAAA4 };//200
			Brown.凸色 = { 0xD7CCC8 };//100
			Brown.ハイライト = { 0xEFEBE9 };////50

			BlueGrey.影色 = { 0x424242 };//Gray 800
			BlueGrey.エッジ色 = { 0x616161 };//Gray 600
			BlueGrey.濃色 = { 0x37474F };//800
			BlueGrey.凹色 = { 0x546E7A };//600
			BlueGrey.グループ = { 0x78909C };//400
			BlueGrey.背景色 = { 0xB0BEC5 };//200
			BlueGrey.凸色 = { 0xCFD8DC };//100
			BlueGrey.ハイライト = { 0xECEFF1 };////50

			//オリジナル配色
			Wood.影色 = { 0x424242 };//Gray 800
			Wood.エッジ色 = { 0x616161 };//Gray 600
			Wood.濃色 = { 82,45,20 };//Blue 800
			Wood.凹色 = { 135,95,60 };//Blue 600
			Wood.グループ = { 175,135,92 };//Blue 400
			Wood.背景色 = { 195,165,132 };//Blue 200
			Wood.凸色 = { 225,205,172 };//Blue 100
			Wood.ハイライト = { 247,235,214 };////Blue 50

			明字 = { 0xEEEEEE };//Gray 200
			灰字 = { 0x9E9E9E };//Gray 500
			暗字 = { 0x424242 };//Gray 900

			No1 = &BlueGrey;

			UI = &Blue;
			Help = &Green;
		}

	};

	Design* Design::No1;
	Design* Design::Help;
	Design* Design::UI;

	Design Design::Green;
	Design Design::Blue;
	Design Design::Brown;
	Design Design::Wood;
	Design Design::BlueGrey;
}