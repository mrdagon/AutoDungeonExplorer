﻿//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once


namespace SDX_BSC
{
	using namespace SDX;

	/*ウィンドウベースクラス*/
	class WindowBox : public GUI_Help
	{
	private:
		bool is最小縮小;
	public:
		WindowType 種類;

		std::vector <GUI_Object*> gui_objects;

		//定数
		static const int ツールバー高さ = 100;
		static const int タイトル枠高さ = 30;
		static const int 枠No = 6;
		static const int タイトル枠No = 8;
		//状態
		bool is表示 = true;//
		std::string 名前 = "未設定";
		std::string 略記 = "????";
		IconType アイコン = IconType::閉じる;

		//座標
		Point 座標;
		Point 相対座標;//タイトル部分を除外してスクロール位置計算後の左上座標
		int 横幅;
		int 縦幅;//タイトル部分は含まない
		int 最大縦, 最小縦;
		int 固定縦 = 0;//スクロールせずに固定な部分
		//内部
		double 縦内部幅;
		double スクロール位置;//最小0、最大立幅内部 - 立幅

		//つかみ処理用
		Point 掴み座標;
		bool is移動中;
		bool is上拡縮中;
		bool is下拡縮中;
		bool isスクロール中;

		//最前面移動用
		bool is最前面 = false;

		/*各種初期化*/
		virtual void init()
		{
			return;
		}

		/*GUI初期化*/
		virtual void GUI_Init()
		{

		}

		/*描画処理と操作処理*/
		void Draw()
		{
			if (is表示 == false) { return; };

			相対座標.x = 座標.x;
			相対座標.y = 座標.y - スクロール位置 + タイトル枠高さ + 固定縦;

			共通Draw();
			//描画領域計算
			//固定部分なしなら全体
			描画範囲(固定縦 == 0);
			派生Draw();
			Screen::GetRenderer()->SetClip();
			SDX::Camera::Get()->position = { 0,0 };
			return;
		}

		/*なんらかの操作をしたorウィンドウ上にあった場合 trueを返す*/
		bool 操作()
		{
			if (is表示 == false) { return false; };

			bool is操作 = 共通操作();
			相対座標.x = 座標.x;
			相対座標.y = 座標.y - スクロール位置 + タイトル枠高さ + 固定縦;

			is操作 = is操作 || 派生操作();

			return is最前面 || is操作 || Rect(座標.x,座標.y, 横幅 , タイトル枠高さ + 縦幅).Hit(&Input::mouse.GetPoint());		
		}

		/*ヘルプ表示 or 枠内ならtrueを返す*/
		bool CheckInfo()
		{
			Point マウス座標 = Input::mouse.GetPoint();

			//タイトル部分をチェック
			if( Rect(座標.x, 座標.y, 横幅, タイトル枠高さ).Hit(&マウス座標) )
			{
				this->Info();
				return true;
			}

			//ウィンドウ枠外なら終了
			if ( !Rect(座標.x, 座標.y + タイトル枠高さ, 横幅, 縦幅).Hit(&Input::mouse.GetPoint()))
			{
				return false;
			}

			マウス座標.x = Input::mouse.x - 相対座標.x;
			
			for (auto& it : gui_objects)
			{
				if (it->is固定)
				{
					マウス座標.y = Input::mouse.y - 座標.y - タイトル枠高さ;// +スクロール位置;
				} else {
					マウス座標.y = Input::mouse.y - 相対座標.y;

					if (Input::mouse.y - 座標.y - タイトル枠高さ < 固定縦)
					{
						return true;
					}
				}

				if (it->位置.Hit(&マウス座標) && it->isヘルプ表示)
				{
					it->Info();
					return true;
				}
			}
			return true;

		}

		virtual void 派生Draw() { return; };
		virtual bool 派生操作() { return false; };

