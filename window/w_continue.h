//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*セーブデータ選択ポップアップウィンドウ*/
	class W_Continue : public WindowBox
	{
	private:

		class GUI_セーブスロット : public GUI_Object
		{
		private:

		public:
			W_Continue* 親;
			SaveData データ;

			GUI_セーブスロット(int id,std::string& ファイル名):
				データ(id,ファイル名)
			{}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 0, 1);

				//セーブスロット番号
				//MFont::BMSize.DrawBold({ px + Lp(50) ,py + Lp(51) }, Color::White, Color::Black, { データ.id / 10 , データ.id % 10 }, false);
				//日数
				MFont::BMSize.DrawBold({ px + Lp(52) ,py + Lp(53) }, Color::White, Color::Black, { データ.日数 , TX::Tool_日付 }, true);
				//到達フロア
				MFont::BMSize.DrawBold({ px + Lp(54) ,py + Lp(55) }, Color::White, Color::Black, { データ.最深フロア , " 階" }, true);				
				//難易度
				MFont::BMSize.DrawBold({ px + Lp(56) ,py + Lp(57) }, Color::White, Color::Black, { "Normal" }, true);
				//クリア済み
				MFont::BMSize.DrawBold({ px + Lp(58) ,py + Lp(59) }, Color(128,128,255), Color::Black, { "Clear" }, false);

				//第一パーティ
				for (int a = 0; a < CV::パーティ人数; a++)
				{
					int no = データ.メインパーティ職業[a];
					if (no < 0) { continue; }
					Job::data[no].Img[0][1]->DrawRotate({ px + Lp(60) + Lp(61) * a ,py + Lp(62) }, 2, 0);
				}

				//xマーク
				MIcon::アイコン[IconType::閉じる].DrawRotate({ px + Lp(63) ,py + Lp(64) }, 1 ,0);
			}

			void Click(double px, double py)
			{
				//xマーク-クリックで確認してから削除
				if (Point(px, py).Hit(&Rect(Lp(63)-Lp(65), Lp(64)- Lp(65), Lp(65)*2, Lp(65)*2)) == true)
				{

					親->確認ウィンドウ.文章.text = "データを削除しますか？";
					int 戻り値 = 親->確認ウィンドウ.ポップアップ呼び出し();
					if (戻り値 == 1)
					{
						親->確認ウィンドウ.文章.text = "本当に削除しますか？";
						int 戻り値 = 親->確認ウィンドウ.ポップアップ呼び出し();
						if (戻り値 == 1)
						{
							親->DeleteSave(データ.id);
						}
					}
					return;
				}

				//確認無しで再開
				親->is表示 = false;
				親->ポップアップ戻り値 = 1;
				親->選択スロット = データ.id;
			}
		};

	public:
		W_Popup 確認ウィンドウ;
		std::vector<GUI_セーブスロット> セーブスロット;
		int 選択スロット;

		void Init()
		{
			種類 = WindowType::Guild;

			名前 = "記録を選ぶ";
			略記 = "記録";
			アイコン = IconType::情報;
			横幅 = 280;
			縦幅 = 170;
			最小縦 = 170;
			最大縦 = 170;
			縦内部幅 = 170;
			スクロール位置 = 0;
			isスクロールバー表示 = true;
			ポップアップ戻り値 = 0;

			//
			確認ウィンドウ.Init();

			//セーブデータの取得
			UpdateSave();
		}

		SaveData* GetSave()
		{
			return &セーブスロット[選択スロット].データ;
		}

		void DeleteSave(int id)
		{
			//削除して再取得
			std::string filename = "file/save/";
			filename += セーブスロット[id].データ.ファイル名;

			std::remove( filename.c_str() );

			UpdateSave();
		}

		void UpdateSave()
		{
			std::vector<std::string> ファイル名;
			SaveData::Getセーブデータinフォルダ(ファイル名);

			gui_objects.clear();
			セーブスロット.clear();
			int a = 0;
			for (auto& it : ファイル名)
			{
				セーブスロット.emplace_back(a, it);
				セーブスロット[a].親 = this;
				a++;
			}


			for (auto& it : セーブスロット)
			{
				gui_objects.push_back(&it);
			}

			SetCSVPage(24);
		}

		void GUI_Update()
		{
			横幅 = Lp(40);
			縦幅 = Lp(41);

			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;

			int a = 0;
			for (auto& it : セーブスロット)
			{
				it.位置 = { Lp(42) , Lp(43) + Lp(44) * a , 横幅 - Lp(45) , Lp(46) };
				a++;
			}
		}
	};
}