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
		int Pスキル[2] = { 0,0 };//未実装

		int 値段 = 10000;

		//攻撃力等のステータス、追加されるスキル等
		int 追加Str, 追加Int, 追加Dex, 追加Hp = 0;

		EnumArray<int, DamageType> 防御;
		int 命中 = 0;
		int 回避 = 0;

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

		void Set( int ランク , ItemType 種類 ,int スキルa,int スキルb, int 追加Hp, int 追加Str, int 追加Dex, int 追加Int, int 物防 , int 魔防, int 命中 ,int 回避)
		{
			this->ランク = ランク;
			this->種類 = 種類;
			this->Aスキル[0] = スキルa;
			this->Aスキル[1] = スキルb;
			this->追加Hp = 追加Hp;
			this->追加Str = 追加Str;
			this->追加Int = 追加Int;
			this->追加Dex = 追加Dex;

			this->防御[DamageType::物理] = 物防;
			this->防御[DamageType::魔法] = 魔防;

			this->命中 = 命中;
			this->回避 = 回避;
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

		for (int a = 0; a < 30; a++)
		{
			std::string name;
			std::string num = (a == 0) ? "" : std::to_string(a + 1);

			int n = 2 + a;

			name = "鉄の斧"; Item::data.emplace_back(0 + a * 9, name + num, "STR武器", ItemImageType::鉄の斧);
			name = "鉄の剣";Item::data.emplace_back(1 + a * 9, name + num, "STR武器", ItemImageType::鉄の剣);
			name = "木の弓"; Item::data.emplace_back(2 + a * 9, name + num, "DEX武器", ItemImageType::木の弓);
			name = "鉄の盾"; Item::data.emplace_back(3 + a * 9, name + num, "VIT武器", ItemImageType::鉄の盾);
			name = "スタッフ"; Item::data.emplace_back(4 + a * 9, name + num, "STR/INT武器", ItemImageType::スタッフ);
			name = "ワンド"; Item::data.emplace_back(5 + a * 9, name + num, "INT武器", ItemImageType::ワンド);
			name = "鉄の鎧"; Item::data.emplace_back(6 + a * 9, name + num, "HP系防具", ItemImageType::鉄の鎧);
			name = "鎖帷子"; Item::data.emplace_back(7 + a * 9, name + num, "回避系防具", ItemImageType::鎖帷子);
			name = "ローブ"; Item::data.emplace_back(8 + a * 9, name + num, "INT系防具", ItemImageType::皮のローブ);

			//                                                   HP,STR,DEX,INT,B防,M防,命中,回避
			Item::data[0 + a * 9].Set(a+1, ItemType::斧  , 3, 4,  0,n*2,  0,  0,  0,  0,  0,  0);
			Item::data[1 + a * 9].Set(a+1, ItemType::剣  , 1, 2,  0,n*2,  n,  0,  0,  0,  0,  0);
			Item::data[2 + a * 9].Set(a+1, ItemType::弓  , 5, 6,  0,  0,n*2,  0,  0,  0,  5,  0);
			Item::data[3 + a * 9].Set(a+1, ItemType::盾  , 7, 8,n*2,n/2,  0,  0,  5,  5,  0,  0);
			Item::data[4 + a * 9].Set(a+1, ItemType::神杖,11,12,  0,n/2,  0,n*2,  0,  0,  0,  0);
			Item::data[5 + a * 9].Set(a+1, ItemType::魔杖, 9,10,  0,  0,  0,n*3,  0,  0,  0,  0);
			Item::data[6 + a * 9].Set(a+1, ItemType::重鎧, 0, 0,n*5,  0,  0,  0,  5,  5,  0,  0);
			Item::data[7 + a * 9].Set(a+1, ItemType::軽鎧, 0, 0,n*3,  0,  0,  0,  0,  0,  5,  5);
			Item::data[8 + a * 9].Set(a+1, ItemType::隠鎧, 0, 0,n*2,  0,  0,  n,  0,  5,  0,  0);
		}

	}

	std::vector<Item> Item::data;
}