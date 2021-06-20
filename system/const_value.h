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
		bool isレイアウト = true;
		constexpr bool isデバッグ = true;

		constexpr int ヘルプ待機時間 = 5;//マウスオーバー開始からヘルプ表示までの猶予時間
		constexpr int スクロール感度 = 30;
		constexpr int ボタンアニメ時間 = 10;//

		//外部データ件数上限
		constexpr int 上限Aスキル種類 = 200;
		constexpr int 上限Pスキル種類 = 200;

		constexpr int 上限素材種類 = 200;

		constexpr int 上限アクセサリ種類 = 200;

		constexpr int 上限ダンジョン数 = 100;

		constexpr int 上限投資案 = 200;

		constexpr int 上限依頼数 = 200;

		constexpr int 上限素材ランク = 10;
		constexpr double サブ素材必要数 = 0.5;

		constexpr int パーティ人数 = 5;
		constexpr int 上限パーティ数 = 3;//データ上増やせるパーティの限界

		constexpr int 上限探索者登録数 = 100;
		constexpr int 最大控え人数 = 35;

		constexpr int 素材系統 = 6;

		constexpr int 投資コスト最大枠数 = 4;

		constexpr int 最大魔物出現数 = 6;
		constexpr int 最大財宝配置数 = 6;

		constexpr int 最大地図数 = 2;

		//探索エフェクト、待ち時間用
		constexpr int 探索移動速度 = 2;
		constexpr int 収集待機A = 160;//素材が流れてくる時間
		constexpr int 収集待機B = 200;//素材収集中の時間
		constexpr int 地図発見待機 = 240;
		constexpr int 全滅暗さ = 128;

		constexpr int 戦闘開始後待ち時間 = 120;
		constexpr int 戦闘1ターン待ち時間 = 30;
		constexpr int 戦闘終了後待ち時間 = 120;

		constexpr int 探索開始時移動時間 = 60;//移動アニメ用
		constexpr int 探索開始時待ち時間 = 240;
		constexpr int 撤退後待ち時間 = 240;

		//
		constexpr int ボス部屋ID = CV::最大地図数;
		constexpr int 財宝部屋ID = 10;

		//戦闘関係の定数
		constexpr int 初期CT乱数 = 50;

		constexpr int 気絶スタン値 = 100;

		//設定関連
		constexpr int 最低解像度 = 9;
		constexpr int 最大解像度 = 20;


		//外部データ最大数//

		constexpr int 最大装備ランク = 99;//+99まで

		constexpr int 最大投資Lv = 10;

		constexpr int 最大Aスキル数 = 4;//一人が戦闘中に装備出来るスキル数

		constexpr int 最大敵Aスキル数 = 8;
		constexpr int 最大敵Pスキル数 = 8;

		constexpr int 最大キースキル数 = 3;

		constexpr int スキル未予約 = 0;
		constexpr int 最大スキル予約数 = 100;

		constexpr int 装備部位数 = 3;

		constexpr int ウィンドウ数 = 7;

		constexpr int 要求経験値 = 200;

		constexpr int 一時間フレーム数 = 720;

		constexpr int 最大投資予約 = 100;

		constexpr int 最大強化予約 = 100;

	}
}