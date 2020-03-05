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

		int 素材数[CV::最大素材ランク];

		double 資金 = 123456789;
		double 現在MP = 100;
		Management* 選択戦術 = 0;
		int 人事ポイント = 10;

		//従業員一覧
		std::vector<Warker*> ギルメン;

		EnumArray<std::vector<Warker*>, CraftType> 製造メンバー;
		Party 探索パーティ[CV::最大パーティ数];

		int 最大パーティ数 = 3;

		//パーティーと配属人員
		EnumArray<int, ManagementType> 部門Lv;
		EnumArray<double, ManagementType> 部門経験値;

		double 集客力;
		double 集客待ち;

		//製造関連
		double 必要製造力 = 1000;

		EnumArray<double, CraftType> 合計製造力;
		EnumArray<double, CraftType> 製造進行度;
		EnumArray<double, CraftType> 実製造力;
		EnumArray<double, CraftType> 使用素材ランク;
		EnumArray<int, CraftType> is装備修復;

		EnumArray<int, CraftType> 壊れた装備;
		//--製造特殊効果とか(未実装)

		//装備品
		bool is装備開発[CV::装備種];
		bool is新規[CV::装備種];
		int 装備所持数[CV::装備種];

		EnumArray < bool,ItemType> is新開発タブ;

		void 製造力計算()
		{
			合計製造力[CraftType::裁縫] = 0;
			合計製造力[CraftType::鍛造] = 0;
			合計製造力[CraftType::魔術] = 0;
			合計製造力[CraftType::木工] = 0;


			for (int a= 0 ; a< (int)CraftType::COUNT ; a++)
			{
				for (auto& it : 製造メンバー[CraftType(a)])
				{
					it->表示ステ計算();
					合計製造力[CraftType(a)] += it->製造力;
				}
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
			//素材所持チェックと消費		
			int 要求数 = 10;
			int 使用ランク = 0;

			for (int a = CV::最大素材ランク-1; a >= 0; a--)
			{
				if (素材数[a] >= 要求数)
				{
					使用ランク = a;
					使用素材ランク[種類] = a;
					素材数[a]--;
					break;
				}
			}
			if (使用ランク < 0) { return false; }

			return true;
		}

		void 装備完成処理(CraftType 種類)
		{
			int itemID = (int)種類;
			double n = 使用素材ランク[種類];
			n = n * 100 + 5;
			
			int rank = Rand::Get((int)n) / 100;

			//rank += (int)使用宝石ランク[種類];
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