﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	enum class Order
	{
		探索重視,
		収集重視,
		戦闘重視,
		ボス討伐,
		COUNT
	};

	class Party
	{
	public:
		Party()
		{
			メンバー.resize(CV::パーティ人数);

			for (int a = 0; a < CV::パーティ人数; a++)
			{
				メンバー[a] = nullptr;
			}
		}

		int ギルドID;

		Dungeon* 探索先;
		Order 探索指示;

		EnumArray<int, MaterialType> 獲得素材[CV::最大素材ランク];
		std::vector <Monster> 魔物;

		std::vector<Warker*> メンバー;
		std::vector<Fighter*> 味方;
		std::vector<Fighter*> 敵;
		int 戦闘待ち;

		double 経験値;
		bool is探索中;
		bool is移動中;
		bool is全滅;
		bool is戦闘;
		bool isボス戦;

		int 部屋ID;
		int 残り移動時間;
		int 残り待機時間;

		void スキルステ計算()
		{
			味方.clear();
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] != nullptr) { 味方.push_back(メンバー[a]); }
				メンバー[a]->探索開始();
			}
			for (int a = 0; a < 味方.size(); a++)
			{
				味方[a]->発動パッシブ.clear();
			}
			for (int a = 0; a < 味方.size(); a++)
			{
				味方[a]->所持スキル計算(味方);
			}
			for (int a = 0; a < 味方.size(); a++)
			{
				味方[a]->基礎ステータス計算(味方, 敵);
			}
		}

		void 探索開始()
		{
			is探索中 = true;
			is移動中 = true;
			is戦闘 = false;
			isボス戦 = false;
			残り移動時間 = 100;
			残り待機時間 = 0;
			//パーティメンバーの体力回復、ステータス計算
			味方.clear();
			スキルステ計算();

			if (味方.size() == 0) { is全滅 = true; }
			else { is全滅 = false; }
		}

		void 探索終了(EnumArray<int, MaterialType> *素材数)
		{
			//素材獲得
			for (int a = 0; a < CV::最大素材ランク; a++)
			{
				for (int b = 0; b < CV::素材種; b++)
				{
					MaterialType mat = MaterialType(b);
					素材数[a][mat] += 獲得素材[a][mat];
					獲得素材[a][mat] = 0;
				}
			}
			//レベルアップ
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] == nullptr){continue;}

				while ( メンバー[a]->レベルアップ() ){}
			}

			スキルステ計算();
		}

		void 探索処理(EnumArray<int, MaterialType> *素材数)
		{
			//探索終了判定
			if (is探索中 == false)
			{
				return;
			}
			if (Game::時間 >= Game::終業時間 && is移動中)
			{
				探索終了(素材数);
				is探索中 = false;
				return;
			}

			//戦闘等のエフェクト更新
			for (auto& it : 味方)
			{
				it->エフェクト更新();
			}
			for (auto& it : 敵)
			{
				it->エフェクト更新();
			}

			//待機中(収集中、戦闘後待機、宝部屋etc)
			if ( 残り待機時間 > 0)
			{
				残り待機時間--;
				if (残り待機時間 == 0)
				{
					残り移動時間 = 100;
					is移動中 = true;
				}
				return;
			}
			//移動中
			if ( 残り移動時間 > 0 )
			{
				残り移動時間--;
				if (残り移動時間 == 0)
				{
					is移動中 = false;
					部屋選び();
				}
				return;
			}
			//戦闘中処理
			戦闘処理();
		}

		//部屋選択関係の処理
		void 部屋選び()
		{
			std::vector<int> room_deck;

			switch (探索指示)
			{
			case Order::探索重視://50%で未探索から探索
				if (Rand::Coin(0.5) == true)
				{
					//ボス部屋以外の未探索部屋
					for (int a = 0; a < 探索先->部屋数; a++)
					{
						if (探索先->部屋[a].is探索[ギルドID] == false && 探索先->部屋[a].種類 != RoomType::ボス)
						{
							room_deck.push_back(a);
						}
					}

				} else {
					ランダム部屋選び(room_deck);
				}
				break;
			case Order::戦闘重視://50%で魔物部屋を探索
				if (Rand::Coin(0.5) == true)
				{
					//素材部屋回避
					for (int a = 0; a < 探索先->部屋数; a++)
					{
						if (探索先->部屋[a].種類 != RoomType::素材 && 探索先->部屋[a].種類 != RoomType::ボス)
						{
							room_deck.push_back(a);
						}
					}
				}
				else {
					ランダム部屋選び(room_deck);
				}
				break;
			case Order::収集重視://50%で素材部屋を探索
				if (Rand::Coin(0.5) == true)
				{
					//魔物部屋回避
					for (int a = 0; a < 探索先->部屋数; a++)
					{
						if (探索先->部屋[a].種類 != RoomType::魔物 && 探索先->部屋[a].種類 != RoomType::ボス)
						{
							room_deck.push_back(a);
						}
					}
				} else {
					ランダム部屋選び(room_deck);
				}
				break;
			case Order::ボス討伐://50%の確率でボス部屋
				探索先->探索率計算(ギルドID);
				double rate = 探索先->探索率[ギルドID]*2 - 1;

				if (rate > 0 && Rand::Coin(rate) == true && 探索先->isボス戦中 == false && 探索先->isボス生存 )
				{
					//ボス部屋
					for (int a = 0; a < 探索先->部屋数; a++)
					{
						if ( 探索先->部屋[a].種類 == RoomType::ボス)
						{
							room_deck.push_back(a);
						}
					}
				} else {
					ランダム部屋選び(room_deck);
				}
				break;
			}

			//部屋が無かった場合ランダム
			if (room_deck.size() <= 0) { ランダム部屋選び(room_deck); };
			//抽選
			部屋ID = room_deck[Rand::Get((int)room_deck.size() - 1)];
			部屋選択後処理();
		}

		void ランダム部屋選び(std::vector<int> &room_deck)
		{
			for (int a = 0; a < 探索先->部屋数; a++)
			{
				if (探索先->部屋[a].種類 != RoomType::ボス)
				{
					room_deck.push_back(a);
				}
			}
		}

		//部屋選択後の処理
		void 部屋選択後処理()
		{
			switch (探索先->部屋[部屋ID].種類)
			{
			case RoomType::素材:
				素材処理();
				break;
			case RoomType::魔物:
				is戦闘 = true;
				戦闘開始(false);
				break;
			case RoomType::財宝:
				財宝処理();
				break;
			case RoomType::ボス:
				is戦闘 = true;
				戦闘開始(true);
				break;
			}

		}

		void 素材処理()
		{
			残り待機時間 = 600;
			//素材獲得処理
			獲得素材[探索先->ランク][探索先->部屋[部屋ID].素材種]++;

			地図発見処理();
		}

		void 財宝処理()
		{
			残り待機時間 = 600;

			獲得素材[探索先->ランク][MaterialType::宝石]++;
			//素材部屋に変化
			探索先->部屋[部屋ID].種類 = RoomType::素材;

			地図発見処理();
		}

		void 戦闘開始(bool isボス)
		{
			敵.clear();
			魔物.clear();


			//敵の生成
			int num = Rand::Get(4, 6);
			if (isボス == true)
			{
				探索先->isボス戦中 = true;
				isボス戦 = true;
				num = 1;
				敵.resize(num);

				魔物.emplace_back(探索先->ボスモンスター, 探索先->Lv , true);
			}
			else
			{
				敵.resize(num);

				for (int a = 0; a < num; a++)
				{
					int mn = Rand::Get(2);
					魔物.emplace_back(探索先->雑魚モンスター[mn],探索先->Lv,false);
				}
			}

			for (int a = 0; a < num; a++)
			{
				敵[a] = &魔物[a];
			}


			//戦闘開始時のパッシブ
			for (auto &it : 味方)
			{
				it->戦闘開始(味方, 敵);
			}

			for (auto &it : 敵)
			{
				it->戦闘開始(敵, 味方);
			}

			//
			戦闘待ち = 30;
		}

		void 戦闘処理()
		{
			if (戦闘待ち > 0)
			{
				戦闘待ち--;
				return;
			}

			while( 1 )
			{ 
				//行動値計算
				int 未行動数 = 0;
				double 最高速度 = -1000;
				Fighter* 行動者 = nullptr;
				bool is味方;

				for (auto &it : 味方)
				{
					if (it->現在HP <= 0) { continue; }
					if (it->残り行動数 > 0 && 最高速度 < it->基礎Agi)
					{
						行動者 = it;
						最高速度 = it->補正Agi;
						is味方 = true;
					}
				}

				for (auto &it : 敵)
				{
					if (it->現在HP <= 0) { continue; }
					if (it->残り行動数 > 0 && 最高速度 < it->基礎Agi)
					{
						行動者 = it;
						最高速度 = it->補正Agi;
						is味方 = false;
					}
				}

				//行動判定,スキル処理
				if (行動者 == nullptr)
				{
					//行動回数再計算してもう一回行動者計算
					for (auto &it : 味方)
					{
						it->残り行動数 = 1;
					}
					for (auto &it : 敵)
					{
						it->残り行動数 = 1;
					}
				}else {
					//行動処理
					if (is味方)
					{
						行動者->戦闘行動(味方, 敵);
						行動者->残り行動数--;
						break;
					} else {
						行動者->戦闘行動(敵, 味方);
						行動者->残り行動数--;
						break;
					}
				}
			}

			戦闘待ち = 12;

			戦闘終了判定();
		}

		void 戦闘終了判定()
		{
			//味方全滅or逃走
			int 死者数 = 0;
			for (auto& it : 味方)
			{
				if (it->現在HP <= 0)
				{
					死者数++;
				}
			}

			if (死者数 == 味方.size())
			{
				戦闘敗北();
				return;
			}
			//敵全滅
			死者数 = 0;
			for (auto& it : 敵)
			{
				if (it->現在HP <= 0)
				{
					死者数++;
				}
			}

			if (死者数 == 敵.size())
			{
				戦闘勝利();
				return;
			}
		}

		void 戦闘勝利()
		{
			if (isボス戦 == true)
			{
				探索先->isボス生存 = false;
				探索先->isボス戦中 = false;
				探索先->部屋[部屋ID].種類 = RoomType::魔物;
			}

			//戦闘後のパッシブ処理
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] != nullptr)
				{
					メンバー[a]->戦闘後処理(メンバー,味方,敵);
				}
			}

			//経験値獲得
			double 経験値 = 0;
			for (auto&it : 魔物)
			{
				経験値 += it.経験値;
			}

			//経験値獲得
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] != nullptr && メンバー[a]->現在HP > 0)
				{
					メンバー[a]->経験値 += 経験値;
				}
			}

			//体力小回復
			for (int a = 0; a < CV::パーティ人数; a++)
			{
				if (メンバー[a] != nullptr)
				{
					メンバー[a]->現在HP += メンバー[a]->最大HP/20;
					if (メンバー[a]->現在HP > メンバー[a]->最大HP) { メンバー[a]->現在HP = メンバー[a]->最大HP; }
				}
			}


			獲得素材[探索先->ランク][探索先->部屋[部屋ID].素材種]++;
			is移動中 = true;
			残り移動時間 = 100;


			地図発見処理();
		}

		void 戦闘敗北()
		{
			if (isボス戦 == true)
			{
				探索先->isボス戦中 = false;
			}

			is全滅 = true;
			is探索中 = false;
		}

		void 地図発見処理()
		{
			int cid = 探索先->部屋[部屋ID].地図;
			if (探索先->部屋[部屋ID].is探索[ギルドID] == false && cid >= 0)
			{
				Dungeon::data[cid].is発見[ギルドID] = true;
			}

			探索先->部屋[部屋ID].is探索[ギルドID] = true;
			探索先->探索率計算(ギルドID);
		}

	};
}