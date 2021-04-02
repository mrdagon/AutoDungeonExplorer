//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;
	/*素材とアイテムウィンドウ*/
	class W_Material: public UIWindow
	{
	private:
		/*素材と数とランク*/
		class UIMaterial : public UIObject
		{
		public:
			Material* 素材種 = nullptr;

			void Draw派生() override
			{
				if (素材種 == nullptr) { return; }

				//枠の描画
				DrawUI(UIType::平ボタン);

				//素材アイコン
				//素材種->image->DrawRotate({ px + Lp(6), py + Lp(7) }, 1, 0);

				//Lv
				//MFont::S->DrawBold({ px + Lp(10) ,py + Lp(11) }, Color::White, Color::Black, { "Lv" , 素材種->ランク }, true);
				
				//所持数
				//MFont::S->DrawBold({ px + Lp(12) ,py + Lp(13) }, Color::White, Color::Black, "x", true);
				//MFont::M->DrawBold({ px + Lp(14)  ,py + Lp(15) }, Color::White, Color::Black, Guild::P->素材数[素材種->ID], true);

			}

			void Over() override
			{}
		};

	public:
		//素材一覧表示６列、高ランクを上に表示

		void Init()
		{
			Set(WindowType::Material, IconType::素材);
			SetPos(LMaterial::ウィンドウ,false,true,false);

			/*
			横幅 = 250;
			縦幅 = 240;
			最小縦 = 240;
			最大縦 = 800;
			縦内部幅 = 480;//120☓ランク数
			スクロール位置 = 0;
			*/

		}

		void Update()
		{
			SetPos(LMaterial::ウィンドウ, false, true, false);
		}
	};
}