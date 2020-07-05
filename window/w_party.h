//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[8][a]

	/*パーティウィンドウ*/
	class W_Party: public WindowBox
	{
	private:

		class GUI_探索先 : public GUI_Object
		{
		public:
			int パーティID;
			Guild::Party* 所属;
			W_Party* 親ウィンドウ;

			GUI_探索先(int パーティID, W_Party* 親ウィンドウ)
			{
				this->パーティID = パーティID;
				所属 = &Guild::P->探索パーティ[パーティID];
				this->親ウィンドウ = 親ウィンドウ;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 11);

				auto dun = Guild::P->探索パーティ[パーティID].探索先;

				//探索先アイコン、レベル
				MIcon::ダンジョン[dun->種類].Draw({ px + LV(12),py + LV(13) });
				MFont::BSSize.DrawBold({ px + LV(14) ,py + LV(15) }, Color::White, Color::Black, { "Lv ", dun->Lv });
				//探索度ゲージと探索率
				MSystem::DrawBar({ px + LV(18) , py + LV(19) }, LV(20), LV(21), dun->探索率, 1 , Color::Blue, Color::White, Color::White, true);				
				MFont::BSSize.DrawBold({ px + LV(16) ,py + LV(17) }, Color::White, Color::Black, { (int)(dun->探索率 * 100) , "%" }, true);				
				//ボス状態
				MIcon::アイコン[IconType::ボス].DrawRotate({ px + LV(22),py + LV(23) }, 1, 0);

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

				MFont::BSSize.DrawBold({ px + LV(22) + 50 ,py + LV(23) - 9 }, Color::White, Color::Black, sボス状態, true);
				//地図状態
				MIcon::アイコン[IconType::地図].DrawRotate({ px + LV(22),py + LV(24) }, 1, 0);
				MFont::BSSize.DrawBold({ px + LV(22) + 50 ,py + LV(24) - 9 }, Color::White, Color::Black, { dun->発見地図 , " / " , dun->最大地図}, true);
				//財宝状態
				MIcon::アイコン[IconType::宝箱].DrawRotate({ px + LV(22),py + LV(25) }, 1, 0);
				MFont::BSSize.DrawBold({ px + LV(22) + 50 ,py + LV(25) - 9 }, Color::White, Color::Black, { dun->発見財宝 , " / " , dun->最大財宝 }, true);


				//探索指示-冒険中は三角を非表示
				if (所属->探索状態 == ExplorerType::編成中 || 所属->探索状態 == ExplorerType::リザルト中)
				{
					MSystem::DrawWindow({ px + LV(31) ,py + LV(32) }, LV(33), LV(34), 0, 1);
					MIcon::アイコン[IconType::三角].Draw({ px + LV(26),py + LV(28) });
					MIcon::アイコン[IconType::三角].Draw({ px + LV(27),py + LV(28) }, true);
				} else {
					MSystem::DrawWindow({ px + LV(31) ,py + LV(32) }, LV(33), LV(34), 1, 0);
				}

				std::string siji;
				switch (Guild::P->探索パーティ[パーティID].探索指示)
				{
				case OrderType::探索: siji = TX::Party_ボス回避; break;
				case OrderType::ボス: siji = TX::Party_ボス討伐; break;
				}

				MFont::BSSize.DrawBold({ px + LV(29) ,py + LV(30) }, Color::White, Color::Black, siji, true);
			}

			void Click(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中 && 所属->探索状態 != ExplorerType::リザルト中) { return; }

				if (Point(px, py).Hit(&Rect(LV(31), LV(32), LV(33), LV(34))) == true)
				{
					int n = int(Guild::P->探索パーティ[パーティID].探索指示);

					if (px < LV(31) + LV(33) / 2) { n--; }
					else { n++; }


					if (n == (int)OrderType::COUNT) { n = 0; }
					if (n <  0) { n = (int)OrderType::COUNT - 1; }

					Guild::P->探索パーティ[パーティID].探索指示 = OrderType(n);
					MSound::効果音[SE::ボタンクリック].Play();
				}
			}

			void Drop(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中 && 所属->探索状態 != ExplorerType::リザルト中) { return; }
				if (W_Drag_Drop::ダンジョン == nullptr) { return; }

				//探索先変更
				所属->探索先 = W_Drag_Drop::ダンジョン;
				MSound::効果音[SE::配置換え].Play();
			}

			void Info派生(Point 座標) override
			{
				Point 補正座標;
				補正座標.x = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;
				補正座標.y = 座標.y - 親ウィンドウ->相対座標.y - 位置.y;


				if (補正座標.Hit(&Rect(LV(31), LV(32), LV(33), LV(34))) == true)
				{
					//探索指示や入れ替え等の操作方法
					SetHelp( TX::Party_探索方針);
					Info座標補正(座標);
					MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 4);
					MFont::MSize.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
				}
				else 
				{
					//探索方針
					InfoDungeon(Guild::P->探索パーティ[パーティID].探索先, 座標);
				}
			}

		};

		class GUI_パーティメンバー : public GUI_Object
		{
		public:
			Warker* ギルメン;
			Guild::Party* 所属;
			W_Party* 親ウィンドウ;
			int 並びID;

			GUI_パーティメンバー(Warker* ギルメン)
			{
				this->ギルメン = ギルメン;
			}

			void Draw派生(double px, double py)
			{
				//未配置時の表示
				if (ギルメン == nullptr)
				{
					//MSystem::DrawBox({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::Gray);
					MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 4);
					return;
				}

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);

				//アイコン、Lv、Expゲージ
				MUnit::ユニット[ギルメン->見た目][10]->DrawRotate({ px + LV(35) ,py + LV(36) }, 2, 0);
				MFont::BSSize.DrawBold({ px + LV(37) ,py + LV(38) }, Color::White, Color::Black, { "Lv " ,ギルメン->Lv} , true);

				MSystem::DrawBar({ px + LV(39),py + LV(40) }, LV(41), LV(42), ギルメン->経験値 / ギルメン->Get要求経験値(), 1, Color::Blue, Color::White, Color::White, true);

				//装備品 x 3と更新ボタン、自動更新設定、装備ランク
				MSystem::DrawWindow({ px + LV(43) ,py + LV(46) }, LV(48), LV(49), 0);
				MSystem::DrawWindow({ px + LV(44) ,py + LV(46) }, LV(48), LV(49), 0);
				MSystem::DrawWindow({ px + LV(45) ,py + LV(47) }, LV(48), LV(49), 0);
				MIcon::アイテム[Item::data[ギルメン->装備[0]].見た目].Draw({ px + LV(43) + LV(50) , py + LV(46) + LV(51) });
				MIcon::アイテム[Item::data[ギルメン->装備[1]].見た目].Draw({ px + LV(44) + LV(50)  , py + LV(46) + LV(51) });
				MIcon::アイテム[Item::data[ギルメン->装備[2]].見た目].Draw({ px + LV(45) + LV(50) , py + LV(47) + LV(51) });

				MFont::BSSize.DrawBold({ px + LV(52) , py + LV(54) }, Color::White, Color::Black, { "Lv " , Item::data[ギルメン->装備[0]].ランク });
				MFont::BSSize.DrawBold({ px + LV(53) , py + LV(54) }, Color::White, Color::Black, { "Lv " ,Item::data[ギルメン->装備[1]].ランク });
				//MFont::BSSize.DrawBold({ px + LV(53) , py + LV(50) + 11 }, Color::White, Color::Black, { "アクセ" });

				//装備更新ボタン
				if (ギルメン->is装備更新)
				{
					MSystem::DrawWindow({ px + LV(55) ,py + LV(56) }, LV(57), LV(58), 2, -1);
				} else {
					MSystem::DrawWindow({ px + LV(55) ,py + LV(56) }, LV(57), LV(58), 0, 1);
				}

				MFont::BSSize.DrawBold({ px + LV(59) ,py + LV(60) }, Color::White, Color::Black, "装備更新");
				MIcon::アイコン[IconType::更新].Draw({ px + LV(61),py + LV(62) });

			}

			void Click(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中) { return; }
				if (ギルメン == nullptr) { return; }

				//自動更新切り替え
				if (Point(px, py).Hit(&Rect(LV(55), LV(56), LV(57), LV(58))) == true)
				{
					ギルメン->is装備更新 = !ギルメン->is装備更新;
					MSound::効果音[SE::ボタンクリック].Play();
					return;
				}

				//ギルメン掴む
				W_Drag_Drop::ギルメン = ギルメン;
				W_Drag_Drop::ウィンドウ = 親ウィンドウ;
				W_Drag_Drop::並びID = 並びID;
				MSound::効果音[SE::ドラッグ].Play();
			}

			void Drop(double px, double py)
			{
				if (所属->探索状態 != ExplorerType::編成中) { return; }

				if (W_Drag_Drop::ギルメン != nullptr)
				{
					//ギルメン入れ替え
					W_Drag_Drop::メンバー移動( 親ウィンドウ , ギルメン , 並びID);
				}
				else if(W_Drag_Drop::アイテム != -1 && ギルメン != nullptr)
				{
					//装備変更
					int 部位 = 0;
					if (Item::data[W_Drag_Drop::アイテム].種類 == ItemType::アクセサリー)
					{
						部位 = 2;
					}else if (Item::data[W_Drag_Drop::アイテム].種類 == ItemType::隠鎧 ||
						Item::data[W_Drag_Drop::アイテム].種類 == ItemType::軽鎧 ||
						Item::data[W_Drag_Drop::アイテム].種類 == ItemType::重鎧 ||
						Item::data[W_Drag_Drop::アイテム].種類 == ItemType::力鎧 ||
						Item::data[W_Drag_Drop::アイテム].種類 == ItemType::技鎧 ||
						Item::data[W_Drag_Drop::アイテム].種類 == ItemType::知鎧 )
					{
						部位 = 1;
					}					

					Guild::P->装備所持数[ギルメン->装備[部位]]++;
					Guild::P->装備所持数[W_Drag_Drop::アイテム]--;
					ギルメン->装備[部位] = W_Drag_Drop::アイテム;
					ギルメン->装備スキル更新();

					所属->基礎ステ再計算();
					MSound::効果音[SE::装備変更].Play();
				}
				else if (W_Drag_Drop::ダンジョン != nullptr) 
				{ 
					所属->探索先 = W_Drag_Drop::ダンジョン;
					MSound::効果音[SE::配置換え].Play();				
				}

			}

			void Info派生(Point 座標) override
			{
				if (所属->探索状態 != ExplorerType::編成中) { return; }
				if (ギルメン == nullptr) { return; }

				Point 補正座標;
				補正座標.x = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;
				補正座標.y = 座標.y - 親ウィンドウ->相対座標.y - 位置.y;

				if (補正座標.Hit(&Rect(LV(43), LV(46), LV(48), LV(49))) )
				{
					//武器
					InfoItem(ギルメン->装備[0], 座標);
				}
				else if (補正座標.Hit(&Rect(LV(44), LV(46), LV(48), LV(49))))
				{
					//防具
					InfoItem(ギルメン->装備[1], 座標);
				}
				else if (補正座標.Hit(&Rect(LV(45), LV(47), LV(48), LV(49))))
				{
					//アクセ
					SetHelp("アクセサリー(未実装)");
					InfoMessage(座標);
					//InfoItem(ギルメン->装備[2], 座標);
				}
				else if (補正座標.Hit(&Rect(LV(55), LV(56), LV(57), LV(58))))
				{
					//Auto
					SetHelp("装備自動更新のON/OFF");
					InfoMessage(座標);
				}
				else
				{
					//ギルメン情報
					InfoHunter(ギルメン, 座標);

				}
			}

		};

		class GUI_パーティ : public GUI_Object
		{
		public:
			int パーティID;
			Guild::Party* 所属;
			W_Party* 親ウィンドウ;

			GUI_パーティ(int パーティID, W_Party* 親ウィンドウ)
			{
				this->パーティID = パーティID;
				所属 = &Guild::P->探索パーティ[パーティID];
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

				Screen::SetBright(Color(所属->暗転, 所属->暗転, 所属->暗転));

				//探索中のダンジョン背景
				Draw背景(px, py);

				//パーティメンバー
				for(int a = 0; a < CV::パーティ人数; a++)
				{
					if (所属->メンバー[a] == nullptr) { continue; }

					Drawギルメン(所属->メンバー[a], px + LV(70) - LV(71) * a, py + LV(72 + a));
				}

				if (所属->発見物 != nullptr)
				{
					所属->発見物->DrawRotate({ LV(84) + px + 所属->発見物X座標 ,LV(85) + py }, 2, 0);
				}

				//探索状態により描画処理
				switch( 所属->探索状態 )
				{
					case ExplorerType::移動中://パーティメンバーのみ、歩くモーション
						break;
					case ExplorerType::収集中://地図、宝箱、素材に対して収集アニメーション
						break;
					case ExplorerType::全滅中:
					case ExplorerType::戦闘中:
					case ExplorerType::撤退中:
						//敵
						for (int a = 0; a < (int)所属->魔物.size(); a++)
						{
							Draw敵(所属->魔物[a], px - LV(70) + LV(78) + LV(71) * a, py + LV(72 + a));
						}
						break;
				}

				Screen::SetBright(Color::White);
			}

			void Draw背景(double px, double py)
			{
				//背景スクロール描画
				const int 手前W = 2, 奥W = 2;

				int w幅 = MSystem::ダンジョン背景[1].GetWidth() - 所属->移動量 + 手前W + 奥W;


				if (w幅 <= 0 ) 所属->移動量 = 0;

				if (w幅 < 位置.GetW() - 手前W - 奥W)
				{
					MSystem::ダンジョン背景[1].DrawPart({ px + 手前W + w幅 , py + 2 }, { 0    , 0 , 位置.GetW() - w幅 - 手前W - 奥W ,位置.GetH() - 4 });
					MSystem::ダンジョン背景[1].DrawPart({ px + 手前W       , py + 2 }, { 所属->移動量, 0 , w幅 , 位置.GetH() - 4 });
				} else {
					//一枚目だけ
					MSystem::ダンジョン背景[1].DrawPart({ px + 手前W , py + 2 }, { 所属->移動量, 0 , 位置.GetW() - 手前W - 奥W ,位置.GetH() - 4 });
				}
				
				//各種表示
				switch (所属->探索先->部屋[所属->部屋ID].種類)
				{
				case RoomType::ボス:
					break;
				}
			}

			void Drawギルメン(Warker* it,double px, double py)
			{
				int 向き = 0;
				double サイズ = 2;

				switch (所属->探索状態)
				{
				case ExplorerType::移動中://パーティメンバーのみ、歩くモーション
					向き = 9 + (Game::時間 / 5 % 4);
					if (向き == 12) { 向き = 11; }
					break;
				case ExplorerType::リザルト中://枠表示、LvUP、探索成果、活躍表示
					向き = 9;
					break;
				case ExplorerType::戦闘中://木 or 岩に対して収集アニメーション
				case ExplorerType::収集中://木 or 岩に対して収集アニメーション
					向き = 9;
					break;
				case ExplorerType::全滅中://全滅表示
					向き = 4;
					break;
				case ExplorerType::撤退中://モンスターそのままで後ろ向きにギルメン逃走
					向き = 6 + (Game::時間 / 3 % 4);
					if (向き == 9) { 向き = 8; }
					break;
				}

				//→向き
				double 角度 = 0;
				if (it->現在HP <= 0)
				{
					角度 = PAI / 2;
					向き = 4;
				}


				MUnit::ユニット[it->見た目][向き]->DrawRotate({ px + (int)it->E座標,py }, サイズ, 角度);
				if (it->E光強さ > 0)
				{
					Screen::SetBlendMode(BlendMode::Add, int(it->E光強さ * 255));
					MUnit::ユニット[it->見た目][向き]->SetColor(it->E光色);
					MUnit::ユニット[it->見た目][向き]->DrawRotate({ px + (int)it->E座標,py }, サイズ, 角度);
					MUnit::ユニット[it->見た目][向き]->SetColor(Color::White);
					Screen::SetBlendMode();
				}

				if (所属->探索状態 == ExplorerType::撤退中) { return; }

				//ライフバー
				int バー幅 = int(LV(82) * サイズ);

				MSystem::DrawBar({ px + LV(80) - バー幅 / 2,py + LV(81) }, バー幅, LV(83), (double)it->現在HP / it->最大HP, 1, Color::Blue, Color::White, Color::White, true);

				if ( it->Eダメージ時間 > 0)
				{
					if (it->Eダメージ == 0)
					{
						//0ならmiss
						MFont::BSSize.DrawBold({ px-15 , py }, Color::White, Color::Black, "miss");
					} else if(it->Eダメージ > 0) {
						//+はダメージ
						MFont::BSSize.DrawBold({ px , py }, Color::White, Color::Black, it->Eダメージ);
					} else if(it->Eダメージ < 0){
						//-は回復
						MFont::BSSize.DrawBold({ px , py }, Color(128,255,128), Color::Black, -it->Eダメージ);
					}
				}

			}

			void Draw敵(Monster& it, double px, double py)
			{					
				//←向き
				if (it.現在HP <= 0) { return; }
				UnitImageType 見た目 = MonsterClass::data[it.種族].見た目;
				int 向き = 7;
				double サイズ = 2;

				if (it.isボス)
				{
					サイズ = 4;
					px += LV(86);
					py += LV(87);
				}


				MUnit::ユニット[見た目][向き]->DrawRotate({ px - (int)it.E座標,py }, サイズ, 0);
				if (it.E光強さ > 0)
				{
					Screen::SetBlendMode(BlendMode::Add, int(it.E光強さ * 255));
					MUnit::ユニット[見た目][向き]->SetColor(it.E光色);
					MUnit::ユニット[見た目][向き]->DrawRotate({ px - (int)it.E座標,py }, サイズ, 0);
					MUnit::ユニット[見た目][向き]->SetColor(Color::White);
					Screen::SetBlendMode();
				}

				int バー幅 = int(LV(82) * サイズ);
				int ボスY = (it.isボス) ? LV(88) : 0;
				//ライフバー
				MSystem::DrawBar({ px + LV(80) - バー幅/2 ,py + LV(81) + ボスY }, バー幅 , LV(83), (double)it.現在HP / it.最大HP, 1, Color::Blue, Color::White, Color::White, true);

				if (it.Eダメージ時間 > 0)
				{
					if (it.Eダメージ == 0)
					{
						//0ならmiss
						MFont::BSSize.DrawBold({ px - 15 , py }, Color::White, Color::Black, "miss");
					}
					else if (it.Eダメージ > 0)
					{
						//+はダメージ
						MFont::BSSize.DrawBold({ px , py }, Color::White, Color::Black, it.Eダメージ);
					}
					else if (it.Eダメージ < 0)
					{
						//-は回復
						MFont::BSSize.DrawBold({ px , py }, Color(128, 255, 128), Color::Black, -it.Eダメージ);
					}
				}

			}

			void Drawリザルト(double px, double py)
			{
				//LV(88)から
				//リザルト枠
				Screen::SetBlendMode(BlendMode::Alpha, 128);
				MSystem::DrawWindow({ px + LV(89) ,py + LV(89) }, (int)位置.GetW() - LV(89)*2 - LV(103), (int)位置.GetH() - LV(89)*2, 1);
				Screen::SetBlendMode();

				//味方5人
				for (int a = 0; a < CV::パーティ人数;a++)
				{
					auto it = 所属->メンバー[a];
					if ( it == nullptr) { continue; }
					//キャラ
					MUnit::ユニット[it->見た目][2]->DrawRotate({ px + LV(90) + LV(91) * a , py + LV(92) }, 2, 0);
					//経験値バー-獲得分の表示
					int バー幅 = LV(93);
					double 経験値割合 = it->経験値 / it->Get要求経験値();
					MSystem::DrawBar({ px + LV(94) - バー幅 / 2 + LV(91) * a ,py + LV(95) }, バー幅, LV(96), 経験値割合, 1, Color::Blue, Color::White, Color::White, true);

					//if ( !it->isレベルアップ演出)
					//{
					//	経験値割合 = (double)it->探検前経験値 / it->Get要求経験値();
					//	MSystem::DrawBar({ px + LV(94) - バー幅 / 2 + LV(91) * a + 1 ,py + LV(95)+1 }, バー幅-2, LV(96), 経験値割合, 0, Color::Blue, Color::White, Color(0,0,0,0), true);
					//}

					//LvUPとスキル習得の文字
					if (it->isスキル習得演出)
					{
						MFont::BSSize.DrawBold({ px + LV(97) + LV(91) * a  , py + LV(98) }, Color::White, Color::Black, "New Skill");
					} else if (it->isレベルアップ演出) {
						MFont::BSSize.DrawBold({ px + LV(97) + LV(91) * a  , py + LV(98) }, Color::White, Color::Black, "  Lv UP");
					}
				}
				int cnt = 0;
				auto itemX = [](int cnt) ->int {
					return LV(99) + (cnt % LV(102)) * LV(101);
				};
				auto itemY = [](int cnt) ->int {
					return LV(100) + (cnt / LV(102)) * LV(101);
				};

				//ボス
				for(int a = 0; a < 所属->撃破ボス数; a++)
				{
					MIcon::アイコン[IconType::ボス].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 2, 0);
					cnt++;
				}
				//地図
				for (int a = 0; a < 所属->獲得地図数; a++)
				{
					MIcon::アイコン[IconType::地図].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 2, 0);
					cnt++;
				}
				//宝箱
				for (int a = 0; a < 所属->獲得財宝数; a++)
				{
					MIcon::アイコン[IconType::宝箱].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 2, 0);
					cnt++;
				}
				//素材

				for (int a = 0; a < (int)所属->獲得素材.size(); a++)
				{
					int rank = 0;

					for (auto& it : 所属->獲得素材[(CraftType)a])
					{
						rank++;
						if (it <= 0) { continue; }

						MIcon::素材[(CraftType)a].DrawRotate({ px + itemX(cnt) ,py + itemY(cnt) }, 1, 0);
						//Lv表示
						MFont::BSSize.DrawBold({ px + itemX(cnt) + LV(104) ,py + itemY(cnt) + LV(105) }, Color::White, Color::Black, { "Lv " ,rank});

						//素材数表示
						MFont::BSSize.DrawBold({ px + itemX(cnt) + LV(106) ,py + itemY(cnt) + LV(107) }, Color::White, Color::Black, { "x", it});
						cnt++;
					}
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

				if (所属->探索状態 != ExplorerType::編成中 && 所属->探索状態 != ExplorerType::リザルト中) { return; }
				if (W_Drag_Drop::ダンジョン == nullptr) { return; }

				所属->探索先 = W_Drag_Drop::ダンジョン;
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
				MFont::MSize.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
			}

		};

	public:
		//パーティ
		std::vector<GUI_パーティ> パーティ;
		std::vector<GUI_探索先> 探索先;
		
		std::vector<GUI_パーティメンバー> パーティメンバー;

		void init()
		{
			//名前 = "ギルド員/\\cff00ff仕事\\cffffff割当";
			種類 = WindowType::Party;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::編成;
			横幅 = 550;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 800;
			縦内部幅 = 800;//120☓ランク数
			スクロール位置 = 0;

			GUI_Init();
		}

		void GUI_Init()
		{
			//オブジェクト初期化
			パーティ.clear();
			探索先.clear();
			パーティメンバー.clear();
			gui_objects.clear();

			int cnt = 0;

			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				パーティ.emplace_back(a,this);
				探索先.emplace_back(a,this);
				パーティ[a].位置 = { LV(0) , LV(1) + (LV(3) + LV(4)) * a , LV(2) , LV(3) };
				探索先[a].位置 = { LV(10) , LV(6) + (LV(3) + LV(4)) * a , LV(11) , LV(8) };

				if (Guild::P->探索パーティ[a].探索状態 != ExplorerType::編成中) { continue; }

				for (int b = 0; b < CV::パーティ人数; b++)
				{
					パーティメンバー.emplace_back(Guild::P->探索パーティ[a].メンバー[b]);
					パーティメンバー.back().所属 = &Guild::P->探索パーティ[a];
					パーティメンバー.back().親ウィンドウ = this;
					パーティメンバー.back().並びID = a * CV::パーティ人数 + b;
					パーティメンバー.back().位置 = { LV(5) - (LV(7) + LV(9)) * b , LV(6) + (LV(3) + LV(4)) * a , LV(7) , LV(8) };
				}
			}

			for (auto& it : パーティメンバー)
			{
				gui_objects.push_back(&it);
			}

			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				gui_objects.push_back(&探索先[a]);
				gui_objects.push_back(&パーティ[a]);				
			}


		}

		void 派生Draw()
		{
			GUI_Init();

			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				パーティ[a].Draw();
				探索先[a].Draw();
			}

			for (auto& it : パーティメンバー)
			{
				if (it.所属->探索状態 == ExplorerType::編成中) { it.Draw(); }
			}
		}

		bool 派生操作()
		{
			for (auto& it : gui_objects)
			{
				it->操作チェック(相対座標.x, 相対座標.y);
			}

			return false;
		}
	};
#undef LV
#undef LV2
#undef LV4
}