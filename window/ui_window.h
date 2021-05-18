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
		inline static int ツールバー高さ = 90;

		WindowType 種類;
		Design** デザイン = &Design::No1;
		UIWindow* ヘルプウィンドウ = nullptr;

		//描画および操作可能なオブジェクト
		std::vector<UIObject*> item;//スクロールするオブジェクト
		std::vector<UIObject*> 固定item;//スクロールしないオブジェクト

		bool is閉じるボタン = true;
		bool isヘルプボタン = true;
		bool is固定 = false;//大きさ変更と掴み移動可能フラグ

		//状態
		bool is表示 = true;//
		IconType アイコン = IconType::閉じる;

		//座標
		Point 座標;
		Point 相対座標;//タイトル部分を除外した、スクロール位置計算後の左上座標
		
		int 横幅;
		int 縦幅 = 0;//タイトル部分は含まない
		int 最大縦, 最小縦;
		int 固定縦 = 0;//スクロールせずに固定な部分の高さ

		//内部の幅、内部幅が縦幅より大きい場合スクロールバーが出る
		int 縦内部幅;
		int スクロール位置 = 0;//最小0、最大立幅内部 - 立幅
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
		void Set(WindowType 種類 , IconType アイコン, Design** デザイン = &Design::No1)
		{
			this->種類 = 種類;
			this->デザイン = デザイン;
			this->アイコン = アイコン;
			スクロール位置 = 0;
		}

		template<class TUIEnum>
		void SetPos(TUIEnum type , bool isSetCenter , bool isスクロールバー , bool is縦幅固定 )
		{
			横幅 = Layout::Data(type).w;
			if (is縦幅固定)
			{
				縦幅 = Layout::Data(type).h;
				最小縦 = 縦幅;
				最大縦 = 縦幅;
				縦内部幅 = 縦幅;
			}
			else
			{
				最小縦 = Layout::Data(type).h;
				最大縦 = Config::解像度H;
				縦内部幅 = 最小縦;
			}

			if (isSetCenter)
			{
				座標.x = Config::解像度W / 2 - 横幅 / 2;
				座標.y = Config::解像度H / 2 - 縦幅 / 2;
			}

			isスクロールバー表示 = isスクロールバー;
		}

		/*描画処理と操作処理*/
		void Draw()
		{
			if (is表示 == false) { return; };

			相対座標.x = 座標.x;
			相対座標.y = 座標.y - スクロール位置 + タイトル枠高さ + 固定縦;

			共通Draw();

			Reset描画範囲(true);
			for (int a = (int)固定item.size() - 1; a >= 0; a--)
			{
				if (固定item[a]->is表示) { 固定item[a]->Draw(); }
			}

			Reset描画範囲(false);
			////配列の後ろから描画
			for (int a = (int)item.size() - 1; a >= 0; a--)
			{
				if (item[a]->is表示) { item[a]->Draw(); }
			}


			Screen::GetRenderer()->SetClip();
			SDX::Camera::Get()->position = { 0,0 };
			return;
		}
		
		void 共通Draw()
		{
			//タイトル部分
			Design* de = *デザイン;

			de->Draw(UIType::タイトル, (int)座標.x, (int)座標.y, 横幅, タイトル枠高さ);

			//ウィンドウ名
			MFont::L->Draw({ (int)座標.x + 34,(int)座標.y + 1 }, Color::White, { TX::Window_名前[種類] });

			//ウィンドウアイコン
			de->Draw(UIType::グループ明, (int)座標.x + 6, (int)座標.y + 6, タイトル枠高さ - 12, タイトル枠高さ - 12);
			MIcon::UI[アイコン].DrawRotate({ 座標.x + 15,座標.y + 15 }, 1, 0);

			//閉じるボタン/ヘルプボタン
			if (is閉じるボタン == true)
			{
				//閉じるボタン
				de->Draw(UIType::グループ明, (int)座標.x + 横幅 - 25, (int)座標.y + 6, タイトル枠高さ - 12, タイトル枠高さ - 12);
				MIcon::UI[IconType::閉じる].DrawRotate({ 座標.x + 横幅 - 16 ,座標.y + 15 }, 1, 0);

			}

			//ヘルプボタン
			if (ヘルプウィンドウ != nullptr)
			{
				de->Draw(UIType::グループ明, (int)座標.x + 横幅 - 55, (int)座標.y + 6, タイトル枠高さ - 12, タイトル枠高さ - 12);
				MIcon::UI[IconType::ヘルプ].DrawRotate({ 座標.x + 横幅 - 46 ,座標.y + 15 }, 1, 0);
			}


			//メイン部分描画
			de->Draw(UIType::ウィンドウ, (int)座標.x, (int)座標.y + タイトル枠高さ, 横幅, 縦幅);

			//スクロール
			if (縦幅 < 縦内部幅)
			{
				de->Draw(UIType::丸フレーム, (int)座標.x + 横幅 - 26, (int)座標.y + タイトル枠高さ + 4, 20, 縦幅 - 8);

				int scrH = int((縦幅 - 16) * 縦幅 / 縦内部幅);
				int scrY = int(座標.y + タイトル枠高さ + 8 + (縦幅 - 16) * スクロール位置 / 縦内部幅);
				de->DrawGauge(座標.x + 横幅 - 23, scrY, 14, scrH, 1);
			}
		}
		
		/*なんらかの操作をしたorウィンドウ上にあった場合 trueを返す*/
		bool Input()
		{
			if (is表示 == false) { return false; };

			bool is操作 = 共通Input();

			相対座標.x = 座標.x;
			相対座標.y = 座標.y - スクロール位置 + タイトル枠高さ + 固定縦;

			//ウィンドウ範囲内の時の操作
			if (Input::mouse.x / Config::解像度X倍 >= 座標.x &&
				Input::mouse.x / Config::解像度X倍 <= 座標.x + 横幅 &&
				Input::mouse.y / Config::解像度X倍 >= 座標.y &&
				Input::mouse.y / Config::解像度X倍 <= 座標.y + 縦幅 + タイトル枠高さ)
			{
				is操作 = is操作 || ObjectInput();
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
				スクロール位置 -= Input::mouse.Whell * CV::スクロール感度;

				if (スクロール位置 > 縦内部幅 - 縦幅) { スクロール位置 = 縦内部幅 - 縦幅; }
				if (スクロール位置 < 0) { スクロール位置 = 0; }
			}

			//左押してない場合共通操作なし
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
				座標.y = std::max( is固定 ? 0 : double(ツールバー高さ), 座標.y);

				return true;
			} else {
				座標.x = std::min(double(Window::GetWidth() - 横幅), 座標.x);
				座標.x = std::max(0.0, 座標.x);

				座標.y = std::min(double(Window::GetHeight() - 縦幅 - タイトル枠高さ), 座標.y);
				座標.y = std::max( is固定 ? 0 : double(ツールバー高さ), 座標.y);
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
				スクロール位置 += Input::mouse.moveY / Config::解像度X倍 * 縦内部幅 / 縦幅;
			}

			if (スクロール位置 > 縦内部幅 - 縦幅) { スクロール位置 = 縦内部幅 - 縦幅; }
			if (スクロール位置 < 0) { スクロール位置 = 0; }

			//クリックしてないなら以降の処理はなし//
			if (Input::mouse.Left.on == false)
			{
				return false;
			}

			//閉じる判定//
			if (is閉じるボタン == true &&
				abs(マウス座標.x - (座標.x + 横幅 - タイトル枠高さ / 2 - 2)) < タイトル枠高さ / 2 - 1 &&
				abs(マウス座標.y - (座標.y + 2 + タイトル枠高さ / 2)) < タイトル枠高さ / 2 - 1)
			{
				is表示 = false;
				MSound::効果音[SE::ウィンドウ閉じ].Play();
				ポップアップリザルト = 0;
				return true;
			}

			//ヘルプクリック
			if (ヘルプウィンドウ != nullptr &&
				abs(マウス座標.x - (座標.x + 横幅 - タイトル枠高さ / 2 - 2) + 30) < タイトル枠高さ / 2 - 1 &&
				abs(マウス座標.y - (座標.y + 2 + タイトル枠高さ / 2)) < タイトル枠高さ / 2 - 1)
			{
				ヘルプウィンドウ->OpenPopup();
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

		bool ObjectInput()
		{
			//配列の前からチェック
			if (Input::mouse.y / Config::解像度X倍 - 座標.y - タイトル枠高さ <= 固定縦 )
			{
				for (auto& it : 固定item)
				{
					//クリックとドロップのチェック
					if (it->CheckInput(座標.x, 座標.y + タイトル枠高さ)) { return true; };
				}
			}

			for (auto& it : item)
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
		int OpenPopup(bool is多重呼び出し = false)
		{
			is表示 = true;
			is固定 = true;

			//ポップアップからのポップアップ呼び出し以外は裏を暗くする
			if (is多重呼び出し == false)
			{
				Drawing::Rect({ 0,0,Config::解像度W , Config::解像度H }, Color(0, 0, 0, 128));
			}

			//現在の画面を記憶
			Image img(Renderer::mainRenderer.GetTexture(), Window::GetWidth() , Window::GetHeight() );
			UIObject::over_time = 0;

			do 
			{
				img.DrawPartExtend({ 0,0 , Config::解像度W , Config::解像度H }, { 0,0 , Window::GetWidth() , Window::GetHeight() });

				Update();
				//ポップアップではドラッグ＆ドロップ操作無し
				//ウィンドウの拡大縮小ドラッグ＆ドロップ無し
				Draw();

				if ( UIObject::over_time >= CV::ヘルプ待機時間 && UIObject::now_help != nullptr && Game::isヘルプ == true)
				{
					UIObject::now_help->DrawHelp();
					Camera::Get()->position.x = 0;
					Camera::Get()->position.y = 0;
				}

				//スクショ
				if (Input::key.F10.on == true)
				{
					keybd_event(VK_LWIN, 0, 0, 0);
					keybd_event(VK_LMENU, 0, 0, 0);
					keybd_event(VK_SNAPSHOT, 0, 0, 0);

					keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
					keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0);
				}

				if (CV::isレイアウト)
				{
					Layout::Draw();
					Layout::Input();
				}

				auto prev_help = UIObject::now_help;
				UIObject::now_help = nullptr;
				共通Input();
				ObjectInput();

				if (prev_help == UIObject::now_help)
				{
					UIObject::over_time++;
				} else {
					UIObject::over_time = 0;
				}

				if (is表示 == false){ break; }
			} while (System::Update(true, false));

			Input::mouse.Left.on = false;
			img.Release();
			UIObject::over_time = 0;

			return ポップアップリザルト;
		}

		void AddItem( UIObject& object , bool is固定 = false)
		{
			if (is固定 == true)
			{
				固定item.push_back(&object);
			} else {
				item.push_back(&object);
			}
		}

		template <class TObject>
		void AddItem( std::vector<TObject>& object , bool is固定 = false)
		{
			if (is固定 == true)
			{
				for (auto& it : object)
				{
					固定item.push_back(&it);
				}
			}
			else {
				for (auto& it : object)
				{
					item.push_back(&it);
				}
			}
		}

		template <class TObject>
		void AddItem(TObject object[] , int 要素数 , bool is固定 = false)
		{
			if (is固定 == true)
			{
				for (int i = 0; i < 要素数; i++)
				{
					固定item.push_back(&object[i]);
				}
			}
			else
			{
				for (int i = 0; i < 要素数; i++)
				{
					item.push_back(&object[i]);
				}
			}
		}

	};

}