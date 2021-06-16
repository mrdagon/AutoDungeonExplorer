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
		class UI財宝 : public UIObject
		{
		public:
			Dungeon* dungeon;

			UI財宝()
			{
				isCanClick = false;
			}

			void Draw派生() override
			{
				DrawUI(UIType::丸フレーム);

				dungeon->財宝[lineID]->image->DrawRotate(GetCenterPos(), 1, 0);
			}

			void Over() override
			{

			}

			void DrawHelp() override
			{
				UIHelp::Item( dungeon->財宝[lineID] ,false);
			}
		};

		class UIMonster : public UIObject
		{
		public:
			int Lv;
			bool isボス;
			MonsterClass* 種族;
			
			UIMonster(MonsterClass* 種族, int Lv, bool isボス) :
				種族(種族),
				Lv(Lv),
				isボス(isボス)
			{
				isCanClick = false;
			}

			void Draw派生() override
			{
				auto& LA = Layout::Data(LDungeon::魔物Lv);

				DrawUI(UIType::丸フレーム);
				種族->image[0][1]->DrawRotate( GetCenterPos() , 2, 0);
				//MFont::M->DrawBold(GetPos(LA), Design::暗字, Design::明字, { Lv } , true);//Lv表示しない
			}

			void Over() override
			{
			}

			void DrawHelp() override
			{
				UIHelp::Monster(種族,Lv);
			}
		};

		class UIDungeon : public UIObject
		{
		public:
			Dungeon* dungeon;

			std::vector<UIMonster> 出現ボス;
			std::vector<UIMonster> 出現モンスター;
			std::vector<UI財宝> 出現財宝;

			//UIButton ボス雑魚表示;

			UIDungeon()
			{
				//ボス雑魚表示.SetHelp(&TH::Dungeon::ボス表示切り替え);
			}

			void SetDungeon(Dungeon* 参照ダンジョン)
			{
				dungeon = 参照ダンジョン;

				出現財宝.reserve(dungeon->財宝.size());

				for (int i = 0; i < dungeon->雑魚モンスター.size() ; i++)
				{
					出現モンスター.emplace_back(dungeon->雑魚モンスター[i], 0 , false);
					出現モンスター.back().SetUI(LDungeon::モンスター, i, this);
					出現モンスター.back().Lv = dungeon->雑魚Lv[i];
				}
				for (int i = 0; i < dungeon->ボスモンスター.size(); i++)
				{
					if (dungeon->ボスモンスター[i]->ID == 0)
					{
						continue;
					}

					出現ボス.emplace_back(dungeon->ボスモンスター[i] , 0 , true);
					出現ボス.back().SetUI(LDungeon::モンスター, i + 6, this);
					出現ボス.back().Lv = dungeon->ボスLv[i];
				}


				for (int i = 0; i < dungeon->財宝.size(); i++)
				{
					出現財宝.emplace_back();
					出現財宝.back().SetUI(LDungeon::財宝, i, this);
					出現財宝.back().dungeon = dungeon;
				}
			}

			void Draw派生() override
			{
				auto &LB = Layout::Data(LDungeon::フロアアイコン);
				auto &LC = Layout::Data(LDungeon::探索率);
				auto &LE = Layout::Data(LDungeon::地図ボスマーカー);
				auto &LF = Layout::Data(LDungeon::種別テキスト);


				if (dungeon->is発見 == false)
				{
					DrawUI(UIType::グループ暗);
					//未発見
					MFont::L->DrawBoldRotate( GetCenterPos() , 1, 0, Design::暗字, Design::明字, { "未発見" }, false);
					return;
				}

				//ダンジョン毎の枠 - 未発見 - ボス発生中は色替え


				DrawUI(isOver ? UIType::平ボタン : UIType::暗ボタン , Design::Input);

				//ダンジョンの外観
				dungeon->image->DrawRotate({ GetX() + LB.x , GetY() + LB.y }, 1, 0);
				MFont::M->DrawEdge({ GetX() + LB.w , GetY() + LB.h }, Design::暗字, { dungeon->ID + 1 , "F" }, true);

				//探索率
				Design::Base->DrawGauge(GetX() + LC.x, GetY()+ LC.y, LC.w, LC.h, dungeon->探索率 );
				MFont::M->DrawBold({ GetX() + LC.並べx , GetY() + LC.並べy }, Design::暗字 , Design::明字 , { (int)(dungeon->探索率 * 100) , "%" }, true);

				//階段位置、ボス位置マーク

				if (dungeon->地図発見探索率[0] > 0)
				{
					int xbuf = dungeon->地図発見探索率[0] * LE.w / 100;

					MIcon::UI[IconType::三角].DrawRotate({ GetX() + xbuf + LE.x,GetY() + LE.y - LE.h }, 2, 3.14 / 2);
					MIcon::UI[IconType::地図].DrawRotate({ GetX() + xbuf + LE.x,GetY() + LE.y }, 2, 0);

				}

				if (dungeon->ボス発見探索率 > 0)
				{
					int xbuf = dungeon->ボス発見探索率 * LE.w / 100;

					MIcon::UI[IconType::三角].DrawRotate({ GetX() + xbuf + LE.x,GetY() + LE.y - LE.h }, 2, 3.14 / 2);
					MIcon::UI[IconType::ボス].DrawRotate({ GetX() + xbuf + LE.x,GetY() + LE.y }, 2, 0);
				}

				//ボス雑魚ボタン - ボス撃破済みだと表示される
				//ボス雑魚表示.Draw();

				//出現モンスター or 出現ボス
				for (auto& it : 出現モンスター)
				{
					it.Draw();
				}

				for (auto& it : 出現ボス)
				{
					it.Draw();
				}

				//財宝表示
				for (auto& it : 出現財宝)
				{
					it.Draw();
				}
				//Enemy F.O.E treasure 
				auto pA = LF.GetPos(0);
				auto pB = LF.GetPos(1);
				auto pC = LF.GetPos(2);

				MFont::M->DrawEdge({ GetX() + pA.x , GetY() + pA.y }, Design::明字, "Enemy");
				if (出現ボス.size() > 0)
				{
					MFont::M->DrawEdge({ GetX() + pB.x , GetY() + pB.y }, Design::明字, "F.O.E");
				}
				MFont::M->DrawEdge({ GetX() + pC.x , GetY() + pC.y }, Design::明字, "Treasure");

			}

			void Click() override
			{
				//ボス/ザコ表示切り替えボタン
				if (dungeon->is発見 == true)
				{
					W_Drag::ダンジョン = dungeon;
					MSound::効果音[SE::ドラッグ].Play();
				}
			}

			bool Check派生(double px, double py)
			{
				//子オブジェクトの当たり判定
				if (dungeon->is発見 == true)
				{
					for (auto& it : 出現ボス)
					{
						if (it.CheckInput(px, py) == true)
						{
							return true;
						}
					}

					for (auto& it : 出現モンスター)
					{
						if (it.CheckInput(px, py) == true)
						{
							return true;
						}
					}
					
					for (auto& it : 出現財宝)
					{
						if (it.CheckInput(px, py) == true)
						{
							return true;
						}
					}

				}

				return false;
			}

			void Over() override
			{
				//ダンジョンの情報
				if (dungeon->is発見 == false)
				{

				}

				//モンスターステータス


				//切り替えボタン説明
			}

			void DrawHelp() override
			{
				if (dungeon->is発見)
				{
					//UIHelp::Dungeon( dungeon );
				}
				else
				{
					UIHelp::Text(&TH::Dungeon::未発見フロア);
				}

			}
		};

	public:
		//階層毎にタブ分け５つ
		//枠
		//ダンジョン
		int 現在タブ = 0;
		UITab タブ[5];
		UITextFrame 枠;
		UIDungeon フロア[CV::上限ダンジョン数];

		void Init()
		{
			Set(WindowType::Dungeon, IconType::迷宮);
			SetPos(LDungeon::ウィンドウ, false, true, false);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化
			枠.SetUI(LDungeon::内枠,"",&Design::Input);
			タブ[0].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::森], "I層",  0);
			タブ[1].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::洞窟], "II層",  1);
			タブ[2].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::砂漠], "III層",  2);
			タブ[3].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::滝], "IV層", 3);
			タブ[4].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::城], "V層",  4);

			for (int i = 0; i < Dungeon::data.size(); i++)
			{
				フロア[i].SetUI(LDungeon::フロア枠);
				フロア[i].SetDungeon(&Dungeon::data[i]);
			}

			//●登録
			item.clear();
			AddItem(枠, true);
			AddItem(タブ, 5, true);
			AddItem(フロア, Dungeon::data.size());

			Update();
		}

		void Update()
		{
			SetPos(LDungeon::ウィンドウ, false, true, false);
			this->固定縦 = Layout::Data(LDungeon::内枠).並べy;

			int cnt = 0;
			for (int i = 0; i < Dungeon::data.size(); i++)
			{
				if (フロア[i].dungeon->層 == 現在タブ)
				{
					フロア[i].lineID = cnt;
					フロア[i].is表示 = true;
					cnt++;
				} else {
					フロア[i].is表示 = false;
				}
			}
		}
	};
}