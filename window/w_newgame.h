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

		class UIボタン : public UIButton
		{
		public:
			W_Newgame* 親;
			GameType 難易度;

			void Click() override
			{
				親->is表示 = false;
				親->ポップアップリザルト = 1;
			}

			void Over() override
			{
				親->マウスオーバー中難易度 = 難易度;
			}
		};

	public:
		UIボタン 難易度ボタン[(int)GameType::COUNT];
		UITextFrame 説明;

		GameType 選択中難易度 = GameType::ノーマル;
		GameType マウスオーバー中難易度 = GameType::COUNT;

		void Init()
		{
			Set(WindowType::Newgame, IconType::情報);
			SetPos(LTitle::始めから_ウィンドウ,true,false,true);

			int a = 0;
			for (auto& it : 難易度ボタン)
			{
				it.親 = this;
				it.難易度 = GameType(a);
				it.SetUI(TX::難易度[a],LTitle::始めから_ボタン, a);
				item.push_back(&it);
				a++;
			}

			説明.SetUI("ここに難易度の説明が出ます\n※β版ではどの難易度も同じです", LTitle::始めから_説明枠);
			item.push_back(&説明);

			選択中難易度 = GameType::COUNT;
			マウスオーバー中難易度 = GameType::COUNT;
		}

		void Update()
		{
			SetPos(LTitle::始めから_ウィンドウ, true, false,true);
		}
	};
}