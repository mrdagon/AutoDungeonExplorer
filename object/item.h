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
			this->ステ[StatusType::HP] = 追加Hp;
			this->ステ[StatusType::力] = 追加Str;
			this->ステ[StatusType::知] = 追加Int;
			this->ステ[StatusType::技] = 追加Dex;
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

		}
	};
}