//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <iostream>

namespace SDX_ADE
{
	using namespace SDX;

	class UIHelp
	{
	private:
		UIHelp()
		{}

		//探索者、モンスターの簡易表示用
		static void ASkillChild(ActiveSkill* Aスキル , int xdif , int ydif )
		{
			auto L1 = LData(LHSkill::Cアイコン);
			auto L2 = LData(LHSkill::C名前);
			auto L3 = LData(LHSkill::ACクールタイム);
			auto L4 = LData(LHSkill::AC説明);

			//アイコン
			Design::Help->DrawRound(L4.x + xdif , L4.y + ydif , L4.w , L4.h );
			Aスキル->image->Draw(L1.GetSubPos(xdif, ydif));

			//名前
			MFont::L->DrawRotate(L2.GetSubPos(xdif, ydif), 1, 0, Design::暗字, Aスキル->名前);

			//クールタイム
			MFont::L->DrawRotate(L3.GetSubPos(xdif, ydif), 1, 0, Design::暗字, Aスキル->クールタイム);

			//効果
			MFont::L->DrawRotate(L4.GetSubPos(xdif, ydif), 1, 0, Design::暗字, Aスキル->説明);

		}

		//装備、探索者、モンスターの簡易表示用
		static void PSkillChild(PassiveSkill* Pスキル , int xdif, int ydif)
		{
			auto L1 = LData(LHSkill::Cアイコン);
			auto L2 = LData(LHSkill::C名前);
			auto L3 = LData(LHSkill::PCタイミング);
			auto L4 = LData(LHSkill::PC説明);

			//効果 説明
			Design::Help->DrawBack(L4.x + xdif, L4.y + ydif, L4.w, L4.h , Design::Help->ハイライト);
			MFont::L->DrawRotate(L4.GetSubPos(xdif, ydif), 1, 0, Design::暗字, { Pスキル->説明 });

			//アイコン
			//Design::Help->DrawRound(L1.x + xdif, L1.y + ydif, L1.w, L1.h);
			Pスキル->image->Draw(L1.GetSubPos(xdif,ydif));

			//名前
			MFont::L->DrawRotate(L2.GetSubPos(xdif, ydif), 1, 0, Design::暗字, { Pスキル->名前 });

			//発動タイミング - 説明に付与
			//MFont::L->DrawRotate(L3.GetSubPos(xdif, ydif), 1, 0, Design::暗字, { (int)Pスキル->タイミング });
		}


		static Point DrawFrame( int w , int h )
		{
			Point pt = Input::mouse.GetPoint();

			//マウス位置とウィンドウサイズから、上下左右どちらの方向にウィンドウ出すか計算
			if (pt.x + w > Config::解像度W)
			{
				pt.x -= w;
			}
			if (pt.y + h > Config::解像度H)
			{
				pt.y -= h;
			}

			Design::Help->Draw(UIType::平ボタン, pt.x, pt.y, w, h);

			//カメラオフセットをセット
			Camera::Get()->position.x = -pt.x;
			Camera::Get()->position.y = -pt.y;

			return pt;
		}

		template<class TLayout>
		static Point DrawFrame(TLayout type)
		{
			auto& it = Layout::Data(type);
			return DrawFrame(  it.w , it.h );
		}

		template<class T>
		static Layout& LData(T レイアウト)
		{
			return Layout::Data(レイアウト);
		}

	public:
		//テキストのみのヘルプ
		static void Text(std::string* テキスト)
		{
			int n = std::count(テキスト->begin(), テキスト->end(), '\n') + 1;

			auto it = DrawFrame(MFont::L->GetDrawStringWidth(*テキスト) + 8, n * MFont::L->GetHeight() + 8 );

			MFont::L->Draw({4,4}, Design::暗字, *テキスト);
		}

		//●特殊なヘルプ
		//スキル習得画面
		static void ASkill(ActiveSkill* Aスキル , int Lv = 0)
		{
			auto L1 = LData(LHSkill::Aアイコン);
			auto L2 = LData(LHSkill::A名前);
			auto L3 = LData(LHSkill::A説明);
			auto L4 = LData(LHSkill::Aクールタイム);
			auto L5 = LData(LHSkill::A隊列);

			auto pt = DrawFrame(LHSkill::Aヘルプ枠);

			//スキルアイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			Aスキル->image->Draw(L1.GetPos());;

			//スキル名
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->Draw(L2.GetPos(), Design::暗字,{ Aスキル->名前 });

			//スキル説明
			Design::Help->Draw(UIType::グループ明, L3);
			MFont::L->Draw(L3.GetPos(), Design::暗字,{ Aスキル->説明 });

			//Lv補正、最大Lvボーナス(とりあえず非表示)

			//クールタイム
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ Aスキル->クールタイム });

