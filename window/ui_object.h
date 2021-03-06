﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;
	class I_UIObject
	{
	public:
		I_UIObject(UILayout& layout):
			layout(layout)
		{}

		UILayout& layout;
		UILayout* 親 = nullptr;
		bool is表示;

		void GetX();
		void GetY();

		void GetW();

		void GetH();


		virtual void Draw();

		//クリック、ドロップ、マウスオーバー判定を処理
		//クリック or ドロップでtrue
		bool 操作チェック(double px, double py)
		{
			return false;
		}

		/*クリック操作*/
		virtual void Click(double px, double py){}

		/*ドロップ操作*/
		virtual void Drop(double px, double py){}

		/*マウスオーバー時の処理*/
		virtual void Over(double px, double py){}
	};

	
	//基本的なUIオブジェクトのベースクラス
	class UIObject : I_UIObject
	{
	public:

	};

	//枠オブジェクト
	class UIFrame : I_UIObject
	{
	public:
		int 枠ID;
	};

	//アイコンオブジェクト
	class UIImage : I_UIObject
	{
	public:
		Image* image;

	};

	//文字列オブジェクト
	class UIString : I_UIObject
	{
	public:
		std::string テキスト;


	};

	//一定間隔で並べられるオブジェクト
	class UIListObject : I_UIObject
	{
	public:
		int lineID = 0;

	};

	//枠オブジェクト
	class UIListFrame : I_UIObject
	{
	public:
		int lineID = 0;
		int 枠ID = 0;

	};

	//画像オブジェクト
	class UIListImage : I_UIObject
	{
	public:
		int lineID = 0;
		Image* image;

	};

	//文字列オブジェクト
	class UIListString : I_UIObject
	{
	public:
		int lineID = 0;
		std::string テキスト;

	};

	class UITab : I_UIObject
	{
	//タブ1枚に付き、1オブジェクト
	public:
		int tabID;
		int& tabSelect参照;
		Image* アイコン;
		std::string テキスト;
	};
}