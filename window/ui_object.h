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
		UIObject(UILayout& layout):
			layout(layout)
		{}

		UILayout& layout;
		UIObject* 親 = nullptr;
		bool is表示;
		int lineID = 0;

		int GetX()
		{
			if (lineID <= 0)
			{
				if (親 == nullptr)
				{
					return layout.x;
				}

				return 親->GetX() + layout.x;
			}

			if (親 == nullptr)
			{
				return layout.x + ( lineID % layout.改行値) * layout.並べx ;
			}

			return 親->GetX() + layout.x + (lineID % layout.改行値) * layout.並べx;
		}
		int GetY()
		{
			if (lineID <= 0)
			{
				if (親 == nullptr)
				{
					return layout.y;
				}
				return 親->GetY() + layout.y;
			}

			if (親 == nullptr)
			{
				return layout.y + (lineID % layout.改行値) * layout.並べy;
			}

			return 親->GetY() + layout.y + (lineID % layout.改行値) * layout.並べy;
		}

		int GetW()
		{
			return layout.w;
		}

		int GetH()
		{
			return layout.h;
		}

		void Draw()
		{
			Draw派生();

			//クリック判定のサイズを表示
			Drawing::Rect({ GetX(),GetY(),GetW(),GetH() }, Color::Red, false);

			//選択直後のオブジェクトはマークを付ける
			if (layout.IsSelect() == true)
			{
				Drawing::Line({ GetX()-30,GetY() }, { GetX()+30,GetY() }, Color::Red, 3);
				Drawing::Line({ GetX(),GetY()-30 }, { GetX(),GetY()-30 }, Color::Red, 3);
			}
		}

		//クリック、ドロップ、マウスオーバー判定を処理 //クリック or ドロップでtrue
		bool 操作チェック(double px, double py)
		{
			if ( is表示 == false) { return false; }

			int posX = GetX();
			int posY = GetY();

			Rect pt = { posX + px, posY + py , GetW() , GetH() };

			if (Input::mouse.GetPoint().Hit(&pt))
			{
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

	

	//枠オブジェクト
	class UIFrame : UIObject
	{
	public:
	};

	//アイコンオブジェクト
	class UIImage : UIObject
	{
	public:
		Font& font;
		ImagePack& image;

	};

	//文字列オブジェクト
	class UIString : UIObject
	{
	public:
		std::string テキスト;


	};

	class UITab : UIObject
	{
	//タブ1枚に付き、1オブジェクト
	public:
		int tabID;
		int& tabSelect参照;
		Image* アイコン;
		std::string テキスト;
	};
}