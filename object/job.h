//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*ギルメンのクラス*/
	class Job
	{
	private:
	public:
		static std::vector<Job> data;

		Job(JobNo 職種,std::string 名前,std::string 説明,UnitImageType 見た目)
		{
			this->職種 = 職種;
			this->名前 = 名前;
			this->説明 = 説明;
			this->見た目 = 見た目;
		}

		void Set(int Hp,int Str,int Dex,int Int,int 物防,int 魔防 , int 命中 , int 回避)
		{
			this->Hp = Hp;
			this->Str = Str;
			this->Int = Int;
			this->Dex = Dex;
			this->防御[DamageType::物理] = 物防;
			this->防御[DamageType::魔法] = 魔防;
			this->命中 = 命中;
			this->回避 = 回避;
		}

		void SetSkill(std::vector<int> rate)
		{
		}

		static void SetSkill(int ID,int ファイター,int ナイト,int レンジャー,int ウィザード,int クレリック)
		{
			Job::data[0].PSkillRate[ID] = ファイター;
			Job::data[1].PSkillRate[ID] = ナイト;
			Job::data[2].PSkillRate[ID] = レンジャー;
			Job::data[3].PSkillRate[ID] = ウィザード;
			Job::data[4].PSkillRate[ID] = クレリック;
		}

		void SetItemASkill(int 武器, int 防具, int スキルA, int スキルB)
		{
			初期装備[0] = 武器;
			初期装備[1] = 防具;
			Aスキル[0] = スキルA;
			Aスキル[1] = スキルB;
		}

		JobNo 職種;

		std::string 名前;
		std::string 説明;
		UnitImageType 見た目;
		int 初期装備[2];
		int Aスキル[2];

		//基礎ステータスーLvでスケーリングする
		int Hp,Str, Int, Dex;
		EnumArray<int, DamageType> 防御;
		int 命中, 回避;

		//他ステータス
		int PSkillRate[CV::Pスキル種];//各スキルの習得確率
	};


	void LoadWarkerClass()
	{
		Job::data.emplace_back(0, "ファイター", "STR/DEX物理",UnitImageType::傭兵);//90
		Job::data.emplace_back(1, "ナイト", "STRタンク",UnitImageType::重装);//78
		Job::data.emplace_back(2, "レンジャー", "DEX物理",UnitImageType::レンジャー);//66
		Job::data.emplace_back(3, "ウィザード", "INT魔法",UnitImageType::魔女);//59
		Job::data.emplace_back(4, "クレリック", "INT回復",UnitImageType::司祭);//99

		Job::data[0].Set(120, 13, 12, 5, 5 , 5 , 5 , 5);
		Job::data[1].Set(150, 11, 10, 7, 15, 10, 0, 0);
		Job::data[2].Set( 90,  8, 14,10, 3, 3, 10, 10);
		Job::data[3].Set( 80,  5,  9,15, 0, 5,  0, 5);
		Job::data[4].Set(120, 10,  7,12, 6, 8,  0, 0);

		Job::data[0].SetItemASkill(1, 6, 22 , 23);
		Job::data[1].SetItemASkill(3, 6, 24, 25);
		Job::data[2].SetItemASkill(2, 7, 26, 27);
		Job::data[3].SetItemASkill(5, 8, 28, 29);
		Job::data[4].SetItemASkill(4, 8, 30, 31);

		///1全然出ない、5そこそこ出る、10出やすい

		//基礎ステ////// フ/ナ/レ/ウ/ク
		Job::SetSkill( 0, 0, 0, 0, 0, 0);//無し
		Job::SetSkill( 1, 5, 8, 4, 3, 5);//HP
		Job::SetSkill( 2, 4, 7, 3, 2, 4);
		Job::SetSkill( 3, 3, 6, 2, 0, 3);
		Job::SetSkill( 4, 8, 5, 0, 0, 4);//STR
		Job::SetSkill( 5, 7, 3, 0, 0, 2);
		Job::SetSkill( 6, 6, 1, 0, 0, 0);
		Job::SetSkill( 7, 4, 0, 8, 0, 0);//DEX
		Job::SetSkill( 8, 3, 0, 7, 0, 0);
		Job::SetSkill( 9, 2, 0, 6, 0, 0);
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
		Job::SetSkill(48, 0, 5, 0, 0,10);//戦後回復
		Job::SetSkill(49, 0, 0, 0, 0, 7);
		Job::SetSkill(50, 5,10, 0, 0, 0);
		Job::SetSkill(51, 0, 0, 5, 5, 0);//魔物素材+
		Job::SetSkill(52, 0, 0, 3, 3, 0);
		Job::SetSkill(53, 0, 0, 5, 5, 0);
		Job::SetSkill(54, 0, 0, 3, 3, 0);
		Job::SetSkill(55, 0, 0,10, 0, 0);//収穫素材+
		Job::SetSkill(56, 0, 0, 6, 0, 0);
		Job::SetSkill(57, 0, 0,10, 0, 0);
		Job::SetSkill(58, 0, 0, 6, 0, 0);
		Job::SetSkill(59,10, 0, 0, 0, 0);//特殊系
		Job::SetSkill(60, 0,10, 0, 0, 0);
		Job::SetSkill(61, 0, 0,10, 0, 0);
		Job::SetSkill(62, 0, 0, 0,10, 0);
		Job::SetSkill(63, 0, 0, 0, 0,10);



		
	}

	std::vector<Job> Job::data;
}