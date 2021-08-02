//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	class IFacility
	{

	};

	/*ギルド*/
	class Guild
	{
	public:
		//内部クラスにして循環参照解決する場合
		class Party
		{
		private:

		public:
			Party()
			{
				魔物.reserve(6);

				for (auto& it : メンバー)
				{
					it = nullptr;
				}
			}

			int パーティID;

			Dungeon* 探索先 = nullptr;
			OrderType 探索指示 = OrderType::なし;

			Explorer* メンバー[CV::パーティ人数];

			//★戦闘用
			std::vector<Monster> 魔物;//戦闘中の相手

			std::vector<Battler*> 味方;
			std::vector<Battler*> 敵;

			int 戦闘中行動待機 = 0;

			//★探検一時ステータス
			double 獲得経験値;
			EnumArray<std::array<int, CV::上限素材ランク>, CraftType> 入手素材;
			std::vector<int> 獲得財宝;//最大で10個まで、0は未発見
			int 地図発見数 = 0;
			int ボス撃破数 = 0;
			int 探索部屋数 = 0;//今回の探索での探索した部屋数

			ExplorType 探索状態 = ExplorType::編成中;
			int 待ち時間 = 0;//移動、戦闘後、素材回収中などの待ち時間

			int 部屋ID = 0;//探索,戦闘中の部屋番号

			//★探索中演出用
			CraftType 発見素材種;
			int 移動量 = 0;
			int 暗転 = 0;
			Image* 発見物 = nullptr;//地図、宝箱、鉱脈、木
			int 発見物X座標 = 0;

			//編成画面の処理
			bool 編成_探索フロア増減(int 変化値)
			{
				if (変化値 == -1)
				{
					for (auto& it : Dungeon::data)
					{
						if (it.ID > 探索先->ID && it.is発見)
						{
							探索先 = &it;
							return true;
						}
					}
				}
				else
				{

					for (int a = (int)Dungeon::data.size() - 1; a >= 0; a--)
					{
						if (Dungeon::data[a].ID < 探索先->ID && Dungeon::data[a].is発見)
						{
							探索先 = &Dungeon::data[a];
							return true;
						}
					}
				}

				return false;
			}

			bool 編成_探索指示(int 変化値)
			{
				int n = int(探索指示) + 変化値;

				if (n == (int)OrderType::COUNT) { n = 0; }
				if (n < 0) { n = (int)OrderType::COUNT - 1; }

				探索指示 = OrderType(n);
			}

			void 基礎ステ再計算()
			{
				味方.clear();
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					味方.push_back(メンバー[a]);
					メンバー[a]->Pスキル.clear();
				}

				//パーティスキルや装備品スキル等の計算
				for (int a = 0; a < (int)味方.size(); a++)
				{
					味方[a]->隊列ID = a;
					味方[a]->パーティID = パーティID;
					味方[a]->基礎ステータス計算();
					味方[a]->戦闘後回復 += Guild::P->戦闘後回復;
					味方[a]->基礎Pスキル補正(味方, 敵);

					味方[a]->現在HP = 味方[a]->補正ステ[StatusType::HP];
				}
			}

			void 探索開始()
			{
				暗転 = 255;
				移動量 = 0;
				発見物X座標 = 0;
				発見物 = nullptr;

				探索状態 = ExplorType::移動中;
				待ち時間 = CV::探索開始時待ち時間;

				//各種リセット
				獲得経験値 = 0;
				地図発見数 = 0;
				ボス撃破数 = 0;
				探索部屋数 = 0;

				魔物.clear();
				敵.clear();

				for (auto& itA : 入手素材)
				{
					for (auto& itB : itA)
					{
						itB = 0;
					}
				}
				
				獲得財宝.clear();

				//パーティメンバーの体力回復、ステータス再計算等
				//経験値獲得とレベルアップ
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					メンバー[a]->探索開始();
				}

				基礎ステ再計算();

				for (auto& it : 味方)
				{
					it->エフェクトリセット();
				}

				//０人パーティは全滅扱いにする
				if (味方.size() == 0) { 探索状態 = ExplorType::全滅中; }
			}

			void 探索終了()
			{


				//素材獲得
				for (int a = 0; a < CV::素材系統; a++)
				{
					for (int b = 0; b < CV::上限素材ランク; b++)
					{
						CraftType ct = (CraftType)a;
						Guild::P->素材数[ct][b] += 入手素材[ct][b];
						Guild::P->資金 += Material::data[ct][b].価格 * 入手素材[ct][b];
						Guild::P->総素材 += 入手素材[ct][b];
						Guild::P->is素材発見[ct][b] = true;
					}
				}

				//アクセサリー獲得
				for (auto& it : 獲得財宝)
				{
					//石碑の欠片は取得出来ないようにする
					if (it > 0)
					{
						Guild::P->アクセサリー所持数[it]++;
					}
				}

				//経験値獲得とレベルアップ
				double 経験値補正 = Guild::P->経験値倍率;

				for (int a = 0; a < CV::パーティ人数; a++)
				{
					if (メンバー[a] == nullptr) { continue; }

					メンバー[a]->探索終了();
					メンバー[a]->経験値 += 獲得経験値 * (経験値補正 + メンバー[a]->経験値補正);
					メンバー[a]->レベルアップ判定();
				}
			}

			void 探索処理()
			{

				//探索終了判定
				if (Game::時間 == Game::終業時間)
				{
					撤退開始();
				}
				if (Game::時間 == Game::起床時間)
				{
					探索状態 = ExplorType::編成中;
				}

				//待機中(収集中、戦闘後待機、宝部屋etc)				
				switch (探索状態)
				{
				case ExplorType::戦闘中:
					戦闘処理();
					break;
				case ExplorType::移動中:
					待ち時間--;
					移動量 += CV::探索移動速度;
					if (待ち時間 == 0) { 部屋抽選(); }
					break;
				case ExplorType::収集中:
					収集処理();
					break;
				case ExplorType::撤退中:
					撤退処理();
					break;
				case ExplorType::全滅中:
					if (暗転 > CV::全滅暗さ)
					{
						暗転--;
					}
				case ExplorType::リザルト中:
					//特に処理しない
					break;
				}
			}

			void エフェクト更新()
			{
				//エフェクト更新
				for (auto& it : 味方)
				{
					it->エフェクト更新();
				}
				for (auto& it : 敵)
				{
					it->エフェクト更新();
				}
			}

			//部屋選択関係の処理
			void 部屋抽選()
			{
				std::vector<int> room_deck;
				room_deck.clear();

				Set部屋抽選リスト(room_deck, true);

				//抽選
				部屋ID = room_deck[Rand::Get((int)room_deck.size() - 1)];
				部屋選択処理();
			}

			void Set部屋抽選リスト(std::vector<int>& room_deck, bool isボス戦)
			{
				//階段発見済み
				int no = 探索先->Is階段発見可能();
				if (no >= 0)
				{
					room_deck.push_back(no);
					return;
				}


				//ボス発見済み
				if (探索先->Isボス戦闘可能(探索部屋数))
				{
					room_deck.push_back(CV::ボス部屋ID);
					return;
				}

				//未探索部屋から抽選
				double 未開探索率 = Guild::P->未開探索補正;

				for (auto& it : メンバー)
				{
					if (it == nullptr) { continue; }

					未開探索率 += it->未探索発見補正;
				}

				if (Rand::Coin(未開探索率))
				{
					for (int a = 0; a < 探索先->部屋.size(); a++)
					{
						if (探索先->部屋[a].is入場 ||
							探索先->部屋[a].is探索 ||
							探索先->部屋[a].種類 == RoomType::ボス ||
							探索先->部屋[a].種類 == RoomType::階段) {
							continue;
						}
						room_deck.push_back(a);
					}
				}

				if (room_deck.size() > 0) { return; }

				//未探索部屋0 or 未開探索パッシブ無しの場合
				for (int a = 0; a < 探索先->部屋.size(); a++)
				{
					if (探索先->部屋[a].is入場 ||
						探索先->部屋[a].種類 == RoomType::ボス ||
						探索先->部屋[a].種類 == RoomType::階段
						)
					{
						continue;
					}

					room_deck.push_back(a);
				}
			}

			void 部屋選択処理()
			{
				//入室フラグON
				探索先->部屋[部屋ID].is入場 = true;

				switch (探索先->部屋[部屋ID].種類)
				{
				case RoomType::ザコ:
					探索状態 = ExplorType::戦闘中;
					戦闘開始(5);
					break;
				case RoomType::素材:
					探索状態 = ExplorType::収集中;
					収集開始();
					break;
				case RoomType::財宝:
					探索状態 = ExplorType::戦闘中;
					戦闘開始(6);
					break;
				case RoomType::階段:
					探索状態 = ExplorType::収集中;
					階段発見();
					break;
				case RoomType::ボス:
					探索状態 = ExplorType::戦闘中;
					ボス戦開始();
					break;
				}

			}

			//収集関係
			void 収集開始()
			{
				部屋探索完了共通();

				switch (Rand::Get(2))
				{
				case 0:
					発見素材種 = CraftType::木材;
					発見物 = &MIcon::UI[IconType::探索_伐採];
					break;
				case 1:
					発見素材種 = CraftType::鉄材;
					発見物 = &MIcon::UI[IconType::探索_採掘];
					break;
				case 2:
					発見素材種 = CraftType::石材;
					発見物 = &MIcon::UI[IconType::探索_採石];
					break;
				default:
					break;
				}

				待ち時間 = CV::地図発見待機;
				発見物X座標 = CV::収集待機A;
			}

			void 階段発見()
			{
				発見物 = &MIcon::UI[IconType::地図];
				探索先->is地図発見[部屋ID] = true;

				//新たなダンジョンを開放
				Dungeon::data[探索先->探索地図ID[部屋ID]].is発見 = true;

				MSound::効果音[SE::地図発見].Play();

				獲得財宝.push_back(-2);//-2は階段

				Quest::達成チェック(QuestType::ダンジョン発見, 探索先->探索地図ID[部屋ID] + 1, Guild::P->アクセサリー所持数);
				Quest::開始チェック(探索先->探索地図ID[部屋ID] + 1);

				//
				待ち時間 = CV::収集待機A;
				発見物X座標 = CV::収集待機A;


				std::string text = "";
				text += std::to_string((探索先->探索地図ID[部屋ID] + 1));
				text += "Fへの地図を発見";

				EventLog::Add(text.c_str(), Game::日付, LogType::探索);
			}

			void 収集処理()
			{
				if (発見物X座標 > 0)
				{
					移動量 += CV::探索移動速度;
					発見物X座標 -= CV::探索移動速度;

					if (発見物X座標 == 0 && 発見物 != &MIcon::UI[IconType::地図])
					{
						素材精算処理();
					}
				}

				待ち時間--;
				if (待ち時間 == 0)
				{
					発見物 = nullptr;
					探索状態 = ExplorType::移動中;
					待ち時間 = CV::収集待機B;
				}
			}

			void 素材精算処理()
			{
				//素材数とレア率を計算
				int 素材数 = 1;

				double レア素材確率 = 0;
				double 素材数増加率 = 0;
				double 上位チャンス = (探索先->ID - 探索先->層 * 10) * 0.05;
				int ランク = Rand::Coin(上位チャンス) ? 探索先->層 + 1 : 探索先->層;

				//パッシブ補正
				for (auto& it : 味方)
				{
					レア素材確率 += it->レア素材収集補正;
					素材数増加率 += it->素材収集量;
				}

				//素材増加パッシブ
				if (Rand::Coin(素材数増加率))
				{
					素材数++;
				}

				//パッシブ効果
				if (Rand::Coin(レア素材確率))
				{
					ランク++;
				}

				//幸運効果
				if (Rand::Coin(0.2))
				{
					ランク++;
				}

				for (int a = 0; a < 素材数; a++)
				{

					入手素材[発見素材種][ランク]++;

					Effect::Add素材(Material::data[発見素材種][ランク].image, a , -1 , パーティID);
				}
			}

			void 魔物精算処理(Monster& it)
			{
				//素材獲得と経験値獲得処理
				int 素材数 = 1;

				double 上位チャンス = (探索先->ID - 探索先->層 * 10) * 0.05;
				int ランク = Rand::Coin(上位チャンス) ? 探索先->層 + 1 : 探索先->層;

				double レア率 = it.種族->レア素材率;
				double 素材数増加率 = 0;
				double 素材獲得率 = 0.2;
				CraftType 素材種 = CraftType::革材;

				switch (Rand::Get(2))
				{
				case 0: 素材種 = CraftType::革材; break;
				case 1: 素材種 = CraftType::骨材; break;
				case 2: 素材種 = CraftType::魔材; break;
				}

				//パッシブ計算
				for (auto& it : 味方)
				{
					レア率 += it->レア素材剥取補正;
					素材数増加率 += it->素材剥取量;
				}

				//素材増加パッシブ
				if (Rand::Coin(素材数増加率))
				{
					素材数++;
				}

				//パッシブ効果
				if (Rand::Coin(レア率))
				{
					ランク++;
				}

				//幸運補正
				if (Rand::Coin(it.種族->レア素材率))
				{
					ランク++;
				}

				if (it.isボス == true)
				{
					ランク++;
					素材数 += 4;
					素材獲得率 = 1.0;
				}

				//素材獲得
				for (int a = 0; a < 素材数; a++)
				{
					if (Rand::Coin(素材獲得率) == false) { continue; }

					入手素材[素材種][ランク]++;
					Effect::Add素材(Material::data[素材種][ランク].image, a, it.隊列ID , パーティID);
				}

				//レアアイテムは勝利時に精算
				獲得経験値 += it.Get経験値();
			}

			//戦闘関係
			void 戦闘開始(int 敵数)
			{
				敵.clear();
				魔物.clear();

				int 抽選回数[CV::最大魔物出現数] = { 0 };
				int 残り抽選数 = 敵数;

				//敵の生成
				//6枠から抽選、同じ物は２回まで、大型は一回まで
				//大型モンスターは２枠使う、最後の抽選で選んだら再抽選
				while (true)
				{
					int rng = Rand::Get((int)探索先->雑魚モンスター.size() - 1);

					if (抽選回数[rng] == 2)
					{
						continue;
					}

					抽選回数[rng]++;
					残り抽選数--;
					if (残り抽選数 <= 0) { break; }
				}

				for (int a = 0; a < CV::最大魔物出現数; a++)
				{
					for (int b = 0; b < 抽選回数[a]; b++)
					{
						魔物.emplace_back(探索先->雑魚モンスター[a], 探索先->雑魚Lv[a]);
					}
				}

				敵.resize(魔物.size());

				for (int a = 0; a < (int)魔物.size(); a++)
				{
					敵[a] = &魔物[a];
					敵[a]->隊列ID = a;
					敵[a]->パーティID = パーティID;
				}

				//戦闘開始時のパッシブと初期化
				for (auto& it : 味方)
				{
					it->戦闘開始(味方, 敵);
				}

				for (auto& it : 敵)
				{
					it->戦闘開始(敵, 味方);
				}

				戦闘中行動待機 = CV::戦闘開始後待ち時間;
			}

			void ボス戦開始()
			{
				if (Config::isボス戦時等速 == true)
				{
					Game::ゲームスピード = 1;
				}

				敵.clear();
				魔物.clear();

				for (int b = 0; b < (int)探索先->ボスモンスター.size(); b++)
				{
					if (探索先->ボスモンスター[b]->ID <= 0)
					{
						continue;
					}

					魔物.emplace_back(探索先->ボスモンスター[b], 探索先->ボスLv[b]);
				}

				敵.resize(魔物.size());

				for (int a = 0; a < 魔物.size(); a++)
				{
					敵[a] = &魔物[a];
					敵[a]->隊列ID = a;
					敵[a]->パーティID = パーティID;
				}

				//BGM変更
				if (探索先->ID % 10 == 9)
				{
					MMusic::BGM[BGMType::エリアボス].Play();
				} else {
					MMusic::BGM[BGMType::通常ボス].Play();

				}

				//SEを鳴らしたりする

				//戦闘開始時のパッシブ
				for (auto& it : 味方)
				{
					it->戦闘開始(味方, 敵);
				}

				for (auto& it : 敵)
				{
					it->戦闘開始(敵, 味方);
				}

				戦闘中行動待機 = CV::戦闘開始後待ち時間;
			}

			void 戦闘処理()
			{
				//全員の全スキルのCT計算
				if (戦闘中行動待機 > 0)
				{
					戦闘中行動待機--;
					return;
				}

				bool isBreak = false;

				//スキルCT上がってるかチェック
				//同時に動くのは１キャラのみ
				for (auto& it : 味方)
				{
					if (it->Aスキル使用チェック(味方, 敵) == true)
					{
						isBreak = true;
						戦闘中行動待機 = CV::戦闘1ターン待ち時間;
						break;
					}
				}
				if (isBreak == false)
				{
					for (auto& it : 敵)
					{
						if (it->Aスキル使用チェック(敵, 味方) == true)
						{
							isBreak = true;
							戦闘中行動待機 = CV::戦闘1ターン待ち時間;
							break;
						}
					}
				}

				//スキルクールタイムとバフ/デバフ持続計算
				for (auto& it : 味方)
				{
					it->ターン経過();
				}
				for (auto& it : 敵)
				{
					it->ターン経過();
				}

				for (auto& it : 魔物)
				{
					if (it.is気絶 == false && it.現在HP <= 0)
					{
						it.is気絶 = true;
						魔物精算処理(it);
					}
				}


				戦闘終了判定();
			}

			bool 戦闘終了判定()
			{
				//味方全滅or逃走
				int is生存 = false;
				for (auto& it : 味方)
				{
					if (it->現在HP > 0)
					{
						is生存 = true;
					}
				}

				if (!is生存)
				{
					戦闘敗北();
					探索先->部屋[部屋ID].is入場 = false;
					return true;
				}
				//敵全滅
				is生存 = false;
				for (auto& it : 敵)
				{
					if (it->現在HP > 0)
					{
						is生存 = true;
					}
				}

				if (!is生存)
				{
					戦闘勝利();
					探索先->部屋[部屋ID].is入場 = false;
					return true;
				}

				return false;
			}

			void 戦闘勝利()
			{
				std::string text = "";
				bool isボス戦後 = false;
				
				//クエスト処理
				switch (探索先->部屋[部屋ID].種類)
				{
				case RoomType::ボス:
					isボス戦後 = true;
					text = 魔物[0].種族->名前;
					text += "を討伐";
					EventLog::Add(text.c_str(), Game::日付, LogType::ボス);

					MMusic::BGM[BGMType::探検中].Play();
					探索先->isボス生存 = false;
					//ボスレアドロップ取得
					for (auto& it : 魔物)
					{
						if (it.種族->ボスドロップ[0] != 0)
						{
							獲得財宝.push_back(it.種族->ボスドロップ[0]);
						}
						if (it.種族->ボスドロップ[1] != 0)
						{
							獲得財宝.push_back(it.種族->ボスドロップ[1]);
						}
					}

					if (探索先->ボス地図ID != 0)
					{
						Dungeon::data[探索先->ボス地図ID].is発見 = true;
					}

					Guild::P->総討伐++;
					Quest::達成チェック(QuestType::累計FOE討伐, Guild::P->総討伐 , Guild::P->アクセサリー所持数);
					Quest::達成チェック(QuestType::固定FOE討伐, 探索先->ID+1 , Guild::P->アクセサリー所持数);
					break;
				case RoomType::財宝:
					探索先->部屋[部屋ID].種類 = RoomType::ザコ;
					探索先->発見財宝数++;
					財宝獲得();
					break;
				}

				部屋探索完了共通();

				//体力回復
				for (int a = 0; a < (int)味方.size(); a++)
				{
					int 回復量 = (int)((味方[a]->戦闘後回復 + Guild::P->戦闘後回復) * 味方[a]->補正ステ[StatusType::HP]);

					if (isボス戦後 == true)
					{
						回復量 = 味方[a]->補正ステ[StatusType::HP];
					}

					味方[a]->現在HP += 回復量;
					味方[a]->現在HP = std::min(味方[a]->現在HP, 味方[a]->補正ステ[StatusType::HP]);

					味方[a]->エフェクトダメージ( -回復量 );
					味方[a]->現在クールダウン = 0;
					味方[a]->現在スキルスロット = 0;
				}

				探索状態 = ExplorType::収集中;
				待ち時間 = CV::戦闘終了後待ち時間;
			}

			void 戦闘敗北()
			{
				if (探索先->部屋[部屋ID].種類 == RoomType::ボス)
				{
					MMusic::BGM[BGMType::探検中].Play();
				}

				int ザコ討伐数 = 0;
				for (auto& it : 敵)
				{
					ザコ討伐数++;
				}

				探索先->部屋[部屋ID].is入場 = false;
				探索状態 = ExplorType::全滅中;
				MSound::効果音[SE::全滅].Play();
				Guild::P->総全滅++;
			}

			void 財宝獲得()
			{
				//探索先->発見財宝++;
				獲得財宝.push_back(探索先->財宝[部屋ID - 10]->ID);
				探索先->is財宝発見[部屋ID - 10] = true;
				発見物 = &MIcon::UI[IconType::宝箱];

				std::string text = "";
				text = 探索先->財宝[部屋ID - 10]->名前;
				text += "を入手";

				EventLog::Add(text.c_str(), Game::日付, LogType::探索);
			}

			void 撤退開始()
			{
				if (探索状態 == ExplorType::戦闘中)
				{
					int ザコ討伐数 = 0;
					for (auto& it : 敵)
					{
						if (it->現在HP <= 0)
						{
							ザコ討伐数++;
						}
					}
				}

				for (auto& it : 味方)
				{
					if (it->現在HP <= 0) { continue; }
					it->エフェクト移動(-6, 10000);
				}

				探索状態 = ExplorType::撤退中;
				探索先->部屋[部屋ID].is入場 = false;
				待ち時間 = CV::撤退後待ち時間;
			}

			void 撤退処理()
			{
				待ち時間--;
				if (待ち時間 == 0)
				{
					探索終了();
					探索状態 = ExplorType::リザルト中;
				}
			}

			void 部屋探索完了共通()
			{
				探索部屋数++;
				探索先->部屋[部屋ID].is探索 = true;
				探索先->部屋[部屋ID].is入場 = false;
				探索先->探索率計算();

				if (探索先->探索率 * 100 >= 探索先->ボス発見探索率 && 探索先->isボス発見 == false)
				{
					std::string text = "";
					text += std::to_string((探索先->ID + 1));
					text += "FでF.O.Eが姿を表す";
					MSound::効果音[SE::ボス発見].Play();
					探索先->isボス発見 = true;
					EventLog::Add(text.c_str(), Game::日付, LogType::ボス);
				}
			}

			bool SaveLoad(File& ファイル, FileMode 読み書きモード)
			{

			}

		};

		int 資金 = 0;

		EnumArray<int[CV::上限素材ランク], CraftType> 素材数;
		EnumArray<bool[CV::上限素材ランク], CraftType> is素材発見;

		//従業員一覧
		Explorer 探索者[CV::上限探索者登録数];

		Party パーティ[CV::上限パーティ数];
		Explorer* 控え探索者[CV::最大控え人数];

		int 最大パーティ数 = 1;

		int 街Lv = 1;
		int 街経験値 = 0;

		//経営戦術効果
		double 戦闘後回復 = 0.1;
		double 経験値倍率 = 1.0;
		double 素材消費倍率 = 1.0;//素材消費倍率
		double 未開探索補正 = 0.0;//未探索部屋抽選補正

		//装備品
		std::array<int, CV::上限アクセサリ種類> アクセサリー所持数 = { 0 };
		//各種記録_Record
		int 総石版 = 0;

		int 累計ボス撃破 = 0;
		int 累計財宝獲得 = 0;
		int 累計素材発見 = 0;
		int 累計魔物撃破 = 0;

		int 総素材 = 0;
		int 総フロア = 0;//全探索フロア数
		int 総討伐 = 0;//討伐時増加
		int 総全滅 = 0;//全滅時増加

		inline static Guild* P;//プレイヤーのギルド

		Guild()
		{
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				パーティ[a].パーティID = a;
			}
		}

		void Init()
		{
			for (int a = 1; a <= 9; a++)
			{
				アクセサリー所持数[a] = 0;
			}

			for (auto& itA : is素材発見)
			{
				for (auto& itB : itA)
				{
					itB = false;
				}
			}

			for (auto& it : 控え探索者)
			{
				it = nullptr;
			}

			探索者登録(0, "レイヤ");
			探索者登録(1, "ガーディ");
			探索者登録(2, "デディ");
			探索者登録(3, "メンター");
			探索者登録(4, "ウィード");
			//オカ
			探索者登録(6, "ラディ");
			探索者登録(7, "アーサー");
			探索者登録(8, "ベルセク");
			//トリ
			//プリ
			探索者登録(11, "パスダー");


			//初期、探索者、テスト用
			//for (int a = 0; a < 5; a++)
			//{
			//	パーティ[0].メンバー[a] = &Guild::P->探索者[a];
			//}

			//パーティ初期化
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				パーティ[a].探索先 = &Dungeon::data[0];
				パーティ[a].基礎ステ再計算();
			}
		}


		Explorer* GetMember(int パーティID, int 並びID)
		{
			if (パーティID < 0)
			{
				return 控え探索者[並びID];
			}
			else
			{
				return パーティ[パーティID].メンバー[並びID];
			}
		}

		bool MemberToID(Explorer* メンバー , int& パーティID ,  int& 並びID)
		{
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				for (int b = 0; b < CV::パーティ人数; b++)
				{
					if (パーティ[a].メンバー[b] == メンバー)
					{
						パーティID = a;
						並びID = b;
						return true;
					}
				}
			}

			for (int a = 0; a < CV::最大控え人数; a++)
			{
				if (控え探索者[a] == メンバー)
				{
					パーティID = -1;
					並びID = a;
					return true;
				}
			}

			パーティID = -2;
			並びID = -1;
			return false;
		}

		void 探索者登録(ID_Job 求人職業 , std::string 求人名前)
		{
			for (int i = 0; i < CV::上限探索者登録数; i++)
			{
				if (探索者[i].is登録済み == false)
				{
					探索者[i].登録(i, 求人職業,1, 求人名前);
					for (auto& it : 控え探索者)
					{
						if (it != nullptr) { continue; }

						it = &探索者[i];
						break;
					}
					break;
				}
			}
		}

		void 除名(Explorer* メンバー)
		{
			bool isHit = false;
			int パーティID = 0;
			int 並びID = 0;

			if (MemberToID(メンバー, パーティID, 並びID) == false) { return; }

			if (パーティID >= 0)
			{
				//探索パーティから除名
				アクセサリー所持数[パーティ[パーティID].メンバー[並びID]->装備[2]->ID]++;
				パーティ[パーティID].メンバー[並びID]->is登録済み = false;
				パーティ[パーティID].メンバー[並びID] = nullptr;
			} else {
				//控えから除名
				アクセサリー所持数[控え探索者[並びID]->装備[2]->ID]++;
				控え探索者[並びID]->is登録済み = false;

				for (int a = 並びID; a < CV::最大控え人数 - 1; a++)
				{
					控え探索者[a] = 控え探索者[a + 1];
				}
				控え探索者[CV::最大控え人数 - 1] = nullptr;
			}

		}

		void 基礎ステ再計算()
		{
			for (int i = 0; i < 3; i++)
			{
				パーティ->基礎ステ再計算();
			}
		}

		//操作処理
		void 操作_配置変更(int パーティA , int 並びA , int パーティB , int 並びB)
		{
			Explorer* メンバーA;
			Explorer* メンバーB;

			if (パーティA < 0)
			{
				メンバーA = 控え探索者[並びA];
			} else {
				メンバーA = パーティ[パーティA].メンバー[並びA];
			}

			if (パーティB < 0)
			{
				メンバーB = 控え探索者[並びB];
				控え探索者[並びB] = メンバーA;
			} else {
				メンバーB = パーティ[パーティB].メンバー[並びB];
				パーティ[パーティB].メンバー[並びB] = メンバーA;
			}

			if (パーティA < 0)
			{
				控え探索者[並びA] = メンバーB;
			} else {
				パーティ[パーティA].メンバー[並びA] = メンバーB;
			}

			ソート控え();
		}

		void 操作_装備在庫(Explorer* メンバー , int 新装備ID , int 装備スロット)
		{
			//現在の装備を外して、在庫+1
			アクセサリー所持数[メンバー->装備[装備スロット]->ID]++;
			

			//装備を変更して、在庫-1
			メンバー->装備[装備スロット] = &Item::accessory_data[新装備ID];
			アクセサリー所持数[新装備ID]--;
		}

		void 操作_装備スワップ(Explorer* メンバーA,int 装備部位A, Explorer* メンバーB, int 装備部位B)
		{
			std::swap(メンバーA->装備[装備部位A], メンバーB->装備[装備部位B]);
		}

		bool 操作_武器防具クリック(Explorer* メンバー , int 装備スロット)
		{
			//素材チェック
			std::array<int, CV::上限素材ランク> メイン素材;
			std::array<int, CV::上限素材ランク> サブ素材;

			CraftType メイン種 = メンバー->装備[装備スロット]->GetMainRecipe(メイン素材);
			CraftType サブ種 = メンバー->装備[装備スロット]->GetSubRecipe(サブ素材);

			//素材数チェック
			for (int i = 0; i < CV::上限素材ランク ; i++)
			{
				if (素材数[メイン種][i] < メイン素材[i]) { return false; }
				if (素材数[サブ種][i] < サブ素材[i] / 2) { return false; }
			}

			//素材を消費
			for (int i = 0; i < CV::上限素材ランク; i++)
			{
				素材数[メイン種][i] -= メイン素材[i];
				素材数[サブ種][i] -= サブ素材[i] / 2;
			}

			メンバー->装備強化(装備スロット);
			return true;
		}

		bool 操作_装備素材チェック(Explorer* メンバー, int 装備スロット)
		{
			//素材チェック
			std::array<int, CV::上限素材ランク> メイン素材;
			std::array<int, CV::上限素材ランク> サブ素材;

			CraftType メイン種 = メンバー->装備[装備スロット]->GetMainRecipe(メイン素材);
			CraftType サブ種 = メンバー->装備[装備スロット]->GetSubRecipe(サブ素材);

			//素材数チェック
			for (int i = 0; i < CV::上限素材ランク; i++)
			{
				if (素材数[メイン種][i] < メイン素材[i]) { return false; }
				if (素材数[サブ種][i] < サブ素材[i] / 2) { return false; }
			}

			return true;
		}

		Explorer* 操作_スキル画面前後(Explorer* メンバー , int 前後)
		{
			//パーティ1～3、控え
			int パーティID,並びID;

			if (MemberToID(メンバー, パーティID, 並びID) == false) { return メンバー; }

			int no = 並びID;
			Explorer* member;

			while (1)
			{
				no += 前後;
				if (no < 0) { no = CV::パーティ人数 - 1; }
				if (no > CV::パーティ人数 - 1) { no = 0; }

				member = パーティ[パーティID].メンバー[no];

				if (member != nullptr)
				{
					return member;
				}
			}


		}

		void 操作_除名(Explorer* メンバー)
		{
			除名(メンバー);
		}

		void 操作_控え移動(int パーティID, int 並びID)
		{
			if (パーティID < 0)
			{
				//控えから削除
				//最後に追加
				for (int a = 0; a < CV::最大控え人数 - 1; a++)
				{
					if (控え探索者[a] == nullptr)
					{
						控え探索者[a] = 控え探索者[並びID];
						break;
					}
				}
				控え探索者[並びID] = nullptr;

				ソート控え();
			}
			else
			{
				//現在パーティから削除
				//最後に追加
				for (int a = 0; a < CV::最大控え人数 - 1; a++)
				{
					if (控え探索者[a] == nullptr)
					{
						控え探索者[a] = パーティ[パーティID].メンバー[並びID];
						break;
					}
				}
				パーティ[パーティID].メンバー[並びID] = nullptr;
			}
		}

		void ソート控え()
		{
			for (int a = 0; a < CV::最大控え人数 - 1; a++)
			{
				if (控え探索者[a] == nullptr)
				{
					控え探索者[a] = 控え探索者[a + 1];
					控え探索者[a + 1] = nullptr;
				}
			}
		}

		//探索関係処理
		void 探索開始()
		{
			//探索指示変更
			装備強化チェック();
			投資予約チェック();
			探索指示チェック();
			予約スキルチェック();

			//エフェクト初期化
			for (int a = 0; a < CV::上限パーティ数; a++)
			{
				Effect::アニメ[a].clear();
				Effect::素材[a].clear();
				Effect::文字[a].clear();
			}

			for (int a = 0; a < 最大パーティ数; a++)
			{
				//パーティ人数をチェック
				パーティ[a].探索開始();
			}
		}

		void 探索処理()
		{
			for (int a = 0; a < 最大パーティ数; a++)
			{
				パーティ[a].探索処理();
			}
		}

		void エフェクト更新()
		{
			for ( int i = 0; i < 最大パーティ数; i++)
			{
				パーティ[i].エフェクト更新();
			}
			Effect::Update();
		}

		void 探索終了()
		{
			//戦利品の回収

			装備強化チェック();
			投資予約チェック();
			探索指示チェック();
			予約スキルチェック();
		}


		//探索開始前後に行う処理
		void 予約スキルチェック()
		{
			

		}

		void 装備強化チェック()
		{

		}

		void 探索指示チェック()
		{

		}

		void 投資予約チェック()
		{

		}

		//クエスト関係
		void リザルト解除()
		{
			for (int i = 0; i < 最大パーティ数; i++)
			{
				パーティ[i].探索状態 = ExplorType::編成中;
			}
		}

		bool SaveLoad(File& ファイル, FileMode 読み書きモード)
		{

		}
	};
}