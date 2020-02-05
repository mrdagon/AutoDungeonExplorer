//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once


namespace SDX_BSC
{
	using namespace SDX;

	/*ウィンドウベースクラス*/

	class GUI_Help
	{
	public:
		const int 枠スキン = 4;

		int ヘルプ縦幅 = 50;
		int ヘルプ横幅 = 50;
		bool isヘルプ表示 = true;
		std::string ヘルプメッセージ = "test";

		/*ヘルプウィンドウ描画共通処理*/
		void Info()
		{
			if (Game::isヘルプ == false) { return; }

			Point p = { Input::mouse.x ,Input::mouse.y };

			Info派生( p );
		}
		
		void Info座標補正(Point &座標)
		{
			//横幅超過
			if (座標.x + ヘルプ横幅 > Window::GetWidth())
			{
				座標.x = 座標.x - ヘルプ横幅;
			}
			//縦幅超過
			if (座標.y + ヘルプ縦幅 > Window::GetHeight())
			{
				座標.y = 座標.y - ヘルプ縦幅;
			}
		}

		/*ヘルプ描画内容*/
		virtual void Info派生(Point 座標)
		{
			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);
			MFont::メイリオ中.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White,Color::Black, ヘルプメッセージ);
		}

		void SetHelp(std::string メッセージ, int 高さ = 40)
		{
			ヘルプメッセージ = メッセージ;
			ヘルプ横幅 = MFont::メイリオ中.GetDrawStringWidth(ヘルプメッセージ) + 20;
			ヘルプ縦幅 = 高さ;
		}


		void InfoHunter(Warker* it,Point 座標)
		{
#define LV(a) DV::I[11][a]

			ヘルプ横幅 = LV(0);
			ヘルプ縦幅 = LV(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			//アイコン、名前、所属、レベル、経験値、給料、忠誠度
			座標.y += LV(2);
			MSystem::DrawWindow({ 座標.x + LV(3),座標.y + LV(4) }, LV(5), LV(6), 枠スキン);

			MUnit::ユニット[it->見た目][1]->DrawRotate({ 座標.x + LV(7) ,座標.y + LV(8) }, 2, 0);

			MFont::BArial小.DrawBold({ 座標.x + LV(9) , 座標.y + LV(10) }, Color::White, Color::Black, { "Lv " , it->Lv });
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(11) , 座標.y + LV(12) }, Color::White, Color::Black, it->名前);

			int 要求exp = (2 + it->Lv * it->Lv) * CV::要求経験値;
			double exprate = it->経験値 / ( 要求exp );
			
			MSystem::DrawBar({ 座標.x + LV(13) , 座標.y + LV(14) }, LV(15), LV(16), exprate, 1 , Color::Blue, Color::White, Color::White, true);//経験値

			MIcon::アイコン[IconType::資金].Draw({ 座標.x + LV(17),座標.y + LV(18) });
			MIcon::アイコン[IconType::ヘルプ].Draw({ 座標.x + LV(17),座標.y + LV(18) + LV(19) });//忠誠度

			MFont::BArial小.DrawBold({ 座標.x + LV(20) , 座標.y + LV(21) }, Color::White, Color::Black, it->現在賃金,true);
			MFont::BArial小.DrawBold({ 座標.x + LV(20) , 座標.y + LV(21) + LV(22) }, Color::White, Color::Black, { it->忠誠度 , " %" }, true);

			//装備品、Aスキル
			//最大HP、基礎ステ、製造力
			座標.y += LV(23);
			MSystem::DrawWindow({ 座標.x + LV(3),座標.y + LV(4) }, LV(5), LV(24), 枠スキン);

			MIcon::アイテム[Item::data[it->装備[0]].見た目].Draw({ 座標.x + LV(25),座標.y + LV(26) });//装備
			MIcon::アイテム[Item::data[it->装備[1]].見た目].Draw({ 座標.x + LV(25),座標.y + LV(26) + LV(27) * 1 });
			MIcon::スキル[ActiveSkill::data[it->アクティブスキル[0]].系統].Draw({ 座標.x + LV(25),座標.y + LV(26) + LV(27) * 2 });//スキル
			MIcon::スキル[ActiveSkill::data[it->アクティブスキル[1]].系統].Draw({ 座標.x + LV(25),座標.y + LV(26) + LV(27) * 3 });

			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(28) , 座標.y + LV(29) }, Color::White, Color::Black, Item::data[it->装備[0]].名前);//装備名
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(28) , 座標.y + LV(29) + LV(27) * 1 }, Color::White, Color::Black, Item::data[it->装備[1]].名前);
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(28) , 座標.y + LV(29) + LV(27) * 2 }, Color::White, Color::Black, ActiveSkill::data[it->アクティブスキル[0]].名前 );//スキル名
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(28) , 座標.y + LV(29) + LV(27) * 3 }, Color::White, Color::Black, ActiveSkill::data[it->アクティブスキル[1]].名前);

			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 0 }, Color::White, Color::Black, "HP");//各種ステータス
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 1 }, Color::White, Color::Black, "STR");
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 2 }, Color::White, Color::Black, "DEX");
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 3 }, Color::White, Color::Black, "INT");
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 4 }, Color::White, Color::Black, "VIT");
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 5 }, Color::White, Color::Black, "AGI");
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(30) , 座標.y + LV(31) + LV(32) * 6 }, Color::White, Color::Black, "MKE");

			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 0 }, Color::White, Color::Black, (int)it->最大HP , true);//各数値
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 1 }, Color::White, Color::Black, (int)it->基礎Str, true);
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 2 }, Color::White, Color::Black, (int)it->基礎Dex, true);
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 3 }, Color::White, Color::Black, (int)it->基礎Int, true);
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 4 }, Color::White, Color::Black, (int)it->基礎Vit, true);
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 5 }, Color::White, Color::Black, (int)it->基礎Agi, true);
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(33) , 座標.y + LV(31) + LV(32) * 6 }, Color::White, Color::Black, (int)it->製造力, true);

			//Pスキル-アイコン、名前、説明
			座標.y += LV(34);
			座標.x += LV(35);
			MSystem::DrawWindow({ 座標.x + LV(45),座標.y + LV(46) }, LV(47), LV(48), 枠スキン);
			int sp = it->スキルポイント;
			for (int a = 0; a < 6; a++)
			{

				if (it->パッシブスキル[a] < 0 || it->パッシブスキル[a] > 30) continue;

				auto pskill = &PassiveSkill::data[it->パッシブスキル[a]];
				
				if (it->isパッシブスキル習得[a] == true)
				{
					MSystem::DrawSkill(pskill->系統, { 座標.x + LV(36), 座標.y + LV(37) }, Color(0, 141, 255));

					//Drawing::Rect({ 座標.x + LV(36)-2,座標.y + LV(37)-2 ,29,29 }, Color::Blue, true);
					//Drawing::Rect({ 座標.x + LV(36)-1,座標.y + LV(37)-1 ,27,27 }, Color::White, true);
					//Drawing::Rect({ 座標.x + LV(36),座標.y + LV(37) ,25,25}, Color::Blue, true);

					//MIcon::スキル[pskill->系統].Draw({ 座標.x + LV(36),座標.y + LV(37) });//スキルアイコンと習得状態
					//MFont::Bメイリオ小.DrawBold({ 座標.x + LV(38) , 座標.y + LV(39) }, Color::White, Color::Black, "習得");//習得状態と必要レベル
				} else {
					Drawing::Rect({ 座標.x + LV(36) - 2,座標.y + LV(37) - 2 ,29,29 }, Color::Gray, true);
					Drawing::Rect({ 座標.x + LV(36) - 1,座標.y + LV(37) - 1 ,27,27 }, Color::White, true);
					Drawing::Rect({ 座標.x + LV(36),座標.y + LV(37) ,25,25 }, Color::Gray, true);

					//Screen::SetBright({ 128,128,128 });
					MIcon::スキル[pskill->系統].Draw({ 座標.x + LV(36),座標.y + LV(37) });//スキルアイコンと習得状態
					//Screen::SetBright();

					int slv = pskill->必要SP - sp + it->Lv;
					sp -= pskill->必要SP;

					MFont::Bメイリオ小.DrawBold({ 座標.x + LV(38) , 座標.y + LV(39) }, Color::White, Color::Black, { "L" , slv });//習得状態と必要レベル
				}

				MFont::Bメイリオ中.DrawBold({ 座標.x + LV(40) , 座標.y + LV(41) }, Color::White, Color::Black, pskill->名前);//スキル名

				MFont::Bメイリオ小.DrawBold({ 座標.x + LV(42) , 座標.y + LV(43) }, Color::White, Color::Black, pskill->説明);//説明文

				座標.y += LV(44);
			}

