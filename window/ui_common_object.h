//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;


	//よく使うUIObjectの基本形
	//文字付きボタンオブジェクト
	class UIButton : public UIObject
	{
	public:
		std::string テキスト = "";
		Image* 画像 = nullptr;

		DesignType UIデザイン = DesignType::セット1;
		bool is押下 = false;//押し下げ状態フラグ
		int 押下状態 = 0;//押下 = true時にどう表示するか

		int テキスト位置 = 5;//1~9、テンキーの位置関係と対応
		int 画像位置 = 5;//1~9、テンキーの位置関係と対応

		//クリック時の処理はオーバーライド
		//ラムダ式でも良さそう

		template<class T>
		void SetUI( T レイアウト, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}

		template<class T>
		void SetUI( std::string 初期テキスト  , T レイアウト, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			テキスト = 初期テキスト;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}
		
		template<class T>
		void SetUI(Image* 画像, T レイアウト, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			this->画像 = 画像;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}

		template<class T>
		void SetUI(Image* 画像, std::string テキスト, T レイアウト, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			this->画像 = 画像;
			this->テキスト = テキスト;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
			画像位置 = 8;
			テキスト位置 = 2;
		}

		void Draw派生()
		{
			//凸ボタン、マウスオーバー時は平
			int yd = 0;

			if (is押下 == true && 押下状態 == 0)
			{
				DrawUI(UIType::凹ボタン, Design::data[UIデザイン]);
				yd = 2;
			}
			else if ((is押下 == true && 押下状態 == 1))
			{
				DrawUI(UIType::平ボタン, Design::data[UIデザイン]);
			}
			else if ((is押下 == true && 押下状態 == 2))
			{
				DrawUI(UIType::凸ボタン, Design::data[UIデザイン]);
				yd = -2;
			}
			else if ( isOver )
			{
				DrawUI( UIType::平ボタン, Design::data[UIデザイン]);
			}
			else
			{
				DrawUI( UIType::凸ボタン, Design::data[UIデザイン]);
				yd = -2;
			}

			if (画像 != nullptr)
			{

				int xd = 0;
				int ydd = yd;

				if (画像位置 == 1 || 画像位置 == 4 || 画像位置 == 7)
				{
					//←
					xd -= layout->w * 2 / 5 - 画像->GetWidth() / 2;

				}
				else if(画像位置 == 3 || 画像位置 == 6 || 画像位置 == 9)
				{
					//→
					xd += layout->w * 2 / 5 - 画像->GetWidth() / 2;
				}

				if (画像位置 == 7 || 画像位置 == 8 || 画像位置 == 9)
				{
					//↑
					ydd -= layout->h * 2 / 5 - 画像->GetHeight() / 2;

				}
				else if(画像位置 == 1 || 画像位置 == 2 || 画像位置 == 3)
				{
					//↓
					ydd -= layout->h * 2 / 5 - 画像->GetHeight() / 2;
				}
				画像->DrawRotate({ GetCenterX() + xd ,GetCenterY() + ydd }, 1, 0);
			}

			if (テキスト.length() > 0)
			{
				int xd = 0;
				int ydd = yd;

				if (テキスト位置 == 1 || テキスト位置 == 4 || テキスト位置 == 7)
				{
					//←
					xd -= MFont::F[layout->フォントID]->GetDrawStringWidth(テキスト)/2;
				}
				else if (テキスト位置 == 3 || テキスト位置 == 6 || テキスト位置 == 9)
				{
					//→
					xd += MFont::F[layout->フォントID]->GetDrawStringWidth(テキスト) / 2;
				}

				if (テキスト位置 == 7 || テキスト位置 == 8 || テキスト位置 == 9)
				{
					//↑
					ydd -= MFont::F[layout->フォントID]->GetSize() + 4;
				}
				else if (テキスト位置 == 1 || テキスト位置 == 2 || テキスト位置 == 3)
				{
					//↓
					ydd += MFont::F[layout->フォントID]->GetSize() - 4;
				}

				MFont::F[layout->フォントID]->DrawRotate({ GetCenterX() + xd, GetCenterY() + ydd }, 1, 0, Design::data[UIデザイン]->暗字, テキスト, false);

			}
		}
	};

	//テキスト表示枠 ＋　テキスト
	class UITextFrame : public UIObject
	{
	public:
		std::string テキスト;
		DesignType UIデザイン;

		template<class T>
		void SetUI(std::string 初期テキスト, T レイアウト, DesignType デザイン = DesignType::セット1, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			テキスト = 初期テキスト;
			UIデザイン = デザイン;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}


		void Draw派生()
		{
			switch (layout->画像ID)
			{
			case 0:
				DrawUI(UIType::背景, Design::data[UIデザイン]);
				break;
				break;
			case 1:
				DrawUI(UIType::グループ明, Design::data[UIデザイン]);
				break;
				break;
			default:
				DrawUI(UIType::グループ暗, Design::data[UIデザイン]);
				break;
			}


			switch (layout->フォントID)
			{
			case 0:
				MFont::S->Draw({ GetX() + 4 , GetY() + 4 }, Design::data[UIデザイン]->暗字, テキスト);
				break;
			case 1:
				MFont::M->Draw({ GetX() + 4 , GetY() + 4 }, Design::data[UIデザイン]->暗字, テキスト);
				break;
			default:
				MFont::L->Draw({ GetX() + 4 , GetY() + 4 }, Design::data[UIデザイン]->暗字, テキスト);
				break;
			}
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