//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	//基本的なUIオブジェクトのベースクラス
	class UIObject
	{
	private:
		virtual void Draw派生()
		{
			drawEvent();
		}

		virtual bool Check派生(double px, double py)
		{
			return false;
		}

	public:
		inline static UIHelp* now_help = nullptr;

		Layout* layout;
		UIObject* 親 = nullptr;
		UIHelp* help = nullptr;
		bool is表示 = true;
		bool is表示オンリー = false;
		bool isOver = false;
		int mousePos = 0;//0、マウス乗っていない：1、左側：2、右側

		int lineID = 0;

		bool isLeftDock = true;//X座標を左端から参照する

		std::function<void()> clickEvent = []() {};
		std::function<void()> drawEvent = []() {};
		std::function<void()> dropEvent = []() {};
		std::function<void()> overEvent = []() {};

		template<class T>
		void SetUI(T レイアウト, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}

		//レイアウト参照、省略表記用
		template<class T>
		Layout& LData(T レイアウト)
		{
			return Layout::Data(レイアウト);
		}


		Point GetPos()
		{
			return { GetX() , GetY() };
		}

		Point GetPos(Layout& レイアウト)
		{
			return { GetX() + レイアウト.x , GetY() + レイアウト.y };
		}

		Point GetCenterPos()
		{
			return { GetCenterX() , GetCenterY() };
		}

		Point GetCenterPos(Layout& レイアウト)
		{
			return { GetCenterX() + レイアウト.x , GetCenterY() + レイアウト.y };
		}

		int GetX()
		{
			if (isLeftDock)
			{
				if (lineID <= 0)
				{
					if (親 == nullptr)
					{
						return layout->x;
					}

					return 親->GetX() + layout->x;
				}

				if (親 == nullptr)
				{
					return layout->x + (lineID % layout->改行値) * layout->並べx;
				}

				return 親->GetX() + layout->x + (lineID % layout->改行値) * layout->並べx;
			}

			if (lineID <= 0)
			{
				if (親 == nullptr)
				{
					return Config::解像度W - (layout->x);
				}

				return Config::解像度W - (親->GetX() + layout->x);
			}

			if (親 == nullptr)
			{
				return Config::解像度W - (layout->x + (lineID % layout->改行値) * layout->並べx);
			}

			return Config::解像度W - (親->GetX() + layout->x + (lineID % layout->改行値) * layout->並べx);

		}

		Font* GetFont()
		{
			if (layout->フォントID < 0 || layout->フォントID > 2)
			{
				return MFont::F[2];
			}

			return MFont::F[layout->フォントID];
		}

		int GetY()
		{
			if (lineID <= 0)
			{
				if (親 == nullptr)
				{
					return layout->y;
				}
				return 親->GetY() + layout->y;
			}

			if (親 == nullptr)
			{
				return layout->y + (lineID / layout->改行値) * layout->並べy;
			}

			return 親->GetY() + layout->y + (lineID / layout->改行値) * layout->並べy;
		}

		int GetCenterX()
		{
			return GetX() + GetW() / 2;
		}

		int GetCenterY()
		{
			return GetY() + GetH() / 2;
		}

		int GetW()
		{
			return layout->w;
		}

		int GetH()
		{
			return layout->h;
		}

		void Draw()
		{
			Draw派生();

			//クリック判定のサイズを表示

			if (CV::isデバッグ)
			{
				if (Game::isデバッグ大きさ表示)
				{
					Drawing::Rect({ GetX(),GetY(),GetW(),GetH() }, Color::Red, false);
				}

				//選択直後のオブジェクトはマークを付ける
				if (layout->IsSelect() == true)
				{
					Drawing::Line({ GetCenterX() - 30,GetCenterY() }, { GetCenterX() + 30,GetCenterY() }, Color::Red, 3);
					Drawing::Line({ GetCenterX(),GetCenterY() + 30 }, { GetCenterX(),GetCenterY() - 30 }, Color::Red, 3);
				}
			}
		}

		void DrawUI(UIType UI枠種 , IDesign* UIデザイン = Design::No1 )
		{
			UIデザイン->Draw(UI枠種, GetX(), GetY(), GetW(), GetH());
		}

		void DrawInfo(int x , int y)
		{
			if (help != nullptr)
			{

			}
		}

		//クリック、ドロップ、マウスオーバー判定を処理 //クリック or ドロップでtrue
		bool CheckInput(double px, double py)
		{
			isOver = false;
			mousePos = 0;
			if ( is表示 == false || is表示オンリー == true ) { return false; }

			if (Check派生(px, py) == true)
			{
				return false;
			}

			int posX = GetX();
			int posY = GetY();

			Rect pt = { posX + px, posY + py , GetW() , GetH() };
			Point mp = Input::mouse.GetPoint();

			if ( mp.Hit(&pt))
			{
				isOver = true;
				mousePos = ( mp.x < pt.x + GetW() / 2) ? 1 : 2;//左右のどちら側をクリックしたか

				if (Input::mouse.Left.on == true)
				{
					Click();
					return true;
				}
				else if (Input::mouse.Left.off == true)
				{
					if (Drop() == true) { return true; };
				}

				//マウスオーバー中の物のヘルプ
				now_help = help;
				Over();
			}

			return false;
		}

		/*クリック操作*/
		virtual void Click()
		{
			clickEvent();		
		}

		/*ドロップ操作*/
		virtual bool Drop()
		{
			dropEvent();
			return true;
		}

		/*マウスオーバー時の処理*/
		virtual void Over()
		{
			overEvent();
		}
	};

}