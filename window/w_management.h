//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	//LayoutValue
	using namespace SDX;

	/*経営戦略ウィンドウ*/
	class W_Facility : public UIWindow
	{
	private:
		class UILv : public UIObject
		{
			void Draw派生() override
			{
				//街経験値 - 現在値、使用後
				double rate = (double)Guild::P->街経験値 / Guild::Facility::必要経験値[Guild::P->街Lv];
				Design::No1->DrawGauge(GetX(), GetY(), GetW(), GetH(), rate);

				//街 Lv 現在値のみ
				MFont::L->Draw({ GetX() + layout->並べx , GetY() + layout->並べy }, Design::暗字, { "街 Lv ",Guild::P->街Lv } , true );
			}

			void Click() override
			{
			}
		};

		class UIGold : public UIObject
		{

			void Draw派生() override
			{

				auto& LA = LData(LManagement::資金現在);
				auto& LB = LData(LManagement::資金消費);
				auto& LC = LData(LManagement::資金アイコン);

				DrawUI(UIType::グループ明);

				//アイコン
				MIcon::UI[IconType::資金].DrawRotate( GetPos(LC) , 2,0);
				if (over戦術 != nullptr)
				{
					//現在資金
					MFont::L->Draw(GetPos(LA), Design::暗字, { 1000 , "G"}, true);
				} else {
					//現在資金
					MFont::L->Draw(GetPos(LA), Design::暗字, { 1000 , "G >"}, true);
					//消費資金
					MFont::L->Draw(GetPos(LB), Design::暗字, { -1000 , "G" }, true);
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
			Guild::Facility* manage;

			void Draw派生() override
			{
				auto& LA = LData(LManagement::プランLv);
				auto& LB = LData(LManagement::プラン名前);
				auto& LC = LData(LManagement::プラン費用);
				auto& LD = LData(LManagement::プランアイコン);

				if (manage->is予約 == true)
				{
					DrawUI(UIType::凹ボタン, Design::UI);
					Camera::Get()->position.y -= 2;					
				}
				else
				{
					DrawUI(isOver ? UIType::凸ハイライト : UIType::凸ボタン, Design::UI);
				}


				//投資名 Lv
				Design::No1->Draw(UIType::丸フレーム, GetX() + LB.x, GetY() + LB.y, LB.w, LB.h);
				MFont::L->Draw({ GetX() + LB.並べx , GetY() + LB.並べy }, Design::暗字, { manage->名前 });
				MFont::L->Draw({ GetX() + LA.x , GetY() + LA.y }, Design::暗字, { "Lv" , manage->投資Lv });
				//費用
				Design::No1->Draw(UIType::丸フレーム, GetX() + LC.x, GetY() + LC.y, LC.w, LC.h);
				MFont::L->Draw({ GetX() + LC.並べx , GetY() + LC.並べy }, Design::暗字, { manage->Get費用() , "G" } , true);

				//投資アイコン
				manage->image->DrawRotate(GetPos(LD), 2, 0);

				if (manage->is予約 == true)
				{
					Camera::Get()->position.y += 2;
				}
			}

			void Click() override
			{
				manage->操作_クリック();
			}

			void Over() override
			{
				over戦術 = manage;
			}


			void DrawHelp() override
			{
				UIHelp::Management( manage );
			}
		};

	public:
		inline static Guild::Facility* over戦術 = nullptr;

		UIGold 資金;//資金と消費G
		UILv 街Lv;//街Lv
		//投資案
		UIPlan 投資案[CV::上限投資案];

		void Init()
		{
			Set( WindowType::Management, IconType::戦略);
			SetPos( LManagement::ウィンドウ , false , true , false );

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化
			資金.SetUI(LManagement::資金枠);
			街Lv.SetUI(LManagement::街Lv枠);

			for (int i = 0; i < Guild::Facility::data.size(); i++)
			{
				投資案[i].SetUI(LManagement::プラン枠, i );
				投資案[i].manage = &Guild::Facility::data[i];
			}

			//●登録
			item.clear();
			AddItem(資金,true);
			AddItem(街Lv,true);
			AddItem(投資案, Guild::Facility::data.size());

			//●ヘルプ
			街Lv.SetHelp(&TH::Management::街Lv);
			資金.SetHelp(&TH::Management::資金);

			Update();
		}

		void Update()
		{
			SetPos(LManagement::ウィンドウ, false, true, false);
			固定縦 = 100;
			over戦術 = nullptr;
		}
	};
}