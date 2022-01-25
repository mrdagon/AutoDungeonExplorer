//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	//参考
	//http://tacoika.blog87.fc2.com/blog-entry-588.html

	struct ASkill補助効果
	{
		BuffType 種類;
		int 基礎値;
		int 反映率;
		//int 確率;
		int 持続;

		ASkill補助効果(BuffType 種類, int 基礎値, int 反映率, int 持続) :
			種類(種類),
			基礎値(基礎値),
			反映率(反映率),
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

		int レアリティ;

		int 戦闘エフェクト;//IDで管理

		bool スキルタグ[(int)SkillType::COUNT];//これでサブ属性は管理

		int 基礎ダメージ;
		int 反映率;
		int 命中;
		int クールタイム;

		ASkillTarget 対象;
		int 範囲 = 1;
		int Hit数;

		StatusType 参照ステータス;
		FormationType 適正隊列;
		DamageType 属性;//スキルタグから取得

		EnumArray<int, ASkillSubType> 追加効果;
		std::vector<ASkill補助効果> 補助効果;

		bool is自己バフ = false;//補助効果の対象が命中した相手でなく自分になる
		
		//関数
		ActiveSkill() {}

		static void LoadData()
		{
			File file_data("file/data/askill.dat",FileMode::Read,true);
			File file_csv("file/data/askill.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2('\t');//空の場合、Vectorのサイズが1になる

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
					std::replace(it.説明.begin(), it.説明.end(), '$', '\n');
				}

				it.ID = i;

				file_data.Read( dummy );//アイコンID
				it.image = &MIcon::Aスキル[dummy];

				file_data.Read(dummy);//エフェクトID
				it.戦闘エフェクト = dummy;

				file_data.Read(dummy);//習得Lv
				file_data.Read(dummy);//前提スキルID
				file_data.Read(dummy);//前提スキルLv

				file_data.Read(it.スキルタグ , (int)SkillType::COUNT);
				
				file_data.Read(it.レアリティ);

				file_data.Read(it.基礎ダメージ);
				file_data.Read(it.反映率);
				file_data.Read(it.命中);
				file_data.Read(dummy);//会心
				file_data.Read(dummy);//会心倍率
				file_data.Read(it.クールタイム);
				file_data.Read(it.対象);
				file_data.Read(it.範囲);
				file_data.Read(it.Hit数);
				file_data.Read(dummy);//減衰率

				file_data.Read(it.参照ステータス);
				file_data.Read(it.適正隊列);
				file_data.Read(dummy);//連続スキルID

				//追加効果最大5つ
				ASkillSubType tmp追加種類[5];
				int tmp追加効果値[5];

				for (int b = 0; b < 5; b++)
				{
					file_data.Read(tmp追加種類[b]);
					file_data.Read(tmp追加効果値[b]);
				}

				for (int i = 0; i < (int)ASkillSubType::COUNT; i++)
				{
					it.追加効果[(ASkillSubType)i] = 0;
				}


				for (int b = 0; b < 5 ; b++)
				{
					if ( tmp追加種類[b] != ASkillSubType::なし)
					{
						if (tmp追加効果値[b] == 0)
						{
							it.追加効果[tmp追加種類[b]] = -1;//Aスキルレベルで特性追加する場合用の処理
						} else {
							it.追加効果[tmp追加種類[b]] = tmp追加効果値[b];
						}

					}
				}

				//レベル補正
				file_data.Read(dummy);
				file_data.Read(dummy);
				file_data.Read(dummy);
				file_data.Read(dummy);

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
					file_data.Read(tmpバフ発動率[b]);//使わない
					file_data.Read(tmpバフ持続[b]);
				}

				for (int b = 0; b < 3; b++)
				{
					if (tmpバフ種[b] != BuffType::なし)
					{
						it.補助効果.emplace_back(tmpバフ種[b], tmpバフ固定値[b], tmpバフ反映率[b], tmpバフ持続[b]);
					}
				}

				//スキル属性代入
				if (it.スキルタグ[(int)SkillType::回復] == true)
				{
					it.属性 = DamageType::回復;
				}
				else if (it.スキルタグ[(int)SkillType::攻撃] == true)
				{
					it.属性 = DamageType::無属性;
				}
				else
				{
					it.属性 = DamageType::補助;
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
		//スキルタグ、is自己バフ、連続使用スキルなどはベースから変化しないのでこっちでは保持しない
		const ActiveSkill* base;

		int 基礎ダメージ = 0;//固定ダメージ
		int 反映率 = 0;
		int 命中 = 0;

		int 会心率 = 0;
		int 会心倍率 = 150;

		ASkillTarget 対象;
		int 範囲 = 1;
		int Hit数;

		StatusType 参照ステータス;
		FormationType 適正隊列;
		DamageType 属性;

		EnumArray< int, ASkillSubType> 追加効果;
		std::vector<ASkill補助効果> 補助効果;

		//Pスキル補正、最後に計算するタイプ
		int ダメージ％増加 = 0;
		int 効果％増加 = 0;
		int 行動値獲得 = 0;
		int バフ発動率 = 0;
		int バフ反映率 = 0;
		int バフ持続 = 0;
		int バフ固定値 = 0;

		//ベースAスキルとLvを元に一時計算用のデータを作成
		ASkillEffect(const ActiveSkill* スキルベース ):
			base(スキルベース)
		{
			基礎ダメージ = base->基礎ダメージ;
			反映率 = base->反映率;
			命中 = base->命中;

			対象 = base->対象;
			範囲 = base->範囲;
			Hit数 = base->Hit数;

			参照ステータス = base->参照ステータス;
			適正隊列 = base->適正隊列;
			属性 = base->属性;

			for (int i = 0; i < base->追加効果.size(); i++)
			{
				追加効果[ASkillSubType(i)] = std::max( 0, base->追加効果[ASkillSubType(i)] );
			}

			for (int i = 0; i < base->補助効果.size(); i++)
			{
				補助効果.emplace_back(base->補助効果[i]);
			}
		}
	};
}