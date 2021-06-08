//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*パーティウィンドウ*/
	class W_Party: public UIWindow
	{
	private:
		//探索者子オブジェクト
		class UI装飾品 : public UIObject
		{
		public:
			int 装備スロット = 2;
			int パーティID;
			int 隊列ID;

			void Draw派生() override
			{
				DrawUI(isOver ? UIType::明ボタン : UIType::平ボタン , Design::UI);
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID]->装備[装備スロット];

				it->image->DrawRotate({ GetCenterX() , GetCenterY() }, 1, 0);
			}

			void Click() override
			{
				W_Drag::ギルメン装備.メンバー = Guild::P->パーティ[パーティID].メンバー[隊列ID];
				W_Drag::ギルメン装備.部位 = 装備スロット;			
			}

			bool Drop() override
			{
				//他ギルメン装備
				if (W_Drag::ギルメン装備.メンバー != nullptr)
				{
					Guild::P->操作_装備スワップ(Guild::P->パーティ[パーティID].メンバー[隊列ID] , 装備スロット , W_Drag::ギルメン装備.メンバー , W_Drag::ギルメン装備.部位);
				}
				//装備在庫
				if (W_Drag::所持装備 != nullptr)
				{
					Guild::P->操作_装備在庫(Guild::P->パーティ[パーティID].メンバー[隊列ID], W_Drag::所持装備->ID , 装備スロット);
				}

				return false;
			}

			void DrawHelp() override
			{
				UIHelp::Item( Guild::P->パーティ[パーティID].メンバー[隊列ID]->装備[装備スロット], false);
			}
		};

		class UI装備 : public UIObject
		{
		public:
			int 装備スロット = 0;
			int パーティID;
			int 隊列ID;

			void Draw派生() override
			{
				auto* member = Guild::P->GetMember(パーティID,隊列ID);

				if (member->装備強化予約[装備スロット] == -1)
				{
					DrawUI(isOver ? UIType::凸ハイライト : UIType::凸ボタン, Design::UI);
				} else {
					DrawUI( UIType::凹ボタン, Design::UI);
				}

				auto& it = member->装備[装備スロット];

				it->image->DrawRotate({ GetCenterX() , GetCenterY() }, 1, 0);
			}

			void Click() override
			{
				Guild::P->操作_武器防具クリック(Guild::P->パーティ[パーティID].メンバー[隊列ID] , 装備スロット);
			}

			void DrawHelp() override
			{
				UIHelp::Item( Guild::P->パーティ[パーティID].メンバー[隊列ID]->装備[装備スロット], true);
			}
		};

		class UIスキルボタン : public UIObject
		{
		public:
			inline static W_Skilltree スキルツリー;
			int パーティID;
			int 隊列ID;

			UIスキルボタン()
			{
				SetHelp(&TH::Party::スキルボタン);
			}

			void Draw派生() override
			{
				DrawUI( isOver ? UIType::凸ハイライト : UIType::凸ボタン, Design::UI);
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID];

				auto& LA = LData(LParty::探索者スキルボタン);
				//スキル
				//ポイント余りやらの状況
				GetFont()->Draw({ GetX() + LA.x ,GetY() + LA.y }, Design::暗字, {"スキル"});
			}

			void Click() override
			{
				スキルツリー.SetMember(Guild::P->パーティ[パーティID].メンバー[隊列ID]);
				スキルツリー.Init();
				スキルツリー.OpenPopup();
			}
		};

		//パーティ子オブジェクト
		class UI探索者 : public UIObject
		{
		public:
			UIスキルボタン スキルボタン;
			UI装備 装備ボタン[2];
			UI装飾品 装飾品ボタン;

			int パーティID;
			int 並びID;

			UI探索者()
			{
				スキルボタン.SetUI(LParty::探索者スキル, 0, this);
				装備ボタン[0].SetUI(LParty::探索者装備, 0, this);
				装備ボタン[1].SetUI(LParty::探索者装備, 2, this);
				装飾品ボタン.SetUI(LParty::探索者装備, 4, this);
			}


			void SetID(int パーティID,int 隊列ID)
			{
				this->パーティID = パーティID;
				this->並びID = 隊列ID;

				スキルボタン.パーティID = パーティID;
				スキルボタン.隊列ID = 並びID;

				for (int i = 0; i < 2; i++)
				{
					装備ボタン[i].装備スロット = i;
					装備ボタン[i].パーティID = パーティID;
					装備ボタン[i].隊列ID = 隊列ID;
				}
				装飾品ボタン.装備スロット = 2;
				装飾品ボタン.パーティID = パーティID;
				装飾品ボタン.隊列ID = 隊列ID;
			}

			void Draw派生() override
			{
				auto& it = Guild::P->パーティ[パーティID].メンバー[並びID];

				auto& LA = Layout::Data(LParty::探索者ドット);
				auto& LB = Layout::Data(LParty::探索者Lv);
				auto& LC = Layout::Data(LParty::探索者経験値);


				//配置している場合の表示
				if (it == nullptr)
				{
					//全体枠
					DrawUI(isOver && W_Drag::探索者.メンバー != nullptr ? UIType::明ボタン : UIType::暗ボタン, Design::UI);
					return;
				}

				//全体枠
				DrawUI(isOver ? UIType::明ボタン : UIType::暗ボタン, Design::UI);

				it->image[0][4]->DrawRotate({ GetX() + LA.x ,GetY() + LA.y }, 2, 0);

				//経験値バー
				Design::No1->DrawGauge(GetX() + LC.x, GetY() + LC.y, LC.w, LC.h, it->Get経験値率());

				//Lv
				GetFont()->DrawBold({ GetX() + LB.x , GetY() + LB.y }, Design::暗字 , Design::明字 , { "Lv " , it->Lv });

				//装備品２つ
				装備ボタン[0].Draw();
				装備ボタン[1].Draw();

				//装飾品１つ
				装飾品ボタン.Draw();

				//スキル画面ボタン
				スキルボタン.Draw();
			}

			bool Check派生(double px, double py) override
			{
				auto& it = Guild::P->パーティ[パーティID].メンバー[並びID];
				if (it == nullptr) { return false; }

				if (スキルボタン.CheckInput(px, py) == true){return true; }
				if (装飾品ボタン.CheckInput(px, py) == true){return true;}
				if (装備ボタン[0].CheckInput(px, py) == true) { return true; }
				if (装備ボタン[1].CheckInput(px, py) == true) { return true; }

				return false;
			}

			void Click() override
			{
				//探索者掴む
				W_Drag::探索者.Set(Guild::P->パーティ[パーティID].メンバー[並びID], パーティID, 並びID);
			}

			bool Drop() override
			{
				//探索者入れ替え
				if (W_Drag::探索者.メンバー != nullptr)
				{
					Guild::P->操作_配置変更(W_Drag::探索者.パーティID, W_Drag::探索者.並びID, パーティID, 並びID);
				}

				return false;
			}

			void DrawHelp() override
			{
				auto& it = Guild::P->パーティ[パーティID].メンバー[並びID];
				if (it != nullptr)
				{
					UIHelp::Explorer(it);
				}
				else
				{
					UIHelp::Text(&TH::Party::空きメンバー);
				}
			}
		};

		class UI探索フロア : public UIObject
		{
		public:
			int パーティID;
			void Draw派生() override
			{
				DrawUI(isOver ? UIType::明ボタン : UIType::平ボタン, Design::UI);
				auto& LA = LData(LParty::探索先変更三角);
				auto& LD = LData(LParty::探索先階数);
				auto* it = Guild::P->パーティ[パーティID].探索先;

				//探索先画像
				it->image->DrawRotate({ GetCenterX() + LA.並べx , GetCenterY() + LA.並べy }, 1, 0);

				//階層
				MFont::M->DrawRotate(GetPos(LD), 1, 0, Design::暗字, { it->ID + 1 , "F" });

				//三角表示
				Font* fr = mousePos == 2 ? MFont::L : MFont::S;
				Font* fl = mousePos == 1 ? MFont::L : MFont::S;

				fl->DrawRotate({ GetX() + LA.x, GetY() + LA.y + LA.h } , 1 , 0, Design::暗字, { "<" });
				fr->DrawRotate({ GetX() + LA.x + LA.w, GetY() + LA.y + LA.h }, 1, 0, Design::暗字, { ">" });
			}

			void Click() override
			{
				if (mousePos == 1)
				{
					Guild::P->パーティ[パーティID].編成_探索フロア増減(+1);
				}
				else
				{
					Guild::P->パーティ[パーティID].編成_探索フロア増減(-1);
				}
			}

			bool Drop() override
			{
				//ダンジョン
				if ( W_Drag::ダンジョン != nullptr)
				{
					Guild::P->パーティ[パーティID].探索先 = W_Drag::ダンジョン;
				}

				return false;
			}


			void Over() override
			{}

			void DrawHelp() override
			{
				//UIHelp::Dungeon(Guild::P->パーティ[パーティID].探索先);
			}
		};

		class UI探索指示 : public UIObject
		{
		public:
			int パーティID;
			void Draw派生() override
			{
				DrawUI(isOver ? UIType::明ボタン : UIType::平ボタン, Design::UI);
				GetFont()->DrawRotate( GetCenterPos(), 1, 0, Design::暗字, { "おまかせ" });

				auto& LA = LData(LParty::探索先変更三角);
				//三角表示
				Font* fr = mousePos == 2 ? MFont::L : MFont::S;
				Font* fl = mousePos == 1 ? MFont::L : MFont::S;
				fl->DrawRotate({ GetX() + LA.x, GetY() + LA.y + LA.h }, 1, 0, Design::暗字, { "<" });
				fr->DrawRotate({ GetX() + LA.x + LA.w, GetY() + LA.y + LA.h }, 1, 0, Design::暗字, { ">" });
			}

			void Click() override
			{
				if (isLeftDock == true)
				{

				}
				else {

				}
			}

			void Over() override
			{}

			void DrawHelp() override
			{
				UIHelp::Text(&TH::Party::探索指示[OrderType::なし]);
			}
		};

		class UI探索先情報 : public UIObject
		{
		public:
			int パーティID;

			void Draw派生() override
			{
				//全体枠
				DrawUI(UIType::グループ暗);

				auto* it = Guild::P->パーティ[パーティID].探索先;
				auto& LA = LData(LParty::探索先ボス);
				auto& LB = LData(LParty::探索先探索度);
				auto& LC = LData(LParty::探索先財宝数);
				auto& LD = LData(LParty::探索先内枠);

				//フロア移動とダンジョンアイコン、探索指示は別オブジェクト
				Design::No1->Draw(UIType::グループ中, GetX() + LD.x , GetY() + LD.y , LD.w , LD.h );

				//探索度-ゲージと％の文字表示
				Design::No1->DrawGauge(GetX() + LB.x , GetY() + LB.y , LB.w , LB.h , it->探索率 );
				GetFont()->DrawBold({ GetX() + LB.並べx ,GetY() + LB.並べy }, Design::暗字, Design::明字, { int(it->探索率*100) , "%" });

				//ボスフラグ - マーカーで表示
				//GetFont()->DrawRotate( GetPos(LA) , 1, 0, Design::暗字, { it->isボス生存 , " ボス生存" });

				//宝箱回収率
				GetFont()->DrawRotate( GetPos(LC), 1, 0, Design::暗字, { "財宝 "  , it->発見財宝数 , " / " , it->最大財宝数 });
			}

			bool Drop() override
			{
				return false;
			}

			void DrawHelp() override
			{
				//UIHelp::Dungeon(Guild::P->パーティ[パーティID].探索先);
			}
		};

		//ウィンドウ子オブジェクト
		class UIパーティ : public UIObject
		{

		public:
			Guild::Party* パーティ;
			UI探索先情報 探索先;
			UI探索フロア 探索フロア;
			UI探索指示 探索指示;
			UI探索者 探索者[CV::パーティ人数];

			UIパーティ()
			{
				パーティ = nullptr;
				探索先.SetUI(LParty::探索先枠,0,this);
				探索フロア.SetUI(LParty::探索先フロア, 0, &探索先);
				探索指示.SetUI(LParty::探索先指示, 0, &探索先);

				探索先.パーティID = lineID;
				探索フロア.パーティID = lineID;
				探索指示.パーティID = lineID;

				for (int i = 0; i < CV::パーティ人数; i++)
				{
					探索者[i].SetUI(LParty::探索者枠, i,this);
				}
			}

			void Init(Guild::Party* パーティ)
			{
				this->パーティ = パーティ;
				探索先.パーティID = パーティ->パーティID;
				for (int i = 0; i < CV::パーティ人数; i++)
				{
					探索者[i].SetID(パーティ->パーティID, i);
				}
			}

			bool Check派生(double px, double py) override
			{
				if (パーティ->探索状態 == ExplorType::編成中)
				{

					if (探索フロア.CheckInput(px, py) == true) { return true; }
					if (探索指示.CheckInput(px, py) == true) { return true; }
					if (探索先.CheckInput(px, py) == true) { return true; }

					for (int i = 0; i < CV::パーティ人数; i++)
					{
						if (探索者[i].CheckInput(px, py) == true) { return true; }
					}
				}

				return false;
			}

			void Draw派生() override
			{

				if (パーティ->探索状態 == ExplorType::編成中)
				{
					Draw街();
				}
				else
				{
					Drawダンジョン();
				}

				//探索先情報は街でもダンジョンでも共通
				探索先.Draw();
				探索フロア.Draw();
				探索指示.Draw();
			}

			void Click() override
			{
				if(パーティ->探索状態 == ExplorType::リザルト中)
				{
					//探索完了後にクリックで街モードに即帰還
					パーティ->探索状態 = ExplorType::編成中;
				}
			}

			bool Drop() override
			{
				if (パーティ->探索状態 != ExplorType::編成中) { return false; }
				//ドロップ操作無し？
				return false;
			}

			//街と探索中で分ける
			void Draw街()
			{
				//全体枠
				DrawUI(UIType::グループ明);
				//パーティメンバー５人
				for (auto& it : 探索者)
				{
					it.Draw();
				}
			}

			void Drawダンジョン()
			{

				//全体枠
				DrawUI(UIType::明ボタン);

				//背景表示
				auto& LA = Layout::Data(LBattle::背景);
				Screen::SetClip({GetX()+LA.x,GetY()+LA.y,LA.w,LA.h});

				Draw背景();

				//味方表示
				for (int i = 0; i < パーティ->味方.size(); i++)
				{
					switch (i)
					{
						case 0:Draw味方(パーティ->メンバー[i], Layout::Data(LBattle::味方A) );break;
						case 1:Draw味方(パーティ->メンバー[i], Layout::Data(LBattle::味方B)); break;
						case 2:Draw味方(パーティ->メンバー[i], Layout::Data(LBattle::味方C)); break;
						case 3:Draw味方(パーティ->メンバー[i], Layout::Data(LBattle::味方D)); break;
						case 4:Draw味方(パーティ->メンバー[i], Layout::Data(LBattle::味方E)); break;
					}					
				}

				//敵表示
				for (int i = 0; i < パーティ->敵.size(); i++)
				{
					switch (i)
					{
						case 0:Draw敵(パーティ->魔物[i], Layout::Data(LBattle::敵A)); break;
						case 1:Draw敵(パーティ->魔物[i], Layout::Data(LBattle::敵B)); break;
						case 2:Draw敵(パーティ->魔物[i], Layout::Data(LBattle::敵C)); break;
						case 3:Draw敵(パーティ->魔物[i], Layout::Data(LBattle::敵D)); break;
						case 4:Draw敵(パーティ->魔物[i], Layout::Data(LBattle::敵E)); break;
						case 5:Draw敵(パーティ->魔物[i], Layout::Data(LBattle::敵F)); break;
					}

				}

				//戦闘エフェクト表示
				Drawエフェクト();

				//素材、財宝、地図の表示
				Drawオブジェクト();

				if (パーティ->探索状態 == ExplorType::リザルト中)
				{
					Drawリザルト();
				}

				Screen::SetClip();
			}

			void Draw背景()
			{
				auto& LA = Layout::Data(LBattle::背景);

				//背景スクロール描画
				Image* image = &MSystem::ダンジョン背景[0];

				//画像は幅の２倍でループするようにしておく
				if (パーティ->移動量 + LA.w > image->GetWidth())
				{
					パーティ->移動量 = 0;
				}
				
				MSystem::ダンジョン背景[0].DrawPart({ GetX() + LA.x , GetY() + LA.y }, { パーティ->移動量, 0 , LA.w - LA.x * 2 ,GetH() - LA.y * 2 });
			}

			void Drawリザルト()
			{

				auto& LA = Layout::Data(LBattle::リザルト枠);
				auto& LB = Layout::Data(LBattle::リザルトキャラ);
				auto& LC = Layout::Data(LBattle::リザルト経験値バー);
				auto& LD = Layout::Data(LBattle::リザルト演出文字);
				auto& LE = Layout::Data(LBattle::リザルト入手品);
				auto& LF = Layout::Data(LBattle::リザルト入手品文字);

				//リザルト枠
				Screen::SetBlendMode(BlendMode::Alpha, 128);
				Design::Blue.Draw(UIType::平ボタン , LA);
				Screen::SetBlendMode();


				//味方5人
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					auto it = パーティ->メンバー[a];
					if (it == nullptr) { continue; }
					//キャラ
					auto ptc = LB.GetPos(a);
					it->image[0][1]->DrawRotate({ GetX() + ptc.x , GetY() + ptc.y }, 2, 0);
					//経験値バー-獲得分の表示
					int バー幅 = 0;
					double 経験値割合 = it->経験値 / it->Get要求経験値();
					double 探検前割合 = (double)it->探検前経験値 / it->Get要求経験値();

					if (it->レベルアップ演出)
					{
						経験値割合 = 1.0;
					}

					auto ptg = LC.GetPos(a);
					Design::Blue.DrawGauge(GetX() + ptg.x, GetY() + ptg.y, LC.w, LC.h,0.5);


					auto ptt = LD.GetPos(a);

					//LvUPとスキル習得の文字
					if (it->レベルアップ演出 >= 0)
					{
						it->レベルアップ演出++;
						MFont::M->DrawBold({ GetX() + ptt.x  , GetY() + ptt.y - it->レベルアップ演出 }, Color::White, Color::Black, "Lv UP");
						if (it->レベルアップ演出 == 40)
						{
							it->レベルアップ演出 = -1;
						}
					}
				}
				int cnt = 0;

				//ボス
				for (int i = 0; i < パーティ->ボス撃破数; i++)
				{
					auto ptb = LE.GetPos(cnt);
					MIcon::UI[IconType::ボス].DrawRotate({ GetX() + ptb.x , GetY() + ptb.y }, 2, 0);
					cnt++;
				}

				//階段
				for (int i = 0; i < パーティ->ボス撃破数; i++)
				{
					auto ptb = LE.GetPos(cnt);
					MIcon::UI[IconType::地図].DrawRotate({ GetX() + ptb.x , GetY() + ptb.y }, 2, 0);
					cnt++;
				}

				//宝箱
				for (int i = 0; i < パーティ->ボス撃破数; i++)
				{
					auto ptb = LE.GetPos(cnt);
					MIcon::UI[IconType::宝箱].DrawRotate({ GetX() + ptb.x , GetY() + ptb.y }, 2, 0);
					cnt++;
				}

				//素材
				for (int a = 0; a < CV::素材系統; a++)
				{
					if (パーティ->獲得素材[a] <= 0) { continue; }

					auto ptb = LE.GetPos(cnt);
					auto& it = Material::data[a];

					it.image->DrawRotate({ GetX() + ptb.x , GetY() + ptb.y }, 1, 0);
					//Lv表示
					MFont::S->DrawBold({ GetX() + ptb.x + LF.x , GetY() + ptb.y + LF.y }, Design::明字 , Design::暗字 , { "★" , it.ランク });

					//素材数表示
					MFont::S->DrawBold({ GetX() + ptb.x + LF.w, GetY() + ptb.y + LF.h }, Design::明字 , Design::暗字, { "x", パーティ->獲得素材[a] });
					cnt++;
				}
			}

			void Draw味方(Explorer* it, Layout& layout )
			{
				auto& LA = Layout::Data(LBattle::ライフバー);
				auto& LB = Layout::Data(LBattle::行動バー);

				int px = GetX() + layout.x;
				int py = GetY() + layout.y;

				bool is反転 = false;
				int 向き = 0;
				double サイズ = 2;
				//探索直後は画面外から走ってくる
				if (Game::時間 < Game::始業時間 + CV::探索開始時移動時間)
				{
					px += (Game::時間 - Game::始業時間 - CV::探索開始時移動時間) * 3;
				}

				switch (パーティ->探索状態)
				{
				case ExplorType::移動中://パーティメンバーのみ、歩くモーション
					向き = 3 + (Game::時間 / 10 % 2);
					break;
				case ExplorType::リザルト中://枠表示、LvUP、探索成果、活躍表示
					向き = 1;
					break;
				case ExplorType::戦闘中://武器装備ドット
					向き = 7;
					break;
				case ExplorType::収集中://木 or 岩に対して収集アニメーション
					if (パーティ->発見物X座標 > 0)
					{
						向き = 3 + (Game::時間 / 10 % 2);
					} else {
						向き = 4;
					}
					break;
				case ExplorType::全滅中://全滅表示
					向き = 1;
					break;
				case ExplorType::撤退中://モンスターそのままで後ろ向きにギルメン逃走
					is反転 = true;
					向き = 3 + (Game::時間 / 5 % 2);
					break;
				}

				//→向き
				double 角度 = 0;
				if (it->現在HP <= 0)
				{
					角度 = PAI / 2;
					向き = 4;
				}

				//ダメージ発行エフェクト
				it->image[0][向き]->DrawRotate({ px + (int)it->E座標,py }, サイズ, 角度, is反転);
				if (it->E光強さ > 0)
				{
					Screen::SetBlendMode(BlendMode::Add, int(it->E光強さ * 255));
					it->image[0][向き]->SetColor(it->E光色);
					it->image[0][向き]->DrawRotate({ px + (int)it->E座標,py }, サイズ, 角度 , is反転);
					it->image[0][向き]->SetColor(Color::White);
					Screen::SetBlendMode();
				}

				if (パーティ->探索状態 == ExplorType::撤退中 || パーティ->探索状態 == ExplorType::リザルト中) { return; }

				//ライフバー
				int バー幅 = 0;
				Design::No1->DrawGauge( px + LA.x - LA.w / 2 , py + LA.y, LA.w, LA.h, (double)it->現在HP / it->補正ステ[StatusType::HP] );

				//行動バー
				Design::Green.DrawGauge(px + LB.x - LB.w / 2, py + LB.y, LB.w, LB.h, 0.5 );
			}

			void Draw敵(Monster& it, Layout& layout)
			{
				auto& LA = Layout::Data(LBattle::ライフバー);
				auto& LB = Layout::Data(LBattle::行動バー);

				int px = layout.x + GetX();
				int py = layout.y + GetY();

				//←向き
				if (it.現在HP <= 0)
				{
					if (it.消滅中 <= 0) { return; }
					Screen::SetDrawMode(Color(it.消滅中, it.消滅中, it.消滅中), BlendMode::Add);
					if (Game::is停止 == false) { it.消滅中 -= 10 * Game::ゲームスピード; }
				}


				auto img = it.種族->image;
				int 向き = 7;
				double サイズ = 2;

				if (it.isボス)
				{
					サイズ = 4;
					px += 0;
					py += 0;
				}

				img[0][向き]->DrawRotate({ px - (int)it.E座標,py }, サイズ, 0);
				if (it.E光強さ > 0)
				{
					Screen::SetBlendMode(BlendMode::Add, int(it.E光強さ * 255));
					img[0][向き]->SetColor(it.E光色);
					img[0][向き]->DrawRotate({ px - (int)it.E座標,py }, サイズ, 0);
					img[0][向き]->SetColor(Color::White);
					Screen::SetBlendMode();
				}

				int ボスY = (it.isボス) ? 0 : 0;

				int gageW = LA.w;
				int gageH = LA.h;

				if (it.isボス)
				{
					gageW *= 2;
					gageH *= 2;
				}

				Screen::SetDrawMode();
				Screen::SetBright(Color(パーティ->暗転, パーティ->暗転, パーティ->暗転));

				//ライフバー
				Design::No1->DrawGauge(px + LA.x - gageW / 2, py + LA.y, LA.w, LA.h, (double)it.現在HP / it.補正ステ[StatusType::HP]);

				//行動バー
				Design::Green.DrawGauge(px + LB.x - gageW / 2, py + LB.y, LB.w, LB.h, 0.5);
			}

			void Drawエフェクト()
			{
				auto& L味方A = Layout::Data(LBattle::味方A);
				auto& L味方B = Layout::Data(LBattle::味方B);
				auto& L味方C = Layout::Data(LBattle::味方C);
				auto& L味方D = Layout::Data(LBattle::味方D);
				auto& L味方E = Layout::Data(LBattle::味方E);

				auto& L敵A = Layout::Data(LBattle::敵A);
				auto& L敵B = Layout::Data(LBattle::敵B);
				auto& L敵C = Layout::Data(LBattle::敵C);
				auto& L敵D = Layout::Data(LBattle::敵D);
				auto& L敵E = Layout::Data(LBattle::敵E);
				auto& L敵F = Layout::Data(LBattle::敵F);

				//スキルエフェクト
				for (auto& it : Effect::アニメ[パーティ->パーティID])
				{
					Layout* PL = nullptr;

					if (it.is味方)
					{
						switch (it.配置ID)
						{
							case 0: PL = &L味方A; break;
							case 1: PL = &L味方B; break;
							case 2: PL = &L味方C; break;
							case 3: PL = &L味方D; break;
							case 4: PL = &L味方E; break;
						}
					} else {
						switch (it.配置ID)
						{
							case 0: PL = &L敵A; break;
							case 1: PL = &L敵B; break;
							case 2: PL = &L敵C; break;
							case 3: PL = &L敵D; break;
							case 4: PL = &L敵E; break;
							case 5: PL = &L敵F; break;
						}

					}
					it.Draw( GetX() + PL->x , GetX() + PL->x, 0.4);
				}

				//文字エフェクト
				for (auto& it : Effect::文字[パーティ->パーティID])
				{
					Layout* PL = nullptr;

					if (it.is味方)
					{
						switch (it.配置ID)
						{
						case 0: PL = &L味方A; break;
						case 1: PL = &L味方B; break;
						case 2: PL = &L味方C; break;
						case 3: PL = &L味方D; break;
						case 4: PL = &L味方E; break;
						}
					}
					else {
						switch (it.配置ID)
						{
						case 0: PL = &L敵A; break;
						case 1: PL = &L敵B; break;
						case 2: PL = &L敵C; break;
						case 3: PL = &L敵D; break;
						case 4: PL = &L敵E; break;
						case 5: PL = &L敵F; break;
						}

					}

					int px = GetX() + PL->x + it.座標X;
					int py = GetY() + PL->y + it.座標Y;

					switch (it.種類)
					{
					case TextEffect::TextType::ダメージ:
						MFont::MAlias.DrawBoldRotate({ px , py }, 1, 0, it.ダメージ色, Color::Black, it.ダメージ量);
						break;
					case TextEffect::TextType::回復:
						MFont::MAlias.DrawBoldRotate({ px , py }, 1, 0, it.回復色, Color::Black, it.ダメージ量);
						break;
					case TextEffect::TextType::回避:
						MFont::SAlias.DrawBoldRotate({ px , py }, 1, 0, Color::White, Color::Black, "miss");
						break;
					}

				}
			}

			void Drawオブジェクト()
			{

				auto& LA = Layout::Data(LBattle::オブジェ);
				int px,py;

				auto& L敵A = Layout::Data(LBattle::敵A);
				auto& L敵B = Layout::Data(LBattle::敵B);
				auto& L敵C = Layout::Data(LBattle::敵C);
				auto& L敵D = Layout::Data(LBattle::敵D);
				auto& L敵E = Layout::Data(LBattle::敵E);
				auto& L敵F = Layout::Data(LBattle::敵F);

				//収集オブジェクトと財宝
				if (パーティ->発見物 != nullptr)
				{
					パーティ->発見物->DrawRotate({ GetX() + パーティ->発見物X座標 + LA.x , GetY() + LA.y },2,0);
				}

				//素材獲得エフェクト
				for (auto& it : Effect::素材[パーティ->パーティID])
				{
					if (it.隠れ時間 > 0) { continue; }

					//敵素材の場合
					if (it.配置ID < 0)
					{
						px = GetX() + LA.x + it.座標X;
						py = GetY() + LA.y + it.座標Y;
					} else {

						Layout* PL = nullptr;

						switch (it.配置ID)
						{
							case 0: PL = &L敵A; break;
							case 1: PL = &L敵B; break;
							case 2: PL = &L敵C; break;
							case 3: PL = &L敵D; break;
							case 4: PL = &L敵E; break;
							case 5: PL = &L敵F; break;
						}

						px = GetX() + PL->x + it.座標X;
						py = GetY() + PL->y + it.座標Y;
					}

					it.image->DrawRotate({ px , py }, 2, 0);
				}
			}

		};

		class UI控え探検者 : public UIObject
		{
		public:
			Explorer* 探索者 = nullptr;
			void Draw派生() override
			{
				auto& LA = Layout::Data(LParty::控えドット);
				auto& LB = Layout::Data(LParty::控えLv);

				//ボタン枠-掴み中だと凹み
				DrawUI(isOver ? UIType::明ボタン : UIType::平ボタン, Design::UI);

				//キャラ画像
				探索者->image[0][1]->DrawRotate( { GetCenterX() + LA.x , GetCenterY() + LA.y }, 2 , 0);

				//Lv
				GetFont()->Draw({ GetCenterX() + LB.x , GetCenterY() + LB.y } , Design::暗字 , { "Lv " , 探索者->Lv });
			}

			void Click() override
			{
				//掴む
				W_Drag::探索者.Set( 探索者 , -1 , lineID-1);
				MSound::効果音[SE::ドラッグ].Play();
			}

			bool Drop() override
			{
				//並び替える
				//探索者->ID;
				if (W_Drag::探索者.メンバー != nullptr)
				{
					//ギルメン入れ替え
					Guild::P->操作_配置変更(W_Drag::探索者.パーティID, W_Drag::探索者.並びID,-1,lineID-1);
				}
				else if(W_Drag::所持装備 != nullptr)
				{
					//アクセサリー交換
					Guild::P->操作_装備在庫(探索者, W_Drag::所持装備->ID ,2);
				}
				else if (W_Drag::ギルメン装備.メンバー != nullptr)
				{
					//パーティメンバーとアクセサリー交換
					Guild::P->操作_装備スワップ(探索者 , 2 , W_Drag::ギルメン装備.メンバー , W_Drag::ギルメン装備.部位);
				}

				return false;

			}


			void DrawHelp() override
			{
				UIHelp::Explorer( 探索者);
			}
		};
	public:
		W_Recruit 求人ウィンドウ;
		W_Popup 除名ウィンドウ;

		UIパーティ パーティ[CV::上限パーティ数];
		UITextFrame 控え枠;
		UI控え探検者 控え[CV::最大控え人数];
		UIButton 除名;
		UIButton 登録;

		void Init()
		{
			求人ウィンドウ.Init();
			除名ウィンドウ.Init(WindowType::Delete);

			Set(種類 = WindowType::Party, IconType::編成);
			SetPos(LParty::ウィンドウ, false, true, false);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化
			int a = -1;
			for (auto& it : パーティ)
			{
				a++;
				it.SetUI(LParty::パーティ枠, a);
				it.Init(&Guild::P->パーティ[a]);				
			}

			登録.SetUI(LParty::控え探索者, &MIcon::UI[IconType::ゴミ箱], "登録",  0, &控え枠);
			除名.SetUI(LParty::控え探索者, &MIcon::UI[IconType::ゴミ箱], "除名",  CV::最大控え人数, &控え枠);
			除名.is押下 = true;//平状態で固定
			除名.押下状態 = 2;
			
			a = 0;//0の位置に登録を置くので1から
			for (auto& it : 控え)
			{
				a++;
				it.SetUI(LParty::控え探索者, a , &控え枠);
				it.探索者 = Guild::P->控え探索者[a-1];
				if (it.探索者 == nullptr) { it.is表示 = false; }
			}
			控え枠.SetUI(LParty::控え枠 ,"" );

			//●登録
			item.clear();
			AddItem(パーティ , CV::上限パーティ数);
			AddItem(登録);
			AddItem(除名);
			AddItem(控え, CV::最大控え人数);
			AddItem(控え枠);

			//●イベント
			登録.clickEvent = [&]()
			{
				求人ウィンドウ.OpenPopup();
				登録.isOver = false;
			};
			
			除名.dropEvent = [&]()
			{
				if (W_Drag::探索者.メンバー != nullptr)
				{
					除名ウィンドウ.OpenPopup();
					if (除名ウィンドウ.ポップアップリザルト == 1)
					{
						Guild::P->操作_除名(W_Drag::探索者.メンバー);
					}
					W_Drag::探索者.メンバー = nullptr;
				}

				return true;
			};

			控え枠.dropEvent = [&]()
			{
				if (W_Drag::探索者.メンバー != nullptr)
				{
					//ギルメン入れ替え
					Guild::P->操作_控え移動(W_Drag::探索者.パーティID, W_Drag::探索者.並びID);
				}
				return true;
			};

			//●ヘルプ設定
			登録.SetHelp(&TH::Party::登録);
			除名.SetHelp(&TH::Party::除名);

		}

		void Update()
		{
			SetPos(LParty::ウィンドウ, false, true, false);

			int a = -1;
			for (auto& it : パーティ)
			{
				a++;
				it.is表示 = it.lineID < Guild::P->最大パーティ数;
				
			}

			a = -1;
			for (auto& it : 控え)
			{
				a++;
				it.探索者 = Guild::P->控え探索者[a];
				it.is表示 = (it.探索者 != nullptr);
			}
			//控え枠の位置はパーティ数で変化			
			auto& LA = Layout::Data(LParty::パーティ枠);
			auto& LB = Layout::Data(LParty::控え枠);

			LB.y = LA.並べy * Guild::P->最大パーティ数 + LB.並べy;

			//パーティ数に応じて内部幅を計算
			縦内部幅 = LB.y + LB.h + LB.並べy * 2;
		}

	};
}