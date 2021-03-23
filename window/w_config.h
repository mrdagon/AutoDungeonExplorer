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
		class UI設定 : public UIObject
		{
		public:
			ConfigType type;

			IconType アイコン;
			std::string 名前;
			std::string 設定値;
			UIImageButton 増加ボタン;
			UIImageButton 減少ボタン;

			W_Config* 親;

			void Set(const char* 名前, IconType アイコン, ConfigType 種類, W_Config* base)
			{
				this->親 = base;
				this->名前 = 名前;
				this->アイコン = アイコン;
				this->type = 種類;

				増加ボタン.SetUI(&MIcon::UI[IconType::三角], &UIDesign::Brown, UIコンフィグ::設定増減, 1);
				減少ボタン.SetUI(&MIcon::UI[IconType::三角], &UIDesign::Brown, UIコンフィグ::設定増減, 0);
			}

			bool Check派生(double px,double py) override
			{
				if (増加ボタン.CheckInput(px, py) == true) { return true; }
				if (減少ボタン.CheckInput(px, py) == true) { return true; }

				return false;
			}

			void Draw派生()
			{
				auto posA = UILayout::Data(UIコンフィグ::設定アイコン);
				auto posB = UILayout::Data(UIコンフィグ::設定項目名);
				auto posC = UILayout::Data(UIコンフィグ::設定数値);

				UIDesign::Brown.Draw(UIType::グループ明, UILayout::Data(UIコンフィグ::設定ボタン));

				MIcon::UI[アイコン].DrawRotate({ posA.x , posB.x },2,0);//アイコン表示削除

				MFont::MAlias.DrawRotate({ posB.x , posB.x } , 1 , 0, Color::Black, 名前, false);

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

				MFont::MAlias.DrawRotate({ posC.x , posC.y } , 1 , 0 , Color::Black, { 設定値 }, true);

				増加ボタン.Draw();
				減少ボタン.Draw();
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

			//レイアウト値
			確定.SetUI("決定", &UIDesign::Brown, UIコンフィグ::決定_キャンセル, 0);
			キャンセル.SetUI("キャンセル", &UIDesign::Brown, UIコンフィグ::決定_キャンセル, 1);


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
			ウィンドウモード.Set(TX::Config_ウィンドウモード.c_str(), IconType::解像度, ConfigType::ウィンドウモード, this);
			BGM音量.Set( TX::Config_音楽.c_str() , IconType::BGM, ConfigType::BGM音量 , this);
			SE音量.Set( TX::Config_効果音.c_str() , IconType::効果音, ConfigType::SE音量, this);
			解像度.Set( TX::Config_解像度.c_str() , IconType::解像度, ConfigType::解像度 , this);
			解像度X倍.Set(TX::Config_音楽.c_str(), IconType::BGM, ConfigType::BGM音量, this);

			ボス戦等速.Set(TX::Config_ボス戦速度.c_str(), IconType::ボス, ConfigType::ボス戦等速, this);
			夜加速.Set(TX::Config_夜間加速.c_str(), IconType::時間, ConfigType::夜加速, this);
			超加速.Set(TX::Config_超加速.c_str(), IconType::時間, ConfigType::超加速, this);
			フォント種.Set(TX::Config_ヘルプ詳細.c_str(), IconType::ヘルプ, ConfigType::フォント, this);

			ウィンドウモード.SetUI(UIコンフィグ::設定ボタン, 0);
			BGM音量.SetUI(UIコンフィグ::設定ボタン, 1);
			SE音量.SetUI(UIコンフィグ::設定ボタン, 2);
			解像度.SetUI(UIコンフィグ::設定ボタン, 3);
			解像度X倍.SetUI(UIコンフィグ::設定ボタン, 4);
			ボス戦等速.SetUI(UIコンフィグ::設定ボタン, 5);
			夜加速.SetUI(UIコンフィグ::設定ボタン, 6);
			超加速.SetUI(UIコンフィグ::設定ボタン, 7);
			フォント種.SetUI(UIコンフィグ::設定ボタン, 8);

			確定.clickEvent = [&](){
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
			キャンセル.clickEvent = [&](){
				//設定変更反映せず終了
				is表示 = false;
				Config::Update();
				MSound::効果音[SE::キャンセル].Play();
			};

			ウィンドウモード.増加ボタン.clickEvent = [&]()
			{
				仮_ウィンドウモード = !仮_ウィンドウモード;
			};
			ウィンドウモード.減少ボタン.clickEvent = [&]()
			{
				仮_ウィンドウモード = !仮_ウィンドウモード;
			};

			BGM音量.増加ボタン.clickEvent = [&]()
			{
				仮_BGM設定 += 1;
				if (仮_BGM設定 > 10) { 仮_BGM設定 = 10; }
			};
			BGM音量.減少ボタン.clickEvent = [&]()
			{
				仮_BGM設定 -= 1;
				if (仮_BGM設定 < 0) { 仮_BGM設定 = 0; }
			};

			SE音量.増加ボタン.clickEvent = [&]()
			{
				仮_SE設定 += 1;
				if ( 仮_SE設定 > 10) { 仮_SE設定 = 10; }
			};
			SE音量.減少ボタン.clickEvent = [&]()
			{
				仮_SE設定 -= 1;
				if ( 仮_SE設定 < 0) { 仮_SE設定 = 0; }
			};

			解像度.増加ボタン.clickEvent = [&]()
			{
				仮_解像度 += 1;
				if (仮_解像度 < 8) { 仮_解像度 = 8; }
			};
			解像度.減少ボタン.clickEvent = [&]()
			{
				仮_解像度 -= 1;
				if (仮_解像度 > 20) { 仮_解像度 = 20; }
			};

			解像度X倍.増加ボタン.clickEvent = [&]()
			{
				仮_解像度X倍 += 1;
				if (仮_解像度X倍 < 1) { 仮_解像度 = 1; }
			};
			解像度X倍.減少ボタン.clickEvent = [&]()
			{
				仮_解像度X倍 -= 1;
				if (仮_解像度X倍 > 4) { 仮_解像度 = 4; }
			};


			ボス戦等速.増加ボタン.clickEvent = [&]()
			{
				仮_ボス戦等速 = !仮_ボス戦等速;
			};
			ボス戦等速.減少ボタン.clickEvent = [&]()
			{
				仮_ボス戦等速 = !仮_ボス戦等速;
			};

			夜加速.増加ボタン.clickEvent = [&]()
			{
				仮_夜加速 = !仮_夜加速;
			};
			夜加速.減少ボタン.clickEvent = [&]()
			{
				仮_夜加速 = !仮_夜加速;
			};

			超加速.増加ボタン.clickEvent = [&]()
			{
				仮_超加速 = !仮_超加速;
			};
			超加速.減少ボタン.clickEvent = [&]()
			{
				仮_超加速 = !仮_超加速;
			};

			フォント種.増加ボタン.clickEvent = [&]()
			{
				仮_フォント種 = !仮_フォント種;
			};
			フォント種.減少ボタン.clickEvent = [&]()
			{
				仮_フォント種 = !仮_フォント種;
			};

			//オブジェクトを登録
			AddItem(BGM音量);
			AddItem(ウィンドウモード);
			AddItem(BGM音量);
			AddItem(SE音量);
			AddItem(解像度);
			AddItem(解像度X倍);

			AddItem(ボス戦等速);
			AddItem(夜加速);
			AddItem(超加速);
			AddItem(フォント種);

			AddItem(確定);
			AddItem(キャンセル);
		}

		void Update()
		{
			SetPos(UIコンフィグ::ウィンドウ, true, false);
		}
	};
}