//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*パーティウィンドウ*/
	class W_Factory: public WindowBox
	{
	private:
		class GUI_メンバーゾーン : public GUI_Object
		{
		public:
			CraftType 部門;
			W_Factory* 親ウィンドウ;

			void Draw派生(double px, double py)
			{
				//todo-完成時のポップアップなどの演出、初製造装備の表示変更

				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 12);
				MSystem::DrawWindow({ px+Lp(23),py+Lp(24) }, Lp(25), Lp(26), Lp(41));
				//作業台
				MSystem::クラフト台[部門].DrawRotate({ px + Lp(15) ,py + Lp(16) }, 2, 0);

				//技術レベルとEXP
				double rate = Guild::P->製造経験[部門] / Guild::P->必要技術経験(部門);
				MSystem::DrawBar({ px + Lp(19),py + Lp(20) }, Lp(21), Lp(22), rate, 1, Color::Blue, Color::White, Color::White, true);
				MFont::BMSize.DrawBold({ px + Lp(17) ,py + Lp(18) }, Color::White, Color::Black, { "Lv" , Guild::P->製造Lv[部門] });

				//製造アイコンと製造進行度合い
				//craft種アイコン
				int id = Guild::P->完成品[部門];
				MSystem::DrawBox({ px + Lp(29) , py + Lp(30) }, Lp(31), Lp(32), Color::White);
				if (id >= 0)
				{
					MIcon::アイテム[Item::data[id].見た目].Draw({ px + Lp(27) , py + Lp(28) });
					MFont::BMSize.DrawBold({ px + Lp(42) , py + Lp(43) }, Color::Yellow, Color::Black, {Item::data[id].Lv},true);
				}
				
				//製造進捗ゲージ
				if (Guild::P->必要製造力[部門] > 0)
				{
					rate = Guild::P->製造進行度[部門] / Guild::P->必要製造力[部門];
				} else {
					rate = 0;
				}

				Color ca, cb;

				if (Guild::P->製造ゲージ色[部門])
				{
					ca.SetColor(255, 128, 128);
					cb.SetColor(64, 64, 255);
				} else {
					cb.SetColor(255, 128, 128);
					ca.SetColor(64, 64, 255);
				}

				MSystem::DrawCircleBar({ px + Lp(29) , py + Lp(30) , Lp(31) , Lp(32) }, rate, ca , cb , 4 , 4);
			}

			void Click(double px, double py)
			{
				//操作無し
			}

			void Drop(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }

				//ギルメン移動して最後に追加
				if (W_Drag::製造メン != nullptr)
				{
					Guild::P->製造移動( W_Drag::製造メン , W_Drag::並びID, nullptr,部門);
					W_Drag::製造メン = nullptr;
				}
			}
		};

		class GUI_製造メンバー : public GUI_Object
		{
		public:
			Crafter* 製造メン;
			W_Factory* 親ウィンドウ;
			int 並びID;

			GUI_製造メンバー(Crafter* 製造メン)
			{
				this->製造メン = 製造メン;
			}

			void Draw派生(double px, double py)
			{
				//todo-製造中はアニメーションさせる
				MSystem::DrawWindow({ px,py }, (int)位置.GetW(), (int)位置.GetH(), 1);
				if (Game::is仕事中 == true)
				{
					//製造中
					int n = Game::アニメーション時間 / 10  %  4 ;
					if (n == 3) { n = 1; }
					n += 6;

					製造メン->Img[0][n]->DrawRotate({ px + Lp(35) , py + Lp(36) }, 2, 0);
				} else {
					//休み中
					製造メン->Img[0][1]->DrawRotate({ px + Lp(35) , py + Lp(36) }, 2, 0);
				}

				MFont::BSSize.DrawBold({ px + Lp(37) ,py + Lp(38) }, Color::White, Color::Black, 製造メン->製造力 , true);
				MIcon::アイコン[IconType::製造力].Draw({ px + Lp(39) , py + Lp(40) });
			}

			void Click(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }
				//ギルメン掴む
				W_Drag::製造メン = 製造メン;
				W_Drag::並びID = 並びID;
				MSound::効果音[SE::ドラッグ].Play();
			}

			void Drop(double px, double py)
			{
				if (Game::is仕事中 == true) { return; }

				//ギルメン入れ替え
				if (W_Drag::製造メン != nullptr)
				{
					Guild::P->製造移動(W_Drag::製造メン, W_Drag::並びID,製造メン,製造メン->配置部門, 並びID);
					W_Drag::製造メン = nullptr;
				}
			}

			void Info派生(Point 座標) override
			{
				ヘルプ横幅 = CSV::I[11][0];
				ヘルプ縦幅 = CSV::I[11][1];
				//InfoHunter(製造メン, 座標);
			}
		};

	public:
		//生産割り当て、武器６系統、防具３系統
		EnumArray<GUI_メンバーゾーン,CraftType> メンバーゾーン;//製造メンバーの表示領域

		EnumArray < std::vector<GUI_製造メンバー>, CraftType> 製造メンバー;

		void Init()
		{
			gui_objects.reserve(256);

			種類 = WindowType::Factory;
			名前 = TX::Window_名前[種類];
			略記 = TX::Window_略記[種類];
			SetHelp(TX::Window_ヘルプ[種類]);

			アイコン = IconType::製造;
			横幅 = 344;
			縦幅 = 125;
			最小縦 = 125;
			最大縦 = 600;
			縦内部幅 = 600;//120☓ランク数
			スクロール位置 = 0;;

			for (int a = 0; a < (int)CraftType::COUNT; a++)
			{
				メンバーゾーン[CraftType(a)].部門 = CraftType(a);
				メンバーゾーン[CraftType(a)].SetHelp(TX::Factory_部門説明[CraftType(a)]);
			}
		}

		void GUI_Update()
		{
			//オブジェクト初期化
			for (auto& it : 製造メンバー)
			{
				it.clear();
			}

			gui_objects.clear();

			for (auto& it : メンバーゾーン)
			{
				it.親ウィンドウ = this;
			}

			for (int b = 0; b < (int)CraftType::COUNT;b++)
			{
				CraftType t = (CraftType)b;

				for (int a = 0; a < (int)Guild::P->製造メンバー[t].size(); a++)
				{
					if (Guild::P->製造メンバー[t][a] == nullptr) { break; }

					製造メンバー[t].emplace_back(Guild::P->製造メンバー[t][a]);
					製造メンバー[t][a].並びID = a;
					製造メンバー[t][a].親ウィンドウ = this;
				}
			}

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				CraftType t = (CraftType)b;

				for (int a = 0; a < (int)製造メンバー[t].size(); a++)
				{
					gui_objects.push_back(&製造メンバー[t][a]);
				}
			}

			gui_objects.push_back(&メンバーゾーン[CraftType::鍛造]);
			gui_objects.push_back(&メンバーゾーン[CraftType::裁縫]);
			gui_objects.push_back(&メンバーゾーン[CraftType::魔術]);
			gui_objects.push_back(&メンバーゾーン[CraftType::木工]);

			SetCSVPage(13);

			//座標初期化
			int n = 0;
			int y = 0;
			const int 列数 = 6;
			int 段数 = 0;

			横幅 = Lp(0);

			for (int b = 0; b < (int)CraftType::COUNT; b++)
			{
				CraftType t = CraftType(b);
				段数 = (int)製造メンバー[t].size() / 列数 + 1;
				if (段数 < 2) { 段数 = 2; }

				//人数に応じてメンバーゾーンのサイズは変動
				メンバーゾーン[t].位置 = { Lp(1) , Lp(2)+y , Lp(0) - Lp(3) , Lp(4) + 段数 * Lp(5) };
				
				for (int a = 0; a < (int)製造メンバー[t].size(); a++)
				{
					製造メンバー[t][a].位置 = { Lp(1) + Lp(8) + Lp(9) * (a % 列数) , Lp(2) + Lp(10) + Lp(11) * (a / 列数) + y ,Lp(12),Lp(13) };
				}

				y += Lp(4) + Lp(7) + 段数 * Lp(6);
			}

			縦内部幅 = y + Lp(14);
		}
	};
}