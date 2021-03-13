//Copyright © 
//[License]GNU Affero General Public License, version 3
//[Contact]
#pragma once
#include <SDXFrameWork.h>
#include "GUI_Factory.h"

namespace NAMESPACE
{
	class CLASSNAME : public SDX::IScene
	{
	public:
		SDX::GUIData guiS;

		CLASSNAME()
		{
			LoadGUI();
			Init();
		}

		//初期化
		void Init() override
		{
			for (auto &it : guiS.dataS)
			{
				it->Init();
			}
		}

		//終了時
		void Final() override
		{
			for (auto &it : guiS.dataS)
			{
				it->Final();
			}
		}

		//更新
		void Update() override
		{
			for (auto &it : guiS.dataS)
			{
				it->Update();
			}
		}

		//描画
		void Draw() override
		{
#ifdef _DEBUG			
			if (Input::key.Return.on){ LoadGUI(); }
#endif
			for (auto &it : guiS.dataS)
			{
				it->Draw();
			}
		}

		void LoadGUI() override
		{
			guiS = SDX::TMXtoGUI( TMX_FILE_NAME , "CLASSNAME", GUI_Factory);
		}
	};
}