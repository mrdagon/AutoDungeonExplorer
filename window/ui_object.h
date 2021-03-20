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

		}

	public:
		inline static UIHelp* now_help = nullptr;

		UILayout* layout;
		UIObject* 親 = nullptr;
		UIHelp* help = nullptr;
		bool is表示 = true;
		bool is表示オンリー = false;
		bool isOver = false;
		int lineID = 0;

		void SetUI(UILayout& レイアウト, int 整列ID, UIObject* 親object = nullptr)
		{
			layout = &レイアウト;
			lineID = 整列ID;
			親 = 親object;
		}

		template<class T>
		void SetLayout(T key)
		{
			layout = &UILayout::Data(key);
		}

		int GetX()
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
				return layout->x + ( lineID % layout->改行値) * layout->並べx ;
			}

			return 親->GetX() + layout->x + (lineID % layout->改行値) * layout->並べx;
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

		void DrawUI(UIType UI枠種 , IUIDesign* UIデザイン)
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
		bool 操作チェック(double px, double py)
		{
			isOver = false;

			if ( is表示 == false || is表示オンリー == true ) { return false; }

			int posX = GetX();
			int posY = GetY();

			Rect pt = { posX + px, posY + py , GetW() , GetH() };

			if (Input::mouse.GetPoint().Hit(&pt))
			{
				isOver = true;

				if (Input::mouse.Left.on == true)
				{
					Click(Input::mouse.x - posX - px, Input::mouse.y - posY - py);
					return true;
				}
				else if (Input::mouse.Left.off == true)
				{
					Drop(Input::mouse.x - posX - px, Input::mouse.y - posY - py);
					return true;
				}

				//マウスオーバー中の物のヘルプ
				now_help = help;
				Over(Input::mouse.x - posX - px, Input::mouse.y - posY - py);
			}

			return false;
		}

		/*クリック操作*/
		virtual void Click(double px, double py){}

		/*ドロップ操作*/
		virtual void Drop(double px, double py){}

		/*マウスオーバー時の処理*/
		virtual void Over(double px, double py){}


	};

	//よく使うUIObjectの基本形
	

	//文字付きボタンオブジェクト
	class UIButton : public UIObject
	{
	public:
		std::string テキスト;
		IUIDesign* UIデザイン;
		bool is押下 = false;//押し下げ状態フラグ

		//クリック時の処理はオーバーライド
		//ラムダ式でも良さそう

		void Draw派生()
		{
			//凸ボタン、マウスオーバー時は平
			if (is押下 == true)
			{
				DrawUI(UIType::凹ボタン, UIデザイン);
				MFont::M->DrawRotate({ GetCenterX() , GetCenterY()+2 }, 1, 0, UIDesign::Brown.暗字, テキスト, false);
			}
			else if (isOver)
			{
				DrawUI( UIType::平ボタン, UIデザイン);
				MFont::M->DrawRotate({ GetCenterX() , GetCenterY() }, 1, 0, UIDesign::Brown.暗字, テキスト, false);
			}
			else
			{
				DrawUI( UIType::凸ボタン, UIデザイン);
				MFont::M->DrawRotate({ GetCenterX() , GetCenterY()-2 }, 1, 0, UIDesign::Brown.暗字, テキスト, false);
			}

		}
	};

	//テキスト表示枠 ＋　テキスト
	class UITextFrame : public UIObject
	{
	public:
		std::string テキスト;
		IUIDesign* UIデザイン;

		void Draw派生()
		{
			DrawUI( UIType::背景, UIデザイン);
			MFont::M->Draw({ GetX() + 4 , GetY() + 4 },UIDesign::Brown.暗字, テキスト );
		}
	};

	class UITab : public UIObject
	{
	//タブ1枚に付き、1オブジェクト
	public:
		int tabID;
		int& tabSelect参照;
		Image* アイコン;
		std::string テキスト;
	};
}