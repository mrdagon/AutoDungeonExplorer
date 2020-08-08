//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*装備品、アイテム*/
	class Item
	{
	private:
	public:
		static std::vector<Item> data;

		ID_Item ID = 0;
		std::string 名前;
		std::string 説明;

		bool isレア = false;
		int Lv;
		int 品質 = 0;
		double 経験値 = 0;

		ItemType 種類;
		ItemImageType 見た目;

		PassiveSkill* Pスキル[2] = { nullptr };//未実装

		//攻撃力等のステータス、追加されるスキル等
		EnumArray<int, StatusType> ステ;

		Item(int id,std::string 名前,std::string 説明,ItemImageType 見た目)
		{
			this->ID = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->見た目 = 見た目;
		}

		Item(int id)
		{
			this->ID = id;
			種類 = (ItemType)Rand::Get((int)ItemType::COUNT - 1);
			見た目 = (ItemImageType)種類;
		}

		void Set( int ランク , ItemType 種類 ,int スキルa,int スキルb, int 追加Hp, int 追加Str, int 追加Dex, int 追加Int, int 物防 , int 魔防, int 命中 ,int 回避, int 品質)
		{
			this->Lv = ランク;
			this->種類 = 種類;
			this->ステ[StatusType::Hp] = 追加Hp;
			this->ステ[StatusType::Str] = 追加Str;
			this->ステ[StatusType::Int] = 追加Int;
			this->ステ[StatusType::Dex] = 追加Dex;
			this->ステ[StatusType::命中] = 命中;
			this->ステ[StatusType::回避] = 回避;

			this->ステ[StatusType::物防] = 物防;
			this->ステ[StatusType::魔防] = 魔防;
		}
	};

	void LoadItem()
	{
		//鍛冶：剣、斧、重鎧
		//木工：槍、弓、盾
		//裁縫：ローブ、軽鎧
		//錬金：魔杖、回復

		//でメインハンド７種、防具３種をとりあえず実装。

		//・武器
		//剣　：　前。STRのみ上昇。CD短め、先頭対象。スキルは低CD単体ダメージ。
		//斧　：　前。STRとHPが上昇。CD長、高威力低命中、先頭対象。スキルは長CD防御無視ダメージ。
		//槍　：　前中。DEXとHPが上昇。CD普通。１～３列からランダム。スキルは前２体にダメージ。
		//弓　：　中後。DEXのみ上昇。CD普通。ランダム対象。スキルは一番弱ってる的にダメージ。
		//盾　：　前。HPとガード上昇。CD普通、低威力、先頭対象。スキルは挑発してターゲットを取る。
		//魔　：　後。INTのみ上昇。CD長、高威力高命中。先頭対象。スキルは全体ダメージ。
		//神　：　後。INTのみ上昇。CD普通、低威力、先頭対象。スキルは一番HP減少率が低い味方を単体回復。


		//・防具
		//重鎧：　HPが大きく上昇、防御も上昇
		//軽鎧：　HPそこそこ、回避が少し上昇。
		//ローブ：　HP少し、INTが上昇。

		Game::対応レシピ[ItemType::剣] = CraftType::鍛造;
		Game::対応レシピ[ItemType::斧] = CraftType::鍛造;//?
		Game::対応レシピ[ItemType::盾] = CraftType::木工;
		Game::対応レシピ[ItemType::槌] = CraftType::木工;//
		Game::対応レシピ[ItemType::刺剣] = CraftType::鍛造;
		Game::対応レシピ[ItemType::槍] = CraftType::木工;
		Game::対応レシピ[ItemType::弓] = CraftType::木工;
		Game::対応レシピ[ItemType::銃] = CraftType::魔術;
		Game::対応レシピ[ItemType::魔杖] = CraftType::魔術;
		Game::対応レシピ[ItemType::骨杖] = CraftType::魔術;
		Game::対応レシピ[ItemType::神杖] = CraftType::魔術;
		Game::対応レシピ[ItemType::祝杖] = CraftType::魔術;
		Game::対応レシピ[ItemType::重鎧] = CraftType::鍛造;
		Game::対応レシピ[ItemType::力鎧] = CraftType::鍛造;
		Game::対応レシピ[ItemType::軽鎧] = CraftType::裁縫;
		Game::対応レシピ[ItemType::技鎧] = CraftType::裁縫;
		Game::対応レシピ[ItemType::隠鎧] = CraftType::裁縫;
		Game::対応レシピ[ItemType::知鎧] = CraftType::裁縫;

		//空き
		Item::data.emplace_back(0, "---", "空き", ItemImageType::アクセサリ);
		Item::data[0].Set(0, ItemType::すべて, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0);

		std::string name;

		name = "鉄の斧"; Item::data.emplace_back(1 , name , "STR武器", ItemImageType::鉄の斧);
		Item::data[1].Set(1, ItemType::斧, 3, 4, 0, 6, 0, 0, 0, 0, 0, 0, 0);

		name = "鉄の剣"; Item::data.emplace_back(2, name , "STR武器", ItemImageType::鉄の剣);
		Item::data[2].Set(1, ItemType::剣, 1, 2, 0, 4, 2, 0, 0, 0, 0, 0, 0);

		name = "木の弓"; Item::data.emplace_back(3, name , "DEX武器", ItemImageType::木の弓);
		Item::data[3].Set(1, ItemType::弓, 5, 6, 0, 0, 4, 0, 0, 0, 5, 0, 0);

		name = "鉄の盾"; Item::data.emplace_back(4, name , "VIT武器", ItemImageType::鉄の盾);
		Item::data[4].Set(1, ItemType::盾, 7, 8,10, 2, 0, 0, 5, 5, 0, 0, 0);
	
		name = "スタッフ"; Item::data.emplace_back(5, name , "STR/INT武器", ItemImageType::スタッフ);
		Item::data[5].Set(1, ItemType::神杖, 11, 12, 0, 1, 0, 4, 0, 0, 0, 0, 0);

		name = "ワンド"; Item::data.emplace_back(6, name , "INT武器", ItemImageType::ワンド);
		Item::data[6].Set(1, ItemType::魔杖, 9, 10, 0, 0, 0, 6, 0, 0, 0, 0, 0);
		
		name = "鉄の鎧"; Item::data.emplace_back(7, name , "HP系防具", ItemImageType::鉄の鎧);
		Item::data[7].Set(1, ItemType::重鎧, 0, 0, 20, 0, 0, 0, 5, 5, 0, 0, 0);
		
		name = "鎖帷子"; Item::data.emplace_back(8, name , "回避系防具", ItemImageType::鎖帷子);
		Item::data[8].Set(1, ItemType::軽鎧, 0, 0, 12, 0, 0, 0, 0, 0, 5, 5, 0);

		name = "ローブ"; Item::data.emplace_back(9, name , "INT系防具", ItemImageType::皮のローブ);
		Item::data[9].Set(1, ItemType::隠鎧, 0, 0, 8, 0, 0, 2, 0, 5, 0, 0, 0);


	}

	std::vector<Item> Item::data;
}