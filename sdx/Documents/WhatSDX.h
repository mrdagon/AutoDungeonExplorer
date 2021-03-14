﻿/*!
@page WhatSDX SDXとは？
SDXFrameworkはC++で自由ゲームを制作するための、クラスライブラリです。\n
以下のような特徴があります。\n
<HR>
<B>特徴</B>\n
<B>1.マルチプラットフォーム</B>\n
内部でSDL2.0を使っているので、多くのプラットフォームで動きます。\n
機能的にはSDL2.0+α程度ですが、SDL2.0に比べるとかなり使いやすくなっています\n
<HR>
<B>2.日本語サポート</B>\n
　作者が日本語の方が得意なので、日本語中心で開発を進めています。\n
　英語主体で開発を進めるのは効率が悪いです。\n
特に仮引数は日本語にするとIDEのヒント表示が見やすくなり、リファレンスを見る回数を減らせ、利用者にとってもメリットがあります。\n
\n
　ついでに差別化になれば良いかなとも思っています\n
　公式ドキュメントが英語だけのライブラリは多くあるので、日本語のサポートを優先した方がまだ特徴が出ます。\n
世界規模で見れば英語話者が多いので、英語主体にした方が開発者が集まる可能性が高くなるのでは？と思う方がいるかもしれませんが、\n
そもそも最近はOSSのゲームライブラリが増えまくっているので、日本語だろうが英語だろうが簡単には開発者は集まらないようです。\n
\n
<HR>
<B>3.シンプル</B>\n
　ライブラリ作者が必要としている機能のみ実装しているのでシンプルな2D用のゲームライブラリになっています。\n
\n
<HR>
<B>4.コピーレフトなライセンス</B>\n
　SDXはコピーレフトなライセンスであるGNU Affero General Public License Version 3を適用している、自由なライブラリです。\n
そのためライブラリを利用したソフトウェアを公開する場合、ソースコードの公開が必須となり、さらに配信業者との契約次第では配布が困難になる場合があります。\n
AGPLを適用すると緩いライセンスに比べて利用者が減るのでは？と思われるかもしれませんが、必ずしもそうでは無いと考えています\n
\n
　ライブラリを配布する場合のライセンスの方針は大きく3つに分ける事が出来ると思います。\n
\n
[1.緩いオープンなライセンス]\n
 例えばApache LicenseやMITライセンスは派生物に対してライセンス表記や特許のクロスライセンスしか求めません。\n
そのためライブラリを利用したコードを公開するかどうかは任意になります。最も多いパターンです。\n
\n
 企業に支援される事を目標とする場合、あるいは規模が極端に小さく著作権を主張する意味が無い場合、\n
ライセンスを確認せずに使えるようにしたい場合、特にこだわりが無い場合、\n
利用者同士でコードを共有せずに競争させて良い物が出来れば良いと言う考えの場合、\n
GitHubを無料で使うためにコードを公開している場合等はApache LicenseやMITライセンスを適用するのが良いと思われます\n
\n
[2.利用料を要求するライセンス]\n
　無料で利用するのは不可能、もしくは機能が制限される、あるいはサポート無しのコピーレフトなライセンスになるが、\n
利用料を払うと緩いライセンスで利用可能になり、サポートが受けられるライブラリがあります。\n
\n
利用者が集まる目算があり、利用料で収入を得たい場合に選ばれる事が多いです\n
\n
[3.コピーレフトなライセンス]\n
GPL等のコピーレフトなライセンスをライブラリに適用するのはユーザー同士が協力する事を強く推奨したい場合には良い選択です。\n
しかしながらライセンスが比較的ややこしかったり、権利を強く主張するので誤解されたり敬遠されがちでもあります\n
場合によっては緩いライセンスを適用した方が良いでしょう。\n
\n
　SDXがAGPL ver3を選択した理由は、以下です。\n
\n
[1.ソフトを販売する上でのデメリットが少ない]\n
　趣味で開発して無償で配布している人にとってはどうでも良いのでしょうが、\n
ソフトウェアを有償で販売したい場合、ソースコードから派生物を自由に作れたり再頒布が自由だと売上に響くので困ります。\n
販売以外で収益を得るのもなんやかんやで困難ですし、ソースコードの公開がダンピングになると言った懸念も有り得ます。\n
\n
　しかしながらゲームの場合、イラストやBGMやシナリオを別のライセンスで配布すれば、ソフトウェア単体ではほぼ動作しないので、商業上の問題が抑えられます。\n
\n
　プラットフォーム事業者との契約によってはコードを公開するのとソフトを配布するのが両立できなかったり、広告外しやガチャをローカルで遊べる仕様に改造出来たり\n
デメリットがある場合もありますが、コード公開する事が経済的に非合理であるとは必ずしも言えません。\n
\n
[2.公開によるメリット]\n
　ライブラリ利用者が増えて、コードが公開されれば、開発コストが下がって、クオリティが向上し、デバッグ済みのコードを再利用出来るので、安定性も上がります\n
ライブラリ開発においては実際にどのような利用がなされているか調査したり取り込む事が楽になるメリットがあります。\n
\n
　普通のライブラリであれば、利用者数が増えてもユーザーが受けるメリットはそんなにありませんが、コピーレフトなライブラリであれば\n
利用者が増える事が利用者のメリットにもなります\n
\n
　自分しか持っていない独自技術がある場合でも公開した方が有利な場合もあります。\n
ゲームの場合、一番最初にそのジャンルを開拓したり新しい事をした場合、後続のゲームが登場する事は宣伝になる上、ファン層の拡大につながる事が多いです。\n
特にマイナーなジャンルは積極的に技術を公開する方がメリットが多いと思います。\n
\n
　また一からゲームを作るのに興味は無いが公開されてるゲームを自由に改造したい人は結構いるので、そういったユーザーに喜ばれます\n
バグ報告等の支援が起こりやすくなると思います、保守コストは馬鹿にならないため、それらも重要です\n
\n
[3.ライブラリがGPLであるメリット]\n
　上記のメリットは、緩いライセンスのライブラリを利用して個別にコードを公開しても生じます。\n
しかしながらライブラリがコピーレフトな場合の方がその効果は大きくなるんじゃないかと思っています。\n
\n
　個人でソースコードを公開しても、公開している人が少ないため、コードを探そうとする人も少ないです。\n
そのため、公開しても必要としている人が見つける可能性は低いです。\n
\n
　ライブラリをコピーレフトにすれば、それを共有するコミュニティが生まれ、開発者の横の繋がりが出来る可能性が上がります。\n
そうなれば自分が欲しいコードがあるか探す人も増えるし、探しやすくなるのではないかと思います。\n
　色んな所の質問掲示板で｢こういうゲームを作りたいが参考になるコードはないか？｣と言った質問を結構見かけるのでコードの需要はあるはずです\n
解説サイトを作るのは相当な手間ですが、コード公開はそこまで手間ではありませんし、特に不利益も無いなら公開するのが道徳的ではないかと思います\n
\n
　このような理由でライブラリをAGPLにしています。\n
\n
　便利なライブラリやツールがあっても、ゲームを一から実装するのは何かと大変です。\n
既にあるコードを利用出来る方が楽に決まっています、多くの人がコードを公開するようになる事で開発が楽になると良いと思います。\n
\n
　他の開発者に協力したり支援する事は決して難しい事でも面倒な事でもありません、コードを公開するだけでも意味があります\n
\n
ライブラリ開発等に興味がある人はOSDNの掲示板で気軽にお問い合わせ下さい。
<HR>
<B>対応開発環境</B>\n
Windows7以降 + VisualStudio2013\n
\n
MacOSX最新版 + Xcode最新版\n
\n
GNU/Linux系のOS + Clang3.3以降\n
\n
解説を書いていないだけでSDL2.0が動く環境では大体使えるはずです\n
<HR>
<B>機能一覧</B>\n
@ref ClassGroup
<HR>
*/