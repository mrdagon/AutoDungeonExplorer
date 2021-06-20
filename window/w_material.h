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

				if (material->image == nullptr)
				{
					return;
				}

				//枠の描画
				DrawUI(UIType::丸フレーム);

				//素材アイコン
				material->image->DrawRotate( GetCenterPos() , 1, 0);

				//必要としてる人がいるマーク？ 1,2,3パーティ

				//所持数
				//MFont::S->DrawEdge({ GetCenterX() + LB.並べx , GetCenterY() + LB.並べy }, Design::暗字, "x");
				MFont::M->DrawEdge({ GetCenterPos(LB) }, Design::暗字, Guild::P->素材数[material->種類][material->ランク], true);
			}

			void Over() override
			{}

			void DrawHelp() override
			{
				UIHelp::Material(material);
			}
		};

		class UIRank : public UIObject
		{
		public:
			int rank = 0;

			void Draw派生() override
			{
				auto& LA = LData(LMaterial::素材ランク);
				auto& LB = LData(LMaterial::素材ランク文字);

				//枠の描画
				DrawUI(UIType::丸フレーム);
				//ランク
				MFont::L->DrawRotateEdge({ GetPos( LB ) },1,0, Design::明字, { "★" , rank+1 }, true);
			}

			void Over() override
			{}
		};

	public:
		//素材一覧表示６列、高ランクを上に表示
		EnumArray<UIMaterial[CV::上限素材ランク], CraftType> 素材;
		UIRank ランク[CV::上限素材ランク];

		void Init()
		{
			Set(WindowType::Material, IconType::素材);
			SetPos(LMaterial::ウィンドウ,false,true,false);

			static W_Popup Hウィンドウ;
			Hウィンドウ.Init(WindowType::Help);
			ヘルプウィンドウ = &Hウィンドウ;

			//●初期化

			for (int b = 0, cnt = 0; b < CV::上限素材ランク; b++)
			{
				for (int a = 0; a < CV::素材系統; a++)
				{
					auto ct = CraftType(a);
					素材[ct][b].SetUI(LMaterial::素材枠, cnt);
					素材[ct][b].material = &Material::data[ct][b];
					cnt++;
				}

			}

			for (int i = 0; i < CV::上限素材ランク; i++)
			{
				ランク[i].SetUI(LMaterial::素材ランク, i);
				ランク[i].rank = i;
			}

			//●登録
			item.clear();
			for (int a = 0 ; a < CV::素材系統; a++)
			{
				auto ct = CraftType(a);
				for (int b = 0; b < CV::上限素材ランク; b++)
				{
					AddItem(素材[ct][b]);
				}
			}
			AddItem(ランク, CV::上限素材ランク);
		}

		void Update()
		{
			SetPos(LMaterial::ウィンドウ, false, true, false);
			縦内部幅 = Layout::Data(LMaterial::ウィンドウ).並べy;
		}
	};
}