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

		PSkillIf 条件;
		int 条件値;

		PSkillTime タイミング;

		PSkillTarget 対象;

		PSkillEffectType 効果種;
		int 効果量;

		int Get条件値(int Lv)
		{
			return 条件値;
		}

		int Get効果値( int Lv)
		{
			return 効果量 * Lv;
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
					std::replace(it.説明.begin(), it.説明.end(), '$', '\n');
				}

				file_data.Read( dummy );
				it.image = &MIcon::Pスキル[dummy];

				file_data.Read(it.isキースキル);

				file_data.Read(it.スキルタグ, (int)SkillType::COUNT);
				file_data.Read(dummy);
				file_data.Read(dummy);
				file_data.Read(dummy);

				file_data.Read(it.条件);
				file_data.Read(it.条件値);
				file_data.Read(dummy);

				file_data.Read(it.タイミング);
				file_data.Read(dummy);
				file_data.Read(it.対象);
				file_data.Read(it.効果種);
				file_data.Read(it.効果量);
				file_data.Read(dummy);
				file_data.Read(dummy);

				file_data.Read(dummy);
				file_data.Read(dummy);


				file_data.Read(dummy);
				file_data.Read(dummy);

				file_data.Read(it.レアリティ);
			}
		}
	};

	class PSkillEffect
	{
	private:
		PassiveSkill* Pスキル;
		int Lv;
	public:
		PSkillEffect(PassiveSkill* Pスキル,int Lv) :
			Pスキル(Pスキル),
			Lv(Lv)
		{}

		PSkillEffectType Get効果種()
		{
			return Pスキル->効果種;
		}

		int Get条件値()
		{
			return Pスキル->Get条件値(Lv);
		}

		int Get効果値()
		{
			return Pスキル->Get効果値(Lv);		
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