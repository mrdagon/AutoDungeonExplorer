//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[16][a]



	/*ギルドの情報*/
	class W_Config : public WindowBox
	{
	private:
		class GUI_数値 : public GUI_Object
		{
		public:
			W_Config* base;
			std::string 名前;
			std::string 設定値;
			IconType アイコン;
			int id;//0 BGM,1効果音,2解像度


			void Set(const char* 名前, const char* 設定値, IconType アイコン, int id, W_Config* base)
			{
				this->名前 = 名前;
				this->設定値 = 設定値;
				this->アイコン = アイコン;
				this->id = id;
				this->base = base;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px ,py }, (int)位置.GetW() , (int)位置.GetH(), 12);
				MIcon::アイコン[アイコン].DrawRotate({px+LV(11),py+LV(12)},2,0);

				MSystem::DrawWindow({ px + LV(24) ,py + LV(26) }, LV(27), LV(28), LV(23), 1);
				MSystem::DrawWindow({ px + LV(25) ,py + LV(26) }, LV(27), LV(28), LV(23), 1);


				MIcon::アイコン[IconType::三角].DrawRotate({ px + LV(13),py + LV(15) },2,0);
				MIcon::アイコン[IconType::三角].DrawRotate({ px + LV(14),py + LV(15) },2,0,true);


				MFont::BMSize.DrawBold({ px + LV(16) ,py + LV(17) }, Color::White, Color::Black, 名前, false);

				switch (id)
				{
				case 0:
					設定値 = std::to_string(base->BGM設定仮 * 10);
					設定値 += " %";
					break;
				case 1:
					設定値 = std::to_string(base->SE設定仮 * 10);
					設定値 += " %";
					break;
				case 2:
					設定値 = std::to_string(base->解像度仮 * 160);
					設定値 += " x ";
					設定値 += std::to_string(base->解像度仮 * 90);
					break;
				}

				MFont::BMSize.DrawBold({ px + LV(18) + MFont::BMSize.GetDrawStringWidth(設定値)/2 ,py + LV(19) }, Color::White, Color::Black, { 設定値 }, true);
			}

			void Click(double px, double py)
			{
				int n = 0;

				if (px > LV(24) && px < LV(24) + LV(27) && py > LV(26) && py < LV(26) + LV(28))
				{
					n = -1;
					MSound::効果音[SE::ボタンクリック].Play();
				}
				if (px > LV(25) && px < LV(25) + LV(27) && py > LV(26) && py < LV(26) + LV(28))
				{
					n = +1;
					MSound::効果音[SE::ボタンクリック].Play();
				}

				switch (id)
				{
				case 0:
					base->BGM設定仮 += n;
					if (base->BGM設定仮 < 0) { base->BGM設定仮 = 0; }
					if (base->BGM設定仮 > 10) { base->BGM設定仮 = 10; }
					break;
				case 1:
					base->SE設定仮 += n;
					if (base->SE設定仮 < 0) { base->SE設定仮 = 0; }
					if (base->SE設定仮 > 10) { base->SE設定仮 = 10; }
					break;
				case 2:
					base->解像度仮 += n;
					if (base->解像度仮 < 8) { base->解像度仮 = 8; }
					if (base->解像度仮 > 20) { base->解像度仮 = 20; }
					break;
				}


			}
		};

		class GUI_確定 : public GUI_Object
		{
		public:
			W_Config* base;

			void Draw派生(double px, double py)
			{
				int dif_x = MFont::BMSize.GetDrawStringWidth( TX::Config_決定 ) / 2;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), LV(23),1);
				MFont::BMSize.DrawBold({ px + LV(20) - dif_x ,py + LV(22) }, Color::White, Color::Black, TX::Config_決定 , false);
			}

			void Click(double px, double py)
			{
				//設定変更反映して終了
				base->is表示 = false;

				Game::BGM設定 = base->BGM設定仮;
				Game::SE設定 = base->SE設定仮;
				Game::解像度設定 = base->解像度仮;

				Game::解像度W = Game::解像度設定 * 160;
				Game::解像度H = Game::解像度設定 * 90;
				Game::解像度W = std::min(Game::解像度W, Game::最大解像度W);
				Game::解像度H = std::min(Game::解像度H, Game::最大解像度H);

				Game::BGM音量 = Game::BGM設定 * Game::BGM設定 / 100.0;
				Game::SE音量 = Game::SE設定 * Game::SE設定 / 100.0;

				Window::SetSize(Game::解像度W, Game::解像度H);

				Window::SetFullscreen(Game::解像度W == Game::最大解像度W && Game::解像度H == Game::最大解像度H);

				base->座標.x = Window::GetWidth() / 2 - base->横幅 / 2;
				base->座標.y = Window::GetHeight() / 2 - base->縦幅 / 2;

				Sound::SetMainVolume(Game::SE音量);
				Music::SetMainVolume(Game::BGM音量);

				MSound::効果音[SE::決定].Play();

			}

		};

		class GUI_キャンセル : public GUI_Object
		{
		public:
			W_Config* base;

			void Draw派生(double px, double py)
			{
				int dif_x = MFont::BMSize.GetDrawStringWidth( TX::Config_キャンセル ) / 2;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), LV(23), 1);
				MFont::BMSize.DrawBold({ px + LV(21) - dif_x ,py + LV(22) }, Color::White, Color::Black, TX::Config_キャンセル, false);
			}

			void Click(double px, double py)
			{
				//設定変更反映せず終了
				base->is表示 = false;

				base->BGM設定仮 = Game::BGM設定;
				base->SE設定仮 = Game::SE設定;
				base->解像度仮 = Game::解像度設定;


				MSound::効果音[SE::キャンセル].Play();
			}
		};

	public:

		GUI_数値 BGM音量;
		GUI_数値 SE音量;
		GUI_数値 解像度;

		GUI_確定 確定;
		GUI_キャンセル キャンセル;

		int BGM設定仮, SE設定仮, 解像度仮;

		void init()
		{
			種類 = WindowType::Config;

			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::情報;
			横幅 = 320;
			縦幅 = 170;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;
			isポップアップ = true;

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			BGM設定仮 = Game::BGM設定;
			SE設定仮 = Game::SE設定;
			解像度仮 = Game::解像度設定;

			BGM音量.Set( TX::Config_音楽.c_str() ,"50 %",IconType::BGM,0,this);
			SE音量.Set( TX::Config_効果音.c_str() ,"50 %", IconType::効果音, 1, this);
			解像度.Set( TX::Config_解像度.c_str() ,"1600 x 900", IconType::解像度, 2, this);

			gui_objects.resize(0);

			gui_objects.push_back(&BGM音量);
			gui_objects.push_back(&SE音量);
			gui_objects.push_back(&解像度);
			gui_objects.push_back(&確定);
			gui_objects.push_back(&キャンセル);

			確定.base = this;
			キャンセル.base = this;
		}

		void GUI_Init()
		{

			解像度.位置 = { LV(0),LV(1) ,LV(4),LV(5) };
			BGM音量.位置 = { LV(0),LV(2),LV(4),LV(5) };
			SE音量.位置 = { LV(0),LV(3),LV(4),LV(5) };
			確定.位置 = { LV(6),LV(8),LV(9),LV(10) };
			キャンセル.位置 = { LV(7),LV(8) , LV(9),LV(10) };
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