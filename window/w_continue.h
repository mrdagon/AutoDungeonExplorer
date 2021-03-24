﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	enum class UIタイトル
	{
		題字,
		ボタン,
		ライセンス,

		始めから_ウィンドウ,
		始めから_ボタン,
		始めから_説明枠,
		始めから_開始ボタン,

		続きから_ウィンドウ,
		続きから_セーブデータ枠,
		続きから_階層,
		続きから_日数,
		続きから_難易度,
		続きから_パーティ,
		続きから_削除,

		クレジット_ウィンドウ,
		クレジット_説明枠,
		COUNT,
		PAGE = (int)UIPage::タイトル
	};

	/*セーブデータ選択ポップアップウィンドウ*/
	class W_Continue : public UIWindow
	{
	private:
		class UIセーブ削除 : public UIObject
		{
		public:
			W_Continue* 親;
			int データID = 0;

			void Draw派生()
			{
				DrawUI(UIType::グループ明 , &UIDesign::Brown );
				MFont::M->DrawRotate({ GetCenterX(),GetCenterY() }, 1, 0, Color::Red, "X");
			}


			void Click()
			{
				//ポップアップ呼び出して、はいを選んだら削除

				//xマーク-クリックで確認してから削除

				親->確認ウィンドウ.文章.テキスト = "データを削除しますか？";
				int 戻り値 = 親->確認ウィンドウ.Openポップアップ();
				if (戻り値 == 1)
				{
					親->DeleteSaveData(データID);
				}
			}
		};

		class GUI_セーブスロット : public UIObject
		{
		private:

		public:
			W_Continue* 親;
			SaveData データ;

			UIセーブ削除 削除;
			UITextFrame 日数;
			UITextFrame フロア;
			UITextFrame 難易度;
			UIObject パーティ;

			GUI_セーブスロット(int id,std::string& ファイル名):
				データ(id,ファイル名)
			{}

			void Init(W_Continue* 親 , std::string name , int id)
			{
				データ.ファイル名 = name;
				SetUI(UIタイトル::続きから_セーブデータ枠 , id );

				日数.SetUI("日数", UIタイトル::続きから_日数 , DesignType::セット1, 0, this);
				フロア.SetUI("フロア",  UIタイトル::続きから_階層 , DesignType::セット1, 0, this);
				難易度.SetUI("難易度",  UIタイトル::続きから_難易度, DesignType::セット1, 0, this);
				パーティ.SetUI( UIタイトル::続きから_パーティ, 0, this);
				削除.SetUI( UIタイトル::続きから_削除, 0, this);

				//個オブジェクトを親に追加
				削除.データID = id;
				削除.親 = 親;
				this->親 = 親;
			}

			void Draw派生() override
			{
				//全体枠
				UIDesign::Brown.Draw(UIType::フレーム, GetX(), GetY(), GetW(), GetH());

				//枠＋文字
				日数.Draw();
				フロア.Draw();
				難易度.Draw();
				削除.Draw();

				//パーティ
				パーティ.DrawUI(UIType::グループ明, &UIDesign::Brown);
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					int no = データ.メインパーティ職業[a];
					if (no < 0) { continue; }
					ExplorerClass::data[no].ちびimage[0][1]->DrawRotate({ パーティ.GetX() + a * パーティ.layout->並べx + 30 , パーティ.GetY() }, 2, 0);
				}

				//xマークは親に追加
			}

			bool Check派生(double px, double py) override
			{
				return 削除.CheckInput(px, py);
			}

			void Click()
			{
				//再開するか確認
				親->確認ウィンドウ.文章.テキスト = "この記録から再開しますか？";
				int 戻り値 = 親->確認ウィンドウ.Openポップアップ();
				if (戻り値 == 1)
				{
					親->is表示 = false;
					親->ポップアップリザルト = 1;
					親->選択スロット = データ.id;
				}
			}
		};

	public:
		W_Popup 確認ウィンドウ;
		std::vector<GUI_セーブスロット> セーブスロット;
		int 選択スロット;

		void Init()
		{
			//セーブデータの取得
			UpdateSaveData();

			//共通初期化
			Set(WindowType::Continue, IconType::情報);
			SetPos(UIタイトル::続きから_ウィンドウ , true , true);
			縦内部幅 = 170 + UILayout::Data(UIタイトル::続きから_ウィンドウ).並べy * セーブスロット.size();
			
			スクロール位置 = 0;

			//ポップアップ初期化
			確認ウィンドウ.Init();			
		}

		void Update()
		{
			SetPos(UIタイトル::続きから_ウィンドウ, true , true);
			縦内部幅 = 170 + UILayout::Data(UIタイトル::続きから_ウィンドウ).並べy * セーブスロット.size();
		}

		SaveData* GetSave()
		{
			return &セーブスロット[選択スロット].データ;
		}

		void DeleteSaveData(int id)
		{
			//削除して再取得
			std::string filename = "file/save/";
			filename += セーブスロット[id].データ.ファイル名;
			std::remove( filename.c_str() );

			UpdateSaveData();
		}

		void UpdateSaveData()
		{
			std::vector<std::string> ファイル名;
			SaveData::Getセーブデータinフォルダ(ファイル名);

			ui_objects.clear();
			セーブスロット.clear();

			int a = 0;
			for (auto& it : ファイル名)
			{
				セーブスロット.emplace_back(a, it);
				a++;
			}

			a = 0;
			for (auto& it : ファイル名)
			{
				セーブスロット[a].Init(this, it, a);
				this->ui_objects.push_back(&セーブスロット[a]);//削除ボタンはクリック可なので親に追加
				a++;
			}
		}
	};
}