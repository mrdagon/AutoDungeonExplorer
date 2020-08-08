//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
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

		W_Config Win_Config;//設定ウィンドウ
		W_Popup Win_Title;//タイトルに戻る



		//ゲーム開始時の初期化処理
		void Init()
		{
			//ギルド初期化
			Guild::P = &Guild::data;

			windows.clear();

			BetaInit();

			//ウィンドウ初期化
			windows.push_back(&Win_Item);
			windows.push_back(&Win_Factory);
			windows.push_back(&Win_Dungeon);
			windows.push_back(&Win_Party);
			windows.push_back(&Win_Management);
			windows.push_back(&Win_Material);
			windows.push_back(&Win_Quest);
			windows.push_back(&Win_Guild);
			windows.push_back(&Win_EventLog);

			ToolBar.SetConfig(&Win_Config,&Win_Title);

			Win_Config.Init();
			Win_Title.Init();

			ToolBar.Init();

			int XXX = 100;
			for (auto& it : windows)
			{
				it->Init();
				it->座標.y = 120;
				it->座標.x = XXX;
				it->is表示 = false;
				XXX += 50;
			}

			Win_Item.is表示 = true;
			Win_Factory.is表示 = true;
			Win_Dungeon.is表示 = true;
			Win_Party.is表示 = true;		

			WinPosSaveAndLoad(FileMode::Read);

			ToolBar.SetWindow(windows);


			Win_Config.is表示 = true;
			Win_Title.is表示 = false;
		}

		void Init(GameType 難易度)
		{}

		void Init(SaveData* セーブ)
		{}

		//デモ版用初期化処理
		void BetaInit()
		{
			//仮データ作成

			//とりあえずBGM鳴らす
			auto test = MMusic::BGM[BGMType::準備中].Play(true);

			tm time;//とりあえず乱数初期化
			Time::GetDate(&time);
			Rand::Reset(time.tm_hour * 3600 + time.tm_min * 60 + time.tm_sec);

			for (int a = 1; a <= 9; a++)
			{
				Guild::P->is装備開発[a] = true;
				Guild::P->is新規[a] = false;
				Guild::P->装備所持数[a] = 3;
			}

			for (auto& it : Guild::P->is素材発見)
			{
				it = false;
			}

			for (int a = 0; a < 4; a++)
			{
				Guild::P->総素材 += 30;
				Guild::P->素材数[a] = 30;
				Guild::P->is素材発見[a] = true;
			}

			Guild::P->投資経験値[ManagementType::経営] = 0;
			Guild::P->投資経験値[ManagementType::人事] = 0;
			Guild::P->投資経験値[ManagementType::製造] = 0;
			Guild::P->投資経験値[ManagementType::探索] = 0;

			Guild::P->投資Lv[ManagementType::経営] = 1;
			Guild::P->投資Lv[ManagementType::人事] = 1;
			Guild::P->投資Lv[ManagementType::製造] = 1;
			Guild::P->投資Lv[ManagementType::探索] = 1;

			Guild::P->資金 = 100000;

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				Guild::P->製造Lv[CraftType(a)] = 1;
				Guild::P->完成品[CraftType(a)] = -1;
			}

			//求人＆初期人材ダミー
			Guild::P->製造要員.clear();
			Guild::P->探索要員.clear();
			Guild::P->ギルメン控え.clear();
			Guild::P->製造要員.reserve(128);
			Guild::P->探索要員.reserve(1024);

			Guild::P->最大パーティ数 = 1;
				
			//ギルメン初期
			for (int a = 0; a < 5; a++)
			{
				Guild::P->探索要員.emplace_back();
				Guild::P->探索要員.back().Make(a, a, 1, "ギルメン");
				Guild::P->探索パーティ[0].メンバー[a] = &Guild::P->探索要員[a];
			}

			//製造初期
			for (int a = 0; a < 4; a++)
			{
				Guild::P->製造要員.emplace_back();
				Guild::P->製造要員.back().Make(a, 1, CraftType(a), "クラフト");
				Guild::P->製造メンバー[CraftType(a % 4)].clear();
				Guild::P->製造メンバー[CraftType(a%4)].push_back(&Guild::P->製造要員[a]);
			}

			//仮ダンジョン
			Dungeon::data.clear();
			Dungeon::data.reserve(100);
			for (int a = 0; a < 100; a++)
			{
				Dungeon::Add(a, "名も無き迷宮", IconType::森 , 100, std::min(a / 10,4), a+1 , 1 , (a % 10 == 9));
				Dungeon::data[a].探索率計算();
			}
			Dungeon::data[0].is発見 = true;

			for (int a = 0; a < CV::最大パーティ数; a++)
			{
				Guild::P->探索パーティ[a].探索先 = &Dungeon::data[0];
				Guild::P->探索パーティ[a].基礎ステ再計算();
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
				Process();
				Draw();

				//60fpsの調整
				while (1)
				{
					if (Time::GetNowCount() - time > frame * 50 / 3.0) { break; }
				}

				if (Game::isゲーム終了 == true) { Game::isゲーム終了 = false; break; }

			}

			WinPosSaveAndLoad(FileMode::Write);
		}

		//操作処理
		void Input()
		{
			if (Input::key.F1.on && CV::isデバッグ) { Game::isデバッグ大きさ表示 = !Game::isデバッグ大きさ表示; }

			if (Input::mouse.Right.on)
			{
				Game::is停止 = !Game::is停止;
				//Game::isヘルプ = !Game::isヘルプ;
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
			W_Drag::Drop();

		}
		//描画処理
		void Draw()
		{
			Game::アニメーション時間++;

			//暫定背景表示-時間で明るさ変化
			//if(Game::時間 > 22 * 360) { MSystem::背景.SetColor({ 0,0,0 }); }
			//else if (Game::時間 > 20 * 360) { MSystem::背景.SetColor({255-(Game::時間 - 20 * 360)*255/720,255 - (Game::時間 - 20 * 360) * 255 / 720,255 - (Game::時間 - 20 * 360) * 255 / 720 }); }//20~22で暗くなる
			//else if (Game::時間 < 4 * 360) { MSystem::背景.SetColor({0,0,0}); }
			//else if (Game::時間 < 6 * 360) { MSystem::背景.SetColor({ (Game::時間 - 4 * 360)*255/720,(Game::時間 - 4 * 360) * 255 / 720,(Game::時間 - 4 * 360) * 255 / 720 }); }//4~6で明るくなる
			//else { MSystem::背景.SetColor(Color::White); }

			const int back_w = 384;
			const int back_h = 288;

			int b倍率 = (Window::GetHeight() - ToolBar.ツールバー高さ) / back_h + 1;
			int h余り = (Window::GetHeight() - ToolBar.ツールバー高さ) % back_h - back_h;

			int w余り = Window::GetWidth() - back_w * b倍率;
			int x差分 = w余り / 2;
			int y差分 = h余り / 2;

			int 幅 = back_w * b倍率;
			int 高 = back_h * b倍率;

			//背景描画
			if (y差分 > 0)
			{
				Drawing::Rect({ 0,ToolBar.ツールバー高さ,Window::GetWidth() , y差分 }, Color(113, 63, 90), true);
				Drawing::Rect({ 0,Window::GetHeight() - y差分,Window::GetWidth() , y差分 }, Color(57, 45, 85), true);
			}
			y差分 += ToolBar.ツールバー高さ;
			x差分 = (Window::GetWidth() - 幅);
			
			static int scr_x = 0;

			MSystem::メインゲーム背景.DrawExtend({ x差分 + scr_x - 幅   ,y差分,幅,高 });
			MSystem::メインゲーム背景.DrawExtend({ x差分 + scr_x        ,y差分,幅,高 });
			MSystem::メインゲーム背景.DrawExtend({ x差分 + scr_x + 幅   ,y差分,幅,高 });
			MSystem::メインゲーム背景.DrawExtend({ x差分 + scr_x + 幅 * 2,y差分,幅,高 });

			MSystem::メインゲーム前景.DrawExtend({ x差分 - 幅,y差分,幅,高 });
			MSystem::メインゲーム前景.DrawExtend({ x差分     ,y差分,幅,高 });
			MSystem::メインゲーム前景.DrawExtend({ x差分 + 幅,y差分,幅,高 });

			for (auto& it : windows)
			{
				if (it->is表示 == false) { continue; };
				it->Draw();
			}

			ToolBar.Draw();

			bool isH = ToolBar.CheckInfo();
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
				no_help.SetHelp("",40);
				no_help.Info();
			}

			W_Drag::Draw();

			if (CV::isデバッグ)
			{
				CSVDraw();
				CSVCheckInput();
			}

		}

		//各種処理
		void Process()
		{

			UseManagement();

			if (Game::is停止) { return; }

			int 加速度;

			加速度 = Game::ゲームスピード;

			if (Game::時間 > Game::就寝時間 || Game::時間 < Game::起床時間) { 加速度 = Game::ゲームスピード * 8; }

			for (int a = 0; a < 加速度; a++)
			{
				if (Game::時間 == Game::始業時間)
				{
					StartWork();
				}
				if (Game::時間 == Game::終業時間)
				{
					EndWork();
				}
				if (Game::時間 >= 360 * 24) 
				{
					EndDay();
				}

				//探索＆製造中
				Guild::P->探索処理();

				if (Game::is仕事中 == true)
				{
					Guild::P->アイテム販売();
					Guild::P->製造処理();
				}

				Game::時間++;
			}
		}

		//業務開始の処理
		void StartWork()
		{
			MMusic::BGM[BGMType::探検中].Play();
			MSound::効果音[SEType::探索開始].Play();

			Game::is仕事中 = true;
			Guild::P->製造力計算();
			Guild::P->探索開始();
			Guild::P->装備取置解除();
		}

		//業務終了の処理
		void EndWork()
		{
			MMusic::BGM[BGMType::準備中].Play();
			MSound::効果音[SEType::探索終了].Play();
			Game::is仕事中 = false;
		}

		//一日終了の処理
		void EndDay()
		{
			Game::日付++;
			Game::時間 = 0;

			//記録追加
			Guild::P->R団員.push_back(Guild::P->総人数);
			Guild::P->R資金.push_back(Guild::P->資金);
			Guild::P->R販売.push_back(Guild::P->総販売);
			Guild::P->R製造.push_back(Guild::P->総製造);
			Guild::P->R素材在庫.push_back(Guild::P->総素材);
			Guild::P->R地図数.push_back(Guild::P->総地図);
			Guild::P->R討伐数.push_back(Guild::P->総討伐);
			Guild::P->R全滅数.push_back(Guild::P->総全滅);
			Guild::P->R名声.push_back(Guild::P->名声);

			Guild::P->装備自動更新();
		}

		//投資処理
		void UseManagement()
		{
			if (Guild::P->選択戦術 == MSkillType::COUNT) { return; }

			//お金足りてたら戦術実行

			if (Guild::P->資金 >= Management::data[(int)Guild::P->選択戦術].消費資金)
			{
				Management::data[(int)Guild::P->選択戦術].Active(Guild::P);
				Guild::P->選択戦術 = MSkillType::COUNT;
			}
		}

		//●セーブ処理
		//ウィンドウ位置保存
		bool WinPosSaveAndLoad(FileMode 保存or読み込み)
		{
			//バイナリ形式で保存
			std::string fname = "file/save/";
			fname += TX::Save_システムファイル名;

			File file( fname.c_str() , 保存or読み込み, false);

			//ファイルが無いのに読み込もうとしたら初期データにする
			if (file.GetFileMode() == FileMode::None)
			{
				return false;
			}

			std::vector<WindowBox*> wins;

			wins.push_back(&Win_Item);
			wins.push_back(&Win_Factory);
			wins.push_back(&Win_Dungeon);
			wins.push_back(&Win_Party);
			wins.push_back(&Win_Management);
			wins.push_back(&Win_Material);
			wins.push_back(&Win_Quest);
			wins.push_back(&Win_Guild);
			wins.push_back(&Win_EventLog);

			for (auto& it : wins)
			{
				file.ReadWrite(it->座標.x);
				file.ReadWrite(it->座標.y);
				file.ReadWrite(it->縦幅);
				file.ReadWrite(it->is表示);
			}

			return true;
		}
	};
}