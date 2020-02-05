//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include "../System/enum_type.h"

namespace SDX_BSC
{
	using namespace SDX;
	//画像、音声、フォント

	//ユニット
	namespace MUnit
	{
		
		EnumArray<ImagePack, UnitImageType> ユニット;

		static void Load()
		{
			ユニット[UnitImageType::ゴブリン].Load("File/unit/unit001.png", 12, 3, 4);
			ユニット[UnitImageType::青ゴブリン].Load("File/unit/unit002.png", 12, 3, 4);
			ユニット[UnitImageType::犬].Load("File/unit/unit003.png", 12, 3, 4);
			ユニット[UnitImageType::青犬].Load("File/unit/unit004.png", 12, 3, 4);
			ユニット[UnitImageType::白猫].Load("File/unit/unit005.png", 12, 3, 4);
			ユニット[UnitImageType::黒猫].Load("File/unit/unit006.png", 12, 3, 4);
			ユニット[UnitImageType::兵士].Load("File/unit/unit007.png", 12, 3, 4);
			ユニット[UnitImageType::赤兵士].Load("File/unit/unit008.png", 12, 3, 4);
			ユニット[UnitImageType::青兵士].Load("File/unit/unit009.png", 12, 3, 4);
			ユニット[UnitImageType::メイド].Load("File/unit/unit010.png", 12, 3, 4);
			ユニット[UnitImageType::ハゲ].Load("File/unit/unit011.png", 12, 3, 4);
			ユニット[UnitImageType::執事].Load("File/unit/unit012.png", 12, 3, 4);
			ユニット[UnitImageType::王].Load("File/unit/unit013.png", 12, 3, 4);
			ユニット[UnitImageType::青王].Load("File/unit/unit014.png", 12, 3, 4);
			ユニット[UnitImageType::王妃].Load("File/unit/unit015.png", 12, 3, 4);
			ユニット[UnitImageType::青王妃].Load("File/unit/unit016.png", 12, 3, 4);
			ユニット[UnitImageType::赤王妃].Load("File/unit/unit017.png", 12, 3, 4);
			ユニット[UnitImageType::小王子].Load("File/unit/unit018.png", 12, 3, 4);
			ユニット[UnitImageType::小姫].Load("File/unit/unit019.png", 12, 3, 4);
			ユニット[UnitImageType::王子].Load("File/unit/unit020.png", 12, 3, 4);
			ユニット[UnitImageType::姫].Load("File/unit/unit023.png", 12, 3, 4);
			ユニット[UnitImageType::ドワーフ].Load("File/unit/unit024.png", 12, 3, 4);
			ユニット[UnitImageType::子ドワーフ].Load("File/unit/unit027.png", 12, 3, 4);
			ユニット[UnitImageType::茶女性].Load("File/unit/unit028.png", 12, 3, 4);
			ユニット[UnitImageType::青女性].Load("File/unit/unit029.png", 12, 3, 4);
			ユニット[UnitImageType::金女性].Load("File/unit/unit031.png", 12, 3, 4);
			ユニット[UnitImageType::緑女性].Load("File/unit/unit033.png", 12, 3, 4);
			ユニット[UnitImageType::茶村人].Load("File/unit/unit030.png", 12, 3, 4);
			ユニット[UnitImageType::金村人].Load("File/unit/unit032.png", 12, 3, 4);
			ユニット[UnitImageType::金子供].Load("File/unit/unit034.png", 12, 3, 4);
			ユニット[UnitImageType::三つ編み].Load("File/unit/unit035.png", 12, 3, 4);
			ユニット[UnitImageType::少年].Load("File/unit/unit036.png", 12, 3, 4);
			ユニット[UnitImageType::少女].Load("File/unit/unit037.png", 12, 3, 4);
			ユニット[UnitImageType::緑防止].Load("File/unit/unit038.png", 12, 3, 4);
			ユニット[UnitImageType::おっさん].Load("File/unit/unit039.png", 12, 3, 4);
			ユニット[UnitImageType::半裸].Load("File/unit/unit040.png", 12, 3, 4);
			ユニット[UnitImageType::青オーク].Load("File/unit/unit041.png", 12, 3, 4);
			ユニット[UnitImageType::赤オーク].Load("File/unit/unit042.png", 12, 3, 4);
			ユニット[UnitImageType::おばさん].Load("File/unit/unit043.png", 12, 3, 4);
			ユニット[UnitImageType::おばあさん].Load("File/unit/unit044.png", 12, 3, 4);
			ユニット[UnitImageType::おじいさん].Load("File/unit/unit045.png", 12, 3, 4);
			ユニット[UnitImageType::勇者].Load("File/unit/unit048.png", 12, 3, 4);
			ユニット[UnitImageType::闘士].Load("File/unit/unit050.png", 12, 3, 4);
			ユニット[UnitImageType::弓士].Load("File/unit/unit053.png", 12, 3, 4);
			ユニット[UnitImageType::剣聖].Load("File/unit/unit055.png", 12, 3, 4);
			ユニット[UnitImageType::武術家].Load("File/unit/unit057.png", 12, 3, 4);
			ユニット[UnitImageType::魔女].Load("File/unit/unit059.png", 12, 3, 4);
			ユニット[UnitImageType::精霊].Load("File/unit/unit062.png", 12, 3, 4);
			ユニット[UnitImageType::くの一].Load("File/unit/unit063.png", 12, 3, 4);
			ユニット[UnitImageType::盗賊].Load("File/unit/unit065.png", 12, 3, 4);
			ユニット[UnitImageType::レンジャー].Load("File/unit/unit066.png", 12, 3, 4);
			ユニット[UnitImageType::妖術師].Load("File/unit/unit068.png", 12, 3, 4);
			ユニット[UnitImageType::大魔導師].Load("File/unit/unit070.png", 12, 3, 4);
			ユニット[UnitImageType::族長].Load("File/unit/unit071.png", 12, 3, 4);
			ユニット[UnitImageType::空手家].Load("File/unit/unit073.png", 12, 3, 4);
			ユニット[UnitImageType::戦士].Load("File/unit/unit075.png", 12, 3, 4);
			ユニット[UnitImageType::戦士2].Load("File/unit/unit077.png", 12, 3, 4);
			ユニット[UnitImageType::重装].Load("File/unit/unit078.png", 12, 3, 4);
			ユニット[UnitImageType::柔術家].Load("File/unit/unit080.png", 12, 3, 4);
			ユニット[UnitImageType::呪術師].Load("File/unit/unit082.png", 12, 3, 4);
			ユニット[UnitImageType::暗殺者].Load("File/unit/unit087.png", 12, 3, 4);
			ユニット[UnitImageType::傭兵].Load("File/unit/unit090.png", 12, 3, 4);
			ユニット[UnitImageType::老兵].Load("File/unit/unit093.png", 12, 3, 4);
			ユニット[UnitImageType::戦士3].Load("File/unit/unit094.png", 12, 3, 4);
			ユニット[UnitImageType::騎士].Load("File/unit/unit097.png", 12, 3, 4);
			ユニット[UnitImageType::司祭].Load("File/unit/unit099.png", 12, 3, 4);

			ユニット[UnitImageType::スライム].Load("File/monster/mon000.png", 12, 3, 4);
			ユニット[UnitImageType::赤スライム].Load("File/monster/mon001.png", 12, 3, 4);
			ユニット[UnitImageType::狼].Load("File/monster/mon002.png", 12, 3, 4);
			ユニット[UnitImageType::青狼].Load("File/monster/mon003.png", 12, 3, 4);
			ユニット[UnitImageType::三頭犬].Load("File/monster/mon004.png", 12, 3, 4);
			ユニット[UnitImageType::スケルトン].Load("File/monster/mon005.png", 12, 3, 4);
			ユニット[UnitImageType::サハギン].Load("File/monster/mon006.png", 12, 3, 4);
			ユニット[UnitImageType::インプ].Load("File/monster/mon007.png", 12, 3, 4);
			ユニット[UnitImageType::トレント].Load("File/monster/mon008.png", 12, 3, 4);
			ユニット[UnitImageType::グリフィン].Load("File/monster/mon009.png", 12, 3, 4);
			ユニット[UnitImageType::ドラゴン].Load("File/monster/mon010.png", 12, 3, 4);

		}
	}

