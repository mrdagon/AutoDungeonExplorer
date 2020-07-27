﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*戦闘員ベースクラス*/
	class Hunter : public Fighter
	{
	private:

	public:

		Hunter()
		{
			気絶時SE = SE::味方気絶;
		}

		void Make(int id , ID_Job ジョブ , int Lv , std::string 名前)
		{
			this->ID = id;
			this->Lv = Lv;
			this->職業 = &Job::data[ジョブ];

			所属 = -1;

			this->名前 = 名前;

			int job = (int)ジョブ;
			Img = Job::data[job].Img;

			装備[0] = Job::data[job].初期装備[0];
			装備[1] = Job::data[job].初期装備[1];
			装備[2] = Job::data[job].初期装備[2];

			スキルポイント = Lv + 10;
			経験値 = 0;

			Aスキル[0] = Job::data[job].初期Aスキル[0];
			Aスキル[1] = Job::data[job].初期Aスキル[1];
			Aスキル[2] = Job::data[job].初期Aスキル[2];
			Aスキル[3] = Job::data[job].初期Aスキル[3];

			スキルリセット(0);

			static std::vector<Fighter*> 仮メンバー;

			基礎ステータス計算();
			基礎Pスキル補正(仮メンバー,仮メンバー);
		}

		bool is特殊人材;//(解雇不可、イベントに絡む等)

		void スキルリセット(int 低下レベル)
		{
			for (auto& it : isAスキル習得)
			{
				it = false;
			}
			for (auto& it : isPスキル習得)
			{
				it = false;
			}
			isAスキル習得[0] = true;
			isAスキル習得[1] = true;

			経験値 = 0;
			Lv = std::max(1,Lv - 低下レベル);

			スキルポイント = Lv + 10;
		}

		//●人事関連
		//所属あり、就活中、ニートの３パターン
		int ID;//data配列内のID

		int 所属;//-1なら無所属

		//●固定ステータス
		std::string 名前;
		Job* 職業;

		std::array<bool, CV::最大Aスキル習得リスト> isAスキル習得;
		std::array<bool, CV::最大Pスキル習得リスト> isPスキル習得;
		int Pスキル習得予約ID = -1;//-1なら予約無し

		//●Lvアップ時等更新ステータス
		int Lv;
		double 経験値 = 0;
		int スキルポイント;

		Item* 装備[CV::装備部位数];//0が武器、1が防具、2がユニーク

		//UI表示用
		int 探検前Lv;
		int 探検前経験値;
		bool isレベルアップ演出;
		bool isスキル習得演出;

		//●再計算ステータス、戦闘以外

		/*パーティ非所属キャラ用ステータス計算*/
		int Get要求経験値()
		{
			return (2 + Lv * Lv) * CV::要求経験値;
		}

		void レベルアップ判定()
		{
			int 要求exp = Get要求経験値();

			if ( 要求exp >= 経験値){
				return;
			}

			経験値 -= 要求exp;
			Lv += 1;
			スキルポイント += 1;
			isレベルアップ演出 = true;

			レベルアップ判定();
		}

		//パッシブ無しの基礎ステータス計算
		void 基礎ステータス計算()
		{
			基礎HP = int(職業->Hp * (10 + Lv) / 10.0);
			基礎ステ[StatusType::Str] = int(職業->ステ[StatusType::Str] * (10 + Lv) / 10);
			基礎ステ[StatusType::Dex] = int(職業->ステ[StatusType::Dex] * (10 + Lv) / 10);
			基礎ステ[StatusType::Int] = int(職業->ステ[StatusType::Int] * (10 + Lv) / 10);

			基礎防御[DamageType::物理] = 職業->防御[DamageType::物理];
			基礎防御[DamageType::魔法] = 職業->防御[DamageType::魔法];

			基礎命中 = 職業->命中;
			基礎回避 = 職業->回避;

			Reset補正ステータス();

			for (int a = 0; a < CV::装備部位数; a++)
			{
				最大HP += 装備[a]->追加Hp;
				補正ステ[StatusType::Str] += 装備[a]->追加Str;
				補正ステ[StatusType::Dex] += 装備[a]->追加Dex;
				補正ステ[StatusType::Int] += 装備[a]->追加Int;

				補正防御[DamageType::物理] += 装備[a]->防御[DamageType::物理];
				補正防御[DamageType::魔法] += 装備[a]->防御[DamageType::魔法];

				補正命中 += 装備[a]->命中;
				補正回避 += 装備[a]->回避;
			}

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				クールダウン速度[a] = 1;
				合計クールダウン[a] = 0;
			}

			//PスキルSの更新
			Pスキル.clear();
			//習得済みパッシブ
			for (int a = 0; a < CV::最大Pスキル習得リスト; a++)
			{
				if (isPスキル習得[a] == true )
				{					
					Pスキル.push_back( 職業->習得Pスキル[a] );
				}
			}

			//装備品パッシブ
			for (int a = 0; a < CV::装備部位数; a++)
			{
				for ( auto& it : 装備[a]->Pスキル )
				{
					if (it != nullptr && it->id != 0)
					{
						Pスキル.push_back(it);
					}
				}
			}
			
			//製造能力(仮)
			現在HP = 最大HP;

			戦闘後回復 = Game::自動回復;
			レア素材剥取補正 = 0.0;
			レア素材収集補正 = 0.0;
			素材剥取量 = 0.0;
			素材収集量 = 0.0;

			//エフェクトとログのリセット
			E速度 = 0;//前出たり、ノックバック
			E反転残り = 0;
			E反転時間 = 0;
			E座標 = 0;
			E光強さ = 0;
			Eダメージ時間 = 0;

			//ログ用
			与ダメージログ = 0;
			受ダメージログ = 0;
			回復ログ = 0;

			//
			探検前Lv = Lv;
			探検前経験値 = (int)経験値;
			isレベルアップ演出 = false;
			isスキル習得演出 = false;
		}

		void 探索終了()
		{
			//経験値の獲得、素材の獲得等の処理

		}

		void On気絶()
		{
			
		}
	};
}