//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	//各種定数
	namespace CV
	{
		constexpr double バージョン = 0.001;
		//constexpr bool isデバッグ = true;
		constexpr bool isデバッグ = false;



		constexpr int パーティ人数 = 5;
		constexpr int 最大パーティ数 = 3;

		constexpr int 最大控え人数 = 35;

		constexpr int 最大製造人数 = 12;//部門毎の最大製造人数

		constexpr int 最大素材種 = 8;

		constexpr int 最大収集種 = 5;//1ダンジョンに設定可能な収集アイテム最大数

		//探索エフェクト、待ち時間用
		constexpr int 探索移動速度 = 2;
		constexpr int 収集待機A = 160;//素材が流れてくる時間
		constexpr int 収集待機B = 200;//素材収集中の時間
		constexpr int 全滅暗さ = 128;

		constexpr int 戦闘開始後待ち時間 = 120;
		constexpr int 戦闘1ターン待ち時間 = 40;
		constexpr int 戦闘終了後待ち時間 = 120;

		constexpr int 探索開始時移動時間 = 60;//移動アニメ用
		constexpr int 探索開始時待ち時間 = 120;
		constexpr int 撤退後待ち時間 = 120;

		//戦闘関係の定数
		constexpr int 初期CT乱数 = 50;

		constexpr int 気絶スタン値 = 100;

		//製造関係の定数
		constexpr int 最大製造スキル数 = 2;
		constexpr int 素材消費数 = 5;

		constexpr int 基礎品質経験値 = 10;

		constexpr int レア素材レア率 = 5;
		constexpr int レア素材値段倍率 = 20;
		constexpr int レア素材経験倍率 = 5;


		//外部データ最大数//
		constexpr int 装備種 = 240;
		constexpr int Pスキル種 = 64;
		constexpr int Aスキル種 = 32;

		constexpr int 最大装備ランク = 99;//+99まで

		constexpr int 最大投資Lv = 10;
		constexpr int 最大技術Lv = 10;

		constexpr int 最大Aスキル数 = 4;//一人が覚えるスキル数

		constexpr int 最大Pスキル習得リスト = 48;//1職業毎
		constexpr int 最大Aスキル習得リスト = 8;
		constexpr int 最大キースキル習得リスト = 3;

		constexpr int 最大装備Pスキル数 = 2;
		constexpr int 装備部位数 = 3;

		constexpr int ウィンドウ数 = 9;

		constexpr int 要求経験値 = 200;

		constexpr int 一時間フレーム数 = 720;

	}
}