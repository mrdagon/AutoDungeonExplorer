//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_BSC
{
	namespace SE
	{
		//const SETType a = SETType::決定

		//操作時効果音
		constexpr SEType 決定 = SEType::決定;
		constexpr SEType キャンセル = SEType::キャンセル;

		constexpr SEType ウィンドウ開く = SEType::ボタン押;
		constexpr SEType ウィンドウ閉じ = SEType::ボタン押;

		constexpr SEType タブ切り替え = SEType::タブ押;
		constexpr SEType ドラッグ = SEType::掴む;
		constexpr SEType 装備変更 = SEType::ボタン押;
		constexpr SEType 配置換え = SEType::装着;

		constexpr SEType ボタンクリック = SEType::ボタン押;
		constexpr SEType 求人リロール = SEType::ボタン押;
		constexpr SEType 雇用 = SEType::装着;
		constexpr SEType 投資予約 = SEType::ボタン押;
		constexpr SEType 投資解除 = SEType::ボタン押;
		constexpr SEType 投資実行 = SEType::投資;

		//通知
		constexpr SEType クエスト完了 = SEType::クエスト完了;
		constexpr SEType 装備作成 = SEType::製造;
		constexpr SEType 新装備作成 = SEType::新製造;
		constexpr SEType 販売 = SEType::販売;//まだ

		//ユニーク作成
		constexpr SEType 部門Lv上昇 = SEType::内政Lv;
		constexpr SEType 技術Lv上昇 = SEType::内政Lv;

		//戦闘/探索効果音
		constexpr SEType 探索開始 = SEType::探索開始;
		constexpr SEType 探索終了 = SEType::探索終了;
		constexpr SEType 地図発見 = SEType::地図発見;//まだ
		constexpr SEType ボス発見 = SEType::ボス発見;//まだ

		constexpr SEType 攻撃 = SEType::攻撃;//まだ
		constexpr SEType 回復 = SEType::回復;//まだ
		constexpr SEType 補助 = SEType::補助;//まだ

		constexpr SEType 味方気絶 = SEType::味方気絶;//まだ
		constexpr SEType 敵気絶 = SEType::敵気絶;//まだ
		constexpr SEType 全滅 = SEType::全滅;//まだ

	}
}