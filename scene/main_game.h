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
		W_SettleLog Win_Settlelog;//収支ウィンドウ

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
			windows.push_back(&Win_Settlelog);

			ToolBar.SetWindow(windows);
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

			tm time;//とりあえず乱数初期化
			Time::GetDate(&time);
			Rand::Reset(time.tm_hour * 3600 + time.tm_min * 60 + time.tm_sec);


			for (int a = 0; a < 9; a++)
			{
				Guild::P->is装備開発[a] = true;
				Guild::P->is新規[a] = false;
				Guild::P->装備所持数[a] = 3;
			}

			for (int a = 0; a < CV::最大素材ランク; a++)
			{
				Guild::P->素材数[a] = 20;
			}

			Guild::P->部門経験値[ManagementType::経営] = Rand::Get(100);
			Guild::P->部門経験値[ManagementType::人事] = Rand::Get(100);
			Guild::P->部門経験値[ManagementType::製造] = Rand::Get(100);
			Guild::P->部門経験値[ManagementType::探索] = Rand::Get(100);

			Guild::P->部門Lv[ManagementType::経営] = 1;
			Guild::P->部門Lv[ManagementType::人事] = 1;
			Guild::P->部門Lv[ManagementType::製造] = 1;
			Guild::P->部門Lv[ManagementType::探索] = 1;

			//戦術ダミー
			for (int a = 0; a < 100; a++)
			{
				Management::managements.emplace_back(a, a / 20, ManagementType(Rand::Get(3)), Rand::Get(200) + 10, Rand::Get(200000000), Rand::Coin(0.5));
			}
			//来客ダミー
			for (int a = 0; a < 100; a++)
			{
				Customer::customers.emplace_back(0,Rand::Get(1300));

				Customer::my_customers.push_back(Customer::customers[a]);
			}
			//求人＆初期人材ダミー
			Warker::data.reserve(2048);
			for (int a = 0; a < 25; a++)
			{
				Warker::data.emplace_back();
				Warker::data[a].Make(a, a%5 , 1, "ナナシ");
				if (a < 15)
				{
					Warker::data[a].所属 = 0;
					Warker::data[a].就活 = -1;
				} else {
					Warker::data[a].所属 = 0;
					Warker::data[a].就活 = -1;
				}
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

			for (int a = 0; a < 12; a++)
			{
				Guild::P->製造メンバー.push_back(&Warker::data[a] + 15);
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

			for (auto& it : Guild::P->製造割当)
			{
				it = 5;
			}
		
			Game::is停止 = true;

			Guild::P->製造力計算();
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

			MSystem::背景.DrawExtend({ 0,WindowBox::ツールバー高さ,Window::GetWidth(),Window::GetHeight() - WindowBox::ツールバー高さ });

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
					if ( Game::日付 % CV::月日数 == 0)
					{
						StartMonth();
					}
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
					if (Game::日付 % CV::月日数 == CV::月日数 - 1)
					{
						EndMonth();
					}
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

			UseTactics();

			//求人追加、仮処理
			if (Warker::data.size() < 45)
			{
				Warker::data.emplace_back();
				Warker::data.back().Make((int)Warker::data.size() - 1, Rand::Get(4), 1, "ナナシ");
			}
		}

		//月初の処理
		void StartMonth()
		{

		}
		//月末の処理
		void EndMonth()
		{

		}

		//製造処理
		void MakeItem()
		{
			Guild::P->製造処理();
		}

		//探索処理
		void ExploreDungeon()
		{
			Guild::P->探索処理();
		}

		//●終日処理
		//経営戦術確定
		void UseTactics()
		{

		}

		//●探索処理

		//●戦闘処理
	};
}