﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*素材*/
	class Material
	{
	private:
	public:
		std::string 名前;
		std::string 説明;
		MaterialType 種類;
		int 基本価格;
		int レア度;
	};
}