	//武器、防具、その他のアイコン
	namespace MIcon
	{
		EnumArray<Image, ItemImageType> アイテム;
		EnumArray<Image, MaterialType> 素材;
		EnumArray<Image, IconType> アイコン;
		EnumArray<Image, EmoteType> エモート;
		EnumArray<Image, DungeonType> ダンジョン;
		EnumArray<Image, SkillType> スキル;
		EnumArray<Image, ItemType> 装備種;
		EnumArray<Image, StatusType> ステータス種;

		static void Load()
		{
			//武器-防具
			アイテム[ItemImageType::鉄の剣].Load("File/wepon/wepon215.png");
			アイテム[ItemImageType::鉄の斧].Load("File/wepon/wepon004.png");
			アイテム[ItemImageType::木の弓].Load("File/wepon/wepon058.png");
			アイテム[ItemImageType::スタッフ].Load("File/wepon/wepon201.png");
			アイテム[ItemImageType::ワンド].Load("File/wepon/wepon165.png");
			アイテム[ItemImageType::鉄の盾].Load("File/wepon/mat_018.png");
			アイテム[ItemImageType::鉄の鎧].Load("File/armor/armor006.png");
			アイテム[ItemImageType::鎖帷子].Load("File/armor/armor016.png");
			アイテム[ItemImageType::皮のローブ].Load("File/armor/armor066.png");
			//素材
			素材[MaterialType::石材].Load("File/system/mat_000.png");
			素材[MaterialType::金属].Load("File/system/mat_001.png");
			素材[MaterialType::木材].Load("File/system/mat_002.png");
			素材[MaterialType::皮革].Load("File/system/mat_003.png");
			素材[MaterialType::骨牙].Load("File/system/mat_004.png");
			素材[MaterialType::羽毛].Load("File/system/mat_005.png");
			素材[MaterialType::宝石].Load("File/system/mat_006.png");
			//アイコン
			アイコン[IconType::閉じる].Load("File/icon/s_057.png");
			アイコン[IconType::星].Load("File/icon/s_014.png");

			アイコン[IconType::来客].Load("File/icon/s_117.png");
			アイコン[IconType::迷宮].Load("File/icon/s_095.png");
			アイコン[IconType::ログ].Load("File/icon/s_012.png");
			アイコン[IconType::目標].Load("File/icon/s_086.png");
			アイコン[IconType::情報].Load("File/icon/s_011.png");
			アイコン[IconType::装備].Load("File/icon/s_118.png");
			アイコン[IconType::戦略].Load("File/icon/s_007.png");
			アイコン[IconType::素材].Load("File/icon/s_116.png");
			アイコン[IconType::団員].Load("File/icon/s_009.png");
			アイコン[IconType::依頼].Load("File/icon/s_046.png");
			アイコン[IconType::求人].Load("File/icon/s_008.png");
			アイコン[IconType::収支].Load("File/icon/s_013.png");

			アイコン[IconType::日付].Load("File/icon/s_056.png");
			アイコン[IconType::時間].Load("File/icon/s_077.png");
			アイコン[IconType::人口].Load("File/icon/s_005.png");
			アイコン[IconType::順位].Load("File/icon/s_017.png");
			アイコン[IconType::資金].Load("File/icon/s_053.png");
			アイコン[IconType::ヘルプ].Load("File/icon/s_089.png");
			アイコン[IconType::停止].Load("File/icon/s_055.png");
			アイコン[IconType::速度].Load("File/icon/s_054.png");
			アイコン[IconType::出口].Load("File/icon/s_065.png");
			アイコン[IconType::三角].Load("File/icon/s_058.png");
			アイコン[IconType::設定].Load("File/icon/s_052.png");
			アイコン[IconType::ハンマー].Load("File/icon/s_045.png");
			アイコン[IconType::宝箱].Load("File/system/other_014.png");

			アイコン[IconType::灰石].Load("File/system/mat_009.png");


			ダンジョン[DungeonType::城].Load("File/system/move_00.png");
			ダンジョン[DungeonType::森].Load("File/system/move_01.png");
			ダンジョン[DungeonType::洞窟].Load("File/system/move_02.png");
			ダンジョン[DungeonType::砂漠].Load("File/system/move_03.png");
			ダンジョン[DungeonType::山].Load("File/system/move_04.png");
			ダンジョン[DungeonType::滝].Load("File/system/move_05.png");
			ダンジョン[DungeonType::塔].Load("File/system/move_06.png");
			ダンジョン[DungeonType::廃墟].Load("File/system/move_07.png");

			スキル[SkillType::剣].Load("File/game_icons/plain-dagger.png");
			スキル[SkillType::斧].Load("File/game_icons/battle-axe.png");
			スキル[SkillType::槌].Load("File/game_icons/flanged-mace.png");
			スキル[SkillType::盾].Load("File/game_icons/checked-shield.png");
			スキル[SkillType::刺剣].Load("File/game_icons/stiletto.png");
			スキル[SkillType::槍].Load("File/game_icons/trident.png");
			スキル[SkillType::弓].Load("File/game_icons/pocket-bow.png");
			スキル[SkillType::銃].Load("File/game_icons/winchester-rifle.png");
			スキル[SkillType::魔杖].Load("File/game_icons/orb-wand.png");
			スキル[SkillType::骨杖].Load("File/game_icons/skull-staff.png");
			スキル[SkillType::神杖].Load("File/game_icons/wizard-staff.png");
			スキル[SkillType::祝杖].Load("File/game_icons/lunar-wand.png");
			スキル[SkillType::鎧].Load("File/game_icons/breastplate.png");
			スキル[SkillType::革鎧].Load("File/game_icons/leather-armor.png");
			スキル[SkillType::ローブ].Load("File/game_icons/robe.png");
			スキル[SkillType::挑発].Load("File/game_icons/arrows-shield.png");
			スキル[SkillType::隠密].Load("File/game_icons/invisible.png");
			スキル[SkillType::防御].Load("File/game_icons/shield-reflect.png");
			スキル[SkillType::回避].Load("File/game_icons/dodging.png");
			スキル[SkillType::魔防].Load("File/game_icons/shield-bash.png");//-消して庇う
			スキル[SkillType::回復].Load("File/game_icons/healing.png");
			スキル[SkillType::攻撃].Load("File/game_icons/saber-slash.png");
			スキル[SkillType::バフ].Load("File/game_icons/embrassed-energy.png");
			スキル[SkillType::デバフ].Load("File/game_icons/stoned-skull.png");
			スキル[SkillType::探索].Load("File/game_icons/tread.png");
			スキル[SkillType::製造].Load("File/game_icons/anvil.png");
			スキル[SkillType::素材].Load("File/game_icons/mining.png");
			スキル[SkillType::STR].Load("File/game_icons/fist.png");
			スキル[SkillType::DEX].Load("File/game_icons/juggler.png");
			スキル[SkillType::INT].Load("File/game_icons/white-book.png");
			スキル[SkillType::VIT].Load("File/game_icons/muscle-fat.png");//HP
			スキル[SkillType::AGI].Load("File/game_icons/sprint.png");
			スキル[SkillType::その他].Load("File/game_icons/talk.png");

			装備種[ItemType::剣].Load("File/game_icons/plain-dagger.png");
			装備種[ItemType::斧].Load("File/game_icons/battle-axe.png");
			装備種[ItemType::槌].Load("File/game_icons/flanged-mace.png");
			装備種[ItemType::盾].Load("File/game_icons/checked-shield.png");
			装備種[ItemType::刺剣].Load("File/game_icons/stiletto.png");
			装備種[ItemType::槍].Load("File/game_icons/trident.png");
			装備種[ItemType::弓].Load("File/game_icons/pocket-bow.png");
			装備種[ItemType::銃].Load("File/game_icons/winchester-rifle.png");
			装備種[ItemType::魔杖].Load("File/game_icons/orb-wand.png");
			装備種[ItemType::骨杖].Load("File/game_icons/skull-staff.png");
			装備種[ItemType::神杖].Load("File/game_icons/wizard-staff.png");
			装備種[ItemType::祝杖].Load("File/game_icons/lunar-wand.png");

			装備種[ItemType::重鎧].Load("File/game_icons/breastplate.png");
			装備種[ItemType::軽鎧].Load("File/game_icons/leather-armor.png");
			装備種[ItemType::隠鎧].Load("File/game_icons/robe.png");
			装備種[ItemType::力鎧].Load("File/game_icons/Plastron.png");
			装備種[ItemType::技鎧].Load("File/game_icons/Mail shirt.png");
			装備種[ItemType::知鎧].Load("File/game_icons/Ninja armor.png");

			装備種[ItemType::すべて].Load("File/game_icons/talk.png");

			
			ステータス種[StatusType::Str].Load("File/game_icons/fist.png");
			ステータス種[StatusType::Dex].Load("File/game_icons/juggler.png");
			ステータス種[StatusType::Int].Load("File/game_icons/white-book.png");
			ステータス種[StatusType::Vit].Load("File/game_icons/muscle-fat.png");
			ステータス種[StatusType::Agi].Load("File/game_icons/sprint.png");

			static Image img_emote;
			img_emote.Load("File/system/emo.png");

			エモート[EmoteType::ビックリ].Copy(img_emote, { 0,0,14,18 });
			エモート[EmoteType::音符].Copy(img_emote, { 14,0,14,18 });
			エモート[EmoteType::困惑].Copy(img_emote, { 14*2,0,14,18 });
			エモート[EmoteType::はてな].Copy(img_emote, { 14*3,0,14,18 });
			エモート[EmoteType::汗].Copy(img_emote, { 14*4,0,14,18 });
			エモート[EmoteType::眠り].Copy(img_emote, { 14*5,0,14,18 });
			エモート[EmoteType::怒り].Copy(img_emote, { 0,18,14,18 });
			エモート[EmoteType::ハート].Copy(img_emote, { 14,18,14,18 });
			エモート[EmoteType::ドクロ].Copy(img_emote, { 14*2,18,14,18 });
			エモート[EmoteType::３点].Copy(img_emote, { 14*3,18,14,18 });
			エモート[EmoteType::２点].Copy(img_emote, { 14*4,18,14,18 });
			エモート[EmoteType::１点].Copy(img_emote, { 14*5,18,14,18 });
		}
	}

