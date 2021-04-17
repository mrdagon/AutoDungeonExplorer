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
			int 財宝ID;
			Dungeon* dungeon;

			void Draw派生() override
			{
				DrawUI(UIType::丸フレーム);
			}

			void Over() override
			{

			}
		};

		class UIMonster : public UIObject
		{
		public:
			int Lv;
			bool isボス;
			MonsterClass* 種族;
			
			UIMonster(MonsterClass* 種族 , int Lv , bool isボス):
				種族(種族),
				Lv(Lv),
				isボス(isボス)
			{}

			void Draw派生() override
			{
				DrawUI(UIType::丸フレーム);
				種族->image[0][1]->DrawRotate( GetCenterPos() , 2, 0);
				//ボスは２倍表示？

			}

			void Over() override
			{
			}
		};

		class UIDungeon : public UIObject
		{
		public:
			Dungeon* dungeon;

			std::vector<UIMonster> 出現ボス;
			std::vector<UIMonster> 出現モンスター;
			std::vector<UI財宝> 出現財宝;

			UIButton ボス雑魚表示;

			void SetDungeon(Dungeon* 参照ダンジョン)
			{
				dungeon = 参照ダンジョン;

				for (int i = 0; i < dungeon->雑魚モンスター.size() ; i++)
				{
					出現モンスター.emplace_back(dungeon->雑魚モンスター[i], 0 , false);
					出現モンスター.back().SetUI(LDungeon::モンスター, i, this);
				}
				for (int i = 0; i < dungeon->ボスモンスター.size(); i++)
				{
					出現ボス.emplace_back(dungeon->ボスモンスター[i] , 0 , true);
					出現ボス.back().SetUI(LDungeon::モンスター, i, this);
				}
				for (int i = 0; i < dungeon->財宝.size(); i++)
				{
					出現財宝.emplace_back();
					出現財宝.back().SetUI(LDungeon::財宝, i, this);
					出現財宝[i].財宝ID = i;
					出現財宝[i].dungeon = dungeon;
				}

				ボス雑魚表示.SetUI(LDungeon::雑魚ボスボタン,"Test", 0, this);

				ボス雑魚表示.clickEvent = [&]() {dungeon->isUIボス表示 = !dungeon->isUIボス表示; };
			}


			void Draw派生() override
			{
				auto &LA = Layout::Data(LDungeon::フロアLv);
				auto &LB = Layout::Data(LDungeon::フロアアイコン);
				auto &LC = Layout::Data(LDungeon::探索率);

				if (dungeon->is発見 == false)
				{
					DrawUI(UIType::グループ暗);
					//未発見
					MFont::M->DrawBoldRotate( GetCenterPos() , 1, 0, Design::明字, Design::暗字, { "未発見" }, false);

					return;
				}

				//ダンジョン毎の枠 - 未発見 - ボス発生中は色替え
				DrawUI(UIType::グループ中);

				//ダンジョンの外観
				dungeon->image->DrawRotate({ GetX() + LB.x , GetY() + LB.y }, 1, 0);
				MFont::S->DrawBold({ GetX() + LB.w , GetY() + LB.h }, Color::White, Color::Black, { dungeon->ID + 1 , "F" }, true);

				//探索率
				Design::No1->DrawGauge(LC.x, LC.y, LC.w, LC.h, dungeon->探索率 + 0.5);
				MFont::S->DrawBold({ GetX() + LC.並べx , GetY() + LC.並べy }, Color::White, Color::Black, { (int)(dungeon->探索率 * 100) , "%" }, true);

				//階段位置、ボス位置マーク

				//ボス雑魚ボタン - ボス撃破済みだと表示される
				ボス雑魚表示.Draw();

				//出現モンスター or 出現ボス
				if (dungeon->isUIボス表示 == true)
				{
					//レベル
					MFont::S->DrawBold({ GetX() + LA.x , GetY() + LA.y }, Color::White, Color::Black, { "Lv",dungeon->ボスLv }, false);

					for (auto& it : 出現ボス)
					{
						it.Draw();
					}
				} else {
					//レベル
					MFont::S->DrawBold({ GetX() + LA.x , GetY() + LA.y }, Color::White, Color::Black, { "Lv",dungeon->雑魚Lv }, false);

					for (auto& it : 出現モンスター)
					{
						it.Draw();
					}
				}

				//財宝表示
				for (auto& it : 出現財宝)
				{
					it.Draw();
				}

			}

			void Click() override
			{
				//ボス/ザコ表示切り替えボタン
				W_Drag::ダンジョン = dungeon;
				MSound::効果音[SE::ドラッグ].Play();
			}

			bool Check派生(double px, double py)
			{
				//子オブジェクトの当たり判定
				if (dungeon->is発見 == true)
				{
					if (dungeon->isUIボス表示 == true)
					{
						for (auto& it : 出現ボス)
						{
							if (it.CheckInput(px, py) == true)
							{
								return true;
							}
						}
					}
					else {
						for (auto& it : 出現モンスター)
						{
							if (it.CheckInput(px, py) == true)
							{
								return true;
							}
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

			//●初期化
			枠.SetUI(LDungeon::内枠,"");
			タブ[0].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::森], "一層",  0);
			タブ[1].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::洞窟], "二層",  1);
			タブ[2].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::砂漠], "三層",  2);
			タブ[3].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::滝], "四層", 3);
			タブ[4].SetUI(LDungeon::タブ, &現在タブ, &MIcon::UI[IconType::城], "五層",  4);

			for (int i = 0; i < Dungeon::data.size(); i++)
			{
				フロア[i].SetUI(LDungeon::フロア枠);
				フロア[i].SetDungeon(&Dungeon::data[i]);
			}

			//●登録
			AddItem(枠 , true);
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