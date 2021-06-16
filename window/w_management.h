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
				double rate = (double)Guild::P->街経験値 / Management::必要経験値[Guild::P->街Lv];
				Design::Input->DrawGauge(GetX(), GetY(), GetW(), GetH(), rate);

				//街 Lv 現在値のみ
				MFont::L->Draw({ GetX() + layout->並べx , GetY() + layout->並べy }, Design::暗字, { " Lv ",Guild::P->街Lv } , true );
			}

			void Click() override
			{
			}
		};
		
		//投資プラン
		class UIPlan : public UIObject
		{
		public:
			Management* manage;

			void Draw派生() override
			{
				auto& LA = LData(LManagement::プランLv);
				auto& LB = LData(LManagement::プラン名前);
				auto& LC = LData(LManagement::プラン費用);
				auto& LD = LData(LManagement::プランアイコン);
				auto& LE = LData(LManagement::素材枠);
				auto& LF = LData(LManagement::素材ランク);
				auto& LG = LData(LManagement::素材必要数);
				auto& LH = LData(LManagement::素材アイコン);

				if (manage->is予約 == true)
				{
					DrawUI(UIType::凹ボタン, Design::Input);
					Camera::Get()->position.y -= 2;					
				}
				else
				{
					DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, Design::Input);
				}


				//投資名 Lv
				//Design::No1->Draw(UIType::丸フレーム, GetX() + LB.x, GetY() + LB.y, LB.w, LB.h);
				MFont::L->DrawEdge({ GetX() + LB.並べx , GetY() + LB.並べy }, Design::暗字, { manage->名前 });
				MFont::L->DrawEdge({ GetX() + LA.x , GetY() + LA.y }, Design::暗字, { "Lv" , manage->投資Lv });
				//費用
				for (int i = 0; i < CV::投資コスト最大枠数; i++)
				{
					if (manage->コスト[i].必要素材数 == 0)
					{
						continue;
					}
					auto pt = LE.GetPos(i);
					auto cost = manage->コスト[i];
					pt.x += GetX();
					pt.y += GetY();

					Design::Input->Draw(UIType::丸フレーム, pt.x, pt.y, LE.w , LE.h );
					MIcon::素材[cost.必要素材種].Draw({ pt.x + LH.x , pt.y + LH.y });

					MFont::M->DrawEdge({ pt.x + LF.x , pt.y +LF.y }, Design::明字, { "★" , cost.必要素材ランク });
					MFont::M->DrawRotateEdge({ pt.x + LG.x , pt.y + LG.y },1,0, Design::暗字, { "x" , cost.必要素材数 });
				}


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
		inline static Management* over戦術 = nullptr;

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
			街Lv.SetUI(LManagement::街Lv枠);

			for (int i = 0; i < Management::data.size(); i++)
			{
				投資案[i].SetUI(LManagement::プラン枠, i );
				投資案[i].manage = &Management::data[i];
			}

			//●登録
			item.clear();
			AddItem(街Lv,true);
			AddItem(投資案, Management::data.size());

			//●ヘルプ
			街Lv.SetHelp(&TH::Management::街Lv);

			Update();
		}

		void Update()
		{
			SetPos(LManagement::ウィンドウ, false, true, false);
			固定縦 = 50;
			over戦術 = nullptr;
		}
	};
}