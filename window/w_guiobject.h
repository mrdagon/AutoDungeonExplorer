//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ウィンドウベースクラス*/
	//削除予定
	class GUI_Object : public GUI_Help
	{
	public:

		Rect 位置;
		bool is固定 = false;//スクロールしない
		bool is表示 = true;

		/*描画内容*/
		virtual void Draw()
		{
			Draw派生(位置.x, 位置.y);
			//デバッグ用に位置を表示
			if (Game::isデバッグ大きさ表示) { Drawing::Rect({ 位置.x, 位置.y ,位置.GetW() , 位置.GetH() }, Color::Red, false); }
		}

		virtual void Draw派生(double px,double py)
		{

		}

		/*クリックチェック*/
		bool 操作チェック(double px, double py)
		{
			if (is表示 == false) { return false; }

			Rect pt = { 位置.x + px, 位置.y +py , 位置.GetW() , 位置.GetH()};

			if (Input::mouse.GetPoint().Hit(&pt))
			{
				if (Input::mouse.Left.on == true)
				{
					Click(Input::mouse.x-位置.x-px,Input::mouse.y-位置.y-py);
					return true;
				}
				else if (Input::mouse.Left.off == true)
				{
					Drop(Input::mouse.x - 位置.x-px, Input::mouse.y - 位置.y-py);
					return true;
				}
				
				Over(Input::mouse.x - 位置.x - px, Input::mouse.y - 位置.y - py);
			}

			return false;
		}

		/*クリック操作*/
		virtual void Click(double px,double py)
		{

		}

		/*ドロップ操作*/
		virtual void Drop(double px, double py)
		{

		}

		/*マウスオーバー時の処理*/
		virtual void Over(double px, double py)
		{

		}

		int csv_page = 0;

		inline int Lp(int no)
		{
			return CSV::I[csv_page][no];
		}
	};

	class GUI_Tab : public GUI_Object
	{
	public:
		int 番号;
		int 文字オフセット = 0;
		int& タブ操作;
		IconType アイコン;
		SkillType スキルアイコン = SkillType::COUNT;
		int アイコンオフセット = 0;
		std::string 文字;
		//NEW表示

		GUI_Tab( int& タブ操作,int 番号, IconType アイコン ,std::string 文字) : 
			番号(番号),タブ操作(タブ操作),アイコン(アイコン),文字(文字)
		{
			is固定 = true;
		}

		void Draw派生(double px, double py)
		{
			int no = 14;
			if (タブ操作 == 番号) { no = 12; }

			MSystem::DrawWindow({ px,py }, 位置.GetW(), 位置.GetH()+10 , no);

			if (スキルアイコン != SkillType::COUNT)
			{
				//MIcon::スキル[スキルアイコン].DrawRotate({ px + 位置.GetW() / 2 , py + (位置.GetH() - 10) / 2 + アイコンオフセット }, 1, 0);
			} else {
				MIcon::UI[アイコン].DrawRotate({ px + 位置.GetW() / 2 , py + (位置.GetH() - 10) / 2 + アイコンオフセット }, 2, 0);
			}

			px -= MFont::MDot.GetDrawStringWidth(文字)/2;
			MFont::MAlias.DrawBold({ px + 位置.GetW() / 2 ,py + (位置.GetH()-10) / 2 + 文字オフセット}, Color::White, Color::Black, 文字);
		}

		void Click(double px, double py)
		{
			タブ操作 = 番号;

			MSound::効果音[SE::タブ切り替え].Play();
		}
	};

	//単純な枠
	class GUI_Frame : public GUI_Object
	{
	public:
		int 枠No = 12;
		std::string text = "";

		void Draw派生(double px, double py)
		{
			MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 枠No);
			if (text != "")
			{
				MFont::SAlias.DrawBold({ px + 6 ,py + 0}, Color::White, Color::Black, text , false);
			}
		}
	};
}