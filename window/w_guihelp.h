//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once


namespace SDX_BSC
{
	using namespace SDX;

	/*ポップアップヘルプ*/

	class GUI_Help
	{
	public:
		const int 枠スキン = 41;
		const int 内スキン = 50;

		int ヘルプ縦幅 = 50;
		int ヘルプ横幅 = 50;
		bool isヘルプ表示 = true;
		std::string ヘルプメッセージ = "";

		static Management* 戦術;

		/*ヘルプウィンドウ描画共通処理*/
		void Info()
		{
			//if (Game::isヘルプ == false) { return; }

			//Point 補正座標;
			//補正座標.x = 座標.x - 親ウィンドウ->相対座標.x - 位置.x;
			//補正座標.y = 座標.y - 親ウィンドウ->相対座標.y - 位置.y;
			Info派生( Input::mouse.GetPoint() );
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
			InfoMessage(座標);
		}

		void SetHelp(std::string メッセージ, int 高さ = 0)
		{
			ヘルプメッセージ = メッセージ;
			ヘルプ横幅 = MFont::MSize.GetDrawStringWidth(ヘルプメッセージ) + 20;

			if (高さ == 0)
			{
				size_t 開始位置 = 0;
				size_t 終了位置 = 0;
				int 行数 = 1;

				while (終了位置 != std::string::npos)
				{
					終了位置 = メッセージ.find("\n", 開始位置);
					開始位置 = 終了位置 + 1;
					行数++;
				}

				ヘルプ縦幅 = 行数 * 20;
			}

		}

		void InfoMessage(Point 座標)
		{
			if (ヘルプメッセージ == "") { return; }

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);
			MFont::MSize.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
		}

