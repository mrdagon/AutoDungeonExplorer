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

		int id = 0;
		std::string 名前;
		std::string 説明;

		bool isレア = false;
		int ランク;
		ItemType 種類;
		StatusType 依存ステータス;
		ItemImageType 見た目;
		int Aスキル[2];
		int Pスキル;

		int 必要製造力;
		int 値段 = 10000;

		//攻撃力等のステータス、追加されるスキル等
		double 追加Str, 追加Int, 追加Dex, 追加Vit, 追加Agi;

		double ブロック;
		double 命中;
		double 回避;

		Item(int id,std::string 名前,std::string 説明,ItemImageType 見た目)
		{
			this->id = id;
			this->名前 = 名前;
			this->説明 = 説明;
			this->見た目 = 見た目;
		}

		Item(int id)
		{
			this->id = id;
			種類 = (ItemType)Rand::Get((int)ItemType::COUNT - 1);
			見た目 = (ItemImageType)種類;
		}

		void Set( int ランク , ItemType 種類 , StatusType 依存ステータス,int スキルa,int スキルb, double 追加Str, double 追加Int, double 追加Dex, double 追加Vit, double 追加Agi)
		{
			this->ランク = ランク;
			this->種類 = 種類;
			this->依存ステータス = 依存ステータス;
			this->Aスキル[0] = スキルa;
			this->Aスキル[1] = スキルb;
			this->追加Str = 追加Str;
			this->追加Int = 追加Int;
			this->追加Dex = 追加Dex;
			this->追加Vit = 追加Vit;
			this->追加Agi = 追加Agi;
			必要製造力 = 10000 + ランク * 2000;
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
		//重鎧：　HPが大きく上昇。
		//軽鎧：　HPそこそこ、回避が少し上昇。
		//ローブ：　HP少し、INTとレジストが上昇。

		Game::対応レシピ[ItemType::剣] = CraftType::鍛造;
		Game::対応レシピ[ItemType::斧] = CraftType::鍛造;
		Game::対応レシピ[ItemType::盾] = CraftType::木工;
		Game::対応レシピ[ItemType::槌] = CraftType::木工;
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


		Item::data.emplace_back(0, "鉄の斧", "STR武器", ItemImageType::鉄の斧);
		Item::data.emplace_back(1, "鉄の剣", "STR武器", ItemImageType::鉄の剣);
		Item::data.emplace_back(2, "木の弓", "DEX武器", ItemImageType::木の弓);
		Item::data.emplace_back(3, "鉄の盾", "VIT武器", ItemImageType::鉄の盾);
		Item::data.emplace_back(4, "スタッフ", "STR/INT武器", ItemImageType::スタッフ);
		Item::data.emplace_back(5, "ワンド", "INT武器", ItemImageType::ワンド);
		Item::data.emplace_back(6, "鉄の鎧", "HP系防具", ItemImageType::鉄の鎧);
		Item::data.emplace_back(7, "鎖帷子", "隠密系防具", ItemImageType::鎖帷子);
		Item::data.emplace_back(8, "ローブ", "対魔系防具", ItemImageType::皮のローブ);

		Item::data[0].Set(1, ItemType::斧, StatusType::Str, 1, 0, 2, 0, 0, 2, 0);
		Item::data[1].Set(1,ItemType::剣,StatusType::Str ,1,0			,4,0,0,0,0);
		Item::data[2].Set(1, ItemType::弓, StatusType::Str, 2, 0, 0, 0, 4, 0, 0);
		Item::data[3].Set(1, ItemType::盾, StatusType::Str, 4, 0		,0,0,0,4,0);
		Item::data[4].Set(1, ItemType::神杖, StatusType::Str, 5, 0, 2, 2, 0, 0, 0);
		Item::data[5].Set(1, ItemType::魔杖, StatusType::Str, 3, 0	,0,4,0,0,0);
		Item::data[6].Set(1, ItemType::重鎧, StatusType::Str, 0, 0		,0,0,0,4,0);
		Item::data[7].Set(1, ItemType::軽鎧, StatusType::Str, 0, 0		,0,0,1,2,1);
		Item::data[8].Set(1, ItemType::隠鎧, StatusType::Str, 0, 0		,0,2,0,2,0);


		for (int a = 1; a < 5; a++)
		{
			std::string name;
			std::string num = std::to_string(a+1);
			int b = a + 1;

			name = "鉄の斧"; Item::data.emplace_back(0 + a * 9, name + num, "STR武器", ItemImageType::鉄の斧);
			name = "鉄の剣";Item::data.emplace_back(1 + a * 9, name + num, "STR武器", ItemImageType::鉄の剣);
			name = "木の弓"; Item::data.emplace_back(2 + a * 9, name + num, "DEX武器", ItemImageType::木の弓);
			name = "鉄の盾"; Item::data.emplace_back(3 + a * 9, name + num, "VIT武器", ItemImageType::鉄の盾);
			name = "スタッフ"; Item::data.emplace_back(4 + a * 9, name + num, "STR/INT武器", ItemImageType::スタッフ);
			name = "ワンド"; Item::data.emplace_back(5 + a * 9, name + num, "INT武器", ItemImageType::ワンド);
			name = "鉄の鎧"; Item::data.emplace_back(6 + a * 9, name + num, "HP系防具", ItemImageType::鉄の鎧);
			name = "鎖帷子"; Item::data.emplace_back(7 + a * 9, name + num, "隠密系防具", ItemImageType::鎖帷子);
			name = "ローブ"; Item::data.emplace_back(8 + a * 9, name + num, "対魔系防具", ItemImageType::皮のローブ);

			Item::data[0 + a * 9].Set(a+1, ItemType::斧, StatusType::Str, 1, 0, 2 * b, 0, 0, 2 * b, 0);
			Item::data[1 + a * 9].Set(a+1, ItemType::剣, StatusType::Str, 1, 0, 4 * b, 0, 0, 0, 0);
			Item::data[2 + a * 9].Set(a+1, ItemType::弓, StatusType::Str, 2, 0, 0, 0, 4 * b, 0, 0);
			Item::data[3 + a * 9].Set(a + 1, ItemType::盾, StatusType::Str, 4, 0, 0, 0, 0, 4 * b, 0);
			Item::data[4 + a * 9].Set(a + 1, ItemType::神杖, StatusType::Str, 5, 0, 2 * b, 2 * b, 0, 0, 0);
			Item::data[5 + a * 9].Set(a + 1, ItemType::魔杖, StatusType::Str, 3, 0, 0, 4 * b, 0, 0, 0);
			Item::data[6 + a * 9].Set(a + 1, ItemType::重鎧, StatusType::Str, 0, 0, 0, 0, 0, 4 * b, 0);
			Item::data[7 + a * 9].Set(a + 1, ItemType::軽鎧, StatusType::Str, 0, 0, 0, 0, 1 * b, 2 * b, 1 * b);
			Item::data[8 + a * 9].Set(a + 1, ItemType::隠鎧, StatusType::Str, 0, 0, 0, 2 * b, 0, 2 * b, 0);
		}

	}

	std::vector<Item> Item::data;
}