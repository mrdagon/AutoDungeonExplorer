//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once


namespace SDX_ADE
{
	using namespace SDX;

	/*ポップアップヘルプ*/

	class GUI_Help
	{
	private:
		int help_csv_page = 0;
	public:
		const int 枠スキン = 41;
		const int 内スキン = 50;
		const int 枠透過率 = 192;

		int ヘルプ縦幅 = 50;
		int ヘルプ横幅 = 50;
		bool isヘルプ表示 = true;
		std::string ヘルプメッセージ = "";

		inline int Lph(int no)
		{
			return CSV::I[help_csv_page][no];
		}

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
				座標.x = std::max( 0.0, 座標.x - ヘルプ横幅);
			}
			//縦幅超過
			if (座標.y + ヘルプ縦幅 > Window::GetHeight())
			{
				座標.y = std::max(0.0, 座標.y - ヘルプ縦幅);
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
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン,0, 枠透過率);
			MFont::MSize.DrawBold({ 座標.x + 10,座標.y + 10 }, Color::White, Color::Black, ヘルプメッセージ);
		}

		void InfoExplorer(Explorer* it, Point 座標)
		{
			help_csv_page = 11;

			ヘルプ横幅 = Lph(0);
			ヘルプ縦幅 = Lph(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);

			//アイコン、名前、所属、レベル、経験値、給料、忠誠度
			座標.y += Lph(2);
			MSystem::DrawWindow({ 座標.x + Lph(3),座標.y + Lph(4) }, Lph(5), Lph(6), 内スキン, 0, 枠透過率);

			it->image[0][1]->DrawRotate({ 座標.x + Lph(7) ,座標.y + Lph(8) }, 2, 0);

			MFont::BSSize.DrawBold({ 座標.x + Lph(9) , 座標.y + Lph(10) }, Color::White, Color::Black, { "Lv " , it->Lv });
			MFont::BMSize.DrawBold({ 座標.x + Lph(11) , 座標.y + Lph(12) }, Color::White, Color::Black, it->名前);

			MSystem::DrawBar({ 座標.x + Lph(13) , 座標.y + Lph(14) }, Lph(15), Lph(16), it->経験値 / it->Get要求経験値(), 1, Color::Blue, Color::White, Color::White, true);//経験値

			//装備品、Aスキル
			//基礎ステ、製造力
			座標.y += Lph(17);
			MSystem::DrawWindow({ 座標.x + Lph(3),座標.y + Lph(4) }, Lph(5), Lph(18), 内スキン, 0, 枠透過率);

			for (int a = 0; a < 2; a++)
			{
				//MIcon::アイテム[it->装備[a]->見た目].Draw({ 座標.x + Lph(19),座標.y + Lph(20) + Lph(21) * a });//装備
				MFont::BSSize.DrawBold({ 座標.x + Lph(22) , 座標.y + Lph(23) + Lph(21) * a }, Color::White, Color::Black, { "Lv" , it->装備[a]->ランク });
				MFont::BMSize.DrawBold({ 座標.x + Lph(24) , 座標.y + Lph(25) + Lph(21) * a }, Color::White, Color::Black, it->装備[a]->名前);
				MFont::SSize.DrawBold({ 座標.x + Lph(22) , 座標.y + Lph(23) + Lph(21) * a }, Color::White, Color::Black, { "Lv" , it->装備[a]->ランク });
				MFont::MSize.DrawBold({ 座標.x + Lph(24) , 座標.y + Lph(25) + Lph(21) * a }, Color::White, Color::Black, it->装備[a]->名前);

			}
			
			//各種ステータス
			for (int a = 0; a < 8; a++)
			{
				//ステータス名
				MFont::BMSize.DrawBold({ 座標.x + Lph(26) , 座標.y + Lph(27) + Lph(28) * a }, Color::White, Color::Black, TX::Help_ステータス[a]);

				//基礎ステータス
				int na, nb;
				switch (a)
				{
					case 0: na = it->基礎ステ[StatusType::HP]; nb = it->補正ステ[StatusType::HP]; break;
					case 1: na = it->基礎ステ[StatusType::力]; nb = it->補正ステ[StatusType::力]; break;
					case 2: na = it->基礎ステ[StatusType::技]; nb = it->補正ステ[StatusType::技]; break;
					case 3: na = it->基礎ステ[StatusType::知]; nb = it->補正ステ[StatusType::知]; break;
					case 4: na = it->基礎ステ[StatusType::物防]; nb = it->補正ステ[StatusType::物防]; break;
					case 5: na = it->基礎ステ[StatusType::魔防]; nb = it->補正ステ[StatusType::魔防]; break;
					case 6: na = it->基礎ステ[StatusType::命中]; nb = it->補正ステ[StatusType::命中]; break;
					case 7: na = it->基礎ステ[StatusType::回避]; nb = it->補正ステ[StatusType::回避]; break;
				}

				MFont::BMSize.DrawBold({ 座標.x + Lph(29) , 座標.y + Lph(30) + Lph(31) * a }, Color::White, Color::Black, na , true);

				//装備＆パッシブ補正値
				if (nb - na > 0) { MFont::BMSize.DrawBold({ 座標.x + Lph(49) , 座標.y + Lph(30) + Lph(31) * a }, Color(128,255,128), Color::Black, { "+",nb - na }, true); }
			}

			//Aスキル-アイコン、名前、説明
			座標.x += Lph(32);
			座標.y += Lph(33);
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				InfoASkillSub(it->Aスキル[a], { 座標.x , 座標.y + a * 80} , true);
			}

			//Pスキル-アイコン、名前、説明
			座標.x += Lph(34);
			座標.y += Lph(35);
			MSystem::DrawWindow({ 座標.x + Lph(45),座標.y + Lph(46) }, Lph(47), Lph(48), 内スキン, 0, 枠透過率);
			int sp = it->スキルポイント;

			for (auto& itp : it->Pスキル)
			{
				InfoPSkillSub(itp, { 座標.x , 座標.y },true,false);
				座標.y += Lph(44);
			}
		}

		void InfoItem(Item* item, Point 座標)
		{
			help_csv_page = 9;

			ヘルプ横幅 = Lph(0);
			ヘルプ縦幅 = Lph(1);

			for (auto& it : item->Pスキル)
			{
				if ( it != nullptr && it->ID != 0) { ヘルプ縦幅 += Lph(22); };
			}


			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);

			//アイコン、武器系統、名前、Lv、ユニーク
			MSystem::DrawWindow({ 座標.x + Lph(2),座標.y + Lph(3) }, Lph(0)-10, Lph(5), 内スキン, 0, 枠透過率);

			//MIcon::アイテム[item->見た目].Draw({ 座標.x + Lph(6),座標.y + Lph(7) });
			MFont::BSSize.DrawBold({ 座標.x + Lph(38) ,座標.y + Lph(39) }, Color::White, Color::Black, {"Lv" , item->ランク });


			MFont::BMSize.DrawBold({ 座標.x + Lph(8),座標.y + Lph(9) }, Color::White, Color::Black, item->名前);

			//販売価格、集客力
			MIcon::UI[IconType::資金].Draw({ 座標.x + Lph(10),座標.y + Lph(11) });//販売価格

			//MFont::BMSize.DrawBold({ 座標.x + Lph(12) , 座標.y + Lph(13) }, Color::White, Color::Black, { it->値段 , " G"}, true);

			//基礎ステータス
			MSystem::DrawWindow({ 座標.x + Lph(2),座標.y + Lph(14) }, Lph(0) - 10, Lph(15), 内スキン, 0, 枠透過率);

			int now_x = 0;
			int num = 0;
			std::string ステ名 = "";

			for (int a = 0; a < 8 ; a++)
			{
				ステ名 = TX::Help_ステータス[a];

				switch (a)
				{
					case 0:num = item->ステ[StatusType::HP]; break;
					case 1:num = item->ステ[StatusType::力];break;
					case 2:num = item->ステ[StatusType::技]; break;
					case 3:num = item->ステ[StatusType::知]; break;
					case 4:num = item->ステ[StatusType::物防]; break;
					case 5:num = item->ステ[StatusType::魔防]; break;
					case 6:num = item->ステ[StatusType::命中]; break;
					case 7:num = item->ステ[StatusType::回避]; break;
				}

				if (num <= 0) { continue; }

				MFont::BSSize.DrawBold({ 座標.x + Lph(16) + now_x,座標.y + Lph(17) }, Color::White, Color::Black, { ステ名 , "+" , num });
				
				now_x += Lph(20);
			}

			int now_y = Lph(35);

			//Aスキルアイコン、名前 、チャージ 、依存 、説明文 X 02
			/*
			for (int a = 0; a < 2; a++)
			{

				if( it->Aスキル[a] == nullptr || it->Aスキル[a]->id == 0) { continue; }

				InfoASkillSub(it->Aスキル[a], {座標.x , 座標.y + now_y}, true);

				now_y += Lph(21);
			}
			*/
			//Pスキル、とりあえず未実装
		}

		void InfoDungeon(Dungeon* it, Point 座標)
		{
			help_csv_page = 10;

			//、ボスの有無、宝物の有無、、雑魚モンスターの種類、出やすい素材
			ヘルプ縦幅 = Lph(0);
			ヘルプ横幅 = Lph(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);

			//アイコン,レベル,名前
			MSystem::DrawWindow({ 座標.x + 5,座標.y + 5 }, Lph(1) - 10 , Lph(13), 内スキン, 0, 枠透過率);
			MSystem::DrawWindow({ 座標.x + 5,座標.y + Lph(13) + 10 }, Lph(1) - 10, Lph(0) - Lph(13) - 15, 内スキン, 0, 枠透過率);

			//アイコン
			it->image->Draw({ 座標.x + Lph(2),座標.y + Lph(3) });
			//エリアレベル
			MFont::BSSize.DrawBold({ 座標.x + Lph(6),座標.y + Lph(7) }, Color::White, Color::Black, {"Lv" ,it->雑魚Lv });

			//名前
			MFont::BMSize.DrawBold({ 座標.x + Lph(4),座標.y + Lph(5) }, Color::White, Color::Black, { "第一層\n" , it->名前 });
			

			//探索率、財宝次ダンジョン等イベント発見状態、特産品
			MSystem::DrawBar({ 座標.x + Lph(8),座標.y + Lph(9) }, Lph(10), Lph(11), it->探索率, 1, Color::Blue, Color::White, Color::White, true);
			MFont::BMSize.DrawBold({ 座標.x + Lph(14),座標.y + Lph(15) }, Color::White, Color::Black, { it->探索率*100, "%" },true);

			//MFont::BSSize.DrawBold({ 座標.x + Lph(34),座標.y + Lph(36) }, Color::White, Color::Black, { it->発見地図 , " / " , it->最大地図 });
			//MFont::BSSize.DrawBold({ 座標.x + Lph(34),座標.y + Lph(37) }, Color::White, Color::Black, { it->発見財宝 , " / " , it->最大財宝 });
			MIcon::UI[IconType::地図].Draw({ 座標.x + Lph(16),座標.y + Lph(17) });
			MIcon::UI[IconType::宝箱].Draw({ 座標.x + Lph(18),座標.y + Lph(19) });
			MIcon::UI[IconType::ボス].Draw({ 座標.x + Lph(20),座標.y + Lph(21) });

			//未発見だとボスアイコンを？マークにする

			if(it->isボス生存 == false){
				MFont::BSSize.DrawBold({ 座標.x + Lph(22),座標.y + Lph(23) }, Color::White, Color::Black, { TX::Dungeon_討伐 });
			} else if(it->isボス発見 == true){
				MFont::BSSize.DrawBold({ 座標.x + Lph(22),座標.y + Lph(23) }, Color::White, Color::Black, { TX::Dungeon_発見 });
			} else {
				MFont::BSSize.DrawBold({ 座標.x + Lph(22),座標.y + Lph(23) }, Color::White, Color::Black, { TX::Dungeon_捜索 });
			}

			//it->ボスモンスター[0]->image[0][1]->DrawRotate({ 座標.x + Lph(24),座標.y + Lph(25) }, 3, 0);

			//for(int a=0;a<it->雑魚モンスター.size();a++)
			//{ 
				//it->雑魚モンスター[a]->image[0][1]->DrawRotate({ 座標.x + Lph(26),座標.y + Lph(27) }, 2, 0);
			//}
			//Lph 28 29未使用
			
			MFont::BSSize.DrawBold({ 座標.x + Lph(30),座標.y + Lph(31) }, Color::White, Color::Black, "Boss");
			MFont::BSSize.DrawBold({ 座標.x + Lph(32),座標.y + Lph(33) }, Color::White, Color::Black, "Monster");
		}

		void InfoManagement(Management* it, Point 座標)
		{
			help_csv_page = 12;

			W_Drag::Over戦術 = it;//消費資金表示するための代入

			ヘルプ縦幅 = Lph(0);
			ヘルプ横幅 = Lph(1);

			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);

			//アイコン + Lph + 名前枠 + 消費資金枠
			MSystem::DrawWindow({ 座標.x + Lph(14) , 座標.y + Lph(15) }, Lph(17), Lph(18), 内スキン, 0, 枠透過率);
			//説明文枠
			MSystem::DrawWindow({ 座標.x + Lph(14) , 座標.y + Lph(16) }, Lph(17), Lph(19), 内スキン, 0, 枠透過率);

			//名前、説明文、アイコン、Lv、必要資金、(使用回数)
			MFont::MSize.DrawBold({ 座標.x + Lph(2),座標.y + Lph(3) }, Color::White, Color::Black, it->名前);
			MFont::MSize.DrawBold({ 座標.x + Lph(4),座標.y + Lph(5) }, Color::White, Color::Black, it->説明);

			//MIcon::アイコン[it->アイコン].DrawRotate({ 座標.x + Lph(6) , 座標.y + Lph(7) }, 2, 0);

			MFont::MSize.DrawBold({ 座標.x + Lph(8),座標.y + Lph(9) }, Color::White, Color::Black, { "Lv", it->ランク } , true);

			MIcon::UI[IconType::資金].Draw({ 座標.x + Lph(10) , 座標.y + Lph(11) });
			MFont::BMSize.DrawBold({ 座標.x + Lph(12) ,座標.y + Lph(13) }, Color::White, Color::Black, { (long long)it->消費資金 , " G" }, true);
		}

		void InfoResult(Guild::Party* パーティ,Point 座標)
		{
			help_csv_page = 17;

			ヘルプ横幅 = Lph(0);
			ヘルプ縦幅 = Lph(1);

			Info座標補正(座標);

			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);
			MFont::BSSize.DrawBold({ 座標.x + Lph(2) , 座標.y + Lph(3) }, Color::White, Color::Black, "与えたダメージ");
			MFont::BSSize.DrawBold({ 座標.x + Lph(2) , 座標.y + Lph(3) + Lph(4) }, Color::White, Color::Black, "受けたダメージ");
			MFont::BSSize.DrawBold({ 座標.x + Lph(2) , 座標.y + Lph(3) + Lph(4)*2 }, Color::White, Color::Black, "味方を回復");
			//項目名

			//パーティメンバー
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				const auto it = パーティ->メンバー[a];
				if ( it == nullptr) { continue; }
				it->image[0][1]->DrawRotate({ 座標.x + Lph(5) + Lph(6)*a , 座標.y + Lph(7) }, 2, 0);
				MFont::BSSize.DrawBold({ 座標.x + Lph(8) + Lph(6) * a , 座標.y + Lph(3) + Lph(4) * 0 }, Color::White, Color::Black, it->与ダメージログ,true);
				MFont::BSSize.DrawBold({ 座標.x + Lph(8) + Lph(6) * a , 座標.y + Lph(3) + Lph(4) * 1 }, Color(255,80,80), Color::Black, it->受ダメージログ, true);
				MFont::BSSize.DrawBold({ 座標.x + Lph(8) + Lph(6) * a , 座標.y + Lph(3) + Lph(4) * 2 }, Color(128,255,128), Color::Black, it->回復ログ, true);
			}
		}

		void InfoMonster(Monster* it , int Lv , int isボス, Point 座標)
		{
			help_csv_page = 11;

			//11 page
			ヘルプ横幅 = Lph(0) - Lph(54);
			ヘルプ縦幅 = Lph(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);

			//アイコン、名前、所属、レベル、経験値、給料、忠誠度
			座標.y += Lph(2);
			MSystem::DrawWindow({ 座標.x + Lph(3),座標.y + Lph(4) }, Lph(5) - Lph(54), Lph(6), 内スキン, 0, 枠透過率);

			it->image[0][1]->DrawRotate({ 座標.x + Lph(7) ,座標.y + Lph(8) }, 2, 0);

			MFont::BSSize.DrawBold({ 座標.x + Lph(50) , 座標.y + Lph(51) }, Color::White, Color::Black, { "Lv " , Lv });
			MFont::BMSize.DrawBold({ 座標.x + Lph(52) , 座標.y + Lph(53) }, Color::White, Color::Black, it->種族->名前);

			//素材、レア素材
			座標.y += Lph(17);
			MSystem::DrawWindow({ 座標.x + Lph(3),座標.y + Lph(4) }, Lph(5) - Lph(54), Lph(18), 内スキン, 0, 枠透過率);

			for (int a = 0; a < 1; a++)
			{
				//Material* 素材 = &Material::data[it->種族->素材];

				//if (素材 == nullptr) { continue; }

				//MIcon::アイコン[素材->アイコン].Draw({ 座標.x + Lph(19),座標.y + Lph(20) + Lph(21) * a });//装備
				//MFont::BSSize.DrawBold({ 座標.x + Lph(22) , 座標.y + Lph(23) + Lph(21) * a }, Color::White, Color::Black, { "Lv" , 素材->Lv });
				//MFont::BMSize.DrawBold({ 座標.x + Lph(24) , 座標.y + Lph(25) + Lph(21) * a }, Color::White, Color::Black, 素材->名前);
			}

			//各種ステータス
			for (int a = 0; a < (int)StatusType::COUNT; a++)
			{
				//ステータス名
				MFont::BMSize.DrawBold({ 座標.x + Lph(26) , 座標.y + Lph(27) + Lph(28) * a }, Color::White, Color::Black, TX::Help_ステータス[a]);

				//基礎ステータス
				int na = it->補正ステ[StatusType(a)];

				//補正後のみ表示
				MFont::BMSize.DrawBold({ 座標.x + Lph(29) , 座標.y + Lph(30) + Lph(31) * a }, Color::White, Color::Black, na, true);
			}

			//Aスキル-アイコン、名前、説明
			座標.x += Lph(32) - Lph(54);
			座標.y += Lph(33);
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if (it->Aスキル[a] == nullptr ) { continue; }

				InfoASkillSub(it->Aスキル[a], { 座標.x , 座標.y + a * 80 }, true);
			}

			//Pスキル-アイコン、名前、説明
			座標.x += Lph(34);
			座標.y += Lph(35);
			MSystem::DrawWindow({ 座標.x + Lph(45),座標.y + Lph(46) }, Lph(47), Lph(48), 内スキン, 0, 枠透過率);
			
			//for (int a = 0; a < CV::最大Pスキル数; a++)
			//{
				//auto pskill = &PassiveSkill::data[it->PスキルID[a]];

				//MSystem::DrawSkill(pskill->系統, { 座標.x + Lph(36), 座標.y + Lph(37) }, Color(0, 141, 255));

				//MFont::BMSize.DrawBold({ 座標.x + Lph(40) , 座標.y + Lph(41) }, Color::White, Color::Black, pskill->名前);//スキル名

				//MFont::BSSize.DrawBold({ 座標.x + Lph(42) , 座標.y + Lph(43) }, Color::White, Color::Black, pskill->説明);//説明文

				//座標.y += Lph(44);
			//}

		}

		void InfoMaterial(Material* it, Point 座標)
		{
			help_csv_page = 18;

			ヘルプ横幅 = Lph(0);
			ヘルプ縦幅 = Lph(1);

			Info座標補正(座標);
			MSystem::DrawWindow({ 座標.x , 座標.y }, ヘルプ横幅, ヘルプ縦幅, 枠スキン, 0, 枠透過率);

			//素材アイコン_Lph_所持数
			it->image->DrawRotate({ 座標.x + Lph(2), 座標.y + Lph(3) }, 1, 0);

			MFont::BSSize.DrawBold({ 座標.x + Lph(4) ,座標.y + Lph(5) }, Color::White, Color::Black, { "Lv" , it->ランク }, true);

			//所持数
			MFont::BMSize.DrawBold({ 座標.x + Lph(8) , 座標.y + Lph(9) }, Color::White, Color::Black, { "x",Guild::P->素材数[it->ID] },true);

			//素材名
			MFont::BMSize.DrawBold({ 座標.x + Lph(10) , 座標.y + Lph(11) }, Color::White, Color::Black, it->名前, true);

			//製造出来るアイテムと確率
		}

		void InfoASkillSub(ActiveSkill* スキル, Point 座標 ,bool is枠描画)
		{
			int page_buf = help_csv_page;
			help_csv_page = 9;

			if (is枠描画)
			{
				MSystem::DrawWindow({ 座標.x + Lph(2),座標.y + Lph(23) }, Lph(0) - 10, Lph(24), 内スキン, 0, 枠透過率);
			}

			std::string s = "";

			MSystem::DrawSkill(スキル->image, { 座標.x + Lph(25),座標.y + Lph(26) },Color(200,64,64 ), s);

			MIcon::UI[IconType::時間].Draw({ 座標.x + Lph(27),座標.y + Lph(28)});//クールダウンor必殺

			MFont::BMSize.DrawBold({ 座標.x + Lph(29),座標.y + Lph(30) }, Color::White, Color::Black, スキル->名前);
			MFont::BSSize.DrawBold({ 座標.x + Lph(31),座標.y + Lph(32) }, Color::White, Color::Black, { 1 });
			if ( スキル->命中 < 2.0 ) { MFont::BSSize.DrawBold({ 座標.x + Lph(36),座標.y + Lph(37) }, Color::White, Color::Black, { "命中 " , (int)(スキル->命中*100) , "%" }); }
			MFont::BSSize.DrawBold({ 座標.x + Lph(33),座標.y + Lph(34) }, Color::White, Color::Black, スキル->説明);

			help_csv_page = page_buf;
		}

		void InfoPSkillSub(PassiveSkill* スキル , Point 座標,bool is習得, bool is枠描画 = false)
		{
			int page_buf = help_csv_page;
			help_csv_page = 11;

			std::string s = "";

			if (is枠描画)
			{
				MSystem::DrawWindow({ 座標.x + Lph(55),座標.y + Lph(56) }, Lph(57), Lph(58), 内スキン, 0, 枠透過率);
			}

			if ( is習得)
			{
				MSystem::DrawSkill(スキル->image, { 座標.x + Lph(36), 座標.y + Lph(37) }, Color(0, 141, 255));
			}else {
				MSystem::DrawSkill(スキル->image, { 座標.x + Lph(36), 座標.y + Lph(37) }, Color::Gray, s);
			}

			MFont::BMSize.DrawBold({ 座標.x + Lph(40) , 座標.y + Lph(41) }, Color::White, Color::Black, スキル->名前);//スキル名

			MFont::BSSize.DrawBold({ 座標.x + Lph(42) , 座標.y + Lph(43) }, Color::White, Color::Black, スキル->説明);//説明文

			help_csv_page = page_buf;
		}

	};
}