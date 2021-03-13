//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/Rect.h>

namespace SDX
{
    /** GUIオブジェクトのテンプレート.*/
    class IGUI
    {
    public:
        IGUI(int id, const Rect& rect , double angle):
            id(id),
            rect(rect),
            angle(angle)
        {}

        virtual ~IGUI()
        {}

        int id;
        Rect rect;
        double angle;

        virtual void Init(){};
        virtual void Final(){};
        virtual void Draw(){};
        virtual void Update(){};

        /** マウスオーバー判定 */
        bool isMouse()
        {
			auto pt = Input::mouse.GetPoint();
            return rect.Hit( &pt );
        }

        /** クリックorタッチ判定 */
        bool isClick()
        {
			auto pt = Input::mouse.GetPoint();
            return Input::mouse.Left.on && rect.Hit(&pt);
        }
    };
}