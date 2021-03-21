//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ギルドの情報*/
	class W_Config : public UIWindow
	{
		enum class ConfigType
		{
			BGM音量,
			SE音量,
			解像度,
			ウィンドウモード,
			装備更新,
			ボス戦等速,
			夜間加速,
			スキル習得停止,
			超加速,
			ヘルプ詳細,
		};

	private:		
		class GUI_設定 : public GUI_Object
		{
		public:
			ConfigType type;
			W_Config* 親;
			std::string 名前;
			std::string 設定値;
			IconType アイコン;

			void Set(const char* 名前, IconType アイコン, ConfigType 種類, W_Config* base)
			{
				this->親 = base;
				this->名前 = 名前;
				this->設定値 = 設定値;
				this->アイコン = アイコン;
				this->type = 種類;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px ,py }, (int)位置.GetW() , (int)位置.GetH(), 12);
				//MIcon::アイコン[アイコン].DrawRotate({px+Lp(11),py+Lp(12)},2,0);//アイコン表示削除

				MSystem::DrawWindow({ px + Lp(24) ,py + Lp(26) }, Lp(27), Lp(28), 0, 1);
				MSystem::DrawWindow({ px + Lp(25) ,py + Lp(26) }, Lp(27), Lp(28), 0, 1);


				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(13),py + Lp(15) },2,0);
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(14),py + Lp(15) },2,0,true);


				MFont::MAlias.DrawBold({ px + Lp(16) ,py + Lp(17) }, Color::White, Color::Black, 名前, false);

				switch (type)
				{
				case ConfigType::BGM音量:
					設定値 = std::to_string(親->仮_BGM設定 * 10);
					設定値 += " %";
					break;
				case ConfigType::SE音量:
					設定値 = std::to_string(親->仮_SE設定 * 10);
					設定値 += " %";
					break;
				case ConfigType::解像度:
					設定値 = std::to_string(親->仮_解像度 * 160);
					設定値 += " x ";
					設定値 += std::to_string(親->仮_解像度 * 90);
					break;
				case ConfigType::ウィンドウモード:
					設定値 = TX::Config_ウィンドウモード設定[(int)親->仮_ウィンドウモード];
					break;
				case ConfigType::装備更新:
					設定値 = TX::Config_装備更新_設定[親->仮_装備更新];
					break;
				case ConfigType::ボス戦等速:
					設定値 = TX::Config_ボス戦速度_設定[親->仮_ボス戦等速 ? 0 : 1];
					break;
				case ConfigType::夜間加速:
					設定値 = TX::Config_夜間加速_設定[親->仮_夜間加速 ? 0 : 1];
					break;
				case ConfigType::スキル習得停止:
					設定値 = TX::Config_スキル習得停止_設定[親->仮_スキル習得時停止 ? 0 : 1];
					break;
				case ConfigType::超加速:
					設定値 = TX::Config_超加速_設定[親->仮_超加速 ? 0 : 1];
					break;
				case ConfigType::ヘルプ詳細:
					設定値 = TX::Config_ヘルプ詳細_設定[親->仮_ヘルプ詳細 ? 0 : 1];
					break;
				}

				MFont::MAlias.DrawBold({ px + Lp(18) + MFont::MAlias.GetDrawStringWidth(設定値)/2 ,py + Lp(19) }, Color::White, Color::Black, { 設定値 }, true);
			}

			void Click(double px, double py)
			{
				int n = 0;

				if (px > Lp(24) && px < Lp(24) + Lp(27) && py > Lp(26) && py < Lp(26) + Lp(28))
				{
					n = -1;
					MSound::効果音[SE::ボタンクリック].Play();
				}
				if (px > Lp(25) && px < Lp(25) + Lp(27) && py > Lp(26) && py < Lp(26) + Lp(28))
				{
					n = +1;
					MSound::効果音[SE::ボタンクリック].Play();
				}

				if (n == 0) { return; }

				int buf = 0;
				switch (type)
				{
				case ConfigType::BGM音量:
					親->仮_BGM設定 += n;
					if (親->仮_BGM設定 < 0) { 親->仮_BGM設定 = 0; }
					if (親->仮_BGM設定 > 10) { 親->仮_BGM設定 = 10; }
					break;
				case ConfigType::SE音量:
					親->仮_SE設定 += n;
					if (親->仮_SE設定 < 0) { 親->仮_SE設定 = 0; }
					if (親->仮_SE設定 > 10) { 親->仮_SE設定 = 10; }
					break;
				case ConfigType::解像度:
					親->仮_解像度 += n;
					if (親->仮_解像度 < 8) { 親->仮_解像度 = 8; }
					if (親->仮_解像度 > 20) { 親->仮_解像度 = 20; }
					break;
				case ConfigType::ウィンドウモード:
					buf = (int)(親->仮_ウィンドウモード)+n;
					if (buf == (int)Config::WindowmodeType::COUNT) { buf = 0; }
					if (buf < 0) { buf = (int)Config::WindowmodeType::COUNT - 1; }
					親->仮_ウィンドウモード = Config::WindowmodeType(buf);
					break;
				case ConfigType::装備更新:
					親->仮_装備更新 = !親->仮_装備更新;
					break;
				case ConfigType::ボス戦等速:
					親->仮_ボス戦等速 = !親->仮_ボス戦等速;
					break;
				case ConfigType::夜間加速:
					親->仮_夜間加速 = !親->仮_夜間加速;
					break;
				case ConfigType::スキル習得停止:
					親->仮_スキル習得時停止 = !親->仮_スキル習得時停止;
					break;
				case ConfigType::超加速:
					親->仮_超加速 = !親->仮_超加速;
					break;
				case ConfigType::ヘルプ詳細:
					親->仮_ヘルプ詳細 = !親->仮_ヘルプ詳細;
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
				int dif_x = MFont::MAlias.GetDrawStringWidth( TX::Config_決定 ) / 2;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 0 , 1);
				MFont::MAlias.DrawBold({ px + Lp(20) - dif_x ,py + Lp(22) }, Color::White, Color::Black, TX::Config_決定 , false);
			}

			void Click(double px, double py)
			{
				//設定代入
				base->is表示 = false;

				Config::BGM設定 = base->仮_BGM設定;
				Config::SE設定 = base->仮_SE設定;
				Config::解像度設定 = base->仮_解像度;
				Config::ウィンドウモード = base->仮_ウィンドウモード;
				Config::is装備自動更新 = base->仮_装備更新;
				Config::isボス戦時等速 = base->仮_ボス戦等速;
				Config::is夜間加速 = base->仮_夜間加速;
				Config::isスキル習得時停止 = base->仮_スキル習得時停止;
				Config::is超加速モード = base->仮_超加速;
				Config::isヘルプ詳細 = base->仮_ヘルプ詳細;


				if (Config::is超加速モード == true)
				{
					Config::ゲーム速度変更倍率 = 4;
					Config::最大ゲーム倍速 = 64;
					Game::ゲームスピード = 1;
				} else {
					Config::ゲーム速度変更倍率 = 2;
					Config::最大ゲーム倍速 = 16;
					Game::ゲームスピード = 1;
				}

				Config::Update();

				MSound::効果音[SE::決定].Play();
			}

		};

		class GUI_キャンセル : public GUI_Object
		{
		public:
			W_Config* base;

			void Draw派生(double px, double py)
			{
				int dif_x = MFont::MAlias.GetDrawStringWidth( TX::Config_キャンセル ) / 2;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 0, 1);
				MFont::MAlias.DrawBold({ px + Lp(21) - dif_x ,py + Lp(22) }, Color::White, Color::Black, TX::Config_キャンセル, false);
			}

			void Click(double px, double py)
			{
				//設定変更反映せず終了
				base->is表示 = false;

				base->仮_BGM設定 = Config::BGM設定;
				base->仮_SE設定 = Config::SE設定;
				base->仮_解像度 = Config::解像度設定;


				MSound::効果音[SE::キャンセル].Play();
			}
		};

	public:

		GUI_設定 BGM音量;
		GUI_設定 SE音量;
		GUI_設定 解像度;

		GUI_設定 ウィンドウモード;
		GUI_設定 装備更新;
		GUI_設定 ボス戦等速;
		GUI_設定 夜間加速;
		GUI_設定 スキル習得停止;
		GUI_設定 超加速;
		GUI_設定 ヘルプ詳細;

		GUI_確定 確定;
		GUI_キャンセル キャンセル;

		int 仮_BGM設定;
		int 仮_SE設定;
		int 仮_解像度;
		Config::WindowmodeType 仮_ウィンドウモード;
		bool 仮_装備更新;
		bool 仮_ボス戦等速;
		bool 仮_夜間加速;
		bool 仮_スキル習得時停止;
		bool 仮_超加速;
		bool 仮_ヘルプ詳細;

		void Init()
		{
			種類 = WindowType::Config;

			アイコン = IconType::情報;
			横幅 = 320;
			縦幅 = 170;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;
			is閉じるボタン = false;
			isスクロールバー表示 = false;

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			//
			仮_BGM設定 = Config::BGM設定;
			仮_SE設定 = Config::SE設定;
			仮_解像度 = Config::解像度設定;
			仮_ウィンドウモード = Config::ウィンドウモード;
			仮_装備更新 = Config::is装備自動更新;
			仮_ボス戦等速 = Config::isボス戦時等速;
			仮_夜間加速 = Config::is夜間加速;
			仮_スキル習得時停止 = Config::isスキル習得時停止;
			仮_超加速 = Config::is超加速モード; 
			仮_ヘルプ詳細 = Config::isヘルプ詳細;

			BGM音量.Set( TX::Config_音楽.c_str() , IconType::BGM, ConfigType::BGM音量 , this);
			SE音量.Set( TX::Config_効果音.c_str() , IconType::効果音, ConfigType::SE音量, this);
			解像度.Set( TX::Config_解像度.c_str() , IconType::解像度, ConfigType::解像度 , this);
			ウィンドウモード.Set(TX::Config_ウィンドウモード.c_str(), IconType::解像度, ConfigType::ウィンドウモード, this);
			装備更新.Set(TX::Config_装備更新.c_str(), IconType::装備, ConfigType::装備更新, this);
			ボス戦等速.Set(TX::Config_ボス戦速度.c_str(), IconType::ボス, ConfigType::ボス戦等速, this);
			夜間加速.Set(TX::Config_夜間加速.c_str(), IconType::時間, ConfigType::夜間加速, this);
			スキル習得停止.Set(TX::Config_スキル習得停止.c_str(), IconType::時間, ConfigType::スキル習得停止, this);
			超加速.Set(TX::Config_超加速.c_str(), IconType::時間, ConfigType::超加速, this);
			ヘルプ詳細.Set(TX::Config_ヘルプ詳細.c_str(), IconType::ヘルプ, ConfigType::ヘルプ詳細, this);

			確定.base = this;
			キャンセル.base = this;
		}

		void GUI_Update()
		{
		}
	};
}