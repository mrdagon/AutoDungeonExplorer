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
				種族->image[0][1]->DrawRotate({ GetX(),GetY() }, 1, 0);
				//ボスは２倍表示

				//レベルも表示？

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

			void SetDungeon(Dungeon* 参照ダンジョン)
			{
				dungeon = 参照ダンジョン;

				for (int i = 0; i < dungeon->雑魚モンスター.size() ; i++)
				{
					出現モンスター.emplace_back(dungeon->雑魚モンスター[i], 0 , false);
					出現モンスター.back().SetUI(LDungeon::フロアモンスター, i, this);
				}
				for (int i = 0; i < dungeon->ボスモンスター.size(); i++)
				{
					出現ボス.emplace_back(dungeon->ボスモンスター[i] , 0 , true);
					出現ボス.back().SetUI(LDungeon::フロアモンスター, i, this);
				}

			}


			void Draw派生() override
			{
				auto &loA = Layout::Data(LDungeon::フロアLv);
				auto &loB = Layout::Data(LDungeon::フロアアイコン);
				auto &loC = Layout::Data(LDungeon::フロアLv);
				auto &loE = Layout::Data(LDungeon::フロアボスマーク);

				if (dungeon->is発見 == false)
				{
					DrawUI(UIType::グループ暗);
					//未発見
					return;
				}

				//ダンジョン毎の枠 - 未発見 - ボス発生中は色替え
				DrawUI(UIType::グループ明);

				//ダンジョンの外観
				dungeon->image->DrawRotate({ GetX() + loB.x , GetY() + loB.y }, 1, 0);

				//レベル/探索率
				MFont::S->DrawBold({ GetX() , GetY() }, Color::White, Color::Black, { (int)(dungeon->探索率 * 100) , "%" }, true);
				MFont::S->DrawBold({ GetX() + loA.x , GetY() + loA.y }, Color::White, Color::Black, { "Lv",dungeon->雑魚Lv }, false);

				//財宝発見数と存在する数
				//階段発見フラグ
				//探索中のパーティ

				//ボスの有無と出現条件
				//出現モンスター or 出現ボス(ボス出現中は通常モンスター見れなくなる)

				if (dungeon->isUIボス表示 == true)
				{
					for (auto& it : 出現ボス)
					{
						it.Draw();
					}
				} else {
					for (auto& it : 出現モンスター)
					{
						it.Draw();
					}
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
				}
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
			枠.SetUI("", LDungeon::内枠);
			タブ[0].SetUI(&現在タブ, &MIcon::UI[IconType::森], "一層", LDungeon::タブ, 0);
			タブ[1].SetUI(&現在タブ, &MIcon::UI[IconType::洞窟], "二層", LDungeon::タブ, 1);
			タブ[2].SetUI(&現在タブ, &MIcon::UI[IconType::砂漠], "三層", LDungeon::タブ, 2);
			タブ[3].SetUI(&現在タブ, &MIcon::UI[IconType::滝], "四層", LDungeon::タブ, 3);
			タブ[4].SetUI(&現在タブ, &MIcon::UI[IconType::城], "五層", LDungeon::タブ, 4);

			for (int i = 0; i < Dungeon::data.size(); i++)
			{
				フロア[i].dungeon = &Dungeon::data[i];
				フロア[i].SetUI(LDungeon::フロア枠);
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
			this->固定縦 = Layout::Data(LDungeon::内枠).h;

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