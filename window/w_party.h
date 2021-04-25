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

		//旧UI
		class GUI_探索先 : public GUI_Object
		{
		public:
			int パーティID;
			Guild::Party* 所属;
			W_Party* 親ウィンドウ;

			void Init(int パーティID, W_Party* 親ウィンドウ)
			{
				this->パーティID = パーティID;
				所属 = &Guild::P->パーティ[パーティID];
				this->親ウィンドウ = 親ウィンドウ;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 11);

				auto dun = Guild::P->パーティ[パーティID].探索先;

				if (所属->探索状態 == ExplorerType::編成中 || 所属->探索状態 == ExplorerType::リザルト中)
				{
					MSystem::DrawWindow({ px + Lp(70) ,py + Lp(71) }, Lp(72), Lp(73), 0, 1);
					MIcon::UI[IconType::三角].Draw({ px + Lp(74),py + Lp(76) });
					MIcon::UI[IconType::三角].Draw({ px + Lp(75),py + Lp(76) }, true);
				} else {
					MSystem::DrawWindow({ px + Lp(70) ,py + Lp(71) }, Lp(72), Lp(73), 1, 0);
				}

				//探索先アイコン、レベル
				dun->image->Draw({ px + Lp(12),py + Lp(13) });
				MFont::SAlias.Draw({ px + Lp(14) ,py + Lp(15) }, Design::暗字, { "Lv ", dun->雑魚Lv });
				//探索度ゲージと探索率
				MSystem::DrawBar({ px + Lp(18) , py + Lp(19) }, Lp(20), Lp(21), dun->探索率, 1 , Color::Blue, Color::White, Color::White, true);				
				MFont::SAlias.Draw({ px + Lp(16) ,py + Lp(17) }, Design::暗字, { (int)(dun->探索率 * 100) , "%" }, true);
				//ボス状態
				MIcon::UI[IconType::ボス].DrawRotate({ px + Lp(22),py + Lp(23) }, 1, 0);

				std::string sボス状態;
				if (dun->isボス生存 == false)
				{
					sボス状態 = TX::Dungeon_討伐;
				}
				else if(dun->isボス発見 == true)
				{
					sボス状態 = TX::Dungeon_発見;
				}
				else
				{
					sボス状態 = TX::Dungeon_捜索;
				}

				MFont::SAlias.DrawBold({ px + Lp(22) + 50 ,py + Lp(23) - 9 }, Color::White, Color::Black, sボス状態, true);
				//地図状態
				MIcon::UI[IconType::地図].DrawRotate({ px + Lp(22),py + Lp(24) }, 1, 0);
				//財宝状態
				MIcon::UI[IconType::宝箱].DrawRotate({ px + Lp(22),py + Lp(25) }, 1, 0);
				
				//探索指示-冒険中は三角を非表示
				if (所属->探索状態 == ExplorerType::編成中 || 所属->探索状態 == ExplorerType::リザルト中)
				{
					MSystem::DrawWindow({ px + Lp(31) ,py + Lp(32) }, Lp(33), Lp(34), 0, 1);
					MIcon::UI[IconType::三角].Draw({ px + Lp(26),py + Lp(28) });
					MIcon::UI[IconType::三角].Draw({ px + Lp(27),py + Lp(28) }, true);

				} else {
					MSystem::DrawWindow({ px + Lp(31) ,py + Lp(32) }, Lp(33), Lp(34), 1, 0);
				}

				std::string siji;
				siji = TX::Party_ボス回避;

				MFont::SAlias.DrawBold({ px + Lp(29) ,py + Lp(30) }, Color::White, Color::Black, siji, true);
			}

			void Click(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中 && 所属->探索状態 != ExplorerType::リザルト中) { return; }

				//探索指示変更
				if (Point(px, py).Hit(&Rect(Lp(31), Lp(32), Lp(33), Lp(34))) == true)
				{
					int n = int(Guild::P->パーティ[パーティID].探索指示);

					if (px < Lp(31) + Lp(33) / 2) { n--; }
					else { n++; }


					if (n == (int)OrderType::COUNT) { n = 0; }
					if (n <  0) { n = (int)OrderType::COUNT - 1; }

					Guild::P->パーティ[パーティID].探索指示 = OrderType(n);
					MSound::効果音[SE::ボタンクリック].Play();
				}
				//探索先変更
				if (Point(px, py).Hit(&Rect(Lp(70), Lp(71), Lp(72), Lp(73))) == true)
				{
					bool result = false;

					if (px < Lp(70) + Lp(72) / 2) { result = 所属->探索先前後(false); }
					else { result = 所属->探索先前後(true); }

					if (result) { MSound::効果音[SE::ボタンクリック].Play(); }
				}
			}

			void Drop(double px, double py)
			{
				if (W_Drag::ダンジョン == nullptr) { return; }
				if (所属->探索状態 != ExplorerType::編成中 && 所属->探索状態 != ExplorerType::リザルト中)
				{ 
					MSound::効果音[SE::配置換え].Play();
					return;
				}

				//探索先変更
				所属->探索先 = W_Drag::ダンジョン;
				MSound::効果音[SE::配置換え].Play();
			}

			void Info派生(Point 座標) override
			{
				Point 補正座標;
				補正座標.x = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;
				補正座標.y = 座標.y - 親ウィンドウ->相対座標.y - 位置.y;


				if (補正座標.Hit(&Rect(Lp(31), Lp(32), Lp(33), Lp(34))) == true)
				{
					//探索指示や入れ替え等の操作方法
					SetHelp( TX::Party_探索方針);
					Info座標補正(座標);
					MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 4);
					MFont::MDot.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
				}
				else 
				{
					//探索方針
					InfoDungeon(Guild::P->パーティ[パーティID].探索先, 座標);
				}
			}

		};
		class GUI_パーティメンバー : public GUI_Object
		{
		public:
			W_Skilltree* スキルツリー;
			Explorer* ギルメン;
			Guild::Party* 所属;
			W_Party* 親ウィンドウ;
			int 並びID;//1パーティ目 0~4、22パーティ目5～9 ...

			void Draw派生(double px, double py)
			{

			}

			void Click(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中) { return; }
				if (ギルメン == nullptr) { return; }

				//装備掴み
				if (Point(px, py).Hit(&Rect(Lp(43), Lp(46), Lp(48), Lp(49))) == true)
				{
					W_Drag::ギルメン装備.メンバー = ギルメン;
					W_Drag::ギルメン装備.部位 = 0;
					return;
				}

				if (Point(px, py).Hit(&Rect(Lp(44), Lp(46), Lp(48), Lp(49))) == true)
				{
					W_Drag::ギルメン装備.メンバー = ギルメン;
					W_Drag::ギルメン装備.部位 = 1;
					return;
				}

				if (Point(px, py).Hit(&Rect(Lp(45), Lp(47), Lp(48), Lp(49))) == true)
				{
					W_Drag::ギルメン装備.メンバー = ギルメン;
					W_Drag::ギルメン装備.部位 = 2;
					return;
				}

				//自動更新切り替え
				if (Point(px, py).Hit(&Rect(Lp(55), Lp(56), Lp(57), Lp(58))) == true)
				{
					//ギルメン->is装備更新 = !ギルメン->is装備更新;
					//MSound::効果音[SE::ボタンクリック].Play();
					スキルツリー->SetMember(ギルメン);
					スキルツリー->Init();
					スキルツリー->OpenPopup();
					所属->基礎ステ再計算();

					return;
				}

				//ギルメン掴む
				W_Drag::探索メン = ギルメン;
				//W_Drag::並びID = 並びID;
				MSound::効果音[SE::ドラッグ].Play();
			}

			void Drop(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中) { return; }

				if (W_Drag::探索メン != nullptr)
				{
					//ギルメン入れ替え
					//Guild::P->パーティ移動( W_Drag::探索メン, W_Drag::並びID , ギルメン , 並びID);
				}
				else if(W_Drag::所持アーティファクト != nullptr && ギルメン != nullptr)
				{
					//装備変更
					int 部位 = 0;
					if (W_Drag::所持アーティファクト->種類 == ItemType::アクセサリー)
					{
						部位 = 2;
					}else if (W_Drag::所持アーティファクト->種類 == ItemType::外套 ||
						W_Drag::所持アーティファクト->種類 == ItemType::軽鎧 ||
						W_Drag::所持アーティファクト->種類 == ItemType::重鎧 ||
						W_Drag::所持アーティファクト->種類 == ItemType::軽装 )
					{
						部位 = 1;
						if (W_Drag::所持アーティファクト->種類 != ギルメン->職業->防具種)
						{
							return;
						}
					}

					//武器は装備種があってないと交換不可
					if (部位 == 0 && W_Drag::所持アーティファクト->種類 != ギルメン->職業->武器種)
					{
						return;
					}

					Guild::P->アクセサリー所持数[ギルメン->装備[部位]->ID]++;
					Guild::P->アクセサリー所持数[W_Drag::所持アーティファクト->ID]--;
					ギルメン->装備[部位] = W_Drag::所持アーティファクト;

					所属->基礎ステ再計算();
					MSound::効果音[SE::装備変更].Play();
				}
				else if (W_Drag::ダンジョン != nullptr) 
				{ 
					所属->探索先 = W_Drag::ダンジョン;
					MSound::効果音[SE::配置換え].Play();				
				}
				else if (W_Drag::ギルメン装備.メンバー != nullptr && ギルメン != nullptr)
				{
					int n = W_Drag::ギルメン装備.部位;

					//武器は装備種あってないと交換不可
					if (n == 0)
					{
						if (W_Drag::ギルメン装備.メンバー->装備[n]->種類 != ギルメン->装備[n]->種類)
						{
							return;
						}
					}

					auto buf = W_Drag::ギルメン装備.メンバー->装備[n];
					W_Drag::ギルメン装備.メンバー->装備[n] = ギルメン->装備[n];
					ギルメン->装備[n] = buf;

					for (auto& it : Guild::P->パーティ)
					{
						it.基礎ステ再計算();
					}

					MSound::効果音[SE::装備変更].Play();
				}

			}

			void Info派生(Point 座標) override
			{
				if (所属->探索状態 != ExplorerType::編成中) { return; }
				if (ギルメン == nullptr) { return; }

				Point 補正座標;
				補正座標.x = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;
				補正座標.y = 座標.y - 親ウィンドウ->相対座標.y - 位置.y;

				if (補正座標.Hit(&Rect(Lp(43), Lp(46), Lp(48), Lp(49))) )
				{
					//武器
					InfoItem(ギルメン->装備[0], 座標);
				}
				else if (補正座標.Hit(&Rect(Lp(44), Lp(46), Lp(48), Lp(49))))
				{
					//防具
					InfoItem(ギルメン->装備[1], 座標);
				}
				else if (補正座標.Hit(&Rect(Lp(45), Lp(47), Lp(48), Lp(49))))
				{
					//アクセ
					SetHelp("アクセサリー(未実装)");
					InfoMessage(座標);
				}
				else if (補正座標.Hit(&Rect(Lp(55), Lp(56), Lp(57), Lp(58))))
				{
					//Auto
					SetHelp("装備自動更新のON/OFF");
					InfoMessage(座標);
				}
				else
				{
					//ギルメン情報
					InfoExplorer(ギルメン, 座標);
				}
			}
		};
		class GUI_パーティ : public GUI_Object
		{
		public:
			int パーティID;
			Guild::Party* 所属;
			W_Party* 親ウィンドウ;

			void Init(int パーティID, W_Party* 親ウィンドウ)
			{
				this->パーティID = パーティID;
				所属 = &Guild::P->パーティ[パーティID];
				this->親ウィンドウ = 親ウィンドウ;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				
				if (所属->探索状態 == ExplorerType::編成中){ return; }

				if (所属->探索状態 == ExplorerType::リザルト中)
				{
					Draw背景(px, py);
					Drawリザルト(px, py);
					return;
				}

				//全滅時の暗転
				Screen::SetBright(Color(所属->暗転, 所属->暗転, 所属->暗転));

				//探索中のダンジョン背景
				Draw背景(px, py);

				//パーティメンバー
				for(int a = 0; a < CV::パーティ人数; a++)
				{
					if (所属->メンバー[a] == nullptr) { continue; }

					Drawギルメン(所属->メンバー[a], px + Lp(0) - Lp(1) * a, py + Lp(2 + a));
				}

				if (所属->発見物 != nullptr)
				{
					所属->発見物->DrawRotate({ Lp(14) + px + 所属->発見物X座標 ,Lp(15) + py }, 2, 0);
				}

				//敵の描画
				for (int a = 0; a < (int)所属->魔物.size(); a++)
				{
					Draw敵(所属->魔物[a], px - Lp(0) + Lp(8) + Lp(1) * a, py + Lp(2 + a));
				}

				Drawエフェクト(px,py);

				Screen::SetBright(Color::White);

				MSystem::DrawWindow({ px - 10 ,py - 10 }, 10 , (int)位置.GetH() + 20 , 11);
				//MSystem::DrawWindow({ px + 位置.GetW() ,py - 10 }, 28, (int)位置.GetH() + 20, 11);
			}

			void Draw背景(double px, double py)
			{
				//背景スクロール描画
				const int 手前W = 2, 奥W = 2;

				int w幅 = MSystem::ダンジョン背景[0].GetWidth() - 所属->移動量 + 手前W + 奥W;


				if (w幅 <= 0 ) 所属->移動量 = 0;

				if (w幅 < 位置.GetW() - 手前W - 奥W)
				{
					MSystem::ダンジョン背景[0].DrawPart({ px + 手前W + w幅 , py + 2 }, { 0    , 0 , 位置.GetW() - w幅 - 手前W - 奥W ,位置.GetH() - 4 });
					MSystem::ダンジョン背景[0].DrawPart({ px + 手前W       , py + 2 }, { 所属->移動量, 0 , w幅 , 位置.GetH() - 4 });
				} else {
					//一枚目だけ
					MSystem::ダンジョン背景[0].DrawPart({ px + 手前W , py + 2 }, { 所属->移動量, 0 , 位置.GetW() - 手前W - 奥W ,位置.GetH() - 4 });
				}
				
				//各種表示
				switch (所属->探索先->部屋[所属->部屋ID].種類)
				{
				case RoomType::ボス:
					break;
				}
			}

			void Drawギルメン(Explorer* it,double px, double py)
			{
				bool is反転 = false;
				int 向き = 0;
				double サイズ = 2;
				//探索直後は画面外から走ってくる
				if (Game::時間 < Game::始業時間 + CV::探索開始時移動時間)
				{
					px += (Game::時間 - Game::始業時間 - CV::探索開始時移動時間) * 3;
				}

				switch (所属->探索状態)
				{
				case ExplorerType::移動中://パーティメンバーのみ、歩くモーション
					向き = 3 + (Game::時間 / 5 % 2);
					break;
				case ExplorerType::リザルト中://枠表示、LvUP、探索成果、活躍表示
					向き = 1;
					break;
				case ExplorerType::戦闘中://武器をかまえる
					向き = 7;
					break;
				case ExplorerType::収集中://木 or 岩に対して収集アニメーション
					向き = 4;
					break;
				case ExplorerType::全滅中://全滅表示
					向き = 1;
					break;
				case ExplorerType::撤退中://モンスターそのままで後ろ向きにギルメン逃走
					is反転 = true;
					向き = 3 + (Game::時間 / 3 % 2);
					break;
				}

				//→向き
				double 角度 = 0;
				if (it->現在HP <= 0)
				{
					角度 = PAI / 2;
					向き = 4;
				}


				it->image[0][向き]->DrawRotate({ px + (int)it->E座標,py }, サイズ, 角度);
				if (it->E光強さ > 0)
				{
					Screen::SetBlendMode(BlendMode::Add, int(it->E光強さ * 255));
					it->image[0][向き]->SetColor(it->E光色);
					it->image[0][向き]->DrawRotate({ px + (int)it->E座標,py }, サイズ, 角度);
					it->image[0][向き]->SetColor(Color::White);
					Screen::SetBlendMode();
				}

				if (所属->探索状態 == ExplorerType::撤退中) { return; }

				//ライフバー
				int バー幅 = int(Lp(12) * サイズ);

				MSystem::DrawBar({ px + Lp(10) - バー幅 / 2,py + Lp(11) }, バー幅, Lp(13), (double)it->現在HP / it->補正ステ[StatusType::HP], 1, Color::Blue, Color::White, Color::White, true);
			}

			void Draw敵(Monster& it, double px, double py)
			{					
				//←向き
				if (it.現在HP <= 0)
				{
					if( it.消滅中 <= 0) { return; }
					Screen::SetDrawMode(Color(it.消滅中, it.消滅中, it.消滅中), BlendMode::Add);
					if (Game::is停止 == false) { it.消滅中 -= 10 * Game::ゲームスピード; }
				}
				

				auto img = it.種族->image;
				int 向き = 7;
				double サイズ = 2;

				if (it.isボス)
				{
					サイズ = 4;
					px += Lp(16);
					py += Lp(17);
				}

				img[0][向き]->DrawRotate({ px - (int)it.E座標,py }, サイズ, 0);
				if (it.E光強さ > 0 )
				{
					Screen::SetBlendMode(BlendMode::Add, int(it.E光強さ * 255));
					img[0][向き]->SetColor(it.E光色);
					img[0][向き]->DrawRotate({ px - (int)it.E座標,py }, サイズ, 0);
					img[0][向き]->SetColor(Color::White);
					Screen::SetBlendMode();
				}

				int バー幅 = int(Lp(12) * サイズ);
				int ボスY = (it.isボス) ? Lp(18) : 0;

				Screen::SetDrawMode();
				Screen::SetBright(Color(所属->暗転, 所属->暗転, 所属->暗転));

				//ライフバー
				if (it.現在HP > 0)
				{
					MSystem::DrawBar({ px + Lp(10) - バー幅 / 2 ,py + Lp(11) + ボスY }, バー幅, Lp(13), (double)it.現在HP / it.補正ステ[StatusType::HP], 1, Color::Blue, Color::White, Color::White, true);
				}
			}

			void Drawエフェクト(double px, double py)
			{
				double buf_x;
				double buf_y;
				//スキルエフェクト
				for (auto& it : Effect::アニメ[パーティID])
				{
					if (it.is味方)
					{
						buf_x = px + Lp(0) - Lp(1) * it.配置ID;
						buf_y = py + Lp(2+it.配置ID);
					} else if (所属->isボス戦中) {
						buf_x = px - Lp(0) + Lp(8) + Lp(1) * it.配置ID + Lp(16);
						buf_y = py + Lp(2 + it.配置ID) + Lp(17);
					} else {
						buf_x = px - Lp(0) + Lp(8) + Lp(1) * it.配置ID;
						buf_y = py + Lp(2 + it.配置ID);
					}

					it.Draw((int)buf_x, (int)buf_y, 0.4);
				}

				//文字エフェクト
				for (auto& it : Effect::文字[パーティID])
				{
					if (it.is味方)
					{
						buf_x = px + Lp(0) - Lp(1) * it.配置ID;
						buf_y = py + Lp(2 + it.配置ID) + it.座標Y;
					}
					else if (所属->isボス戦中) {
						buf_x = px - Lp(0) + Lp(8) + Lp(1) * it.配置ID + Lp(16);
						buf_y = py + Lp(2 + it.配置ID) + Lp(17) + it.座標Y;
					}
					else {
						buf_x = px - Lp(0) + Lp(8) + Lp(1) * it.配置ID;
						buf_y = py + Lp(2 + it.配置ID) + it.座標Y;
					}

					switch (it.種類)
					{
						case TextEffect::TextType::ダメージ:
							MFont::MAlias.DrawBoldRotate({ buf_x,buf_y }, 1, 0, it.ダメージ色, Color::Black, it.ダメージ量);
							break;
						case TextEffect::TextType::回復:
							MFont::MAlias.DrawBoldRotate({ buf_x,buf_y }, 1, 0, it.回復色, Color::Black, it.ダメージ量);
							break;
						case TextEffect::TextType::回避:
							MFont::SAlias.DrawBoldRotate({ buf_x,buf_y }, 1, 0, Color::White, Color::Black, "miss");
							break;
					}

				}
				

				//素材獲得エフェクト
				for (auto& it : Effect::素材[パーティID])
				{
					if (it.隠れ時間 > 0) { continue; }

					//敵素材の場合
					if (it.配置ID < 0)
					{
						buf_x = Lp(14) + px;
						buf_y = Lp(15) + py + it.座標Y;
					} else if (所属->isボス戦中) {
						buf_x = px - Lp(0) + Lp(8) + Lp(1) * it.配置ID + Lp(16);
						buf_y = py + Lp(2 + it.配置ID) + Lp(17) + it.座標Y;
					} else {
						buf_x = px - Lp(0) + Lp(8) + Lp(1) * it.配置ID;
						buf_y = py + Lp(2 + it.配置ID) + it.座標Y;
					}

					it.image->DrawRotate({ buf_x , buf_y }, 1, 0);
				}

			}

			int itemX(int cnt)
			{
				return Lp(29) + (cnt % Lp(32)) * Lp(31);
			}

			int itemY(int cnt)
			{
				return Lp(30) + (cnt / Lp(32)) * Lp(31);
			}

			void Drawリザルト(double px, double py)
			{
				//Lp(18)から
				//リザルト枠
				Screen::SetBlendMode(BlendMode::Alpha, 128);
				MSystem::DrawWindow({ px + Lp(19) ,py + Lp(19) }, (int)位置.GetW() - Lp(19)*2 - Lp(33), (int)位置.GetH() - Lp(19)*2, 1);
				Screen::SetBlendMode();

				//味方5人
				for (int a = 0; a < CV::パーティ人数;a++)
				{
					auto it = 所属->メンバー[a];
					if ( it == nullptr) { continue; }
					//キャラ
					it->image[0][1]->DrawRotate({ px + Lp(20) + Lp(21) * a , py + Lp(22) }, 2, 0);
					//経験値バー-獲得分の表示
					int バー幅 = Lp(23);
					double 経験値割合 = it->経験値 / it->Get要求経験値();
					double 探検前割合 = (double)it->探検前経験値 / it->Get要求経験値();

					if (it->isレベルアップ演出)
					{
						経験値割合 = 1.0;
					}

					MSystem::DrawBarTwo({ px + Lp(24) - バー幅 / 2 + Lp(21) * a ,py + Lp(25) }, バー幅, Lp(26), 探検前割合, 経験値割合, 1, Color::Blue, Color(64, 255, 64), Color::White, Color::White, true);

					//LvUPとスキル習得の文字
					if (it->isスキル習得演出)
					{
						MFont::SAlias.DrawBold({ px + Lp(27) + Lp(21) * a  , py + Lp(28) }, Color::White, Color::Black, "New Skill");
					} else if (it->isレベルアップ演出) {
						MFont::SAlias.DrawBold({ px + Lp(27) + Lp(21) * a  , py + Lp(28) }, Color::White, Color::Black, "  Lv UP");
					}
				}
				int cnt = 0;

				//ボス
				
					MIcon::UI[IconType::ボス].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 2, 0);
					cnt++;
				
				//地図
				
					MIcon::UI[IconType::地図].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 2, 0);
					cnt++;
				
				//宝箱

					MIcon::UI[IconType::宝箱].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 2, 0);
					cnt++;
				
				//素材

				for (int a = 0; a < CV::素材系統; a++)
				{
					if (所属->獲得素材[a] <= 0) { continue; }

					auto& it = Material::data[a];

					it.image->DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 1, 0);
					//Lv表示
					MFont::SAlias.DrawBold({ px + itemX(cnt) + Lp(34) ,py + itemY(cnt) + Lp(35) }, Color::White, Color::Black, { "Lv " , it.ランク });

					//素材数表示
					MFont::SAlias.DrawBold({ px + itemX(cnt) + Lp(36) ,py + itemY(cnt) + Lp(37) }, Color::White, Color::Black, { "x", 所属->獲得素材[a] });
					cnt++;					
				}
			}

			void Click(double px, double py)
			{
				if (所属->探索状態 == ExplorerType::リザルト中)
				{
					所属->探索状態 = ExplorerType::編成中;
				}
			}

			void Drop(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中 && 所属->探索状態 != ExplorerType::リザルト中)
				{
					MSound::効果音[SE::配置換え].Play();
					return;
				}
				if (W_Drag::ダンジョン == nullptr) { return; }

				所属->探索先 = W_Drag::ダンジョン;
				MSound::効果音[SE::配置換え].Play();
			}

			void Info派生(Point 座標) override
			{
				//探索先情報
				if (所属->探索状態 != ExplorerType::編成中)
				{
					InfoResult(所属,座標);
					return;
				}

				SetHelp("ダンジョンドラッグ＆ドロップで探索先変更\nギルメンドラッグ＆ドロップで編成変更\n方針ボタンで探索方針変更");
				Info座標補正(座標);
				MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 4);
				MFont::MDot.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
			}
		};


		//探索者子オブジェクト
		class UI装飾品 : public UIObject
		{
		public:
			int 装備スロット = 2;
			int パーティID;
			int 隊列ID;

			void Draw派生() override
			{
				DrawUI(UIType::明ボタン);
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID]->装備[装備スロット];

				it->image->DrawRotate({ GetCenterX() , GetCenterY() }, 1, 0);
			}

			void Click() override
			{}

			void Over() override
			{}
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
				DrawUI(isOver ? UIType::平ボタン : UIType::凸ボタン);
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID]->装備[装備スロット];

				it->image->DrawRotate({ GetCenterX() , GetCenterY() }, 1, 0);
			}

			void Click() override
			{
			
			}

			void Over() override
			{
			
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
				DrawUI( isOver ? UIType::平ボタン : UIType::凸ボタン);
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID];

				auto& LA = LData(LParty::探索者スキルボタン);
				//スキル
				//ポイント余りやらの状況
				GetFont()->Draw({ GetX() + LA.x ,GetY() + LA.y }, Design::暗字, {"スキル\n10 P"});
			}

			void Click() override
			{
				スキルツリー.SetMember(Guild::P->パーティ[パーティID].メンバー[隊列ID]);
				スキルツリー.Init();
				スキルツリー.OpenPopup();
			}

			void Over() override
			{
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
			int 隊列ID;

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
				this->隊列ID = 隊列ID;

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
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID];

				auto& LA = Layout::Data(LParty::探索者ドット);
				auto& LB = Layout::Data(LParty::探索者Lv);
				auto& LC = Layout::Data(LParty::探索者経験値);

				//全体枠
				DrawUI(UIType::平ボタン);

				//配置している場合の表示
				if (it == nullptr) { return; }

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
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID];
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

				//探索先変更、探索指示変更



			}

			bool Drop() override
			{
				//探索者入れ替え

				//探索先変更

				return false;
			}

			void DrawHelp() override
			{
				auto& it = Guild::P->パーティ[パーティID].メンバー[隊列ID];
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
				DrawUI(UIType::明ボタン);
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

				}
				else
				{

				}
			}

			void Over() override
			{}

			void DrawHelp() override
			{
				UIHelp::Dungeon(Guild::P->パーティ[パーティID].探索先);
			}
		};

		class UI探索指示 : public UIObject
		{
		public:
			int パーティID;
			void Draw派生() override
			{
				DrawUI(UIType::明ボタン);
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

				//ボスフラグ
				//存在しない、未発見、発見、討伐済みの４種
				GetFont()->DrawRotate( GetPos(LA) , 1, 0, Design::暗字, { it->isボス生存 , " ボス生存" });

				//宝箱回収率
				GetFont()->DrawRotate( GetPos(LC), 1, 0, Design::暗字, { "財宝 "  , it->発見財宝数 , " / " , it->最大財宝数 });
			}

			void Click() override
			{
				//探索者掴む

				//探索先変更、探索指示変更

			}

			bool Drop() override
			{
				//探索者入れ替え

				//探索先変更


				return false;
			}

			void DrawHelp() override
			{
				UIHelp::Dungeon(Guild::P->パーティ[パーティID].探索先);
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
				if (探索フロア.CheckInput(px, py) == true) { return true; }
				if (探索指示.CheckInput(px, py) == true) { return true; }
				if (探索先.CheckInput(px, py) == true) { return true; }

				for (int i = 0; i < CV::パーティ人数; i++)
				{
					if (探索者[i].CheckInput(px, py) == true) { return true; }
				}

				return false;
			}

			void Draw派生() override
			{

				if (パーティ->探索状態 == ExplorerType::編成中)
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
				if (パーティ->探索状態 == ExplorerType::編成中)
				{
					//街
					//探索者掴む

					//探索先変更、探索指示変更

					//探索者の装備掴む、スキルウィンドウ開く、装備強化

				}
				else if(パーティ->探索状態 == ExplorerType::撤退中)
				{
					//探索完了後にクリックで街モードに即帰還

				}
			}

			bool Drop() override
			{
				if (パーティ->探索状態 != ExplorerType::編成中) { return false; }
				//探索者入れ替え

				//探索先変更

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
				//色々表示
				DrawUI(UIType::平ボタン);

			}

		};

		class UI控え探検者 : public UIObject
		{
		public:
			Explorer* 探索者 = nullptr;
			void Draw派生() override
			{
				auto& la = Layout::Data(LParty::控えドット);
				auto& lb = Layout::Data(LParty::控えLv);

				//ボタン枠-掴み中だと凹み
				DrawUI(UIType::明ボタン);

				//キャラ画像
				探索者->image[0][1]->DrawRotate( { GetCenterX() + la.x , GetCenterY() + la.y }, 2 , 0);

				//Lv
				GetFont()->Draw({ GetCenterX() + lb.x , GetCenterY() + lb.y } , Design::暗字 , { "Lv " , 探索者->Lv });
			}

			void Click() override
			{
				//掴む
				W_Drag::探索メン = 探索者;
				MSound::効果音[SE::ドラッグ].Play();
			}

			bool Drop() override
			{
				//並び替える
				//探索者->ID;
				if (W_Drag::探索メン != nullptr)
				{
					//ギルメン入れ替え
				}
				else if(W_Drag::所持アーティファクト != nullptr)
				{
					//アクセサリー交換
				}
				else if (W_Drag::ギルメン装備.メンバー != nullptr)
				{
					//パーティメンバーとアクセサリー交換
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
				除名ウィンドウ.OpenPopup();			
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

			for (auto& it : 控え)
			{
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