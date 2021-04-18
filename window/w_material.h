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
		/*素材と数*/
		class UIMaterial : public UIObject
		{
		public:
			Material* material = nullptr;

			void Draw派生() override
			{
				auto& LB = LData(LMaterial::素材所持数);

				//枠の描画
				DrawUI(UIType::丸フレーム);

				//素材アイコン
				material->image->DrawRotate( GetCenterPos() , 1, 0);

				//ランク
				//MFont::S->DrawBold({ GetCenterPos(LA) }, Design::明字, Design::暗字, { "☆" , material->ランク }, true);
				
				//所持数
				//MFont::S->DrawBold({ GetCenterX() + LB.並べx , GetCenterY() + LB.並べy }, Design::明字, Design::暗字, "x", true);
				//MFont::S->DrawBold({ GetCenterPos(LB) }, Design::明字, Design::暗字, Guild::P->素材数[material->ID], true);

				//MFont::S->DrawRotate({ GetCenterPos(LA) },1,0, Design::暗字, { "☆ " , material->ランク }, true);

				//所持数
				MFont::S->Draw({ GetCenterX() + LB.並べx , GetCenterY() + LB.並べy }, Design::暗字, "x");
				MFont::S->Draw({ GetCenterPos(LB) }, Design::暗字, Guild::P->素材数[material->ID], true);
			}

			void Over() override
			{}
		};

		class UIRank : public UIObject
		{
		public:
			int rank = 0;

			void Draw派生() override
			{
				auto& LA = LData(LMaterial::素材ランク);

				//枠の描画
				DrawUI(UIType::グループ明);
				//ランク
				MFont::M->DrawRotate({ GetCenterPos() },1,0, Design::暗字, { "★" , rank }, true);
			}

			void Over() override
			{}
		};

	public:
		//素材一覧表示６列、高ランクを上に表示
		UIMaterial 素材[CV::上限素材種類];
		UIRank ランク[CV::上限素材ランク];

		void Init()
		{
			Set(WindowType::Material, IconType::素材);
			SetPos(LMaterial::ウィンドウ,false,true,false);

			//●初期化
			for (int i = 0; i < Material::data.size(); i++)
			{
				素材[i].SetUI(LMaterial::素材枠, i);
				素材[i].material = &Material::data[i];
			}
			for (int i = 0; i < CV::上限素材ランク; i++)
			{
				ランク[i].SetUI(LMaterial::素材ランク, i);
				ランク[i].rank = CV::上限素材ランク - i;
			}

			//●登録
			AddItem(素材, Material::data.size());
			AddItem(ランク, CV::上限素材ランク);
		}

		void Update()
		{
			SetPos(LMaterial::ウィンドウ, false, true, false);
		}
	};
}