#undef LV
		}

		void InfoItem(int itemID, Point 座標)
		{
			#define LV(a) DV::I[9][a]
			//Aスキル、
			auto* it = &Item::data[itemID];
			ヘルプ横幅 = LV(0);
			ヘルプ縦幅 = LV(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			//アイコン、武器系統、名前
			MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(3) }, LV(4), LV(5), 枠スキン);

			MIcon::アイテム[it->見た目].Draw({ 座標.x + LV(6),座標.y + LV(7) });
			//MIcon::装備種[it->種類].Draw({ 座標.x + LV(8),座標.y + LV(7) });
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(9),座標.y + LV(10) }, Color::White, Color::Black, it->名前);

			//基礎ステータス-依存してるのは文字色変化
			MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(11) }, LV(4), LV(12), 枠スキン);
			
			Color col[5];

			for (int a = 0; a < 5; a++)
			{
				col[a].SetColor(128, 128, 128);
			}

			if (it->追加Str > 0) { col[0].SetColor(255, 255, 255); }
			if (it->追加Dex > 0) { col[1].SetColor(255, 255, 255); }
			if (it->追加Int > 0) { col[2].SetColor(255, 255, 255); }
			if (it->追加Vit > 0) { col[3].SetColor(255, 255, 255); }
			if (it->追加Agi > 0) { col[4].SetColor(255, 255, 255); }

			Color 強調色(255, 64, 64);

			if (it->依存ステータス == StatusType::Str) { col[0] = 強調色; }
			if (it->依存ステータス == StatusType::Dex) { col[1] = 強調色; }
			if (it->依存ステータス == StatusType::Int) { col[2] = 強調色; }
			if (it->依存ステータス == StatusType::Vit) { col[3] = 強調色; }
			if (it->依存ステータス == StatusType::Agi) { col[4] = 強調色; }

			MFont::BArial小.DrawBold({ 座標.x + LV(14),座標.y + LV(13) }, col[0], Color::Black, "STR");
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15),座標.y + LV(13) }, col[1], Color::Black, "DEX");
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15)*2,座標.y + LV(13) }, col[2], Color::Black, "INT");
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15)*3,座標.y + LV(13) }, col[3], Color::Black, "VIT");
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15)*4,座標.y + LV(13) }, col[4], Color::Black, "AGI");

			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(16),座標.y + LV(17) }, Color::White, Color::Black, { it->追加Str },true);
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15) + LV(16),座標.y + LV(17) }, Color::White, Color::Black, { it->追加Dex }, true);
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15)*2 + LV(16),座標.y + LV(17) }, Color::White, Color::Black, { it->追加Int }, true);
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15)*3 + LV(16),座標.y + LV(17) }, Color::White, Color::Black, { it->追加Vit }, true);
			MFont::BArial小.DrawBold({ 座標.x + LV(14) + LV(15)*4 + LV(16),座標.y + LV(17) }, Color::White, Color::Black, { it->追加Agi }, true);

			//Aスキルアイコン、名前 、チャージ 、依存 、説明文 X 02
			for (int a = 0; a < 2; a++)
			{
				MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(18) + LV(32) * a }, LV(4), LV(19), 枠スキン);
				MIcon::スキル[ActiveSkill::data[it->Aスキル[a]].系統].Draw({ 座標.x + LV(20),座標.y + LV(21) + LV(32) * a });
				//MIcon::ステータス種[ActiveSkill::data[it->Aスキル[a]].依存ステータス].SetColor(Color::Red);
				//MIcon::ステータス種[ActiveSkill::data[it->Aスキル[a]].依存ステータス].DrawRotate({ 座標.x + LV(22),座標.y + LV(23) + LV(32) * a },0.7,0);
				
				MIcon::アイコン[IconType::星].Draw({ 座標.x + LV(24),座標.y + LV(25) + LV(32) * a });//チャージアイコン
				
				MFont::Bメイリオ中.DrawBold({ 座標.x + LV(26),座標.y + LV(27) + LV(32) * a }, Color::White, Color::Black, ActiveSkill::data[it->Aスキル[a]].名前);
				MFont::Bメイリオ小.DrawBold({ 座標.x + LV(28),座標.y + LV(29) + LV(32) * a }, Color::White, Color::Black, ActiveSkill::data[it->Aスキル[a]].必要チャージ);
				MFont::Bメイリオ小.DrawBold({ 座標.x + LV(30),座標.y + LV(31) + LV(32) * a }, Color::White, Color::Black, ActiveSkill::data[it->Aスキル[a]].説明);
			}

			//製造時間、製造素材量
			MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(33) }, LV(4), LV(34), 枠スキン);
			//MIcon::アイコン[IconType::ハンマー].Draw({ 座標.x + LV(35),座標.y + LV(36) });
			//MIcon::素材[it->素材[0]].Draw({ 座標.x + LV(37),座標.y + LV(38) });
			//if (it->素材必要数[1] > 0) { MIcon::素材[it->素材[1]].Draw({ 座標.x + LV(37) + LV(39) ,座標.y + LV(38) }); }
			//if (it->素材必要数[1] > 0) { MIcon::素材[it->素材[2]].Draw({ 座標.x + LV(37) + LV(39) * 2,座標.y + LV(38) }); }

			//MFont::BArial中.DrawBold({ 座標.x + LV(40) , 座標.y + LV(41) }, Color::White, Color::Black, it->必要製造力, true);
			//MFont::BArial小.DrawBold({ 座標.x + LV(42) + LV(44) , 座標.y + LV(43) }, Color::White, Color::Black, it->素材必要数[0], true);
			//if (it->素材必要数[1] > 0) {MFont::BArial小.DrawBold({ 座標.x + LV(42) + LV(44) + LV(39), 座標.y + LV(43) }, Color::White, Color::Black, it->素材必要数[1], true);}
			//if (it->素材必要数[1] > 0) { MFont::BArial小.DrawBold({ 座標.x + LV(42) + LV(44) + LV(39) * 2, 座標.y + LV(43) }, Color::White, Color::Black, it->素材必要数[2], true); }
			
			
			//販売価格、集客力
			MIcon::アイコン[IconType::資金].Draw({ 座標.x + LV(45),座標.y + LV(46) });//販売価格
			//MIcon::アイコン[IconType::人口].Draw({ 座標.x + LV(47),座標.y + LV(46) });//集客

			MFont::BArial中.DrawBold({ 座標.x + LV(48) , 座標.y + LV(49) }, Color::White, Color::Black, it->値段, true);
			//MFont::BArial中.DrawBold({ 座標.x + LV(50) , 座標.y + LV(49) }, Color::White, Color::Black, it->集客力,true);

			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(51) , 座標.y + LV(53) }, Color::White, Color::Black, "製造力");
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(52) , 座標.y + LV(53) }, Color::White, Color::Black, "素材");
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(54) , 座標.y + LV(56) }, Color::White, Color::Black, "値段");
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(55) , 座標.y + LV(56) }, Color::White, Color::Black, "集客力");