			//隊列
			Design::Help->Draw(UIType::丸フレーム, L5);
			MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ (int)Aスキル->適正隊列 });
		}

		//スキル習得画面
		static void PSkill(PassiveSkill* Pスキル , int Lv = 0)
		{
			auto L1 = LData(LHSkill::Pアイコン);
			auto L2 = LData(LHSkill::P名前);
			auto L3 = LData(LHSkill::P説明);
			auto L4 = LData(LHSkill::Pタイミング);

			auto pt = DrawFrame(LHSkill::Pヘルプ枠);

			if (Pスキル == nullptr)
			{
				return;
			}

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			Pスキル->image->Draw(L1.GetPos());;

			//スキル名
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ Pスキル->名前 });

			//スキル説明
			Design::Help->Draw(UIType::グループ明, L3);
			MFont::L->Draw(L3.GetPos(), Design::暗字,{ Pスキル->説明 });

			//発動条件
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(),1,0, Design::暗字,{ (int)Pスキル->タイミング });

			//Lv補正、最大Lvボーナス(とりあえず非表示)
		}

		//パーティウィンドウ、ダンジョン一覧から
		static void Dungeon(Dungeon* 迷宮)
		{
			auto L1 = LData(LDungeon::Hアイコン);
			auto L2 = LData(LDungeon::H名前);
			auto L3 = LData(LDungeon::H説明);
			auto L4 = LData(LDungeon::H探索率);
			auto L5 = LData(LDungeon::Hモンスター);
			auto L6 = LData(LDungeon::H財宝);

			auto pt = DrawFrame(LDungeon::ヘルプ枠);

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			迷宮->image->Draw(L1.GetPos());;

			//フロア名
			//Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 迷宮->名前 });
			
			//フロア説明 - テキスト作成するの大変なのでやっぱり削除
			//Design::Help->Draw(UIType::グループ明, L3);
			//MFont::L->Draw(L3.GetPos(), Design::暗字,{ 迷宮->説明 });

			//探索率状況
			//Design::Help->Draw(UIType::丸フレーム, L4);
			//MFont::L->DrawBoldRotate(L4.GetPos(), 1, 0, Design::暗字 , Design::明字 , { (int)迷宮->探索率 , "%"});
			//Design::Help->DrawGauge(L4.x, L4.y, L4.w, L4.h, 迷宮->探索率 + 0.5 );

			//階段位置 ボス位置マーカー、探索率は被るので出さない？

			//雑魚 or ボス
			if (迷宮->isUIボス表示)
			{
				for (int i = 0; i < 迷宮->ボスモンスター.size(); i++)
				{
					Design::Help->Draw(UIType::丸フレーム, L5);
					迷宮->ボスモンスター[i]->image[0][1]->DrawRotate(L5.GetPos(i), 1, 0);
					MFont::L->DrawRotate(L5.GetPos(i), 1, 0, Design::暗字, { "Lv ?" });
				}
			} else {
				for (int i = 0; i < 迷宮->雑魚モンスター.size(); i++)
				{
					Design::Help->Draw(UIType::丸フレーム, L5);
					迷宮->雑魚モンスター[i]->image[0][1]->DrawRotate(L5.GetPos(i), 1, 0);
					MFont::L->DrawRotate(L5.GetPos(i), 1, 0, Design::暗字, { "Lv ?" });
				}
			}

			//財宝
			for (int i = 0; i < 迷宮->財宝.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L6);
				迷宮->財宝[i]->image->Draw(L6.GetPos(i));
				MFont::L->DrawRotate(L6.GetPos(i), 1, 0, Design::暗字,{ 迷宮->財宝[i]->名前});
			}
		}

		//ダンジョン一覧から
		static void Monster(MonsterClass* 魔物, int Lv)
		{
			auto L1 = LData(LHMonster::ドット);
			auto L2 = LData(LHMonster::名前);
			auto L3 = LData(LHMonster::素材);
			auto L4 = LData(LHMonster::ボスマーク);
			auto L5 = LData(LHMonster::ボスドロップ);
			auto L6 = LData(LHMonster::基礎ステータス);
			auto L7 = LData(LHMonster::アクティブスキル);
			auto L8 = LData(LHMonster::パッシブスキル);
			auto L9 = LData(LHMonster::Lv);

			auto pt = DrawFrame(LHMonster::ヘルプ枠);

			//ドット絵
			Design::Help->Draw(UIType::丸フレーム, L1);
			魔物->image[0][0]->DrawRotate(L1.GetPos(),2,0);

			//Lv
			MFont::L->DrawRotate(L9.GetPos(), 1, 0, Design::暗字, { "Lv " , Lv});


			//名前
			MFont::L->DrawRotate(L2.GetSubPos(L1.w/2 , L1.h/2), 1, 0, Design::暗字,{ 魔物->名前 });

			//素材種 - アイコンのみ

			//魔物->素材種

			if (魔物->isボス)
			{
				//ボスドロップ
				Design::Help->Draw(UIType::丸フレーム, L5);
				MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ 魔物->ボスドロップ });

				//Boss表示
				MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字, { "Boss" });
			}

			//基礎ステータス
			for (int i = 0, cnt = 0; i < 魔物->ステ.size(); i++)
			{
				StatusType st = (StatusType)i;
				switch (st)
				{
				case StatusType::力:
				case StatusType::技:
				case StatusType::知:
					if (魔物->ステ[st] == 0) { continue; }
					break;
				case StatusType::会心:
					continue;
				}
				Design::Help->Draw(UIType::丸フレーム, L6, cnt);
				MFont::L->DrawRotate(L6.GetSubPos(L6.h + 4, L6.h / 2, cnt), 1, 0, Design::暗字, { TX::ステータス[st] });
				MFont::L->DrawRotate(L6.GetSubPos(L6.w - L6.h, L6.h / 2, cnt), 1, 0, Design::暗字, { (int)魔物->ステ[st], true });
				cnt++;
			}

			//アクティブスキル
			for (int i = 0; i < 魔物->Aスキル.size(); i++)
			{
				auto pos = L7.GetPos(i);
				ASkillChild(魔物->Aスキル[i], pos.x, pos.y);
			}

			//パッシブスキル
			for (int i = 0; i < 魔物->Pスキル.size() && i < 4; i++)
			{
				auto pos = L8.GetPos(i);
				PSkillChild(魔物->Pスキル[i], pos.x, pos.y);
			}
		}

		//装備品、性能と必要素材
		static void Item(Item* 装備 , bool is武器防具)
		{
			auto L1 = LData(LItem::Hアイコン);
			auto L2 = LData(LItem::H名前);
			auto L3 = LData(LItem::H説明);
			auto L4 = LData(LItem::Hステータス);
			auto L5 = LData(LItem::Hパッシブ);
			auto L6 = LData(LItem::Hレシピ);

			if (is武器防具 == true)
			{
				Layout::Data(LItem::ヘルプ枠).h += Layout::Data(LItem::ヘルプ枠).並べy;
			}


			auto pt = DrawFrame(LItem::ヘルプ枠);
			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			装備->image->Draw(L1.GetPos());;

			//名前
			//Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 装備->名前 });

			//説明
			Design::Help->Draw(UIType::グループ明, L3);
			MFont::L->Draw(L3.GetPos(), Design::暗字,{ 装備->説明 });

			//ステータス変化 - 初期化処理で、説明に付与する
			//for (int i = 0; i < 装備->ステ.size(); i++)
			//{
			//	Design::Help->Draw(UIType::丸フレーム, L4);
			//	MFont::L->DrawRotate(L4.GetPos(i), 1, 0, Design::暗字,{ "ステータス"});
			//}

			if (is武器防具 == false)
			{
				//アクセサリーはパッシブがある
				PSkillChild(装備->Pスキル[0], L5.x, L5.y);
				return;
			}

			Layout::Data(LItem::ヘルプ枠).h -= Layout::Data(LItem::ヘルプ枠).並べy;

			//レシピ
			for (int i = 0; i < 装備->レシピ.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L6);
				MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ "レシピ" });
			}
		}

		//パーティメンバー、控えメンバー
		static void Explorer(Explorer* 探索者)
		{
			auto L1 = LData(LHExplorer::ドット);
			auto L2 = LData(LHExplorer::名前);
			auto L3 = LData(LHExplorer::経験値バー);
			auto L4 = LData(LHExplorer::Lv);
			auto L5 = LData(LHExplorer::装備);
			auto L6 = LData(LHExplorer::Aスキル);
			auto L7 = LData(LHExplorer::習得キースキル);
			//auto L8 = LData(LHExplorer::習得Aスキル); 見せない
			auto L9 = LData(LHExplorer::習得Pスキル);
			auto L10 = LData(LHExplorer::職業);
			auto L11 = LData(LHExplorer::基礎ステータス);

			auto pt = DrawFrame(LHExplorer::ヘルプ枠);

			//ドット絵
			Design::Help->Draw(UIType::丸フレーム, L1);
			探索者->image[0][1]->DrawRotate(L1.GetPos(),2,0);;

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 探索者->名前 });

			//職業
			Design::Help->Draw(UIType::丸フレーム, L10);
			MFont::L->DrawRotate(L10.GetSubPos(L10.w/2,L10.h/2), 1, 0, Design::暗字, { 探索者->職業->名前 });

			//経験値バー いらない？
			//Design::Help->Draw(UIType::丸フレーム, L3);			;
			//MFont::L->DrawBold(L3.GetPos(), Design::暗字, Design::明字,{ (int)探索者->Get経験値率() , "%"} , true);

			//Lv
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{"Lv",探索者->Lv });

			//基礎ステータス
			for (int i = 0,cnt = 0; i < 探索者->基礎ステ.size(); i++)
			{
				StatusType st = (StatusType)i;
				switch (st)
				{
				case StatusType::力:
				case StatusType::技:
				case StatusType::知:
					if (探索者->基礎ステ[st] == 0) { continue; }
					break;
				case StatusType::会心:
					continue;
				}
				Design::Help->Draw(UIType::丸フレーム, L11, cnt);
				MFont::L->DrawRotate(L11.GetSubPos(L11.h + 4, L11.h / 2, cnt), 1, 0, Design::暗字, { TX::ステータス[st] });
				MFont::L->DrawRotate(L11.GetSubPos( L11.w - L11.h , L11.h / 2, cnt), 1, 0, Design::暗字, { (int)探索者->基礎ステ[st], true });
				cnt++;
			}
			//装備 - 武器 - 防具 - アクセサリー
			for (int i = 0; i < 3; i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L5 , i);
				探索者->装備[i]->image->DrawRotate(L5.GetSubPos(L5.h / 2, L5.h / 2,i), 1 ,0);
				MFont::L->DrawRotate(L5.GetSubPos(L5.w / 2 + 8, L5.h / 2,i),1,0, Design::暗字, { 探索者->装備[i]->名前 });
			}

			//装備Aスキル
			for (int i = 0; i < CV::最大Aスキル数; i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L6 , i);
				探索者->装備Aスキル通常[i]->image->DrawRotate(L6.GetSubPos(L6.h / 2, L6.h / 2 , i),1,0);
				MFont::L->DrawRotate(L6.GetSubPos(L6.w / 2 + 8, L6.h / 2, i) , 1 , 0 , Design::暗字,{ 探索者->装備Aスキル通常[i]->名前 });
			}

			//習得キースキル(未実装)
			Design::Help->Draw(UIType::丸フレーム, L7);
			MFont::L->DrawRotate(L7.GetSubPos(L7.w/2,L7.h/2), 1, 0, Design::暗字, { "キースキル"});

			//習得Aスキルは表示しない

			//習得PスキルとLv
			for (int i = 0; i < 探索者->職業->習得Pスキル.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L9 , i);
				//探索者->習得PスキルLv;
				探索者->職業->習得Pスキル[i]->image->DrawRotate(L9.GetSubPos(L9.h / 2, L9.h / 2, i), 1, 0);
				MFont::L->DrawRotate(L9.GetSubPos(L9.w/2 + 8, L9.h/2, i), 1, 0, Design::暗字,{ 探索者->職業->習得Pスキル[i]->名前 });
			}
		}

		//クエスト詳細
		static void Management(Management* 投資)
		{
			auto L1 = LData(LManagement::Hアイコン);
			auto L2 = LData(LManagement::H名前);
			auto L3 = LData(LManagement::H説明);
			auto L4 = LData(LManagement::H消費資金);
			auto L5 = LData(LManagement::HLv);

			auto pt = DrawFrame(LManagement::ヘルプ枠);

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			投資->image->Draw(L1.GetPos());;

			//名前
			//Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 投資->名前 });


			//説明
			Design::Help->Draw(UIType::グループ明, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ 投資->説明 });

			//消費資金
			//Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ 投資->消費資金 , "G" });

			//現在レベル
			//Design::Help->Draw(UIType::丸フレーム, L5);
			MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ "Lv" , 投資->投資Lv });

			//投資後レベル
			//投資後効果
		}

		//クエスト詳細
		static void Quest(Quest* 依頼)
		{
			auto L1 = LData(LQuest::Hアイコン);
			auto L2 = LData(LQuest::H名前);
			auto L3 = LData(LQuest::H依頼人);
			auto L4 = LData(LQuest::H依頼人名前);
			auto L5 = LData(LQuest::H説明);
			auto L6 = LData(LQuest::H受注状況);
			auto L7 = LData(LQuest::H報酬説明);
			auto L8 = LData(LQuest::H受注条件);

			auto pt = DrawFrame(LQuest::ヘルプ枠);

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			依頼->image->Draw(L1.GetPos());;

			//名前
			//Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 依頼->名前 });

			//説明
			Design::Help->Draw(UIType::グループ明, L5);
			MFont::L->Draw(L5.GetPos(), Design::暗字, { 依頼->説明 });

			//依頼者ドット
			//Design::Help->Draw(UIType::丸フレーム, L3);
			依頼->依頼人image->DrawRotate(L3.GetPos(),2,0);

			//依頼者名前(未実装)
			//Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ "依頼人の名前" });

			//受注状態
			MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ "状況" });

			//説明 報酬(未実装)
			//MFont::L->DrawRotate(L7.GetPos(), 1, 0, Design::暗字,{ "報酬説明（未実装）"});
			
			//受注条件(未実装)
			//MFont::L->DrawRotate(L8.GetPos(), 1, 0, Design::暗字,{ "受注条件（未実装）"});
		}

		//今回の探索での被ダメージ、与ダメージ、回復量など表示
		static void Party(Guild::Party* パーティ)
		{
			auto L1 = LData(LBattle::Hメンバー);
			auto L2 = LData(LBattle::H項目名);
			auto L3 = LData(LBattle::H数値);

			auto pt = DrawFrame(LBattle::ヘルプ枠);
			MFont::L->Draw({ 0,0 }, Design::暗字, "パーティ記録");

			//メンバードット
			for (int i = 0; i < CV::パーティ人数; i++)
			{
				パーティ->メンバー[i]->image[0][1]->Draw(L1.GetPos());;
				Design::Help->Draw(UIType::丸フレーム, L1);
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字,{ "名前" });
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字, { "与ダメ" });
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字, { "被ダメ" });
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字, { "回復" });
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字, { "被弾" });
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字, { "狙われ率" });
				MFont::L->DrawRotate(L1.GetPos(), 1, 0, Design::暗字, { "行動回数" });
			}


		}

		//素材名、系統、ランク、値段、個数
		static void Material(Material* 素材)
		{
			auto L1 = LData(LMaterial::Hアイコン);
			auto L2 = LData(LMaterial::Hランク);
			auto L3 = LData(LMaterial::H名前);
			auto L4 = LData(LMaterial::H説明);
			auto L5 = LData(LMaterial::H価格);
			auto L6 = LData(LMaterial::H所持数);
			auto L7 = LData(LMaterial::H必要メンバー);

			auto pt = DrawFrame(LMaterial::ヘルプ枠);

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			素材->image->Draw(L1.GetPos());;

			//ランク
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ "★ " , 素材->ランク });

			//名前
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ 素材->名前 });

			//説明 - 文章作るのが大変なので非表示
			//Design::Help->Draw(UIType::丸フレーム, L4);
			//MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ 素材->説明 });

			//価格
			Design::Help->Draw(UIType::丸フレーム, L5);
			MFont::L->Draw(L5.GetPos(), Design::暗字, { "価格 " , 素材->価格 , "G" } );

			//所持数
			Design::Help->Draw(UIType::丸フレーム, L6);
			MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ "所持数 x " , Guild::P->素材数[素材->ID] });

			//必要とするメンバーと個数
			Design::Help->Draw(UIType::丸フレーム, L7);
			MFont::L->DrawRotate(L7.GetPos(), 1, 0, Design::暗字, { "要求表示、未実装" });


		}

	};
}