		void 共通Draw()
		{
			//タイトル部分
			MSystem::DrawWindow(座標, 横幅, タイトル枠高さ, タイトル枠No);
			MSystem::DrawWindow({ 座標.x + 6,座標.y + 6 }, タイトル枠高さ - 12, タイトル枠高さ - 12, 11);
			MFont::Bメイリオ中.DrawBold({ 座標.x + 34,座標.y + 3 }, Color::White,Color::Black,{ 名前 });
			MIcon::アイコン[アイコン].DrawRotate({ 座標.x + 15,座標.y + 15 }, 1, 0);

			//閉じるボタン
			MSystem::DrawWindow({ 座標.x + 横幅 - 25,座標.y + 6 }, タイトル枠高さ - 12 , タイトル枠高さ - 12, 11);
			MIcon::アイコン[IconType::閉じる].DrawRotate({ 座標.x + 横幅 -16 ,座標.y + 15 },1,0);

			//メイン部分描画
			MSystem::DrawWindow({ 座標.x,座標.y+ タイトル枠高さ }, 横幅, 縦幅, 枠No);

			//ウィンドウスクロール用
			//スクロール最大高さ = 縦幅-8-8
			if (縦幅 < 縦内部幅)
			{
				MSystem::DrawWindow({ 座標.x + 横幅 - 26 , 座標.y + タイトル枠高さ + 4 }, 20, 縦幅 - 8, 2 , -1);

				int scrH = int((縦幅-16) * 縦幅 / 縦内部幅);
				int scrY = int(座標.y + タイトル枠高さ + 8 + (縦幅 - 16) * スクロール位置 / 縦内部幅);
				MSystem::DrawWindow({ 座標.x + 横幅 - 23 , scrY }, 14, scrH, 14);
			}

			return;
		}
		bool 共通操作()
		{
			Point マウス座標 = Input::mouse.GetPoint();

			//ホイール操作
			if (Rect(座標.x, 座標.y + タイトル枠高さ, 横幅, 縦幅).Hit(&Input::mouse.GetPoint()) && Input::mouse.Whell != 0 && !is下拡縮中 && !is上拡縮中 && !isスクロール中)
			{
				スクロール位置 -= Input::mouse.Whell * 20;

				if (スクロール位置 > 縦内部幅 - 縦幅) { スクロール位置 = 縦内部幅 - 縦幅; }
				if (スクロール位置 < 0) { スクロール位置 = 0; }
			}

			//左クリックしていない場合共通操作なし
			if (Input::mouse.Left.hold == false)
			{
				is移動中 = false;
				is上拡縮中 = false;
				is下拡縮中 = false;
				isスクロール中 = false;
				return false;
			}

			//タイトル掴んで移動中
			if (is移動中)
			{
				//座標.x += Input::mouse.moveX;
				//座標.y += Input::mouse.moveY;

				座標.x = マウス座標.x + 掴み座標.x;
				座標.y = マウス座標.y + 掴み座標.y;
				座標.x = std::max(0.0, 座標.x);
				座標.x = std::min(double(Window::GetWidth() - 横幅), 座標.x);

				座標.y = std::max(double(ツールバー高さ), 座標.y);
				座標.y = std::min(double(Window::GetHeight() - 縦幅 - タイトル枠高さ), 座標.y);

				return true;
			}

			//上側掴んで拡大縮小中
			if (is上拡縮中)
			{
				if (is最小縮小 == true && 座標.y < マウス座標.y)
				{
					return true;
				} else {
					is最小縮小 = false;
				}

				if (座標.y > Input::mouse.y + 5 && Input::mouse.moveY > 0)
				{
					return true;
				}

				縦幅 -= Input::mouse.moveY;
				座標.y += Input::mouse.moveY;

				if (座標.y < ツールバー高さ)
				{
					縦幅 -= int(ツールバー高さ - 座標.y);
					座標.y = ツールバー高さ;

				}

				if (縦幅 > 最大縦)
				{
					座標.y += 縦幅 - 最大縦;
					縦幅 = 最大縦;
				}
				if (縦幅 < 最小縦)
				{
					座標.y += 縦幅 - 最小縦;
					縦幅 = 最小縦;
					is最小縮小 = true;
				}




			}

			//下側掴んで拡大縮小中
			if (is下拡縮中)
			{
				if (is最小縮小 == true && 座標.y + タイトル枠高さ + 最小縦 > マウス座標.y)
				{
					return true;
				} else {
					is最小縮小 = false;
				}

				if (座標.y + 縦幅 < Input::mouse.y - タイトル枠高さ - 5 && Input::mouse.moveY < 0)
				{
					return true;
				}

				縦幅 += Input::mouse.moveY;

				if (縦幅 < 最小縦)
				{
					//座標.y += 縦幅 - 最小縦;
					縦幅 = 最小縦;
					is最小縮小 = true;
				}
				if (縦幅 > 最大縦) { 縦幅 = 最大縦; }
			}

			//スクロールバー掴んでいる
			if (isスクロール中 &&
				マウス座標.y > 座標.y + タイトル枠高さ &&
				マウス座標.y < 座標.y + タイトル枠高さ + 縦幅)
			{
				スクロール位置 += Input::mouse.moveY * 縦内部幅 / 縦幅;
			}

			if (スクロール位置 > 縦内部幅 - 縦幅) { スクロール位置 = 縦内部幅 - 縦幅; }
			if (スクロール位置 < 0) { スクロール位置 = 0; }

			//クリックしてないなら以降の処理はなし//
			if (Input::mouse.Left.on == false)
			{
				return false;
			}
			
			//閉じる判定//
			if (abs(マウス座標.x - (座標.x + 横幅 - タイトル枠高さ / 2 - 2)) < タイトル枠高さ/2-1 &&
				abs(マウス座標.y - (座標.y + 2 + タイトル枠高さ/2)) < タイトル枠高さ/2-1)
			{
				is表示 = false;
				return true;
			}


			//上側掴む
			if (abs(マウス座標.y - 座標.y) < 10 &&
				マウス座標.x > 座標.x &&
				マウス座標.x < 座標.x + 横幅) 
			{
				掴み座標.x = 座標.x - マウス座標.x;
				掴み座標.y = 座標.y - マウス座標.y;

				is上拡縮中 = true;
				return true;
			}
			//下側掴む
			if (abs(マウス座標.y - (座標.y + 縦幅 + タイトル枠高さ)) < 10 &&
				マウス座標.x > 座標.x &&
				マウス座標.x < 座標.x + 横幅)
			{
				掴み座標.x = 座標.x - マウス座標.x;
				掴み座標.y = 座標.y - マウス座標.y;
				is下拡縮中 = true;
				return true;
			}
			//タイトル掴む
			if (マウス座標.y > 座標.y &&
				マウス座標.y < 座標.y + タイトル枠高さ &&
				マウス座標.x > 座標.x &&
				マウス座標.x < 座標.x + 横幅 )
			{
				掴み座標.x = 座標.x - マウス座標.x;
				掴み座標.y = 座標.y - マウス座標.y;
				is移動中 = true;
				return true;
			}

			//スクロール掴む
			if (マウス座標.y > 座標.y + タイトル枠高さ &&
				マウス座標.y < 座標.y + タイトル枠高さ + 縦幅 &&
				マウス座標.x > 座標.x + 横幅 - 24 &&
				マウス座標.x < 座標.x + 横幅)
			{
				//スクロール位置を計算
				//最小0 ～ 縦内部幅 - 縦幅
				double dis_y = double( マウス座標.y - (座標.y + タイトル枠高さ) ) / 縦幅;
				int スクロール移動位置 = int((縦内部幅) * (dis_y));

				if (スクロール移動位置 < スクロール位置 )
				{
					スクロール位置 -= 縦幅;
				}
				else if (スクロール移動位置 > スクロール位置 + 縦幅)
				{
					スクロール位置 += 縦幅;
				}
				else
				{
					isスクロール中 = true;
				}

				if (スクロール位置 > 縦内部幅 - 縦幅) { スクロール位置 = 縦内部幅 - 縦幅; }
				if (スクロール位置 < 0) { スクロール位置 = 0; }

				return true;
			}

			return false;
		}

		bool 前面Check()
		{
			if (is最前面)
			{
				is最前面 = false;
				return true;
			}

			return Rect(座標.x, 座標.y, 横幅, タイトル枠高さ + 縦幅).Hit(&Input::mouse.GetPoint()) && Input::mouse.Left.on;
		}

		/*falseなら固定部分のみ、trueなら全体*/
		void 描画範囲(bool is全体)
		{
			if (is全体)
			{
				//固定部分外して相対座標
				SDX::Camera::Get()->position = { -相対座標.x,-相対座標.y };
				Screen::GetRenderer()->SetClip({ 4,4 + スクロール位置,横幅 - 28,縦幅 - 8 - 固定縦});
			} else {
				//固定部分
				SDX::Camera::Get()->position = { -座標.x,-座標.y - タイトル枠高さ };
				Screen::GetRenderer()->SetClip({ 4,4 ,横幅 - 28,縦幅 - 8 });
			}
		}
	};
}