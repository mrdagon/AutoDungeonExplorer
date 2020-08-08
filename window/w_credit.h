//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*汎用２択ポップアップウィンドウ用*/
	class W_Credit : public WindowBox
	{
	private:
		class GUI_文字 : public GUI_Object
		{
		public:
			std::string text;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 10, 0);
				MFont::BMSize.DrawBold({ px + Lp(35) ,py + Lp(35) }, Color::White, Color::Black, { text }, false);
			}
		};

	public:

		GUI_文字 文章;

		void Init()
		{
			gui_objects.clear();
			種類 = WindowType::Guild;

			名前 = "クレジット";
			略記 = "クレジット";
			アイコン = IconType::情報;
			横幅 = 280;
			縦幅 = 170;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			文章.text = "付属ドキュメントに書いてます（仮）\n";

			gui_objects.push_back(&文章);


			SetCSVPage(24);
		}

		void GUI_Update()
		{
			横幅 = Lp(30);
			縦幅 = Lp(31);

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			文章.位置 = { Lp(32),Lp(32) , 横幅 - Lp(33), 縦幅 - Lp(34) };
		}
	};
}