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
		void Get生存リスト(std::vector<Battler*>& 生存リスト, const std::vector<Battler*>& 敵)
		{
			生存リスト.reserve(6);
			生存リスト.clear();
			for (auto& it : 敵)
			{
				if (it->現在HP > 0) { 生存リスト.push_back(it); }
			}
		}


	public:

		ImagePack *image;
		int パーティID;

		//●基礎ステータス
		int Aスキル数 = 4;
		ActiveSkill* Aスキル[CV::最大Aスキル数] = {nullptr};
		int AスキルLv[CV::最大Aスキル数];

		//Pスキルは発動タイミングでコンテナ分ければ多少高速化になるかも
		std::vector<PassiveSkill*> Pスキル;//本人のパッシブ、装備パッシブを格納
		std::vector<int> PスキルLv;

		//●装備とパッシブ補正後
		EnumArray<int, StatusType> 基礎ステ;//Lv、装備補正、常時パッシブのステータス
		EnumArray<int, StatusType> 補正ステ;//条件付き基礎ステータス上昇P効果適用後、および常時パッシブ計算用の一時ステータス
		EnumArray<int, StatusType> ステ割合上昇;//基礎ステ割合上昇を最後に計算する用

		//特殊ステータス - あとでstatusTypeに追加？
		int 基礎デバフ抵抗;
		int 基礎異常抵抗;
		int 基礎回復補正;

		int デバフ抵抗;
		int 異常抵抗;
		int 回復補正;

		//現在の状態
		int 現在HP = 0;
		bool is気絶 = false;

		//スキルクールダウン
		int 現在スキルスロット = 0;
		int 現在クールダウン;
		int 必要クールダウン[CV::最大Aスキル数];

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

		//攻撃受け側の一時変数
		int Hit数 = 0;

		//ギルメンは基礎ステLv補正+常時パッシブ+装備
		//モンスター基礎ステLv補正+常時パッシブ
		virtual void 基礎ステータス計算() = 0;

		void 基礎Pスキル補正(std::vector<Battler*>& 味方, std::vector<Battler*>& 敵)
		{
			//味方と自分の基礎Pスキルによる補正ステ計算
			Pスキル条件チェック(PSkillTime::常時, nullptr, 味方, 敵);
		}

		void 基礎Pスキル反映()
		{
			//Pスキル補正を確定
			基礎ステ[StatusType::HP] = 補正ステ[StatusType::HP];
			基礎ステ[StatusType::力] = 補正ステ[StatusType::力];
			基礎ステ[StatusType::技] = 補正ステ[StatusType::技];
			基礎ステ[StatusType::知] = 補正ステ[StatusType::知];

			基礎ステ[StatusType::物防] = 補正ステ[StatusType::物防];
			基礎ステ[StatusType::魔防] = 補正ステ[StatusType::魔防];

			基礎ステ[StatusType::命中] = 補正ステ[StatusType::命中];
			基礎ステ[StatusType::回避] = 補正ステ[StatusType::回避];

			//割合増加を反映
		}

		//補正ステータス=基礎ステータスにしてバフ残り時間もリセット
		void Reset一時補正ステータス()
		{
			補正ステ[StatusType::HP] = 基礎ステ[StatusType::HP];
			補正ステ[StatusType::力] = 基礎ステ[StatusType::力];
			補正ステ[StatusType::技] = 基礎ステ[StatusType::技];
			補正ステ[StatusType::知] = 基礎ステ[StatusType::知];

			補正ステ[StatusType::物防] = 基礎ステ[StatusType::物防];
			補正ステ[StatusType::魔防] = 基礎ステ[StatusType::魔防];

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
			auto t = BuffType::Str;

			switch (ステータス種)
			{
				case StatusType::HP: return 補正ステ[ステータス種];//HP一時上昇スキル未実装
				case StatusType::力: t = BuffType::Str; break;
				case StatusType::技: t = BuffType::Dex; break;
				case StatusType::知: t = BuffType::Int; break;
				case StatusType::物防: t = BuffType::物防; break;
				case StatusType::魔防: t = BuffType::魔防; break;
				case StatusType::命中: t = BuffType::命中; break;
				case StatusType::回避: t = BuffType::回避; break;
				case StatusType::会心: return 補正ステ[ステータス種];
			}

			double value = (バフ[t].持続 > 0) ? 補正ステ[ステータス種] + バフ[t].効果 : 補正ステ[ステータス種];

			if (value < 0) { return 0; }//ステータスはマイナスにはならない

			return value;
		}

		double Get防御(DamageType ダメージ種)
		{
			switch (ダメージ種)
			{
			case SDX_ADE::DamageType::物理:
				return 補正ステ[StatusType::物防] + バフ[BuffType::物防].効果;
				break;
			case SDX_ADE::DamageType::魔法:
				return 補正ステ[StatusType::魔防] + バフ[BuffType::魔防].効果;
				break;
			default:
				return 0;//無属性スキルは防御無視
				break;
			}

			return 0;
		}

		void バフ使用(BuffType バフデバフ種 , double 効果量 , int 時間)
		{
			BuffType t = BuffType(バフデバフ種);
			//バフ中のバフ or デバフ中のデバフ、時間、効果量で大きい方に更新
			//バフ中にデバフ or デバフ中にバフ、時間は大きい方から小さい方を引く、効果は時間が長い方になる

			if (効果量 > 0 )
			{
				if (バフ[t].効果 > 0)
				{
					バフ[t].効果 = std::max(バフ[t].効果,効果量);
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

		//エフェクト関係
		void エフェクト更新()
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
					}else{
						E座標 = 0;
						E速度 = 0;
									
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
				Effect::文字[パーティID].emplace_back(TextEffect::TextType::回避, 0, is味方, 隊列ID);
			} else if (ダメージ > 0) {
				Effect::文字[パーティID].emplace_back(TextEffect::TextType::ダメージ, ダメージ , is味方 , 隊列ID);
			} else {
				Effect::文字[パーティID].emplace_back(TextEffect::TextType::回復, -ダメージ, is味方, 隊列ID);
			}
		}

		void エフェクトアニメ(int ID)
		{
			Effect::アニメ[パーティID].emplace_back(ID, is味方, 隊列ID);
		}

		void 戦闘開始(std::vector<Battler*>& 味方, std::vector<Battler*>& 敵)
		{
			//初期化
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{

			}

			//バフ初期化
			for (auto& it : バフ) { it.効果 = 0; it.持続 = 0; }

			//パッシブ効果の計算
			Pスキル条件チェック(PSkillTime::戦闘開始時, nullptr, 味方, 敵);
		}

		void ターン経過()
		{
			if (現在HP <= 0) { return ; }

			//スキル発動チェック
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
			}

			//バフ持続などの処理
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

			//スキル発動チェック
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if (Aスキル[a] == nullptr) { continue; }

			}

			return false;
		}

		Battler* is挑発敵(std::vector<Battler*>& 敵 , int 範囲 ,bool is前)
		{
			if (範囲 > (int)敵.size()) { 範囲 = (int)敵.size(); }

			if (is前)
			{
				for (int a = 0; a < 範囲; a++)
				{
					if (敵[a]->バフ[BuffType::挑発].効果 > 0) { return 敵[a]; }
				}
			} else {
				for (int a = (int)敵.size() -1 ; a >= (int)敵.size() - 範囲; a--)
				{
					if (敵[a]->バフ[BuffType::挑発].効果 > 0) { return 敵[a]; }
				}
			}

			return nullptr;
		}

		void 対象選択(const ASkillEffect &Aスキル, std::vector<Battler*>& 対象, std::vector<Battler*>&味方,std::vector<Battler*> &敵)
		{
			//攻撃or回復対象を選択
			static std::vector<Battler*> 生存リスト;
			Battler* 暫定対象 = nullptr;
			int max = 0;
			/*
			switch (Aスキル.対象)
			{
			case ASkillTarget::自分:
				Hit数+= Aスキル.Hit数;
				break;
			case ASkillTarget::味方弱者:
				暫定数値 = 100;
				for (auto& it : 味方)
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
			case ASkillTarget::味方全員:
				for (auto& it : 味方)
				{
					it->Hit数 += Aスキル.Hit数;
				}
				break;
			case ASkillTarget::敵ランダム:
				Get生存リスト(生存リスト, 敵);
				暫定対象 = is挑発敵(生存リスト,99,true);

				if (暫定対象 != nullptr)
				{
					暫定対象->Hit数 += Aスキル.Hit数;
					break;
				}

				for (int a = 0; a < Aスキル.Hit数; a++)
				{
					生存リスト[Rand::Get((int)生存リスト.size() - 1)]->Hit数++;
				}
			case ASkillTarget::敵前ランダム:
				Get生存リスト(生存リスト, 敵);
				暫定対象 = is挑発敵(生存リスト, Aスキル.範囲,true);

				if (暫定対象 != nullptr)
				{
					暫定対象->Hit数 += Aスキル.Hit数;
					break;
				}

				max = std::min(Aスキル.範囲, (int)生存リスト.size()) - 1;
				for (int a = 0; a < Aスキル.Hit数; a++)
				{
					生存リスト[Rand::Get(max)]->Hit数++;
				}
				break;
			case ASkillTarget::敵後ランダム:
				Get生存リスト(生存リスト, 敵);
				暫定対象 = is挑発敵(生存リスト,Aスキル.範囲,false);

				if (暫定対象 != nullptr)
				{
					暫定対象->Hit数 += Aスキル.Hit数;
					break;
				}

				max = std::min(Aスキル.範囲, (int)生存リスト.size()) - 1;
				for (int a = 0; a < Aスキル.Hit数; a++)
				{
					生存リスト[((int)生存リスト.size() - 1) - Rand::Get(max)]->Hit数++;
				}
				break;
			case ASkillTarget::敵前:
				Get生存リスト(生存リスト, 敵);
				for (int a = 0 ; a < (int)生存リスト.size() ; a++)
				{
					if (a > Aスキル.範囲) { break; }
					生存リスト[a]->Hit数+= Aスキル.Hit数;
				}
				break;
			case ASkillTarget::敵後:
				Get生存リスト(生存リスト, 敵);
				for (int a = (int)敵.size() - 1; a >= 0; a--)
				{
					if (a < (int)生存リスト.size() - Aスキル.範囲 ) { break; }
					生存リスト[a]->Hit数+= Aスキル.Hit数;
				}
				break;
			case ASkillTarget::敵全:
				for (auto& it : 敵)
				{
					it->Hit数+= Aスキル.Hit数;
				}
				break;
			case ASkillTarget::敵弱者:
				//挑発チェック
				Get生存リスト(生存リスト, 敵);
				暫定対象 = is挑発敵(生存リスト,99,true);

				if (暫定対象 == nullptr)
				{
					暫定数値 = 100;
					for (auto& it : 生存リスト)
					{
						double HP割合 = it->現在HP / it->補正ステ[StatusType::HP];
						if (暫定数値 > HP割合)
						{
							暫定対象 = it;
							暫定数値 = HP割合;
						}
					}
				}

				暫定対象->Hit数+= Aスキル.Hit数;
				break;
			}
			*/
			for (auto& it : 敵)
			{
				if (it->Hit数 > 0) {
					対象.push_back(it); 
				}
			}
			for (auto& it : 味方)
			{
				if (it->Hit数 > 0) { 
					対象.push_back(it); 
				}
			}
		}

		void Aスキル処理(const ActiveSkill* スキル, std::vector<Battler*> &味方, std::vector<Battler*> &敵)
		{
			//攻撃エフェクト
			エフェクト移動(10, 2);

			//スキル処理
			ASkillEffect ase(スキル,1);

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
				if ( !Rand::Coin(Aスキル.命中 - Getステ(StatusType::回避))) { continue; }
				is回避 = false;

				合計ダメージ += (int)(Aスキル.基礎ダメージ + Aスキル.反映率 * スキル使用者->Getステ(Aスキル.base->参照ステータス));

				for (int b = 0; b < (int)BuffType::COUNT; b++)
				{
					auto t = BuffType(b);

					//if (Aスキル.バフ確率[t] <= 0 || !Rand::Coin(Aスキル.バフ確率[t])) { continue; }

					//バフ使用(t, Aスキル.バフ反映率[t] * Aスキル.バフ効果補正, int(Aスキル.バフ持続[t] * Aスキル.バフ持続補正));
					//isバフ = (Aスキル.バフ反映率[t] > 0);
					//isデバフ = (Aスキル.バフ反映率[t] < 0);

					if (isバフ)
					{
						E光色 = Color(0, 0, 255);
						E光強さ = 1.0;
					}
					if(isデバフ){
						E光色 = Color(128, 0, 128);
						E光強さ = 1.0;
					}
				}
			}

			//ダメージ、回復処理
			if (合計ダメージ > 0)
			{
				switch (Aスキル.base->属性)
				{
				case DamageType::物理:
					合計ダメージ = (int)(合計ダメージ * 50 / (Get防御(DamageType::物理) + 50.0) * (1.0 - バフ[BuffType::被ダメ軽減].効果));
					if (合計ダメージ > 現在HP) { 合計ダメージ = 現在HP; }
					現在HP -= 合計ダメージ;
					受ダメージログ += 合計ダメージ;
					スキル使用者->与ダメージログ += 合計ダメージ;
					Pスキル条件チェック(PSkillTime::攻撃を受けた時, &Aスキル, 味方, 敵);
					//エフェクト
					エフェクト光( Color(255, 0, 0) );
					//エフェクト移動(-5, 2);
					エフェクトダメージ(合計ダメージ);
					break;
				case DamageType::魔法:
					合計ダメージ = (int)(合計ダメージ * 50 / (Get防御(DamageType::魔法) + 50.0) * (1.0 - バフ[BuffType::被ダメ軽減].効果));
					if (合計ダメージ > 現在HP) { 合計ダメージ = 現在HP; }
					現在HP -= 合計ダメージ;
					受ダメージログ += 合計ダメージ;
					スキル使用者->与ダメージログ += 合計ダメージ;
					Pスキル条件チェック(PSkillTime::攻撃を受けた時, &Aスキル, 味方, 敵);
					//エフェクト
					エフェクト光(Color(255, 0, 0));
					//エフェクト移動(-5, 2);
					エフェクトダメージ(合計ダメージ);
					break;
				case DamageType::回復:
					if (合計ダメージ + 現在HP > 補正ステ[StatusType::HP]) { 合計ダメージ = 補正ステ[StatusType::HP] - 現在HP; }
					現在HP += 合計ダメージ;
					スキル使用者->回復ログ += 合計ダメージ;
					Pスキル条件チェック(PSkillTime::回復を受けた時, &Aスキル, 味方, 敵);
					//エフェクト
					エフェクト光(Color(0, 255, 0));
					エフェクトダメージ(-合計ダメージ);
					break;
				}
			}
			else if (is回避)
			{
				エフェクトダメージ(0);
				Pスキル条件チェック(PSkillTime::回避した時, &Aスキル, 味方, 敵);
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

			//スタン付与
			バフ[BuffType::スタン].効果 = 1;
			バフ[BuffType::スタン].持続 = CV::気絶スタン値;
		}

		//条件をチェックして、条件にあってるならPスキル処理を呼び出す
		void Pスキル条件チェック(PSkillTime タイミング,ASkillEffect* Aスキル, std::vector<Battler*> &味方, std::vector<Battler*> &敵)
		{
			for (auto &it : Pスキル)
			{
				if (it->タイミング != タイミング) { continue; }
				if (Aスキル != nullptr)
				{
					//if( it->Aスキル種 != Aスキル->種類) { continue; }
					//if ( it->装備種 != ItemType::すべて && it->装備種 != Aスキル->装備種) { continue; }
					//if (it->発動率 <= 0.0 || !Rand::Coin(it->発動率)) { continue; }
				}
				int num = (int)敵.size();

				switch (it->条件)
				{
				case PSkillIf::HP一定以上:
					if (現在HP / 補正ステ[StatusType::HP] < it->条件値) { continue; }
					break;
				case PSkillIf::HP一定以下:
					if (現在HP / 補正ステ[StatusType::HP] > it->条件値) { continue; }
					break;
				case PSkillIf::敵の数が一定以下:
					for (int a = 0; a < (int)敵.size(); a++)
					{
						if (敵[a]->現在HP <= 0) { num--; }
					}
					if (num > it->条件値) { continue; }
					break;
				case PSkillIf::敵の数が一定以上:
					for (int a = 0; a < (int)敵.size(); a++)
					{
						if (敵[a]->現在HP <= 0) { num--; }
					}
					if (num < it->条件値) { continue; }
					break;
				}
	
				if (タイミング == PSkillTime::常時 && it->対象 == PSkillTarget::味方全員 && 味方.size() >0)
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

		void Pスキル処理(PassiveSkill* Pスキル,ASkillEffect* Aスキル, std::vector<Battler*> &味方, std::vector<Battler*> &敵)
		{
			//とりあえずβのだけ実装
			switch (Pスキル->効果種[0])
			{
			//基礎限定効果
			case PSkillEffect::HP増加:
				補正ステ[StatusType::HP] += Pスキル->効果量[0];
				break;
			case PSkillEffect::STR増加:
				補正ステ[StatusType::力] += Pスキル->効果量[0];
				break;
			case PSkillEffect::INT増加:
				補正ステ[StatusType::知] += Pスキル->効果量[0];
				break;
			case PSkillEffect::DEX増加:
				補正ステ[StatusType::技] += Pスキル->効果量[0];
				break;
			case PSkillEffect::物防増加:
				補正ステ[StatusType::物防] += Pスキル->効果量[0];
				break;
			case PSkillEffect::魔防増加:
				補正ステ[StatusType::魔防] += Pスキル->効果量[0];
				break;
			case PSkillEffect::命中増加:
				補正ステ[StatusType::命中] += Pスキル->効果量[0];
				break;
			case PSkillEffect::回避増加:
				補正ステ[StatusType::回避] += Pスキル->効果量[0];
				break;
			case PSkillEffect::スキルCT増減:
				for (int a = 0; a < CV::最大Aスキル数; a++)
				{
				}
				break;
			//基礎非戦闘
			case PSkillEffect::採取増加:
				素材収集量 += Pスキル->効果量[0];
				break;
			case PSkillEffect::レア採取増加:
				レア素材収集補正 += Pスキル->効果量[0];
				break;
			case PSkillEffect::剥取増加:
				素材剥取量 += Pスキル->効果量[0];
				break;
			case PSkillEffect::レア剥取増加:
				レア素材剥取補正 += Pスキル->効果量[0];
				break;
			case PSkillEffect::戦闘後回復:
				戦闘後回復 += Pスキル->効果量[0];
				break;
			//スキル使用時限定
			case PSkillEffect::スキル威力増減:
				//Aスキル->反映率 *= 1.0 + Pスキル->効果量[0];
				break;
			case PSkillEffect::スキル効果増減:
				//Aスキル->バフ効果補正 += Pスキル->効果量[0];
				break;
			//色んなタイミングで発動可能
			case PSkillEffect::与ダメージバフ:
				if (Pスキル->対象 == PSkillTarget::スキル対象)
				{
					//Aスキル->バフ確率[BuffType::与ダメ増減] = 1.0;
					//Aスキル->バフ持続[BuffType::与ダメ増減] = Pスキル->持続時間;
					//Aスキル->バフ反映率[BuffType::与ダメ増減] = Pスキル->効果量[0];
				} else {
					//自己バフ
					バフ使用(BuffType::与ダメ増減, Pスキル->効果量[0], Pスキル->持続時間);
				}
				break;
			case PSkillEffect::受ダメージバフ:
				if (Pスキル->対象 == PSkillTarget::スキル対象)
				{
					//Aスキル->バフ確率[BuffType::被ダメ軽減] = 1.0;
					//Aスキル->バフ持続[BuffType::被ダメ軽減] = Pスキル->持続時間;
					//Aスキル->バフ反映率[BuffType::被ダメ軽減] = Pスキル->効果量[0];
				} else {
					//自己
					バフ使用(BuffType::被ダメ軽減, Pスキル->効果量[0], Pスキル->持続時間);
				}
				break;
			}
		}
	};
}