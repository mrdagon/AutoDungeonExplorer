//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*探索者ベースクラス*/
	class Explorer : public Battler
	{
	public:
		Explorer()
		{
			気絶時SE = SE::味方気絶;
			is味方 = true;
		}

		void Make(int id , ID_Job ジョブ , int Lv , std::string 名前)
		{
			this->ID = id;
			this->Lv = Lv;
			this->職業 = &ExplorerClass::data[ジョブ];
			this->名前 = 名前;

			int job = (int)ジョブ;
			image = ExplorerClass::data[job].ちびimage;

			装備[0] = ExplorerClass::data[job].初期装備[0];
			装備[1] = ExplorerClass::data[job].初期装備[1];
			装備[2] = ExplorerClass::data[job].初期装備[2];

			スキルポイント = Lv + 10;
			経験値 = 0;

			アクティブスキル[0] = ExplorerClass::data[job].初期Aスキル[0];
			アクティブスキル[1] = ExplorerClass::data[job].初期Aスキル[1];
			アクティブスキル[2] = ExplorerClass::data[job].初期Aスキル[2];
			アクティブスキル[3] = ExplorerClass::data[job].初期Aスキル[3];

			スキルリセット(0);

			static std::vector<Battler*> 仮メンバー;

			//基礎ステータス/装備/常時パッシブによる補正効果
			基礎ステータス計算();
			基礎Pスキル補正(仮メンバー,仮メンバー);
		}

		bool is特殊人材;//(解雇不可、イベントに絡む等)

		void スキルリセット(int 低下レベル)
		{
			for (auto& it : AスキルLv)
			{
				it = 0;
			}
			for (auto& it : PスキルLv)
			{
				it = 0;
			}
			for (auto& it : スキル習得予約)
			{
				it = 0;
			}

			経験値 = 0;
			Lv = std::max(1,Lv - 低下レベル);

			スキルポイント = Lv + 10;
		}

		//●人事関連
		int ID;//guildのvector配列内のindex

		//●固定ステータス
		std::string 名前;
		ExplorerClass* 職業;
		
		//●スキル習得状況
		std::array<int, CV::最大Aスキル種類> AスキルLv;
		std::array<int, CV::最大Pスキル種類> PスキルLv;
		int スキル習得予約[100];//0は未予約 -はAスキル、+はPスキル

		//●Lvアップ時等更新ステータス
		int Lv;
		double 経験値 = 0;
		int スキルポイント;//余っているスキルポイント

		Item* 装備[CV::装備部位数];//0が武器、1が防具、2がユニーク

		ActiveSkill* 装備Aスキル通常[CV::最大Aスキル数];
		ActiveSkill* 装備Aスキルボス[CV::最大Aスキル数];

		int 探検前Lv;
		int 探検前経験値;

		//UI表示用
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

			レベルアップ判定();//2レベ以上上がった時用の再起呼び出し

		}

		//パッシブ無しの基礎ステータス計算
		void 基礎ステータス計算()
		{
			基礎ステ[StatusType::HP] = int(職業->ステ[StatusType::HP] * (10 + Lv) / 10.0);
			基礎ステ[StatusType::力] = int(職業->ステ[StatusType::力] * (10 + Lv) / 10);
			基礎ステ[StatusType::技] = int(職業->ステ[StatusType::技] * (10 + Lv) / 10);
			基礎ステ[StatusType::知] = int(職業->ステ[StatusType::知] * (10 + Lv) / 10);

			基礎ステ[StatusType::命中] = 職業->ステ[StatusType::命中];
			基礎ステ[StatusType::回避] = 職業->ステ[StatusType::回避];

			基礎ステ[StatusType::物防] = 職業->ステ[StatusType::物防];
			基礎ステ[StatusType::魔防] = 職業->ステ[StatusType::魔防];

			基礎ステ[StatusType::会心] = 職業->ステ[StatusType::会心];

			Reset補正ステータス();

			for (int a = 0; a < CV::装備部位数; a++)
			{
				補正ステ[StatusType::HP] += 装備[a]->ステ[StatusType::HP];
				補正ステ[StatusType::力] += 装備[a]->ステ[StatusType::力];
				補正ステ[StatusType::技] += 装備[a]->ステ[StatusType::技];
				補正ステ[StatusType::知] += 装備[a]->ステ[StatusType::知];

				補正ステ[StatusType::命中] += 装備[a]->ステ[StatusType::命中];
				補正ステ[StatusType::回避] += 装備[a]->ステ[StatusType::回避];

				補正ステ[StatusType::物防] += 装備[a]->ステ[StatusType::物防];
				補正ステ[StatusType::魔防] += 装備[a]->ステ[StatusType::魔防];
				補正ステ[StatusType::会心] += 装備[a]->ステ[StatusType::会心];
			}

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
			}

			//PスキルSの更新
			パッシブスキル.clear();
			//習得済みパッシブ

			//装備品パッシブ
			for (int a = 0; a < CV::装備部位数; a++)
			{
				for ( auto& it : 装備[a]->Pスキル )
				{
					if (it != nullptr && it->ID != 0)
					{
						パッシブスキル.push_back(it);
					}
				}
			}
			
			//製造能力(仮)
			現在HP = 補正ステ[StatusType::HP];

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