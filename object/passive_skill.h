//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../system/enum_type.h"

namespace SDX_ADE
{
	using namespace SDX;

	//タイミング


	/*パッシブスキル*/
	class PassiveSkill
	{
	private:
	public:
		inline static std::vector<PassiveSkill> data;

		PassiveSkill()
		{}

		//保存しない変数
		Image* image;

		//-基本情報
		ID_PSkill ID;
		std::string 名前;
		std::string 説明;

		int レアリティ;
		bool isキースキル = false;

		bool スキルタグ[(int)SkillType::COUNT];

		ID_PSkill 習得前提PスキルID;//MOD用、今回は使わない
		int 習得前提PスキルLv;
		int 習得必要Lv;

		PSkillIf 条件;
		int 条件値;
		int 持続時間;//一時バフ用

		PSkillTime タイミング;
		int 発動率;
		PSkillTarget 対象;

		PSkillEffect 効果種[2];
		int 効果量[2];

		PSkillLvType レベル補正_種類[2];
		int レベル補正_数値[2];

		int Get条件値(int Lv)
		{
			int value = 条件値;
			Lv -= 1;

			if (Lv <= 0) { return value; }

			for (int i = 0; i < 2; i++)
			{
				if (レベル補正_種類[i] == PSkillLvType::条件値)
				{
					if (i == 1) { Lv = (Lv + 1) / 5; }
					value += レベル補正_数値[i] * Lv;
				}
			}

			return value;
		}

		int Get発動率(int Lv)
		{
			int value = 発動率;

			Lv -= 1;

			if (Lv <= 0) { return value; }

			for (int i = 0; i < 2; i++)
			{
				if (レベル補正_種類[i] == PSkillLvType::発動率)
				{
					if (i == 1) { Lv = (Lv + 1) / 5; }
					value += レベル補正_数値[i]*Lv;
				}
			}

			return value;
		}

		int Get効果値( int index , int Lv)
		{
			int value = 効果量[index];
			Lv -= 1;
			if (Lv <= 0) { return value; }

			if (index == 0 )
			{
				for (int i = 0; i < 2; i++)
				{
					if (レベル補正_種類[i] == PSkillLvType::効果値1)
					{
						if (i == 1) { Lv = (Lv + 1) / 5; }
						value += レベル補正_数値[i] * Lv;
					}
				}
			} else {
				for (int i = 0; i < 2; i++)
				{
					if (レベル補正_種類[i] == PSkillLvType::効果値2)
					{
						if (i == 1) { Lv = (Lv + 1) / 5; }
						value += レベル補正_数値[i] * Lv;
					}
				}
			}

			return value;
		}

		int Get持続値(int Lv)
		{
			int value = 持続時間;
			Lv -= 1;

			if (Lv <= 0) { return value; }

			for (int i = 0; i < 2; i++)
			{
				if (レベル補正_種類[i] == PSkillLvType::持続時間)
				{
					if (i == 1) { Lv = (Lv + 1) / 5; }
					value += レベル補正_数値[i] * Lv;
				}
			}

			return value;
		}

		static void LoadData()
		{
			File file_data("file/data/pskill.dat", FileMode::Read, true);
			File file_csv("file/data/pskill.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);

			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				data.emplace_back();
				auto& it = data.back();

				it.ID = i;
				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				file_data.Read( dummy );
				it.image = &MIcon::Pスキル[dummy];

				file_data.Read(it.isキースキル);

				file_data.Read(it.スキルタグ, (int)SkillType::COUNT);
				file_data.Read(it.習得前提PスキルID);
				file_data.Read(it.習得前提PスキルLv);
				file_data.Read(it.習得必要Lv);

				file_data.Read(it.条件);
				file_data.Read(it.条件値);
				file_data.Read(it.持続時間);

				file_data.Read(it.タイミング);
				file_data.Read(it.発動率);
				file_data.Read(it.対象);
				file_data.Read(it.効果種[0]);
				file_data.Read(it.効果量[0]);
				file_data.Read(it.効果種[1]);
				file_data.Read(it.効果量[1]);

				file_data.Read(it.レベル補正_種類[0]);
				file_data.Read(it.レベル補正_数値[0]);


				file_data.Read(it.レベル補正_種類[1]);
				file_data.Read(it.レベル補正_数値[1]);

				file_data.Read(it.レアリティ);
			}
		}
	};


	//Pスキル処理の流れ
	//複数人パッシブや装備パッシブを探索開始時に代入処理する

	//無条件基礎ステ系CT変化系パッシブを探索開始時に処理

	//スキル使用時に、威力:命中変化

	//各関数でTime条件があってるかチェック
	//IF条件、Aスキル条件、装備条件、発動確率をチェック、しきい値付きの条件をチェック
	//パッシブ効果の処理は一箇所にまとめる

	//パッシブ処理してる関数
	//常時○開始時、攻撃スキル防御回復時
	//戦闘勝利時○
	//基礎計算時○

	//スキル使用時
	//通常攻撃時




}