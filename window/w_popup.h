//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*汎用２択ポップアップウィンドウ*/
	class W_Popup : public UIWindow
	{
	public:

		UITextFrame 文章;

		UIButton 確定;
		UIButton キャンセル;

		void Init()
		{
			Set(WindowType::Config, &UIDesign::Brown, IconType::情報);

			横幅 = UILayout::Data(UI基本::ポップアップ_ウィンドウ).w;
			縦幅 = UILayout::Data(UI基本::ポップアップ_ウィンドウ).h;
			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;

			is閉じるボタン = false;
			isスクロールバー表示 = false;

			文章.SetUI("テキスト未設定", &UIDesign::Brown, UI基本::ポップアップ_説明);
			確定.SetUI("はい", &UIDesign::Brown, UI基本::ポップアップ_はい);
			キャンセル.SetUI("いいえ", &UIDesign::Brown, UI基本::ポップアップ_いいえ);

			確定.clickEvent = [&](double x, double y)
			{
				is表示 = false;
				ポップアップリザルト = 1;
			};

			キャンセル.clickEvent = [&](double x, double y)
			{
				is表示 = false;
				ポップアップリザルト = 0;
			};

			ui_objects.push_back(&文章);
			ui_objects.push_back(&確定);
			ui_objects.push_back(&キャンセル);
		}

		void Update()
		{
			横幅 = UILayout::Data(UI基本::ポップアップ_ウィンドウ).w;
			縦幅 = UILayout::Data(UI基本::ポップアップ_ウィンドウ).h;
			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;
		}
	};
}