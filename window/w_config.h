//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	enum class UIコンフィグ
	{
		ウィンドウ,
		決定_キャンセル,
		設定ボタン,
		設定アイコン,//子項目４つ
		設定項目名,
		設定数値,
		設定増減,
		COUNT,
		PAGE = (int)UIPage::コンフィグ
	};


	/*ギルドの情報*/
	class W_Config : public UIWindow
	{
		enum class ConfigType
		{
			BGM音量,
			SE音量,
			解像度,
			ウィンドウモード,
			解像度X倍,

			ボス戦等速,
			夜加速,
			超加速,
			フォント
		};

	private:
		//UIImageButtonを追加
		class UI増減ボタン : public UIObject
		{
		public:
		};

		class UI設定 : public UIObject
		{
		public:
			ConfigType type;

			IconType アイコン;
			std::string 名前;
			std::string 設定値;
			UI増減ボタン 増加;
			UI増減ボタン 減少;

			W_Config* 親;

			void Set(const char* 名前, IconType アイコン, ConfigType 種類, W_Config* base)
			{
				this->親 = base;
				this->名前 = 名前;
				this->アイコン = アイコン;
				this->type = 種類;
			}

			bool Check派生(double px,double py) override
			{
				if (増加.CheckInput(px, py) == true) { return true; }
				if (減少.CheckInput(px, py) == true) { return true; }

				return false;
			}

			void Draw派生()
			{
				//MSystem::DrawWindow({ px ,py }, (int)位置.GetW() , (int)位置.GetH(), 12);
				//MIcon::アイコン[アイコン].DrawRotate({px+Lp(11),py+Lp(12)},2,0);//アイコン表示削除

				//MFont::MAlias.DrawBold({ px + Lp(16) ,py + Lp(17) }, Color::White, Color::Black, 名前, false);

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
				case ConfigType::解像度X倍:
					設定値 = std::to_string(親->仮_解像度 * 160);
					設定値 += " x ";
					設定値 += std::to_string(親->仮_解像度 * 90);
					break;
				case ConfigType::ウィンドウモード:
					設定値 = TX::Config_ウィンドウモード設定[(int)親->仮_ウィンドウモード];
					break;
				case ConfigType::ボス戦等速:
					設定値 = TX::Config_ボス戦速度_設定[親->仮_ボス戦等速 ? 0 : 1];
					break;
				case ConfigType::夜加速:
					設定値 = TX::Config_夜間加速_設定[親->仮_夜加速 ? 0 : 1];
					break;
				case ConfigType::超加速:
					設定値 = TX::Config_超加速_設定[親->仮_超加速 ? 0 : 1];
					break;
				case ConfigType::フォント:
					設定値 = TX::Config_超加速_設定[親->仮_超加速 ? 0 : 1];
					break;
				}

				//MFont::MAlias.DrawBold({ px + Lp(18) + MFont::MAlias.GetDrawStringWidth(設定値)/2 ,py + Lp(19) }, Color::White, Color::Black, { 設定値 }, true);


				増加.Draw();
				減少.Draw();
			}

			void Click(double px, double py)
			{
				int n = 0;

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
					親->仮_ウィンドウモード = !親->仮_ウィンドウモード;
					break;
				case ConfigType::ボス戦等速:
					親->仮_ボス戦等速 = !親->仮_ボス戦等速;
					break;
				case ConfigType::夜加速:
					親->仮_夜加速 = !親->仮_夜加速;
					break;
				case ConfigType::超加速:
					親->仮_超加速 = !親->仮_超加速;
					break;
				}
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

			}
		};

	public:
		UI設定 ウィンドウモード;
		UI設定 BGM音量;
		UI設定 SE音量;
		UI設定 解像度;
		UI設定 解像度X倍;

		UI設定 ボス戦等速;
		UI設定 夜加速;
		UI設定 超加速;
		UI設定 フォント種;

		UIButton 確定;
		UIButton キャンセル;

		bool 仮_ウィンドウモード;
		int 仮_BGM設定;
		int 仮_SE設定;
		int 仮_解像度;
		int 仮_解像度X倍;

		bool 仮_ボス戦等速;
		bool 仮_夜加速;
		bool 仮_超加速;
		bool 仮_フォント種;

		void Init()
		{
			//基本Window設定
			Set(WindowType::Config, &UIDesign::Brown, IconType::情報);
			SetPos(UIコンフィグ::ウィンドウ, true, false);
			is閉じるボタン = false;

			//仮数値に現在の設定を代入
			仮_BGM設定 = Config::BGM設定;
			仮_SE設定 = Config::SE設定;
			仮_解像度 = Config::解像度設定;
			仮_ウィンドウモード = Config::isウィンドウ;
			仮_解像度X倍 = Config::解像度X倍;

			仮_ボス戦等速 = Config::isボス戦時等速;
			仮_夜加速 = Config::is夜加速;
			仮_超加速 = Config::is超加速; 
			仮_フォント種 = Config::isドットフォント;

			//設定値、代入
			BGM音量.Set( TX::Config_音楽.c_str() , IconType::BGM, ConfigType::BGM音量 , this);
			SE音量.Set( TX::Config_効果音.c_str() , IconType::効果音, ConfigType::SE音量, this);
			解像度.Set( TX::Config_解像度.c_str() , IconType::解像度, ConfigType::解像度 , this);
			ウィンドウモード.Set(TX::Config_ウィンドウモード.c_str(), IconType::解像度, ConfigType::ウィンドウモード, this);
			解像度X倍.Set(TX::Config_音楽.c_str(), IconType::BGM, ConfigType::BGM音量, this);

			ボス戦等速.Set(TX::Config_ボス戦速度.c_str(), IconType::ボス, ConfigType::ボス戦等速, this);
			夜加速.Set(TX::Config_夜間加速.c_str(), IconType::時間, ConfigType::夜加速, this);
			超加速.Set(TX::Config_超加速.c_str(), IconType::時間, ConfigType::超加速, this);
			フォント種.Set(TX::Config_ヘルプ詳細.c_str(), IconType::ヘルプ, ConfigType::フォント, this);

			確定.clickEvent = [&](double x, double y){
				is表示 = false;

				Config::BGM設定 = 仮_BGM設定;
				Config::SE設定 = 仮_SE設定;
				Config::解像度設定 = 仮_解像度;
				Config::isウィンドウ = 仮_ウィンドウモード;

				Config::isボス戦時等速 = 仮_ボス戦等速;
				Config::is夜加速 = 仮_夜加速;
				Config::is超加速 = 仮_超加速;

				Config::Update();

				MSound::効果音[SE::決定].Play();
			};
			キャンセル.clickEvent = [&](double x, double y) {
				//設定変更反映せず終了
				is表示 = false;

				//仮_BGM設定 = Config::BGM設定;
				//仮_SE設定 = Config::SE設定;
				//仮_解像度 = Config::解像度設定;

				MSound::効果音[SE::キャンセル].Play();
			};

			//オブジェクトを登録
			AddItem(BGM音量);
		}
	};
}