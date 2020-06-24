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
		constexpr SEType キャンセル = SEType::決定;

		constexpr SEType ウィンドウ開く = SEType::決定;
		constexpr SEType ウィンドウ閉じ = SEType::決定;

		constexpr SEType タブ切り替え = SEType::決定;
		constexpr SEType ドラッグ = SEType::決定;
		constexpr SEType 装備変更 = SEType::決定;
		constexpr SEType 配置換え = SEType::決定;

		constexpr SEType ボタンクリック = SEType::決定;
		constexpr SEType 求人リロール = SEType::決定;
		constexpr SEType 雇用 = SEType::決定;
		constexpr SEType 投資予約 = SEType::決定;
		constexpr SEType 投資解除 = SEType::決定;
		constexpr SEType 投資実行 = SEType::決定;

		//通知
		constexpr SEType クエスト完了 = SEType::決定;
		constexpr SEType 装備作成 = SEType::決定;
		constexpr SEType 新装備作成 = SEType::決定;
		//ユニーク作成
		constexpr SEType 部門Lv上昇 = SEType::決定;
		constexpr SEType 技術Lv上昇 = SEType::決定;

		//戦闘/探索効果音
		constexpr SEType ダンジョン発見 = SEType::決定;//まだ
		constexpr SEType ボス発見 = SEType::決定;//まだ
		constexpr SEType ギルメン気絶 = SEType::決定;//まだ
		constexpr SEType 撤退 = SEType::決定;//まだ

	}
}