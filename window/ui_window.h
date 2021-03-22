//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*ウィンドウベースクラス*/
	class UIWindow
	{
	private:
		bool is最小縮小;
	public:
		static const int タイトル枠高さ = 30;
		static const int ツールバー高さ = 90;

		WindowType 種類;
		IUIDesign* デザイン = &UIDesign::Green;

		//描画および操作可能なオブジェクト
		std::vector<UIObject*> ui_objects;//スクロールするオブジェクト
		std::vector<UIObject*> 固定objects;//スクロールしないオブジェクト

		bool is閉じるボタン = true;
		bool is固定 = false;//大きさ変更と掴み移動可能フラグ

		//状態
		bool is表示 = true;//
		IconType アイコン = IconType::閉じる;

		//座標
		Point 座標;
		Point 相対座標;//タイトル部分を除外した、スクロール位置計算後の左上座標
		
		int 横幅;
		int 縦幅;//タイトル部分は含まない
		int 最大縦, 最小縦;
		int 固定縦 = 0;//スクロールせずに固定な部分の高さ

		//内部の幅、内部幅が縦幅より大きい場合スクロールバーが出る
		double 縦内部幅;
		double スクロール位置 = 0;//最小0、最大立幅内部 - 立幅
		bool isスクロールバー表示 = true;

		//つかみ処理用、一時変数
		Point 掴み座標;
		bool is移動中 = false;
		bool is上拡縮中 = false;
		bool is下拡縮中 = false;
		bool isスクロール中 = false;

		bool is最前面へ移動 = false;//trueの時、falseにして一番前に持ってくる


		int ポップアップリザルト = 0;

		/*各種初期化*/
		virtual void Init() = 0;

		virtual void Update(){}

		//基本情報を代入
		void Set(WindowType 種類 , IUIDesign* デザイン , IconType アイコン)
		{
			this->種類 = 種類;
			this->デザイン = デザイン;
			this->アイコン = アイコン;
		}

		template<class TUIEnum>
		void SetPos(TUIEnum type , bool isSetCenter , bool isスクロールバー)
		{
			横幅 = UILayout::Data(type).w;
			縦幅 = UILayout::Data(type).h;

			if (isSetCenter)
			{
				座標.x = Window::GetWidth() / 2 - 横幅 / 2;
				座標.y = Window::GetHeight() / 2 - 縦幅 / 2;
			}

			最小縦 = 縦幅;
			最大縦 = 縦幅;
			縦内部幅 = 縦幅;

			スクロール位置 = 0;
			isスクロールバー表示 = isスクロールバー;
		}

		/*描画処理と操作処理*/
		void Draw()
		{
			if (is表示 == false) { return; };

			相対座標.x = 座標.x;
			相対座標.y = 座標.y - スクロール位置 + タイトル枠高さ + 固定縦;

			共通Draw();


			Reset描画範囲(false);
			////配列の後ろから描画
			for (int a = (int)ui_objects.size() - 1; a >= 0; a--)
			{
				if (ui_objects[a]->is表示) { ui_objects[a]->Draw(); }
			}

			Reset描画範囲(true);
			for (int a = (int)固定objects.size() - 1; a >= 0; a--)
			{
				if (固定objects[a]->is表示) { 固定objects[a]->Draw(); }
			}

			派生Draw();
			Screen::GetRenderer()->SetClip();
			SDX::Camera::Get()->position = { 0,0 };
			return;
		}
		
		void 共通Draw()
		{
			//タイトル部分
			デザイン->Draw(UIType::タイトル, 座標.x, 座標.y, 横幅, タイトル枠高さ);

			//ウィンドウアイコン			
			デザイン->Draw(UIType::背景, 座標.x + 6, 座標.y + 6, タイトル枠高さ - 12, タイトル枠高さ - 12);
			
			MFont::M->Draw({ 座標.x + 34,座標.y + 1 }, Color::White ,{ TX::Window_名前[種類] });
			//MIcon::UI[アイコン].DrawRotate({ 座標.x + 15,座標.y + 15 }, 1, 0);

			//閉じるボタン/ヘルプボタン
			if (is閉じるボタン == true)
			{
				デザイン->Draw(UIType::背景, 座標.x + 横幅 - 25, 座標.y + 6, タイトル枠高さ - 12, タイトル枠高さ - 12);
				//MIcon::UI[IconType::閉じる].DrawRotate({ 座標.x + 横幅 - 16 ,座標.y + 15 }, 1, 0);
			}

			//メイン部分描画
			デザイン->Draw(UIType::ウィンドウ, 座標.x, 座標.y + タイトル枠高さ, 横幅, 縦幅);

			//ウィンドウスクロール部分
			//スクロール最大高さ = 縦幅-8-8
			if (縦幅 < 縦内部幅)
			{
				MSystem::DrawWindow({ 座標.x + 横幅 - 26 , 座標.y + タイトル枠高さ + 4 }, 20, 縦幅 - 8, 2, -1);

				int scrH = int((縦幅 - 16) * 縦幅 / 縦内部幅);
				int scrY = int(座標.y + タイトル枠高さ + 8 + (縦幅 - 16) * スクロール位置 / 縦内部幅);
				MSystem::DrawWindow({ 座標.x + 横幅 - 23 , scrY }, 14, scrH, 14);
			}
		}
		
		virtual void 派生Draw()
		{
		};

		/*なんらかの操作をしたorウィンドウ上にあった場合 trueを返す*/
		bool Input()
		{
			if (is表示 == false) { return false; };

			bool is操作 = 共通Input();

			相対座標.x = 座標.x;
			相対座標.y = 座標.y - スクロール位置 + タイトル枠高さ + 固定縦;

			//ウィンドウ範囲内の時の操作
			if (Input::mouse.x >= 座標.x &&
				Input::mouse.x <= 座標.x + 横幅 &&
				Input::mouse.y >= 座標.y &&
				Input::mouse.y <= 座標.y + 縦幅 + タイトル枠高さ)
			{
				is操作 = is操作 || 派生Input();
			}

			return is最前面へ移動 || is操作 || Rect(座標.x,座標.y, 横幅 , タイトル枠高さ + 縦幅).Hit(&Input::mouse.GetPoint());		
		}
		
		//ドラッグ移動、拡大、縮小、閉じる、ホイール操作
		bool 共通Input()
		{
			Point マウス座標 = Input::mouse.GetPoint();

			//ホイール操作
			if (isスクロールバー表示 && Rect(座標.x, 座標.y + タイトル枠高さ, 横幅, 縦幅).Hit(&Input::mouse.GetPoint()) && Input::mouse.Whell != 0 && !is下拡縮中 && !is上拡縮中 && !isスクロール中)
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
				座標.x = マウス座標.x + 掴み座標.x;
				座標.y = マウス座標.y + 掴み座標.y;

				座標.x = std::min(double(Window::GetWidth() - 横幅), 座標.x);
				座標.x = std::max(0.0, 座標.x);

				座標.y = std::min(double(Window::GetHeight() - 縦幅 - タイトル枠高さ), 座標.y);
				座標.y = std::max(double(ツールバー高さ), 座標.y);

				return true;
			}
			else {
				座標.x = std::min(double(Window::GetWidth() - 横幅), 座標.x);
				座標.x = std::max(0.0, 座標.x);

				座標.y = std::min(double(Window::GetHeight() - 縦幅 - タイトル枠高さ), 座標.y);
				座標.y = std::max(double(ツールバー高さ), 座標.y);
			}

			//上側掴んで拡大縮小中
			if (is上拡縮中)
			{
				if (is最小縮小 == true && 座標.y < マウス座標.y)
				{
					return true;
				}
				else {
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
				}
				else {
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
			if (isスクロール中 && isスクロールバー表示 &&
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
			if (is閉じるボタン &&
				abs(マウス座標.x - (座標.x + 横幅 - タイトル枠高さ / 2 - 2)) < タイトル枠高さ / 2 - 1 &&
				abs(マウス座標.y - (座標.y + 2 + タイトル枠高さ / 2)) < タイトル枠高さ / 2 - 1)
			{
				is表示 = false;
				MSound::効果音[SE::ウィンドウ閉じ].Play();
				return true;
			}

			//上側掴む
			if (is固定 == false &&
				abs(マウス座標.y - 座標.y) < 10 &&
				マウス座標.x > 座標.x &&
				マウス座標.x < 座標.x + 横幅)
			{
				掴み座標.x = 座標.x - マウス座標.x;
				掴み座標.y = 座標.y - マウス座標.y;

				is上拡縮中 = true;
				return true;
			}
			//下側掴む
			if (is固定 == false &&
				abs(マウス座標.y - (座標.y + 縦幅 + タイトル枠高さ)) < 10 &&
				マウス座標.x > 座標.x &&
				マウス座標.x < 座標.x + 横幅)
			{
				掴み座標.x = 座標.x - マウス座標.x;
				掴み座標.y = 座標.y - マウス座標.y;
				is下拡縮中 = true;
				return true;
			}
			//タイトル掴む
			if (is固定 == false &&
				マウス座標.y > 座標.y &&
				マウス座標.y < 座標.y + タイトル枠高さ &&
				マウス座標.x > 座標.x &&
				マウス座標.x < 座標.x + 横幅)
			{
				掴み座標.x = 座標.x - マウス座標.x;
				掴み座標.y = 座標.y - マウス座標.y;
				is移動中 = true;
				return true;
			}

			//スクロール掴む
			if (isスクロールバー表示 &&
				マウス座標.y > 座標.y + タイトル枠高さ &&
				マウス座標.y < 座標.y + タイトル枠高さ + 縦幅 &&
				マウス座標.x > 座標.x + 横幅 - 24 &&
				マウス座標.x < 座標.x + 横幅)
			{
				//スクロール位置を計算
				//最小0 ～ 縦内部幅 - 縦幅
				double dis_y = double(マウス座標.y - (座標.y + タイトル枠高さ)) / 縦幅;
				int スクロール移動位置 = int((縦内部幅) * (dis_y));

				if (スクロール移動位置 < スクロール位置)
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

		virtual bool 派生Input()
		{
			//配列の前からチェック
			for (auto& it : 固定objects)
			{
				//クリックとドロップのチェック
				if (it->CheckInput(座標.x, 座標.y + タイトル枠高さ)) { return true; };
			}

			for (auto& it : ui_objects)
			{
				//クリックとドロップのチェック
				if (it->CheckInput(相対座標.x, 相対座標.y)) { return true; };
			}

			return false;
		};

		//どこかをクリックするか、最前面フラグがtrueの時最前面へ
		bool Check最前面へ移動()
		{
			if (is最前面へ移動)
			{
				is最前面へ移動 = false;
				return true;
			}

			return Rect(座標.x, 座標.y, 横幅, タイトル枠高さ + 縦幅).Hit(&Input::mouse.GetPoint()) && Input::mouse.Left.on;
		}

		/*描画範囲の制限と描画位置補正を計算.falseなら固定部分のみ、trueなら全体*/
		void Reset描画範囲(bool is固定)
		{
			int スクロールバー太さ = 28;
			if ( isスクロールバー表示 == false) { スクロールバー太さ = 0; }

			if (is固定)
			{
				//固定部分
				SDX::Camera::Get()->position = { -座標.x,-座標.y - タイトル枠高さ };
				Screen::GetRenderer()->SetClip({ 4,4 ,横幅 - スクロールバー太さ,縦幅 - 8 });
			} else {
				//固定部分を省いた相対座標
				SDX::Camera::Get()->position = { -相対座標.x,-相対座標.y };
				Screen::GetRenderer()->SetClip({ 4,4 + スクロール位置,横幅 - スクロールバー太さ,縦幅 - 8 - 固定縦 });
			}
		}

		/*最前面にこのウィンドウだけ表示*/
		int Openポップアップ(bool is多重呼び出し = false)
		{
			is表示 = true;
			is固定 = true;

			//ポップアップからのポップアップ呼び出し以外は裏を暗くする
			if (is多重呼び出し == false)
			{
				Drawing::Rect({ 0,0,Window::GetWidth(),Window::GetHeight() }, Color(0, 0, 0, 128));
			}


			//現在の画面を記憶
			Image img(Renderer::mainRenderer.GetTexture(), Window::GetWidth() , Window::GetHeight() );

			while (System::Update(true,false))
			{
				//img.DrawExtend({ 0,0 , Window::GetWidth() / full_rate, Window::GetHeight() / full_rate });
				img.DrawPartExtend({ 0,0 , Window::GetWidth() , Window::GetHeight() }, { 0,0 , Window::GetWidth() * Config::解像度X倍 , Window::GetHeight() * Config::解像度X倍 });

				Update();
				Draw();
				//ポップアップではドラッグ＆ドロップ無し
				//ウィンドウの拡大縮小ドラッグ＆ドロップ無し
				共通Input();
				派生Input();

				//✗クリック判定
				if (is閉じるボタン == true &&
					abs(Input::mouse.x - (座標.x + 横幅 - タイトル枠高さ / 2 - 2)) < タイトル枠高さ / 2 - 1 &&
					abs(Input::mouse.y - (座標.y + 2 + タイトル枠高さ / 2)) < タイトル枠高さ / 2 - 1 && 
					Input::mouse.Left.on )
				{
					is表示 = false;
					ポップアップリザルト = 0;
					MSound::効果音[SE::ウィンドウ閉じ].Play();
					break;
				}

				if (CV::isデバッグ)
				{
					UILayout::Draw();
					UILayout::Input();
				}

				if (is表示 == false){ break; }
			}

			Input::mouse.Left.on = false;
			img.Release();

			return ポップアップリザルト;
		}

		void AddItem( UIObject& object , bool is固定 = false)
		{
			if (is固定 == true)
			{
				固定objects.push_back(&object);
			} else {
				ui_objects.push_back(&object);
			}
		}
	};

}