	//UI等のシステム画像
	namespace MSystem
	{
		ImagePack ウィンドウ枠;
		Image 背景;

		static void Load()
		{
			ウィンドウ枠.Load("File/system/window_skin.png", 60, 10, 6);
			背景.Load("File/system/back4.png");
		}

		/*立体が＋なら飛び出す、マイナスならへこむ*/
		static void DrawWindow(Point 座標, double 横幅, double 縦幅, int 枠No, int 立体 = 0)
		{
			if (立体 != 0)
			{
				Drawing::Rect({ 座標.x,座標.y,横幅 ,縦幅 }, Color::Black);
				if (立体 < 0)
				{
					
					座標.x -= 立体;
					座標.y -= 立体;
					横幅 += 立体;
					縦幅 += 立体;

				} else {
					横幅 -= 立体;
					縦幅 -= 立体;
					//Drawing::Rect({ 座標.x+立体,座標.y + 立体,横幅,縦幅 }, Color::Black);
				}
			}

			ウィンドウ枠[枠No]->DrawPart(座標, { 0,0,10,10 });//左上
			ウィンドウ枠[枠No]->DrawPart({ 座標.x + 横幅 - 10 , 座標.y }, { 20, 0,10,10 });//右上
			ウィンドウ枠[枠No]->DrawPart({ 座標.x , 座標.y + 縦幅 - 10 }, {  0,20,10,10 });//左下
			ウィンドウ枠[枠No]->DrawPart({ 座標.x + 横幅 - 10 , 座標.y + 縦幅 - 10 }, { 20,20,10,10 });//右下

			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y             , 横幅-20 , 10}, { 10,0,10,10 });//上
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y + 縦幅 - 10 , 横幅-20 , 10}, { 10,20,10,10 });//下
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x      , 座標.y + 10        , 10 , 縦幅 - 20}, { 0,10,10,10 });//左
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 横幅 - 10 , 座標.y + 10 , 10 , 縦幅 - 20}, { 20,10,10,10 });//右

			//内部
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y + 10 , 横幅 - 20 , 縦幅 - 20 }, { 10,10,10,10 });//右

		}

		static void DrawBox(const Point &座標, const int 横幅, const int 縦幅,const Color &色)
		{
			Drawing::Rect(Rect(座標.x + 1, 座標.y, 横幅 - 2, 縦幅), 色);
			Drawing::Rect(Rect(座標.x , 座標.y+1, 横幅 , 縦幅-2), 色);
		}

		static void DrawBoxBold(const Point &座標, const int 横幅, const int 縦幅, const Color &色,int 枠太さ , const Color&枠色)
		{
			Drawing::Rect(Rect(座標.x + 1, 座標.y, 横幅 - 2, 縦幅), 枠色);
			Drawing::Rect(Rect(座標.x, 座標.y + 1, 横幅, 縦幅 - 2), 枠色);
			Drawing::Rect(Rect(座標.x + 1 +枠太さ, 座標.y + 枠太さ, 横幅 - 2 - 枠太さ*2, 縦幅 - 枠太さ * 2), 色);
			Drawing::Rect(Rect(座標.x + 枠太さ, 座標.y + 1 + 枠太さ, 横幅 - 枠太さ * 2, 縦幅 - 2 - 枠太さ * 2), 色);
		}
	
		static void DrawBar(const Point &座標, const int 横幅, const int 縦幅, double 割合, int 枠太さ, const Color &色, const Color&枠色, const Color&中色 , bool is左側)
		{
			割合 = std::max(0.0, 割合);
			割合 = std::min(1.0, 割合);

			DrawBoxBold(座標, 横幅, 縦幅, 中色, 枠太さ, 枠色);
			int ww = int((横幅 - 枠太さ * 2) * 割合);
			int hh = 縦幅 - 枠太さ * 2;

			if (割合 <= 0.0 || ww < 1)
			{
				return;
			}

			if (is左側)
			{
				DrawBox({座標.x+枠太さ,座標.y+枠太さ},ww,hh,色);
			} else {
				DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 色);
			}
		}
	
		static void DrawSkill(SkillType スキル種, const Point &座標, Color 色)
		{
			Drawing::Rect({ 座標.x ,座標.y ,29,29 }, 色, true);
			Drawing::Rect({ 座標.x + 1,座標.y +1,27,27 }, Color::White, true);
			Drawing::Rect({ 座標.x + 2,座標.y + 2 ,25,25 }, 色, true);

			MIcon::スキル[スキル種].Draw({ 座標.x + 2,座標.y+2 });
		}

	}

	//文字データ
	namespace MFont
	{
		//SystemFont::UI_Gothic
		Font Arial小;
		Font Arial中;
		Font Arial大;

		Font BArial小;
		Font BArial中;
		Font BArial大;

		//meiryo.ttc
		Font メイリオ小;
		Font メイリオ中;
		Font メイリオ大;
		Font Bメイリオ小;
		Font Bメイリオ中;
		Font Bメイリオ大;

		ImagePack 白数字;
		ImagePack 黒数字;
		ImagePack 英数字;

		static void Load()
		{
			std::string f1 = "File/font/NotoSans-Regular.ttf";
			std::string f1b = "File/font/NotoSans-Bold.ttf";
			std::string f2 = "File/font/mplus-1m-Regular.ttf";
			std::string f2b = "File/font/mplus-1m-Bold.ttf";
			f1 = "File/font/mplus-1m-Regular.ttf";
			f1b = "File/font/mplus-1m-Bold.ttf";
			bool iszeroswap = true;

			Arial小.Load(f1.c_str(), 12);
			Arial中.Load(f1.c_str(), 18);
			Arial大.Load(f1.c_str(), 24);
			BArial小.Load(f1b.c_str(), 12);
			BArial中.Load(f1b.c_str(), 18);
			BArial大.Load(f1b.c_str(), 24);
			メイリオ小.Load(f2.c_str(), 12);
			メイリオ中.Load(f2.c_str(), 18);
			メイリオ大.Load(f2.c_str(), 24);
			Bメイリオ小.Load(f2b.c_str(), 12);
			Bメイリオ中.Load(f2b.c_str(), 18);
			Bメイリオ大.Load(f2b.c_str(), 24);

			if (iszeroswap)
			{
				Arial小.SetImage("0", Arial小.GetImage("O"));
				Arial中.SetImage("0", Arial中.GetImage("O"));
				Arial大.SetImage("0", Arial大.GetImage("O"));
				BArial小.SetImage("0", BArial小.GetImage("O"));
				BArial中.SetImage("0", BArial中.GetImage("O"));
				BArial大.SetImage("0", BArial大.GetImage("O"));

				メイリオ小.SetImage("0", メイリオ小.GetImage("O"));
				メイリオ中.SetImage("0", メイリオ中.GetImage("O"));
				メイリオ大.SetImage("0", メイリオ大.GetImage("O"));
				Bメイリオ小.SetImage("0", Bメイリオ小.GetImage("O"));
				Bメイリオ中.SetImage("0", Bメイリオ中.GetImage("O"));
				Bメイリオ大.SetImage("0", Bメイリオ大.GetImage("O"));
			}
		}
	}

	//BGM
	namespace MMusic
	{
		Music 戦闘中;
		Music 敗北;
		Music 戦闘開始;
		Music 内政中;
		Music 勝利;

		static void Load()
		{
			戦闘中.Load("file/music/c18.mp3");
			敗北.Load("file/music/c18.mp3");
			戦闘開始.Load("file/music/c18.mp3");
			内政中.Load("file/music/c18.mp3");
			勝利.Load("file/music/c18.mp3");
		}
	}

	//効果音
	namespace MSound
	{
		EnumArray<Sound, SEType> 効果音;

		static void Load()
		{
			効果音[SEType::決定].Load("file/sound/coin04.wav");
		}
	}

	//全読み込み
	static void LoadMaterial()
	{
		MFont::Load();

		//Loading::Start();

		MUnit::Load();
		MIcon::Load();
		MSystem::Load();

		MMusic::Load();
		MSound::Load();

		//Loading::End();

		//非同期読み込み完了確認
		while (System::Update())
		{
			if (Loading::GetLoadingCount() == Loading::GetSuccesCount()) break;			
		}
	}
}