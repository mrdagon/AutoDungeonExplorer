/*!
@page howtoMac SDXの導入方法(MacOSX)

SDXFrameworkの使用には\n
「SDXFramework」\n
「Xcode」\n
が必要です。\n
Xcode以外の環境に以外ついては説明しませんが、多分出来るはずです。\n
<HR>
<B>1 Xcodeをインストールする</B>\n
AppStoreからXcodeの最新版をダウンロードしてインストールします。 \n
<HR>
<B>2 SDXFrameworkをダウンロードする</B>\n
下記サイトで最新版を配布しているので、リンク先からダウンロードして下さい\n
<a href="https://sourceforge.jp/projects/dxframework/" target="_blank"><B>OSDN</B></a>\n
解凍すると「SDXFramework」と言うフォルダが出来るので。\n
ホームディレクリ等において下さい。\n
<HR>
<B>3 frameworkのインストール</B>\n
①  Finderを開き、上部メニューの「移動」から「フォルダへ移動」を選び「/System」と入力します。\n
\n
② ライブラリフォルダを開き、Frameworksフォルダを開きます。\n
\n
③ Frameworksフォルダ に  「SDXFramework/MacOSX」の中にある\n
「SDL2.framework」\n
「SDL2_image.framework」\n
「SDL2_mixer.framework」\n
「SDL2_ttf.framework」\n
の４つをドラッグ＆ドロップして追加し、パスワードを入力してインストールします。\n
<HR>
<B>4 新規プロジェクトを作成する</B>\n
Xcodeを起動したら新規プロジェクトを作成します。\n
\n
①上部メニューの「File」の「New」から「Project」を選びます。\n
\n
②Command Line Toolのプロジェクトを作成して下さい。プロジェクト名は好きなように付けて下さい。TypeはC++にします。\n
\n
<HR>
<B>5 プロジェクトの設定</B>\n
①エクスプローラからプロジェクトを選びます\n
\n
②メインウィンドウにプロジェクトの設定が表示されるので、画面の上の方にある「Build Phases」を選択します\n
\n
③Link Binaly With Libraryesをクリックします\n
Add  frameworks & libraries here に  「SDXFramework/MacOSX」の中にある\n
「SDL2.framework」\n
「SDL2_image.framework」\n
「SDL2_mixer.framework」\n
「SDL2_ttf.framework」\n
の４つをドラッグ＆ドロップして追加します。\n
\n
④さらにCopy Filesに上の4つのframeworkをドラッグ＆ドロップして追加します。\n
\n
⑤画面の上の方にある「Build Settings」を選択します\n
左のBasicをAllに変更します。\n
\n
⑥画面をスクロールしてLinking の項目から  Runpath Search Pathsを開き\n
@code
@loader_path/../Frameworks/
@endcode
と入力します。\n
⑦画面をスクロールしてSerch Paths の項目から Header Search Pathsを開き\n
先ほど解凍した「SDXFramework/jni/SDL/include｣フォルダをドラッグ＆ドロップして追加します。\n
以上でプロジェクトの設定は完了です\n
\n
<HR>
<B>6 サンプルソースのビルド</B>\n
画面左側の「Sorce」のフォルダのmain.cppファイルを開きます。\n
main.cppファイルに以下のコードをコピペして、コンパイルして実行して下さい。\n
@code
#include <SDXFramework.h>
#include <SDXafx.h>

using namespace SDX;

int main(int argc, char* argv[])
{
System::Initialise("sample", 640, 480);//ライブラリの初期化

int x = 320;
int y = 240;

while (System::Update())
{
if (Input::pad.Down.hold) y += 5;
if (Input::pad.Up.hold) y -= 5;
if (Input::pad.Right.hold) x += 5;
if (Input::pad.Left.hold) x -= 5;

Drawing::Rect({x-10, y-10, 20, 20}, Color::White, true);
}

System::End();//ライブラリの終了処理

return 0;
}
@endcode
\n
画面に白い□が表示され、カーソルで移動出来れば導入成功です。\n
失敗した場合は、もう一度手順を確認して下さい。\n
よくわからない場合は、掲示板で「新しい話題を始める」をクリックして質問して下さい。\n
<a href="http://sourceforge.jp/projects/dxframework/forums/31378/" target="_blank"><B>SDXFramework：ヘルプフォーラム</B></a>\n
\n
<HR>
<B>7 プリコンパイル済みヘッダーを利用する</B>\n
[参考/Xcode5でプリコンパイル済みヘッダを使う]\n
http://qiita.com/idtkb/items/839cc85200a8e30c76cd
\n
上記の方法で行けるようです。\n
\n
メインの開発環境がXCode以外でとりあえずコンパイル出来れば良い場合は\n
@code
#include "PreCompile.cpp"
@endcode
上のような感じにmain.cppで、他のcppファイルをインクルードすれば良いです。\n
\n
<B>8 画像ファイルを置く場所</B>\n
実行ファイルがある所に置いて下さい\n
\n
<B>9 完成したソフトを配布する</B>\n
.appファイルを作ります。以下のサイトを参考にして下さい。\n
\n
[参考/MacでSDLアプリケーションの作り方]\n
http://d.hatena.ne.jp/o_mega/20080512/1210612958
\n
[参考/Library not loaded エラー？ここを見直そう]\n
http://qiita.com/kakipo/items/3cd87e00bc96bc3888b2
\n
*/