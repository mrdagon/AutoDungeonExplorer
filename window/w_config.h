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
			UIButton 増加ボタン;
			UIButton 減少ボタン;

			W_Config* 親;

			void Set(const char* 名前, IconType アイコン, ConfigType 種類, W_Config* base)
			{
				this->親 = base;
				this->名前 = 名前;
				this->アイコン = アイコン;
				this->type = 種類;

				増加ボタン.SetUI(LConfig::設定増減, &MIcon::UI[IconType::三角],  1,this);
				減少ボタン.SetUI(LConfig::設定増減, &MIcon::UI[IconType::三角],  0,this);
			}

			bool Check派生(double px,double py) override
			{
				if (増加ボタン.CheckInput(px, py) == true) { return true; }
				if (減少ボタン.CheckInput(px, py) == true) { return true; }

				return false;
			}

			void Draw派生()
			{

				auto posA = Layout::Data(LConfig::設定アイコン);
				auto posB = Layout::Data(LConfig::設定項目名);
				auto posC = Layout::Data(LConfig::設定数値);

				//UIDesign::Brown.Draw(UIType::背景, UILayout::Data(UIコンフィグ::設定ボタン));
				DrawUI(UIType::丸フレーム, Design::No1);

				MIcon::UI[アイコン].DrawRotate({ GetX() + posA.x , GetY() + posA.y },2,0);//アイコン表示削除

				MFont::L->DrawRotate({ GetX() + posB.x , GetY() + posB.y } , 1 , 0, Color::Black, 名前, false);

				MFont::L->DrawRotate({ GetX() + posC.x , GetY() + posC.y } , 1 , 0 , Color::Black, { 設定値 }, true);

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
			Set(WindowType::Config, IconType::情報);
			SetPos(LConfig::ウィンドウ, true, false , true);


			//●仮数値に現在の設定を代入
			仮_BGM設定 = Config::BGM設定;
			仮_SE設定 = Config::SE設定;
			仮_解像度 = Config::解像度設定;
			仮_ウィンドウモード = Config::isウィンドウ;
			仮_解像度X倍 = Config::解像度X倍;

			仮_ボス戦等速 = Config::isボス戦時等速;
			仮_夜加速 = Config::is夜加速;
			仮_超加速 = Config::is超加速; 
			仮_フォント種 = Config::isドットフォント;

			//●初期化
			確定.SetUI(LConfig::決定_キャンセル, "決定",  0);
			キャンセル.SetUI(LConfig::決定_キャンセル, "キャンセル",  1);

			ウィンドウモード.Set(TX::Config_ウィンドウモード.c_str(), IconType::解像度, ConfigType::ウィンドウモード, this);
			BGM音量.Set( TX::Config_音楽.c_str() , IconType::BGM, ConfigType::BGM音量 , this);
			SE音量.Set( TX::Config_効果音.c_str() , IconType::効果音, ConfigType::SE音量, this);
			解像度.Set( TX::Config_解像度.c_str() , IconType::解像度, ConfigType::解像度 , this);
			解像度X倍.Set(TX::Config_解像度X倍.c_str(), IconType::解像度, ConfigType::BGM音量, this);

			ボス戦等速.Set(TX::Config_ボス戦速度.c_str(), IconType::ボス, ConfigType::ボス戦等速, this);
			夜加速.Set(TX::Config_夜間加速.c_str(), IconType::時間, ConfigType::夜加速, this);
			超加速.Set(TX::Config_超加速.c_str(), IconType::時間, ConfigType::超加速, this);
			フォント種.Set(TX::Config_フォント種.c_str(), IconType::ヘルプ, ConfigType::フォント, this);

			ウィンドウモード.SetUI(LConfig::設定ボタン, 0);
			解像度.SetUI(LConfig::設定ボタン, 2);
			解像度X倍.SetUI(LConfig::設定ボタン, 4);
			BGM音量.SetUI(LConfig::設定ボタン, 7);
			SE音量.SetUI(LConfig::設定ボタン, 9);
			ボス戦等速.SetUI(LConfig::設定ボタン, 12);
			夜加速.SetUI(LConfig::設定ボタン, 14);
			超加速.SetUI(LConfig::設定ボタン, 16);
			フォント種.SetUI(LConfig::設定ボタン, 18);

			//●イベント
			確定.clickEvent = [&](){
				is表示 = false;

				Config::BGM設定 = 仮_BGM設定;
				Config::SE設定 = 仮_SE設定;
				Config::解像度設定 = 仮_解像度;
				Config::isウィンドウ = 仮_ウィンドウモード;
				Config::解像度X倍 = 仮_解像度X倍;

				Config::isボス戦時等速 = 仮_ボス戦等速;
				Config::is夜加速 = 仮_夜加速;
				Config::is超加速 = 仮_超加速;
				Config::isドットフォント = 仮_フォント種;

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
				ウィンドウモード.設定値 = TX::Config_ウィンドウモード設定[(int)仮_ウィンドウモード];
			};
			ウィンドウモード.減少ボタン.clickEvent = [&]()
			{
				仮_ウィンドウモード = !仮_ウィンドウモード;
				ウィンドウモード.設定値 = TX::Config_ウィンドウモード設定[(int)仮_ウィンドウモード];

			};

			BGM音量.増加ボタン.clickEvent = [&]()
			{
				仮_BGM設定 += 1;
				if (仮_BGM設定 > 10) { 仮_BGM設定 = 10; }
				BGM音量.設定値 = std::to_string(仮_BGM設定 * 10) + " %";
				Config::BGM音量 = 仮_BGM設定 * 仮_BGM設定 / 100.0;
				Music::SetMainVolume(Config::BGM音量);
			};
			BGM音量.減少ボタン.clickEvent = [&]()
			{
				仮_BGM設定 -= 1;
				if (仮_BGM設定 < 0) { 仮_BGM設定 = 0; }
				BGM音量.設定値 = std::to_string(仮_BGM設定 * 10) + " %";
				Config::BGM音量 = 仮_BGM設定 * 仮_BGM設定 / 100.0;
				Music::SetMainVolume(Config::BGM音量);
			};

			SE音量.増加ボタン.clickEvent = [&]()
			{
				仮_SE設定 += 1;
				if ( 仮_SE設定 > 10) { 仮_SE設定 = 10; }
				SE音量.設定値 = std::to_string(仮_SE設定 * 10) + " %";
				Config::SE音量 = 仮_SE設定 * 仮_SE設定 / 100.0;
				Sound::SetMainVolume(Config::SE音量);
				MSound::効果音[SE::決定].Play();
			};
			SE音量.減少ボタン.clickEvent = [&]()
			{
				仮_SE設定 -= 1;
				if ( 仮_SE設定 < 0) { 仮_SE設定 = 0; }
				SE音量.設定値 = std::to_string(仮_SE設定 * 10) + " %";
				Config::SE音量 = 仮_SE設定 * 仮_SE設定 / 100.0;
				Sound::SetMainVolume(Config::SE音量);
				MSound::効果音[SE::決定].Play();
			};

			解像度.増加ボタン.clickEvent = [&]()
			{
				仮_解像度 += 1;
				if (仮_解像度 > 20) { 仮_解像度 = 20; }
				解像度.設定値 = std::to_string(仮_解像度 * 160) + " x " + std::to_string(仮_解像度 * 90);
			};
			解像度.減少ボタン.clickEvent = [&]()
			{
				仮_解像度 -= 1;
				if (仮_解像度 < 6) { 仮_解像度 = 6; }
				解像度.設定値 = std::to_string(仮_解像度 * 160) + " x " + std::to_string(仮_解像度 * 90);
			};

			解像度X倍.増加ボタン.clickEvent = [&]()
			{
				仮_解像度X倍 += 1;
				if (仮_解像度X倍 > 2) { 仮_解像度X倍 = 1; }
				解像度X倍.設定値 = TX::Config_4Kモード[仮_解像度X倍];
			};
			解像度X倍.減少ボタン.clickEvent = [&]()
			{
				仮_解像度X倍 -= 1;
				if (仮_解像度X倍 < 1) { 仮_解像度X倍 = 2; }
				解像度X倍.設定値 = TX::Config_4Kモード[仮_解像度X倍];
			};

			ボス戦等速.増加ボタン.clickEvent = [&]()
			{
				仮_ボス戦等速 = !仮_ボス戦等速;
				ボス戦等速.設定値 = TX::Config_ボス戦速度_設定[仮_ボス戦等速 ? 0 : 1];
			};
			ボス戦等速.減少ボタン.clickEvent = [&]()
			{
				仮_ボス戦等速 = !仮_ボス戦等速;
				ボス戦等速.設定値 = TX::Config_ボス戦速度_設定[仮_ボス戦等速 ? 0 : 1];
			};

			夜加速.増加ボタン.clickEvent = [&]()
			{
				仮_夜加速 = !仮_夜加速;
				夜加速.設定値 = TX::Config_夜間加速_設定[仮_夜加速 ? 0 : 1];
			};
			夜加速.減少ボタン.clickEvent = [&]()
			{
				仮_夜加速 = !仮_夜加速;
				夜加速.設定値 = TX::Config_夜間加速_設定[仮_夜加速 ? 0 : 1];
			};

			超加速.増加ボタン.clickEvent = [&]()
			{
				仮_超加速 = !仮_超加速;
				超加速.設定値 = TX::Config_超加速_設定[仮_超加速 ? 0 : 1];
			};
			超加速.減少ボタン.clickEvent = [&]()
			{
				仮_超加速 = !仮_超加速;
				超加速.設定値 = TX::Config_超加速_設定[仮_超加速 ? 0 : 1];
			};

			フォント種.増加ボタン.clickEvent = [&]()
			{
				仮_フォント種 = !仮_フォント種;
				フォント種.設定値 = TX::Config_フォント設定[仮_フォント種 ? 0 : 1];
			};
			フォント種.減少ボタン.clickEvent = [&]()
			{
				仮_フォント種 = !仮_フォント種;
				フォント種.設定値 = TX::Config_フォント設定[仮_フォント種 ? 0 : 1];
			};

			//●初期テキスト
			ウィンドウモード.設定値 = TX::Config_ウィンドウモード設定[(int)仮_ウィンドウモード];
			BGM音量.設定値 = std::to_string(仮_BGM設定 * 10) + " %";
			SE音量.設定値 = std::to_string(仮_SE設定 * 10) + " %";
			解像度.設定値 = std::to_string(仮_解像度 * 160) + " x " + std::to_string(仮_解像度 * 90);
			解像度X倍.設定値 = TX::Config_4Kモード[仮_解像度X倍];
			ボス戦等速.設定値 = TX::Config_ボス戦速度_設定[仮_ボス戦等速 ? 0 : 1];
			夜加速.設定値 = TX::Config_夜間加速_設定[仮_夜加速 ? 0 : 1];
			超加速.設定値 = TX::Config_超加速_設定[仮_超加速 ? 0 : 1];
			フォント種.設定値 = TX::Config_フォント設定[仮_フォント種 ? 0 : 1];

			//●登録
			item.clear();
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
			SetPos(LConfig::ウィンドウ, true, false , true);
		}
	};
}