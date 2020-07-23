//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*装備品、アイテム*/
	class Item
	{
	private:
	public:
		static std::vector<Item> data;

		int ID = 0;
		std::string 名前;
		std::string 説明;

		bool isレア = false;
		int Lv;
		int 品質 = 0;
		ItemType 種類;
		ItemImageType 見た目;
		ActiveSkill* Aスキル[2] = { nullptr };
		PassiveSkill* Pスキル[2] = { nullptr };//未実装

		int 値段 = 10000;

		//攻撃力等のステータス、追加されるスキル等
		int 追加Str, 追加Int, 追加Dex, 追加Hp = 0;

		EnumArray<int, DamageType> 防御;
		int 命中 = 0;
		int 回避 = 0;

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
			this->Aスキル[0] = &ActiveSkill::data[スキルa];
			this->Aスキル[1] = &ActiveSkill::data[スキルb];
			this->追加Hp = 追加Hp;
			this->追加Str = 追加Str;
			this->追加Int = 追加Int;
			this->追加Dex = 追加Dex;

			this->防御[DamageType::物理] = 物防;
			this->防御[DamageType::魔法] = 魔防;

			this->命中 = 命中;
			this->回避 = 回避;

			this->値段 = 5000 + (ランク - 1) * 2000;

			this->品質 = 品質;
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
		std::string num;
		int n;

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "鉄の斧"; Item::data.emplace_back(1 + a, name + num, "STR武器", ItemImageType::鉄の斧);
			Item::data[1 + a].Set(a + 1, ItemType::斧, 3, 4, 0, n * 2, 0, 0, 0, 0, 0, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "鉄の剣"; Item::data.emplace_back(1 + 4 * 1 + a, name + num, "STR武器", ItemImageType::鉄の剣);
			Item::data[1 + 4 * 1 + a].Set(a + 1, ItemType::剣, 1, 2, 0, n * 2, n, 0, 0, 0, 0, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "木の弓"; Item::data.emplace_back(1 + 4 * 2 + a, name + num, "DEX武器", ItemImageType::木の弓);
			Item::data[1 + 4 * 2 + a].Set(a + 1, ItemType::弓, 5, 6, 0, 0, n * 2, 0, 0, 0, 5, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "鉄の盾"; Item::data.emplace_back(1 + 4 * 3 + a, name + num, "VIT武器", ItemImageType::鉄の盾);
			Item::data[1 + 4 * 3 + a].Set(a + 1, ItemType::盾, 7, 8, n * 2, n / 2, 0, 0, 5, 5, 0, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "スタッフ"; Item::data.emplace_back(1 + 4 * 4 + a, name + num, "STR/INT武器", ItemImageType::スタッフ);
			Item::data[1 + 4 * 4 + a].Set(a + 1, ItemType::神杖, 11, 12, 0, n / 2, 0, n * 2, 0, 0, 0, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "ワンド"; Item::data.emplace_back(1 + 4 * 5 + a, name + num, "INT武器", ItemImageType::ワンド);
			Item::data[1 + 4 * 5 + a].Set(a + 1, ItemType::魔杖, 9, 10, 0, 0, 0, n * 3, 0, 0, 0, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "鉄の鎧"; Item::data.emplace_back(1 + 4 * 6 + a, name + num, "HP系防具", ItemImageType::鉄の鎧);
			Item::data[1 + 4 * 6 + a].Set(a+1, ItemType::重鎧, 0, 0, n * 5, 0, 0, 0, 5, 5, 0, 0, a);
		}

		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "鎖帷子"; Item::data.emplace_back(1 + 4 * 7 + a, name + num, "回避系防具", ItemImageType::鎖帷子);
			Item::data[1 + 4 * 7 + a].Set(a + 1, ItemType::軽鎧, 0, 0, n * 3, 0, 0, 0, 0, 0, 5, 5, a);
		}


		for (int a = 0; a < CV::最大装備ランク; a++)
		{
			num = (a == 0) ? "" : std::to_string(a + 1); n = 2 + a;
			name = "ローブ"; Item::data.emplace_back(1 + 4 * 8 + a, name + num, "INT系防具", ItemImageType::皮のローブ);
			Item::data[1 + 4 * 8 + a].Set(a + 1, ItemType::隠鎧, 0, 0, n * 2, 0, 0, n, 0, 5, 0, 0, a);
		}

	}

	std::vector<Item> Item::data;
}