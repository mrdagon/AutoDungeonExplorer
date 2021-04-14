//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	//LayoutValue
	using namespace SDX;

	/*経営戦略ウィンドウ*/
	class W_Management : public UIWindow
	{
	private:
		class UILv : public UIObject
		{
			void Draw派生() override
			{
				DrawUI(UIType::凸ボタン);

				//現在 街Lv
				double rate = (double)Guild::P->投資経験値 / Management::必要経験値[Guild::P->投資Lv];

				//MSystem::DrawBar({ px,py }, (int)位置.GetW(), (int)位置.GetH(), rate, 1, Color::Blue, Color::White, Color::White, true);

				//MFont::SDot.DrawBold({ px + Lp(30) ,py + Lp(31) }, Color::White, Color::Black, { "Lv",Guild::P->投資Lv });
				//投資経験値ゲージと増加量
			}

			void Click() override
			{
			}
		};

		class UIGold : public UIObject
		{

			void Draw派生() override
			{				
				DrawUI(UIType::凸ボタン);

				//現在資金

				//消費資金

				//選択戦術の資金消費を表示、不足している場合赤色

				//現在の資金
				//MIcon::UI[IconType::資金].Draw({ px + Lp(34) , py + Lp(35) });
				//MFont::MAlias.DrawBold({ px + Lp(32) ,py + Lp(33) }, Color::White, Color::Black, { (long long)Guild::P->資金 , " G" }, true);
				//消費する資金
				//if (W_Drag::Over戦術 != nullptr)
				{
					Color fc = { 255,128,128 };
					//if (W_Drag::Over戦術->消費資金 <= Guild::P->資金) { fc = Color(128,255,128); }
					//MFont::MAlias.DrawBold({ px + Lp(36) ,py + Lp(37) }, fc, Color::Black, { "- " ,W_Drag::Over戦術->消費資金 , " G" }, true);
					//W_Drag::Over戦術 = nullptr;
				}
				if (true)
				{
					Color fc = { 255,128,128 };
					//if (Guild::P->選択戦術->消費資金 > Guild::P->資金) { fc = Color::Red; }
					//MFont::MAlias.DrawBold({ px + Lp(36) ,py + Lp(37) }, fc, Color::Black, { "- " , Management::data[0].消費資金 , " G" }, true);
				}
			}

			void Click() override
			{
			}

		};

		//投資プラン
		class UIPlan : public UIObject
		{
		public:
			Management* 参照戦術;

			void Draw派生() override
			{
				//街レベル不足で枠表示変化
				DrawUI(UIType::凸ボタン);

				参照戦術->image->DrawRotate({ GetCenterX() , GetCenterY() }, 2, 0);
			}

			void Click() override
			{
				//街レベル不足で使用不可
				if ( 参照戦術->is使用可 == false )
				{
					return;
				}

				//資金不足で使用不可
				if (参照戦術->消費資金 < Guild::P->資金)
				{
					return;
				}
			}

			void Over() override
			{
				over戦術 = 参照戦術;
			}
		};

	public:
		inline static Management* over戦術 = nullptr;
		//タブ無くす
		UIGold 資金;//資金と消費G
		UILv 街Lv;//街Lv
		//投資案
		UITextFrame Lvグループ[10];//タブでは無く、レベル毎にグループ分け
		UIPlan 投資案[CV::上限投資案];

		int 現在タブ = 0;
		int 戦術数 = 0;

		void Init()
		{
			Set( WindowType::Management, IconType::戦略);
			SetPos( LManagement::ウィンドウ , false , true , false );
			//●初期化
			資金.SetUI(LManagement::資金枠);
			街Lv.SetUI(LManagement::街Lv枠);

			for (int i = 0; i < 10; i++)
			{
				Lvグループ[i].SetUI(LManagement::街グループ枠, "" ,  DesignType::セット1, i);
			}

			for (int i = 0; i < Management::data.size(); i++)
			{
				投資案[i].SetUI(LManagement::投資案枠, i, &Lvグループ[0]);
				投資案[i].参照戦術 = &Management::data[i];
			}

			//●登録

			AddItem(資金);
			AddItem(街Lv);
			AddItem(Lvグループ,10);
			AddItem(投資案, Management::data.size());

			Update();
		}

		void Update()
		{
			SetPos(LManagement::ウィンドウ, false, true, false);
		}
	};
}