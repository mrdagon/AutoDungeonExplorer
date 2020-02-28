//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*依頼*/
	class Quest
	{
	private:
	public:
		ClientS 依頼者;
		QuestType 依頼系統;
		int 要求素材[2];//素材依頼時のランクと数
		ItemNo 要求アイテム;//アイテム依頼時
		MonsterNo 要求魔獣;//討伐依頼時
		int 要求数;
		bool is受注;//受注前かどうか
		int 受注日;
		int 期日;

		bool is共通;//全ギルド共通依頼
	};
}