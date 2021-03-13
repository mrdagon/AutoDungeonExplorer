/*
@page HowToTiled Tiled連携機能
GUIエディタとしてTiledを利用する方法の解説です。\n
Tiledは以下から入手出来ます。\n
http://www.mapeditor.org/
\n
<HR>
Tiledで作成したtmxファイルをコードに変換するソフト「TiledConv.exe」の解説です\n
\n
TiledConv.exeを使うとtmxファイルからソースコードが生成出来ます。\n
\n
<B>1.tmxファイルの編集</B>\n
まずテンプレートに従って、tmxファイルを編集します。\n
説明を読むだけだと意味が分からないと思いますが、実際に試すとそんなに難しくないと思います。\n
『SDXFramework/Sample/template.tmx』を見ながら読むと良いです。\n
\n
<B>1.1.オブジェクトクラスの定義<B>\n
TEMPLATEという名前のオブジェクト･レイヤーを作成します。\n
TEMPLATEレイヤーに配置された四角形のパラメータによって、オブジェクトクラスのコードが生成されます\n
\n
名前にはクラス名を入れます。
種類には画像オブジェクトの場合Image、それ以外の場合Rectと入力します。\n
場所、大きさ、回転は出力するコードには影響を与えません。\n
\n
カスタムプロパティを追加する事で、メンバー変数とコードの追加が行えます。\n
メンバー変数を追加したい場合は、プロパティ名に変数名、プロパティの値に型名を入れて下さい。\n
コードを追加したい場合は、プロパティ名に関数名(先頭に~を付ける)、プロパティの値に出力コードを入力して下さい。\n
出力コード内にメンバー変数を入れたい場合は@変数名として下さい。\n
\n
<B>1.2.四角形の配置<B>\n
オブジェクト･レイヤーを追加し、四角形を配置します\n
\n
名前にはオブジェクトの識別名を入れます。\n
種類には先ほどTEMPLATEレイヤーでRectに定義したオブジェクトクラス名を入れます。\n
画面上で表示したい位置に配置して下さい。\n
回転には現在対応していないので、回転はさせないで下さい\n
\n
カスタムプロパティにはオブジェクトクラスと同じプロパティを追加し、プロパティ値の部分に値を入れて下さい。\n
\n
<B>1.3.画像の配置<B>\n
タイルセットを追加します。\n
タイルセットに追加する画像とtmxファイルの位置関係はゲームの実行ファイルと画像ファイルの位置関係と同じにして下さい。\n
同じレイヤーにタイルを配置します。\n
\n
名前にはオブジェクトの識別名を入れます。\n
種類には先ほどTEMPLATEレイヤーでImageに定義したオブジェクトクラス名を入れます、省略した場合Imageと入力したのと同じになります。\n
画面上で表示したい位置に配置して下さい。\n
回転には現在対応していないので、回転はさせないで下さい\n
\n
カスタムプロパティにはオブジェクトクラスと同じプロパティを追加し、プロパティ値の部分に値を入れて下さい。\n
\n
保存すると準備は完了です\n
\n
<B>2.コードの生成</B>\n
tmxファイルから、オブジェクトクラス、シーンクラス、オブジェクトの列挙型のコードを生成します。\n
\n
tmxファイルがあるフォルダに｢ClassTemplate.h｣｢SceneTemplate.h｣｢EnumTemplate.h｣を置きます。\n
(これらはSDXFramework/Tiledに置いてあります。)\n
その後tmxファイルをTiledConv.exeにドロップすると、コードが生成されます。\n
\n
<B>3.生成されたコードの利用</B>\n
SDXのプロジェクトを作成し、生成したコードをmain.cppと同じ場所に置き、以下のようなコードを実行して下さい。\n
\n
@code

#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>

SDX::ImagePack imageS;
SDX::IFrame* frameS[10];
SDX::IFont* fontS[10];

#include "TestScene.h"

int main(int argc, char* argv[])
{
using namespace SDX;
//事前にtemplate.tmxをコードに変換し
//TestScene等のコードを作成しておく事
System::Initialise("test", 640, 480);

imageS.LoadTmx("template.tmx");
fontS[0] = new Font(SystemFont::Gothic, 10);
auto frame0 = ImagePack("data/pipo-WindowBase001.png", 9, 3, 3);
auto frame1 = ImagePack("data/pipo-WindowBase004.png", 9, 3, 3);
frameS[0] = new BmpFrame(&frame0);
frameS[1] = new BmpFrame(&frame1);

TestScene scene;

while (System::Update())
{
scene.Draw();
}

return 0;
}

@endcode
\n
成功すると、\n
\n
<B>4.実行中にtmxファイルを読み込む</B>\n
サンプルファイルそのままだと実行中にtmxファイルを編集、その後Enterキーを押すとオブジェクトの位置が更新されるようになっています。\n
どうなっているかは"TestScene.h"のコードを読むと大体分かると思います\n
\n
<B>5.コードの再更新</B>\n
生成されるコードとテンプレ\n
\n
*/