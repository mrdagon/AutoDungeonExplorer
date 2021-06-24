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

		//
		void 登録(int id , ID_Job ジョブ , int Lv , std::string 名前)
		{
			this->ID = id;
			this->Lv = Lv;
			this->is登録済み = true;
			this->職業 = &ExplorerClass::data[ジョブ];
			this->名前 = 名前;

			int job = (int)ジョブ;
			image = ExplorerClass::data[job].ちびimage;

			装備[0] = ExplorerClass::data[job].初期装備[0];
			装備[1] = ExplorerClass::data[job].初期装備[1];
			装備[2] = ExplorerClass::data[job].初期装備[2];

			スキルポイント = Lv + 10;
			経験値 = 0;

			Aスキル.resize(CV::最大Aスキル数);

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				Aスキル[a] = ExplorerClass::data[job].初期Aスキル[a];
				装備Aスキル[a] = ExplorerClass::data[job].初期Aスキル[a];
			}


			スキルリセット(0);

			static std::vector<Battler*> 仮メンバー;

			//基礎ステータス/装備/常時パッシブによる補正効果
			基礎ステータス計算();
			基礎Pスキル補正(仮メンバー,仮メンバー);
		}

		bool is特殊人材;//(解雇不可、イベントに絡む等)

		void スキルリセット(int 低下Lv)
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
				it = CV::スキル未予約;
			}

			if (低下Lv > 0)
			{
				経験値 = 0;
				Lv = std::max(1, Lv - 低下Lv);
			}

			スキルポイント = Lv + 0;
		}

		//●人事関連
		int ID;//guildのvector配列内のindex
		bool is登録済み;

		//●固定ステータス
		std::string 名前;
		ExplorerClass* 職業;
		
		//●スキル習得状況
		std::array<int, CV::上限Aスキル種類> 習得AスキルLv;
		std::array<int, CV::上限Pスキル種類> 習得PスキルLv;

		int スキル習得予約[CV::最大スキル予約数];//0は未予約 -はAスキル、+はPスキル

		//●Lvアップ時等更新ステータス
		int Lv = 1;
		double 経験値 = 0;
		int スキルポイント;//余っているスキルポイント

		Item* 装備[CV::装備部位数];//0が武器、1が防具、2がユニーク

		ActiveSkill* 装備Aスキル[CV::最大Aスキル数];
		//ActiveSkill* 装備Aスキルボス[CV::最大Aスキル数];

		int 探検前Lv;
		int 探検前経験値;

		//UI表示用
		int レベルアップ演出 = -1;
		bool isスキル習得演出;

		//●再計算ステータス、戦闘以外

		/*パーティ非所属キャラ用ステータス計算*/
		int Get要求経験値()
		{
			return (2 + Lv * Lv) * CV::要求経験値;
		}

		double Get経験値率()
		{
			return (double)探検前経験値 / Get要求経験値();
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
			レベルアップ演出 = true;

			レベルアップ判定();//2レベ以上上がった時用の再起呼び出し

		}

		//基礎ステータス計算
		//パーティパッシブがあるので、Pスキルは補正は別関数
		void 基礎ステータス計算()
		{
			//とりあえずモンスターはLvで12%で成長、味方はLvで10%成長
			基礎ステ[StatusType::HP] = int(職業->ステ[StatusType::HP] * (9 + Lv) / 10);
			基礎ステ[StatusType::力] = int(職業->ステ[StatusType::力] * (9 + Lv) / 10);
			基礎ステ[StatusType::技] = int(職業->ステ[StatusType::技] * (9 + Lv) / 10);
			基礎ステ[StatusType::知] = int(職業->ステ[StatusType::知] * (9 + Lv) / 10);

			基礎ステ[StatusType::命中] = int(職業->ステ[StatusType::命中] * (49 + Lv) / 50);
			基礎ステ[StatusType::回避] = int(職業->ステ[StatusType::回避] * (49 + Lv) / 50);

			基礎ステ[StatusType::物防] = int(職業->ステ[StatusType::物防] * (29 + Lv) / 30);
			基礎ステ[StatusType::魔防] = int(職業->ステ[StatusType::魔防] * (29 + Lv) / 30);

			基礎ステ[StatusType::会心] = 職業->ステ[StatusType::会心];

			Reset一時補正ステータス();

			//装備品補正
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

			//Aスキルセット
			Aスキル.resize(CV::最大Aスキル数);
			AスキルLv.resize(CV::最大Aスキル数);
			必要クールダウン.resize(CV::最大Aスキル数);

			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				Aスキル[a] = 装備Aスキル[a];
				AスキルLv[a] = 習得AスキルLv[Aスキル[a]->ID];
				必要クールダウン[a] = Aスキル[a]->クールタイム;
			}

			//PスキルSの更新
			Pスキル.clear();
			//習得済みパッシブをpush
			for (int a = 0; a < CV::上限Pスキル種類; a++)
			{
				if (習得PスキルLv[a] > 0)
				{
					Pスキル.push_back( &PassiveSkill::data[a] );
					PスキルLv.push_back(習得PスキルLv[a]);
				}
			}

			//装備品パッシブ
			for (int a = 0; a < CV::装備部位数; a++)
			{
				for (int b = 0; b < 1; b++)
				{
					if (装備[a]->Pスキル[b] != nullptr && 装備[a]->Pスキル[b]->ID != 0)
					{
						Pスキル.push_back(装備[a]->Pスキル[b]);
						PスキルLv.push_back(装備[a]->PスキルLv[b]);
					}
				}
			}

			現在HP = 補正ステ[StatusType::HP];

			戦闘後回復 = Game::自動回復;
			レア素材剥取補正 = 0.0;
			レア素材収集補正 = 0.0;
			素材剥取量 = 0.0;
			素材収集量 = 0.0;

			//
			探検前Lv = Lv;
			探検前経験値 = (int)経験値;
			レベルアップ演出 = -1;
			isスキル習得演出 = false;		
		}
		
		void 探索開始()
		{
			//経験値の獲得、素材の獲得等の処理
			レベルアップ演出 = -1;
		}

		void 探索終了()
		{
			//経験値の獲得、素材の獲得等の処理

		}

		void On気絶()
		{
			
		}

		bool 装備強化(int 装備スロット)
		{
			return true;
		}

		bool 素材チェック(int 装備スロット)
		{
			return true;
		}

		//スキル画面用
		enum class Resultスキル強化
		{
			強化,
			予約,
			予約失敗,
			解除,
			解除失敗
		};

		int Pスキル予約Lv(int スキルID)
		{
			int 現在Lv = 習得PスキルLv[スキルID];
			for (int i = 0; i < CV::最大スキル予約数; i++)
			{
				if (スキル習得予約[i] == スキルID)
				{
					現在Lv++;
				}
			}
			return 現在Lv;
		}

		int Aスキル予約Lv(int スキルID)
		{
			int 現在Lv = 習得AスキルLv[スキルID];
			for (int i = 0; i < CV::最大スキル予約数; i++)
			{
				if (スキル習得予約[i] == -スキルID)
				{
					現在Lv++;
				}
			}
			return 現在Lv;
		}

		Resultスキル強化 Pスキル予約(int スキルID)
		{
			//現在Lvと合計予約数を計算
			int 現在Lv = Pスキル予約Lv(スキルID);

			//合計が5以上なら強化不可
			if (現在Lv >= 5) { return Resultスキル強化::予約失敗; }

			for (int i = 0; i < CV::最大スキル予約数; i++)
			{
				if (スキル習得予約[i] == 0)
				{
					スキル習得予約[i] = スキルID;
					break;
				}
			}
		}

		Resultスキル強化 Aスキル予約(int スキルID)
		{
			//現在Lvと合計予約数を計算
			int 現在Lv = Aスキル予約Lv(スキルID);

			//合計が5以上なら強化不可
			if (現在Lv >= 5) { return Resultスキル強化::予約失敗; }

			for (int i = 0; i < CV::最大スキル予約数; i++)
			{
				if (スキル習得予約[i] == 0)
				{
					スキル習得予約[i] = -スキルID;
					break;
				}
			}
		}

		Resultスキル強化 Pスキル解除(int スキルID)
		{
			int index = -1;

			for (int i = CV::最大スキル予約数 - 1; i >= 0; i--)
			{
				if (スキル習得予約[i] == スキルID)
				{
					スキル予約解除(i);
					return Resultスキル強化::解除;
				}
			}

			return Resultスキル強化::解除失敗;
		}

		Resultスキル強化 Aスキル解除(int スキルID)
		{
			int index = -1;
			for (int i = CV::最大スキル予約数 - 1; i >= 0; i--)
			{
				if (スキル習得予約[i] == -スキルID)
				{
					スキル予約解除(i);
					return Resultスキル強化::解除;
				}
			}

			return Resultスキル強化::解除失敗;			
		}

		int 操作_装備Aスキル変更(int スロット, ActiveSkill* スキル)
		{
			for (int i = 0; i < CV::最大Aスキル数; i++)
			{
				if ( 装備Aスキル[i] == スキル)
				{
					装備Aスキル[i] = 装備Aスキル[スロット];
					装備Aスキル[スロット] = スキル;
					return i;
				}
			}

			装備Aスキル[スロット] = スキル;
			return スロット;
		}

		void スキル予約解除(int 予約ID)
		{
			for (int i = 予約ID ; i < CV::最大スキル予約数 - 1; i++)
			{
				スキル習得予約[i] = スキル習得予約[i+1];
			}
			スキル習得予約[CV::最大スキル予約数 - 1] = CV::スキル未予約;

		}

		void 操作_キースキル習得(int スキルID)
		{

		}

		void 操作_スキルリセット()
		{
			int 低下Lv = Lv / 10 + 2;
			if (低下Lv <= 2) { 低下Lv = 0; }
			スキルリセット(低下Lv);
		}
	};
}