		void InfoHunter(Warker* it, Point 座標)
		{
#define LV(a) DV::I[11][a]

			ヘルプ横幅 = LV(0);
			ヘルプ縦幅 = LV(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			//アイコン、名前、所属、レベル、経験値、給料、忠誠度
			座標.y += LV(2);
			MSystem::DrawWindow({ 座標.x + LV(3),座標.y + LV(4) }, LV(5), LV(6), 内スキン);

			MUnit::ユニット[it->見た目][1]->DrawRotate({ 座標.x + LV(7) ,座標.y + LV(8) }, 2, 0);

			MFont::BSSize.DrawBold({ 座標.x + LV(9) , 座標.y + LV(10) }, Color::White, Color::Black, { "Lv " , it->Lv });
			MFont::BMSize.DrawBold({ 座標.x + LV(11) , 座標.y + LV(12) }, Color::White, Color::Black, it->名前);

			double exprate = it->Get経験値獲得率();

			MSystem::DrawBar({ 座標.x + LV(13) , 座標.y + LV(14) }, LV(15), LV(16), exprate, 1, Color::Blue, Color::White, Color::White, true);//経験値

			//装備品、Aスキル
			//最大HP、基礎ステ、製造力
			座標.y += LV(17);
			MSystem::DrawWindow({ 座標.x + LV(3),座標.y + LV(4) }, LV(5), LV(18), 内スキン);

			MIcon::アイテム[Item::data[it->装備[0]].見た目].Draw({ 座標.x + LV(19),座標.y + LV(20) });//装備
			MIcon::アイテム[Item::data[it->装備[1]].見た目].Draw({ 座標.x + LV(19),座標.y + LV(20) + LV(21) });
			MFont::BSSize.DrawBold({ 座標.x + LV(22) , 座標.y + LV(23) }, Color::White, Color::Black, { "Lv" , Item::data[it->装備[0]].ランク });
			MFont::BSSize.DrawBold({ 座標.x + LV(22) , 座標.y + LV(23) + LV(21) }, Color::White, Color::Black, { "Lv" , Item::data[it->装備[1]].ランク });

			MFont::BMSize.DrawBold({ 座標.x + LV(24) , 座標.y + LV(25) }, Color::White, Color::Black, Item::data[it->装備[0]].名前);//装備名
			MFont::BMSize.DrawBold({ 座標.x + LV(24) , 座標.y + LV(25) + LV(21) }, Color::White, Color::Black, Item::data[it->装備[1]].名前);

			//各種ステータス
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 0 }, Color::White, Color::Black, TX::Help_ステータス[0] );
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 1 }, Color::White, Color::Black, TX::Help_ステータス[1]);
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 2 }, Color::White, Color::Black, TX::Help_ステータス[2]);
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 3 }, Color::White, Color::Black, TX::Help_ステータス[3]);
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 4 }, Color::White, Color::Black, TX::Help_ステータス[4]);
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 5 }, Color::White, Color::Black, TX::Help_ステータス[5]);
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 6 }, Color::White, Color::Black, TX::Help_ステータス[6]);
			MFont::BMSize.DrawBold({ 座標.x + LV(26) , 座標.y + LV(27) + LV(28) * 7 }, Color::White, Color::Black, TX::Help_ステータス[7]);

			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 0 }, Color::White, Color::Black, (int)it->最大HP , true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 1 }, Color::White, Color::Black, (int)it->基礎Str, true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 2 }, Color::White, Color::Black, (int)it->基礎Dex, true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 3 }, Color::White, Color::Black, (int)it->基礎Int, true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 4 }, Color::White, Color::Black, (int)it->基礎防御[DamageType::物理], true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 5 }, Color::White, Color::Black, (int)it->基礎防御[DamageType::魔法], true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 6 }, Color::White, Color::Black, (int)it->基礎命中, true);
			MFont::BMSize.DrawBold({ 座標.x + LV(29) , 座標.y + LV(30) + LV(31) * 7 }, Color::White, Color::Black, (int)it->基礎回避, true);

			//Aスキル-アイコン、名前、説明
			座標.x += LV(32);
			座標.y += LV(33);
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				InfoASkillSub(it->アクティブスキル[a], { 座標.x , 座標.y + a * 80});
			}

			//Pスキル-アイコン、名前、説明
			座標.x += LV(34);
			座標.y += LV(35);
			MSystem::DrawWindow({ 座標.x + LV(45),座標.y + LV(46) }, LV(47), LV(48), 内スキン);
			int sp = it->スキルポイント;
			for (int a = 0; a < CV::最大Pスキル数; a++)
			{
				auto pskill = &PassiveSkill::data[it->パッシブスキル[a]];
				
				std::string s = "";

				if (it->isパッシブスキル習得[a] == true)
				{
					MSystem::DrawSkill(pskill->系統, { 座標.x + LV(36), 座標.y + LV(37) }, Color(0, 141, 255));
				} else {
					int slv = pskill->必要SP - sp + it->Lv;
					sp -= pskill->必要SP;

					if (slv < 10)
					{
						s = "Lv ";
						s += std::to_string(slv);
					} else {
						s = "Lv";
						s += std::to_string(slv);
					}

					MSystem::DrawSkill(pskill->系統, { 座標.x + LV(36), 座標.y + LV(37) }, Color::Gray , s);
					//MFont::Bメイリオ小.DrawBold({ 座標.x + LV(38) , 座標.y + LV(39) }, Color::White, Color::Black, { "Lv" , slv },true);//習得状態と必要レベル
				}

				MFont::BMSize.DrawBold({ 座標.x + LV(40) , 座標.y + LV(41) }, Color::White, Color::Black, pskill->名前);//スキル名

				MFont::BSSize.DrawBold({ 座標.x + LV(42) , 座標.y + LV(43) }, Color::White, Color::Black, pskill->説明);//説明文

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

			for (int a = 0; a < 2; a++)
			{
				if (it->Aスキル[a] != nullptr && it->Aスキル[a]->id != 0) { ヘルプ縦幅 += LV(22); };
				if (it->Pスキル[a] != nullptr && it->Pスキル[a]->id != 0) { ヘルプ縦幅 += LV(22); };
			}

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			//アイコン、武器系統、名前、Lv、ユニーク
			MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(3) }, LV(0)-10, LV(5), 内スキン);

			MIcon::アイテム[it->見た目].Draw({ 座標.x + LV(6),座標.y + LV(7) });
			MFont::BSSize.DrawBold({ 座標.x + LV(38) ,座標.y + LV(39) }, Color::White, Color::Black, {"Lv" , it->ランク});


			MFont::BMSize.DrawBold({ 座標.x + LV(8),座標.y + LV(9) }, Color::White, Color::Black, it->名前);

			//販売価格、集客力
			MIcon::アイコン[IconType::資金].Draw({ 座標.x + LV(10),座標.y + LV(11) });//販売価格

			MFont::BMSize.DrawBold({ 座標.x + LV(12) , 座標.y + LV(13) }, Color::White, Color::Black, { it->値段 , " G"}, true);

			//基礎ステータス
			MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(14) }, LV(0) - 10, LV(15), 内スキン);

			int now_x = 0;
			int num = 0;
			std::string ステ名 = "";

			for (int a = 0; a < 8; a++)
			{
				ステ名 = TX::Help_ステータス[a];

				switch (a)
				{
				case 0:num = it->追加Hp; break;
				case 1:num = it->追加Str;break;
				case 2:num = it->追加Dex; break;
				case 3:num = it->追加Int; break;
				case 4:num = it->防御[DamageType::物理]; break;
				case 5:num = it->防御[DamageType::魔法]; break;
				case 6:num = it->命中; break;
				case 7:num = it->回避; break;
				}

				if (num <= 0) { continue; }

				MFont::BSSize.DrawBold({ 座標.x + LV(16) + now_x,座標.y + LV(17) }, Color::White, Color::Black, { ステ名 , "+" , num });
				//MFont::BSSize.DrawBold({ 座標.x + LV(18) + now_x,座標.y + LV(19) }, Color::White, Color::Black, { num }, true);

				now_x += LV(20);
			}

			int now_y = LV(35);

			//Aスキルアイコン、名前 、チャージ 、依存 、説明文 X 02
			for (int a = 0; a < 2; a++)
			{

				if( it->Aスキル[a] == nullptr || it->Aスキル[a]->id == 0) { continue; }

				InfoASkillSub(it->Aスキル[a], {座標.x , 座標.y + now_y} );

				now_y += LV(21);
			}

			//Pスキル、とりあえず未実装

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

			//アイコン,レベル,名前
			MSystem::DrawWindow({ 座標.x + 5,座標.y + 5 }, LV(1) - 10 , LV(13), 内スキン);
			MSystem::DrawWindow({ 座標.x + 5,座標.y + LV(13) + 10 }, LV(1) - 10, LV(0) - LV(13) - 15, 内スキン);
			//MSystem::DrawWindow({ 座標.x + 5,座標.y + 83 }, LV(1) - 10, 31, LV(12));

			//アイコン
			MIcon::ダンジョン[it->種類].Draw({ 座標.x + LV(2),座標.y + LV(3) });
			//エリアレベル
			MFont::BSSize.DrawBold({ 座標.x + LV(6),座標.y + LV(7) }, Color::White, Color::Black, {"Lv" ,it->Lv});

			//名前
			MFont::BMSize.DrawBold({ 座標.x + LV(4),座標.y + LV(5) }, Color::White, Color::Black, { "第一層\n" , it->名前 });
			

			//探索率、財宝次ダンジョン等イベント発見状態、特産品
			MSystem::DrawBar({ 座標.x + LV(8),座標.y + LV(9) }, LV(10), LV(11), it->探索率, 1, Color::Blue, Color::White, Color::White, true);
			MFont::BMSize.DrawBold({ 座標.x + LV(14),座標.y + LV(15) }, Color::White, Color::Black, { it->探索率*100, "%" },true);

			MFont::BSSize.DrawBold({ 座標.x + LV(34),座標.y + LV(36) }, Color::White, Color::Black, { it->発見地図 , " / " , it->最大地図 });
			MFont::BSSize.DrawBold({ 座標.x + LV(34),座標.y + LV(37) }, Color::White, Color::Black, { it->発見財宝 , " / " , it->最大財宝 });
			MIcon::アイコン[IconType::地図].Draw({ 座標.x + LV(16),座標.y + LV(17) });
			MIcon::アイコン[IconType::宝箱].Draw({ 座標.x + LV(18),座標.y + LV(19) });
			MIcon::アイコン[IconType::ボス].Draw({ 座標.x + LV(20),座標.y + LV(21) });

			//未発見だとボスアイコンを？マークにする

			if(it->isボス生存 == false){
				MFont::BSSize.DrawBold({ 座標.x + LV(22),座標.y + LV(23) }, Color::White, Color::Black, { TX::Dungeon_討伐 });
			} else if(it->isボス発見 == true){
				MFont::BSSize.DrawBold({ 座標.x + LV(22),座標.y + LV(23) }, Color::White, Color::Black, { TX::Dungeon_発見 });
			} else {
				MFont::BSSize.DrawBold({ 座標.x + LV(22),座標.y + LV(23) }, Color::White, Color::Black, { TX::Dungeon_捜索 });
			}

			MUnit::ユニット[MonsterClass::data[(int)it->ボスモンスター].見た目][1]->DrawRotate({ 座標.x + LV(24),座標.y + LV(25) }, 3, 0);

			MUnit::ユニット[MonsterClass::data[(int)it->雑魚モンスター[0]].見た目][1]->DrawRotate({ 座標.x + LV(26),座標.y + LV(27) }, 2, 0);
			MUnit::ユニット[MonsterClass::data[(int)it->雑魚モンスター[1]].見た目][1]->DrawRotate({ 座標.x + LV(28),座標.y + LV(27) }, 2, 0);
			MUnit::ユニット[MonsterClass::data[(int)it->雑魚モンスター[2]].見た目][1]->DrawRotate({ 座標.x + LV(29),座標.y + LV(27) }, 2, 0);
			
			MFont::BSSize.DrawBold({ 座標.x + LV(30),座標.y + LV(31) }, Color::White, Color::Black, "Boss");
			MFont::BSSize.DrawBold({ 座標.x + LV(32),座標.y + LV(33) }, Color::White, Color::Black, "Monster");



