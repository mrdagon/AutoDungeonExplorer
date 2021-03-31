//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class W_Dungeon : public UIWindow
	{
	private:
		class GUI_Dun : public GUI_Object
		{
		public:
			Dungeon* 参照 = nullptr;
			W_Dungeon* 親ウィンドウ = nullptr;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				参照->image->DrawRotate({ px + Lp(15),py + Lp(16) },1,0);
				MFont::SAlias.DrawBold({ px + Lp(17), py + Lp(18) }, Color::White, Color::Black, { (int)(参照->探索率*100) , "%"}, true);
				MFont::SAlias.DrawBold({ px + Lp(19), py + Lp(20) }, Color::White, Color::Black, { "Lv",参照->雑魚Lv }, false);

				//ボス
				//参照->ボスモンスター[0].image[0][1]->DrawRotate({ px + Lp(21), py + Lp(22) }, 3, 0);
				MFont::SAlias.DrawBold({ px + Lp(23), py + Lp(24) }, Color::White, Color::Black, "Boss");

				//ザコ
				for (int a = 0; a < (int)参照->雑魚モンスター.size() ; a++)
				{
					//参照->雑魚モンスター[a].image[0][1]->DrawRotate({ px + Lp(25) + Lp(26) * a, py + Lp(27) }, 2, 0);
				}
			}

			void Click(double px, double py)
			{
				//ダンジョンを掴む
				W_Drag::ダンジョン = 参照;
				MSound::効果音[SE::ドラッグ].Play();
			}

			void Info派生(Point 座標) override
			{
				double px = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;

				if ( px > Lp(21) - 20 && px < Lp(21) + 20)
				{
					//ボスモンスターヘルプ
					//InfoMonster( &参照->ボスモンスター[0], 参照->ボスLv, true, 座標);
					return;
				}

				for (int a = 0; a < (int)参照->雑魚モンスター.size(); a++)
				{
					if (px > Lp(25) + Lp(26) * a - 20 && px < Lp(25) + Lp(26) * a + 20)
					{
						//ザコモンスターヘルプ
						//InfoMonster( &参照->雑魚モンスター[a],参照->雑魚Lv,false,座標);
						
						return;
					}
				}

				//モンスター以外
				InfoDungeon(参照, 座標);
			}

		};

		class UIDungeon : public UIObject
		{
		public:
			//ダンジョン毎の枠
			//ダンジョンの外観
			//階層
			//探索率
			//財宝発見数と存在する数
			//階段発見フラグ
			//探索中のパーティ
			//ボスの有無と出現条件
			//出現モンスター or 出現ボス(ボス出現中は通常モンスター見れなくなる)
		};

	public:

		//階層毎にタブ分け５つ
		//枠
		//ダンジョン
		int 現在タブ = 0;
		UITab タブ[5];
		UITextFrame 枠;

		void Init()
		{

			Set(WindowType::Dungeon, IconType::迷宮);
			SetPos(LDungeon::ウィンドウ, false, true, false);

			//●初期化
			枠.SetUI("", LDungeon::内枠);
			タブ[0].SetUI(&現在タブ, &MIcon::UI[IconType::森], "一層", LDungeon::タブ, 0);
			タブ[1].SetUI(&現在タブ, &MIcon::UI[IconType::洞窟], "二層", LDungeon::タブ, 1);
			タブ[2].SetUI(&現在タブ, &MIcon::UI[IconType::砂漠], "三層", LDungeon::タブ, 2);
			タブ[3].SetUI(&現在タブ, &MIcon::UI[IconType::滝], "四層", LDungeon::タブ, 3);
			タブ[4].SetUI(&現在タブ, &MIcon::UI[IconType::城], "五層", LDungeon::タブ, 4);

			//●登録
			AddItem(枠);
			AddItem(タブ, 5);
		}

		void Update()
		{
			SetPos(LDungeon::ウィンドウ, false, true, false);	
		}
	};
}