#undef LV
		}

		/*非実装*/
		void InfoASkill(int skillID,Point 座標)
		{
			#define LV(a) DV::I[11][a]
			//アイコン、影響ステータス、名前、説明文、必要チャージ
			auto* it = &ActiveSkill::data[skillID];

			MFont::メイリオ中.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, "Aスキル");
#undef LV
		}

		void InfoDungeon(Dungeon* it, Point 座標)
		{
			#define LV(a) DV::I[10][a]
			//、ボスの有無、宝物の有無、、雑魚モンスターの種類、出やすい素材
			ヘルプ縦幅 = LV(0);
			ヘルプ横幅 = LV(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			MSystem::DrawWindow({ 座標.x + 5,座標.y + 5 }, 210, 31, LV(12));
			MSystem::DrawWindow({ 座標.x + 5,座標.y + 38 }, 210, LV(13), LV(12));
			MSystem::DrawWindow({ 座標.x + 5,座標.y + 83 }, 210, 31, LV(12));

			//アイコン
			MIcon::ダンジョン[it->種類].Draw({ 座標.x + LV(2),座標.y + LV(3) });
			//ランク
			MIcon::アイコン[IconType::星].Draw({ 座標.x + LV(8),座標.y + LV(9) });
			MFont::BArial中.DrawBold({ 座標.x + LV(10),座標.y + LV(11) }, Color::White, Color::Black, { it->ランク+1 });

			//レベル
			MFont::BArial小.DrawBold({ 座標.x + LV(6),座標.y + LV(7) }, Color::White, Color::Black, {"Lv" ,it->Lv});

			//名前
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(4),座標.y + LV(5) }, Color::White, Color::Black, it->名前);
			

			//探索率、財宝次ダンジョン等イベント発見状態、特産品
			MFont::Bメイリオ中.DrawBold({ 座標.x + LV(14),座標.y + LV(15) }, Color::White, Color::Black, { it->探索率[Guild::P->id]*100, "%" },true);

			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(35),座標.y + LV(34) }, Color::White, Color::Black, { "探索率"});
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(36),座標.y + LV(34) }, Color::White, Color::Black, { "地図" });
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(37),座標.y + LV(34) }, Color::White, Color::Black, { "宝物" });
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(38),座標.y + LV(34) }, Color::White, Color::Black, { "特産" });

			MIcon::アイコン[IconType::星].Draw({ 座標.x + LV(16),座標.y + LV(17) });
			MIcon::アイコン[IconType::星].Draw({ 座標.x + LV(18),座標.y + LV(19) });
			MIcon::素材[MaterialType::金属].Draw({ 座標.x + LV(20),座標.y + LV(21) });

			//ボス状態、雑魚モンスター

			if (it->isボス生存 == false)
			{
				MFont::Bメイリオ中.DrawBold({ 座標.x + LV(22),座標.y + LV(23) }, Color::White, Color::Black, { "Hunted!" });
			} else if(it->探索率[Guild::P->id] > 50){
				MFont::Bメイリオ中.DrawBold({ 座標.x + LV(22),座標.y + LV(23) }, Color::White, Color::Black, { "Alive" });
			} else {
				MFont::Bメイリオ中.DrawBold({ 座標.x + LV(22),座標.y + LV(23) }, Color::White, Color::Black, { "Unknown" });
			}

			MUnit::ユニット[MonsterClass::data[(int)it->ボスモンスター].見た目][1]->DrawRotate({ 座標.x + LV(24),座標.y + LV(25)},2,0);
			MUnit::ユニット[MonsterClass::data[(int)it->雑魚モンスター[0]].見た目][1]->DrawRotate({ 座標.x + LV(26),座標.y + LV(27) }, 1, 0);
			MUnit::ユニット[MonsterClass::data[(int)it->雑魚モンスター[1]].見た目][1]->DrawRotate({ 座標.x + LV(28),座標.y + LV(27) }, 1, 0);
			MUnit::ユニット[MonsterClass::data[(int)it->雑魚モンスター[2]].見た目][1]->DrawRotate({ 座標.x + LV(29),座標.y + LV(27) }, 1, 0);
			
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(30),座標.y + LV(31) }, Color::White, Color::Black, "Boss");
			MFont::Bメイリオ小.DrawBold({ 座標.x + LV(32),座標.y + LV(33) }, Color::White, Color::Black, "Monster");
