//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[2][a]



	/*決算ログ*/
	class W_SettleLog : public WindowBox
	{
	private:

	public:
		//・販売数
		//・売上
		//・レシピ別製造数
		//・合計製造数
		//・合計素材獲得量
		//・合計素材消費量
		//・人件費
		//・ギルド人数
		//・経営戦術費用
		//・利益
		//・総資産
		//・ダンジョン発見数
		//・ボス討伐数
		//・撤退回数
		//・依頼達成数
		//・名声値


		void init()
		{
			種類 = WindowType::Record;
			名前 = "記録";
			略記 = "記録";
			アイコン = IconType::収支;
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