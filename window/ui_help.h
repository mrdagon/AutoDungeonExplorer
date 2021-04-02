//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class UIHelp
	{
	private:
		UIHelp();
		//装備、探検者、モンスターで使い回す
		static void ASkillChild(ActiveSkill* Aスキル)
		{}

		static void PSkillChild(PassiveSkill* Pスキル)
		{}


		static void DrawFrame(int x , int y , int w , int h)
		{
			//マウス位置とウィンドウサイズから、上下左右どちらの方向にウィンドウ出すか計算

			//カメラ座標を計算
		}

		template<class TLayout>
		static void DrawFrame(TLayout type)
		{
			auto& it = Layout::Data(type);
			DrawFrame( it.x , it.y , it.w , it.h );
		}

	public:
		//テキストのみのヘルプ
		static void Text(std::string& テキスト)
		{
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