//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class BaseItem
	{
	public:
		static EnumArray<BaseItem, ItemType> data;
		
		ItemType 系統;

		//基礎ステ + 補正ステ x (装備性能 + 品質)
		EnumArray<int, StatusType> 基礎ステ;
		EnumArray<int, StatusType> 上昇ステ;
		PassiveSkill* Pスキル;

		static void Load()
		{
			

		}
	};

	EnumArray<BaseItem, ItemType> BaseItem::data;

	/*装備品、アイテム*/
	class Item
	{
	private:
	public:
		inline static std::vector<Item> data;

		ID_Item ID = 0;
		std::string 名前;
		std::string 説明;

		bool isレア = false;
		int Lv;

		int 品質 = 0;
		int 基礎性能 = 0;
		double 経験値 = 0;//品質強化経験値

		ItemType 種類;
		ItemImageType 見た目;

		PassiveSkill* Pスキル[1] = { nullptr };//未実装

		//攻撃力等のステータス、追加されるスキル等
		EnumArray<int, StatusType> ステ;

		int Getステ(StatusType ステータス種)
		{
			return BaseItem::data[種類].基礎ステ[ステータス種] + BaseItem::data[種類].上昇ステ[ステータス種] * Get性能();
		}

		int Get性能()
		{
			return 基礎性能 + 品質 * 10;
		}

		//経験値増加と品質上昇処理
		bool Add品質経験値(int 経験点)
		{
			経験値 += 経験点;

			if (経験値 >= 100 * (品質+1))
			{
				経験値 -= 100 * (品質 + 1);
				品質++;
				return true;
			}

			return false;
		}

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
			this->ステ[StatusType::生命] = 追加Hp;
			this->ステ[StatusType::筋力] = 追加Str;
			this->ステ[StatusType::知力] = 追加Int;
			this->ステ[StatusType::技力] = 追加Dex;
			this->ステ[StatusType::命中] = 命中;
			this->ステ[StatusType::回避] = 回避;

			this->ステ[StatusType::物防] = 物防;
			this->ステ[StatusType::魔防] = 魔防;
		}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//品質と経験値を読込
		}

		//外部データ読込
		static void LoadData()
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

			Game::対応レシピ[ItemType::大剣] = CraftType::鍛造;
			Game::対応レシピ[ItemType::剣盾] = CraftType::木工;
			Game::対応レシピ[ItemType::大盾] = CraftType::木工;
			Game::対応レシピ[ItemType::円盤] = CraftType::魔術;
			Game::対応レシピ[ItemType::斧] = CraftType::鍛造;
			Game::対応レシピ[ItemType::刀] = CraftType::鍛造;
			Game::対応レシピ[ItemType::弓] = CraftType::木工;
			Game::対応レシピ[ItemType::神杖] = CraftType::魔術;
			Game::対応レシピ[ItemType::錫杖] = CraftType::魔術;
			Game::対応レシピ[ItemType::導杖] = CraftType::木工;
			Game::対応レシピ[ItemType::書物] = CraftType::裁縫;
			Game::対応レシピ[ItemType::水晶] = CraftType::魔術;

			Game::対応レシピ[ItemType::重鎧] = CraftType::鍛造;
			Game::対応レシピ[ItemType::軽鎧] = CraftType::裁縫;
			Game::対応レシピ[ItemType::軽装] = CraftType::裁縫;
			Game::対応レシピ[ItemType::外套] = CraftType::裁縫;
			
			//空き
			Item::data.emplace_back(0, "---", "空き", ItemImageType::アクセサリ);
			Item::data[0].Set(0, ItemType::すべて, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

			std::string name;

			name = "鉄の斧"; Item::data.emplace_back(1, name, "STR武器", ItemImageType::斧);
			Item::data[1].Set(1, ItemType::斧, 3, 4, 0, 6, 0, 0, 0, 0, 0, 0, 0);

			name = "鉄の剣"; Item::data.emplace_back(2, name, "STR武器", ItemImageType::大剣);
			Item::data[2].Set(1, ItemType::大剣, 1, 2, 0, 4, 2, 0, 0, 0, 0, 0, 0);

			name = "木の弓"; Item::data.emplace_back(3, name, "DEX武器", ItemImageType::弓);
			Item::data[3].Set(1, ItemType::弓, 5, 6, 0, 0, 4, 0, 0, 0, 5, 0, 0);

			name = "鉄の盾"; Item::data.emplace_back(4, name, "VIT武器", ItemImageType::大盾);
			Item::data[4].Set(1, ItemType::大盾, 7, 8, 10, 2, 0, 0, 5, 5, 0, 0, 0);

			name = "スタッフ"; Item::data.emplace_back(5, name, "STR/INT武器", ItemImageType::神杖);
			Item::data[5].Set(1, ItemType::神杖, 11, 12, 0, 1, 0, 4, 0, 0, 0, 0, 0);

			name = "ワンド"; Item::data.emplace_back(6, name, "INT武器", ItemImageType::書物);
			Item::data[6].Set(1, ItemType::書物, 9, 10, 0, 0, 0, 6, 0, 0, 0, 0, 0);

			name = "鉄の鎧"; Item::data.emplace_back(7, name, "HP系防具", ItemImageType::重鎧);
			Item::data[7].Set(1, ItemType::重鎧, 0, 0, 20, 0, 0, 0, 5, 5, 0, 0, 0);

			name = "鎖帷子"; Item::data.emplace_back(8, name, "回避系防具", ItemImageType::軽鎧);
			Item::data[8].Set(1, ItemType::軽鎧, 0, 0, 12, 0, 0, 0, 0, 0, 5, 5, 0);

			name = "ローブ"; Item::data.emplace_back(9, name, "INT系防具", ItemImageType::外套);
			Item::data[9].Set(1, ItemType::外套, 0, 0, 8, 0, 0, 2, 0, 5, 0, 0, 0);
		}
	};
}