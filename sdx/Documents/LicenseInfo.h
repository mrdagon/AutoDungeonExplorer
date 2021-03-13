/*!
@page LicenseInfo ライセンスについて
SDXFrameworkのライセンスはAGPL Ver3です。<BR>
http://www.gnu.org/licenses/agpl-3.0.html
\n
マニュアルのソースもライセンスもAGPL Ver3です\n
<HR>
英語のライセンス文を読むのが辛い人向けの概略です。\n
細かい部分は省略しているので、気になる方はライセンス文を読んでください\n
\n
SDXFrameworkを利用して作成したソフトウェアを配布する場合以下を守る必要があります。\n
\n
[ソースコードの公開]\n
　ソフトを所持している人がソースコードを入手出来るようにする必要があります\n
ソフトと一緒に配布する、Github等で公開する、同梱はせず問い合わせが来たらメールで送る等、公開方法はいくつかあります。\n
バージョンアップ前のコードを要求されるとややこしいとかあるので、Githubで公開したり、ソフトと一緒に配布する方が楽ではあります。\n
\n
SDXFrameworkの部分のコードは一緒に配布するか、あるいはどこで入手可能かを示す必要があります。\n
独自の修正をしていたり、Githubで公開している開発途中のバージョンを使っている場合は、一緒に配布して貰った方が良いです。\n
\n
[同じライセンスの適用]\n
　ソースコードは全体としてAGPL Ver3を適用する必要があります\n
(新規に書いた部分はAGPL Ver3と互換性があれば、別のライセンスでも構いません)\n
\n
[再配布の許可]\n
　配布したソフトウェアの実行ファイルは再配布を許可する必要があります\n
\n
[ソースコード以外]\n
　ソフトと一緒に配布する画像、音声、テキストファイル等は好きなライセンスを設定出来ます\n
再配布可能にしてもしなくてもかまいません。\n
\n
[特許]\n
　公開したソフトウェアに利用されている特許の権利をあなたが所持している場合、派生した著作物等に対してその特許を行使できません\n
\n
[ライセンス文と著作権表記]\n
　License.txtをソフトウェアと一緒に配布する必要があります\n
以下の2行の表記をソフトウェアと一緒に配布するドキュメント、あるいはソフトウェア内のクレジットで明示して下さい\n
\n
<B>ライセンス表記</B><BR>
Copyright © 2014~ SDXFramework\n
http://sourceforge.jp/projects/dxframework/simple/
<BR>
<B>内部で使っているライブラリのライセンス</B><BR>
SDL2.0等が利用しているライブラリのライセンスにも従う必要があります\n
該当するdll等を使用していない場合、それらのライセンスを表記する必要はありません\n
使用する場合は各種ライセンス表記が必要です\n
各ライセンス文はLicenceフォルダにコピーが置いてあります\n
\n
SDL2\n
SDL2_image\n
SDL2_mixer\n
SDL2_ttf\n
zlib\n
はzlibライセンスなので、無改変の場合特にライセンス表記は不要です。\n
<table>
<caption>ライブラリ一覧</caption>
<tr style="background:#ccccff"> <td>SDL_image</td>				<td> </td></tr>
<tr>							<td>libjpeg			<td>独自ライセンス。使用している事を表記する必要がある。</td></tr>
<tr>							<td>libpng			<td>libpngライセンス。表記は任意</td></tr>
<tr>							<td>libtiff			<td>BSDライクライセンス。著作権者表記、ライセンス文のコピーが必要、著作者名を勝手に宣伝使ってはいけない</td></tr>
<tr>							<td>libwebp			<td>3条項BSDライセンス。著作権者表記、ライセンス文のコピーが必要、著作者名を勝手に宣伝使ってはいけない</td></tr>
<tr style="background:#ccccff"> <td>SDL_mixer</td><td> </td></tr>
<tr>							<td>libFLAC				<td>3条項BSDライセンス。著作権者表記、ライセンス文のコピーが必要、著作者名を勝手に宣伝使ってはいけない</td></tr>
<tr>							<td>libmikmod				<td>LGPL ver2。著作権者表記、ライセンス文のコピー等が必要</td></tr>
<tr>							<td>libmodplug				<td>パブリックドメイン。著作権表記等は任意</td></tr>
<tr>							<td>libogg/libvorbis		<td>3条項BSDライセンス。著作権者表記、ライセンス文のコピーが必要、著作者名を勝手に宣伝使ってはいけない</td></tr>
<tr>							<td>smpeg2				<td>LGPL ver2。著作権者表記、ライセンス文のコピー等が必要</td></tr>
<tr style="background:#ccccff"> <td>SDL_ttf</td><td> </td></tr>
<tr>							<td>libfreetype	<td>FreeType License。著作権者表記、ライセンス文のコピーが必要</td></tr>
</table>
\n
例えば全ての機能を利用する場合は、\n
SDXFramework Copyright © 2014~ \n
http://sourceforge.jp/projects/dxframework/simple/
\n
libjpeg copyright (C) 1991-2012, Thomas G. Lane, Guido Vollbeding.All rights reserved.\n
libtiff Copyright (c) 1988-1997 Sam Leffler.All rights reserved.\n
libtiff Copyright (c) 1991-1997 Silicon Graphics, Inc.All rights reserved.\n
libwebp Copyright (c) 2010, Google Inc.All rights reserved.\n
libFLAC Copyright (C) 2000,2001,2002,2003,2004,2005,2006,2007  Josh Coalson.All rights reserved.\n
libmikmod Copyright (c) Mikmod.All rights reserved.\n
libogg Copyright (c) 2002-2008 Xiph.org Foundation.All rights reserved.\n
smpeg Copyright (c)Loki Software.All rights reserved.\n
libfreetype  Copyright 1996-2002, 2006 by David Turner, Robert Wilhelm, and Werner Lemberg.All rights reserved.\n
\n
以上の内容をreadmeやゲーム内のクレジット等の分かりやすい所に明記し。\n
Licenceフォルダのテキストファイルを一緒に配布する等して下さい\n
<HR>
SDXFrameworkには以下のライブラリを利用しています\n
Android用の設定ファイルを一部変更しています\n
\n
<a href="http://www.libsdl.org/index.php" target="_blank"><B>SDL</B></a>\n
<a href="http://www.libsdl.org/projects/SDL_image/" target="_blank"><B>SDL_image</B></a>\n
<a href="http://www.libsdl.org/projects/SDL_mixer/" target="_blank"><B>SDL_mixer</B></a>\n
<a href="http://www.libsdl.org/projects/SDL_ttf/" target="_blank"><B>SDL_ttf</B></a>\n
\n
libjpeg copyright (C) 1991-2012, Thomas G. Lane, Guido Vollbeding.All rights reserved.\n
\n
libtiff Copyright (c) 1988-1997 Sam Leffler.All rights reserved.\n
libtiff Copyright (c) 1991-1997 Silicon Graphics, Inc.All rights reserved.\n
\n
libwebp Copyright (c) 2010, Google Inc.All rights reserved.\n
libFLAC Copyright (C) 2000,2001,2002,2003,2004,2005,2006,2007  Josh Coalson.All rights reserved.\n
libmikmod Copyright (c) Mikmod.All rights reserved.\n
libogg Copyright (c) 2002-2008 Xiph.org Foundation.All rights reserved.\n
smpeg Copyright (c)Loki Software.All rights reserved.\n
libfreetype  Copyright 1996-2002, 2006 by David Turner, Robert Wilhelm, and Werner Lemberg.All rights reserved.\n
\n
*/