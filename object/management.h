//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*経営戦術*/
	class Management
	{
	private:
	public:
		static std::vector<Management> managements;

		Management(int ID,int Lv,ManagementType 系統,int MP , int 資金 , bool is永続):
			ID(ID),Lv(Lv),系統(系統),消費MP(MP),消費資金(資金),is永続(is永続)
		{

		}


		int ID;
		int Lv;//習得レベル
		std::string 名前;
		std::string 説明文;
		ManagementType 系統;
		int 消費MP;
		int 消費資金;
		IconType アイコン = IconType::資金;
		bool is永続;//単発効果 or 永続効果

		/*戦術実行効果*/
		void Active()
		{

		}
	};

	std::vector<Management> Management::managements;

}