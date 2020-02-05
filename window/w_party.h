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
		class GUI_パーティ : public GUI_Object
		{
		public:
			int パーティID;
			Party* 参照先;
			W_Party* 親ウィンドウ;

			GUI_パーティ(int パーティID)
			{
				this->パーティID = パーティID;
				参照先 = &Guild::P->探索パーティ[パーティID];
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 14);
				MSystem::DrawBox({ px + LV(20) , py + LV(21) }, LV(22), LV(23), Color::White);

				MSystem::DrawBox({ px + LV(54) , py + LV(55) }, 62, 14, Color::White);
				MFont::Bメイリオ小.DrawBold({ px + LV(56) ,py + LV(57) }, Color::White, Color::Black, { "Party " , パーティID+1} );

				auto dun = Guild::P->探索パーティ[パーティID].探索先;

				MIcon::ダンジョン[dun->種類].Draw({ px + LV(24),py + LV(25) });
				MFont::BArial小.DrawBold({ px + LV(26) ,py + LV(27) }, Color::White, Color::Black, { "Lv ", dun->Lv });
				MFont::BArial小.DrawBold({ px + LV(28) ,py + LV(29) }, Color::White, Color::Black, { (int)(dun->探索率[Guild::P->id]*100) , "%" }, true);

				std::string siji;
				switch (Guild::P->探索パーティ[パーティID].探索指示)
				{
					case Order::探索重視: siji = "探索\n重視"; break;
					case Order::ボス討伐: siji = "ボス\n討伐"; break;
					case Order::戦闘重視: siji = "戦闘\n重視"; break;
					case Order::収集重視: siji = "収集\n重視"; break;
				}

				MFont::Bメイリオ小.DrawBold({ px + LV(30) ,py + LV(31) }, Color::White, Color::Black, siji , true);

				if (参照先->is探索中 == false) { return; }
				//探索中の表示
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (参照先->メンバー[a] != nullptr)
					{
						Draw探検(px,py);
						return;
					}
				}
			}

			void Draw探検(double px, double py)
			{
				MSystem::DrawBox({ px + LV(60) , py + LV(61) }, LV(62), LV(63), Color::White);//全体の枠

				//探索中-歩くだけ
				if (参照先->is移動中)
				{
					Draw移動(px,py);
					return;
				}

				//各種表示
				switch (参照先->探索先->部屋[参照先->部屋ID].種類)
				{
				case RoomType::ボス:
				case RoomType::魔物:
					Draw戦闘(px,py);
					break;
				case RoomType::素材:
					Draw収集(px, py);
					break;
				case RoomType::財宝:
					Draw財宝(px, py);
					break;
				}
			}

			void Draw移動(double px, double py)
			{

			}

			void Draw戦闘(double px, double py)
			{
				int n = (int)参照先->魔物.size();
				int xd, xdd;

				if (n <= 5)
				{
					xdd = LV(72);
				}
				else {
					xdd = LV(72) * 5 / n;
				}

				xd = -xdd / 2 * (n - 1);
					
				for (int a = 0; a < n; a++)
				{
					MonsterClass& mc = MonsterClass::data[参照先->魔物[a].種族];
					Monster& ms = 参照先->魔物[a];

					if (ms.現在HP <= 0) { continue; }

					//ライフバー
					double rate = ms.現在HP / ms.最大HP;
					MSystem::DrawBar({ px + LV(71) + xdd * a + xd + LV(74) ,py + LV(73) + LV(75) }, LV(68) * 2 / 3, LV(69), rate, LV(70), Color::Blue, Color::Black, Color::White, true);
					//ユニット
					//Screen::SetBright( ms.E色 );
					MUnit::ユニット[mc.見た目][1]->DrawRotate({ px + LV(71) + xdd * a + xd ,py + LV(73) + (int)ms.E前進 }, 2, 0);
					//Screen::SetBright();

				}
			}

			void Draw収集(double px, double py)
			{
				MaterialType mat = 参照先->探索先->部屋[参照先->部屋ID].素材種;

				MIcon::素材[mat].DrawRotate({ px + LV(71) ,py + LV(73) }, 1, 0);
			}

			void Draw財宝(double px, double py)
			{

				MIcon::アイコン[IconType::宝箱].DrawRotate({ px + LV(71) ,py + LV(73) }, 1, 0);
			}

			void Click(double px, double py)
			{
				if (参照先->is探索中 == true) { return; }

				//探索指示変更
				if (Point(px, py).Hit(&Rect(LV(20), LV(21), LV(22), LV(23))) == true)
				{
					int n = int(Guild::P->探索パーティ[パーティID].探索指示) + 1;
					if (n == (int)Order::COUNT) { n = 0; }
					Guild::P->探索パーティ[パーティID].探索指示 = Order(n);
				}
			}

			void Drop(double px, double py)
			{
				if (参照先->is探索中 == true) { return; }

				//探索先変更
				if (Point(px,py).Hit(&Rect(LV(20), LV(21), LV(22), LV(23))) == true && W_Drag_Drop::ダンジョン != nullptr)
				{
					Guild::P->探索パーティ[パーティID].探索先 = W_Drag_Drop::ダンジョン;
				}
			}

			void Info派生(Point 座標) override
			{
				//探索先情報
				if (座標.Hit(&Rect( 親ウィンドウ->座標.x + 位置.x + LV(20) , 位置.y + 親ウィンドウ->座標.y + LV(21) , LV(22), LV(23))) == true )
				{
					InfoDungeon(Guild::P->探索パーティ[パーティID].探索先, 座標);
				} else {
					//探索指示や入れ替え等の操作方法
					SetHelp("ダンジョンクリックで探索方針変更\nダンジョンドラッグ＆ドロップで探索先変更\nギルメンクリックで隊列変更\nギルメンドラッグ＆ドロップで編成変更", 110);
					Info座標補正(座標);
					MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 4);
					MFont::メイリオ中.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
				}
			}

		};

		class GUI_パーティメンバー : public GUI_Object
		{
		public:
			Warker* ギルメン;
			Party* 所属;
			W_Party* 親ウィンドウ;
			int 並びID;

			GUI_パーティメンバー(Warker* ギルメン)
			{
				this->ギルメン = ギルメン;
			}

			void Draw派生(double px, double py)
			{
				if (所属->is探索中 == true)
				{
					Draw探索中(px, py);
				} else {
					Draw休憩中(px, py);
				}
			}

			void Draw休憩中(double px, double py)
			{
				if (ギルメン == nullptr)
				{
					MSystem::DrawBox({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::Gray);
					return;
				}

				MSystem::DrawBox({ px,py }, (int)位置.GetW(), (int)位置.GetH(), Color::White);


				if (ギルメン->隊列 == FormationType::前列)
				{
					MUnit::ユニット[ギルメン->見た目][1]->DrawRotate({ px + LV(32) ,py + LV(33) }, 2, 0);
					MFont::Arial小.DrawBold({ px + LV(34) ,py + LV(35) }, Color::White, Color::Black, "Front");
				}
				else {
					MUnit::ユニット[ギルメン->見た目][1]->DrawRotate({ px + LV(32) ,py + 28 }, 2, 0);
					MFont::Arial小.DrawBold({ px + LV(34) ,py + 0 }, Color::White, Color::Black, "Back");
				}

				MIcon::アイテム[Item::data[ギルメン->装備[0]].見た目].Draw({ px + LV(36) , py + LV(38) });
				MIcon::アイテム[Item::data[ギルメン->装備[1]].見た目].Draw({ px + LV(37) , py + LV(38) });

				Screen::SetBright(Color::Blue);
				MIcon::スキル[ActiveSkill::data[ギルメン->アクティブスキル[0]].系統].Draw({ px + LV(39) , py + LV(41) + 25 });
				if (ギルメン->アクティブスキル[1] != 0) { MIcon::スキル[ActiveSkill::data[ギルメン->アクティブスキル[1]].系統].Draw({ px + LV(40) , py + LV(41) + 25 }); }
				Screen::SetBright(Color::White);
			}

			void Draw探索中(double px, double py)
			{
				if (ギルメン == nullptr)
				{
					return;
				}

				int anime = Game::アニメーション時間 / 12 % 4;
				if (anime == 3 || 所属->is移動中 == false) { anime = 1; }

				//アイコン
				Screen::SetBright(ギルメン->E色);
				if (ギルメン->隊列 == FormationType::前列)
				{
					MUnit::ユニット[ギルメン->見た目][3 + anime]->DrawRotate({ px + LV(32) ,py + LV(64) - (int)ギルメン->E前進 }, 2, 0);
				}
				else {
					MUnit::ユニット[ギルメン->見た目][3 + anime]->DrawRotate({ px + LV(32) ,py + LV(64) + LV(65) - (int)ギルメン->E前進 }, 2, 0);
				}
				Screen::SetBright();
				//HPゲージ
				double rate = ギルメン->現在HP / ギルメン->最大HP;

				MSystem::DrawBar({ px + LV(66),py + LV(67)  }, LV(68), LV(69), rate, LV(70), Color::Blue, Color::Black, Color::White, true);

			}

			void Click(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }
				if (ギルメン == nullptr) { return; }

				//ギルメン掴む
				W_Drag_Drop::ギルメン = ギルメン;
				W_Drag_Drop::ウィンドウ = 親ウィンドウ;
				W_Drag_Drop::並びID = 並びID;
			}

			void Drop(double px, double py)
			{
				if (Game::is仕事中 == true || 所属->is探索中) { return; }

				if (W_Drag_Drop::ギルメン == ギルメン && ギルメン != nullptr )
				{
					//前後列入れ替え
					if (ギルメン->隊列 == FormationType::前列) { ギルメン->隊列 = FormationType::後列; }
					else { ギルメン->隊列 = FormationType::前列; }

				}
				else if (W_Drag_Drop::ギルメン != nullptr)
				{
					//ギルメン入れ替え
					W_Drag_Drop::メンバー移動( 親ウィンドウ , ギルメン , 並びID);
				}
				else if(W_Drag_Drop::アイテム != -1 && ギルメン != nullptr)
				{
					//装備変更
					int 部位 = 0;
					if (Item::data[W_Drag_Drop::アイテム].種類 == ItemType::隠鎧 ||
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
					ギルメン->装備アップデート();

					所属->スキルステ計算();
				}
			}

			void Info派生(Point 座標) override
			{
				if (ギルメン == nullptr) { return; }

				//ギルメン情報
				if (座標.y < 位置.y + 親ウィンドウ->座標.y + LV(59) || Game::is仕事中)
				{
					//ギルメン情報
					InfoHunter(ギルメン, 座標);
				} else if(座標.x < 親ウィンドウ->座標.x + 位置.x + 位置.GetW()/2){
					//武器
					InfoItem(ギルメン->装備[0], 座標);
				} else {
					//防具
					InfoItem(ギルメン->装備[1], 座標);
				}
			}

		};

	public:
		//パーティ
		std::vector<GUI_パーティ> パーティ;
		
		std::vector<GUI_パーティメンバー> パーティメンバー;

		void init()
		{
			//名前 = "ギルド員/\\cff00ff仕事\\cffffff割当";
			種類 = WindowType::Party;
			名前 = "ギルド員/割当";
			略記 = "団員";
			アイコン = IconType::団員;
			横幅 = 344;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
		}

		void GUI_Init()
		{
			//オブジェクト初期化
			パーティ.clear();
			パーティメンバー.clear();
			gui_objects.clear();

			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				パーティ.emplace_back(a);
				パーティ[a].親ウィンドウ = this;
				for (int b = 0; b < CV::パーティ人数; b++)
				{
					パーティメンバー.emplace_back(Guild::P->探索パーティ[a].メンバー[b]);
					パーティメンバー[a*CV::パーティ人数 + b].所属 = &Guild::P->探索パーティ[a];
					パーティメンバー[a*CV::パーティ人数 + b].親ウィンドウ = this;
					パーティメンバー[a*CV::パーティ人数 + b].並びID = a * CV::パーティ人数 + b;
				}
			}

			for (int a = 0; a < パーティメンバー.size(); a++)
			{
				gui_objects.push_back(&パーティメンバー[a]);
			}

			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				gui_objects.push_back(&パーティ[a]);
			}

			//座標初期化
			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				パーティ[a].位置 = { LV(0) , LV(1) + LV(4) * a , LV(2) , LV(3) };

				for (int b = 0; b < CV::パーティ人数; b++)
				{
					パーティメンバー[a * 5 + b].位置 = { LV(5) + LV(9) * b , LV(6) + LV(4) * a , LV(7) , LV(8) };
				}
			}

			int n = 0;

			縦内部幅 = Guild::P->最大パーティ数 * LV(4) + 20;
		}

		void 派生Draw()
		{
			GUI_Init();

			for (auto& it : パーティ)
			{
				it.Draw();
			}

			for (auto& it : パーティメンバー)
			{
				it.Draw();
			}
		}

		bool 派生操作()
		{
			for (auto& it : パーティ)
			{
				it.操作チェック(相対座標.x, 相対座標.y);
			}

			for (auto& it : パーティメンバー)
			{
				it.操作チェック(相対座標.x, 相対座標.y);
			}

			return false;
		}
	};
#undef LV
#undef LV2
#undef LV4
}