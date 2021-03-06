﻿//Copyright © 2019 (´･@･)
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
		W_Item Win_Item;//装備品
		W_Management Win_Management;//経営戦術
		W_Material Win_Material;//素材
		W_Party Win_Party;//ギルメン
		W_Quest Win_Quest;//クエスト

		W_Config Win_Config;//設定ウィンドウ
		W_Popup Win_Title;//タイトルに戻る

		Guild guild;

		//ゲーム開始時の初期化処理
		MainGame()
		{}

		void Init()
		{
			//ギルド初期化
			Guild::P = &guild;

			windows.clear();

			BetaInit();

			//ウィンドウ初期化
			windows.push_back(&Win_Item);
			windows.push_back(&Win_Dungeon);
			windows.push_back(&Win_Party);
			windows.push_back(&Win_Management);
			windows.push_back(&Win_Material);
			windows.push_back(&Win_Quest);
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
			Win_Dungeon.is表示 = true;
			Win_Party.is表示 = true;		

			WindowSaveLoad(FileMode::Read);

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
			//BGM鳴らす
			auto test = MMusic::BGM[BGMType::準備中].Play(true);
			
			//乱数初期化
			tm time;
			Time::GetDate(&time);
			Rand::Reset(time.tm_hour * 3600 + time.tm_min * 60 + time.tm_sec);


			Guild::P->Init();

			//ダンジョン初期化
			Dungeon::ResetData();
			Quest::ResetData();
			Management::ResetData();

			Game::is停止 = true;
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

			WindowSaveLoad(FileMode::Write);
		}

		//操作処理
		void Input()
		{
			if (Input::key.F1.on && CV::isデバッグ) { Game::isデバッグ大きさ表示 = !Game::isデバッグ大きさ表示; }

			if (Input::mouse.Right.on)
			{
				MSound::効果音[SE::ボタンクリック].Play();
				Game::is停止 = !Game::is停止;
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

			if ((Game::時間 > Game::就寝時間 || Game::時間 < Game::起床時間) && Config::is夜間加速) { 加速度 = Game::ゲームスピード * 4; }

			for (int a = 0; a < 加速度; a++)
			{
				if (Game::時間 == Game::始業時間 - 1 && Game::is直前スキル自動習得 == true)
				{
					Game::is停止 = true;
					Game::is直前スキル自動習得 = false;
					break;
				}

				if (Game::時間 == Game::始業時間)
				{
					StartWork();
				}
				if (Game::時間 == Game::終業時間)
				{
					EndWork();
				}
				if (Game::時間 >= Game::日没時間) 
				{
					EndDay();
				}

				//探索＆製造中
				Guild::P->探索処理();
				Game::時間++;
			}
		}

		//業務開始の処理
		void StartWork()
		{
			MMusic::BGM[BGMType::探検中].Play();
			MSound::効果音[SEType::探索開始].Play();

			Game::is仕事中 = true;
			Guild::P->探索開始();
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
		}

		//投資処理
		void UseManagement()
		{
			
		}

		//●セーブ処理
		bool Save(SaveData* セーブデータ)
		{
			File file(セーブデータ->ファイル名.c_str() ,FileMode::Write, false);

			//ヘッダー部分セーブ

			//
			Game::SaveLoad(file, FileMode::Write);
			Dungeon::SaveLoad(file, FileMode::Write);
			EventLog::SaveLoad(file, FileMode::Write);
			Item::SaveLoad(file, FileMode::Write);
			Management::SaveLoad(file, FileMode::Write);
			Quest::SaveLoad(file, FileMode::Write);
			Effect::SaveLoad(file, FileMode::Write);
			Guild::P->SaveLoad(file, FileMode::Write);
			WindowSaveLoad(FileMode::Write);
		}

		bool Load(SaveData* セーブデータ)
		{
			File file(セーブデータ->ファイル名.c_str(), FileMode::Read, false);

			//ヘッダー部分ロードスキップ

			//
			Game::SaveLoad(file, FileMode::Read);
			Dungeon::SaveLoad(file, FileMode::Read);
			EventLog::SaveLoad(file, FileMode::Read);
			Item::SaveLoad(file, FileMode::Read);
			Management::SaveLoad(file, FileMode::Read);
			Quest::SaveLoad(file, FileMode::Read);
			Effect::SaveLoad(file, FileMode::Read);
			Guild::P->SaveLoad(file, FileMode::Read);
			WindowSaveLoad(FileMode::Read);

		}

		//ウィンドウ位置保存
		bool WindowSaveLoad(FileMode 保存or読み込み)
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
			wins.push_back(&Win_Dungeon);
			wins.push_back(&Win_Party);
			wins.push_back(&Win_Management);
			wins.push_back(&Win_Material);
			wins.push_back(&Win_Quest);
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