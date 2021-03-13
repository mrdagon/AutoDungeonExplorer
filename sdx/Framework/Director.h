//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Framework/IScene.h>

namespace SDX
{
    /** シーンを管理するクラス.*/
    /** \include Director.h*/
    class Director
    {
    private:
        MONO_STATE(Director)

        static std::vector<std::shared_ptr<IScene>>& Single()
        {
            static std::vector<std::shared_ptr<IScene>> instance;
            return instance;
        }

        /** 消滅したSceneを片付ける.*/
        static void Remove()
        {
            auto it = Single().begin();

            while (it != Single().end())
            {
                if ((*it)->isEnd)
                {
                    it = Single().erase(it);
                    if (Single().size() == 0){ break; }
                    continue;
                }
                it++;
            }
        }

    public:
        /** 実行開始.*/
        static void Run()
        {
            Time::ResetFPS();

            while (System::Update(IsDraw()))
            {
                if (Single().size() == 0){ break; }
                Single().back()->Update();
                if (IsDraw()){ Single().back()->Draw(); }

                Time::CheckFPS();

                Remove();
            }
        }

        /** Sceneを追加しスタックに積む.*/
        /** 追加したシーンがアクティブになる\n*/
        /**	既に追加されているシーンの場合アクティブにするだけ*/
        static void AddScene(std::shared_ptr<IScene> 追加するシーン)
        {
            bool isExist = false;

            //既に存在する場合、削除してから追加
            auto it = Single().begin();
            while (it != Single().end())
            {
                if ((*it) == 追加するシーン)
                {
                    isExist = true;
                    Single().erase(it);
                    break;
                }
                ++it;
            }

            Single().push_back(追加するシーン);
        }

        /** 上からインデックス番目のシーンを取得.*/
        /** 0で現在アクティブなシーン、1で一つ前*/
        static std::shared_ptr<IScene> GetScene(int インデックス)
        {
            return Single()[Single().size() - インデックス - 1];
        }

        /** 上からインデックス番目のシーンをアクティブにする.*/
        /** 0で現在アクティブなシーン*/
        static bool ActiveScene(int インデックス)
        {
            int no = (int)Single().size() - インデックス - 1;
            if (no < 0) { return false; }

            AddScene(Single()[no]);

            return true;
        }

        /** 描画更新フラグを設定.*/
        static bool& IsDraw()
        {
            static bool isDraw = true;
            return isDraw;
        }
  
    };
}
