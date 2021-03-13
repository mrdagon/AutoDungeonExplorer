//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
//Qiitaのこの記事を参考にしています[http://qiita.com/episteme/items/0e3c2ee8a8c03780f01e]
//Qiitaの利用規約9条2項、参照の事

#pragma once
#include <Multimedia/SDX.h>

#ifdef __WINDOWS__
#include <filesystem>
#include <direct.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

namespace SDX
{
	/** ディレクトリの作成、ディレクトリ内のファイルの列挙関数郡.*/
	/**@todo とりあえずWindow版のみ実装*/
	/**バグったので一旦非実装*/

}