//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[20][a]

	/*ポップアップウィンドウ用*/
	class W_Popup : public WindowBox
	{
	private:
		class GUI_文字 : public GUI_Object
		{
		public:
			std::string 文章;


			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12, 0);

				MFont::BMSize.DrawBold({ px + LV(9) ,py + LV(10) }, Color::White, Color::Black, { 文章 }, true);
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

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), LV(13),1);
				MFont::BMSize.DrawBold({ px + LV(11) - dif_x ,py + LV(12) }, Color::White, Color::Black, 文字, false);
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

			文章.文章 = "アンケートに答えますか？\n(ブラウザを開きます)";
			確定.文字 = "はい";
			キャンセル.文字 = "いいえ";

			確定.base = this;
			キャンセル.base = this;
			確定.id = 0;
			キャンセル.id = 1;

			gui_objects.push_back(&文章);
			gui_objects.push_back(&確定);
			gui_objects.push_back(&キャンセル);
		}

		void GUI_Init()
		{
			文章.位置 = { LV(0),LV(1) ,LV(2),LV(3) };
			確定.位置 = { LV(4),LV(6),LV(7),LV(8) };
			キャンセル.位置 = { LV(5),LV(6) , LV(7),LV(8) };
		}

		void 派生Draw()
		{
			GUI_Init();

			for (auto& it : gui_objects)
			{
				it->Draw();
			}

		}

		bool 派生操作()
		{
			for (auto& it : gui_objects)
			{
				it->操作チェック(相対座標.x, 相対座標.y);
			}

			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}