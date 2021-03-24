//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*汎用２択ポップアップウィンドウ用*/
	class W_Credit : public UIWindow
	{
	public:

		UITextFrame 文章;

		void Init()
		{
			Set(WindowType::Config, IconType::情報);
			SetPos(UIタイトル::クレジット_ウィンドウ, true , true);

			縦内部幅 = std::max(縦幅, UILayout::Data(UIタイトル::クレジット_説明枠).h + 16);

			文章.SetUI("付属テキストの内容を表示\nあああああ\nああ\nあ" , UIタイトル::クレジット_説明枠);

			AddItem(文章);
		}

		void Update()
		{
			SetPos(UIタイトル::クレジット_ウィンドウ, true , true);
			縦内部幅 = std::max(縦幅, UILayout::Data(UIタイトル::クレジット_説明枠).h + 16);
		}
	};
}