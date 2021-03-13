//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Tiled/IGUI.h>

namespace SDX
{
	/** GUIオブジェクトのテンプレート.*/
	class GUIData
	{
	public:
		//全体のデータ
		//全体の大きさは width*tileWidth,height*tileHeightになる
		int width;//横方向のタイル数
		int height;//縦方向のタイル数
		int tileWidth;//タイル一枚の横幅
		int tileHeight;//タイル一枚の縦幅

		//マップレイヤーのデータ

		//マップチップのデータ
		
		//IGUIの情報
		std::vector<std::shared_ptr<IGUI>> dataS;
	};
}