#undef LV
		}

		void InfoManagement(Management* it, Point 座標)
		{
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			#define LV(a) DV::I[12][a]
			//アイコン、ランク、名前、必要MP、必要資金、説明文
			MFont::メイリオ中.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, "経営戦術");
#undef LV
		}

	};


	class GUI_Object : public GUI_Help
	{
	public:

		Rect 位置;
		bool is固定 = false;//スクロールしない

		/*描画内容*/
		virtual void Draw()
		{
			Draw派生(位置.x, 位置.y);
			//デバッグ用に位置を表示
			if(SV::gui_check)Drawing::Rect({ 位置.x, 位置.y ,位置.GetW() , 位置.GetH()},Color::Red,false);
		}

		virtual void Draw派生(double px,double py)
		{

		}

		/*クリックチェック*/
		void 操作チェック(double px , double py)
		{
			Rect pt = { 位置.x + px, 位置.y +py , 位置.GetW() , 位置.GetH()};

			if (Input::mouse.GetPoint().Hit(&pt))
			{
				if (Input::mouse.Left.on == true)
				{
					Click(Input::mouse.x-位置.x-px,Input::mouse.y-位置.y-py);
				}
				if (Input::mouse.Left.off == true)
				{
					Drop(Input::mouse.x - 位置.x-px, Input::mouse.y - 位置.y-py);
				}
			}
		}

		/*クリック操作*/
		virtual void Click(double px,double py)
		{

		}

		/*ドロップ操作*/
		virtual void Drop(double px, double py)
		{

		}



	};

	class GUI_Tab : public GUI_Object
	{
	public:
		int 番号;
		int 文字オフセット = 0;
		int& タブ操作;
		IconType アイコン;
		SkillType スキルアイコン = SkillType::COUNT;
		int アイコンオフセット = 0;
		std::string 文字;
		//NEW表示

		GUI_Tab( int& タブ操作,int 番号, IconType アイコン ,std::string 文字) : 
			番号(番号),タブ操作(タブ操作),アイコン(アイコン),文字(文字)
		{
			is固定 = true;
		}

		void Set(int 番号, int* タブ操作, IconType アイコン, std::string& 文字)
		{
		}

		void Draw派生(double px, double py)
		{
			int no = 14;
			if (タブ操作 == 番号) { no = 12; }

			MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH()+10 , no);

			if (スキルアイコン != SkillType::COUNT)
			{
				//Screen::SetBright(Color::Black);
				MIcon::スキル[スキルアイコン].DrawRotate({ px + 位置.GetW() / 2 , py + (位置.GetH() - 10) / 2 + アイコンオフセット }, 1, 0);
				//Screen::SetBright();
			} else {
				MIcon::アイコン[アイコン].DrawRotate({ px + 位置.GetW() / 2 , py + (位置.GetH() - 10) / 2 + アイコンオフセット }, 2, 0);
			}

			px -= MFont::メイリオ中.GetDrawStringWidth(文字)/2;
			MFont::メイリオ中.DrawBold({ px + 位置.GetW() / 2 ,py + (位置.GetH()-10) / 2 + 文字オフセット}, Color::White, Color::Black, 文字);
		}

		void Click(double px, double py)
		{
			タブ操作 = 番号;
		}
	};
}