//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#pragma once
namespace SDX_ADE
{
	//シナリオの仕様変更で廃止予定

	using namespace SDX;
	//テキストウィンドウ１つと、顔と感情吹き出しで会話シーン作る
	//Windowクラスは継承しない
	class W_Scenario
	{
	private:
		class Actor
		{
		public:
			static Rect 名前枠;
			int id;
			std::string 名前 = "???";
			Point 座標;
			double ジャンプH = 0;
			double ジャンプ速度 = 10000;
			int 向き = 1;
			ImagePack* 画像 = nullptr;

			bool isトーク中 = false;;

			void Draw()
			{
				int x = int(座標.x);
				int y = int(座標.y + ジャンプH);

				if (ジャンプ速度 < -CSV::I[25][20])
				{
					ジャンプH += ジャンプ速度;
					ジャンプ速度 += CSV::I[25][21] / 10.0;
				} else {
					ジャンプH = 0;
				}

				画像[0][向き]->DrawRotate({ x,y }, 4, 0);

				if (isトーク中 == false) { return; }
				//感情吹き出し表示

				MSystem::吹き出し.DrawRotate({ 座標.x,座標.y - CSV::I[25][22] }, 2, 0);

				//名前
				MSystem::DrawWindow({ 名前枠.x,名前枠.y }, (int)名前枠.GetW(), (int)名前枠.GetH(), 0, 1);
				MFont::SAlias.DrawBoldRotate({ 名前枠.x + 名前枠.GetW() / 2,名前枠.y + 名前枠.GetH() / 2 }, 1, 0, Color::White, Color::Black, { 名前 }, true);

			}
		};

		class Page
		{
		public:
			static Rect 座標;
			int アクターID;
			int 向き;
			std::string テキスト;

			//このページに進めた時の処理
			void In(std::vector<Actor> &アクター)
			{
				for (auto& it : アクター)
				{
					it.isトーク中 = false;
				}

				アクター[アクターID].ジャンプH = 0;
				アクター[アクターID].ジャンプ速度 = CSV::I[25][20];
				アクター[アクターID].isトーク中 = true;
			}

			//戻した時の処理
			void Back(std::vector<Actor>& アクター)
			{
				//全員の感情をリセット
				for (auto& it : アクター)
				{
					it.isトーク中 = false;
				}

				アクター[アクターID].isトーク中 = true;
			}

			void Draw()
			{
				//枠と文章
				MSystem::DrawWindow({ 座標.x,座標.y }, (int)座標.GetW(), (int)座標.GetH(), 1, 1);
				MFont::LAlias.DrawBoldRotate({ 座標.x + CSV::I[25][23],座標.y + CSV::I[25][24] }, 1, 0, Color::White, Color::Black, { テキスト }, true);
			}

		};


		class ボタン
		{
		public:
			std::string テキスト;
			Rect 座標;

			void Draw()
			{
				MSystem::DrawWindow({ 座標.x,座標.y }, (int)座標.GetW(), (int)座標.GetH(), 0 , 1);
				MFont::LAlias.DrawBoldRotate({ 座標.x + 座標.GetW() / 2,座標.y + 座標.GetH() /2 },1,0, Color::White, Color::Black, { テキスト }, true);
			}
		};


	public:	
		const int csv_page = 25;
		int now_page = 0;
		int top_page = 0;
		std::vector<Page> ページ;
		std::vector<Actor> アクター;

		ボタン スキップボタン;
		ボタン バックボタン;

		void Init(int シナリオID)
		{
			now_page = 0;
			top_page = 0;

			ページ.clear();
			アクター.clear();
			//とりあえず仮
			for (int a = 0; a < 10; a++)
			{
				ページ.emplace_back();
				ページ[a].アクターID = a % 3;
				ページ[a].向き = a;
				ページ[a].テキスト = "ページ";
				ページ[a].テキスト += std::to_string(a);
				ページ[a].テキスト += "\nサンプル\nサンプル～\nサンプル～";
			}

			for (int a = 0; a < 3; a++)
			{
				アクター.emplace_back();
				アクター[a].id = a;
				アクター[a].画像 = &MUnit::ユニット[UnitImageType(a)];
				アクター[a].名前 = "アクター";
				アクター[a].名前 += std::to_string(a);
			}

			スキップボタン.テキスト = "Skip";
			バックボタン.テキスト = "Back";

			ページ[0].In(アクター);
		}

		void Load(int id)
		{

		}

		void GUI_Init()
		{
			int w = Window::GetWidth();
			int h = Window::GetHeight();

			Page::座標 = { (w - Lp(0)) / 2 , h/2 + Lp(2) ,Lp(0),Lp(1) };

			int a = 0;
			for (auto& it : アクター)
			{
				it.座標 = { (w / 2 ) + Lp(3) + Lp(4) * a , h/2 + Lp(5) };
				a++;
			}

			スキップボタン.座標 = { (w / 2) + Lp(6),h / 2 + Lp(7),Lp(9),Lp(10) };
			バックボタン.座標 = { (w / 2) + Lp(6),h / 2 + Lp(8),Lp(9),Lp(10) };

			Actor::名前枠 = { (w - Lp(13)) / 2 + Lp(11) , h / 2 + Lp(12) ,Lp(13),Lp(14) };
		}

		void Draw()
		{
			GUI_Init();

			//テキストと枠と名前
			ページ[now_page].Draw();

			//キャラドットと感情と吹き出し、喋ってるキャラを大きくする
			for (auto& it : アクター)
			{
				it.Draw();
				if (it.id == ページ[now_page].アクターID){ it.Draw(); }
			}

			//スキップボタン
			スキップボタン.Draw();
			バックボタン.Draw();
		}

		//終了時 true
		bool 操作()
		{
			const Point& pt = Input::mouse.GetPoint();

			if (Input::mouse.Left.on == false) { return false; }


			//戻るでバックログ
			if (pt.Hit(&バックボタン.座標) )
			{
				if (now_page > 0)
				{
					now_page--;
					ページ[now_page].Back(アクター);
				}
				return false;
			}

			//スキップボタンクリックで終了
			if (pt.Hit(&スキップボタン.座標))
			{
				return true;
			}

			//クリックで進む or 先頭へ
			now_page++;
			if (now_page < ページ.size())
			{
				ページ[now_page].In(アクター);
				return false;
			}

			//最後のページクリックで終了
			return true;
		}

		void ポップアップ呼び出し()
		{
			//裏をやや暗くする
			Drawing::Rect({ 0,0,Window::GetWidth(),Window::GetHeight() }, Color(0, 0, 0, 128));

			//現在の画面を記憶
			Image img(Renderer::mainRenderer.GetTexture(), Window::GetWidth(), Window::GetHeight());

			while (System::Update(true, false))
			{
				//img.DrawExtend({ 0,0 , Window::GetWidth() / full_rate, Window::GetHeight() / full_rate });
				img.DrawPartExtend({ 0,0 , Window::GetWidth() , Window::GetHeight()  } , { 0,0 , Window::GetWidth() * Config::解像度X倍 , Window::GetHeight() * Config::解像度X倍 });

				Draw();
				if (操作() == true) { break; }

				if (CV::isデバッグ)
				{
					CSVDraw();
					CSVCheckInput();
				}
			}

			img.Release();

			return ;
		}


		inline int Lp(int no)
		{
			return CSV::I[csv_page][no];
		}
	};

	Rect W_Scenario::Actor::名前枠;
	Rect W_Scenario::Page::座標;
}