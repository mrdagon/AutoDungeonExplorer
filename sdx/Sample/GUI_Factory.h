#pragma once
#include <Tiled/GUIData.h>
#include <vector>
#include <string>
#include "Image.h"
#include "Button.h"
#include "Frame.h"
#include "Text.h"

namespace SDX
{
	void GUI_Factory(GUIData& data, std::string& type , int id , int gid, Rect rect, double zoomW , double zoomH , double angle, std::vector<std::string>& properties)
	{
		if(type == "Image")
		{
			data.dataS.push_back(std::make_shared<Image>(id,rect,angle,gid,zoomW,zoomH));
		}
		else if(type == "Button")
		{
			data.dataS.push_back(std::make_shared<Button>(id,rect,angle,std::atoi(properties[0].c_str())));
		}
		else if(type == "Frame")
		{
			data.dataS.push_back(std::make_shared<Frame>(id,rect,angle,std::atoi(properties[0].c_str())));
		}
		else if(type == "Text")
		{
			data.dataS.push_back(std::make_shared<Text>(id,rect,angle,std::atoi(properties[0].c_str()),properties[1].c_str()));
		}
	}
}
