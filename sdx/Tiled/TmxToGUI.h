//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Tiled/IGUI.h>
#include <Tiled/GUIData.h>
#include <Tiled/GetTag.h>
#include <vector>

namespace SDX
{
	/** Tiledで作成したデータ(.tmx)を変換してGUIDataにする関数.*/
	/**@todo 実装中*/
	/** \include TranceCode.h*/
	GUIData TMXtoGUI(const char* tmxファイル名 , const char* シーン名, std::function<void(GUIData& data, std::string& type , int id, int gid, Rect rect, double zoomW , double zoomH , double angle, std::vector<std::string>& properties)> Factory関数 )
	{
		File file(tmxファイル名, FileMode::Read);
		auto strS = file.GetLineS();
		GUIData guiS;
		bool visible = false;
		bool isScene = false;

		std::string layerName = "";
		std::string name = "";
		std::string type = "";
		int id = 0;
		int gid = 0;
		Rect rect;
		double angle = 0;
		double zoomW = 0;
		double zoomH = 0;
		std::vector<std::string> properties;
		struct TileSize
		{
			TileSize(int w, int h) :
				w(w),
				h(h)
			{}

			int w;
			int h;
		};
		std::vector<TileSize> tileS;//各タイルの大きさ
		tileS.push_back({ 0, 0 });//ID=0は空

		int index = 0;
		int tileW;
		int tileH;

		for (auto &it : strS)
		{
			//タイル情報を取得
			if (it.find("<tileset") != std::string::npos)
			{
				tileW = std::atoi(GetTag(it, "tilewidth=").c_str());
				tileH = std::atoi(GetTag(it, "tileheight=").c_str());
			}
			else if (it.find("<image width") != std::string::npos)
			{
				tileS.push_back({ std::atoi(GetTag(it, "width=").c_str()), std::atoi(GetTag(it, "height=").c_str()) });
			}
			else if (it.find("<image source") != std::string::npos)
			{
				int w = std::atoi(GetTag(it, "width=").c_str()) / tileW;
				int h = std::atoi(GetTag(it, "height=").c_str()) / tileH;

				for (int a = 0; a < w*h; ++a)
				{
					tileS.push_back({ tileW, tileH });
				}
			}
			else if (it.find("<map") != std::string::npos)
			{
				//フォーム全体の情報
			}
			else if (it.find("<objectgroup") != std::string::npos)
			{
				//レイヤー名を取得
				layerName = GetTag(it, "name=");
				isScene = (layerName == シーン名);
			}
			else if (it.find("</objectgroup>") != std::string::npos && isScene)
			{
				break;//目的のSceneの情報を読み取り完了
			}
			else if (it.find("<object") != std::string::npos)
			{
				//非表示の場合は追加しない
				if (it.find("visible=\"0\"") != std::string::npos || !isScene )
				{
					visible = false;
				}
				else
				{
					name = GetTag(it, "name=");
					type = GetTag(it, "type=");
					if (type == ""){ type = "Image"; }
					rect.x = std::atoi(GetTag(it, "x=").c_str());
					rect.y = std::atoi(GetTag(it, "y=").c_str());
					rect.widthRight = std::atof(GetTag(it, "width=").c_str());
					rect.heightDown = std::atof(GetTag(it, "height=").c_str());
					id = std::atoi(GetTag(it, " id=").c_str());
					gid = std::atoi(GetTag(it, "gid=").c_str());
					angle = std::atof(GetTag(it, "rotation=").c_str());

					if (gid != 0)
					{
						//タイルセットから大きさを取得
						rect.y -= tileS[gid].h;
						if (rect.widthRight > 0){ zoomW = rect.widthRight; }
						if (rect.heightDown > 0){ zoomH = rect.heightDown; }
						rect.widthRight = tileS[gid].w * zoomW;
						rect.heightDown = tileS[gid].h * zoomH;
					}

					properties.clear();
					visible = true;
					//次の行がpropertiesでは無いなら追加
					if (strS[index + 1].find("<properties>") == std::string::npos)
					{
						Factory関数(guiS, type , id , gid, rect,zoomW,zoomH, angle, properties);
					}
				}
			}
			else if (it.find("<property") != std::string::npos && visible)
			{
				//非表示の時はプロパティも無視する
				int b = it.find("value=") + 7;
				properties.push_back(it.substr(b, it.find("\"", b) - b));
			}
			else if (it.find("</object>") != std::string::npos && visible)
			{
				//追加処理
				Factory関数(guiS, type, id , gid, rect , zoomW , zoomH , angle, properties);
			}
			++index;
		}

		return guiS;
	}
}