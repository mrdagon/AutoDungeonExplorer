//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/

#pragma once
namespace SDX_BSC
{
	using namespace SDX;
	//テキストウィンドウ２つと、顔と感情吹き出しで会話シーン作る

	class W_Scenario
	{
	private:

	public:
		int csv_page = 0;

		void Draw()
		{
			//テキストと枠


			//キャラドット


			//感情アイコン


		}

		void 操作()
		{
			//クリックで進む

			//スキップボタンクリックで終了

		}

		void ポップアップ呼び出し()
		{
			//裏をやや暗くする
			Drawing::Rect({ 0,0,Window::GetWidth(),Window::GetHeight() }, Color(0, 0, 0, 128));

			//描画倍率を取得
			int full_rate = 1;
			if (Config::ウィンドウモード == Config::WindowmodeType::二倍フルスクリーン) { full_rate = 2; }
			if (Config::ウィンドウモード == Config::WindowmodeType::四倍フルスクリーン) { full_rate = 4; }

			//現在の画面を記憶
			Image img(Renderer::mainRenderer.GetTexture(), Window::GetWidth(), Window::GetHeight());

			while (System::Update(true, false))
			{
				img.DrawExtend({ 0,0 , Window::GetWidth() / full_rate, Window::GetHeight() / full_rate });

				Draw();
				CSVDraw();
				操作();

				if (CV::isデバッグ)
				{
					CSVCheckInput();
				}
			}

			img.Release();

			return ;
		}
	};

}