//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
namespace SDX
{
	/** シーンのインターフェース.*/
	/** \include Director.h*/
	class IScene
	{
	public:
		bool isEnd = false;//!< 消滅フラグ

		virtual ~IScene() = default;

		/**更新処理.*/
		virtual void Update() = 0;

		/**描画処理.*/
		virtual void Draw() = 0;

		/**初期化処理.*/
		virtual void Init(){}

		/**終了時の処理.*/
		virtual void Final(){}

		/**GUIの読み込み処理.*/
		virtual void LoadGUI(){}
	};
}