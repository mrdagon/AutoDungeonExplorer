//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*難易度選択ポップアップウィンドウ*/
	class W_Newgame : public UIWindow
	{
	private:

		class GUI_ボタン : public UIButton
		{
		public:
			W_Newgame* 親;
			GameType 難易度;

			void Click(double px, double py)
			{
				for (auto& it : 親->難易度ボタン)
				{
					it.is押下 = false;
				}

				if (親->選択中難易度 == 難易度)
				{
					親->選択中難易度 = GameType::COUNT;					
				} else {
					親->選択中難易度 = 難易度;
					is押下 = true;
				}
			}

			void Over(double px, double py)
			{
				親->マウスオーバー中難易度 = 難易度;
			}
		};

		class GUI_開始ボタン : public UIButton
		{
		public:
			W_Newgame* 親;

			void Click(double px, double py)
			{
				if (親->選択中難易度 == GameType::COUNT) { return; }
				親->is表示 = false;
				親->ポップアップリザルト = 1;
			}
		};

	public:
		GUI_ボタン 難易度ボタン[(int)GameType::COUNT];
		GUI_開始ボタン 開始;
		UITextFrame 説明;

		GameType 選択中難易度 = GameType::COUNT;
		GameType マウスオーバー中難易度 = GameType::COUNT;

		void Init()
		{
			種類 = WindowType::Newgame;
			デザイン = &UIDesign::Brown;

			タイトル名 = "難易度選択";
			//省略名 = "難易度選択";
			アイコン = IconType::情報;

			横幅 = UILayout::Data(UIタイトル::始めから_ウィンドウ).w;
			縦幅 = UILayout::Data(UIタイトル::始めから_ウィンドウ).h;
			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;
			最小縦 = 縦幅;
			最大縦 = 縦幅;
			縦内部幅 = 縦幅;

			isスクロールバー表示 = false;

			int a = 0;
			for (auto& it : 難易度ボタン)
			{
				it.親 = this;
				it.難易度 = GameType(a);
				it.UIデザイン = &UIDesign::Brown;
				it.SetLayout(UIタイトル::始めから_ボタン);
				it.lineID = a;
				ui_objects.push_back(&it);
				a++;
			}

			難易度ボタン[0].テキスト = "ノーマル";
			難易度ボタン[1].テキスト = "ハードコア";
			難易度ボタン[2].テキスト = "デスマーチ";

			開始.UIデザイン = &UIDesign::Brown;
			開始.テキスト = "決定";
			開始.親 = this;
			開始.SetLayout(UIタイトル::始めから_開始ボタン);
			ui_objects.push_back(&開始);

			説明.UIデザイン = &UIDesign::Brown;
			説明.テキスト = "ここに難易度の説明が出ます\n※β版ではどの難易度も同じです";
			説明.SetLayout(UIタイトル::始めから_説明枠);
			ui_objects.push_back(&説明);

			選択中難易度 = GameType::COUNT;
			マウスオーバー中難易度 = GameType::COUNT;

		}

		void Update()
		{
			横幅 = UILayout::Data(UIタイトル::始めから_ウィンドウ).w;
			縦幅 = UILayout::Data(UIタイトル::始めから_ウィンドウ).h;
			座標.x = Window::GetWidth() / 2 - 横幅 / 2;
			座標.y = Window::GetHeight() / 2 - 縦幅 / 2;
		}
	};
}