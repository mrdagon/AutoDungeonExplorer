//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[6][a]



	/*求人ウィンドウ*/
	class W_Recruit: public WindowBox
	{
	private:

		class GUI_Reqback :public GUI_Object
		{
		public:

			void Draw派生(double px, double py)
			{
				//枠の描画
				MSystem::DrawWindow({ px      , py }, 位置.GetW(), 位置.GetH(), 12);
			}
		};

		class GUI_ReqPoint :public GUI_Object
		{
		public:
			W_Recruit *親;

			void Draw派生(double px, double py)
			{
				//枠の描画
				MSystem::DrawWindow({ px      , py }, 位置.GetW(), 位置.GetH(), 11);

				MIcon::アイコン[IconType::求人].DrawRotate({ px + LV(22),py + LV(23) },2,0);

				MFont::BArial中.DrawBold({ px + LV(24) ,py + LV(25) }, Color::White, Color::Black, { Guild::P->人事ポイント }, true);


				if (W_Drag_Drop::ギルメン != nullptr && W_Drag_Drop::ギルメン->所属 == -1)
				{
					親->要求点 = 2;
				}

				if (親->要求点 > 0)
				{
					MFont::BArial中.DrawBold({ px + LV(26) ,py + LV(25) }, { 255,128,128 }, Color::Black, { "→" }, true);
					MFont::BArial中.DrawBold({ px + LV(27) ,py + LV(25) }, { 255,128,128 }, Color::Black, { Guild::P->人事ポイント - 親->要求点 }, true);
					親->要求点 = 0;
				}

			}
		};

		class GUI_ReqRoll :public GUI_Object
		{
		public:
			W_Recruit* 親;
			bool isPush = false;
			int 連打防止 = 0;

			void Draw派生(double px, double py)
			{
				//枠の描画
				if (Input::mouse.Left.hold && isPush == true)
				{
					MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 3, -1);
				} else {
					isPush = false;
					MSystem::DrawWindow({ px , py }, 位置.GetW(), 位置.GetH(), 1, 1);
				}

				MIcon::アイコン[IconType::再募集].DrawRotate({ px + LV(28),py + LV(23) }, 1, 0, true);
				MFont::BArial中.DrawBold({ px + LV(29) ,py + LV(25) }, Color::White , Color::Black, { "Reroll" }, true);
				連打防止--;
			}

			void Click(double px, double py)
			{

				//志願者のリロール
				isPush = true;
				if (連打防止 > 0) { return; }
				//人事点があるかチェックして-1する
				if (Guild::P->人事ポイント <= 0)
				{
					return;
				}

				//志願者のリロール、とりあえず5人
				int count = 0;
				for (auto&it : Warker::data )
				{
					if (it.所属 == -1)
					{
						//再生成する
						it.Make(it.ID, Rand::Get(4), 1, "ナナーシ");
						count++;
					}
				}

				//足りてない部分は新規作成
				for (; count < 6; count++)
				{
					Warker::data.emplace_back();
					Warker::data.back().Make((int)Warker::data.size()-1, Rand::Get(4), 1, "シンキー");
				}

				Guild::P->人事ポイント--;

			}

			void Over(double px, double py) override
			{
				親->要求点 = 1;
			}
		};

		class GUI_Req : public GUI_Object
		{
		public:
			W_Recruit *親ウィンドウ;
			Warker* 参照先;
			int 並びID;

			GUI_Req(Warker* 参照先) :
				参照先(参照先)
			{}


			void Draw派生(double px, double py)
			{
				//現在客数,ピーク客数,合計客数
				
				//キャラアイコン,レベル,雇用予定表示
				if (参照先->所属 >= 0)
				{
					MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				} else {
					MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				}

				MUnit::ユニット[参照先->見た目][1]->DrawRotate({ px + LV(9) ,py + LV(9) }, 2, 0);
				MFont::BArial小.DrawBold({ px + LV(6) ,py + LV(8) }, Color::White, Color::Black, 参照先->Lv, true);

				MFont::BArial小.DrawBold({ px + LV(7) ,py + LV(8) }, Color::White, Color::Black, "Lv", true);

			}

			void Click(double px, double py)
			{
				W_Drag_Drop::ギルメン = 参照先;
				W_Drag_Drop::ウィンドウ = 親ウィンドウ;
				W_Drag_Drop::並びID = 並びID;
			}


			void Info派生(Point 座標) override
			{
				InfoHunter(参照先,座標);
			}

		};


	public:
		int 要求点 = 0;

		GUI_ReqRoll リロール;
		GUI_ReqPoint 人事点;
		GUI_Reqback 求職枠;
		std::vector<GUI_Req> 求職者;//求職者

		void init()
		{
			種類 = WindowType::Recruit;
			名前 = "求人";
			略記 = "求人";
			アイコン = IconType::求人;
			横幅 = 280;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 180;
			縦内部幅 = 180;//120xランク数
			スクロール位置 = 0;

			リロール.親 = this;
			人事点.親 = this;
		}

		void GUI_init()
		{
			求職者.clear();
			gui_objects.clear();

			for (auto &it : Warker::data)
			{
				if (it.所属 == -1)
				{
					求職者.emplace_back(&it);
				}
			}

			for (auto &it : 求職者)
			{
				gui_objects.push_back(&it);
				it.親ウィンドウ = this;
			}

			if (求職者.size() > 18)
			{
				最大縦 = int(求職者.size()+5) / 6 * LV(5)+15;
				縦内部幅 = 最大縦;
			}

			int n = 0;
			for (auto &it : 求職者)
			{
				it.位置 = { LV(0) + n%6 * LV(4) ,LV(1) + n / 6 *LV(5) ,LV(2),LV(3) };
				it.isヘルプ表示 = true;
				n++;
			}


			求職枠.位置 = { LV(10) , LV(11) , LV(12) , int(求職者.size() + 5) / 6 * LV(5) + LV(13) };
			人事点.位置 = { LV(14) , LV(15) , LV(16) , LV(17) };
			リロール.位置 = { LV(18) , LV(19) , LV(20) , LV(21) };

			リロール.SetHelp("クリック：雇用Pを1消費して、志願者を新たに探します");


			gui_objects.push_back(&求職枠);
			gui_objects.push_back(&人事点);
			gui_objects.push_back(&リロール);
		}

		void 派生Draw()
		{
			GUI_init();

			求職枠.Draw();

			for (auto &it : 求職者)
			{
				it.Draw();
			}

			人事点.Draw();
			リロール.Draw();
		}

		bool 派生操作()
		{
			for (auto& it : 求職者)
			{
				it.操作チェック(相対座標.x, 相対座標.y);
			}

			人事点.操作チェック(相対座標.x, 相対座標.y);
			リロール.操作チェック(相対座標.x, 相対座標.y);

			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}