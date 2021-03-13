/*!
@page ReleaseNote 更新履歴
各バージョンの主な更新履歴です \n
今後の変更予定はOSDNのチケットやTodo一覧を参照して下さい\n
\n
OSDNで配布しているファイルはデータを全て含む、安定版です\n
開発中のバージョンを入手したい場合や、差分ファイルだけ欲しい場合は\n
以下のページ右下の"Download ZIP"からソースをダウンロードし\n
https://github.com/mrdagon/SDXFramework
\n
SDXFramework>jni>SDL>includeに解凍したファイルを上書きして下さい\n
\n
<HR>
<B>ver 0.13</B>\n
[破壊的変更]\n
SDXafx.hのファイルパスを変更\n
IModelの設計をGetShapeとGetSpriteをオーバーライドする形に変更\n
Font::DrawRotateで一行分上に表示されている等の不具合を修正\n
Fontクラスで登録されていない文字を表示する際に空白が入る用に修正\n
Font::GetCsvToStringで改行コードが残る不具合を修正\n
VisualStudioでReleaseビルドする時はMTにするように変更\n
[細かな修正等]\n
OMIT_SDL2_TTFマクロでttf関連の機能を無効に出来るように変更\n
Fontの内部構造をmapからunorderd_mapに変更\n
削除した実装はOldフォルダに移す事に\n
UtilityにAny.hとPool.hを追加、デフォルトでインクルードはしていない\n
Sample関数を名前空間でくくってたのを解除\n
VisualStudio2015に対応したlibファイルを追加、プラットフォームツールセットをv140でも動作するように\n
Timeに日付を文字列で返す関数GetDateStringを追加\n
Systemにプラットフォームの種類を取得する関数と、タブレットかどうかを取得する関数を追加。\n
LoadBMPFont関数を非同期読み込み対応\n
Drawing関数で半透明指定が無効になっていたバグを修正\n
Font::MakeBmpFontで出力されるファイル名に文字サイズが入るように修正\n
外部エディタとしてTiledとの連携機能を仮実装\n
\n
<B>ver 0.12</B>\n
Window::SetLogicalSize関数を追加\n
ウィンドウサイズを倍にして、表示倍率も倍にするといった事が簡単に出来るようになります\n
Android関連の不具合を修正。Androidの導入方法を修正。\n
BMPフォントを出力する関数と、読み込む関数を追加\n
ドキュメントを色々修正\n
\n
<B>ver 0.11</B>\n
SoundとMusicに全体の音量を変更する関数を追加\n
\n
<B>ver 0.10</B>\n
[大きめの破壊的変更]\n
BmpFontをFontに統合して廃止\n
Cameraクラスを再設計\n
AnimeクラスをFilmクラスに名称変更、Anime::PlayerをAnimeに名称変更し設計見直し\n
引数が座標X、座標Yとかになっている物をconst Point&に変更\n
引数が座標X、座標Y、幅、高さとかになっている物をconst Rect&に変更\n
DrawExtendの引数をPoint2つからRectに変更\n
Directorクラスのバグを修正\n
IFontクラスの反転フラグの引数の位置を変更\n
\n
[細かい破壊的変更]\n
DXLib版と分離したので～Handleのusing宣言を削除\n
NULL_HANDLEマクロを削除\n
Font初期化時の引数を変更\n
Waitクラスを削除してSystemに統合\n
Window::SetFullScreenをWindow::SetFullscreenに変更\n
SoundとMusicのPlayTypeを削除、及び引数をPlayTypeからboolに変更\n
必ずtrueを返す関数の戻り値をboolからvoidに変更\n
Load済みのImageやSound等に対してLoadした場合失敗するように統一\n
Shape::Draw関数の引数を削減\n
MOTIONの仕様を変更\n
\n
[新機能追加]\n
Fontクラスを改善、機能強化\n
Screenクラスの機能をRendererクラスに分割して再設計＆機能強化\n
Windowクラスの機能をSubWindowクラスに分割して再設計＆機能強化\n
Mouse::SetVisibleを実装\n
Soundクラスにエフェクト系関数追加\n
ThreadLoadクラスをLoadingクラスに名称変更して実装完了\n
Mouse,Joypad,Keyboardで列挙子からキーの状態を取る機能を追加\n
Drawingの円描画と正三角形描画を実装\n
\n
[その他の変更]\n
一部Get関数のconst漏れを修正\n
ヘッダーファイルの分割粒度やファイル名を変更\n
Sampleコードの分割粒度やファイル名を変更\n
非実装のJoypadの振動関数を削除\n
非実装のScreen::Copyを削除\n
Soundクラスの非実装関数を一部削除\n
ImageからisScreen,isAlpha,isTransフラグ関係を削除\n
BlendBltとFilterBltをそれぞれBlend,Filterに統合(ただし未実装)\n
Copyコンストラクタを色々禁止\n
GNU/Linuxのコンパイル方法を修正\n
Macで配布する場合の注意事項を追記\n
Sample実行用の画像ファイル等を配布開始\n
\n
<B>ver 0.09</B>\n
ライセンスをAGPL Ver3に変更\n
DXLIB版を開発終了、以降はSDL2.0版の開発に注力して行きます。\n
DXLIB版とSDL2.0版の互換性の維持を終了\n
\n
int 座標X,int 座標Yとなっている関数をconst Point &座標に変更\n
int X座標,int Y座標,int 高さ,int 幅はconst Rect &領域に変更\n
非実装だったZマスク系関数を削除\n
テキスト入力系の関数を一旦削除\n
Rectの座標を左上以外に出来るように変更\n
ユーティリティーにEnumArrayを追加\n
GNU/Linuxに対応\n
MacOSX 10.6に対応\n
<HR>
<B>ver 0.08</B>\n
細かいバグを修正\n
<HR>
<B>ver 0.07</B>\n
Android対応強化\n
Fileクラスを修正、Multimediaフォルダに移動\n
ModelMoveクラスの関数名を全て英語に変更\n
四角同士の当たり判定の無駄な処理を消して高速化\n
Touchクラスを追加\n
Sample.hをSample/Sample.hに変更\n
可変文字列の引数を全てVariadicStreamに変更\n
ドキュメントに移植に関するページを追加\n
大体実装が終わったので、SDL版とDXLIB版のソースを分割、#define SDLや#define DXLIBを不要に\n
<HR>
<B>ver 0.06</B>\n
iOSとandroidに暫定対応\n
\n
SDL版のImage::DrawRotateのバグを修正\n
<HR>
<B>ver 0.051</B>\n
SystemFont名前空間にデフォルトフォントを追加\n
DrawingにSetDefaultFont関数を追加\n
\n
MacでもFileクラスのファイル指定が常に相対パスになるように修正\n
\n
WindowsでSDLを使う場合、#define SDL_WINとするように変更\n
\n
サンプルゲームのバグを大幅に修正\n
\n
Fontの回転描画と、フォントからImageを作成する関数を追加\n
\n
SDLに円等の図形描画機能を実装\n
<B>ver 0.05</B>\n
MacOSX対応\n
\n
可変数引数を使用していた関数を全てVariadicStreamを利用するように変更\n
\n
Fileクラスのバグを修正\n
\n
SpFontの仕様を変更\n
\n
Drawing::Rect\n
Screen::SaveBmp\n
Screen::SetArea\n
の3つを座標指定から大きさを指定するように変更
\n
AsyncroLoad を Loading に 改名\n
\n
線分と円の当たり判定のバグを修正\n
\n
コメントや引数名を修正\n
\n
UpDateとなっていた関数をUpdateに変更\n
\n
<BR>
<B>ver 0.04</B>\n
安定版として公開開始\n
*/