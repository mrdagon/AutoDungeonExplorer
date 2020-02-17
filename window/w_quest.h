//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[15][a]



	/*依頼ウィンドウ*/
	class W_Quest : public WindowBox
	{
	private:

	public:
		void init()
		{
			種類 = WindowType::Quest;
			名前 = "クエスト";
			略記 = "依頼";
			アイコン = IconType::依頼;
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