//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*経営戦術*/
	class Management
	{
	private:
	public:
		inline static std::vector<Management> data;
		inline static const int 必要経験値[CV::最大投資Lv] =
		{
			500000,
			1000000,
			2000000,
			4000000,
			8000000,
		   15000000,
		   25000000,
		   35000000,
		   50000000,
		   70000000,
		};

		Management(int ID,int Lv,ManagementType 系統, int 資金 , bool is永続):
			ID(ID),Lv(Lv),系統(系統),消費資金(資金),is永続(is永続)
		{
			MID = MSkillType(ID);
		}

		int ID;
		int Lv;//習得レベル
		std::string 名前;
		std::string 説明文;
		ManagementType 系統;
		MSkillType MID;

		int 消費資金;
		int 増加資金 = 0;
		int 使用回数 = 0;
		IconType アイコン = IconType::資金;
		bool is永続;//単発効果 or 永続効果
		bool can使用 = true;

		/*戦術実行効果*/
		void Active(Guild* guild)
		{
			//資金消費
			guild->資金 -= 消費資金;
			guild->投資経験値[系統] += 消費資金;
			消費資金 += 増加資金;
			使用回数++;
			//ログ
			EventLog::Add(0, Game::日付, LogDetailType::経営戦術使用, ID);

			if (is永続) { can使用 = false; }

			//部門Lv上昇判定
			if (!Lv上昇判定()){

				MSound::効果音[SE::投資実行].Play();
			}

			switch( MSkillType(ID) )
			{
				case MSkillType::ビラ配り:
					guild->集客力 += 5;
					break;
				case MSkillType::薄利多売:
					break;
				case MSkillType::新人発掘:
					break;
				case MSkillType::OJT:
					guild->戦闘経験補正 += 0.1;
					break;
				case MSkillType::技術研究:
					break;
				case MSkillType::低コスト化:
					guild->素材節約 += 0.1;
					break;
				case MSkillType::探索術:
					guild->未開探索 += 0.05;
					break;
				case MSkillType::探索許可証:
					if (guild->最大パーティ数 < CV::最大パーティ数){guild->最大パーティ数++;}
					break;
				case MSkillType::探索許可証2:
					if (guild->最大パーティ数 < CV::最大パーティ数) { guild->最大パーティ数++; }
					break;
			}


		}

		bool Lv上昇判定()
		{
			if (Guild::P->投資Lv[系統] < CV::最大投資Lv &&
				Guild::P->投資経験値[系統] > 必要経験値[Guild::P->投資Lv[系統]])
			{
				Guild::P->投資経験値[系統] -= 必要経験値[Guild::P->投資Lv[系統]];
				Guild::P->投資Lv[系統]++;

				EventLog::Add(0, Game::日付, LogDetailType::部門Lv上昇, (int)系統);
				MSound::効果音[SE::部門Lv上昇].Play();
				return true;
			}

			MSound::効果音[SE::投資実行].Play();
			return false;
		}

		static void LoadData()
		{
			//仮データ作成
			data.emplace_back(0, 1, ManagementType::経営, 100000, false);
			data.emplace_back(1, 1, ManagementType::経営, 500000, true);
			data.emplace_back(2, 1, ManagementType::人事,  30000, false);
			data.emplace_back(3, 1, ManagementType::人事, 500000, true);
			data.emplace_back(4, 1, ManagementType::製造, 100000, false);
			data.emplace_back(5, 1, ManagementType::製造, 500000, true);
			data.emplace_back(6, 1, ManagementType::探索, 100000, false);
			data.emplace_back(7, 1, ManagementType::探索, 500000, true);
			data.emplace_back(8, 2, ManagementType::探索,2000000, true);

			data[0].アイコン = IconType::資金;
			data[1].アイコン = IconType::資金;
			data[2].アイコン = IconType::求人;
			data[3].アイコン = IconType::求人;
			data[4].アイコン = IconType::製造;
			data[5].アイコン = IconType::製造;
			data[6].アイコン = IconType::迷宮;
			data[7].アイコン = IconType::迷宮;

			data[0].名前 = "ビラ配り";
			data[1].名前 = "薄利多売";
			data[2].名前 = "新人発掘";
			data[3].名前 = "OJT";
			data[4].名前 = "技術研究";
			data[5].名前 = "低コスト化";
			data[6].名前 = "探索術";
			data[7].名前 = "探索許可証";
			data[8].名前 = "探索許可証その２";

			data[0].説明文 = "集客力が0.5人/day増加";
			data[1].説明文 = "販売価格を一割引にする、来客が二割増";
			data[2].説明文 = "雇用ポイント+1";
			data[3].説明文 = "戦闘経験+10%";
			data[4].説明文 = "技術経験+10%";
			data[5].説明文 = "10%の確率で素材消費無し";
			data[6].説明文 = "探索進行確率が+5%";
			data[7].説明文 = "最大パーティ編成数+1";
			data[8].説明文 = "最大パーティ編成数+1";


			//経営、集客力上昇が何回でも使える。販売価格低下、客数増加
			//人事、人事ポイント＋１が何回でも使える。志願者数＋１が一回だけ。
			//製造、全部門技術Lv上昇が何回でも、素材消費減少が一回だけ。
			//探索、未探索部屋発見率＋が何回でも使える。探索パーティ＋１が一回だけ。
		}

		static bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//増加資金と使用回数
		}
	};

}