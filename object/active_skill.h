//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	//参考
	//http://tacoika.blog87.fc2.com/blog-entry-588.html


	struct ASkill追加効果
	{
		ASkill追加効果(ASkillSubType 種類, int 値) :
			種類(種類),
			値(値)
		{}

		ASkillSubType 種類;
		int 値;
	};
	struct ASkill補助効果
	{
		BuffType 種類;
		int 基礎値;
		int 反映率;
		int 確率;
		int 持続;

		ASkill補助効果(BuffType 種類, int 基礎値, int 反映率, int 確率, int 持続) :
			種類(種類),
			基礎値(基礎値),
			反映率(反映率),
			確率(確率),
			持続(持続)
		{}

	};

	/*アクティブスキル*/
	//外部データから読み込む
	class ActiveSkill
	{

	public:
		inline static std::vector<ActiveSkill> data;
		//保存しない変数
		Image* image;

		//変数
		ID_ASkill ID;
		std::string 名前;
		std::string 説明;

		ImagePack* 戦闘エフェクト;

		int 習得Lv;
		int 習得前提スキルID;
		int 習得前提スキルLv;

		bool スキルタグ[(int)SkillType::COUNT];//これでサブ属性は管理

		int 基礎ダメージ;
		int 反映率;
		int 命中;
		int 会心率 = 0;
		int 会心倍率 = 100;
		int クールタイム;

		ASkillTarget 対象;
		int 範囲 = 1;
		int Hit数;

		StatusType 参照ステータス;
		FormationType 適正隊列;
		DamageType 属性;//スキルタグから取得

		ID_ASkill 連続スキル;

		std::vector<ASkill追加効果> 追加効果;
		std::vector<ASkill補助効果> 補助効果;

		bool is自己バフ = false;//補助効果の対象が命中した相手でなく自分になる
		
		int レベル補正_種類[2];
		int レベル補正_数値[2][9];

		//関数
		ActiveSkill() {}

		static void LoadData()
		{
			File file_data("file/data/askill.dat",FileMode::Read,true);
			File file_csv("file/data/askill.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

			int data_count = 0;
			file_data.Read(data_count);
			
			for (int i = 0; i < data_count; i++)
			{
				int dummy;

				data.emplace_back();
				auto& it = data.back();

				it.名前 = strs[i][0];
				if (strs[i].size() == 2)
				{
					it.説明 = strs[i][1];
				}

				it.ID = i;

				file_data.Read( dummy );
				it.image = &MIcon::Aスキル[dummy];

				file_data.Read(dummy);
				it.戦闘エフェクト = &MEffect::エフェクト[dummy];

				file_data.Read(it.習得Lv);
				file_data.Read(it.習得前提スキルID);
				file_data.Read(it.習得前提スキルLv);

				file_data.Read(it.スキルタグ , (int)SkillType::COUNT);
				
				file_data.Read(it.基礎ダメージ);
				file_data.Read(it.反映率);
				file_data.Read(it.命中);
				file_data.Read(it.会心率);
				file_data.Read(it.会心倍率);
				file_data.Read(it.クールタイム);
				file_data.Read(it.対象);
				file_data.Read(it.範囲);
				file_data.Read(it.Hit数);
				file_data.Read(dummy);//減衰率はスキップ

				file_data.Read(it.参照ステータス);
				file_data.Read(it.適正隊列);
				file_data.Read(it.連続スキル);

				//追加効果最大5つ
				ASkillSubType tmp追加種類[5];
				int tmp追加効果値[5];

				for (int b = 0; b < 5; b++)
				{
					file_data.Read(tmp追加種類[b]);
					file_data.Read(tmp追加効果値[b]);
				}

				for (int b = 0; b < 5; b++)
				{
					if ( tmp追加種類[b] != ASkillSubType::なし)
					{
						it.追加効果.emplace_back( tmp追加種類[b], tmp追加効果値[b]);
					}
				}

				//レベル補正
				file_data.Read(it.レベル補正_種類[0]);
				file_data.Read(it.レベル補正_数値[0],9);
				file_data.Read(it.レベル補正_種類[1]);
				file_data.Read(it.レベル補正_数値[1], 9);

				file_data.Read(it.is自己バフ);

				//補助効果最大3つ
				BuffType tmpバフ種[3];
				int tmpバフ固定値[3];
				int tmpバフ反映率[3];
				int tmpバフ発動率[3];
				int tmpバフ持続[3];

				for (int b = 0; b < 3; b++)
				{
					file_data.Read(tmpバフ種[b]);
					file_data.Read(tmpバフ固定値[b]);
					file_data.Read(tmpバフ反映率[b]);
					file_data.Read(tmpバフ発動率[b]);
					file_data.Read(tmpバフ持続[b]);
				}

				for (int b = 0; b < 3; b++)
				{
					if (tmpバフ種[b] != BuffType::なし)
					{
						it.補助効果.emplace_back(tmpバフ種[b], tmpバフ固定値[b], tmpバフ反映率[b], tmpバフ発動率[b], tmpバフ持続[b]);
					}
				}

				//スキル属性代入
				it.属性 = DamageType::無属性;
				if ( it.スキルタグ[(int)SkillType::物理] == true)
				{
					it.属性 = DamageType::物理;
				}
				else if (it.スキルタグ[(int)SkillType::魔法] == true)
				{
					it.属性 = DamageType::魔法;
				}
				
			}

		}
	};

	/*ダメージ計算用*/
	//元データの数値をコピーしてLv補正掛けて、Pスキル補正かけての計算する用
	//一時的なデータ
	class ASkillEffect
	{
	public:
		//
		//スキルタグ、is自己バフ、連続使用スキル

		const ActiveSkill* base;

		ASkillTarget 対象;
		int 範囲 = 1;

		FormationType 適正隊列;
		DamageType 属性;

		ItemType 装備種 = ItemType::すべて;

		int Hit数 = 1;//多段ヒット数
		double 命中 = 1.0;

		double 基礎ダメージ = 0;//固定ダメージ
		double 反映率 = 0;

		double 会心率 = 0.05;
		double 会心倍率 = 1.5;

		std::vector<ASkill追加効果> 追加効果;
		std::vector<ASkill補助効果> 補助効果;

		//ASkillにないやつ
		double バフ効果補正 = 1.0;
		double バフ持続補正 = 1.0;

		ASkillEffect(const ActiveSkill* スキルベース):
			base(スキルベース)
		{

		}


	};
}