/*!
@page ClassGroup 機能別、クラス一覧
<table>
<caption>クラス一覧</caption>
<tr style="background:#8888ff"> <th>マルチメディア</th> <th>プラットフォーム依存の処理を肩代わりするクラス</th></tr>
<tr style="background:#ccccff"> <td>システムの処理</td><td> </td></tr>
<tr>							<td>SDX::System</td>		<td>ライブラリの初期化やシステム的な処理を行う関数群</td></tr>
<tr>							<td>SDX::Window</td>		<td>アクティブウィンドウを扱うクラス</td></tr>
<tr>							<td>SDX::SubWindow</td>		<td>ウィンドウの生成と管理クラス</td></tr>
<tr>							<td>SDX::Screen				<td>アクティブな描画先を扱うクラス</td></tr>
<tr>							<td>SDX::Renderer			<td>描画領域の管理クラス</td></tr>
<tr style="background:#ccccff"> <td>描画</td>				<td> </td></tr>
<tr>							<td>SDX::Drawing			<td>リソースを読み込まずに描画を行う関数群</td></tr>
<tr>							<td>SDX::IDrawable			<td>描画可能なクラスのインターフェース</td></tr>
<tr>							<td>SDX::Image				<td>画像データを表すクラス</td></tr>
<tr>							<td>SDX::Font				<td>フォントデータを表すクラス</td></tr>
<tr>							<td>SDX::Color				<td>色を表すクラス</td></tr>
<tr>							<td>SDX::Loading			<td>リソースの非同期読み込み設定関数群</td></tr>
<tr style="background:#ccccff"> <td>画像処理[未実装]</td><td> </td></tr>
<tr>							<td>SDX::Blend				<td>Image同士の合成処理を行う関数群[未実装]</td></tr>
<tr>							<td>SDX::Filter				<td>Imageにフィルター処理を行う関数群[未実装]</td></tr>
<tr style="background:#ccccff"> <td>音声、動画</td><td> </td></tr>
<tr>							<td>SDX::Music				<td>BGM用音声を表すクラス</td></tr>
<tr>							<td>SDX::Sound				<td>効果音用音声を表すクラス</td></tr>
<tr>							<td>SDX::Movie				<td>動画を表すクラス[未実装]</td></tr>
<tr style="background:#ccccff"> <td>入力</td><td></td></tr>
<tr>							<td>SDX::Input				<td>キーやマウスによる入力をまとめて管理するクラス</td></tr>
<tr>							<td>SDX::Key				<td>各ボタンとキーを表すクラス</td></tr>
<tr>							<td>SDX::Joypad				<td>ジョイパッドの状態を表すクラス</td></tr>
<tr>							<td>SDX::Keyboard			<td>キーボードの状態を表すクラス</td></tr>
<tr>							<td>SDX::Mouse				<td>マウスの状態を表すクラス</td></tr>
<tr>							<td>SDX::Touch				<td>タッチ操作の状態を表すクラス</td></tr>
<tr>							<td>SDX::Gesture			<td>タッチ操作の各種ジェスチャー</td></tr>
<tr style="background:#8888ff"> <th>フレームワーク</th>		<th>マルチメディアクラスを間接利用するクラス等</th></tr>
<tr style="background:#ccccff"> <td>拡張描画機能</td><td>	</td></tr>
<tr>							<td>SDX::ImagePack			<td>複数のImageをまとめるクラス</td></tr>
<tr>							<td>SDX::Film				<td>Imageをまとめてコマ送りアニメとして表すクラス</td></tr>
<tr>							<td>SDX::Anime				<td>Imageをまとめてコマ送りアニメとして表すクラス</td></tr>
<tr>							<td>SDX::IFrame				<td>描画用枠のインターフェース</td></tr>
<tr>							<td>SDX::BmpFrame			<td>描画用枠を表すクラス</td></tr>
<tr>							<td>SDX::Camera				<td>2D用に座標変換を行うカメラを表すクラス</td></tr>
<tr style="background:#ccccff"> <td>図形と当たり判定</td><td> </td></tr>
<tr>							<td>SDX::IShape				<td>位置情報を持つ図形の抽象クラス</td></tr>
<tr>							<td>SDX::Complex			<td>複合図形を表すクラス</td></tr>
<tr>							<td>SDX::Point				<td>点を表す図形クラス</td></tr>
<tr>							<td>SDX::Line				<td>太さのある線を表す図形クラス</td></tr>
<tr>							<td>SDX::Rect				<td>矩形を表す図形クラス</td></tr>
<tr>							<td>SDX::Circle				<td>円を表す図形クラス</td></tr>
<tr style="background:#8888ff"> <th>ユーティリティー</th>	<th>その他の便利なクラス</th></tr>
<tr>							<td>SDX::File				<td>入出力可能なテキストかバイナリファイルを表すクラス</td></tr>
<tr>							<td>SDX::Dirctory			<td>フォルダ内のファイル名を取得、フォルダの作成</td></tr>
<tr>							<td>SDX::Rand				<td>乱数生成関数群</td></tr>
<tr>							<td>SDX::Time				<td>時間と日付を取得する関数群</td></tr>
<tr>							<td>SDX::MOTION				<td>移動方法のポリシー郡</td></tr>
<tr>							<td>SDX::EnumArray			<td>列挙型用固定配列</td></tr>
<tr>							<td>SDX::SPEED				<td>速度変化のポリシー郡</td></tr>
<tr style="background:#8888ff"> <th>設計サンプル</th>		<th>再利用可能な設計のサンプル集</th></tr>
<tr style="background:#ccccff"> <td>2Dスプライト</th><td> </td></tr>
<tr>							<td>SDX::ISprite			<td>2Dモデルに貼り付けるスプライトを表す抽象クラス</td></tr>
<tr>							<td>SDX::SpImage			<td>Imageのスプライト</td></tr>
<tr>							<td>SDX::SpAnime			<td>Animeのスプライト</td></tr>
<tr>							<td>SDX::SpFont				<td>IFontのスプライト</td></tr>
<tr>							<td>SDX::SpFrame			<td>IFrameのスプライト</td></tr>
<tr>							<td>SDX::SpMap				<td>マップチップのスプライト</td></tr>
<tr>							<td>SDX::SpNull				<td>何も描画しないスプライト</td></tr>
<tr style="background:#ccccff"> <td>2Dモデル</td><td> </td></tr>
<tr>							<td>SDX::Model				<td>ShapeとSpriteをまとめて、2Dモデルを表すクラス</td></tr>
<tr style="background:#ccccff"> <td>シーン管理</td><td></td></tr>
<tr>							<td>SDX::IScene				<td>シーンのインターフェース</td></tr>
<tr>							<td>SDX::Director			<td>シーンを管理するクラス</td></tr>
</table>
*/