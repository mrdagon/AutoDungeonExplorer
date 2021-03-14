//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	enum UIPage
	{
		タイトル,
		COUNT
	};
	
	class UILayout
	{
	private:
		inline static int now_page = 0;
		inline static int now_index[UIPage::COUNT];
		inline static std::string data_name[UIPage::COUNT];
		inline static std::vector<UILayout> data[UIPage::COUNT];

	public:
		std::string 登録名 = "";
		int x = 0, y = 0;
		int w = 0, h = 0;
		int 並べx = 0, 並べy = 0;//並べないやつは自由に使える？
		int 画像ID = 0;

		UILayout()
		{}

		UILayout(std::string 登録名):
			登録名(登録名)
		{}

		UILayout( std::string 登録名 , int x, int y, int w, int h, int 並べx, int 並べy, int 画像ID):
			登録名(登録名),
			x(x),
			y(y),
			w(w),
			h(h),
			並べx(並べx),
			並べy(並べy),
			画像ID(画像ID)
		{}

		static UILayout& GetData(std::string key, int group)
		{
			//登録名を同じ物を探す
			//オブジェクト作成時に一回だけ呼び出す
			for (int a = 0; a < data[group].size(); a++)
			{
				if (data[group][a].登録名 == key)
				{
					return data[group][a];
				}
			}

			//登録データが無い場合新規追加
			data[group].emplace_back(key);
			return data[group].back();
		}

		static void LoadData()
		{
			//ページ名一覧とページ毎の選択中indexを読み込み
			File file("file/layout/index.csv",FileMode::Read,false);
			auto csv = file.GetCsvToString2();
			file.Close();

			//全てのページを読み込み
			for (int a = 0; a < UIPage::COUNT; a++)
			{
				data_name[a] = csv[a][0];
				now_index[a] = std::stoi(csv[a][1]);

				std::string file_name = "file/layout/";
				file_name += data_name[a];
				file_name += ".csv";

				File page_file( file_name.c_str() ,FileMode::Read,false);
				auto csv2 = page_file.GetCsvToString2();
				page_file.Close();

				for (int b = 0; b < csv2.size(); b++)
				{
					data[a].emplace_back(
						csv2[b][0],
						std::stoi(csv2[b][1]),
						std::stoi(csv2[b][2]),
						std::stoi(csv2[b][3]),
						std::stoi(csv2[b][4]),
						std::stoi(csv2[b][5]),
						std::stoi(csv2[b][6]),
						std::stoi(csv2[b][7])
					);
				}
			}
		}


		static void SaveData()
		{
			//ページ名と選択index
			File file("file/layout/index.csv", FileMode::Write, false);
		
			//各ページの情報
			for (int a = 0; a < UIPage::COUNT; a++)
			{
				file.AddLine( { data_name[a] , "," , now_index[a]});

				std::string file_name = "file/layout/";
				file_name += data_name[a];
				file_name += ".csv";

				File page_file(file_name.c_str(), FileMode::Write, false);

				for (auto& it : data[a])
				{
					page_file.AddLine({	it.登録名 , "," ,
									it.x , ",",
									it.y , ",",
									it.w , ",",
									it.h , ",",
									it.並べx , ",",
									it.並べy , ",",
									it.画像ID 
						});

				}
			}

		}

		//現在のページ、オブジェクト一覧、選択中のオブジェクトパラメータを表示
		static void Draw()
		{
			//現在のページ番号と名前


			//現在のページのアイテム


			//選択中のアイテムのパラメータ7種

		
		
		}

		//入力を受け取って、ページ切り替え、選択状態ON/OFF、パラメータ調整処理を行う
		static void Input()
		{
			const int 連打st = 30;
			const int 連打rp = 5;

			//Numpadで選択オブジェクト変更
			if (Input::key.Numpad2.IsPush(連打st,連打rp))
			{
				now_index[now_page]--;
				if (now_index[now_page] < 0) { now_index[now_page] = data[now_page].size()-1; }
			}
			if (Input::key.Numpad8.IsPush(連打st, 連打rp))
			{
				now_index[now_page]--;
				if (now_index[now_page] >= data[now_page].size()) { now_index[now_page] = 0; }
			}

			if (Input::key.Numpad4.IsPush(連打st, 連打rp))
			{
				now_page--;
				if ( now_page < 0) { now_page = UIPage::COUNT; }
			}
			if (Input::key.Numpad6.IsPush(連打st, 連打rp))
			{
				now_page++;
				if (now_page >= UIPage::COUNT) { now_page = 0; }
			}


			UILayout& it = data[now_page][now_index[now_page]];

			//通常カーソル操作で移動
			bool isShft = (Input::key.LShift.hold || Input::key.RShift.hold);
			bool isCtrl = (Input::key.RControl.hold || Input::key.LControl.hold);

			if (Input::key.Down.IsPush(連打st, 連打rp))
			{
				if (isShft)
				{
					it.h++;
				}
				else if (isCtrl)
				{
					it.並べy++;
				}
				else
				{
					it.y++;
				}
			}
			if (Input::key.Up.IsPush(連打st, 連打rp))
			{
				if (isShft)
				{
					it.h--;
					if (it.h < 0) { it.h = 0; }
				}
				else if (isCtrl)
				{
					it.並べy--;
				}
				else
				{
					it.y--;
				}
			}

			if (Input::key.Left.IsPush(連打st, 連打rp))
			{
				if (isShft)
				{
					it.w--;
					if (it.w < 0) { it.w = 0; }
				}
				else if (isCtrl)
				{
					it.並べx--;
				}
				else
				{
					it.x--;
				}
			}
			if (Input::key.Right.IsPush(連打st, 連打rp))
			{
				if (isShft)
				{
					it.w++;
				}
				else if (isCtrl)
				{
					it.並べx--;					
				}
				else
				{
					it.x++;
				}
			}

			//PageUP,PageDownで画像ID
			if (Input::key.PageUp.IsPush(連打st, 連打rp) == true)
			{
				it.画像ID++;
			}
			if (Input::key.PageDown.IsPush(連打st, 連打rp) == true)
			{
				it.画像ID--;
				if (it.画像ID < 0) { it.画像ID = 0; }
			}

			//ポーズキーで保存、読み込みは参照先が壊れるので未対応
			if (Input::key.Pause.on == true)
			{
				SaveData();
			}
		}
	};

}