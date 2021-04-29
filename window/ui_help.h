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
		static void ASkillChild(ActiveSkill* Aスキル)
		{
			auto L1 = LData(LHSkill::Cアイコン);
			auto L2 = LData(LHSkill::C名前);
			auto L3 = LData(LHSkill::ACクールタイム);
			auto L4 = LData(LHSkill::AC説明);

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			Aスキル->image->Draw(L1.GetPos());

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字, Aスキル->名前);

			//クールタイム
			Design::Help->Draw(UIType::丸フレーム, L3);
			Aスキル->クールタイム;
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字, Aスキル->クールタイム);

			//効果
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字, Aスキル->説明);

		}

		//装備、探索者、モンスターの簡易表示用
		static void PSkillChild(PassiveSkill* Pスキル)
		{
			auto L1 = LData(LHSkill::Cアイコン);
			auto L2 = LData(LHSkill::C名前);
			auto L3 = LData(LHSkill::PCタイミング);
			auto L4 = LData(LHSkill::PC説明);

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			Pスキル->image->Draw(L1.GetPos());

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字, { Pスキル->名前 });


			//発動タイミング
			Design::Help->Draw(UIType::丸フレーム, L3);
			//Pスキル->タイミング;
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字, { (int)Pスキル->タイミング });

			//効果
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字, { Pスキル->説明 } );
		}


		static Point DrawFrame( int w , int h)
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

			Design::Help->Draw(UIType::明ボタン, pt.x, pt.y, w, h);

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
			MFont::L->Draw({ 0,0 }, Design::暗字, { "Aスキル説明" });

			//スキルアイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			Aスキル->image->Draw(L1.GetPos());;

			//スキル名
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ Aスキル->名前 });

			//スキル説明
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ Aスキル->説明 });

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
			MFont::L->Draw({0,0}, Design::暗字, { "Pスキル説明" });

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			Pスキル->image->Draw(L1.GetPos());;

			//スキル名
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ Pスキル->名前 });

			//スキル説明
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ Pスキル->説明 });

			//発動条件
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ (int)Pスキル->タイミング });

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
			MFont::L->Draw({ 0,0 }, Design::暗字, { "ダンジョン" });

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			迷宮->image->Draw(L1.GetPos());;

			//フロア名
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 迷宮->名前 });
			
			//フロア説明
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ 迷宮->説明 });

			//探索率状況
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ (int)迷宮->探索率 , "%"});

			//階段位置 ボス位置マーカー

			//雑魚 or ボス
			for (int i = 0 ; i < 迷宮->雑魚モンスター.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L5);
				MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ "Lv ?"});
			}

			//ボス
			for (int i = 0; i < 迷宮->ボスモンスター.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L5);
				MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ "Lv ?"});
			}

			//財宝
			for (int i = 0; i < 迷宮->財宝.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L6);
				迷宮->財宝[i]->image->Draw(L6.GetPos());
				MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ 迷宮->財宝[i]->名前});
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

			auto pt = DrawFrame(LHMonster::ヘルプ枠);
			MFont::L->Draw({ 0,0 }, Design::暗字, "モンスター");

			//ドット絵
			Design::Help->Draw(UIType::丸フレーム, L1);
			魔物->image[0][0]->Draw(L1.GetPos());

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 魔物->名前 });

			//素材種 - アイコンのみ
			Design::Help->Draw(UIType::丸フレーム, L3);
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
			Design::Help->Draw(UIType::丸フレーム, L6);
			MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ "ステータス" });

			//アクティブスキル
			for (int i = 0; i < 魔物->Aスキル.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L7);
				MFont::L->DrawRotate(L7.GetPos(), 1, 0, Design::暗字,{ "Aスキル"});
			}

			//パッシブスキル
			for (int i = 0; i < 魔物->Pスキル.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L8);
				MFont::L->DrawRotate(L8.GetPos(), 1, 0, Design::暗字,{ "Pスキル"});
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

			auto pt = DrawFrame(LItem::ヘルプ枠);
			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			装備->image->Draw(L1.GetPos());;

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 装備->名前 });

			//説明
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ 装備->説明 });

			//ステータス上昇量
			for (int i = 0; i < 装備->ステ.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L4);
				MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ "ステータス"});
			}

			//パッシブ効果
			Design::Help->Draw(UIType::丸フレーム, L5);
			PSkillChild(装備->Pスキル[0]);

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

			auto pt = DrawFrame(LHExplorer::ヘルプ枠);
			MFont::L->Draw({ 0,0 }, Design::暗字, "探索者");

			//ドット絵
			Design::Help->Draw(UIType::丸フレーム, L1);
			探索者->image[0][1]->Draw(L1.GetPos());;

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 探索者->名前 });

			//経験値バー
			Design::Help->Draw(UIType::丸フレーム, L3);			;
			MFont::L->DrawBold(L3.GetPos(), Design::暗字, Design::明字,{ (int)探索者->Get経験値率() , "%"} , true);

			//Lv
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{"Lv",探索者->Lv });

			//装備 - アクセサリー
			for (int i = 0; i < 3; i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L5);
				MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字, { 探索者->装備[i]->名前 });
			}

			//装備Aスキル
			for (int i = 0; i < CV::最大Aスキル数; i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L6);
				MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ 探索者->装備Aスキル通常[i]->名前 });
			}

			//習得キースキル(未実装)
			Design::Help->Draw(UIType::丸フレーム, L7);
			MFont::L->DrawRotate(L7.GetPos(), 1, 0, Design::暗字, { "キースキル"});

			//習得PスキルとLv
			for (int i = 0; i < 探索者->職業->習得Pスキル.size(); i++)
			{
				Design::Help->Draw(UIType::丸フレーム, L9);
				//探索者->習得PスキルLv;
				MFont::L->DrawRotate(L9.GetPos(), 1, 0, Design::暗字,{ "Pスキル名"});
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
			MFont::L->Draw({ 0,0 }, Design::暗字, "投資プラン");

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			投資->image->Draw(L1.GetPos());;

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 投資->名前 });


			//説明
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ 投資->説明 });

			//消費資金
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ 投資->消費資金 });

			//現在レベル
			Design::Help->Draw(UIType::丸フレーム, L5);
			MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ 投資->投資Lv });

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

			auto pt = DrawFrame(LHSkill::Pヘルプ枠);
			MFont::L->Draw({ 0,0 }, Design::暗字, "クエスト");

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			依頼->image->Draw(L1.GetPos());;

			//名前
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 依頼->名前 });

			//依頼者ドット
			Design::Help->Draw(UIType::丸フレーム, L3);
			依頼->依頼人image;

			//依頼者名前(未実装)
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ "" });

			//説明
			Design::Help->Draw(UIType::丸フレーム, L5);
			MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ 依頼->説明 });

			//受注状態
			MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ "受注状態" });

			//説明 報酬(未実装)
			Design::Help->Draw(UIType::丸フレーム, L7);
			MFont::L->DrawRotate(L7.GetPos(), 1, 0, Design::暗字,{ "報酬！"});
			
			//受注条件(未実装)
			Design::Help->Draw(UIType::丸フレーム, L8);
			MFont::L->DrawRotate(L8.GetPos(), 1, 0, Design::暗字,{ "受注条件"});
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

			auto pt = DrawFrame(LMaterial::ヘルプ枠);
			MFont::L->Draw({ 0,0 }, Design::暗字, "素材");

			//アイコン
			Design::Help->Draw(UIType::丸フレーム, L1);
			素材->image->Draw(L1.GetPos());;

			//ランク
			Design::Help->Draw(UIType::丸フレーム, L2);
			MFont::L->DrawRotate(L2.GetPos(), 1, 0, Design::暗字,{ 素材->ランク });

			//名前
			Design::Help->Draw(UIType::丸フレーム, L3);
			MFont::L->DrawRotate(L3.GetPos(), 1, 0, Design::暗字,{ 素材->名前 });

			//説明
			Design::Help->Draw(UIType::丸フレーム, L4);
			MFont::L->DrawRotate(L4.GetPos(), 1, 0, Design::暗字,{ 素材->説明 });

			//価格
			Design::Help->Draw(UIType::丸フレーム, L5);
			MFont::L->DrawRotate(L5.GetPos(), 1, 0, Design::暗字,{ 素材->価格 });

			//所持数
			Design::Help->Draw(UIType::丸フレーム, L6);
			MFont::L->DrawRotate(L6.GetPos(), 1, 0, Design::暗字,{ "所持数" });

			//必要とするメンバーと個数
		}

	};
}