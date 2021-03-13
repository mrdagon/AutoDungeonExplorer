/*!
@page howtoGNULinux SDXの導入方法(GNU/Linux)
Ubuntu14.04での導入方法です。他のディストリビューションでも大体同じになると思います\n
とりあえずターミナルからのコンパイル方法だけ解説します.
<HR>
<B>1.SDL2.0のインストール</B>\n
ターミナルを起動して以下のコマンドを実行する\n
$ sudo apt-get install libsdl2-dev\n
$ sudo apt-get install libsdl2-image-dev\n
$ sudo apt-get install libsdl2-ttf-dev\n
$ sudo apt-get install libsdl2-mixer-de\n
これでSDLの必要なファイルがインストールされます
<HR>
<B>2.SDXの導入</B>\n
SDXFramework/jni/SDL/includeフォルダをインクルードパスに指定するか\n
ターミナルから"sudo nautilus /usr/local"でフォルダを開いて、includeフォルダにコピーするかして下さい\n
<HR>
<B>3.コンパイル</B>\n
clangの最新版や標準ライブラリ等を入手し、c++のコンパイルが可能な状態にします\n
\n
main.cppファイルを作成します。\n
@code
#include <SDXFramework.h>
#include <Multimedia/SDXafx.h>

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
main.cppがあるディレクトリに移動してコマンドを実行\n
"clang++ -std=c++11 -o sdxtest main.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer"\n
(sdxtestの部分を変えると出力されるファイル名が変わります、sudo su する必要がある場合もあります)
sdxtest.aとかが出力されたら成功です.
*/