//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルド*/
	class Guild
	{
	private:

	public:
		static Guild* P;//プレイヤーのギルド
		static Guild data[CV::最大ギルド数];

		//ダンジョン発見済み、部屋攻略フラグ
		//イベントログ
		//Management 習得フラグ、使用フラグ
		//依頼人別の評価
		//ギルドマスターが誰か
		//アイテム所持数、開発可フラグ、在庫目標数
		//素材所持数
		int id = 0;

		EnumArray<int, MaterialType> 素材数[CV::最大素材ランク];

		double 資金 = 123456789;
		double 現在MP = 100;
		Management* 選択戦術 = 0;

		//従業員一覧
		std::vector<Warker*> ギルメン;

		std::vector<Warker*> 製造メンバー;
		Party 探索パーティ[CV::最大パーティ数];

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 部門Lv;
		EnumArray<double, ManagementType> 部門経験値;

		double 集客力;
		double 集客待ち;

		//製造関連
		double 必要製造力 = 1000;

		double 合計製造力 = 0;
		EnumArray<double, CraftType> 製造進行度;
		EnumArray<double, CraftType> 実製造力;
		EnumArray<double, CraftType> 使用素材ランク;
		EnumArray<double, CraftType> 使用宝石ランク;
		;
		EnumArray<int, CraftType> 製造割当;
		EnumArray<bool, CraftType> is宝石;
		//--製造特殊効果とか(未実装)

		//装備品
		bool is装備開発[CV::装備種];
		bool is新規[CV::装備種];
		int 装備所持数[CV::装備種];

		EnumArray < bool,ItemType> is新開発タブ;

		void 雇用処理()
		{
			for (auto& it : Warker::data)
			{
				if (it.is内定 == true && it.就活 == id)
				{
					it.is内定 = false;
					it.就活 = -1;
					it.所属 = id;
					製造メンバー.push_back(&it);

				}
			}
		}

		void 製造力計算()
		{
			合計製造力 = 0;
			for (auto &it : 製造メンバー)
			{
				it->表示ステ計算();
				合計製造力 += it->製造力;
			}

			double 合計割当 = 0;
			for (auto &it : 製造割当)
			{
				合計割当 += it;
			}

			if (合計割当 == 0) { 合計割当 = 1; }

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				CraftType n = (CraftType)a;
				実製造力[n] = 製造割当[n] / 合計割当;
			}
		}



		void 製造処理()
		{

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				CraftType n = (CraftType)a;
				//素材チェック
				if (製造進行度[n] == 0 && 実製造力[n] > 0)
				{
					if (素材チェック(n) == false) { continue; }
				}

				製造進行度[n] += 実製造力[n];

				if (製造進行度[n] >= 必要製造力)
				{
					装備完成処理(n);
					製造進行度[n] = 0;
				}
			}
		}

		bool 素材チェック(CraftType 種類)
		{
			Recipe* レシピ = &Recipe::data[種類];
			int 抽選ランク[4];
			int 何個目 = 0;

			//宝石チェック
			使用宝石ランク[種類] = 0;
			if (is宝石[種類] == true)
			{
				int 宝石合計 = 0;

				for (int a = CV::最大素材ランク - 1; a >= 0; a--)
				{
					宝石合計 += 素材数[a][MaterialType::宝石];
				}

				//4つ以上宝石必要
				if (宝石合計 >= 4)
				{
					//高ランクからチェック
					for (int a = CV::最大素材ランク - 1; a >= 0; a--)
					{
						while (素材数[a][MaterialType::宝石] > 0)
						{
							抽選ランク[何個目] = a;
							素材数[a][MaterialType::宝石]--;
							何個目++;

							if (何個目 >= 4)
							{
								使用宝石ランク[種類] = 抽選ランク[Rand::Get(3)] + 1;
								使用素材ランク[種類] = 使用宝石ランク[種類];
								return true;
							}
						}
					}
				}
			}

			//素材所持チェック
			for (int b = 0; b < 2; b++)
			{
				int 要求数 = レシピ->素材数;

				if (レシピ->素材[b] == MaterialType::COUNT) { continue; }

				for (int a = 0; a < CV::最大素材ランク; a++)
				{
					要求数 -= 素材数[a][レシピ->素材[b]];
				}
				if (要求数 > 0) { return false; }
			}

			//素材消費処理
			使用素材ランク[種類] = 0;
			for (int b = 0; b < 2; b++)
			{
				int 要求数 = レシピ->素材数;

				if (レシピ->素材[b] == MaterialType::COUNT) { continue; }

				for (int a = CV::最大素材ランク - 1; a >= 0; a--)
				{
					while (要求数 > 0 && 素材数[a][レシピ->素材[b]] > 0)
					{
						素材数[a][レシピ->素材[b]]--;
						要求数--;
						抽選ランク[何個目] = a;
						何個目++;
					}
				}
			}

			使用素材ランク[種類] = 抽選ランク[Rand::Get(3)] + 1;

			return true;
		}

		void 装備完成処理(CraftType 種類)
		{
			int itemID = (int)種類;
			double n = 使用素材ランク[種類];
			n = n * 100 + 5;
			
			int rank = Rand::Get((int)n) / 100;

			rank += (int)使用宝石ランク[種類];
			if (rank > 4) { rank = 4; }
			
			装備所持数[itemID + rank * 9]++;
			is装備開発[itemID + rank*9] = true;
		}

		void 探索開始()
		{
			for (int a = 0; a < 最大パーティ数; a++)
			{
				//パーティ人数をチェック
				探索パーティ[a].探索開始();
			}
		}

		void 探索処理()
		{
			for (int a = 0; a < 最大パーティ数; a++)
			{
				if (探索パーティ[a].味方.size() > 0 && 探索パーティ[a].is全滅 == false){探索パーティ[a].探索処理(素材数);}
			}
		}
	};


	Guild* Guild::P;
	Guild Guild::data[CV::最大ギルド数];
}