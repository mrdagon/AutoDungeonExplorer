//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*味方とモンスターベースクラス*/
	class Battler
	{
	private:
		void Get対象リスト(std::vector<Battler*>& 対象リスト, const std::vector<Battler*>& 対象 , const ASkillEffect& Aスキル, bool is挑発有効 , bool is隠密有効 , FormationType 隊列)
		{
			対象リスト.reserve(6);
			対象リスト.clear();
			
			int 位置 = 0;

			if (is挑発有効)
			{
				if (隊列 == FormationType::前列)
				{
					for (auto& it : 対象)
					{
						if (it->現在HP > 0)
						{
							位置++;
							if( it->バフ[BuffType::マーク].効果 > 0 && 位置 <= Aスキル.範囲) { 対象リスト.push_back(it); }
						}
					}
				} else {
					for (int i = 対象.size()-1;i>=0 ;i--)
					{
						if (対象[i]->現在HP > 0)
						{
							位置++;
							if( 対象[i]->バフ[BuffType::マーク].効果 > 0 && 位置 <= Aスキル.範囲 ) { 対象リスト.push_back(対象[i]); }
						}
					}

				}

				if (対象リスト.size() > 0)
				{
					return;
				}
			}


			for (auto& it : 対象)
			{
				if (it->現在HP > 0) { 対象リスト.push_back(it); }
			}
			//隠密効果により、リストから除外
		}


	public:

		ImagePack *image;
		int パーティID;

		//●基礎ステータス
		std::vector<ActiveSkill*> Aスキル = {nullptr};

		//Pスキルは発動タイミングでコンテナ分ければ多少高速化になるかも
		std::vector<PassiveSkill*> Pスキル;//本人のパッシブ、装備パッシブを格納
		std::vector<int> PスキルLv;

		//●装備とパッシブ補正後
		EnumArray<int, StatusType> 基礎ステ;//Lv、装備補正、常時パッシブ適用後のステータス
		EnumArray<int, StatusType> 補正ステ;//条件付き基礎ステータス上昇P効果適用後、および常時パッシブ計算用の一時ステータス
		EnumArray<int, StatusType> ステ割合上昇;//基礎ステ割合上昇を最後に計算する用

		//特殊ステータス - あとでstatusTypeに追加？
		double 毒耐性 = 1.0;
		double 出血耐性 = 1.0;
		double 回復補正 = 1.0;
		double シールド補正 = 1.0;

		bool is回復超過シールド;
		int 復活 = 0;
		bool isマーク耐性 = false;
		bool is常時マーク = false;
		double 常時ダメージ上昇 = 1.0;
		double 常時ダメージ減少 = 1.0;

		//現在の状態
		int 現在HP = 0;
		int 現在シールド = 0;
		bool is気絶 = false;

		//スキルクールダウン
		int 現在スキルスロット = 0;
		int 現在クールダウン;
		std::vector<int> 必要クールダウン;

		SEType 気絶時SE = SE::敵気絶;

		//一時的なバフ兼デバフ、効果量、効果時間
		int 隊列ID;//0が先頭、以下1.2.3.4...
		bool is味方 = false;

		struct Buff
		{
			double 効果 = 0;
			int 持続 = 0;
		};

		EnumArray<Buff, BuffType> バフ;//一時的なバフとデバフ

		//アニメやエフェクト用変数
		double E速度 = 0;//前出たり、ノックバック速度
		int E反転残り = 0;
		int E反転時間 = 0;
		double E座標 = 0;

		Color E光色;//ダメージ赤、回復緑、補助青
		double E光強さ = 0;

		//ヘルプ表示ログ用
		int 与ダメージログ = 0;
		int 受ダメージログ = 0;
		int 回復ログ = 0;

		//探索スキル効果
		double 戦闘後回復 = 0.0;
		double レア素材剥取補正 = 0.0;
		double レア素材収集補正 = 0.0;
		double 素材剥取量 = 0.0;
		double 素材収集量 = 0.0;

		double 全ランク素材獲得 = 0.0;

		double 経験値補正 = 0.0;

		double 未探索発見補正 = 0.0;
		double 魔物部屋補正 = 0.0;
		double 素材部屋補正 = 0.0;
		double 移動速度補正 = 0.0;
		double 活動時間補正 = 0.0;

		double 財宝部屋補正 = 0.0;
		double レア財宝補正 = 0.0;

		bool isアクセ複数入手 = false;
		double 素材複数入手 = 0.0;

		//攻撃受け側の一時変数
		int Hit数 = 0;

		//ギルメンは基礎ステLv補正+常時パッシブ+装備
		//モンスター基礎ステLv補正+常時パッシブ
		virtual void 基礎ステータス計算() = 0;

		void 基礎Pスキル補正(std::vector<Battler*>& 味方, std::vector<Battler*>& 敵)
		{
			//味方と自分の基礎Pスキルによる補正ステ計算
			for (auto& it : ステ割合上昇)
			{
				it = 0;
			}

			Pスキル条件チェック(PSkillTime::常時, nullptr, 味方, 敵);
			基礎Pスキル反映();
		}

		//常時ステータス上昇パッシブの計算用
		void 基礎Pスキル反映()
		{			//割合増加を反映
			補正ステ[StatusType::HP] += 補正ステ[StatusType::HP] * ステ割合上昇[StatusType::HP] / 100;
			補正ステ[StatusType::パワー] += 補正ステ[StatusType::パワー] * ステ割合上昇[StatusType::パワー] / 100;

			補正ステ[StatusType::防御] += 補正ステ[StatusType::防御] * ステ割合上昇[StatusType::防御] / 100;

			補正ステ[StatusType::命中] += 補正ステ[StatusType::命中] * ステ割合上昇[StatusType::命中] / 100;
			補正ステ[StatusType::回避] += 補正ステ[StatusType::回避] * ステ割合上昇[StatusType::回避] / 100;

			//Pスキル補正を確定
			基礎ステ[StatusType::HP] = 補正ステ[StatusType::HP];
			基礎ステ[StatusType::パワー] = 補正ステ[StatusType::パワー];

			基礎ステ[StatusType::防御] = 補正ステ[StatusType::防御];

			基礎ステ[StatusType::命中] = 補正ステ[StatusType::命中];
			基礎ステ[StatusType::回避] = 補正ステ[StatusType::回避];



		}

		//補正ステータス=基礎ステータスにしてバフ残り時間もリセット
		void Reset一時補正ステータス()
		{
			補正ステ[StatusType::HP] = 基礎ステ[StatusType::HP];
			補正ステ[StatusType::パワー] = 基礎ステ[StatusType::パワー];

			補正ステ[StatusType::防御] = 基礎ステ[StatusType::防御];

			補正ステ[StatusType::命中] = 基礎ステ[StatusType::命中];
			補正ステ[StatusType::回避] = 基礎ステ[StatusType::回避];

			for (auto& it : バフ)
			{
				it.効果 = 0;
				it.持続 = 0;
			}
		}

		//バフ/デバフ補正後ステータス取得
		//ステ補正系バフは全て加算処理
		double Getステ(StatusType ステータス種)
		{
			auto t = BuffType::パワー;

			switch (ステータス種)
			{
				case StatusType::HP: return 補正ステ[ステータス種];//HP一時上昇スキル未実装
				case StatusType::パワー: t = BuffType::パワー; break;
				case StatusType::防御: t = BuffType::防御; break;
				case StatusType::命中: t = BuffType::命中; break;
				case StatusType::回避: t = BuffType::回避; break;
			}

			double value = (バフ[t].持続 > 0) ? 補正ステ[ステータス種] + バフ[t].効果 : 補正ステ[ステータス種];

			if (value < 0) { return 0; }//ステータスはマイナスにはならない

			return value;
		}

		double Get防御(DamageType ダメージ種)
		{
			return 補正ステ[StatusType::防御] + バフ[BuffType::防御].効果;
		}

		void バフ使用(BuffType バフデバフ種 , double 効果量 , int 時間)
		{
			BuffType t = BuffType(バフデバフ種);
			//バフ中のバフ or デバフ中のデバフ、時間、効果量で大きい方に更新
			//バフ中にデバフ or デバフ中にバフ、時間は大きい方から小さい方を引く、効果は時間が長い方になる
			//毒は特殊で持続を更新、効果は加算する

			if (効果量 > 0 )
			{
				if (バフ[t].効果 > 0)
				{
					if (バフデバフ種 == BuffType::猛毒)
					{
						バフ[t].効果 += バフ[t].効果;
					} else {
						バフ[t].効果 = std::max(バフ[t].効果, 効果量);
					}

					バフ[t].持続 = std::max(バフ[t].持続, 時間);
				} else {
					if (バフ[t].持続 > 時間)
					{
						バフ[t].持続 -= 時間;
					} else {
						バフ[t].持続 = 時間 - バフ[t].持続;
						バフ[t].効果 = 効果量;
					}
				}
			}
			else 			
			{
				if (バフ[t].効果 > 0)
				{
					if (バフ[t].持続 > 時間)
					{
						バフ[t].持続 -= 時間;
					} else {
						バフ[t].持続 = 時間 - バフ[t].持続;
						バフ[t].効果 = 効果量;
					}
				} else {
					バフ[t].効果 = std::min(バフ[t].効果, 効果量);
					バフ[t].持続 = std::max(バフ[t].持続, 時間);
				}
			}
		}

		//■エフェクト関係
		void エフェクト更新()
		{
			for (int i = 0; i < Game::ゲームスピード; i++)
			{
				if (E速度 != 0)
				{
					E座標 += E速度;
					E反転残り--;
					if (E反転残り == 0)
					{
						if (E反転時間 > 0)
						{
							E速度 *= -1;
							E反転残り = E反転時間;
							E反転時間 = 0;
						}
						else {
							E座標 = 0;
							E速度 = 0;
						}
					}
				}
			}

			if (E光強さ > 0)
			{
				E光強さ -= 0.05;
				if (E光強さ < 0) { E光強さ = 0; }
			}
		}

		void エフェクト移動(double 移動速度, int 移動時間)
		{
			E速度 = 移動速度;
			E反転残り = 移動時間;
			E反転時間 = 移動時間;
		}

		void エフェクト光(Color 光色)
		{
			E光色 = 光色;
			E光強さ = 1.0;
		}

		void エフェクトダメージ( int ダメージ)
		{
			if (ダメージ == 0)
			{
				Effect::Add文字(TextEffect::TextType::回避, 0, is味方, 隊列ID, パーティID);
			} else if (ダメージ > 0) {
				Effect::Add文字(TextEffect::TextType::ダメージ, ダメージ , is味方 , 隊列ID, パーティID);
			} else {
				Effect::Add文字(TextEffect::TextType::回復, -ダメージ, is味方, 隊列ID, パーティID);
			}
		}

		void エフェクトアニメ(int ID)
		{
			Effect::Addアニメ(ID, is味方, 隊列ID, パーティID);
			//Effect::アニメ[パーティID].emplace_back(ID, is味方, 隊列ID);
		}

		void エフェクトリセット()
		{
			//初期化
			現在スキルスロット = 0;
			現在クールダウン = 0;

			//エフェクト初期化
			E速度 = 0;
			E反転残り = 0;
			E反転時間 = 0;
			E座標 = 0;
			E光強さ = 0;

			//ログ用
			与ダメージログ = 0;
			受ダメージログ = 0;
			回復ログ = 0;
		}

		//■戦闘中処理
		void 戦闘開始(std::vector<Battler*>& 味方, std::vector<Battler*>& 敵)
		{
			エフェクトリセット();

			//バフ初期化
			for (auto& it : バフ) { it.効果 = 0; it.持続 = 0; }

			//パッシブ効果の計算
			Pスキル条件チェック(PSkillTime::戦闘開始時, nullptr, 味方, 敵);
		}

		void ターン経過()
		{
			if (現在HP <= 0) { return ; }

			現在クールダウン += 1;

			//バフ効果時間処理
			for (auto& it : バフ) {
				if (it.持続 > 0)
				{
					it.持続--;
					if (it.持続 <= 0) { it.効果 = 0.0; }
				}
			}
		}

		bool Aスキル使用チェック(std::vector<Battler*>& 味方, std::vector<Battler*>& 敵)
		{
			if (現在HP <= 0) { return false; }

			if (必要クールダウン[現在スキルスロット] <= 現在クールダウン)
			{
				//持続ダメージ
				if (バフ[BuffType::猛毒].持続 > 0)
				{
					現在HP -= バフ[BuffType::猛毒].効果;
					バフ[BuffType::猛毒].効果 /= 2;
				}
				if (バフ[BuffType::出血].持続 > 0)
				{
					現在HP -= バフ[BuffType::出血].効果;
				}


				if (現在HP <= 0) { 
					現在HP = 0;
					return true;
				}

				//スキルの発動
				Aスキル使用(Aスキル[現在スキルスロット], 味方, 敵);
					
				現在クールダウン -= 必要クールダウン[現在スキルスロット];
				現在スキルスロット = (現在スキルスロット+1) % Aスキル.size();

				return true;
			}

			return false;
		}

		void 対象選択(ASkillEffect &Aスキル, std::vector<Battler*>& 対象結果, std::vector<Battler*>&味方,std::vector<Battler*> &敵)
		{
			//攻撃or回復対象を選択
			static std::vector<Battler*> 対象リスト;
			Battler* 暫定対象 = nullptr;
			int 暫定数値 = 1000;
			int max = 0;
			int rng = 0;

			int count = 0;
			
			switch (Aスキル.対象)
			{
			//味方対象
			case ASkillTarget::自分:
				Aスキル.追加効果[ASkillSubType::必中] = 100;
				Hit数+= Aスキル.Hit数;
				break;
			case ASkillTarget::弱者:
				Aスキル.追加効果[ASkillSubType::必中] = 100;
				Get対象リスト(対象リスト, 味方 , Aスキル , false, false , FormationType::前列);
				for (auto& it : 対象リスト)
				{
					double HP割合 = (double)it->現在HP / it->補正ステ[StatusType::HP];
					if (暫定数値 > HP割合)
					{
						暫定対象 = it;
						暫定数値 = HP割合;
					}
				}
				if (暫定対象 != nullptr) { 暫定対象->Hit数 += Aスキル.Hit数; }
				break;
			case ASkillTarget::前列:
				Aスキル.追加効果[ASkillSubType::必中] = 100;
				Get対象リスト(対象リスト, 味方, Aスキル,false,false, FormationType::前列);

				rng = Rand::Get((int)対象リスト.size() - 1);
				対象リスト[rng]->Hit数 += Aスキル.Hit数;
				break;
			case ASkillTarget::後列:
				Aスキル.追加効果[ASkillSubType::必中] = 100;
				Get対象リスト(対象リスト, 味方, Aスキル, false, false, FormationType::後列);

				rng = Rand::Get((int)対象リスト.size() - 1);
				対象リスト[rng]->Hit数 += Aスキル.Hit数;

				break;
			case ASkillTarget::前列範囲:
				Aスキル.追加効果[ASkillSubType::必中] = 100;
				Get対象リスト(対象リスト, 味方, Aスキル,false,false, FormationType::前列);

				for (auto& it : 対象リスト)
				{
					it->Hit数 += Aスキル.Hit数;
				}
				break;
			case ASkillTarget::後列範囲:
				Aスキル.追加効果[ASkillSubType::必中] = 100;
				Get対象リスト(対象リスト, 味方, Aスキル, false, false, FormationType::後列);
				for (auto& it : 対象リスト)
				{
					it->Hit数 += Aスキル.Hit数;
				}
				break;
			//敵対象
			case ASkillTarget::敵前列:
				Get対象リスト(対象リスト, 敵, Aスキル,true,true, FormationType::前列);
				
				for (int a = 0; a < Aスキル.Hit数; a++)
				{
					対象リスト[Rand::Get((int)対象リスト.size() - 1)]->Hit数++;
				}
				break;
			case ASkillTarget::敵後列:
				Get対象リスト(対象リスト, 敵, Aスキル, true, true, FormationType::後列);

				max = std::min(Aスキル.範囲, (int)対象リスト.size()) - 1;
				for (int a = 0; a < Aスキル.Hit数; a++)
				{
					対象リスト[Rand::Get(max)]->Hit数++;
				}
				break;
			case ASkillTarget::敵前列範囲:
				Get対象リスト(対象リスト, 敵, Aスキル, false, false, FormationType::前列);
				for (int a = 0 ; a < (int)対象リスト.size() ; a++)
				{
					if (a > Aスキル.範囲) { break; }
					対象リスト[a]->Hit数+= Aスキル.Hit数;
				}
				break;
			case ASkillTarget::敵後列範囲:
				Get対象リスト(対象リスト, 敵, Aスキル, false, false, FormationType::後列);
				for (int a = (int)敵.size() - 1; a >= 0; a--)
				{
					if (a < (int)対象リスト.size() - Aスキル.範囲 ) { break; }
					対象リスト[a]->Hit数+= Aスキル.Hit数;
				}
				break;
			case ASkillTarget::敵弱者:
				//挑発チェック
				Get対象リスト(対象リスト, 敵, Aスキル, false, false, FormationType::後列);
				
				for (auto& it : 対象リスト)
				{
					double HP割合 = it->現在HP / it->補正ステ[StatusType::HP];
					if (暫定数値 > HP割合)
					{
						暫定対象 = it;
						暫定数値 = HP割合;
					}
				}
				
				暫定対象->Hit数+= Aスキル.Hit数;
				break;
			}
			
			for (auto& it : 敵)
			{
				if (it->Hit数 > 0) {
					対象結果.push_back(it); 
				}
			}
			for (auto& it : 味方)
			{
				if (it->Hit数 > 0) { 
					対象結果.push_back(it); 
				}
			}
		}

		void Aスキル使用(const ActiveSkill* スキル, std::vector<Battler*> &味方, std::vector<Battler*> &敵)
		{
			//攻撃エフェクト
			エフェクト移動(5, 6);

			//スキル処理
			ASkillEffect ase(スキル);

			//スキル使用者のパッシブ補正、威力命中補正、追加効果追加等
			Pスキル条件チェック(PSkillTime::スキル使用時, &ase, 味方, 敵);
			
			//スキル受ける側のパッシブ補正

			//対象選択
			std::vector<Battler*> 対象;
			対象.reserve(6);
			対象.clear();

			対象選択(ase,対象, 味方, 敵);

			//効果発動
			for (auto& it : 対象)
			{
				it->スキル受け(ase, this, 味方, 敵);
			}
		}

		/*攻撃オブジェクトを引数に取る、攻撃や回復を受けた側の処理*/
		void スキル受け(ASkillEffect& Aスキル,Battler* スキル使用者,std::vector<Battler*>& 味方, std::vector<Battler*>& 敵)
		{
			int 合計ダメージ = 0;
			bool is回避 = true;
			bool isバフ = false;
			bool isデバフ = false;

			//命中とかに関係無くエフェクト
			エフェクトアニメ(Aスキル.base->戦闘エフェクト);
			
			//Hit数だけ命中判定
			for (int a = 0; a < Hit数; a++)
			{
				//命中判定
				double hit_rate = double(Aスキル.命中 - Getステ(StatusType::回避)) / 100.0;
				hit_rate = std::max( double(Aスキル.命中) / 500.0 , hit_rate);

				if (Aスキル.追加効果[ASkillSubType::必中] == 0 && !Rand::Coin( hit_rate )) { continue; }
				is回避 = false;

				合計ダメージ += (int)(Aスキル.基礎ダメージ + Aスキル.反映率 * スキル使用者->Getステ(Aスキル.base->参照ステータス)) / 100;

				for (auto& it : Aスキル.補助効果)
				{
					if (Rand::Coin((double)(it.確率+ Aスキル.バフ発動率) / 100) == false ) {continue; }
					int バフ値 = it.基礎値 + Aスキル.バフ固定値 + (Aスキル.バフ反映率 + it.反映率) * (スキル使用者->補正ステ[StatusType::パワー]) / 100;

					if (it.種類 == BuffType::スタン)
					{
						現在クールダウン -= バフ値;
						if (現在クールダウン < 0) { 現在クールダウン = 0; }
					}
					else
					{
						バフ使用(it.種類, バフ値 , it.持続 + Aスキル.バフ持続);
					}
				}
			}

			if (スキル使用者->バフ[BuffType::与ダメ増減].持続 > 0)
			{
				合計ダメージ = 合計ダメージ * (100 + スキル使用者->バフ[BuffType::与ダメ増減].効果) / 100;
			}

			if (バフ[BuffType::被ダメ増減].持続 > 0)
			{
				合計ダメージ = 合計ダメージ * (100 + バフ[BuffType::被ダメ増減].効果) / 100;
			}

			//ダメージ、回復処理
			if (合計ダメージ > 0)
			{

				if (Aスキル.追加効果[ASkillSubType::吸収] > 0)
				{
					int 吸収量 = 合計ダメージ * Aスキル.追加効果[ASkillSubType::吸収] / 100;
					スキル使用者->現在HP += 吸収量;
					スキル使用者->エフェクトダメージ(-吸収量);
				}

				switch (Aスキル.base->属性)
				{
				case DamageType::物理:
					合計ダメージ = (int)(合計ダメージ * 50 / (Get防御(DamageType::物理) + 50.0) * (1.0 - バフ[BuffType::被ダメ増減].効果));
					if (合計ダメージ > 現在HP) { 合計ダメージ = 現在HP; }
					現在HP -= 合計ダメージ;
					受ダメージログ += 合計ダメージ;
					スキル使用者->与ダメージログ += 合計ダメージ;
					//エフェクト
					エフェクト光( Color(255, 0, 0) );
					//エフェクト移動(-5, 2);
					エフェクトダメージ(合計ダメージ);
					break;
				case DamageType::魔法:
					合計ダメージ = (int)(合計ダメージ * 50 / (Get防御(DamageType::魔法) + 50.0) * (1.0 - バフ[BuffType::被ダメ増減].効果));
					if (合計ダメージ > 現在HP) { 合計ダメージ = 現在HP; }
					現在HP -= 合計ダメージ;
					受ダメージログ += 合計ダメージ;
					スキル使用者->与ダメージログ += 合計ダメージ;
					//エフェクト
					エフェクト光(Color(255, 0, 0));
					//エフェクト移動(-5, 2);
					エフェクトダメージ(合計ダメージ);
					break;
				case DamageType::回復:
					if (合計ダメージ + 現在HP > 補正ステ[StatusType::HP]) { 合計ダメージ = 補正ステ[StatusType::HP] - 現在HP; }
					現在HP += 合計ダメージ;
					スキル使用者->回復ログ += 合計ダメージ;
					//エフェクト
					エフェクト光(Color(0, 255, 0));
					エフェクトダメージ(-合計ダメージ);
					break;
				}

				if (Aスキル.追加効果[ASkillSubType::処刑] > 0 && 現在HP * 100 < 補正ステ[StatusType::HP] * Aスキル.追加効果[ASkillSubType::処刑])
				{
					現在HP = 0;
				}
			}
			else if (is回避)
			{
				エフェクトダメージ(0);
			}

			if (現在HP <= 0)
			{
				On気絶();
			}

			Hit数 = 0;
		}

		void On気絶()
		{
			MSound::効果音[気絶時SE].Play();

			//バフ/デバフ解除
			for (auto& it : バフ) { it.効果 = 0; it.持続 = 0; }

			//クールダウンを初期化
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
			}
		}

		//条件をチェックして、条件にあってるならPスキル処理を呼び出す
		void Pスキル条件チェック(PSkillTime タイミング,ASkillEffect* Aスキル, std::vector<Battler*> &味方, std::vector<Battler*> &敵)
		{
			int index = -1;

			for (auto &ps : Pスキル)
			{
				index++;
				int Lv = PスキルLv[index];
				PSkillEffect it(ps, Lv);

				if (ps->タイミング != タイミング) { continue; }
				if (Aスキル != nullptr)
				{
					//スキルタグ一致判定
					bool check_tag = false;
					for (int i = 0; i < (int)SkillType::COUNT; i++)
					{
						if (Aスキル->base->スキルタグ[i] == true && ps->スキルタグ[i] == true)
						{
							check_tag = true;
							break;
						}
					}
					if (check_tag == false) { continue; }

					if( ps->発動率 <= 0.0 || !Rand::Coin(it.Get発動率())) { continue; }
				}
				int num = (int)敵.size();

				switch (ps->条件)
				{
				case PSkillIf::HP一定以上:
					if (現在HP / 補正ステ[StatusType::HP] < it.Get条件値() ) { continue; }
					break;
				case PSkillIf::HP一定以下:
					if (現在HP / 補正ステ[StatusType::HP] > it.Get条件値() ) { continue; }
					break;
				case PSkillIf::敵の数が一定以下:
					for (int a = 0; a < (int)敵.size(); a++)
					{
						if (敵[a]->現在HP <= 0) { num--; }
					}
					if (num > it.Get条件値()) { continue; }
					break;
				case PSkillIf::敵の数が一定以上:
					for (int a = 0; a < (int)敵.size(); a++)
					{
						if (敵[a]->現在HP <= 0) { num--; }
					}
					if (num < it.Get条件値() ) { continue; }
					break;
				}
	
				if (タイミング == PSkillTime::常時 && ps->対象 == PSkillTarget::味方全員 && 味方.size() >0)
				{
					for (auto& itB : 味方)
					{
						itB->Pスキル処理(it, Aスキル, 味方, 敵);
					}
				} else {
					Pスキル処理(it, Aスキル, 味方, 敵);
				}

			}
		}

		void Pスキル処理(PSkillEffect& Pスキル,ASkillEffect* Aスキル, std::vector<Battler*> &味方, std::vector<Battler*> &敵)
		{
			//とりあえずβのだけ実装
				int num_I = Pスキル.Get効果値();
				double num_D = (double)num_I / 100;
				
				switch (Pスキル.Get効果種())
				{
					case PSkillEffectType::なし:
					//＠スキル強化://●アクティブスキル、通常攻撃強化
					case PSkillEffectType::スキル威力増減:
						Aスキル->ダメージ％増加 += num_I;
						break;
					case PSkillEffectType::スキル命中増減:
						Aスキル->命中 += num_I;
						break;
					case PSkillEffectType::隊列無視:
						Aスキル->適正隊列 = FormationType::全列;
						break;
					case PSkillEffectType::必中:
						Aスキル->追加効果[ASkillSubType::必中] += num_I;
						break;
					case PSkillEffectType::マーク無視:
						Aスキル->追加効果[ASkillSubType::マーク無視] += num_I;
						break;
					case PSkillEffectType::防御貫通://1で完全無視
						Aスキル->追加効果[ASkillSubType::防御貫通] += num_I;
						break;
					case PSkillEffectType::回避貫通:
						Aスキル->追加効果[ASkillSubType::回避貫通] += num_I;
						break;
					case PSkillEffectType::バフ固定値:
						Aスキル->バフ固定値 += num_I;
						break;
					case PSkillEffectType::バフ反映率:
						Aスキル->バフ反映率 += num_I;
						break;
					case PSkillEffectType::バフ持続:
						Aスキル->バフ持続 += num_I;
						break;
					case PSkillEffectType::デバフ固定値:
						Aスキル->バフ固定値 += num_I;
						break;
					case PSkillEffectType::デバフ反映率:
						Aスキル->バフ反映率 += num_I;
						break;
					case PSkillEffectType::デバフ持続:
						Aスキル->バフ持続 += num_I;
						break;
					case PSkillEffectType::回復超過シールド://通常スキル無し
						is回復超過シールド = true;
						break;
					case PSkillEffectType::CT獲得:
						現在クールダウン += num_I;
						break;
					case PSkillEffectType::シールド獲得:
						現在シールド += num_I;
						break;
					case PSkillEffectType::吸収:
						Aスキル->追加効果[ASkillSubType::吸収] += num_I;
						break;
					case PSkillEffectType::処刑:
						Aスキル->追加効果[ASkillSubType::処刑] += num_I;
						break;
					case PSkillEffectType::出血追撃:
						Aスキル->追加効果[ASkillSubType::出血追撃] += num_I;
						break;
					case PSkillEffectType::毒追撃:
						Aスキル->追加効果[ASkillSubType::毒追撃] += num_I;
						break;
					case PSkillEffectType::挑発追撃:
						Aスキル->追加効果[ASkillSubType::マーク追撃] += num_I;
						break;
					case PSkillEffectType::フルHP特攻:
						Aスキル->追加効果[ASkillSubType::フルHP特攻] += num_I;
						break;
					case PSkillEffectType::HP半分以下特攻:
						Aスキル->追加効果[ASkillSubType::HP半分以下特攻] += num_I;
						break;
					case PSkillEffectType::HP半分以上特攻:
						Aスキル->追加効果[ASkillSubType::HP半分以上特攻] += num_I;
						break;
					//＠保持効果://●バフ、特殊ステータス増加
					case PSkillEffectType::与ダメージバフ:
						バフ[BuffType::与ダメ増減].効果 = 1 + num_D;
						バフ[BuffType::与ダメ増減].持続 = 200;
						break;
					case PSkillEffectType::受ダメージバフ:
						バフ[BuffType::被ダメ増減].効果 = 1 - num_D;
						バフ[BuffType::被ダメ増減].持続 = 200;
						break;
					case PSkillEffectType::回復率増加:
						回復補正 += num_D;
						break;
					case PSkillEffectType::シールド獲得量増加:
						シールド補正 += num_D;
						break;
					case PSkillEffectType::HP1で耐える:
						復活 = num_I;
						break;
					case PSkillEffectType::毒耐性:
						毒耐性 -= num_D;
						if (毒耐性 < 0) { 毒耐性 = 0; }
						break;
					case PSkillEffectType::出血耐性:
						出血耐性 -= num_D;
						if (出血耐性 < 0) { 出血耐性 = 0; }
						break;
					case PSkillEffectType::毒出血耐性:
						毒耐性 -= num_D;
						出血耐性 -= num_D;
						if (毒耐性 < 0) { 毒耐性 = 0; }
						if (出血耐性 < 0) { 出血耐性 = 0; }
						break;
					//●非戦闘系
					case PSkillEffectType::未探索発見率増加:
						未探索発見補正 += num_D;
						break;
					case PSkillEffectType::戦闘後回復:
						戦闘後回復 += num_D;
						break;
					case PSkillEffectType::剥取増加:
						素材剥取量 += num_D;
						break;
					case PSkillEffectType::レア剥取増加:
						レア素材剥取補正 += num_D;
						break;
					case PSkillEffectType::採取増加:
						素材収集量 += num_D;
						break;
					case PSkillEffectType::レア採取増加:
						レア素材収集補正 += num_D;
						break;
					case PSkillEffectType::魔物部屋率減少:
						魔物部屋補正 -= num_D;
						break;
					case PSkillEffectType::魔物部屋率上昇:
						魔物部屋補正 += num_D;
						経験値補正 += num_D;
						break;
					case PSkillEffectType::素材部屋率上昇:
						素材部屋補正 += num_D;
						break;
					case PSkillEffectType::財宝部屋増加:
						財宝部屋補正 += num_D;
						break;
					case PSkillEffectType::財宝レア度増加:
						レア財宝補正 += num_D;
						break;
					case PSkillEffectType::移動速度上昇:
						移動速度補正 += num_D;
						break;
					//●その他
					case PSkillEffectType::HP増加:
						補正ステ[StatusType::HP] += num_I;
						break;
					case PSkillEffectType::パワー増加:
						補正ステ[StatusType::パワー] += num_I;
						break;
					case PSkillEffectType::防御増加:
						補正ステ[StatusType::防御] += num_I;
						break;
					case PSkillEffectType::命中増加:
						補正ステ[StatusType::命中] += num_I;
						break;
					case PSkillEffectType::回避増加:
						補正ステ[StatusType::回避] += num_I;
						break;
					case PSkillEffectType::HP割合増加:
						ステ割合上昇[StatusType::HP] += num_I;
						break;
					case PSkillEffectType::パワー割合増加:
						ステ割合上昇[StatusType::パワー] += num_I;
						break;
					case PSkillEffectType::経験値増加:
						経験値補正 += num_D;
						break;
					//＠キーパッシブ:
					case PSkillEffectType::スレイヤーA:
						//HP15%以下即死
						Aスキル->追加効果[ASkillSubType::処刑] += num_I;
						break;
					case PSkillEffectType::スレイヤーB:
						//回復超過シールド
						is回復超過シールド = true;
						break;
					case PSkillEffectType::ガーディアンA:
						//毒と出血を無効
						毒耐性 -= num_D;
						出血耐性 -= num_D;
						if (毒耐性 < 0) { 毒耐性 = 0; }
						if (出血耐性 < 0) { 出血耐性 = 0; }
						break;
					case PSkillEffectType::ガーディアンB:
						//味方全員の防御+5
						補正ステ[StatusType::HP] += num_I;
						break;
					case PSkillEffectType::デッドアイA:
						//命中と防御+20、回避-20
						補正ステ[StatusType::命中] += num_I;
						補正ステ[StatusType::防御] += num_I;
						補正ステ[StatusType::回避] -= num_I;
						break;
					case PSkillEffectType::デッドアイB:
						//探索速度+20
						移動速度補正 += num_D;
						break;
					case PSkillEffectType::エレメンタリストA:
						//回避貫通100%
						Aスキル->追加効果[ASkillSubType::回避貫通] += num_I;
						break;
					case PSkillEffectType::エレメンタリストB:
						//防御貫通100%
						Aスキル->追加効果[ASkillSubType::防御貫通] += num_I;
						break;
					case PSkillEffectType::クレリックA:
						//味方全員に耐性30%
						毒耐性 -= num_D;
						出血耐性 -= num_D;
						if (毒耐性 < 0) { 毒耐性 = 0; }
						if (出血耐性 < 0) { 出血耐性 = 0; }
						break;
					case PSkillEffectType::クレリックB:
						//スキルに回復超過シールド
						Aスキル->追加効果[ASkillSubType::超過回復] += num_I;
						break;
					case PSkillEffectType::オカルティストA:
						//戦闘開始時にHPと同じ量のシールド
						現在シールド += 補正ステ[StatusType::HP];
						break;
					case PSkillEffectType::オカルティストB:
						//デバフスキルが必中
						Aスキル->追加効果[ASkillSubType::必中] += num_I;
						break;
					case PSkillEffectType::グラディエーターA:
						//先頭にいると命中とパワー+20
						補正ステ[StatusType::命中] += num_I;
						補正ステ[StatusType::パワー] += num_I;
						break;
					case PSkillEffectType::グラディエーターB:
						//常にマーク
						is常時マーク = true;
						break;
					case PSkillEffectType::アサシンA:
						//前列スキルが後列スキル化
						Aスキル->適正隊列 = FormationType::全列;
						break;
					case PSkillEffectType::アサシンB:
						//HP半分以上の敵へダメージ+50%
						Aスキル->追加効果[ASkillSubType::HP半分以上特攻] += num_I;
						break;
					case PSkillEffectType::バーサーカーA:
						//与えるダメージ、受けるダメージ1.4倍
						常時ダメージ上昇 = 1 + num_D;
						常時ダメージ減少 = 1 + num_D;
						break;
					case PSkillEffectType::バーサーカーB:
						//先頭にいる時、スキルダメージ+50%
						Aスキル->ダメージ％増加 += num_I;
						break;
					case PSkillEffectType::トリックスターA:
						//毒ダメージ x0.7 、 毒持続 x 2.0
						Aスキル->バフ反映率 -= 30;
						Aスキル->バフ持続 += 100;
						break;
					case PSkillEffectType::トリックスターB:
						//戦闘開始時、行動値が最大
						現在クールダウン = 9999;
						break;
					case PSkillEffectType::シャーマンA:
						//戦闘開始時、全員に与ダメx1.2バフを付与
						バフ[BuffType::与ダメ増減].効果 = 1 + num_D;
						バフ[BuffType::与ダメ増減].持続 = 200;
						break;
					case PSkillEffectType::シャーマンB:
						//戦闘開始時、全員に被ダメx0.8バフを付与
						バフ[BuffType::被ダメ増減].効果 = 1 - num_D;
						バフ[BuffType::被ダメ増減].持続 = 200;
						break;
					case PSkillEffectType::パスファインダーA:
						//アクセサリーが追加で手に入る
						isアクセ複数入手 = true;
						break;
					case PSkillEffectType::パスファインダーB:
						//一定確率で全ランクの素材を同時に獲得
						素材複数入手 = num_D;
						break;
				}
			}
	};
}