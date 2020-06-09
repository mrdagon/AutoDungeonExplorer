//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*客-廃止*/
	/*
	class Customer
	{
	private:
	public:
		static std::vector<Customer> customers;
		static std::list<Customer> my_customers;

		Customer(int 来店ギルド,int 待ち時間):
			来店ギルド(来店ギルド),待ち時間(待ち時間)
		{
			見た目 = UnitImageType(Rand::Get((int)UnitImageType::COUNT-1));
		}

		UnitImageType 見た目 = UnitImageType::王;
		ItemType 武器種;
		ItemType 防具種;
		int 待機限界 = 1000;

		//来店中ステータス
		int 来店ギルド;//-1なら非来店、それ以外ならどこかの店
		int 待ち時間;//現在の待ち時間、待機限界まで行くと怒り状態
		bool 接客待ち;
	};

	std::vector<Customer> Customer::customers;
	std::list<Customer> Customer::my_customers;
	*/
}