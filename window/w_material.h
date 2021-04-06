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
		UIMaterial 素材[CV::上限素材種類];
		UITextFrame 内枠;

		void Init()
		{
			Set(WindowType::Material, IconType::素材);
			SetPos(LMaterial::ウィンドウ,false,true,false);

			//●初期化
			for (int i = 0; i < Material::data.size(); i++)
			{
				素材[i].SetUI(LMaterial::素材枠, i);
				素材[i].素材種 = &Material::data[i];
			}
			内枠.SetUI("", LMaterial::内枠);

			//●登録
			AddItem(素材, Material::data.size());
			AddItem(内枠);
		}

		void Update()
		{
			SetPos(LMaterial::ウィンドウ, false, true, false);
		}
	};
}