//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*待遇変更ウィンドウ*/
	class W_Skilltree : public UIWindow
	{
	private:
		class GUI_編集中ギルメン : public GUI_Object
		{
		public:
			W_Skilltree* 親;

			void Draw派生(double px, double py)
			{
				auto it = 親->ギルメン;

				//枠
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				//キャラクター
				it->image[0][1]->DrawRotate({ px + Lp(40) , py + Lp(41) }, 2, 0);
				//名前
				MFont::MAlias.DrawBold({ px + Lp(42) ,py + Lp(43) }, Color::White, Color::Black, it->名前, false);
				//LV
				MFont::SAlias.DrawBold({ px + Lp(44) ,py + Lp(45) }, Color::White, Color::Black, {"Lv " , it->Lv}, true);

				//選択ボタン
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(60),py + Lp(62) },2,0);
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(61),py + Lp(62) },2,0, true);

				//例外的に入力処理もここでやる
			}

			void Click(double px, double py)
			{


				//W_Drag::Aスキル = nullptr;
			}

			void Info派生(Point 座標) override
			{

			}
		};

		class UI装備スキルコンボアイテム : public UIObject
		{
		public:
			ActiveSkill* askill;

			void Draw派生() override
			{
				DrawUI(UIType::凸ボタン);

			}

			void Click() override
			{

			}

			void DrawHelp() override
			{
				UIHelp::ASkill(askill);
			}
		};

		class UI装備スキルコンボボックス : public UIObject
		{
		public:
			std::vector<UI装備スキルコンボアイテム> item;

			void Init()
			{
				auto* it = W_Skilltree::ギルメン;
				item.clear();
				item.resize(it->職業->習得Aスキル.size());

				for (int i = 0; i < item.size(); i++)
				{
					item[i].SetUI(LSkill::スキルコンボアイテム, i , this);
					item[i].askill = it->職業->習得Aスキル[i];
				}

			}

			void Draw派生() override
			{
				DrawUI(UIType::平ボタン);
				this->layout->h = layout->並べy + item[0].layout->並べy * item.size();


				for (int i = 0; i < item.size(); i++)
				{
					item[i].Draw();
				}
			}

			virtual bool Check派生(double px, double py) override
			{
				for (int i = 0; i < item.size(); i++)
				{
					if (item[i].CheckInput(px, py) == true) { return true; }
				}

				return false;
			}

			void Click() override
			{

			}
		};

		class UI探索者 : public UIObject
		{
		public:
			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン;
				auto& LA = LData(LSkill::探索者ドット);
				auto& LB = LData(LSkill::探索者立ち絵);
				auto& LC = LData(LSkill::探索者名前);
				auto& LD = LData(LSkill::探索者Lv);
				auto& LE = LData(LSkill::探索者スキルP);
				auto& LF = LData(LSkill::探索者職業名);

				DrawUI(UIType::グループ明);

				//キャラドット絵
				it->image[0][1]->DrawRotate(GetPos(LA) , 2 , 0);

				//キャラ立ち絵
				it->職業->立ち絵image->DrawRotate(GetPos(LB),2,0);

				//名前
				MFont::L->DrawRotate(GetPos(LC), 1, 0, Design::暗字, { it->名前 });

				//職業名
				MFont::L->DrawRotate(GetPos(LF),1,0, Design::暗字, { it->職業->名前 } , false);

				//Lv
				MFont::L->Draw(GetPos(LD), Design::暗字, { "Lv" , it->Lv } , true);

				//残りスキルポイント or 予約ポイント
				MFont::L->Draw( GetPos(LE) , Design::暗字, { it->スキルポイント , " スキルポイント"  });

			}

			void Click() override
			{

			}
		};

		class UI装備Aスキル : public UIObject
		{
		public:

			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン->装備Aスキル通常[lineID];
				int Lv = W_Skilltree::ギルメン->習得AスキルLv[it->ID];
				auto& LA = LData(LSkill::装備スキルLv);
				auto& LB = LData(LSkill::装備スキルスロット);

				//Lv Maxで押せなくする
				DrawUI(UIType::平ボタン);
				it->image->DrawRotate({ GetX() + GetH() / 2 , GetY() + GetH() / 2 }, 2, 0);

				switch (lineID)
				{
					case 0:MFont::L->Draw(GetPos(LB), Design::暗字, { "1st" }); break;
					case 1:MFont::L->Draw(GetPos(LB), Design::暗字, { "2nd" }); break;
					case 2:MFont::L->Draw(GetPos(LB), Design::暗字, { "3rd" }); break;
					case 3:MFont::L->Draw(GetPos(LB), Design::暗字, { "4th" }); break;
				}

				

				MFont::L->Draw(GetPos(LA), Design::暗字, { "Lv " , Lv },true);
			}

			void Click() override
			{

			}

			void DrawHelp() override
			{
				auto* it = W_Skilltree::ギルメン->装備Aスキル通常[lineID];
				UIHelp::ASkill( it );
			}
		};

		class UI予約スキル : public UIObject
		{
		public:
			void Draw派生() override
			{
				int no = W_Skilltree::ギルメン->スキル習得予約[lineID];
				auto& LA = LData(LSkill::スキルLv);
				DrawUI(UIType::平ボタン);

				if( no > 0 )
				{
					auto* it = &PassiveSkill::data[no];
					it->image->DrawRotate(GetCenterPos(), 2, 0);
				}
				else
				{
					auto* it = &ActiveSkill::data[-no];
					it->image->DrawRotate(GetCenterPos(), 2, 0);
				}
			}

			void Click() override
			{

			}

			void DrawHelp() override
			{
				//AスキルかPスキル
				int no = W_Skilltree::ギルメン->スキル習得予約[lineID];
				if (no > 0)
				{
					UIHelp::PSkill(&PassiveSkill::data[no]);
				}
				else
				{
					UIHelp::ASkill(&ActiveSkill::data[-no]);
				}


			}
		};

		class UIキースキル : public UIObject
		{
		public:
			void Draw派生() override
			{
				DrawUI(UIType::平ボタン);
				auto& LB = LData(LSkill::キースキル名前);

				MIcon::UI[IconType::ヘルプ].DrawRotate({ GetX() + GetH() / 2 , GetY() + GetH() / 2 }, 2, 0);
				MFont::L->DrawRotate(GetCenterPos(LB),1,0, Design::暗字, { "キースキル未実装" });
			}

			void Click() override
			{

			}

			void DrawHelp() override
			{
				UIHelp::PSkill(nullptr);
			}
		};

		class UIPスキル : public UIObject
		{
		public:
			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン->職業->習得Pスキル[lineID];
				int Lv = W_Skilltree::ギルメン->習得PスキルLv[it->ID];
				auto& LA = LData(LSkill::スキルLv);

				DrawUI(UIType::平ボタン);

				it->image->DrawRotate(GetCenterPos(), 2, 0);

				//予約は+表示、予約分は文字色を変える
				MFont::L->Draw( GetPos(LA) , Design::暗字, { "Lv " , Lv });
			}

			void Click() override
			{

			}

			void DrawHelp() override
			{
				UIHelp::PSkill(W_Skilltree::ギルメン->職業->習得Pスキル[lineID]);
			}
		};

		class UIAスキル : public UIObject
		{
		public:
			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン->職業->習得Aスキル[lineID];
				int Lv = W_Skilltree::ギルメン->習得AスキルLv[it->ID];
				auto& LA = LData(LSkill::スキルLv);

				DrawUI(UIType::平ボタン);

				it->image->DrawRotate(GetCenterPos(), 2, 0);

				//予約は+表示、予約分は文字色を変える
				MFont::S->Draw( GetPos(LA) , Design::暗字, { "Lv " , Lv });
			}

			void Click() override
			{

			}

			void DrawHelp() override
			{
				UIHelp::ASkill(W_Skilltree::ギルメン->職業->習得Aスキル[lineID]);
			}
		};

	public:
		//GUI_編集中ギルメン 編集中ギルメン;//キャラアイコンと名前
		//GUI_スキルポイント スキルポイント;//現在のスキルポイントと獲得後のスキルポイント
		//GUI_スキル枠 Aスキル枠;//Aスキル表示エリア
		//GUI_スキル枠 Pスキル枠;//Pスキル表示エリア
		//GUI_NowAスキル NowAスキル[CV::最大Aスキル数];//Pスキル
		//GUI_再教育 再教育;
		//GUI_習得 習得;

				//ギルメンの画像と名前
		//前へと次へ(確定前はクリック不可にする)
		//装備中のAスキル、通常と対ボス

		//キースキル
		//Aスキル
		//Pスキル

		//習得予約表示

		//確定ボタン
		//キャンセル
		//忘却 - スキルポイントのリセット
		//残りスキルポイントと予約状態の表示

		UI装備スキルコンボボックス スキルコンボボックス;
		int 選択中スキルスロット = 0;

		UI探索者 探索者;
		UI装備Aスキル 装備Aスキル[CV::最大Aスキル数];
		UI予約スキル 予約スキル[CV::最大スキル予約数];
		UIキースキル キースキル[CV::最大キースキル数];

		UIPスキル Pスキル[CV::上限Pスキル種類];
		UIPスキル Aスキル[CV::上限Aスキル種類];

		UITextFrame 予約スキル枠;
		UITextFrame 装備スキル枠;
		UITextFrame 習得スキル枠;

		UIButton リセット;
		UIButton 確定;
		UIButton キャンセル;

		inline static Explorer* ギルメン;

		void SetMember(Explorer* ギルメン)
		{
			this->ギルメン = ギルメン;
		}

		void Init()
		{
			Set(WindowType::Skilltree, IconType::ランク);
			SetPos(LSkill::ウィンドウ,true,false,true);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化
			探索者.SetUI(LSkill::探索者);
			for (int i = 0; i < CV::最大Aスキル数; i++)
			{
				装備Aスキル[i].SetUI(LSkill::装備Aスキル,i);
			}
			予約スキル枠.SetUI(LSkill::予約スキル枠,"習得予定");
			装備スキル枠.SetUI(LSkill::装備スキル枠,"スキル使用順");
			習得スキル枠.SetUI(LSkill::習得スキル枠,"習得スキル");

			for (int i = 0; i < CV::最大キースキル数; i++)
			{
				キースキル[i].SetUI(LSkill::キースキル,i);
			}
			for (int i = 0; i < CV::上限Pスキル種類; i++)
			{
				Pスキル[i].SetUI(LSkill::Pスキル,i);
			}
			for (int i = 0; i < CV::上限Aスキル種類; i++)
			{
				Aスキル[i].SetUI(LSkill::Aスキル,i);
			}
			for (int i = 0; i < CV::最大スキル予約数; i++)
			{
				予約スキル[i].SetUI(LSkill::予約スキル, i);
			}

			リセット.SetUI(LSkill::リセットボタン , "再訓練");
			確定.SetUI(LSkill::確定ボタン , "確定");
			キャンセル.SetUI(LSkill::確定ボタン, "キャンセル" , 1);

			スキルコンボボックス.SetUI(LSkill::スキルコンボボックス);
			スキルコンボボックス.Init();

			リセット.clickEvent = [&](){};
			確定.clickEvent = [&](){};
			キャンセル.clickEvent = [&](){};

			//●登録
			item.clear();
			AddItem(スキルコンボボックス);

			AddItem(リセット);
			AddItem(確定);
			AddItem(キャンセル);

			AddItem(探索者);

			AddItem(装備Aスキル , CV::最大Aスキル数);
			AddItem(キースキル , CV::最大キースキル数);

			AddItem(予約スキル, CV::最大スキル予約数);
			AddItem(Pスキル , CV::上限Pスキル種類);
			AddItem(Aスキル , CV::上限Aスキル種類);

			AddItem(予約スキル枠);
			AddItem(装備スキル枠);
			AddItem(習得スキル枠);

			Update();
		}

		void Update()
		{
			SetPos(LSkill::ウィンドウ, true, false, true);

			//一旦全部非表示
			for (auto& it : Pスキル)
			{
				it.is表示 = false;
			}
			for (auto& it : Aスキル)
			{
				it.is表示 = false;
			}
			for (auto& it : 予約スキル)
			{
				it.is表示 = false;
			}

			//習得可能なPスキルとAスキルの更新
			auto& job = ギルメン->職業;

			int cnt = 0;
			for (auto& it: job->習得Pスキル)
			{
				Pスキル[it->ID].is表示 = true;
				Pスキル[it->ID].lineID = cnt;
				cnt++;
			}
			cnt = 0;
			for (auto& it : job->習得Aスキル)
			{
				Aスキル[it->ID].is表示 = true;
				Aスキル[it->ID].lineID = cnt;
				cnt++;
			}

			cnt = 0;
			for (int i = 0; i < CV::最大スキル予約数; i++)
			{
				if (ギルメン->スキル習得予約[i] == 1) { break; }
				予約スキル[i].is表示 = true;
				cnt++;
			}

		}
	};
}