//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ポップアップウィンドウ用*/
	class W_TextInput : public WindowBox
	{
	private:
		class GUI_文字 : public GUI_Object
		{
		public:
			std::string 文章;


			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12, 0);

				MFont::BMSize.DrawBold({ px + Lp(9) ,py + Lp(10) }, Color::White, Color::Black, { 文章 }, true);
			}
		};

		class GUI_ボタン : public GUI_Object
		{
		public:
			int id;
			W_Popup* base;
			std::string 文字;

			void Draw派生(double px, double py)
			{
				int dif_x = MFont::BMSize.GetDrawStringWidth(文字) / 2;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Lp(13),1);
				MFont::BMSize.DrawBold({ px + Lp(11) - dif_x ,py + Lp(12) }, Color::White, Color::Black, 文字, false);
			}

			void Click(double px, double py)
			{
				base->is表示 = false;
				base->ポップアップ戻り値 = id;
			}

		};

	public:

		GUI_文字 文章;

		GUI_ボタン 確定;
		GUI_ボタン キャンセル;

		void init()
		{
			種類 = WindowType::Guild;

			名前 = "確認";
			略記 = "確認";
			アイコン = IconType::情報;
			横幅 = 280;
			縦幅 = 170;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;
			isポップアップ = true;

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			文章.文章 = "ゲームを終了しますか？";
			確定.文字 = "はい";
			キャンセル.文字 = "いいえ";

			確定.base = this;
			キャンセル.base = this;
			確定.id = 0;
			キャンセル.id = 1;

			gui_objects.push_back(&文章);
			gui_objects.push_back(&確定);
			gui_objects.push_back(&キャンセル);

			SetCSVPage(20);
		}

		void GUI_Init()
		{
			文章.位置 = { Lp(0),Lp(1) ,Lp(2),Lp(3) };
			確定.位置 = { Lp(4),Lp(6),Lp(7),Lp(8) };
			キャンセル.位置 = { Lp(5),Lp(6) , Lp(7),Lp(8) };
		}
	};
}