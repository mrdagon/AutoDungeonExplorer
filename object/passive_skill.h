//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include "../system/enum_type.h"

namespace SDX_ADE
{
	using namespace SDX;

	//実装メモ
	//http://tacoika.blog87.fc2.com/blog-entry-590.html

	//タイミング
	enum class PSkillTime
	{
		常時,//探索開始時や編成変更時のみ処理
		戦闘開始時,
		スキル使用時,
		スキル受ける前,
		//トリガー系パッシブ
		攻撃を受けた時,
		回復を受けた時,
		回避した時,
		自分が気絶した時,
		味方が気絶した時,
		自分が撃破した時,
		味方が撃破した時,//自分も含む
	};

	//条件
	enum class PSkillIf
	{
		条件無し,
		//状況条件
		HP一定以上,
		HP一定以下,
		敵の数が一定以下,
		敵の数が一定以上,
		自身が状態異常,
		自身が隠密,
		自身が挑発,
		前列,
		後列
	};

	enum class PSkillTarget
	{
		自分,
		味方全員,
		スキル対象,
		敵単体,//敵対象パッシブは戦闘開始時とリアクション系のみ
		敵全体,
		その他
	};

	enum class PSkillEffect
	{
		なし,
		//●アクティブスキル、通常攻撃強化
		＠スキル強化,
		ダメージ増加,
		スキル威力増減,
		スキル効果増減,
		スキルCT増減,
		アクティブスキル発動,
		物理化,
		魔法化,
		隊列無視,
		必中,
		隠れる無視,
		挑発無視,
		異常回復,
		気絶回復,
		防御貫通,//1で完全無視
		魔防貫通,
		回避貫通,
		超過回復,//最大HPを超えた分バリアを貼る
		バフ固定値,
		バフ反映率,
		バフ発動率,
		バフ持続,
		バフ延長,
		デバフ延長,
		バフ強化,//-1で解除、1で効果倍増
		デバフ強化,//-1で解除、1で効果倍増
		先制,//1で戦闘開始時100%
		むらっけ,
		吸収,//1で与えたダメージと同じだけ回復
		処刑,
		異常追撃,
		挑発追撃,
		//●バフ、特殊ステータス増加
		＠保持効果,
		与ダメージバフ,
		受ダメージバフ,
		HP1で耐える,
		異常無効,
		デバフ無効,
		身代わり,
		CT減少,
		HP回復,
		未探索発見率増加,
		戦闘後回復,
		剥取増加,
		レア剥取増加,
		採取増加,
		レア採取増加,
		魔物部屋率上昇,
		素材部屋率上昇,
		移動速度上昇,
		//●その他
		HP増加,
		STR増加,
		INT増加,
		DEX増加,
		物防増加,
		魔防増加,
		命中増加,
		回避増加,
		HP割合増加,
		STR割合増加,
		INT割合増加,
		DEX割合増加,
		物防割合増加,
		魔防割合増加,
		経験値増加,
		＠キーパッシブ,
	};

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

		bool isキースキル = false;

		bool スキルタグ[(int)SkillType::COUNT];

		ID_PSkill 習得前提PスキルID;
		int 習得前提PスキルLv;
		int 習得必要Lv;

		PSkillIf 条件;
		int 条件値;
		int 持続時間;

		PSkillTime タイミング;
		int 発動率;
		PSkillTarget 対象;

		PSkillEffect 効果種[2];
		int 効果量[2];

		int レベル補正種[2];
		int レベル補正値[2][9];

		static void LoadData()
		{
			File file_data("file/data/pskill.dat", FileMode::Read, true);
			File file_csv("file/data/pskill.csv", FileMode::Read, false);
			auto strs = file_csv.GetCsvToString2();//空の場合、Vectorのサイズが1になる

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

				file_data.Read(it.レベル補正種[0]);
				for (int b = 0; b < 9; b++)
				{
					file_data.Read(it.レベル補正値[0][b]);
				}

				file_data.Read(it.レベル補正種[1]);
				for (int b = 0; b < 9; b++)
				{
					file_data.Read(it.レベル補正値[1][b]);
				}
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