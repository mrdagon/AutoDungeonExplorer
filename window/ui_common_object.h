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

		Design** UIデザイン = &Design::No1;
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
		void SetUI(T レイアウト, std::string 初期テキスト  ,  int 整列ID = 0, UIObject* 親object = nullptr)
		{
			テキスト = 初期テキスト;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}
		
		template<class T>
		void SetUI(T レイアウト, Image* 画像,  int 整列ID = 0, UIObject* 親object = nullptr)
		{
			this->画像 = 画像;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}

		template<class T>
		void SetUI(T レイアウト, Image* 画像, std::string テキスト,  int 整列ID = 0, UIObject* 親object = nullptr)
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
			bool push = false;

			if (is押下 == true && 押下状態 == 0)
			{
				DrawUI(UIType::凹ボタン, *UIデザイン);
				yd = 2;
				push = true;
			}
			else if ((is押下 == true && 押下状態 == 1))
			{
				DrawUI(UIType::平ボタン, *UIデザイン);
			}
			else if ((is押下 == true && 押下状態 == 2))
			{
				DrawUI(UIType::凸ボタン, *UIデザイン);
				yd = -2;
			}
			else if ( isOver )
			{
				DrawUI( UIType::平ボタン, *UIデザイン);
			}
			else
			{
				DrawUI( UIType::凸ボタン, *UIデザイン);
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

				GetFont()->DrawRotate({ GetCenterX() + xd, GetCenterY() + ydd }, 1, 0, push ? Design::明字 : Design::暗字, テキスト, false);
			}
		}
	};

	//テキスト表示枠 ＋　テキスト
	class UITextFrame : public UIObject
	{
	public:
		std::string テキスト;
		Design** UIデザイン = &Design::No1;

		template<class T>
		void SetUI( T レイアウト,std::string 初期テキスト, Design** デザイン = &Design::No1, int 整列ID = 0, UIObject* 親object = nullptr)
		{
			テキスト = 初期テキスト;
			UIデザイン = デザイン;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			親 = 親object;
		}

		void Draw派生() override
		{
			switch (layout->画像ID)
			{
			case 0:
				DrawUI(UIType::グループ明, *UIデザイン);
				break;
			case 1:
				DrawUI(UIType::グループ中, *UIデザイン);
				break;
			default:
				DrawUI(UIType::グループ暗, *UIデザイン);
				break;
			}

			GetFont()->Draw({ GetX() + 4 , GetY() + 4 }, Design::暗字, テキスト);
		}
	};

	class UITab : public UIObject
	{
	//タブ1枚に付き、1オブジェクト
	public:
		int* tabNo参照;

		int tabID;
		Image* 画像;
		std::string テキスト;
		Design** UIデザイン = &Design::No1;

		int テキスト位置 = 5;//1~9、テンキーの位置関係と対応
		int 画像位置 = 5;//1~9、テンキーの位置関係と対応

		template<class T>
		void SetUI(T レイアウト, int* tabNo , Image* 画像, std::string テキスト, int 整列ID , UIObject* 親object = nullptr)
		{
			tabNo参照 = tabNo;

			this->画像 = 画像;
			this->テキスト = テキスト;
			layout = &Layout::Data(レイアウト);
			lineID = 整列ID;
			tabID = 整列ID;

			親 = 親object;
			if (テキスト == "" || 画像 == nullptr)
			{
				画像位置 = 5;
				テキスト位置 = 5;
			} else {
				画像位置 = 8;
				テキスト位置 = 2;
			}
		}

		void Draw派生() override
		{
			bool push = false;

			if (tabID == *tabNo参照)
			{
				DrawUI(UIType::グループ明 , *UIデザイン );
			}
			else
			{
				push = true;
				DrawUI(UIType::グループ暗 , *UIデザイン );
			}

			if (画像 != nullptr)
			{
				int xd = 0;
				int yd = 0;

				if (画像位置 == 1 || 画像位置 == 4 || 画像位置 == 7)
				{
					//←
					xd -= layout->w * 2 / 5 - 画像->GetWidth() / 2;

				}
				else if (画像位置 == 3 || 画像位置 == 6 || 画像位置 == 9)
				{
					//→
					xd += layout->w * 2 / 5 - 画像->GetWidth() / 2;
				}

				if (画像位置 == 7 || 画像位置 == 8 || 画像位置 == 9)
				{
					//↑
					yd -= layout->h * 2 / 5 - 画像->GetHeight() / 2;

				}
				else if (画像位置 == 1 || 画像位置 == 2 || 画像位置 == 3)
				{
					//↓
					yd -= layout->h * 2 / 5 - 画像->GetHeight() / 2;
				}
				画像->DrawRotate({ GetCenterX() + xd ,GetCenterY() + yd }, 1, 0);
			}

			if (テキスト.length() > 0)
			{
				int xd = 0;
				int yd = 0;

				if (テキスト位置 == 1 || テキスト位置 == 4 || テキスト位置 == 7)
				{
					//←
					xd -= MFont::F[layout->フォントID]->GetDrawStringWidth(テキスト) / 2;
				}
				else if (テキスト位置 == 3 || テキスト位置 == 6 || テキスト位置 == 9)
				{
					//→
					xd += MFont::F[layout->フォントID]->GetDrawStringWidth(テキスト) / 2;
				}

				if (テキスト位置 == 7 || テキスト位置 == 8 || テキスト位置 == 9)
				{
					//↑
					yd -= MFont::F[layout->フォントID]->GetSize() + 4;
				}
				else if (テキスト位置 == 1 || テキスト位置 == 2 || テキスト位置 == 3)
				{
					//↓
					yd += MFont::F[layout->フォントID]->GetSize() - 4;
				}

				GetFont()->DrawRotate({ GetCenterX() + xd, GetCenterY() + yd },1,0, push ? Design::明字 : Design::暗字 , テキスト, false);
			}

		}

		void Click() override
		{
			if ( *tabNo参照 != tabID )
			{
				*tabNo参照 = tabID;
				clickEvent();
			}
		}

	};
}