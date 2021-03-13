//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <vector>

namespace SDX_ADE
{
	using namespace SDX;
	//探索中のエフェクト
	//FigterとPartyに持たしても良さそう

	//ダメージエフェクト-数値or回復or miss or Buffがポップ

	class TextEffect
	{
	private:

	public:
		enum class TextType
		{
			ダメージ,
			回復,
			回避,
			COUNT
		};

		const Color ダメージ色 = { 255,120,120 };
		const Color 回復色 = { 60,255,60 };
		const Color バフ = { 60,60,255 };
		const Color デバフ = { 255,60,255 };

		bool is味方;
		int 配置ID;

		TextType 種類;
		int ダメージ量;
		int 座標Y = 10;
		const int 表示終了Y = -10;
		const int 移動Y = -1;

		TextEffect(TextType 種類 , int ダメージ量 , bool is味方 , int 配置ID):
			種類(種類),
			ダメージ量(ダメージ量),
			is味方(is味方),
			配置ID(配置ID)
		{}

		//破棄する場合 trueを返す
		bool Update()
		{
			座標Y += 移動Y;
			return (座標Y < 表示終了Y);
		}

		TextEffect& operator=(const TextEffect& コピー元)
		{
			// 代入操作時に行う処理を記述
			this->ダメージ量 = コピー元.ダメージ量;
			this->種類 = コピー元.種類;
			this->座標Y = コピー元.座標Y;
			this->is味方 = コピー元.is味方;
			this->配置ID = コピー元.配置ID;

			return *this;
		}
	};

	//コマ送りアニメ戦闘エフェクト
	class BattleEffect
	{
	private:
		const int フレーム時間 = 4;
		int 加算減産;
		int フレーム番号 = 0;
		int アニメ時間 = 0;

	public:

		bool is味方;
		int 配置ID;

		ImagePack& スキルエフェクト;

		BattleEffect(int id, bool is味方, int 配置ID) :
			スキルエフェクト(MEffect::エフェクト[id]),
			加算減産(MEffect::エフェクト種類[id]),
			is味方(is味方),
			配置ID(配置ID)
		{}

		//破棄する場合 trueを返す
		bool Update()
		{
			アニメ時間++;
			if (アニメ時間 >= フレーム時間)
			{
				フレーム番号++;
				アニメ時間 = 0;

				if (フレーム番号 >= スキルエフェクト.GetSize())
				{
					return true;
				}
			}

			return false;
		}

		BattleEffect& operator=(const BattleEffect& コピー元)
		{
			// 代入操作時に行う処理を記述
			this->スキルエフェクト = コピー元.スキルエフェクト;
			this->フレーム番号 = コピー元.フレーム番号;
			this->アニメ時間 = コピー元.アニメ時間;
			this->is味方 = コピー元.is味方;
			this->配置ID = コピー元.配置ID;

			return *this;
		}

		bool Draw(int x ,int y , double 拡大率)
		{
			if (加算減産 == 1 ) { Screen::SetBlendMode(BlendMode::Add); }
			スキルエフェクト[フレーム番号]->DrawRotate({ x,y }, 拡大率, 0);
			if (加算減産 != 0) { Screen::SetBlendMode(); }
			return false;
		}
	};

	//素材入手エフェクト-素材がポップする
	class MaterialEffect
	{
	private:
		const int ポップ間隔 = 15;
	public:
		Image* image;
		int 隠れ時間;
		int 配置ID;//敵ドロップの場合0以上にする

		int 座標Y = 0;

		const int 表示終了Y = -20;
		const int 移動Y = -1;

		MaterialEffect(Image* image , int 隠れ時間 , int 配置ID = -1):
			image(image),
			隠れ時間(隠れ時間 * ポップ間隔),
			配置ID(配置ID)
		{}

		//破棄する場合 trueを返す
		bool Update()
		{
			if (隠れ時間 > 0)
			{
				隠れ時間--;
				return false;
			}

			座標Y += 移動Y;

			return (座標Y < 表示終了Y);
		}

		MaterialEffect& operator=(const MaterialEffect& コピー元)
		{
			// 代入操作時に行う処理を記述
			this->image = コピー元.image;
			this->隠れ時間 = コピー元.隠れ時間;
			this->座標Y = コピー元.座標Y;
			this->配置ID = コピー元.配置ID;
		
			return *this;
		}
	};
	
	class Effect
	{
	public:
		//パーティ毎のエフェクト保持用vector
		inline static std::vector<TextEffect> 文字[CV::上限パーティ数];
		inline static std::vector<BattleEffect> アニメ[CV::上限パーティ数];
		inline static std::vector<MaterialEffect> 素材[CV::上限パーティ数];

		template <class T>
		static void UpdateAndDelete(std::vector<T>& エフェクト)
		{
			if (エフェクト.size() == 0) { return; }

			auto it_del = std::remove_if(エフェクト.begin(), エフェクト.end(),
				[](T& it) ->bool { return it.Update(); });

			エフェクト.erase(it_del, エフェクト.end());
		}

		static void SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//エフェクトは保存しない
		}
	};
}