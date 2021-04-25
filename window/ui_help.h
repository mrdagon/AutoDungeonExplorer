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

		//装備、モンスターで簡易表示する用
		static void ASkillChild(ActiveSkill* Aスキル)
		{
			//アイコン
			//名前
			//クールタイム
			//効果
		}

		static void PSkillChild(PassiveSkill* Pスキル)
		{
			//アイコン
			//名前
			//発動条件
			//効果
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

			Design::Blue.Draw(UIType::明ボタン, pt.x, pt.y, w, h);

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

			it.x += 4;
			it.y += 4;

			MFont::L->Draw( it , Design::暗字, *テキスト);
		}

		//●特殊なヘルプ
		//スキル習得画面
		static void ASkill(ActiveSkill* Aスキル , int Lv = 0)
		{
			auto pt = DrawFrame(LHSkill::Aヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "Aスキル説明");

			//スキルアイコン
			//スキル名
			//スキル説明
			//Lv補正、最大Lvボーナス
			//クールタイム
			//隊列
		}

		//スキル習得画面
		static void PSkill(PassiveSkill* Pスキル , int Lv = 0)
		{
			auto pt = DrawFrame(LHSkill::Pヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "Pスキル");

			//スキルアイコン
			//スキル名
			//スキル説明
			//Lv補正、最大Lvボーナス
			//発動条件
		}

		//パーティウィンドウ、ダンジョン一覧から
		static void Dungeon(Dungeon* ダンジョン)
		{
			auto pt = DrawFrame(LDungeon::ヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "ダンジョン");

			//フロア名
			//フロア説明
			//探索率状況
			//階段位置、ボス位置
			//雑魚
			//ボス
			//財宝
		}

		//ダンジョン一覧から
		static void Monster(MonsterClass* 種族, int Lv)
		{
			auto pt = DrawFrame(LHMonster::ヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "モンスター");

			//見た目
			//名前
			//素材種
			//ボスドロップ
			//ボス表示

			//基礎ステータス
			//アクティブスキル
			//パッシブスキル
		}

		//装備品、性能と必要素材
		static void Item(Item* 装備 , bool isレシピ表示)
		{
			auto pt = DrawFrame(LItem::ヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "アイテム");

			//アイコン
			//名前
			//説明
			//ステータス上昇量
			//パッシブ効果

			//レシピ
		}

		//パーティメンバー、控えメンバー
		static void Explorer(Explorer* 探検者)
		{
			auto pt = DrawFrame(LHExplorer::ヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "探索者");

			//ドット絵
			//名前
			//経験値バー
			//Lv
			//装備
			//アクセサリー
			//装備Aスキル
			//習得キースキル
			//習得PスキルとLv
		}

		//クエスト詳細
		static void Management(Management* 投資プラン)
		{
			auto pt = DrawFrame(LManagement::ヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "投資プラン");

			//アイコン
			//名前
			//説明
			//消費資金
			//現在レベル
			//投資後レベル
			//投資後効果
		}

		//クエスト詳細
		static void Quest(Quest* クエスト)
		{
			auto pt = DrawFrame(LHSkill::Pヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "クエスト");

			//アイコン
			//名前
			//依頼者ドット
			//依頼者名前
			//説明
			//受注状態
			//説明 報酬
			//受注条件
		}

		//今回の探索での被ダメージ、与ダメージ、回復量など表示
		static void Party(Guild::Party* パーティ)
		{
			auto pt = DrawFrame(LHSkill::Pヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "パーティ記録");

			//メンバードット
			//与ダメージ
			//被ダメージ
			//味方回復
			//被弾回数
			//行動回数
		}

		//素材名、系統、ランク、値段、個数
		static void Material(Material* 素材)
		{
			auto pt = DrawFrame(LMaterial::ヘルプ枠);
			MFont::L->Draw(pt, Design::暗字, "素材");

			//アイコン
			//Lv
			//名前
			//説明
			//価格
			//所持数
			//必要とするメンバーと個数
		}

	};
}