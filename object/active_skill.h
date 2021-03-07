//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	//参考
	//http://tacoika.blog87.fc2.com/blog-entry-588.html

	//スキル対象
	enum class ASkillTarget
	{
		自分,
		隣接,
		前列,
		後列,
		弱者,
		前列範囲,
		後列範囲,
		敵前列,
		敵後列,
		敵弱者,
		敵前列範囲,
		敵後列範囲,
		COUNT
	};

	//スキルタグ
	enum class ASkillType
	{
		//基本タグ
		攻撃,
		回復,
		バフ,
		デバフ,
		//範囲
		単体,
		範囲,
		暗殺,

		物理,
		魔法,

		斬撃,
		打撃,
		射撃,
		火炎,
		氷雪,
		雷撃,
		//参照ステータス
		STR,
		INT,
		DEX,
		指定なし,
		COUNT
	};

	//バフ・デバフ効果
	enum class BuffType
	{
		なし,
		＠バフ・デバフ,
		与ダメ増減,//割合増減
		被ダメ軽減,//割合増減
		物防,//+数値
		魔防,//+数値
		Str,//+数値
		Dex,//+数値
		Int,//+数値
		命中,//+数値
		回避,//+数値
		挑発,//ターゲットになる
		隠密,//ターゲットから外れる
		速度,//CT速度割合増減
		かばわれ,//数値の隊列の味方にかばわれる、一回かばうと残り時間０
		異常バリア,//状態異常を無効化する、一回無効化すると残り時間０
		両方バリア,//物理/魔法両方に対するバリア
		物理バリア,//物理ダメージを数値分吸収
		魔法バリア,//魔法ダメージを数値分吸収
		再生,//時間経過で回復
		祝福,//回復効果低減 or 増加
		復活,//気絶しても回復する
		分身,//スキルのHit数が増加、攻撃を受けると回避して分身消滅

		//デメリットのみのやつ
		＠状態異常,
		出血,//行動時ダメージ
		猛毒,//一定時間毎にダメージ
		スタン,//一定値CTが減少
		麻痺,//物理スキルの速度低下、回避減少？
		沈黙,//魔法スキルの速度低下
		暗闇,//物理スキルの命中低下、回避減少
		混乱,//攻撃対象が敵味方ランダムに
		石化,//行動不能、回復が遅い、回避０
		睡眠,//行動不能、ダメージで回復、回避０
		呪い,//与えたダメージが自分に跳ね返ってくる
		宣告,//時間経過で気絶
		COUNT
	};

	//追加効果
	enum class ASkillSubType
	{
		//実質bool値
		なし,
		必中,
		隠れる無視,
		挑発無視,
		異常回復,
		気絶回復,

		//エディタ上は-100～100の整数、ゲーム上は-1.0～1.0のdouble
		防御貫通,//1で完全無視
		回避貫通,
		超過回復,//最大HPを超えた分バリアを貼る
		ダメージ幅,//1で0～2.0倍
		バフ延長,//-1で解除、1で持続倍増
		デバフ延長,//-1で解除、1で持続倍増
		バフ強化,//-0.5で半減、1で倍増
		デバフ強化,//-0.5で半減、1で倍増
		先制,//1で戦闘開始時100%
		吸収,//1で与えたダメージと同じだけ回復
		コスト,//1で残りHPの100%消費
		全力,//自分のHPが100%なら威力増加
		窮地,//自分のHPが30%以下なら威力が増加
		処刑,
		挑発追撃,
		異常追撃,
		反撃,//削除予定
		COUNT
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

		EffectAnimeType 戦闘エフェクト = EffectAnimeType::斬;

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

		struct 追加効果
		{
			追加効果(ASkillSubType 種類 , int 値):
				種類(種類),
				値(値)
			{}

			ASkillSubType 種類;
			int 値;
		};
		struct 補助効果
		{
			BuffType 種類;
			int 基礎値;
			int 反映率;
			int 確率;
			int 持続;

			補助効果( BuffType 種類,int 基礎値,int 反映率,int 確率,int 持続 ):
				種類(種類),
				基礎値(基礎値),
				反映率(反映率),
				確率(確率),
				持続(持続)
			{}

		};

		std::vector<追加効果> 追加効果;
		std::vector<補助効果> 補助効果;

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

				file_data.Read(it.戦闘エフェクト);

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
		const ActiveSkill* base;

		EffectAnimeType 戦闘エフェクト;

		ASkillTarget 対象;
		int 範囲 = 1;

		StatusType 依存ステータス;
		FormationType 適正隊列;
		ASkillType 種類;

		DamageType 属性;

		ItemType 装備種 = ItemType::すべて;

		int Hit数 = 1;//多段ヒット数
		double 命中 = 1.0;

		double 基礎効果 = 0;//固定ダメージ
		double 反映率 = 0;

		double 会心率 = 0.05;
		double 会心倍率 = 1.5;

		//バフ効果
		EnumArray<double, BuffType> バフ基礎値;
		EnumArray<double, BuffType> バフ反映率;
		EnumArray<double, BuffType> バフ確率;
		EnumArray<int, BuffType> バフ持続;

		//追加効果など
		EnumArray<double, ASkillSubType> 追加効果;
		bool is自己バフ = false;//バフ効果の対象が命中した相手でなく自分になる
		double 減衰率 = 1.0;//2番目以降のターゲットへのダメージ倍率

		//ASkillにないやつ
		double バフ効果補正 = 1.0;
		double バフ持続補正 = 1.0;

		ASkillEffect(const ActiveSkill* スキルベース):
			base(スキルベース)
		{

		}


	};
}