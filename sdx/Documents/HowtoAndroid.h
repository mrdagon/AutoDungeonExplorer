/*!
@page howtoAndroid SDXの導入方法(android)
androidの環境構築は他のOSに比べるとややこしいです\n
実機デバッグの設定方法は機種により違うので各自で調べて下さい\n
clangにしか対応していないのでandroidNDKの64bit版だと使えないと思います\n
動作確認がちょっと中途半端で、不具合等多いかもしれません\n
winでeclipseを使う場合のみ動作確認済みです\n
\n
以下も参考にして下さい。\n
@ref PortaBility\n
<HR>
<B>1.android-sdkの導入</B>\n
以下のサイトを参考にしてjavaやeclipseの環境を構築して下さい\n
http://techfun.cc/techinf/setup/android/ \n
<HR>
<B>2.android-ndkの導入</B>\n
以下のサイトを参考にしてandroid-ndkを導入して下さい\n
http://dench.flatlib.jp/opengl/androidsdk \n
<HR>
<B>3.SDXの導入とプロジェクト作成</B>\n
eclipseを起動しworkspaceフォルダを作成、SDXFrameworkフォルダをコピーします。\n
※ここまではライブラリ導入時、一度だけ行えば良いです\n
<HR>
<B>4.新規プロジェクトの作成</B>\n
eclipseを起動し、ファイルメニューからインポートを選び、Existing Android Code Into Workspaceを選びます\n
ルート・ディレクトリにworkspace内のSDXFrameworkフォルダを選択します\n
プロジェクトをワークスペースにコピーにチェックを入れ、新規プロジェクト名を設定し完了を押します。\n
少し待つとコピーされたプロジェクトが作成されます\n
@code
workspace/作成したプロジェクト名/jni/src
@endcode
にmain.cppを置いて下さい\n
@code
workspace/プロジェクト名/assets
@endcode
の中に画像ファイル等のリソースを置いてください。
画像等のファイル名は英小文字と数字、アンダーバーのみにして下さい。\n
<HR>
<B>5.日本語の識別子を含む場合</B>\n
※ この項目は必須ではありません\n
関数名やクラス名にアルファベット、数字、アンダーバー以外を使用している場合、アセンブリエラーが出ます。\n
そういった場合、配布している"UTFConvert.exe"を使って識別子名を変換して下さい。\n
<HR>
<B>6.端末の向きの変更</B>\n
※ この項目は必須ではありません\n
プロジェクトフォルダ直下の｢AndroidManifest.xml｣を開きます。\n
@code
<activity android:screenOrientation="landscape">
@endcode
のままなら横向き固定\n
@code
<activity android:screenOrientation="portrait">
@endcode
に変更すると縦固定になります。\n
現在画面の回転には対応していません\n
[参考]\n
http://pentan.info/android/screen_orientation.html
\n
<HR>
<B>7.配布パッケージ名の変更等</B>\n
SDXFrameworkフォルダ直下の｢AndroidManifest.xml｣を開きます。\n
@code
<activity android:name="SDLActivity"
@endcode
上の行の"SDLActivity"の部分を変更します、漢字やひらがなを含む名前には出来ません\n
\n
アイコンを変更する場合は、res>drawable～フォルダ内の各画像を差し替えて下さい\n
\n
[参考]\n
http://ggkuron.hatenablog.com/entry/2013/08/02/073940
\n
<HR>
<B>8.コンパイルと実行</B>\n
アクセサリや、スタートボタン右クリック(Win8)でコマンドプロンプトを開き
@code
cd workspace/プロジェクト名
@endcode
で作成したプロジェクトのフォルダに移動\n
@code
ndk-build
@endcode
のコマンドでコンパイルを行います\n
\n
eclipseを起動し、ソフトを実行します\n
シミュレータの場合、OpenGL絡みのでエラーが出る場合があります\n
その場合は実機でデバッグして下さい\n
\n
端末側で更新されていない場合がありますが、その場合はもう一度ソフトを実行して下さい\n
<HR>
<B>9.eclipse上でのndk-build</B>\n
[調査中]\n
プロジェクト>プロパティー>C/C++ ビルド>ツールチェーンエディターの\n
現在のビルダーを AndroidBuilderに変更する？\n
<HR>
<B>10.配布方法</B>\n
binフォルダに.apkファイルが作成されるので、それを配布して下さい。\n
配布方法は色々あるので、GooglePlayへの登録方法やらkindlestoreへの登録方法等をネットで調べて下さい。\n
\n
*/
