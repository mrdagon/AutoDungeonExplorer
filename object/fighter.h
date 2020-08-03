//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*従業員ベースクラス*/
	class Fighter
	{
	private:
		void Get生存リスト(std::vector<Fighter*>& 生存リスト, const std::vector<Fighter*>& 敵)
		{
			生存リスト.reserve(6);
			生存リスト.clear();
			for (auto& it : 敵)
			{
				if (it->現在HP > 0) { 生存リスト.push_back(it); }
			}
		}
	public:
		ImagePack *Img;
		int パーティID;

		//●固定、基礎ステータス
		ActiveSkill* Aスキル[CV::最大Aスキル数] = {nullptr};
		std::vector<PassiveSkill*> Pスキル;//本人のパッシブ、装備、パーティパッシブを格納

		//●基礎ステータス
		EnumArray<int, StatusType> 基礎ステ;
		//EnumArray<int,DamageType> 基礎防御;
		//●装備とパッシブ補正後
		EnumArray<int, StatusType> 補正ステ;
		//EnumArray<int, DamageType> 補正防御;
		//●計算後ステータス、戦闘中ステータス、パッシブ計算
		int 現在HP = 0;
		//スキルクールダウン
		double 合計クールダウン[CV::最大Aスキル数];
		double クールダウン速度[CV::最大Aスキル数];

		SEType 気絶時SE = SE::敵気絶;

		//一時的なバフ兼デバフ、効果量、効果時間
		int 隊列ID;//0が先頭、以下1.2.3.4...
		bool is味方 = false;

		struct Buff
		{
			double 効果 = 0;
			int 持続 = 0;
		};

		EnumArray<Buff, BuffType> バフ;

		//エフェクト用数値
		double E速度 = 0;//前出たり、ノックバック速度
		int E反転残り = 0;
		int E反転時間 = 0;
		double E座標 = 0;

		Color E光色;//ダメージ赤、回復緑、補助青
		double E光強さ = 0;

		//累計ダメージログ用
		int 与ダメージログ = 0;
		int 受ダメージログ = 0;
		int 回復ログ = 0;

		//探索スキル効果
		double 戦闘後回復 = 0.0;
		double レア素材剥取補正 = 0.0;
		double レア素材収集補正 = 0.0;
		double 素材剥取量 = 0.0;
		double 素材収集量 = 0.0;

		//攻撃受け時用の一時変数
		int Hit数 = 0;

		//ギルメンは基礎ステ+装備
		virtual void 基礎ステータス計算() = 0;

		void 基礎Pスキル補正(std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{
			//味方と自分の基礎Pスキルによる補正ステ計算
			Pスキル条件チェック(PSkillTime::常時, nullptr, 味方, 敵);
		}

		//補正ステータス=基礎ステータスにしてバフ残り時間もリセット
		void Reset補正ステータス()
		{
			補正ステ[StatusType::Hp] = 基礎ステ[StatusType::Hp];
			補正ステ[StatusType::Str] = 基礎ステ[StatusType::Str];
			補正ステ[StatusType::Dex] = 基礎ステ[StatusType::Dex];
			補正ステ[StatusType::Int] = 基礎ステ[StatusType::Int];

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

		//一時バフ補正後ステータス取得
		double Getステ(StatusType ステータス種)
		{
			auto t = BuffType::Str;

			switch (ステータス種)
			{
			case StatusType::Str:
				t = BuffType::Str;
				break;
			case StatusType::Dex:
				t = BuffType::Dex;
				break;
			case StatusType::Int:
				t = BuffType::Int;				
				break;
			}

			return (バフ[t].持続 > 0) ? 補正ステ[ステータス種] * バフ[t].効果 : 補正ステ[ステータス種];
		}

		double Get防御(DamageType ダメージ種)
		{
			BuffType t = (ダメージ種 == DamageType::物理) ? (BuffType::物防):(BuffType::魔防);

			switch (ダメージ種)
			{
			case SDX_BSC::DamageType::物理:
				return 補正ステ[StatusType::物防] + バフ[t].効果;
				break;
			case SDX_BSC::DamageType::魔法:
				return 補正ステ[StatusType::魔防] + バフ[t].効果;
				break;
			default:
				return 0;
				break;
			}

			return 0;
		}

		double Get命中()
		{
			return double((バフ[BuffType::命中].持続 > 0) ? 補正ステ[StatusType::命中] + バフ[BuffType::命中].効果 : 補正ステ[StatusType::命中])/100;
		}

		double Get回避()
		{
			return double((バフ[BuffType::回避].持続 > 0) ? 補正ステ[StatusType::回避] + バフ[BuffType::回避].効果 : 補正ステ[StatusType::回避] )/100;
		}

		void バフ使用(BuffType バフデバフ種 , double 効果量 , int 時間)
		{
			BuffType t = BuffType(バフデバフ種);
			//バフ中のバフ デバフ中のデバフ、時間、効果量で大きい方に更新
			//バフ中にデバフ デバフ中にバフ、時間は大きい方から小さい方を引く、効果は時間が長い方になる

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

		void エフェクトアニメ(EffectAnimeType アニメ)
		{
			Effect::アニメ[パーティID].emplace_back(アニメ, is味方, 隊列ID);
		}

		void 戦闘開始(std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{
			//初期化
			for (int a = 0; a < CV::最大Aスキル数 - 1; a++)
			{
				合計クールダウン[a] = Rand::Get(50);
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
				合計クールダウン[a] += クールダウン速度[a];
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

		bool Aスキル使用チェック(std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{
			if (現在HP <= 0) { return false; }

			//スキル発動チェック
			for (int a = 0; a < CV::最大Aスキル数; a++)
			{
				if (Aスキル[a] == nullptr) { continue; }

				if ( 合計クールダウン[a] > Aスキル[a]->必要クールタイム)
				{
					合計クールダウン[a] -= Aスキル[a]->必要クールタイム;
					Aスキル処理(Aスキル[a], 味方, 敵);
					return true;
				}
			}

			return false;
		}

		Fighter* is挑発敵(std::vector<Fighter*>& 敵 , int 範囲 ,bool is前)
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

		void 対象選択(const ASkillEffect &Aスキル, std::vector<Fighter*>& 対象, std::vector<Fighter*>&味方,std::vector<Fighter*> &敵)
		{
			//攻撃or回復対象を選択
			static std::vector<Fighter*> 生存リスト;
			Fighter* 暫定対象 = nullptr;
			double 暫定数値;
			int max = 0;

			switch (Aスキル.対象)
			{
			case ASkillTarget::自分:
				Hit数+= Aスキル.Hit数;
				break;
			case ASkillTarget::味方弱者:
				暫定数値 = 100;
				for (auto& it : 味方)
				{
					double HP割合 = (double)it->現在HP / it->補正ステ[StatusType::Hp];
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
						double HP割合 = it->現在HP / it->補正ステ[StatusType::Hp];
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

		void Aスキル処理(const ActiveSkill* スキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//攻撃エフェクト
			エフェクト移動(10, 2);

			//スキル処理
			ASkillEffect ase(スキル);
			//パッシブ補正、威力命中補正、追加効果追加等
			Pスキル条件チェック(PSkillTime::スキル使用時, &ase, 味方, 敵);
			if (ase.種類 == ASkillType::回復)
			{
				//MSound::効果音[SE::回復].Play();
				Pスキル条件チェック(PSkillTime::回復スキル使用時, &ase, 味方, 敵);
			}
			else if (ase.種類 == ASkillType::物理 || ase.種類 == ASkillType::魔法)
			{
				//MSound::効果音[SE::攻撃].Play();
				Pスキル条件チェック(PSkillTime::攻撃スキル使用時, &ase, 味方, 敵);
			}
			else if (ase.種類 == ASkillType::バフ || ase.種類 == ASkillType::デバフ)
			{
				//MSound::効果音[SE::補助].Play();
				Pスキル条件チェック(PSkillTime::補助スキル使用時, &ase, 味方, 敵);
			}

			//対象選択
			std::vector<Fighter*> 対象;
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
		void スキル受け(ASkillEffect& Aスキル,Fighter* スキル使用者,std::vector<Fighter*>& 味方, std::vector<Fighter*>& 敵)
		{
			int 合計ダメージ = 0;
			bool is回避 = true;
			bool isバフ = false;
			bool isデバフ = false;

			//命中とかに関係無くエフェクト
			エフェクトアニメ(Aスキル.戦闘エフェクト);

			//Hit数だけ命中判定
			for (int a = 0; a < Hit数; a++)
			{
				//命中判定
				if ( !Rand::Coin(Aスキル.命中 - Get回避())) { continue; }
				is回避 = false;

				合計ダメージ += (int)(Aスキル.基礎効果 + Aスキル.反映率 * スキル使用者->Getステ(Aスキル.依存ステータス));

				for (int b = 0; b < (int)BuffType::COUNT; b++)
				{
					auto t = BuffType(b);

					if (Aスキル.バフ確率[t] <= 0 || !Rand::Coin(Aスキル.バフ確率[t])) { continue; }

					バフ使用(t, Aスキル.バフ反映率[t] * Aスキル.バフ効果補正, int(Aスキル.バフ持続[t] * Aスキル.バフ持続補正));
					isバフ = (Aスキル.バフ反映率[t] > 0);
					isデバフ = (Aスキル.バフ反映率[t] < 0);

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
				switch (Aスキル.種類)
				{
				case ASkillType::物理:
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
				case ASkillType::魔法:
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
				case ASkillType::回復:
					if (合計ダメージ + 現在HP > 補正ステ[StatusType::Hp]) { 合計ダメージ = 補正ステ[StatusType::Hp] - 現在HP; }
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
				MSound::効果音[気絶時SE].Play();
			}

			Hit数 = 0;
		}

		//条件をチェックして、条件にあってるならPスキル処理を呼び出す
		void Pスキル条件チェック(PSkillTime タイミング,ASkillEffect* Aスキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			for (auto &it : Pスキル)
			{
				if (it->タイミング != タイミング) { continue; }
				if (Aスキル != nullptr)
				{
					if( it->Aスキル種 != Aスキル->種類) { continue; }
					if ( it->装備種 != ItemType::すべて && it->装備種 != Aスキル->装備種) { continue; }
					if (it->発動率 <= 0.0 || !Rand::Coin(it->発動率)) { continue; }
				}
				int num = (int)敵.size();

				switch (it->条件)
				{
				case PSkillIf::HP一定以上:
					if (現在HP / 補正ステ[StatusType::Hp] < it->条件値) { continue; }
					break;
				case PSkillIf::HP一定以下:
					if (現在HP / 補正ステ[StatusType::Hp] > it->条件値) { continue; }
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

		void Pスキル処理(PassiveSkill* Pスキル,ASkillEffect* Aスキル, std::vector<Fighter*> &味方, std::vector<Fighter*> &敵)
		{
			//とりあえずβのだけ実装
			switch (Pスキル->効果)
			{
			//基礎限定効果
			case PSkillEffect::HP増加:
				補正ステ[StatusType::Hp] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::STR増加:
				補正ステ[StatusType::Str] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::INT増加:
				補正ステ[StatusType::Int] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::DEX増加:
				補正ステ[StatusType::Dex] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::物防増加:
				補正ステ[StatusType::物防] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::魔防増加:
				補正ステ[StatusType::魔防] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::命中増加:
				補正ステ[StatusType::命中] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::回避増加:
				補正ステ[StatusType::回避] += (int)Pスキル->効果量;
				break;
			case PSkillEffect::スキルCT増減:
				for (int a = 0; a < CV::最大Aスキル数; a++)
				{
					if (Pスキル->Aスキル種 != Aスキル[a].種類) { continue; }
					if (Pスキル->装備種 != ItemType::すべて && Pスキル->装備種 != Aスキル[a].装備種) { continue; }
					クールダウン速度[a] *= 1.0 + Pスキル->効果量;
				}
				break;
			//基礎非戦闘
			case PSkillEffect::収集量増加:
				素材収集量 += Pスキル->効果量;
				break;
			case PSkillEffect::収集ランク増加:
				レア素材収集補正 += Pスキル->効果量;
				break;
			case PSkillEffect::剥取量増加:
				素材剥取量 += Pスキル->効果量;
				break;
			case PSkillEffect::剥取ランク増加:
				レア素材剥取補正 += Pスキル->効果量;
				break;
			case PSkillEffect::戦闘後回復:
				戦闘後回復 += Pスキル->効果量;
				break;
			//スキル使用時限定
			case PSkillEffect::スキル威力増減:
				Aスキル->反映率 *= 1.0 + Pスキル->効果量;
				break;
			case PSkillEffect::スキル効果増減:
				Aスキル->バフ効果補正 += Pスキル->効果量;
				break;
			case PSkillEffect::スキル持続増減:
				Aスキル->バフ持続補正 += Pスキル->効果量;
				break;
			//色んなタイミングで発動可能
			case PSkillEffect::与ダメージバフ:
				if (Pスキル->対象 == PSkillTarget::スキル対象)
				{
					Aスキル->バフ確率[BuffType::与ダメ増減] = 1.0;
					Aスキル->バフ持続[BuffType::与ダメ増減] = Pスキル->持続時間;
					Aスキル->バフ反映率[BuffType::与ダメ増減] = Pスキル->効果量;
				} else {
					//自己バフ
					バフ使用(BuffType::与ダメ増減, Pスキル->効果量, Pスキル->持続時間);
				}
				break;
			case PSkillEffect::受ダメージバフ:
				if (Pスキル->対象 == PSkillTarget::スキル対象)
				{
					Aスキル->バフ確率[BuffType::被ダメ軽減] = 1.0;
					Aスキル->バフ持続[BuffType::被ダメ軽減] = Pスキル->持続時間;
					Aスキル->バフ反映率[BuffType::被ダメ軽減] = Pスキル->効果量;
				} else {
					//自己
					バフ使用(BuffType::被ダメ軽減, Pスキル->効果量, Pスキル->持続時間);
				}
				break;
			case PSkillEffect::スキルチャージ獲得:
				for (int a = 0; a < CV::最大Aスキル数; a++)
				{
					合計クールダウン[a] += Pスキル->効果量;
				}
				break;
			}
		}
	};
}