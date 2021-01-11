//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ギルメンのクラス*/
	class Job
	{
	private:
	public:
		inline static std::vector<Job> data;

		Job(JobType 職種,std::string 名前,std::string 説明,UnitImageType 見た目)
		{
			this->職種 = 職種;
			this->名前 = 名前;
			this->説明 = 説明;
			this->Img = &MJob::ちび[職種];

			初期装備[0] = &Item::data[0];
			初期装備[1] = &Item::data[0];
			初期装備[2] = &Item::data[0];

			ResetP習得スキル();
			SetA習得スキル();
		}

		void Set(int Hp,int Str,int Dex,int Int,int 物防,int 魔防 , int 命中 , int 回避)
		{
			this->ステ[StatusType::生命] = Hp;
			this->ステ[StatusType::筋力] = Str;
			this->ステ[StatusType::知力] = Int;
			this->ステ[StatusType::技力] = Dex;
			this->ステ[StatusType::命中] = 命中;
			this->ステ[StatusType::回避] = 回避;

			this->ステ[StatusType::物防] = 物防;
			this->ステ[StatusType::魔防] = 魔防;
		}

		void SetSkill(std::vector<int> rate)
		{
		}

		static void SetSkill(int ID,int ファイター,int ナイト,int レンジャー,int ウィザード,int クレリック)
		{
			if (ファイター > 0) { Job::data[0].SetP習得スキル(ID); }
			if (ナイト> 0) { Job::data[1].SetP習得スキル(ID); }
			if (レンジャー > 0) { Job::data[2].SetP習得スキル(ID); }
			if (ウィザード > 0) { Job::data[3].SetP習得スキル(ID); }
			if (クレリック > 0) { Job::data[4].SetP習得スキル(ID); }

		}

		void SetP習得スキル(int ID)
		{
			for (int a = 0; a < CV::最大Pスキル習得リスト; a++)
			{
				if (習得Pスキル[a] == nullptr)
				{
					習得Pスキル[a] = &PassiveSkill::data[ID];
					break;
				}
			}
		}

		void SetItemASkill(int 武器, int 防具, int スキルA, int スキルB ,int スキルC ,int スキルD)
		{
			初期装備[0] = &Item::data[武器];
			初期装備[1] = &Item::data[防具];
			初期装備[2] = &Item::data[0];
			初期Aスキル[0] = &ActiveSkill::data[スキルA];
			初期Aスキル[1] = &ActiveSkill::data[スキルB];
			初期Aスキル[2] = &ActiveSkill::data[スキルC];
			初期Aスキル[3] = &ActiveSkill::data[スキルD];
		}

		void SetA習得スキル()
		{
			習得Aスキル[0] = &ActiveSkill::data[22];
			習得Aスキル[1] = &ActiveSkill::data[23];
			習得Aスキル[2] = &ActiveSkill::data[24];
			習得Aスキル[3] = &ActiveSkill::data[25];
			習得Aスキル[4] = &ActiveSkill::data[26];
			習得Aスキル[5] = &ActiveSkill::data[27];
			習得Aスキル[6] = &ActiveSkill::data[28];
			習得Aスキル[7] = &ActiveSkill::data[29];
		}

		void ResetP習得スキル()
		{
			for (auto& it : 習得Pスキル)
			{
				it = nullptr;
			}
		}

		JobType 職種;

		std::string 名前;
		std::string 概説 = "説明文- 未設定";
		std::string 説明;
		ImagePack *Img;

		ItemType 武器種;
		ItemType 防具種;
		Item* 初期装備[CV::装備部位数];
		ActiveSkill* 初期Aスキル[CV::最大Aスキル数];//初期スキル
		
		//キャラクリ
		ActiveSkill* 習得Aスキル[CV::最大Aスキル習得リスト];
		PassiveSkill* 習得Pスキル[CV::最大Pスキル習得リスト];

		//基礎ステータスーLvでスケーリングする
		//int Hp;
		EnumArray<int, StatusType> ステ;
		//int 命中, 回避;

		static void LoadData()
		{
			Job::data.emplace_back(JobType::スレイヤー, "スレイヤー", "STR/DEX物理", UnitImageType::傭兵);//90
			Job::data.emplace_back(JobType::ガーディアン, "ガーディアン", "STRタンク", UnitImageType::重装);//78
			Job::data.emplace_back(JobType::デッドアイ, "デッドアイ", "DEX物理", UnitImageType::レンジャー);//66
			Job::data.emplace_back(JobType::エレメンタリスト, "エレメンタリスト", "INT魔法", UnitImageType::魔女);//59
			Job::data.emplace_back(JobType::メディック, "メディック", "INT回復", UnitImageType::司祭);//99

			Job::data.emplace_back(JobType::オカルティスト, "オカルティスト", "INT回復", UnitImageType::おじいさん);//99
			Job::data.emplace_back(JobType::グラディエーター, "グラディエータ", "INT回復", UnitImageType::おじいさん);//99
			Job::data.emplace_back(JobType::シノビ, "シノビ", "INT回復", UnitImageType::おじいさん);//99
			Job::data.emplace_back(JobType::バーサーカー, "バーサーカー", "INT回復", UnitImageType::おじいさん);//99
			Job::data.emplace_back(JobType::トリックスター, "トリックスター", "INT回復", UnitImageType::おじいさん);//99
			Job::data.emplace_back(JobType::ミスティック, "ミスティック", "INT回復", UnitImageType::おじいさん);//99
			Job::data.emplace_back(JobType::カートグラファ, "カートグラファ", "INT回復", UnitImageType::おじいさん);//99

			Job::data[0].概説 = "前衛 : 物理アタッカー";
			Job::data[0].説明 = "大剣を振るう戦士\n近接戦闘のエキスパートで、\n多数の敵をまとめて切り伏せる\n豪快な剣技を扱う";

			Job::data[1].概説 = "前衛 ： 防御型タンク";
			Job::data[1].説明 = "盾となり味方を守護する\n最前線で全ての攻撃を受けきる\n全職業でも随一のタフさを持つ";

			Job::data[2].概説 = "後衛 : 射撃アタッカー";
			Job::data[2].説明 = "弓の名手\n狙いを付けた獲物は逃さず\n一撃は必殺の射撃で仕留める";

			Job::data[3].概説 = "後衛 : 魔法アタッカー";
			Job::data[3].説明 = "元素魔術の使い手\n物理攻撃が効かない魔物も\n魔術によって打ち倒す事が出来る";

			Job::data[4].概説 = "中衛 : ヒーラー";
			Job::data[4].説明 = "回復の術に長けた神秘家\n回復に特化し、攻撃力は期待出来ないが\nパーティの生存力を大きく引き上げる";


			Job::data[0].Set(90, 13, 11, 5, 5, 5, 5, 5);
			Job::data[1].Set(100, 11, 10, 7, 15, 10, 0, 0);
			Job::data[2].Set(65, 8, 16, 10, 3, 3, 10, 10);
			Job::data[3].Set(60, 5, 9, 17, 0, 5, 0, 5);
			Job::data[4].Set(90, 10, 7, 12, 6, 8, 0, 0);

			Job::data[0].SetItemASkill(1, 7, 1, 2, 22, 23);
			Job::data[1].SetItemASkill(4, 7, 7, 8, 24, 25);
			Job::data[2].SetItemASkill(3, 8, 5, 6, 26, 27);
			Job::data[3].SetItemASkill(5, 9, 9, 10, 28, 29);
			Job::data[4].SetItemASkill(6, 9, 11, 12, 30, 31);

			for (auto& it : Job::data)
			{
				it.武器種 = it.初期装備[0]->種類;
				it.防具種 = it.初期装備[1]->種類;
			}


			///1全然出ない、5そこそこ出る、10出やすい

			//基礎ステ////// フ/ナ/レ/ウ/ク
			Job::SetSkill(0, 0, 0, 0, 0, 0);//無し
			Job::SetSkill(1, 5, 8, 4, 3, 5);//HP
			Job::SetSkill(2, 4, 7, 3, 2, 4);
			Job::SetSkill(3, 3, 6, 2, 0, 3);
			Job::SetSkill(4, 8, 5, 0, 0, 4);//STR
			Job::SetSkill(5, 7, 3, 0, 0, 2);
			Job::SetSkill(6, 6, 1, 0, 0, 0);
			Job::SetSkill(7, 4, 0, 8, 0, 0);//DEX
			Job::SetSkill(8, 3, 0, 7, 0, 0);
			Job::SetSkill(9, 2, 0, 6, 0, 0);
			Job::SetSkill(10, 0, 4, 0, 8, 7);//INT
			Job::SetSkill(11, 0, 2, 0, 7, 6);
			Job::SetSkill(12, 0, 0, 0, 6, 5);
			Job::SetSkill(13, 5, 0, 0, 0, 0);//剣、斧、弓、魔、神、盾
			Job::SetSkill(14, 5, 0, 0, 0, 0);
			Job::SetSkill(15, 5, 0, 0, 0, 0);
			Job::SetSkill(16, 5, 0, 0, 0, 0);
			Job::SetSkill(17, 0, 0, 5, 0, 0);
			Job::SetSkill(18, 0, 0, 5, 0, 0);
			Job::SetSkill(19, 0, 0, 0, 5, 0);
			Job::SetSkill(20, 0, 0, 0, 5, 0);
			Job::SetSkill(21, 0, 0, 0, 0, 5);
			Job::SetSkill(22, 0, 0, 0, 0, 5);
			Job::SetSkill(23, 0, 5, 0, 0, 0);
			Job::SetSkill(24, 0, 5, 0, 0, 0);
			Job::SetSkill(25, 0, 5, 0, 0, 0);
			Job::SetSkill(26, 3, 5, 0, 0, 3);//物防魔防回避命中
			Job::SetSkill(27, 0, 3, 0, 0, 1);
			Job::SetSkill(28, 0, 5, 0, 3, 3);
			Job::SetSkill(29, 0, 3, 0, 0, 1);
			Job::SetSkill(30, 3, 0, 7, 0, 0);
			Job::SetSkill(31, 0, 0, 5, 0, 0);
			Job::SetSkill(32, 5, 0, 7, 0, 0);
			Job::SetSkill(33, 0, 0, 5, 0, 0);
			Job::SetSkill(34, 5, 0, 5, 0, 0);//物理スキル強化
			Job::SetSkill(35, 3, 0, 3, 0, 0);
			Job::SetSkill(36, 5, 0, 5, 0, 0);
			Job::SetSkill(37, 3, 0, 3, 0, 0);
			Job::SetSkill(38, 0, 0, 0, 5, 3);//魔法スキル強化
			Job::SetSkill(39, 0, 0, 0, 3, 1);
			Job::SetSkill(40, 0, 0, 0, 5, 3);
			Job::SetSkill(41, 0, 0, 0, 3, 1);
			Job::SetSkill(42, 0, 3, 0, 0, 5);//回復スキル強化
			Job::SetSkill(43, 0, 1, 0, 0, 3);
			Job::SetSkill(44, 0, 3, 0, 0, 5);
			Job::SetSkill(45, 0, 1, 0, 0, 3);
			Job::SetSkill(46, 5, 5, 5, 5, 5);//奥義強化
			Job::SetSkill(47, 3, 3, 3, 3, 3);
			Job::SetSkill(48, 0, 5, 0, 0, 10);//戦後回復
			Job::SetSkill(49, 0, 0, 0, 0, 7);
			Job::SetSkill(50, 5, 10, 0, 0, 0);
			Job::SetSkill(51, 0, 0, 5, 5, 0);//魔物素材+
			Job::SetSkill(52, 0, 0, 3, 3, 0);
			Job::SetSkill(53, 0, 0, 5, 5, 0);
			Job::SetSkill(54, 0, 0, 3, 3, 0);
			Job::SetSkill(55, 0, 0, 10, 0, 0);//収穫素材+
			Job::SetSkill(56, 0, 0, 6, 0, 0);
			Job::SetSkill(57, 0, 0, 10, 0, 0);
			Job::SetSkill(58, 0, 0, 6, 0, 0);
			Job::SetSkill(59, 10, 0, 0, 0, 0);//特殊系
			Job::SetSkill(60, 0, 10, 0, 0, 0);
			Job::SetSkill(61, 0, 0, 10, 0, 0);
			Job::SetSkill(62, 0, 0, 0, 10, 0);
			Job::SetSkill(63, 0, 0, 0, 0, 10);
		}
	};

}