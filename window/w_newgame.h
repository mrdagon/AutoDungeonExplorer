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
	public:
		UIButton 難易度ボタン[(int)GameType::COUNT];
		UITextFrame 説明;
		GameType 選択中難易度 = GameType::ノーマル;

		void Init()
		{
			Set(WindowType::Newgame, IconType::情報);
			SetPos(LTitle::始めから_ウィンドウ,true,false,true);

			//●初期化
			int a = 0;
			for (auto& it : 難易度ボタン)
			{
				it.SetUI(TX::難易度[a],LTitle::始めから_ボタン, a);

				it.clickEvent = [&]()
				{
					is表示 = false;
					ポップアップリザルト = it.lineID + 1;
					選択中難易度 = GameType(it.lineID);
				};
				a++;
			}
			説明.SetUI("ここに難易度の説明が出ます\n※β版ではどの難易度も同じです", LTitle::始めから_説明枠);

			//●登録
			AddItem(難易度ボタン , (int)GameType::COUNT );
			AddItem(説明);
		}

		void Update()
		{
			SetPos(LTitle::始めから_ウィンドウ, true, false,true);
		}
	};
}