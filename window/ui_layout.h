//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;



	//ページ毎のオブジェクトの列挙型、共通で使うパラメータ	


	class Layout
	{
	private:
		Color col;

		inline static int now_page = 0;//選択中のページ
		inline static int now_index[(int)UIPage::COUNT];//選択中のインデックス
		inline static std::string data_name[(int)UIPage::COUNT];//ページ名
		inline static std::vector<Layout> data[(int)UIPage::COUNT];//各アイテム
		inline static Layout* select_now;//現在選択中のアイテム
		inline static int select_time = 0;//直前に選択を変更してからのフレーム数
	public:

		//index.csv
		//各pageのファイル名と選択中のindexを保持する

		//****.csv
		//各pageのアイテムのデータ、名前、x,y,w,h,並べx,並べy,画像IDの順

		std::string 登録名 = "";
		int x = 0, y = 0;
		int w = 0, h = 0;
		int 並べx = 0, 並べy = 0;//並べないやつは自由に使える？
		int 改行値 = 1;//並べ時に何個で改行するか、たまにしか変更しないのでウォッチを使う

		int 画像ID = 0;
		int フォントID = 0;//0～2

		Layout()
		{}

		Layout(std::string 登録名):
			登録名(登録名)
		{}

		Layout( std::string 登録名 , int x, int y, int w, int h, int 並べx, int 並べy, int 改行値, int 画像ID , int フォントID):
			登録名(登録名),
			x(x),
			y(y),
			w(w),
			h(h),
			並べx(並べx),
			並べy(並べy),
			改行値(std::max(1,改行値)),
			画像ID(画像ID),
			フォントID(フォントID)
		{}

		//60フレーム以内に選択されているオブジェクトかどうか
		bool IsSelect()
		{
			return (this == select_now && select_time <= 60);
		}

		template< class TUIEnum>
		static Layout& Data( TUIEnum key )
		{
			int no = (int)key;

			//デバッグ時のみサイズ足りてなかったら拡大する
			if (data[(int)TUIEnum::PAGE].size() <= no)
			{
				data[(int)TUIEnum::PAGE].resize(no+1);
			}

			return data[(int)TUIEnum::PAGE][no];
		}

		static void LoadData()
		{
			//ページ名一覧とページ毎の選択中indexを読み込み
			File file("file/layout/index.csv",FileMode::Read,false);
			auto csv = file.GetCsvToString2();
			file.Close();

			now_page = std::stoi(csv[0][0]);

			//全てのページを読み込み
			for (int a = 0; a < (int)UIPage::COUNT; a++)
			{
				data_name[a] = csv[a+1][0];
				now_index[a] = std::stoi(csv[a+1][1]);

				std::string file_name = "file/layout/";
				file_name += data_name[a];
				file_name += ".csv";

				File page_file( file_name.c_str() ,FileMode::Read,false);
				auto csv2 = page_file.GetCsvToString2();
				page_file.Close();

				data[a].reserve(256);//最領域確保時参照が崩れるので多めに確保

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
						std::stoi(csv2[b][7]),
						std::stoi(csv2[b][8]),
						std::stoi(csv2[b][9])
					);
				}
			}
		}


		static void SaveData()
		{
			//ページ名と選択index
			File file("file/layout/index.csv", FileMode::Write, false);

			file.AddLine({ now_page , ",now_page" ,  });

			//各ページの情報
			for (int a = 0; a < (int)UIPage::COUNT; a++)
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
									it.改行値 , ",",
									it.画像ID , ",",
									it.フォントID
						});

				}
			}

		}

		//現在のページ、オブジェクト一覧、選択中のオブジェクトパラメータを表示
		static void Draw()
		{
			//入力中ラベル名
			std::string str = "ラベル：";
			MFont::MDot.DrawBold({ 10,5 }, Color::White, Color::Black, str + System::inputText + System::textComposition);

			//現在のページ番号と名前
			MFont::MDot.DrawBold({ 10,30 }, Color::White, Color::Black, { "現在ページ：" ,  now_page , ":" , data_name[now_page] , " : Index " , now_index[now_page] , "/" , data[now_page].size() -1 });
			
			//選択中のアイテムのパラメータ7種
			auto& it = data[now_page][now_index[now_page]];
			MFont::MDot.DrawBold({ 10,55 }, Color::White, Color::Black, { "座標(" , it.x , "," , it.y , "),大きさ(" , it.w , "," , it.h , "),整列(" , it.並べx , "," , it.並べy , "),ID(画像 " , it.画像ID , ",フォント " , it.フォントID , ") 改行値 = " , it.改行値 });

			int now_page_max = (int)data[now_page].size();
			int p_no = now_index[now_page]/30;


			//現在のページのアイテム
			for (int a = 0; a < std::min(30, now_page_max - p_no * 30); a++)
			{
				Color color = Color::White;

				if (now_index[now_page] == a + p_no * 30)
				{
					color = Color::Red;
				}
				MFont::MDot.DrawBold({ 10 , a * 21 + 85 }, color , Color::Black, { a + p_no * 30 , ":" });

				MFont::MDot.DrawBold({ 60 , a * 21 + 85 }, color , Color::Black, data[now_page][a + p_no * 30].登録名 );
			}


	
		}

		//入力を受け取って、ページ切り替え、選択状態ON/OFF、パラメータ調整処理を行う
		static void Input()
		{
			const int 連打st = 30;
			const int 連打rp = 5;
			select_time++;

			//Numpadで選択オブジェクト変更
			if (Input::key.Numpad8.IsPush(連打st,連打rp))
			{
				now_index[now_page]--;
				select_time = 0;
				if (now_index[now_page] < 0) { now_index[now_page] = (int)data[now_page].size()-1; }
			}
			if (Input::key.Numpad2.IsPush(連打st, 連打rp))
			{
				now_index[now_page]++;
				select_time = 0;
				if (now_index[now_page] >= data[now_page].size()) { now_index[now_page] = 0; }
			}

			if (Input::key.Numpad4.IsPush(連打st, 連打rp))
			{
				now_page--;
				select_time = 0;
				if ( now_page < 0) { now_page = (int)UIPage::COUNT-1; }
			}
			if (Input::key.Numpad6.IsPush(連打st, 連打rp))
			{
				now_page++;
				select_time = 0;
				if (now_page >= (int)UIPage::COUNT) { now_page = 0; }
			}


			Layout& it = data[now_page][now_index[now_page]];
			select_now = &it;

			//通常カーソル操作で移動
			bool isShft = (Input::key.LShift.hold || Input::key.RShift.hold);
			bool isCtrl = (Input::key.RControl.hold || Input::key.LControl.hold);

			if (Input::key.Down.IsPush(連打st, 連打rp))
			{
				int n = (Input::key.Down.holdCount < 120) ? 1 : 5;

				if (isShft)
				{
					it.h += n;
				}
				else if (isCtrl)
				{
					it.並べy += n;
				}
				else
				{
					it.y += n;
				}
				return;
			}
			if (Input::key.Up.IsPush(連打st, 連打rp))
			{
				int n = (Input::key.Up.holdCount < 120) ? 1 : 5;

				if (isShft)
				{
					it.h -= n;
					if (it.h < 0) { it.h = 0; }
				}
				else if (isCtrl)
				{
					it.並べy -= n;
				}
				else
				{
					it.y -= n;
				}
				return;
			}

			if (Input::key.Left.IsPush(連打st, 連打rp))
			{
				int n = (Input::key.Left.holdCount < 120) ? 1 : 5;

				if (isShft)
				{
					it.w -= n;
					if (it.w < 0) { it.w = 0; }
				}
				else if (isCtrl)
				{
					it.並べx -= n;
				}
				else
				{
					it.x -= n;
				}
				return;
			}
			if (Input::key.Right.IsPush(連打st, 連打rp))
			{
				int n = (Input::key.Right.holdCount < 120) ? 1 : 5;

				if (isShft)
				{
					it.w += n;
				}
				else if (isCtrl)
				{
					it.並べx += n;					
				}
				else
				{
					it.x += n;
				}
				return;
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

			//Enterでフォントサイズ
			if (Input::key.NUMPADEnter.IsPush(連打st, 連打rp) == true)
			{
				it.フォントID++;
				if (it.フォントID > 2) { it.フォントID = 0; }
			}

			//homeで改行値
			if (Input::key.Home.IsPush(連打st, 連打rp) == true)
			{
				it.改行値++;
				if (it.改行値 > 100) { it.改行値 = 100; }
			}
			if (Input::key.End.IsPush(連打st, 連打rp) == true)
			{
				it.改行値--;
				if (it.改行値 < 1) { it.改行値 = 1; }
			}

			//直接入力
			if (Input::key.Back.IsPush(連打st, 連打rp))
			{
				if (System::inputText.length() > 0)
				{
					System::inputText = "";
				}
			}

			//Enter長押しで代入
			if (Input::key.Return.holdCount == 15)
			{	
				it.登録名 = System::inputText;
				System::inputText = "";
			}

			//デバッグ時にブレークポイント挟んで選択中をウォッチ
			if (Input::key.F2.on == true)
			{
				select_now = select_now;
			}

			//ポーズキーで保存、読み込みは参照先が壊れるので未対応
			if (Input::key.Pause.on == true)
			{
				SaveData();
			}

			if (Input::key.Pause.holdCount > 60)
			{
				CV::isレイアウト = false;
			}
		}
	};

}