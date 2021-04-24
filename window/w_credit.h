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
			Set(WindowType::Credit, IconType::情報);
			SetPos(LTitle::クレジット_ウィンドウ, true , true , true);
			縦内部幅 = std::max(縦幅, Layout::Data(LTitle::クレジット_説明枠).h + 16);

			//●初期化
			文章.SetUI( LTitle::クレジット_説明枠 , "付属テキストの内容を表示\nあああああ\nああ\nあ");

			//●登録
			item.clear();
			AddItem(文章);
		}

		void Update()
		{
			SetPos(LTitle::クレジット_ウィンドウ, true , true , true);
			縦内部幅 = std::max(縦幅, Layout::Data(LTitle::クレジット_説明枠).h + 16);
		}
	};
}