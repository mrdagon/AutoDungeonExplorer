//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*イベントログウィンドウ*/
	class W_EventLog : public UIWindow
	{
		class UILog : public UIObject
		{
			public:
			void Draw派生() override
			{

			}
		};


	public:	
		//タブ
		UITab タブ[5];

		int 現在タブ = 0;

		void Init()
		{
			Set( WindowType::EventLog , IconType::ログ );
			SetPos(LLog::ウィンドウ, false, true, false);

			/*
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;
			固定縦 = 50;
			*/

			//全て
			//クエスト
			//ボス
			//宝物
			//ダンジョン発見
			//種類アイコン[LogType::重要] = IconType::ランク;
			//種類アイコン[LogType::経営] = IconType::情報;
			//種類アイコン[LogType::人事] = IconType::求人;
			//種類アイコン[LogType::製造] = IconType::製造;
			//種類アイコン[LogType::探索] = IconType::迷宮;
		}

		void Update()
		{
			SetPos(LLog::ウィンドウ, false, true, false);
		}
	};
}