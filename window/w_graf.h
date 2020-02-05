//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[2][a]



	/*決算詳細ウィンドウ*/
	class W_graf: public WindowBox
	{
	private:

	public:
		void init()
		{
			種類 = WindowType::Graf;
			名前 = "決算";
			略記 = "決算";
			アイコン = IconType::素材;
			横幅 = 230;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
		}

		void 派生Draw()
		{
		}

		bool 派生操作()
		{
			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}