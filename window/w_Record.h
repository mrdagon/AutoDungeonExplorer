//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	using namespace SDX;
#define LV(a) DV::I[14][a]


	//ギルド情報と統合したのでボツ
	/*決算ログ*/
	class W_SettleLog : public WindowBox
	{
	private:
		class GUI_日付 : public GUI_Object
		{
		public:
			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				//通算or月間
				MFont::BArial中.DrawBold({ px + LV(9) ,py + LV(10) }, Color::White, Color::Black, "通算", false);
				MIcon::アイコン[IconType::三角].Draw({ px + LV(11),py + LV(13) });
				MIcon::アイコン[IconType::三角].Draw({ px + LV(12),py + LV(13) }, true);
			
				//月間の場合、年月
				MIcon::アイコン[IconType::三角].Draw({ px + LV(15),py + LV(13) });
				MIcon::アイコン[IconType::三角].Draw({ px + LV(16),py + LV(13) }, true);
				MFont::BArial中.DrawBold({ px + LV(14) ,py + LV(10) }, Color::White, Color::Black, { "1234年 10月 " }, true);
			}

			void Click(double px, double py)
			{
				//通算or月間の切り替え
				if (py > LV(7) && py < LV(7) + 20)
				{
					if (px > LV(5) - 5 && px < LV(5) + 15)
					{

					}
					if (px > LV(6) - 5 && px < LV(6) + 15)
					{

					}
				}
				//月の切り替え
			}

		};

		class GUI_数値 : public GUI_Object
		{
		public:
			std::string 名前;
			std::string 単位;
			IconType アイコン;
			int id;

			void Set(const char* 名前, const char* 単位, IconType アイコン, int id)
			{
				this->名前 = 名前;
				this->単位 = 単位;
				this->アイコン = アイコン;
				this->id = id;
			}

			void Draw派生(double px, double py)
			{
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				MIcon::アイコン[IconType::資金].Draw({ px + LV(17),py + LV(18) });

				MFont::BArial中.DrawBold({ px + LV(19) ,py + LV(21) }, Color::White, Color::Black, 名前, false);
				MFont::BArial中.DrawBold({ px + LV(20) ,py + LV(21) }, Color::White, Color::Black, { "1234 ", 単位 }, true);
			}
		};

	public:

		GUI_日付 日付;
		GUI_数値 販売数;
		GUI_数値 売上;
		GUI_数値 斬撃製造;//レシピ別製造数
		GUI_数値 打撃製造;
		GUI_数値 刺突製造;
		GUI_数値 射撃製造;
		GUI_数値 魔術製造;
		GUI_数値 神秘製造;
		GUI_数値 STR鎧製造;
		GUI_数値 DEX鎧製造;
		GUI_数値 INT鎧製造;
		GUI_数値 合計製造数;
		GUI_数値 素材獲得;
		GUI_数値 素材消費;
		GUI_数値 人件費;
		GUI_数値 ギルド人数;
		GUI_数値 経営費;
		GUI_数値 利益;
		GUI_数値 資産;
		GUI_数値 地図発見;
		GUI_数値 ボス討伐;
		GUI_数値 撤退回数;
		GUI_数値 依頼達成;
		GUI_数値 名声;


		void init()
		{
			種類 = WindowType::Record;
			名前 = "記録";
			略記 = "記録";
			アイコン = IconType::収支;
			横幅 = 330;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 725;
			縦内部幅 = 725;//120☓ランク数
			スクロール位置 = 0;

			販売数.Set("販売数","個",IconType::資金,0);
			売上.Set("売上", "G", IconType::資金, 1);
			斬撃製造.Set("製造<斬撃>", "個", IconType::資金, 2);
			打撃製造.Set("製造<打撃>", "個", IconType::資金, 3);
			刺突製造.Set("製造<刺突>", "個", IconType::資金, 4);
			射撃製造.Set("製造<射撃>", "個", IconType::資金, 5);
			魔術製造.Set("製造<魔術>", "個", IconType::資金, 6);
			神秘製造.Set("製造<神秘>", "個", IconType::資金, 7);
			STR鎧製造.Set("製造<重防>", "個", IconType::資金, 8);
			DEX鎧製造.Set("製造<軽防>", "個", IconType::資金, 9);
			INT鎧製造.Set("製造<魔防>", "個", IconType::資金, 10);
			合計製造数.Set("製造合計", "個", IconType::資金, 11);
			素材獲得.Set("素材獲得", "個", IconType::資金, 12);
			素材消費.Set("素材消費", "個", IconType::資金, 13);
			人件費.Set("人件費", "G", IconType::資金, 14);
			ギルド人数.Set("ギルド人数", "人", IconType::資金, 15);
			経営費.Set("経営費", "G", IconType::資金, 16);
			利益.Set("利益", "G", IconType::資金, 17);
			資産.Set("資産", "G", IconType::資金, 18);
			地図発見.Set("地図発見", "枚", IconType::資金, 19);
			ボス討伐.Set("ボス討伐", "体", IconType::資金, 20);
			撤退回数.Set("撤退回数", "回", IconType::資金, 21);
			依頼達成.Set("依頼達成", "件", IconType::資金, 22);
			名声.Set("名声", "P", IconType::資金, 23);

			gui_objects.push_back(&日付);
			gui_objects.push_back(&販売数);
			gui_objects.push_back(&売上);
			gui_objects.push_back(&斬撃製造);//レシピ別製造数
			gui_objects.push_back(&打撃製造);
			gui_objects.push_back(&刺突製造);
			gui_objects.push_back(&射撃製造);
			gui_objects.push_back(&魔術製造);
			gui_objects.push_back(&神秘製造);
			gui_objects.push_back(&STR鎧製造);
			gui_objects.push_back(&DEX鎧製造);
			gui_objects.push_back(&INT鎧製造);
			gui_objects.push_back(&合計製造数);
			gui_objects.push_back(&素材獲得);
			gui_objects.push_back(&素材消費);
			gui_objects.push_back(&人件費);
			gui_objects.push_back(&ギルド人数);
			gui_objects.push_back(&経営費);
			gui_objects.push_back(&利益);
			gui_objects.push_back(&資産);
			gui_objects.push_back(&地図発見);
			gui_objects.push_back(&ボス討伐);
			gui_objects.push_back(&撤退回数);
			gui_objects.push_back(&依頼達成);
			gui_objects.push_back(&名声);
		}


		void GUI_Init()
		{
			日付.位置 = { LV(0) , LV(1) , LV(2) , LV(3) };

			販売数.位置 = { LV(4) , LV(5) , LV(7) , LV(8) };
			売上.位置 = { LV(4) , LV(5) + LV(6) * 1, LV(7) , LV(8) };
			斬撃製造.位置 = { LV(4) , LV(5) + LV(6) * 2, LV(7) , LV(8) };
			打撃製造.位置 = { LV(4) , LV(5) + LV(6) * 3, LV(7) , LV(8) };
			刺突製造.位置 = { LV(4) , LV(5) + LV(6) * 4, LV(7) , LV(8) };
			射撃製造.位置 = { LV(4) , LV(5) + LV(6) * 5, LV(7) , LV(8) };
			魔術製造.位置 = { LV(4) , LV(5) + LV(6) * 6, LV(7) , LV(8) };
			神秘製造.位置 = { LV(4) , LV(5) + LV(6) * 7, LV(7) , LV(8) };
			STR鎧製造.位置 = { LV(4) , LV(5) + LV(6) * 8, LV(7) , LV(8) };
			DEX鎧製造.位置 = { LV(4) , LV(5) + LV(6) * 9, LV(7) , LV(8) };
			INT鎧製造.位置 = { LV(4) , LV(5) + LV(6) * 10, LV(7) , LV(8) };
			合計製造数.位置 = { LV(4) , LV(5) + LV(6) * 11, LV(7) , LV(8) };
			素材獲得.位置 = { LV(4) , LV(5) + LV(6) * 12, LV(7) , LV(8) };
			素材消費.位置 = { LV(4) , LV(5) + LV(6) * 13, LV(7) , LV(8) };
			人件費.位置 = { LV(4) , LV(5) + LV(6) * 14, LV(7) , LV(8) };
			ギルド人数.位置 = { LV(4) , LV(5) + LV(6) * 15, LV(7) , LV(8) };
			経営費.位置 = { LV(4) , LV(5) + LV(6) * 16, LV(7) , LV(8) };
			利益.位置 = { LV(4) , LV(5) + LV(6) * 17, LV(7) , LV(8) };
			資産.位置 = { LV(4) , LV(5) + LV(6) * 18, LV(7) , LV(8) };
			地図発見.位置 = { LV(4) , LV(5) + LV(6) * 19, LV(7) , LV(8) };
			ボス討伐.位置 = { LV(4) , LV(5) + LV(6) * 20, LV(7) , LV(8) };
			撤退回数.位置 = { LV(4) , LV(5) + LV(6) * 21, LV(7) , LV(8) };
			依頼達成.位置 = { LV(4) , LV(5) + LV(6) * 22, LV(7) , LV(8) };
			名声.位置 = { LV(4) , LV(5) + LV(6) * 23, LV(7) , LV(8) };
		}

		void 派生Draw()
		{
			GUI_Init();

			for (auto& it : gui_objects)
			{
				it->Draw();
			}
		}

		bool 派生操作()
		{
			for (auto& it : gui_objects)
			{
				it->操作チェック(相対座標.x, 相対座標.y);
			}

			return false;
		}

	};
#undef LV
#undef LV2
#undef LV4
}