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
				DrawUI(UIType::平ボタン);

				//遺物アイコン
				Item::accessory_data[itemID].image->DrawRotate({GetCenterX(),GetCenterY()} , 1 , 0);

				//所持数
				auto& itA = Layout::Data(LItem::アイテム数);
				GetFont()->DrawBold({ GetX() + itA.x ,GetY() + itA.y }, Design::data[DesignType::セット1]->明字 , Design::data[DesignType::セット1]->暗字, { "x" , Guild::P->アクセサリー所持数[itemID] },true);

				auto& itB = Layout::Data(LItem::アイテムレア度);
				//レアリティ
				MFont::F[0]->DrawBold({ GetX() + itB.x ,GetY() + itB.y}, Design::data[DesignType::セット1]->明字, Design::data[DesignType::セット1]->暗字, { "☆" , Item::accessory_data[itemID].ランク }, false);
			}

			void Click() override
			{
				//掴む処理

			}

			void Drop() override
			{
				//探索者の遺物と交換

			}
		};

	public:
		UIItem アイテム[CV::最大アクセサリ種類];
		UITextFrame 内枠;

		int 装備数 = 0;
		int 現在タブ = 0;

		void Init()
		{
			Set(WindowType::Item, IconType::装備);
			SetPos(LItem::ウィンドウ,false, true,false);
			
			//●初期化
			int a = -1;
			for (auto& it : アイテム)
			{
				a++;
				it.SetUI(LItem::アイテム);
				it.itemID = a;
			}
			内枠.SetUI("", LItem::内枠);

			//●登録
			AddItem(アイテム,CV::最大アクセサリ種類);
			AddItem(内枠);

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
				if (Guild::P->アクセサリー所持数[a] > 0)
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