#undef LV
		}

		void InfoManagement(Management* it, Point 座標)
		{
			戦術 = it;//消費資金表示するための代入
			#define LV(a) DV::I[12][a]
			ヘルプ縦幅 = LV(0);
			ヘルプ横幅 = LV(1);

			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン);

			//アイコン + LV + 名前枠 + 消費資金枠
			MSystem::DrawWindow({ 座標.x + LV(14) , 座標.y + LV(15) }, LV(17), LV(18), 内スキン);
			//説明文枠
			MSystem::DrawWindow({ 座標.x + LV(14) , 座標.y + LV(16) }, LV(17), LV(19), 内スキン);

			//名前、説明文、アイコン、Lv、必要資金、(使用回数)
			MFont::MSize.DrawBold({ 座標.x + LV(2),座標.y + LV(3) }, Color::White, Color::Black, it->名前);
			MFont::MSize.DrawBold({ 座標.x + LV(4),座標.y + LV(5) }, Color::White, Color::Black, it->説明文);

			MIcon::アイコン[it->アイコン].DrawRotate({ 座標.x + LV(6) , 座標.y + LV(7) }, 2, 0);

			MFont::MSize.DrawBold({ 座標.x + LV(8),座標.y + LV(9) }, Color::White, Color::Black, { "Lv", it->Lv } , true);

			MIcon::アイコン[IconType::資金].Draw({ 座標.x + LV(10) , 座標.y + LV(11) });
			MFont::BMSize.DrawBold({ 座標.x + LV(12) ,座標.y + LV(13) }, Color::White, Color::Black, { (long long)it->消費資金 , " G" }, true);

			#undef LV
		}

		void InfoASkillSub(ActiveSkill* スキル, Point 座標)
		{
#define LV(a) DV::I[9][a]

			MSystem::DrawWindow({ 座標.x + LV(2),座標.y + LV(23)}, LV(0) - 10, LV(24), 内スキン);

			std::string s = "";

			MSystem::DrawSkill(スキル->系統, { 座標.x + LV(25),座標.y + LV(26) },Color(200,64,64 ), s);

			MIcon::アイコン[IconType::時間].Draw({ 座標.x + LV(27),座標.y + LV(28)});//クールダウンor必殺

			MFont::BMSize.DrawBold({ 座標.x + LV(29),座標.y + LV(30) }, Color::White, Color::Black, スキル->名前);
			MFont::BSSize.DrawBold({ 座標.x + LV(31),座標.y + LV(32) }, Color::White, Color::Black, { スキル->必要チャージ });
			if ( スキル->命中 < 2.0 ) { MFont::BSSize.DrawBold({ 座標.x + LV(36),座標.y + LV(37) }, Color::White, Color::Black, { "命中 " , (int)(スキル->命中*100) , "%" }); }
			MFont::BSSize.DrawBold({ 座標.x + LV(33),座標.y + LV(34) }, Color::White, Color::Black, スキル->説明);
			
#undef LV
		}
	};

	Management* GUI_Help::戦術 = nullptr;
}