//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Film.h>

namespace SDX
{
    /** Filmに再生状態を付与したクラス.*/
    /** \include Anime.h */
    class Anime : public IDrawable
    {
    private:
        const Film* film;//!<対応アニメ
        int direct = 1;//!<進行方向
        int frameNumber = 0;//!<現在のコマ
        double timer = 0;//!<経過時間
    public:

        /** コンストラクタ.*/
        Anime(const Film* 再生する対象) :
            film(再生する対象)
        {}

        /** カウンタの更新.*/
        /** 最後のコマに到達した場合falseを返す*/
        bool Update(double 経過フレーム = 1)
        {
            timer += 経過フレーム;

            if (timer > film->times[frameNumber])
            {
                timer -= film->times[frameNumber];
                switch (film->nexts[frameNumber])
                {
                case (int)NextFrame::Normal:
                    frameNumber += direct;
                    break;
                case (int)NextFrame::ToFront:
                    direct = 1;
                    frameNumber += direct;
                    break;
                case (int)NextFrame::ToBack:
                    direct = -1;
                    frameNumber += direct;
                    break;
                case (int)NextFrame::End:
                    return false;
                    break;
                default:
                    frameNumber = film->nexts[frameNumber];
                    break;
                }

                if ((unsigned int)frameNumber >= film->imageS.size()) frameNumber = 0;
                if (frameNumber < 0) frameNumber = (int)film->imageS.size() - 1;
            }

            return true;
        }

        /** 現在のコマを取得.*/
        Image* GetFrame() const
        {
            return film[0][frameNumber];
        }

        /** コマの位置を設定.*/
        /** 値は0から、Filmのコマ数を超えた場合最終コマ、値が負の場合は0コマ目.*/
        void SetFrame(int コマ数)
        {
            if (コマ数 >= film->GetSize())
            {
                コマ数 = film->GetSize() - 1;
            }
            else if (コマ数 < 0)
            {
                コマ数 = 0;
            }
            frameNumber = コマ数;
            timer = 0;
        }

        /** 指定座標に描画.*/
        bool Draw(const Point &座標, bool 反転フラグ = false) const override
        {
            return GetFrame()->Draw(座標, 反転フラグ);
        }

        /** 指定矩形内に描画.*/
        bool DrawExtend(const Rect &描画領域, bool 反転フラグ = false) const override
        {
            return GetFrame()->DrawExtend(描画領域, 反転フラグ);
        }

        /** 角度、拡大率を指定して描画.*/
        bool DrawRotate(const Point &座標, double 拡大率, double 角度, bool 反転フラグ = false) const override
        {
            return GetFrame()->DrawRotate(座標, 拡大率, 角度, 反転フラグ);
        }
        /** 回転軸、角度、拡大率を指定して描画.*/
        bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率, double 角度, bool 反転フラグ = false) const override
        {
            return GetFrame()->DrawRotateAxis(座標, 回転軸座標, 拡大率, 角度, 反転フラグ);
        }
        /** 回転軸、角度、拡大率を縦横別に指定して描画.*/
        bool DrawRotateAxis(const Point &座標, const Point &回転軸座標, double 拡大率X, double 拡大率Y, double 角度, bool 反転フラグ = false) const override
        {
            return GetFrame()->DrawRotateAxis(座標, 回転軸座標, 拡大率X, 拡大率Y, 角度, 反転フラグ);
        }

        /** 指定した一部分を描画.*/
        bool DrawPart(const Point &描画先座標, const Rect &描画元領域, bool 反転フラグ = false) const override
        {
            return GetFrame()->DrawPart(描画先座標, 描画元領域, 反転フラグ);
        }
    };
}