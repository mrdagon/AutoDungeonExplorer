//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*待遇変更ウィンドウ*/
	class W_Skilltree : public UIWindow
	{
	private:
		class GUI_編集中ギルメン : public GUI_Object
		{
		public:
			W_Skilltree* 親;

			void Draw派生(double px, double py)
			{
				auto it = 親->ギルメン;

				//枠
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				//キャラクター
				it->image[0][1]->DrawRotate({ px + Lp(40) , py + Lp(41) }, 2, 0);
				//名前
				MFont::MAlias.DrawBold({ px + Lp(42) ,py + Lp(43) }, Color::White, Color::Black, it->名前, false);
				//LV
				MFont::SAlias.DrawBold({ px + Lp(44) ,py + Lp(45) }, Color::White, Color::Black, {"Lv " , it->Lv}, true);

				//選択ボタン
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(60),py + Lp(62) },2,0);
				MIcon::UI[IconType::三角].DrawRotate({ px + Lp(61),py + Lp(62) },2,0, true);

				//例外的に入力処理もここでやる
			}

			void Click(double px, double py)
			{
				//ギルメン切り替え
				if (px < 位置.GetW() / 2)
				{
					親->配置id--;
					if (親->配置id < 0) { 親->配置id = Guild::P->最大パーティ数*5 -1; }
				} else {
					親->配置id++;
					if (親->配置id >= Guild::P->最大パーティ数 * 5) { 親->配置id = 0; }
				}

				
				親->ギルメン = Guild::P->探索パーティ[親->配置id / 5].メンバー[親->配置id % 5];

				W_Drag::Aスキル = nullptr;
			}

			void Info派生(Point 座標) override
			{

			}
		};

		class GUI_スキルポイント : public GUI_Object
		{
		public:
			W_Skilltree* 親;
			void Draw派生(double px, double py)
			{
				auto it = 親->ギルメン;

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				MFont::MAlias.DrawBold({ px + Lp(46) ,py + Lp(47) }, Color::White, Color::Black, { "SkillPoint " , it->スキルポイント }, false);
			}
		};

		class GUI_スキル枠 : public GUI_Object
		{
		public:
			bool isアクティブ枠;//fならパッシブ

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				MFont::SAlias.DrawBold({ px + Lp(48) ,py + Lp(49) }, Color::White, Color::Black, (isアクティブ枠) ? ("ActiveSkill") : ("PassiveSkill"), false);
			}
		};

		class GUI_NowAスキル : public GUI_Object
		{
		public:
			W_Skilltree* 親;
			int id;

			void Draw派生(double px, double py)
			{
				auto it = 親->ギルメン->Aスキル[id];

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 0,0);
				//スキルアイコン
				MSystem::DrawSkill(it->image, { px + Lp(64) , py + Lp(65) }, Color(200, 64, 64));
				//習得に必要なポイントorレベル
				MFont::SAlias.DrawBold({ px + Lp(66) ,py + Lp(67) }, Color::White, Color::Black, {"Slot ",id+1}, true);
			}

			void Drop(double px, double py)
			{
				if (W_Drag::Aスキル == nullptr) { return; }
				
				for (int a = 0; a < 4; a++)
				{
					if (親->ギルメン->Aスキル[a] == W_Drag::Aスキル)
					{
						親->ギルメン->Aスキル[a] = 親->ギルメン->Aスキル[id];
						親->ギルメン->Aスキル[id] = W_Drag::Aスキル;
						return;
					}
				}

				親->ギルメン->Aスキル[id] = W_Drag::Aスキル;
			}

			void Info派生(Point 座標) override
			{
				InfoASkillSub(親->ギルメン->Aスキル[id], 座標, true);
			}
		};

		class GUI_Aスキル : public GUI_Object
		{
		public:
			W_Skilltree* 親;
			int id;

			void Draw派生(double px, double py)
			{
				auto it = 親->ギルメン->職業->習得Aスキル[id];
				bool is習得 = true;
				int 凹み = 0;

				if (it == nullptr) { return; }

				if (!is習得) {
					MSystem::DrawWindow({ px ,py }, (int)位置.GetW(), (int)位置.GetH(), 2 - 凹み * 2, 凹み);
				} else {
					MSystem::DrawWindow({ px ,py }, (int)位置.GetW(), (int)位置.GetH(), 0, 凹み);
				}

				//スキルアイコン
				MSystem::DrawSkill( it->image , { px + Lp(50),py + Lp(51) }, (is習得) ? Color(200, 64, 64) : Color::Gray);
				//習得に必要なポイントorレベル
				if (!is習得) { MFont::SAlias.DrawBold({ px + Lp(52) ,py + Lp(53) }, Color::White, Color::Black, { "Lv" , 1 }, true); }
			}

			void Click(double px, double py)
			{
				auto it = 親->ギルメン->職業->習得Aスキル[id];

				//習得済みなら掴む
				W_Drag::Aスキル = it;
				return;


				//未習得でポイント足りてるなら仮習得
				//if (親->ギルメン->スキルポイント < it->必要SP) { return; }
				//親->Aスキル仮習得ID = (親->Aスキル仮習得ID == id) ? (-1) : (id);
				//親->Pスキル仮習得ID =-1;
			}

			void Info派生(Point 座標) override
			{
				InfoASkillSub( 親->ギルメン->職業->習得Aスキル[id],座標,true);
			}
		};

		class GUI_Pスキル : public GUI_Object
		{
		public:
			W_Skilltree* 親;
			int id;

			void Draw派生(double px, double py)
			{
				auto it = 親->ギルメン->職業->習得Pスキル[id];
				bool is習得 = true;
				int 凹み = 0;

				if (it == nullptr) { return; }

				if (!is習得) {
					if (親->Pスキル仮習得ID == id ) { 凹み = -1; }
				}

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 2 - 凹み * 2, 凹み);
				//スキルアイコン
				MSystem::DrawSkill( it->image, { px + Lp(54) ,py + Lp(55) }, (is習得) ? Color(0, 141, 255) : Color::Gray, "");
			}

			void Click(double px, double py)
			{
				//未習得でポイント足りてるなら仮習得
				auto it = 親->ギルメン->職業->習得Pスキル[id];

				if (it == nullptr) { return; }


				親->Pスキル仮習得ID = (親->Pスキル仮習得ID == id) ? (-1) : (id);
			}

			void Info派生(Point 座標) override
			{
				//親->ギルメン->isPスキル習得[id]
				auto it = 親->ギルメン->職業->習得Pスキル[id];
				if (it == nullptr) { return; }

				InfoPSkillSub(it,座標,true,true);
			}
		};

		class GUI_再教育 : public GUI_Object
		{
		public:
			W_Skilltree* 親;
			W_Skilltree* base;
			W_Popup 確認ウィンドウ;

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1, 1);

				MFont::MAlias.DrawBold({ px + Lp(58) ,py + Lp(59) }, Color::White, Color::Black, "再教育", false);
			}

			void Click(double px, double py)
			{
				//ポップアップでスキルリセットするか確認してするなら
				確認ウィンドウ.is表示 = true;
				確認ウィンドウ.Init();
				確認ウィンドウ.文章.text = "スキルをリセットする？\n(レベルが５下がる)";

				int res = 確認ウィンドウ.Openポップアップ();

				//はい ならレベル下げてスキルリセット
				if (res == 1)
				{
					親->ギルメン->スキルリセット(5);
				}

			}
		};

		class GUI_習得 : public GUI_Object
		{
		public:
			W_Skilltree* 親;
			W_Skilltree* base;

			void Draw派生(double px, double py)
			{
				std::string str = "";

				if (親->Pスキル仮習得ID >= 0 ) {

					MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1, 1);
				} else {
					str = "習得";
					MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 2, 0);
				}


				MFont::MAlias.DrawBold({ px + Lp(63) ,py + Lp(59) }, Color::White, Color::Black, str, false);
			}

			void Click(double px, double py)
			{
				//選択中のスキルを習得
				if (親->Pスキル仮習得ID >= 0)
				{
					auto ps = 親->ギルメン->職業->習得Pスキル[親->Pスキル仮習得ID];

					//習得処理
					//親->ギルメン->isPスキル習得[親->Pスキル仮習得ID] = true;
					親->Pスキル仮習得ID = -1;
				}
			}
		};

	public:
		GUI_編集中ギルメン 編集中ギルメン;//キャラアイコンと名前
		GUI_スキルポイント スキルポイント;//現在のスキルポイントと獲得後のスキルポイント
		GUI_スキル枠 Aスキル枠;//Aスキル表示エリア
		GUI_スキル枠 Pスキル枠;//Pスキル表示エリア
		GUI_NowAスキル NowAスキル[CV::最大Aスキル数];//Pスキル
		GUI_再教育 再教育;
		GUI_習得 習得;

		std::array<GUI_Aスキル, 100> Aスキル;
		std::array<GUI_Pスキル, 100> Pスキル;
		//決定ボタン
		//キャンセルボタン
		Explorer* ギルメン;
		int 配置id;;
		int Pスキル仮習得ID = -1;

		void Init()
		{
			種類 = WindowType::Skilltree;
			タイトル名 = TX::Window_名前[種類];
			省略名 = TX::Window_略記[種類];
			アイコン = IconType::ランク;
			横幅 = 230;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 縦幅;
			縦内部幅 = 縦幅;
			スクロール位置 = 0;
			isスクロールバー表示 = false;
			
			編集中ギルメン.親 = this;
			スキルポイント.親 = this;
			Aスキル枠.isアクティブ枠 = true;
			Pスキル枠.isアクティブ枠 = false;
			再教育.親 = this;
			習得.親 = this;

			int a = 0;

			for (auto& it : NowAスキル)
			{
				it.親 = this;
				it.id = a;
				a++;
			}

			for (int a = 0; a < Aスキル.size(); a++)
			{
				Aスキル[a].id = a;
				Aスキル[a].親 = this;
			}
			for (int a = 0; a < Pスキル.size(); a++)
			{
				Pスキル[a].id = a;
				Pスキル[a].親 = this;
			}
		}
	};
}