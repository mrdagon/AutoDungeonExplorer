//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;

	/*アイテムウィンドウ*/
	class W_Item: public UIWindow
	{
	private:
		class UIItem : public UIObject
		{
		public:
			int itemID;


			void Draw派生() override
			{
				//枠
				Design* dt = Design::Input;
				if (W_Drag::所持装備 != nullptr && W_Drag::所持装備->ID == itemID) { dt = Design::Draging; }
				if (W_Drag::ギルメン装備.メンバー != nullptr) { dt = Design::CanDrop; }

				DrawUI( isOver ? UIType::明ボタン : UIType::平ボタン , dt );

				//遺物アイコン
				Item::accessory_data[itemID].image->DrawRotate({GetCenterX(),GetCenterY()} , 1 , 0);

				//所持数
				auto& itA = Layout::Data(LItem::アイテム数);
				GetFont()->DrawEdge({ GetX() + itA.x ,GetY() + itA.y }, Design::暗字, {  Guild::P->アクセサリー所持数[itemID] },true);

				auto& itB = Layout::Data(LItem::アイテムレア度);
				//レアリティ
				MFont::S->DrawEdge({ GetX() + itB.x ,GetY() + itB.y}, Design::暗字, { "★" , Item::accessory_data[itemID].ランク }, false);
			}

			void Click() override
			{
				//掴む処理
				W_Drag::所持装備 = &Item::accessory_data[itemID];
			}

			bool Drop() override
			{
				//探索者の装備と交換
				if (W_Drag::ギルメン装備.メンバー != nullptr)
				{
					Guild::P->操作_装備在庫(W_Drag::ギルメン装備.メンバー, Item::accessory_data[itemID].ID , W_Drag::ギルメン装備.部位);
				}

				return false;
			}

			void DrawHelp() override
			{
				UIHelp::Item( &Item::accessory_data[itemID], false);
			}
		};

		class UIItem枠 : public UITextFrame
		{

			void Draw派生() override
			{
				UIデザイン = (W_Drag::ギルメン装備.メンバー != nullptr) ? &Design::CanDrop : &Design::Base;

				switch (layout->画像ID)
				{
				case 0:
					DrawUI(UIType::グループ明, *UIデザイン);
					break;
				case 1:
					DrawUI(UIType::グループ中, *UIデザイン);
					break;
				default:
					DrawUI(UIType::グループ暗, *UIデザイン);
					break;
				}
			}
		};

	public:
		UIItem アイテム[CV::上限アクセサリ種類];
		UIItem枠 内枠;

		int 装備数 = 0;
		int 現在タブ = 0;

		void Init()
		{
			Set(WindowType::Item, IconType::装備);
			SetPos(LItem::ウィンドウ,false, true,false);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化
			int a = -1;
			for (auto& it : アイテム)
			{
				a++;
				it.SetUI(LItem::アイテム);
				it.itemID = a;
			}
			内枠.SetUI(LItem::内枠,"");

			//●登録
			item.clear();
			AddItem(アイテム,CV::上限アクセサリ種類);
			AddItem(内枠);

			内枠.dropEvent = [&]()
			{
				if (W_Drag::ギルメン装備.メンバー != nullptr)
				{
					Guild::P->操作_装備在庫(W_Drag::ギルメン装備.メンバー, 0 , W_Drag::ギルメン装備.部位);
				}
				return true;
			};

			Update();
		}

		void Update()
		{
			SetPos(LItem::ウィンドウ, false, true , false);

			//所持してる遺物のみ表示する
			int a = -1;
			int cnt = 0;
			for (auto& it : アイテム)
			{
				a++;
				//0番は装備無しなので表示しない
				if (Guild::P->アクセサリー所持数[a] > 0 && a != 0)
				{
					it.lineID = cnt;
					cnt++;
					it.is表示 = true;
				}
				else {
					it.is表示 = false;
				}
			}

			縦内部幅 = 16 + ((cnt-1) / Layout::Data(LItem::アイテム).改行値 + 1) * Layout::Data(LItem::アイテム).並べy;
			Layout::Data(LItem::内枠).h = 縦内部幅 - Layout::Data(LItem::内枠).y * 2;
		}


	};
}