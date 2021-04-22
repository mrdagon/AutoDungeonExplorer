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

		//装備、探検者、モンスターで使い回す
		static void ASkillChild(ActiveSkill* Aスキル)
		{}

		static void PSkillChild(PassiveSkill* Pスキル)
		{}


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

			Design::No1->Draw(UIType::明ボタン, pt.x, pt.y, w, h);

			return pt;
		}

		template<class TLayout>
		static Point DrawFrame(TLayout type)
		{
			auto& it = Layout::Data(type);
			return DrawFrame(  it.w , it.h );
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
		static void ASkill(ActiveSkill* Aスキル)
		{

		}

		//スキル習得画面
		static void PSkill(PassiveSkill* Pスキル)
		{

		}

		//パーティウィンドウ、ダンジョン一覧から
		static void Dungeon(Dungeon* ダンジョン)
		{

		}

		//ダンジョン一覧から
		static void Monster(MonsterClass* 種族, int Lv)
		{

		}

		//装備品、性能と
		static void Equip(Item* 装備 , bool isレシピ表示)
		{

		}

		//パーティメンバー、控えメンバー
		static void Explorer(Explorer* 探検者)
		{

		}

		//クエスト詳細
		static void Quest(Quest* クエスト)
		{

		}

		//被ダメージ、与ダメージ、回復量など表示
		static void Party(Guild::Party* パーティ)
		{

		}

		//素材名、系統、ランク、値段、個数
		static void Material(Material 素材)
		{

		}

	};
}