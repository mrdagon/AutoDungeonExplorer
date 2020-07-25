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
			ユニット[UnitImageType::ゴブリン].Load("file/unit/unit001.png", 12, 3, 4);
			ユニット[UnitImageType::青ゴブリン].Load("file/unit/unit002.png", 12, 3, 4);
			ユニット[UnitImageType::犬].Load("file/unit/unit003.png", 12, 3, 4);
			ユニット[UnitImageType::青犬].Load("file/unit/unit004.png", 12, 3, 4);
			ユニット[UnitImageType::白猫].Load("file/unit/unit005.png", 12, 3, 4);
			ユニット[UnitImageType::黒猫].Load("file/unit/unit006.png", 12, 3, 4);
			ユニット[UnitImageType::兵士].Load("file/unit/unit007.png", 12, 3, 4);
			ユニット[UnitImageType::赤兵士].Load("file/unit/unit008.png", 12, 3, 4);
			ユニット[UnitImageType::青兵士].Load("file/unit/unit009.png", 12, 3, 4);
			ユニット[UnitImageType::メイド].Load("file/unit/unit010.png", 12, 3, 4);
			ユニット[UnitImageType::ハゲ].Load("file/unit/unit011.png", 12, 3, 4);
			ユニット[UnitImageType::執事].Load("file/unit/unit012.png", 12, 3, 4);
			ユニット[UnitImageType::王].Load("file/unit/unit013.png", 12, 3, 4);
			ユニット[UnitImageType::青王].Load("file/unit/unit014.png", 12, 3, 4);
			ユニット[UnitImageType::王妃].Load("file/unit/unit015.png", 12, 3, 4);
			ユニット[UnitImageType::青王妃].Load("file/unit/unit016.png", 12, 3, 4);
			ユニット[UnitImageType::赤王妃].Load("file/unit/unit017.png", 12, 3, 4);
			ユニット[UnitImageType::小王子].Load("file/unit/unit018.png", 12, 3, 4);
			ユニット[UnitImageType::小姫].Load("file/unit/unit019.png", 12, 3, 4);
			ユニット[UnitImageType::王子].Load("file/unit/unit020.png", 12, 3, 4);
			ユニット[UnitImageType::姫].Load("file/unit/unit023.png", 12, 3, 4);
			ユニット[UnitImageType::ドワーフ].Load("file/unit/unit024.png", 12, 3, 4);
			ユニット[UnitImageType::子ドワーフ].Load("file/unit/unit027.png", 12, 3, 4);
			ユニット[UnitImageType::茶女性].Load("file/unit/unit028.png", 12, 3, 4);
			ユニット[UnitImageType::青女性].Load("file/unit/unit029.png", 12, 3, 4);
			ユニット[UnitImageType::金女性].Load("file/unit/unit031.png", 12, 3, 4);
			ユニット[UnitImageType::緑女性].Load("file/unit/unit033.png", 12, 3, 4);
			ユニット[UnitImageType::茶村人].Load("file/unit/unit030.png", 12, 3, 4);
			ユニット[UnitImageType::金村人].Load("file/unit/unit032.png", 12, 3, 4);
			ユニット[UnitImageType::金子供].Load("file/unit/unit034.png", 12, 3, 4);
			ユニット[UnitImageType::三つ編み].Load("file/unit/unit035.png", 12, 3, 4);
			ユニット[UnitImageType::少年].Load("file/unit/unit036.png", 12, 3, 4);
			ユニット[UnitImageType::少女].Load("file/unit/unit037.png", 12, 3, 4);
			ユニット[UnitImageType::緑防止].Load("file/unit/unit038.png", 12, 3, 4);
			ユニット[UnitImageType::おっさん].Load("file/unit/unit039.png", 12, 3, 4);
			ユニット[UnitImageType::半裸].Load("file/unit/unit040.png", 12, 3, 4);
			ユニット[UnitImageType::青オーク].Load("file/unit/unit041.png", 12, 3, 4);
			ユニット[UnitImageType::赤オーク].Load("file/unit/unit042.png", 12, 3, 4);
			ユニット[UnitImageType::おばさん].Load("file/unit/unit043.png", 12, 3, 4);
			ユニット[UnitImageType::おばあさん].Load("file/unit/unit044.png", 12, 3, 4);
			ユニット[UnitImageType::おじいさん].Load("file/unit/unit045.png", 12, 3, 4);
			ユニット[UnitImageType::勇者].Load("file/unit/unit048.png", 12, 3, 4);
			ユニット[UnitImageType::闘士].Load("file/unit/unit050.png", 12, 3, 4);
			ユニット[UnitImageType::弓士].Load("file/unit/unit053.png", 12, 3, 4);
			ユニット[UnitImageType::剣聖].Load("file/unit/unit055.png", 12, 3, 4);
			ユニット[UnitImageType::武術家].Load("file/unit/unit057.png", 12, 3, 4);
			ユニット[UnitImageType::魔女].Load("file/unit/unit059.png", 12, 3, 4);
			ユニット[UnitImageType::精霊].Load("file/unit/unit062.png", 12, 3, 4);
			ユニット[UnitImageType::くの一].Load("file/unit/unit063.png", 12, 3, 4);
			ユニット[UnitImageType::盗賊].Load("file/unit/unit065.png", 12, 3, 4);
			ユニット[UnitImageType::レンジャー].Load("file/unit/unit066.png", 12, 3, 4);
			ユニット[UnitImageType::妖術師].Load("file/unit/unit068.png", 12, 3, 4);
			ユニット[UnitImageType::大魔導師].Load("file/unit/unit070.png", 12, 3, 4);
			ユニット[UnitImageType::族長].Load("file/unit/unit071.png", 12, 3, 4);
			ユニット[UnitImageType::空手家].Load("file/unit/unit073.png", 12, 3, 4);
			ユニット[UnitImageType::戦士].Load("file/unit/unit075.png", 12, 3, 4);
			ユニット[UnitImageType::戦士2].Load("file/unit/unit077.png", 12, 3, 4);
			ユニット[UnitImageType::重装].Load("file/unit/unit078.png", 12, 3, 4);
			ユニット[UnitImageType::柔術家].Load("file/unit/unit080.png", 12, 3, 4);
			ユニット[UnitImageType::呪術師].Load("file/unit/unit082.png", 12, 3, 4);
			ユニット[UnitImageType::暗殺者].Load("file/unit/unit087.png", 12, 3, 4);
			ユニット[UnitImageType::傭兵].Load("file/unit/unit090.png", 12, 3, 4);
			ユニット[UnitImageType::老兵].Load("file/unit/unit093.png", 12, 3, 4);
			ユニット[UnitImageType::戦士3].Load("file/unit/unit094.png", 12, 3, 4);
			ユニット[UnitImageType::騎士].Load("file/unit/unit097.png", 12, 3, 4);
			ユニット[UnitImageType::司祭].Load("file/unit/unit099.png", 12, 3, 4);

			ユニット[UnitImageType::スライム].Load("file/monster/mon000.png", 12, 3, 4);
			ユニット[UnitImageType::赤スライム].Load("file/monster/mon001.png", 12, 3, 4);
			ユニット[UnitImageType::狼].Load("file/monster/mon002.png", 12, 3, 4);
			ユニット[UnitImageType::青狼].Load("file/monster/mon003.png", 12, 3, 4);
			ユニット[UnitImageType::三頭犬].Load("file/monster/mon004.png", 12, 3, 4);
			ユニット[UnitImageType::スケルトン].Load("file/monster/mon005.png", 12, 3, 4);
			ユニット[UnitImageType::サハギン].Load("file/monster/mon006.png", 12, 3, 4);
			ユニット[UnitImageType::インプ].Load("file/monster/mon007.png", 12, 3, 4);
			ユニット[UnitImageType::トレント].Load("file/monster/mon008.png", 12, 3, 4);
			ユニット[UnitImageType::グリフィン].Load("file/monster/mon009.png", 12, 3, 4);
			ユニット[UnitImageType::ドラゴン].Load("file/monster/mon010.png", 12, 3, 4);

		}
	}

	//武器、防具、その他のアイコン
	namespace MIcon
	{
		EnumArray<Image, ItemImageType> アイテム;
		EnumArray<Image, IconType> アイコン;
		EnumArray<Image, EmoteType> エモート;
		EnumArray<Image, SkillType> スキル;
		EnumArray<Image, ItemType> 装備種;
		EnumArray<Image, StatusType> ステータス種;

		static void LoadIcon()
		{
			//UI汎用
			アイコン[IconType::閉じる].Load("file/icon/tojiru.png");
			アイコン[IconType::資金].Load("file/icon/sikin.png");
			アイコン[IconType::三角].Load("file/icon/sankaku.png");
			アイコン[IconType::製造力].Load("file/icon/seizouryoku.png");
			アイコン[IconType::製造力].Load("file/icon/kanryou.png");
			アイコン[IconType::ランク].Load("file/icon/rank.png");
			//各種ウィンドウアイコン
			アイコン[IconType::装備].Load("file/icon/item.png");
			アイコン[IconType::製造].Load("file/icon/seizou.png");
			アイコン[IconType::迷宮].Load("file/icon/dungeon.png");
			アイコン[IconType::編成].Load("file/icon/hensei.png");
			アイコン[IconType::求人].Load("file/icon/kyuujin.png");
			アイコン[IconType::戦略].Load("file/icon/senryaku.png");
			アイコン[IconType::素材].Load("file/icon/sozai.png");
			アイコン[IconType::依頼].Load("file/icon/irai.png");
			アイコン[IconType::情報].Load("file/icon/jyouhou.png");
			アイコン[IconType::ログ].Load("file/icon/log.png");

			アイコン[IconType::全て].Load("file/icon/all.png");
			アイコン[IconType::ボス].Load("file/icon/boss.png");
			アイコン[IconType::地図].Load("file/icon/tizu.png");
			アイコン[IconType::宝箱].Load("file/icon/takarabako.png");
			アイコン[IconType::更新].Load("file/icon/kousin.png");

			アイコン[IconType::再募集].Load("file/icon/saibosyuu.png");
				
			アイコン[IconType::メインクエ].Load("file/icon/mainquest.png");//
			アイコン[IconType::サブクエ].Load("file/icon/subquest.png");//
			アイコン[IconType::名声].Load("file/icon/meisei.png");

			アイコン[IconType::集客].Load("file/icon/raikyaku.png");
			アイコン[IconType::開発].Load("file/icon/kaihatu.png");
			アイコン[IconType::撤退].Load("file/icon/.png");//

			アイコン[IconType::解像度].Load("file/icon/kaizoudo.png");
			アイコン[IconType::BGM].Load("file/icon/bgm.png");
			アイコン[IconType::効果音].Load("file/icon/koukaon.png");

			アイコン[IconType::New].Load("file/icon/new.png");

			//素材
			アイコン[IconType::鉄材].Load("file/system/mat_001.png");
			アイコン[IconType::木材].Load("file/system/mat_002.png");
			アイコン[IconType::皮材].Load("file/system/mat_003.png");
			アイコン[IconType::骨材].Load("file/system/mat_004.png");

			//上部分バー
			アイコン[IconType::日付].Load("file/icon/hiduke.png");
			アイコン[IconType::時間].Load("file/icon/jikan.png");
			アイコン[IconType::人口].Load("file/icon/jinkou.png");
			アイコン[IconType::ヘルプ].Load("file/icon/help.png");
			アイコン[IconType::停止].Load("file/icon/teisi.png");
			アイコン[IconType::速度].Load("file/icon/sokudo.png");
			アイコン[IconType::設定].Load("file/icon/settei.png");
			アイコン[IconType::終了].Load("file/icon/deguti.png");
		}

		static void LoadOther()
		{
			//武器-防具
			アイテム[ItemImageType::鉄の剣].Load("file/wepon/wepon215.png");
			アイテム[ItemImageType::鉄の斧].Load("file/wepon/wepon004.png");
			アイテム[ItemImageType::木の弓].Load("file/wepon/wepon058.png");
			アイテム[ItemImageType::スタッフ].Load("file/wepon/wepon201.png");
			アイテム[ItemImageType::ワンド].Load("file/wepon/wepon165.png");
			アイテム[ItemImageType::鉄の盾].Load("file/wepon/mat_018.png");
			アイテム[ItemImageType::鉄の鎧].Load("file/armor/armor006.png");
			アイテム[ItemImageType::鎖帷子].Load("file/armor/armor016.png");
			アイテム[ItemImageType::皮のローブ].Load("file/armor/armor066.png");
			アイテム[ItemImageType::アクセサリ].Load("file/accessory/boots_007.png");
			//素材

			アイコン[IconType::城].Load("file/system/move_00.png");
			アイコン[IconType::森].Load("file/system/move_01.png");
			アイコン[IconType::洞窟].Load("file/system/move_02.png");
			アイコン[IconType::砂漠].Load("file/system/move_03.png");
			アイコン[IconType::山].Load("file/system/move_04.png");
			アイコン[IconType::滝].Load("file/system/move_05.png");
			アイコン[IconType::塔].Load("file/system/move_06.png");
			アイコン[IconType::廃墟].Load("file/system/move_07.png");

			スキル[SkillType::剣].Load("file/game_icons/plain-dagger.png");
			スキル[SkillType::斧].Load("file/game_icons/battle-axe.png");
			スキル[SkillType::槌].Load("file/game_icons/flanged-mace.png");
			スキル[SkillType::盾].Load("file/game_icons/checked-shield.png");
			スキル[SkillType::刺剣].Load("file/game_icons/stiletto.png");
			スキル[SkillType::槍].Load("file/game_icons/trident.png");
			スキル[SkillType::弓].Load("file/game_icons/pocket-bow.png");
			スキル[SkillType::銃].Load("file/game_icons/winchester-rifle.png");
			スキル[SkillType::魔杖].Load("file/game_icons/orb-wand.png");
			スキル[SkillType::骨杖].Load("file/game_icons/skull-staff.png");
			スキル[SkillType::神杖].Load("file/game_icons/wizard-staff.png");
			スキル[SkillType::祝杖].Load("file/game_icons/lunar-wand.png");
			スキル[SkillType::鎧].Load("file/game_icons/breastplate.png");
			スキル[SkillType::革鎧].Load("file/game_icons/leather-armor.png");
			スキル[SkillType::ローブ].Load("file/game_icons/robe.png");
			スキル[SkillType::挑発].Load("file/game_icons/arrows-shield.png");
			スキル[SkillType::隠密].Load("file/game_icons/invisible.png");
			スキル[SkillType::防御].Load("file/game_icons/shield-reflect.png");
			スキル[SkillType::回避].Load("file/game_icons/dodging.png");
			スキル[SkillType::魔防].Load("file/game_icons/shield-bash.png");//-消して庇う
			スキル[SkillType::回復].Load("file/game_icons/healing.png");
			スキル[SkillType::攻撃].Load("file/game_icons/saber-slash.png");
			スキル[SkillType::バフ].Load("file/game_icons/embrassed-energy.png");
			スキル[SkillType::デバフ].Load("file/game_icons/stoned-skull.png");
			スキル[SkillType::探索].Load("file/game_icons/tread.png");
			スキル[SkillType::製造].Load("file/game_icons/anvil.png");
			スキル[SkillType::素材].Load("file/game_icons/mining.png");
			スキル[SkillType::STR].Load("file/game_icons/fist.png");
			スキル[SkillType::DEX].Load("file/game_icons/juggler.png");
			スキル[SkillType::INT].Load("file/game_icons/white-book.png");
			スキル[SkillType::その他].Load("file/game_icons/talk.png");

			装備種[ItemType::剣].Load("file/game_icons/plain-dagger.png");
			装備種[ItemType::斧].Load("file/game_icons/battle-axe.png");
			装備種[ItemType::槌].Load("file/game_icons/flanged-mace.png");
			装備種[ItemType::盾].Load("file/game_icons/checked-shield.png");
			装備種[ItemType::刺剣].Load("file/game_icons/stiletto.png");
			装備種[ItemType::槍].Load("file/game_icons/trident.png");
			装備種[ItemType::弓].Load("file/game_icons/pocket-bow.png");
			装備種[ItemType::銃].Load("file/game_icons/winchester-rifle.png");
			装備種[ItemType::魔杖].Load("file/game_icons/orb-wand.png");
			装備種[ItemType::骨杖].Load("file/game_icons/skull-staff.png");
			装備種[ItemType::神杖].Load("file/game_icons/wizard-staff.png");
			装備種[ItemType::祝杖].Load("file/game_icons/lunar-wand.png");

			装備種[ItemType::重鎧].Load("file/game_icons/breastplate.png");
			装備種[ItemType::軽鎧].Load("file/game_icons/leather-armor.png");
			装備種[ItemType::隠鎧].Load("file/game_icons/robe.png");
			装備種[ItemType::力鎧].Load("file/game_icons/Plastron.png");
			装備種[ItemType::技鎧].Load("file/game_icons/Mail shirt.png");
			装備種[ItemType::知鎧].Load("file/game_icons/Ninja armor.png");

			装備種[ItemType::すべて].Load("file/game_icons/talk.png");


			ステータス種[StatusType::Str].Load("file/game_icons/fist.png");
			ステータス種[StatusType::Dex].Load("file/game_icons/juggler.png");
			ステータス種[StatusType::Int].Load("file/game_icons/white-book.png");

			static Image img_emote;
			img_emote.Load("file/system/emo.png");

			エモート[EmoteType::ビックリ].Copy(img_emote, { 0,0,14,18 });
			エモート[EmoteType::音符].Copy(img_emote, { 14,0,14,18 });
			エモート[EmoteType::困惑].Copy(img_emote, { 14 * 2,0,14,18 });
			エモート[EmoteType::はてな].Copy(img_emote, { 14 * 3,0,14,18 });
			エモート[EmoteType::汗].Copy(img_emote, { 14 * 4,0,14,18 });
			エモート[EmoteType::眠り].Copy(img_emote, { 14 * 5,0,14,18 });
			エモート[EmoteType::怒り].Copy(img_emote, { 0,18,14,18 });
			エモート[EmoteType::ハート].Copy(img_emote, { 14,18,14,18 });
			エモート[EmoteType::ドクロ].Copy(img_emote, { 14 * 2,18,14,18 });
			エモート[EmoteType::３点].Copy(img_emote, { 14 * 3,18,14,18 });
			エモート[EmoteType::２点].Copy(img_emote, { 14 * 4,18,14,18 });
			エモート[EmoteType::１点].Copy(img_emote, { 14 * 5,18,14,18 });
		}

		static void Load()
		{
			LoadIcon();
			LoadOther();
		}
	}

	//文字データ
	namespace MFont
	{
		Font SSize;
		Font MSize;
		Font LSize;

		Font BSSize;
		Font BMSize;
		Font BLSize;

		static void Load()
		{
			//std::string f1 = "file/font/NotoSans-Regular.ttf";
			//std::string f1b = "file/font/NotoSans-Bold.ttf";
			std::string f1 = "file/font/mplus-1m-Regular.ttf";
			std::string f1b = "file/font/mplus-1m-Bold.ttf";
			//f1 = "file/font/mplus-1m-Regular.ttf";
			//f1b = "file/font/mplus-1m-Bold.ttf";
			bool iszeroswap = true;

			SSize.Load(f1.c_str(), 14);
			MSize.Load(f1.c_str(), 18);
			LSize.Load(f1.c_str(), 24);
			BSSize.Load(f1b.c_str(), 14);
			BMSize.Load(f1b.c_str(), 18);
			BLSize.Load(f1b.c_str(), 24);

			if (iszeroswap)
			{
				SSize.SetImage("0", SSize.GetImage("O"));
				MSize.SetImage("0", MSize.GetImage("O"));
				LSize.SetImage("0", LSize.GetImage("O"));
				BSSize.SetImage("0", BSSize.GetImage("O"));
				BMSize.SetImage("0", BMSize.GetImage("O"));
				BLSize.SetImage("0", BLSize.GetImage("O"));
			}
		}
	}

	//戦闘エフェクト
	namespace MEffect
	{
		EnumArray<ImagePack, EffectType> エフェクト;

		static void Load()
		{
			エフェクト[EffectType::斬].Load("file/effect/pipo-btleffect001.png", 5, 5, 1);
			エフェクト[EffectType::打].Load("file/effect/pipo-btleffect002.png", 9, 9, 1);
			エフェクト[EffectType::突].Load("file/effect/pipo-btleffect006_.png", 7, 7, 1);
			エフェクト[EffectType::炎].Load("file/effect/pipo-btleffect024.png", 8, 8, 1);
			エフェクト[EffectType::雷].Load("file/effect/pipo-btleffect027.png", 8, 8, 1);
			エフェクト[EffectType::氷].Load("file/effect/pipo-btleffect029.png", 8, 8, 1);
			エフェクト[EffectType::バフ].Load("file/effect/pipo-btleffect019.png", 10, 10, 1);
			エフェクト[EffectType::デバフ].Load("file/effect/pipo-btleffect020.png", 10, 10, 1);
			エフェクト[EffectType::回復].Load("file/effect/pipo-btleffect045.png", 10, 10, 1);
			エフェクト[EffectType::異常].Load("file/effect/pipo-btleffect017.png", 8, 8, 1);
			エフェクト[EffectType::爪].Load("file/effect/pipo-btleffect121.png", 8, 5, 2);
			エフェクト[EffectType::牙].Load("file/effect/pipo-btleffect122.png", 8, 5, 2);
		}
	}

	//職業立ち絵
	namespace MJob
	{
		EnumArray<Image, JobType> 立ち絵;

		static void Load()
		{
			立ち絵[JobType::ガーディアン].Load("file/job/BR97.png");
			立ち絵[JobType::グラディエーター].Load("file/job/BR40.png");
			立ち絵[JobType::カートグラファ].Load("file/job/BR223.png");
			立ち絵[JobType::メディック].Load("file/job/BR99.png");
			立ち絵[JobType::ミスティック].Load("file/job/BR122.png");
			立ち絵[JobType::オカルティスト].Load("file/job/BR42.png");
			立ち絵[JobType::バーサーカー].Load("file/job/BR113.png");
			立ち絵[JobType::スレイヤー].Load("file/job/BR16.png");
			立ち絵[JobType::シノビ].Load("file/job/BR200.png");
			立ち絵[JobType::デッドアイ].Load("file/job/BR92.png");
			立ち絵[JobType::エレメンタリスト].Load("file/job/BR207.png");
			立ち絵[JobType::トリックスター].Load("file/job/BR44.png");
		}
	}

	//BGM
	namespace MMusic
	{
		EnumArray<Music, BGMType> BGM;


		static void Load()
		{
			BGM[BGMType::準備中].Load("file/music/furattoguild.mp3");
			BGM[BGMType::探検中].Load("file/music/komichiwokakenukete.mp3");
			BGM[BGMType::通常ボス].Load("file/music/kinokomonchaku.mp3");
			BGM[BGMType::エリアボス].Load("file/music/wazawainobisyu.mp3");
			BGM[BGMType::タイトル].Load("file/music/furattoguild.mp3");


			for (auto& it : BGM)
			{
				it.SetFadeInTime(500);
				it.SetFadeOutTime(500);
			}

		}
	}

	//効果音
	namespace MSound
	{
		EnumArray<Sound, SEType> 効果音;

		static void Load()
		{
			効果音[SEType::決定].Load("file/sound/cursor05.wav");
			効果音[SEType::キャンセル].Load("file/sound/cursor01.wav");
			効果音[SEType::ボタン押].Load("file/sound/kachi05.wav");
			効果音[SEType::タブ押].Load("file/sound/paper00.wav");
			効果音[SEType::掴む].Load("file/sound/kachi11.wav");
			効果音[SEType::装着].Load("file/sound/weapon00.wav");
			効果音[SEType::投資].Load("file/sound/coin05.wav");
			//内政効果音
			効果音[SEType::クエスト完了].Load("file/sound/metal35.wav");
			効果音[SEType::製造].Load("file/sound/metal14.wav");
			効果音[SEType::新製造].Load("file/sound/metal28.wav");
			効果音[SEType::内政Lv].Load("file/sound/power22.wav");
			効果音[SEType::販売].Load("file/sound/coin01.wav");

			//戦闘探索効果音
			効果音[SEType::地図発見].Load("file/sound/bell03.wav");
			効果音[SEType::ボス発見].Load("file/sound/unari00.wav");
			効果音[SEType::探索開始].Load("file/sound/step00.wav");
			効果音[SEType::探索終了].Load("file/sound/step04.wav");

			//伐採 wood05
			//採掘 metal18

			効果音[SEType::攻撃].Load("file/sound/hit17.wav");
			効果音[SEType::回復].Load("file/sound/pyoro42.wav");
			効果音[SEType::補助].Load("file/sound/power05.wav");

			効果音[SEType::味方気絶].Load("file/sound/voice004.wav");
			効果音[SEType::敵気絶].Load("file/sound/voice005.wav");
			効果音[SEType::全滅].Load("file/sound/voice017.wav");
		}
	}

	//UI等のシステム画像
	//後でライブラリに追加する候補？
	namespace MSystem
	{
		ImagePack ウィンドウ枠;
		Image 背景;
		Image ダンジョン背景[5];
		EnumArray<Image, CraftType> クラフト台;

		static void Load()
		{
			ウィンドウ枠.Load("file/system/window_skin.png", 60, 10, 6);
			背景.Load("file/system/town02.png");
			ダンジョン背景[0].Load("file/system/dunback00.png");
			ダンジョン背景[1].Load("file/system/dunback01.png");
			ダンジョン背景[2].Load("file/system/facback.png");

			クラフト台[CraftType::鍛造].Load("file/system/craft00.png");
			クラフト台[CraftType::裁縫].Load("file/system/craft01.png");
			クラフト台[CraftType::木工].Load("file/system/craft02.png");
			クラフト台[CraftType::魔術].Load("file/system/craft03.png");
		}

		/*立体が＋なら飛び出す、マイナスならへこむ*/
		static void DrawWindow(Point 座標, double 横幅, double 縦幅, int 枠No, int 立体 = 0 , int 透過率 = 255)
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

				}
				else {
					横幅 -= 立体;
					縦幅 -= 立体;
					//Drawing::Rect({ 座標.x+立体,座標.y + 立体,横幅,縦幅 }, Color::Black);
				}
			}

			if (透過率 < 255)
			{
				Screen::SetBlendMode(BlendMode::Alpha, 透過率);
			}

			ウィンドウ枠[枠No]->DrawPart(座標, { 0,0,10,10 });//左上
			ウィンドウ枠[枠No]->DrawPart({ 座標.x + 横幅 - 10 , 座標.y }, { 20, 0,10,10 });//右上
			ウィンドウ枠[枠No]->DrawPart({ 座標.x , 座標.y + 縦幅 - 10 }, { 0,20,10,10 });//左下
			ウィンドウ枠[枠No]->DrawPart({ 座標.x + 横幅 - 10 , 座標.y + 縦幅 - 10 }, { 20,20,10,10 });//右下

			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y             , 横幅 - 20 , 10 }, { 10,0,10,10 });//上
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y + 縦幅 - 10 , 横幅 - 20 , 10 }, { 10,20,10,10 });//下
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x      , 座標.y + 10        , 10 , 縦幅 - 20 }, { 0,10,10,10 });//左
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 横幅 - 10 , 座標.y + 10 , 10 , 縦幅 - 20 }, { 20,10,10,10 });//右

			//内部
			ウィンドウ枠[枠No]->DrawPartExtend({ 座標.x + 10 , 座標.y + 10 , 横幅 - 20 , 縦幅 - 20 }, { 10,10,10,10 });//右

			if (透過率 < 255)
			{
				Screen::SetBlendMode(BlendMode::NoBlend);
			}
		}

		static void DrawBox(const Point& 座標, const int 横幅, const int 縦幅, const Color& 色)
		{
			Drawing::Rect(Rect(座標.x + 1, 座標.y, 横幅 - 2, 縦幅), 色);
			Drawing::Rect(Rect(座標.x, 座標.y + 1, 横幅, 縦幅 - 2), 色);
		}

		static void DrawBoxBold(const Point& 座標, const int 横幅, const int 縦幅, const Color& 色, int 枠太さ, const Color& 枠色)
		{
			Drawing::Rect(Rect(座標.x + 1, 座標.y, 横幅 - 2, 縦幅), 枠色);
			Drawing::Rect(Rect(座標.x, 座標.y + 1, 横幅, 縦幅 - 2), 枠色);
			Drawing::Rect(Rect(座標.x + 1 + 枠太さ, 座標.y + 枠太さ, 横幅 - 2 - 枠太さ * 2, 縦幅 - 枠太さ * 2), 色);
			Drawing::Rect(Rect(座標.x + 枠太さ, 座標.y + 1 + 枠太さ, 横幅 - 枠太さ * 2, 縦幅 - 2 - 枠太さ * 2), 色);
		}

		static void DrawBar(const Point& 座標, const int 横幅, const int 縦幅, double 割合, int 枠太さ, const Color& 色, const Color& 枠色, const Color& 中色, bool is左側)
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
				DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 色);
			}
			else {
				DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 色);
			}
		}

		static void DrawSkill(SkillType スキル種, const Point& 座標, Color 色, std::string messe = "")
		{
			Drawing::Rect({ 座標.x ,座標.y ,29,29 }, 色, true);
			Drawing::Rect({ 座標.x + 1,座標.y + 1,27,27 }, Color::White, true);
			Drawing::Rect({ 座標.x + 2,座標.y + 2 ,25,25 }, 色, true);

			MIcon::スキル[スキル種].Draw({ 座標.x + 2,座標.y + 2 });
			MFont::BSSize.DrawBold({ 座標.x + 2 , 座標.y + 12 }, Color::White, Color::Black, messe);
		}

		static void DrawCircleBar(Rect 座標, double ゲージ率, Color 表色, Color 裏色, double 太さ, double 裏太さ)
		{
			Point p1, p2, p3, p4, p5;
			p1.SetPos(座標.x, 座標.y);
			p2.SetPos(座標.x + 座標.GetW(), 座標.y);
			p3.SetPos(座標.x + 座標.GetW(), 座標.y + 座標.GetH());
			p4.SetPos(座標.x, 座標.y + 座標.GetH());
			p5 = p1;

			//裏色
			Drawing::Line(p1, p2, 裏色, (int)裏太さ);
			Drawing::Line(p2, p3, 裏色, (int)裏太さ);
			Drawing::Line(p3, p4, 裏色, (int)裏太さ);
			Drawing::Line(p4, p1, 裏色, (int)裏太さ);

			Drawing::Circle({ p1.x, p1.y, 裏太さ / 2 }, 裏色);
			Drawing::Circle({ p2.x, p2.y, 裏太さ / 2 }, 裏色);
			Drawing::Circle({ p3.x, p3.y, 裏太さ / 2 }, 裏色);
			Drawing::Circle({ p4.x, p4.y, 裏太さ / 2 }, 裏色);

			//表
			if (ゲージ率 == 0) { return; }

			if (ゲージ率 < 0.25)
			{
				p2.x = 座標.x + 座標.GetW() * ゲージ率 * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Circle({ p1.x, p1.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p2.x, p2.y, 太さ / 2 }, 表色);
			}
			else if (ゲージ率 < 0.5)
			{
				p3.y = 座標.y + 座標.GetH() * (ゲージ率 - 0.25) * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Line(p2, p3, 表色, (int)太さ);
				Drawing::Circle({ p1.x, p1.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p2.x, p2.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p3.x, p3.y, 太さ / 2 }, 表色);
			}
			else if (ゲージ率 < 0.75)
			{
				p4.x = 座標.x + 座標.GetW() - 座標.GetW() * (ゲージ率 - 0.5) * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Line(p2, p3, 表色, (int)太さ);
				Drawing::Line(p3, p4, 表色, (int)太さ);
				Drawing::Circle({ p1.x, p1.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p2.x, p2.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p3.x, p3.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p4.x, p4.y, 太さ / 2 }, 表色);
			}
			else
			{
				p5.y = 座標.y + 座標.GetH() - 座標.GetH() * (ゲージ率 - 0.75) * 4;
				Drawing::Line(p1, p2, 表色, (int)太さ);
				Drawing::Line(p2, p3, 表色, (int)太さ);
				Drawing::Line(p3, p4, 表色, (int)太さ);
				Drawing::Line(p4, p5, 表色, (int)太さ);
				Drawing::Circle({ p1.x, p1.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p2.x, p2.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p3.x, p3.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p4.x, p4.y, 太さ / 2 }, 表色);
				Drawing::Circle({ p5.x, p5.y, 太さ / 2 }, 表色);
			}
		}

	}


	//全読み込み
	static void LoadAsset()
	{
		MFont::Load();

		//Loading::Start();

		MUnit::Load();
		MIcon::Load();
		MSystem::Load();

		MEffect::Load();
		MJob::Load();

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