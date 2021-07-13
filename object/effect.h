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
		int 座標X = 0;
		int 座標Y = 10;
		bool isEnd = false;
		const int 表示終了Y = -10;
		const int 移動Y = -1;

		TextEffect(TextType 種類 , int ダメージ量 , bool is味方 , int 配置ID):
			種類(種類),
			ダメージ量(ダメージ量),
			is味方(is味方),
			配置ID(配置ID)
		{}

		void Set(TextType 種類, int ダメージ量, bool is味方, int 配置ID)
		{
			this->種類 = 種類;
			this->ダメージ量 = ダメージ量;
			this->is味方 = is味方;
			this->配置ID = 配置ID;

			座標X = 0;
			座標Y = 10;
			isEnd = false;
		}

		void Draw(int px, int py)
		{
			if (isEnd == true) { return; }

			switch (種類)
			{
			case TextEffect::TextType::ダメージ:
				MFont::M->DrawBoldRotate({ px , py }, 1, 0, ダメージ色, Color::Black, ダメージ量);
				break;
			case TextEffect::TextType::回復:
				MFont::M->DrawBoldRotate({ px , py }, 1, 0, 回復色, Color::Black, ダメージ量);
				break;
			case TextEffect::TextType::回避:
				MFont::M->DrawBoldRotate({ px , py }, 1, 0, Color::White, Color::Black, "miss");
				break;
			}
			座標Y += 移動Y * (int)std::sqrt(Game::ゲームスピード);

			isEnd = (座標Y < 表示終了Y);
		}
	};

	//コマ送りアニメ戦闘エフェクト
	class BattleEffect
	{
	private:
		const int フレーム時間 = 4;
		int 加減算;
		int フレーム番号 = 0;
		int アニメ時間 = 0;

	public:

		bool is味方;
		int 配置ID;
		bool isEnd = false;

		ImagePack* スキルエフェクト;

		BattleEffect(int id, bool is味方, int 配置ID) :
			スキルエフェクト(&MEffect::エフェクト[id]),
			加減算(MEffect::エフェクト種類[id]),
			is味方(is味方),
			配置ID(配置ID)
		{}


		void Set(int id, bool is味方, int 配置ID)
		{
			this->スキルエフェクト = &MEffect::エフェクト[id];
			this->加減算 = MEffect::エフェクト種類[id];
			this->is味方 = is味方;
			this->配置ID = 配置ID;
			this->フレーム番号 = 0;
			this->アニメ時間 = 0;
			this->isEnd = false;
		}

		bool Draw(int x ,int y , double 拡大率)
		{
			if (isEnd == true) { return false; }

			if (加減算 == 1 ) { Screen::SetBlendMode(BlendMode::Add); }
			スキルエフェクト[0][フレーム番号]->DrawRotate({ x,y }, 拡大率, 0);
			if (加減算 != 0) { Screen::SetBlendMode(); }

			アニメ時間 += Game::ゲームスピード;

			while (1)
			{
				if (アニメ時間 >= フレーム時間)
				{
					フレーム番号++;
					アニメ時間 -= フレーム時間;
				}
				else
				{
					break;
				}
			}

			if (フレーム番号 >= スキルエフェクト->GetSize())
			{
				フレーム番号 = スキルエフェクト->GetSize() - 1;
				isEnd = true;
			}

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

		int 座標X = 0;
		int 座標Y = 0;
		bool isEnd = false;

		const int 表示終了Y = -20;
		const int 移動Y = -1;

		MaterialEffect(Image* image , int 隠れ時間 , int 配置ID = -1):
			image(image),
			隠れ時間(隠れ時間 * ポップ間隔),
			配置ID(配置ID)
		{}

		void Set(Image* image, int 隠れ時間, int 配置ID)
		{
			座標X = 0;
			座標Y = 0;
			isEnd = false;

			this->image = image;
			this->隠れ時間 = 隠れ時間;
			this->配置ID = 配置ID;
		}

		//破棄する場合 trueを返す
		bool Update()
		{
			if (隠れ時間 > 0)
			{
				隠れ時間--;
				return false;
			}
		}

		//描画時に座標を少し移動
		void Draw(int px,int py)
		{
			if (座標Y < 表示終了Y)
			{
				isEnd = true;
				return;
			}

			image->DrawRotate({ px , py }, 1, 0);
			座標Y += 移動Y * (int)std::sqrt(Game::ゲームスピード);
		}
	};
	
	class Effect
	{
	public:
		//パーティ毎のエフェクト保持用vector
		inline static std::vector<TextEffect> 文字[CV::上限パーティ数];
		inline static std::vector<BattleEffect> アニメ[CV::上限パーティ数];
		inline static std::vector<MaterialEffect> 素材[CV::上限パーティ数];

		static void Addアニメ(int id, bool is味方, int 配置ID,int パーティID)
		{
			for (int i = 0; i < アニメ[パーティID].size(); i++)
			{
				if (アニメ[パーティID][i].isEnd == true)
				{
					アニメ[パーティID][i].Set(id, is味方, 配置ID);
					return;
				}
			}

			アニメ[パーティID].emplace_back(id, is味方, 配置ID);
		}

		static void Add文字(TextEffect::TextType 種類, int ダメージ量, bool is味方, int 配置ID,int パーティID)
		{
			for (int i = 0; i < 文字[パーティID].size(); i++)
			{
				if (文字[パーティID][i].isEnd == true)
				{
					文字[パーティID][i].Set(種類, ダメージ量, is味方, 配置ID);
					return;
				}
			}

			文字[パーティID].emplace_back(種類, ダメージ量, is味方, 配置ID);
		}

		static void Add素材(Image* image, int 隠れ時間, int 配置ID, int パーティID)
		{
			for (int i = 0; i < 素材[パーティID].size(); i++)
			{
				if (素材[パーティID][i].isEnd == true)
				{
					素材[パーティID][i].Set(image, 隠れ時間, 配置ID);
					return;
				}
			}

			素材[パーティID].emplace_back(image, 隠れ時間, 配置ID);
		}



		static void Update()
		{
			for (int i = 0; i < CV::上限パーティ数; i++)
			{
				for (auto& it : 素材[i])
				{
					it.Update();
				}
			}
		}

		static void SaveLoad(File& ファイル, FileMode 読み書きモード)
		{
			//エフェクトは保存しない
		}
	};
}