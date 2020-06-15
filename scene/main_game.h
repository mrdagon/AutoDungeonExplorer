//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;

	/*メインゲーム*/
	class MainGame
	{
	private:

	public:
		//各種変数
		std::vector<WindowBox*> windows;

		W_ToolBar ToolBar;

		W_Dungeon  Win_Dungeon;//ダンジョン
		W_EventLog Win_EventLog;//ログ
		W_Guild Win_Guild;//ギルド情報
		W_Item Win_Item;//装備品
		W_Factory Win_Factory;//製造
		W_Management Win_Management;//経営戦術
		W_Material Win_Material;//素材
		W_Party Win_Party;//ギルメン
		W_Quest Win_Quest;//クエスト
		W_Recruit Win_Recruit;//求職

		W_Config Win_Config;//設定ウィンドウ
		W_Popup Win_Title;//タイトルに戻る

		//ゲーム開始時の初期化処理
		void Init()
		{
			//ギルド初期化
			Guild::P = &Guild::data[0];
			Guild::P->id = 0;

			BetaInit();

			//ウィンドウ初期化
			windows.push_back(&Win_Item);
			windows.push_back(&Win_Factory);
			windows.push_back(&Win_Dungeon);
			windows.push_back(&Win_Party);
			windows.push_back(&Win_Recruit);
			windows.push_back(&Win_Management);
			windows.push_back(&Win_Material);
			windows.push_back(&Win_Quest);
			windows.push_back(&Win_Guild);
			windows.push_back(&Win_EventLog);

			ToolBar.SetConfig(&Win_Config,&Win_Title);

			Win_Config.init();
			Win_Title.init();

			ToolBar.init();

			int XXX = 100;
			for (auto& it : windows)
			{
				it->init();
				it->座標.y = 120;
				it->座標.x = XXX;
				it->is表示 = false;
				XXX += 50;
			}

			ToolBar.SetWindow(windows);

			Win_Item.is表示 = true;
			Win_Factory.is表示 = true;
			Win_Dungeon.is表示 = true;
			Win_Party.is表示 = true;
			Win_Recruit.is表示 = true;
			Win_Material.is表示 = true;

			Win_Config.is表示 = true;
			Win_Title.is表示 = false;

			for (int a = 0; a < CV::最大パーティ数; a++)
			{
				Guild::P->探索パーティ[a].ギルドID = Guild::P->id;
			}


		}

		//デモ版用初期化処理
		void BetaInit()
		{
			//仮データ作成

			//とりあえずBGM鳴らす
			auto test = MMusic::メインBGM.Play(true);

			tm time;//とりあえず乱数初期化
			Time::GetDate(&time);
			Rand::Reset(time.tm_hour * 3600 + time.tm_min * 60 + time.tm_sec);

			for (int a = 0; a < 9; a++)
			{
				Guild::P->is装備開発[a] = true;
				Guild::P->is新規[a] = false;
				Guild::P->装備所持数[a] = 3;
			}

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				for (int a = 0; a < 1; a++)
				{
					Guild::P->総素材 += 1000;
					Guild::P->素材数[CraftType(b)][a] = 1000;
					Guild::P->is素材発見[CraftType(b)][a] = true;
				}
			}

			Guild::P->部門経験値[ManagementType::経営] = Rand::Get(100);
			Guild::P->部門経験値[ManagementType::人事] = Rand::Get(100);
			Guild::P->部門経験値[ManagementType::製造] = Rand::Get(100);
			Guild::P->部門経験値[ManagementType::探索] = Rand::Get(100);

			Guild::P->部門Lv[ManagementType::経営] = 1;
			Guild::P->部門Lv[ManagementType::人事] = 1;
			Guild::P->部門Lv[ManagementType::製造] = 1;
			Guild::P->部門Lv[ManagementType::探索] = 1;

			Guild::P->資金 = 1000000;

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				Guild::P->製造Lv[CraftType(a)] = 1;
				Guild::P->完成品[CraftType(a)] = -1;
			}

			//戦術仮データ読み込み
			Management::Load();

			//求人＆初期人材ダミー
			Warker::data.reserve(2048);
			for (int a = 0; a < 25; a++)
			{
				Warker::data.emplace_back();
				Warker::data[a].Make(a, a%5 , 1, "ナナシ");
				
				Warker::data[a].所属 = 0;
			}

			//初期求人
			for (int a = 0; a < 10; a++)
			{
				Warker::data.emplace_back();
				Warker::data.back().Make((int)Warker::data.size() - 1, Rand::Get(4), 1, "ナナシ");
			}

			//仮ダンジョン
			for (int a = 0; a < 100; a++)
			{
				Dungeon::Add(a, "名も無き迷宮", DungeonType(Rand::Get((int)DungeonType::COUNT - 1)), 100, a / 20, a+1);
				Dungeon::data[a].探索率計算(Guild::P->id);
			}
			Dungeon::data[0].is発見[0] = true;

			//ギルメン初期-仮配置
			for (int a = 0; a < 15; a++)
			{
				Guild::P->ギルメン.push_back(&Warker::data[a]);
			}

			for (int a = 0; a < 10; a++)
			{

				Guild::P->製造メンバー[CraftType(a%4)].push_back(&Warker::data[a+15]);
				Warker::data[a + 15].製造配置 = CraftType(a % 4);
			}

			for (int a = 0; a < Guild::P->最大パーティ数; a++)
			{
				for (int b = 0; b < CV::パーティ人数; b++)
				{
					Guild::P->探索パーティ[a].メンバー[b] = &Warker::data[a * CV::パーティ人数 + b];
				}
			}

			Guild::P->探索パーティ[0].探索先 = &Dungeon::data[0];
			Guild::P->探索パーティ[1].探索先 = &Dungeon::data[0];
			Guild::P->探索パーティ[2].探索先 = &Dungeon::data[0];

			Guild::P->探索パーティ[0].スキルステ計算();
			Guild::P->探索パーティ[1].スキルステ計算();
			Guild::P->探索パーティ[2].スキルステ計算();

			Guild::P->最大パーティ数 = 3;

			Game::is停止 = true;

			Guild::P->製造力計算();

			Quest::BetaQuest();
		}

		//メインループ処理
		void Main()
		{
			double frame = 0;
			double time = Time::GetNowCount();

			while (System::Update(true,false))
			{
				frame++;
				
				Input();
				GameProcess();
				Draw();

				//60fpsの調整
				while (1)
				{
					if (Time::GetNowCount() - time > frame * 50 / 3.0) { break; }
				}
			}

			if (CV::isデバッグ)
			{
				DebugEnd("file/layout/layout_data.txt");
				DebugEnd("file/layout/backup.txt");
			}

		}

		//操作処理
		void Input()
		{
			if (Input::key.F1.on && CV::isデバッグ) { SV::gui_check = !SV::gui_check; }

			if (Input::mouse.Right.on)
			{
				Game::isヘルプ = !Game::isヘルプ;
			}

			ToolBar.操作();
			for (int a = (int)windows.size() - 1; a >= 0; a--)
			{
				if (windows[a]->操作() == true)
				{
					//操作したのは最後に持っていく
					if (windows[a]->前面Check())
					{
						windows.push_back(windows[a]);
						windows.erase(windows.begin() + a);
					}
					break;
				}
			}
			W_Drag_Drop::操作();

		}
		//描画処理
		void Draw()
		{
			Game::アニメーション時間++;

			//暫定背景表示-時間で明るさ変化
			if(Game::時間 > 22 * 360) { MSystem::背景.SetColor({ 0,0,0 }); }
			else if (Game::時間 > 20 * 360) { MSystem::背景.SetColor({255-(Game::時間 - 20 * 360)*255/720,255 - (Game::時間 - 20 * 360) * 255 / 720,255 - (Game::時間 - 20 * 360) * 255 / 720 }); }//20~22で暗くなる
			else if (Game::時間 < 4 * 360) { MSystem::背景.SetColor({0,0,0}); }
			else if (Game::時間 < 6 * 360) { MSystem::背景.SetColor({ (Game::時間 - 4 * 360)*255/720,(Game::時間 - 4 * 360) * 255 / 720,(Game::時間 - 4 * 360) * 255 / 720 }); }//4~6で明るくなる
			else { MSystem::背景.SetColor(Color::White); }

			MSystem::背景.DrawExtend({ 0,0,Window::GetWidth(),Window::GetHeight()});

			for (auto& it : windows)
			{
				if (it->is表示 == false) { continue; };
				it->Draw();
			}

			ToolBar.Draw();

			bool isH = ToolBar.CheckInformation();
			if (Input::mouse.y < WindowBox::ツールバー高さ)
			{
				isH = true;
			}

			for (int a = (int)windows.size() - 1; a >= 0; a--)
			{
				if (windows[a]->is表示 == false) { continue; };
				if (windows[a]->CheckInfo())
				{
					isH = true;
					break;
				}
			}

			if (isH == false && Game::isヘルプ == true)
			{
				static GUI_Help no_help;
				no_help.SetHelp("右クリックでヘルプ表示ON/OFF",40);
				no_help.Info();
			}

			//Win_Title.Draw();
			//Win_Config.Draw();

			W_Drag_Drop::Draw();

			if (CV::isデバッグ)
			{
				DebugDraw();
				DebugCheckInput();
			}

		}

		//各種処理
		void GameProcess()
		{
			if (Game::is停止) { return; }

			int 加速度;

			加速度 = Game::ゲームスピード;

			if (Game::時間 > Game::就寝時間 || Game::時間 < Game::起床時間) { 加速度 = 64; }

			for (int a = 0; a < 加速度; a++)
			{
				if (Game::時間 == Game::起床時間)
				{
					StartDay();
				}
				if (Game::時間 == Game::始業時間)
				{
					StartWork();
				}
				if (Game::時間 == Game::終業時間)
				{
					EndWork();
				}
				if (Game::時間 == Game::就寝時間)
				{
					EndDay();
				}
				if (Game::時間 >= 360 * 24) 
				{
					Game::日付++;
					Game::時間 = 0;
				}

				//探索＆製造中
				ExploreDungeon();

				if (Game::is仕事中 == true)
				{
					SellItem();
					MakeItem();
					ExploreDungeon();
				}


				Game::時間++;
			}
		}

		//一日開始の処理
		void StartDay()
		{
			Game::is仕事中 = false;
		}

		//業務開始の処理
		void StartWork()
		{
			Game::is仕事中 = true;
			Guild::P->製造力計算();
			Guild::P->探索開始();
			Guild::P->装備取置解除();
		}

		//業務終了の処理
		void EndWork()
		{
			Game::is仕事中 = false;
		}
		//一日終了の処理
		void EndDay()
		{
			Game::is仕事中 = false;

			//求人追加、仮処理
			if (Warker::data.size() < 45)
			{
				Warker::data.emplace_back();
				Warker::data.back().Make((int)Warker::data.size() - 1, Rand::Get(4), 1, "ナナシ");
			}

			Guild::P->装備自動更新();
		}

		//月初の処理
		void StartMonth()
		{

		}
		//月末の処理
		//void EndMonth()
		//{
		//
		//}

		//製造処理
		void MakeItem()
		{
			Guild::P->製造処理();
		}

		//販売処理
		void SellItem()
		{
			Guild::P->アイテム販売();
		}

		//探索処理
		void ExploreDungeon()
		{
			Guild::P->探索処理();
		}


		//●探索処理

		//●戦闘処理
	};
}