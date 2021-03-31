//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	//LayoutValue
	using namespace SDX;

	/*経営戦略ウィンドウ*/
	class W_Management : public UIWindow
	{
	private:
		class GUI_MLv : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				double rate = (double)Guild::P->投資経験値 / Management::必要経験値[Guild::P->投資Lv];

				MSystem::DrawBar({ px,py }, (int)位置.GetW(), (int)位置.GetH(), rate, 1, Color::Blue, Color::White, Color::White, true);

				MFont::SDot.DrawBold({ px + Lp(30) ,py + Lp(31) }, Color::White, Color::Black, { "Lv",Guild::P->投資Lv });
			}
		};

		class GUI_Gold : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				//選択戦術の資金消費を表示、不足している場合赤色
				MSystem::DrawWindow({ px ,py }, 位置.GetW(), 位置.GetH(), 11);

				//現在の資金
				MIcon::UI[IconType::資金].Draw({ px + Lp(34) , py + Lp(35) });
				MFont::MAlias.DrawBold({ px + Lp(32) ,py + Lp(33) }, Color::White, Color::Black, { (long long)Guild::P->資金 , " G" }, true);
				//消費する資金
				//if (W_Drag::Over戦術 != nullptr)
				{
					Color fc = { 255,128,128 };
					//if (W_Drag::Over戦術->消費資金 <= Guild::P->資金) { fc = Color(128,255,128); }
					//MFont::MAlias.DrawBold({ px + Lp(36) ,py + Lp(37) }, fc, Color::Black, { "- " ,W_Drag::Over戦術->消費資金 , " G" }, true);
					//W_Drag::Over戦術 = nullptr;
				}
				if ( true )
				{
					Color fc = {255,128,128};
					//if (Guild::P->選択戦術->消費資金 > Guild::P->資金) { fc = Color::Red; }
					MFont::MAlias.DrawBold({ px + Lp(36) ,py + Lp(37) }, fc, Color::Black, {"- " , Management::data[0].消費資金 , " G"}, true);
				}

			}
		};
		class GUI_Rank : public GUI_Object
		{
		public:
			int ランク = 0;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px ,py }, 位置.GetW(), 位置.GetH(), 11);

				MFont::MAlias.DrawBold({ px + Lp(41),py + Lp(42) }, Color::White, Color::Black, { "Lv " , ランク });

			}
		};
		class GUI_Skill : public GUI_Object
		{
		public:
			Management* 参照戦術;
			int クリック時間 = 0;

			void Draw派生(double px, double py)
			{
				Color bc = Color::Black;
				bool can使用 = 参照戦術->is使用可 && (参照戦術->消費資金 <= Guild::P->資金);
			
				//bool isLv = (参照戦術->Lv <= Guild::P->投資Lv[参照戦術->系統]);
				//bool is選択中 = (Guild::P->選択戦術 == 参照戦術->MID);

				/*
				int 枠No = 1;
				int 凹凸 = 0;
				if (参照戦術->is永続 && 参照戦術->使用回数 > 0)
				{
					//使用済み、永続
					枠No = 5;
				}
				else if (!isLv)
				{
					//Lv不足は灰色
					枠No = 15;
				}
				else if (is選択中 || クリック時間 > 0)
				{
					//選択中は凹み
					枠No = 4;
					凹凸 = -2;
				}
				else if (can使用)
				{
					//使用可能で盛り上がり
					枠No = 1;
					凹凸 = 2;
				}
				else
				{
					//資金不足
					枠No = 3;
				}

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(),枠No,凹凸);
				//MIcon::アイコン[参照戦術->アイコン].DrawRotate({px + (int)位置.GetW()/2 - 凹凸,py + (int)位置.GetH()/2 - 凹凸 },2,0);
				*/
				クリック時間--;

			}
			void Click(double px, double py)
			{
				//お金足りてたら使用、不足してたら予約状態にする
				if (!参照戦術->is使用可)
				{
					return;
				}

				/*
				if (Guild::P->選択戦術 != 参照戦術->MID)
				{
					Guild::P->選択戦術 = 参照戦術->MID;
					if (Guild::P->資金 >= 参照戦術->消費資金)
					{
						MSound::効果音[SE::投資実行].Play();
					} else {
						MSound::効果音[SE::投資予約].Play();
					}
				} else {
					Guild::P->選択戦術 = MSkillType::COUNT;
					MSound::効果音[SE::投資解除].Play();
				}
				*/

				クリック時間 = 5;
			}

			void Info派生(Point 座標) override
			{
				InfoManagement(参照戦術, 座標);
			}

		};

	public:

		//タブ無くす
		UIObject 資金;//資金と消費G
		UIObject 街Lv;//街Lv
		//投資案
		UITextFrame Lvグループ;
		//同じ種類でレベル違いは横に並べる？

		int 現在タブ = 0;
		int 戦術数 = 0;

		void Init()
		{
			Set( WindowType::Management, IconType::戦略);
			SetPos( LManagement::ウィンドウ , false , true , false );

			/*
			横幅 = 320;
			縦幅 = 300;
			最小縦 = 200;
			最大縦 = 600;
			縦内部幅 = 600;//変動する
			固定縦 = 85;
			スクロール位置 = 0;
			*/

			Update();
		}

		void Update()
		{
			SetPos(LManagement::ウィンドウ, false, true, false);
		}
	};
}