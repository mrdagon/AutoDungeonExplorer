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
			

			void Draw派生() override
			{
				auto* skill = W_Skilltree::ギルメン->職業->習得Aスキル[lineID];
				int Lv = W_Skilltree::ギルメン->習得AスキルLv[skill->ID];
				auto& LA = LData(LSkill::スキルLv);

				DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, Design::Input);
				skill->image->DrawRotate(GetCenterPos(),2,0);
				MFont::L->DrawBold(GetPos(LA), Design::暗字 , Design::明字 , { Lv } );
			}

			void Click() override
			{
				int 装備スロット = W_Skilltree::This->スキルコンボボックス.装備スロット;

				auto* skill = W_Skilltree::ギルメン->職業->習得Aスキル[lineID];
				int slot = W_Skilltree::ギルメン->操作_装備Aスキル変更(装備スロット, skill);

				W_Skilltree::This->装備Aスキル[slot].押下アニメ = CV::ボタンアニメ時間;
				W_Skilltree::This->装備Aスキル[装備スロット].押下アニメ = CV::ボタンアニメ時間;

				W_Skilltree::This->スキルコンボボックス.is表示 = false;
			}

			void DrawHelp() override
			{
				auto* skill = W_Skilltree::ギルメン->職業->習得Aスキル[lineID];
				UIHelp::ASkill(skill);
			}
		};

		class UI装備スキルコンボボックス : public UIObject
		{
		public:
			std::vector<UI装備スキルコンボアイテム> item;
			int 装備スロット = 0;
			
			void Init()
			{
				auto* it = W_Skilltree::ギルメン;
				item.clear();
				item.resize(it->職業->習得Aスキル.size());

				for (int i = 0; i < item.size(); i++)
				{
					item[i].SetUI(LSkill::スキルコンボアイテム, i , this);
				}

				is表示 = false;

			}

			void Draw派生() override
			{
				DrawUI(UIType::明ボタン);
				this->layout->h = layout->並べy + item[0].layout->並べy * item.size();

				bool now_over = false;

				for (int i = 0; i < item.size(); i++)
				{
					if (item[i].isOver == true)
					{
						now_over = true;
						break;
					}
				}

				for (int i = 0; i < item.size(); i++)
				{
					item[i].Draw();
				}

				if (Input::mouse.Left.on == true && now_over == false)
				{
					if (						
						W_Skilltree::This->装備Aスキル[0].isOver == false && 
						W_Skilltree::This->装備Aスキル[1].isOver == false &&
						W_Skilltree::This->装備Aスキル[2].isOver == false &&
						W_Skilltree::This->装備Aスキル[3].isOver == false )
					{
						W_Skilltree::This->スキルコンボボックス.is表示 = false;
					}

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
				Input::mouse.Left.on = false;
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

				DrawUI(UIType::グループ明, Design::Input);

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
		};

		class UI装備Aスキル : public UIObject
		{
		public:
			int 押下アニメ = 0;

			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン->装備Aスキル[lineID];
				int Lv = W_Skilltree::ギルメン->習得AスキルLv[it->ID];
				auto& LA = LData(LSkill::装備スキルLv);
				auto& LB = LData(LSkill::装備スキルスロット);

				//Lv Maxで押せなくする
				if (押下アニメ > 0)
				{
					//スワップや変更があった場合のアニメーション
					押下アニメ--;
					DrawUI( UIType::凹ボタン, Design::Input);
				} else {
					DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, Design::Input);
				}


				it->image->DrawRotate({ GetX() + GetW() / 2  , GetY() + GetW() / 2 + layout->並べy }, 2, 0);

				switch (lineID)
				{
					case 0:MFont::L->DrawBold(GetPos(LB), Design::暗字 , Design::明字, { "1st" }); break;
					case 1:MFont::L->DrawBold(GetPos(LB), Design::暗字, Design::明字, { "2nd" }); break;
					case 2:MFont::L->DrawBold(GetPos(LB), Design::暗字, Design::明字, { "3rd" }); break;
					case 3:MFont::L->DrawBold(GetPos(LB), Design::暗字, Design::明字, { "4th" }); break;
				}

				MFont::L->DrawBold(GetPos(LA), Design::暗字, Design::明字, { Lv },true);
			}

			void Click() override
			{
				if (W_Skilltree::This->スキルコンボボックス.装備スロット == lineID && W_Skilltree::This->スキルコンボボックス.is表示 == true)
				{
					W_Skilltree::This->スキルコンボボックス.is表示 = false;
				} else {
					W_Skilltree::This->スキルコンボボックス.is表示 = true;
					W_Skilltree::This->スキルコンボボックス.装備スロット = lineID;
					W_Skilltree::This->スキルコンボボックス.layout->x = this->GetX();
					W_Skilltree::This->スキルコンボボックス.layout->y = this->GetY() + this->GetH();
				}
			}

			void DrawHelp() override
			{
				auto* it = W_Skilltree::ギルメン->装備Aスキル[lineID];
				UIHelp::ASkill( it );
			}
		};

		class UI予約スキル : public UIObject
		{
		public:
			int 追加アニメ = 0;

			void Draw派生() override
			{
				int no = W_Skilltree::ギルメン->スキル習得予約[lineID];
				auto& LA = LData(LSkill::スキルLv);
				Design* design = lineID < W_Skilltree::ギルメン->スキルポイント ? &Design::Green : Design::Input;

				if (追加アニメ > 0)
				{
					追加アニメ--;
					DrawUI(UIType::凹ボタン, design );
				} else {
					DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, design );
				}

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
				W_Skilltree::ギルメン->スキル予約解除(lineID);
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
			int 押下アニメ = 0;
		public:
			void Draw派生() override
			{
				auto& LB = LData(LSkill::キースキル名前);

				if (押下アニメ > 0)
				{
					押下アニメ--;
					DrawUI(UIType::平ボタン, Design::Input);
				} else {
					DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, Design::Input);
				}

				MIcon::UI[IconType::ヘルプ].DrawRotate({ GetX() + GetH() / 2 , GetY() + GetH() / 2 }, 2, 0);
				MFont::L->DrawRotate(GetCenterPos(LB),1,0, Design::暗字, { "キースキル未実装" });
			}

			void Click() override
			{
				W_Skilltree::ギルメン->操作_キースキル習得(lineID);
			}

			void DrawHelp() override
			{
				UIHelp::PSkill(nullptr);
			}
		};

		class UIPスキル : public UIObject
		{
			int 押下アニメ = 0;
		public:
			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン->職業->習得Pスキル[lineID];
				int Lv = W_Skilltree::ギルメン->習得PスキルLv[it->ID];
				int 予約Lv = W_Skilltree::ギルメン->GetPスキル予約Lv(it->ID);
				auto& LA = LData(LSkill::スキルLv);

				if (押下アニメ > 0)
				{
					押下アニメ--;
					DrawUI(UIType::平ボタン, Design::Input);
				} else {
					DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, Design::Input);
				}

				it->image->DrawRotate(GetCenterPos(), 2, 0);

				//予約は+表示、予約分は文字色を変える

				MFont::L->DrawBold(GetPos(LA), Design::暗字, Design::明字, { Lv });
				if (Lv != 予約Lv)
				{
					MFont::L->DrawBold({ GetPos(LA).x + LA.並べx,  GetPos(LA).y}, Design::暗字, Design::明字, { ">", });
					MFont::L->DrawBold({ GetPos(LA).x + LA.並べx * 2,  GetPos(LA).y }, Design::Green.凹色, Design::明字, { 予約Lv });
				}

			}

			void Click() override
			{
				auto result = W_Skilltree::ギルメン->Pスキル予約(W_Skilltree::ギルメン->職業->習得Pスキル[lineID]->ID);

				if ( result != Explorer::Resultスキル強化::予約失敗)
				{
					押下アニメ = CV::ボタンアニメ時間;
				}
			}

			void RightClick() override
			{
				auto result = W_Skilltree::ギルメン->Pスキル解除(W_Skilltree::ギルメン->職業->習得Pスキル[lineID]->ID);

				if (result != Explorer::Resultスキル強化::解除失敗)
				{
					押下アニメ = CV::ボタンアニメ時間;
				}
			}

			void DrawHelp() override
			{
				UIHelp::PSkill(W_Skilltree::ギルメン->職業->習得Pスキル[lineID]);
			}
		};

		class UIAスキル : public UIObject
		{
			int 押下アニメ = 0;
		public:
			void Draw派生() override
			{
				auto* it = W_Skilltree::ギルメン->職業->習得Aスキル[lineID];
				int Lv = W_Skilltree::ギルメン->習得AスキルLv[it->ID];
				int 予約Lv = W_Skilltree::ギルメン->GetAスキル予約Lv(it->ID);
				auto& LA = LData(LSkill::スキルLv);

				if (押下アニメ > 0)
				{
					押下アニメ--;
					DrawUI(UIType::平ボタン, Design::Input);
				} else {
					DrawUI(isOver ? UIType::凸明ボタン : UIType::凸ボタン, Design::Input);
				}

				it->image->DrawRotate(GetCenterPos(), 2, 0);

				//予約は+表示、予約分は文字色を変える
				MFont::L->DrawBold(GetPos(LA), Design::暗字, Design::明字, { Lv });
				if (Lv != 予約Lv)
				{
					MFont::L->DrawBold({ GetPos(LA).x + LA.並べx,  GetPos(LA).y }, Design::暗字, Design::明字, { ">", });
					MFont::L->DrawBold({ GetPos(LA).x + LA.並べx * 2,  GetPos(LA).y }, Design::Green.凹色, Design::明字, { 予約Lv });
				}
			}

			void Click() override
			{
				auto result = W_Skilltree::ギルメン->Aスキル予約(W_Skilltree::ギルメン->職業->習得Aスキル[lineID]->ID);

				if ( result != Explorer::Resultスキル強化::予約失敗)
				{
					押下アニメ = CV::ボタンアニメ時間;
				}
			}

			void RightClick() override
			{
				auto result = W_Skilltree::ギルメン->Aスキル解除(W_Skilltree::ギルメン->職業->習得Aスキル[lineID]->ID);

				if (result != Explorer::Resultスキル強化::解除失敗)
				{
					押下アニメ = CV::ボタンアニメ時間;
				}
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

		inline static W_Skilltree* This;
		inline static Explorer* ギルメン;

		W_Popup リセット確認;

		UI装備スキルコンボボックス スキルコンボボックス;
		int 選択中スキルスロット = 0;

		UI探索者 探索者;
		UI装備Aスキル 装備Aスキル[CV::最大Aスキル数];
		UI予約スキル 予約スキル[CV::最大スキル予約数];
		UIキースキル キースキル[CV::最大キースキル数];

		UIPスキル Pスキル[CV::上限Pスキル種類];
		UIAスキル Aスキル[CV::上限Aスキル種類];

		UITextFrame 予約スキル枠;
		UITextFrame 装備スキル枠;
		UITextFrame 習得スキル枠;

		UIButton リセット;
		UIButton 確定;
		UIButton 前後[2];


		void SetMember(Explorer* ギルメン)
		{
			this->ギルメン = ギルメン;
		}

		void Init()
		{
			This = this;

			Set(WindowType::Skilltree, IconType::ランク);
			SetPos(LSkill::ウィンドウ,true,false,true);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			is閉じるボタン = false;
			ヘルプウィンドウ = &Hウィンドウ;
			リセット確認.Init(WindowType::ResetSkill);

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
			前後[0].SetUI(LSkill::前後ボタン, "＜" , 0);
			前後[1].SetUI(LSkill::前後ボタン, "＞", 1);

			スキルコンボボックス.SetUI(LSkill::スキルコンボボックス);
			スキルコンボボックス.Init();

			//●イベント
			リセット.clickEvent = [&]()
			{
				リセット確認.OpenPopup();
				if (リセット確認.ポップアップリザルト == 1)
				{
					ギルメン->操作_スキルリセット();
				}
			};
			確定.clickEvent = [&]()
			{
				this->is表示 = false;

				for (int a = 0; a < 100; a++)
				{
					Guild::P->探索者[a].予約スキル習得();
				}

			};
			前後[0].clickEvent = [&]()
			{ 
				ギルメン = Guild::P->操作_スキル画面前後( ギルメン , -1 );
			};
			前後[1].clickEvent = [&]()
			{
				ギルメン = Guild::P->操作_スキル画面前後( ギルメン ,  1 );
			};

			//●登録
			item.clear();
			AddItem(探索者);


			//AddItem(リセット);
			AddItem(確定);

			AddItem(装備Aスキル , CV::最大Aスキル数);
			AddItem(スキルコンボボックス);
			AddItem(キースキル , CV::最大キースキル数);

			AddItem(予約スキル, CV::最大スキル予約数);
			AddItem(Pスキル , CV::上限Pスキル種類);
			AddItem(Aスキル , CV::上限Aスキル種類);


			AddItem(予約スキル枠);
			AddItem(装備スキル枠);
			AddItem(習得スキル枠);

			AddItem(前後[0]);
			AddItem(前後[1]);

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
				if (ギルメン->スキル習得予約[i] == 0) { break; }

				予約スキル[i].is表示 = true;
				cnt++;
			}

			//予約スキル16個以上で調整を入れる
			//63*15 = 合計 945になるよう調整

			if (cnt <= 16)
			{
				Layout::Data(LSkill::予約スキル).並べx = 63;
			} else {
				Layout::Data(LSkill::予約スキル).並べx = 945.0 / (cnt-1);
			}

		}
	};
}