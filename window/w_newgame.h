//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*難易度選択ポップアップウィンドウ*/
	class W_Newgame : public WindowBox
	{
	private:

		class GUI_ボタン : public GUI_Object
		{
		public:
			W_Newgame* 親;
			GameType 難易度;
			std::string 文字;

			void Draw派生(double px, double py)
			{
				int 凹み = (親->選択中難易度 == 難易度) ? 2 : 0 ;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 凹み , 1 - 凹み);
				MFont::BMSize.DrawBoldRotate({ px + 位置.GetW() / 2 , py + 位置.GetH() / 2 } , 1 , 0, Color::White, Color::Black, 文字, false);
			}

			void Click(double px, double py)
			{
				if (親->選択中難易度 == 難易度)
				{
					親->選択中難易度 = GameType::COUNT;					
				} else {
					親->選択中難易度 = 難易度;
				}
			}

			void Over(double px, double py)
			{
				親->マウスオーバー中難易度 = 難易度;
			}
		};

		class GUI_開始ボタン : public GUI_Object
		{
		public:
			W_Newgame* 親;
			std::string 文字;

			void Draw派生(double px, double py)
			{
				int 凹み = (親->選択中難易度 == GameType::COUNT) ? 0 : 1;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1 - 凹み, 凹み);
				MFont::BMSize.DrawBoldRotate({ px + 位置.GetW() / 2 , py + 位置.GetH() / 2 }, 1, 0, Color::White, Color::Black, 文字, false);
			}

			void Click(double px, double py)
			{
				if (親->選択中難易度 == GameType::COUNT) { return; }
				親->is表示 = false;
				親->ポップアップ戻り値 = 1;
			}
		};

		class GUI_説明 : public GUI_Object
		{
		public:
			W_Newgame* 親;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 10, 0);

				if (親->選択中難易度 == GameType::COUNT && 親->マウスオーバー中難易度 == GameType::COUNT) { return; }

				const std::string 文字 = "難易度の説明(仮)\n（※現在はどの難易度も共通）";
				
				MFont::BMSize.DrawBold({ px + Lp(23) ,py + Lp(24) }, Color::White, Color::Black, 文字, false);
			}
		};

	public:
		GUI_ボタン 難易度ボタン[(int)GameType::COUNT];

		GUI_開始ボタン 開始;

		GUI_説明 説明;

		GameType 選択中難易度 = GameType::COUNT;
		GameType マウスオーバー中難易度 = GameType::COUNT;

		void Init()
		{
			gui_objects.clear();
			種類 = WindowType::Newgame;

			名前 = "難易度選択";
			略記 = "難易度選択";
			アイコン = IconType::情報;
			横幅 = 280;
			縦幅 = 170;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;
			isスクロールバー表示 = false;
			ポップアップ戻り値 = 0;

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			gui_objects.push_back(&開始);
			gui_objects.push_back(&説明);

			int a = 0;
			for (auto& it : 難易度ボタン)
			{
				it.親 = this;
				it.難易度 = GameType(a);
				gui_objects.push_back(&it);
				a++;
			}
			難易度ボタン[0].文字 = "ノーマル";
			//難易度ボタン[1].文字 = "ハードコア";
			難易度ボタン[1].文字 = "デスマーチ";

			開始.文字 = "決定";

			開始.親 = this;
			説明.親 = this;


			選択中難易度 = GameType::COUNT;
			マウスオーバー中難易度 = GameType::COUNT;

			SetCSVPage(24);
		}

		void GUI_Update()
		{

			横幅 = Lp(10);
			縦幅 = Lp(11);

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			開始.位置 = { Lp(12),Lp(13),Lp(14),Lp(15) };

			説明.位置 = { Lp(16),Lp(17),Lp(18),Lp(19) };

			int a = 0;
			for (auto& it : 難易度ボタン)
			{
				it.位置 = { Lp(20),Lp(21)+Lp(22)*a,Lp(14),Lp(15) };
				a++;
			}
		}
	};
}