//Copyright © 2019 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once

namespace SDX_ADE
{
	using namespace SDX;
	//画像、音声、フォント

	//ユニット
	namespace MUnit
	{
		
		EnumArray<ImagePack, UnitImageType> ユニット;
		ImagePack モンスター[100];

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
		//最大数は暫定
		EnumArray<Image, IconType> UI;

		EnumArray<Image, CraftType> 素材;
		EnumArray<Image, QuestType> クエスト;

		Image 装備品[100];
		Image アクセサリ[100];

		Image Aスキル[100];
		Image Pスキル[100];
		Image ダンジョン[10];

		Image 投資[100];

		

		EnumArray<Image, ItemType> 装備種;//いらない？
		EnumArray<Image, StatusType> ステータス種;//ステータスのアイコン？

		static void LoadIcon()
		{
			//UI汎用
			UI[IconType::閉じる].Load("file/icon/tojiru.png");
			UI[IconType::資金].Load("file/icon/sikin.png");
			UI[IconType::三角].Load("file/icon/sankaku.png");
			UI[IconType::製造力].Load("file/icon/seizouryoku.png");
			UI[IconType::製造力].Load("file/icon/kanryou.png");
			UI[IconType::ランク].Load("file/icon/rank.png");
			UI[IconType::ゴミ箱].Load("file/icon/dustbox.png");
			//各種ウィンドウアイコン
			UI[IconType::装備].Load("file/icon/item.png");
			UI[IconType::製造].Load("file/icon/seizou.png");
			UI[IconType::迷宮].Load("file/icon/dungeon.png");
			UI[IconType::編成].Load("file/icon/hensei.png");
			UI[IconType::求人].Load("file/icon/kyuujin.png");
			UI[IconType::戦略].Load("file/icon/senryaku.png");
			UI[IconType::素材].Load("file/icon/sozai.png");
			UI[IconType::依頼].Load("file/icon/irai.png");
			UI[IconType::情報].Load("file/icon/jyouhou.png");
			UI[IconType::ログ].Load("file/icon/log.png");

			UI[IconType::全て].Load("file/icon/all.png");
			UI[IconType::ボス].Load("file/icon/boss.png");
			UI[IconType::地図].Load("file/icon/tizu.png");
			UI[IconType::宝箱].Load("file/icon/takarabako.png");
			UI[IconType::更新].Load("file/icon/kousin.png");

			UI[IconType::再募集].Load("file/icon/saibosyuu.png");
				
			UI[IconType::メインクエ].Load("file/icon/mainquest.png");//
			UI[IconType::サブクエ].Load("file/icon/subquest.png");//
			UI[IconType::名声].Load("file/icon/meisei.png");

			UI[IconType::集客].Load("file/icon/raikyaku.png");
			UI[IconType::開発].Load("file/icon/kaihatu.png");
			UI[IconType::撤退].Load("file/icon/.png");//

			UI[IconType::解像度].Load("file/icon/kaizoudo.png");
			UI[IconType::BGM].Load("file/icon/bgm.png");
			UI[IconType::効果音].Load("file/icon/koukaon.png");

			UI[IconType::New].Load("file/icon/new.png");

			//素材
			UI[IconType::鉄材].Load("file/system/mat_001.png");
			UI[IconType::木材].Load("file/system/mat_002.png");
			UI[IconType::皮材].Load("file/system/mat_003.png");
			UI[IconType::骨材].Load("file/system/mat_004.png");

			//探索用
			UI[IconType::探索_伐採].Load("file/system/dun00.png");
			UI[IconType::探索_採掘].Load("file/system/dun01.png");
			UI[IconType::探索_財宝].Load("file/system/dun02.png");
			UI[IconType::探索_地図].Load("file/system/dun03.png");
			UI[IconType::探索_石版].Load("file/system/dun04.png");

			//上部分バー
			UI[IconType::日付].Load("file/icon/hiduke.png");
			UI[IconType::時間].Load("file/icon/jikan.png");
			UI[IconType::人口].Load("file/icon/jinkou.png");
			UI[IconType::ヘルプ].Load("file/icon/help.png");
			UI[IconType::停止].Load("file/icon/teisi.png");
			UI[IconType::速度].Load("file/icon/sokudo.png");
			UI[IconType::設定].Load("file/icon/settei.png");
			UI[IconType::終了].Load("file/icon/deguti.png");
		}

		static void LoadOther()
		{
			//武器-防具
			装備品[(int)ItemType::大剣].Load("file/equip/wepon000.png");
			装備品[(int)ItemType::剣盾].Load("file/equip/wepon001.png");
			装備品[(int)ItemType::大盾].Load("file/equip/wepon002.png");
			装備品[(int)ItemType::円盤].Load("file/equip/wepon003.png");
			装備品[(int)ItemType::斧].Load("file/equip/wepon004.png");
			装備品[(int)ItemType::刀].Load("file/equip/wepon005.png");
			装備品[(int)ItemType::弓].Load("file/equip/wepon006.png");
			装備品[(int)ItemType::神杖].Load("file/equip/wepon007.png");
			装備品[(int)ItemType::錫杖].Load("file/equip/wepon008.png");
			装備品[(int)ItemType::導杖].Load("file/equip/wepon009.png");
			装備品[(int)ItemType::書物].Load("file/equip/wepon010.png");
			装備品[(int)ItemType::水晶].Load("file/equip/wepon011.png");

			装備品[(int)ItemType::重鎧].Load("file/equip/armor000.png");
			装備品[(int)ItemType::軽鎧].Load("file/equip/armor001.png");
			装備品[(int)ItemType::軽装].Load("file/equip/armor002.png");
			装備品[(int)ItemType::外套].Load("file/equip/armor003.png");

			アクセサリ[0].Load("file/accessory/boots_007.png");
			//素材

			UI[IconType::城].Load("file/system/move_00.png");
			UI[IconType::森].Load("file/system/move_01.png");
			UI[IconType::洞窟].Load("file/system/move_02.png");
			UI[IconType::砂漠].Load("file/system/move_03.png");
			UI[IconType::山].Load("file/system/move_04.png");
			UI[IconType::滝].Load("file/system/move_05.png");
			UI[IconType::塔].Load("file/system/move_06.png");
			UI[IconType::廃墟].Load("file/system/move_07.png");


			Aスキル[(int)SkillType::回復].Load("file/game_icons/healing.png");
			Aスキル[(int)SkillType::攻撃].Load("file/game_icons/saber-slash.png");
			Aスキル[(int)SkillType::バフ].Load("file/game_icons/embrassed-energy.png");
			Aスキル[(int)SkillType::デバフ].Load("file/game_icons/stoned-skull.png");


			装備種[ItemType::大剣].Load("file/game_icons/plain-dagger.png");
			装備種[ItemType::剣盾].Load("file/game_icons/battle-axe.png");
			装備種[ItemType::大盾].Load("file/game_icons/flanged-mace.png");
			装備種[ItemType::円盤].Load("file/game_icons/checked-shield.png");
			装備種[ItemType::斧].Load("file/game_icons/stiletto.png");
			装備種[ItemType::刀].Load("file/game_icons/trident.png");
			装備種[ItemType::弓].Load("file/game_icons/pocket-bow.png");
			装備種[ItemType::神杖].Load("file/game_icons/winchester-rifle.png");
			装備種[ItemType::錫杖].Load("file/game_icons/orb-wand.png");
			装備種[ItemType::導杖].Load("file/game_icons/skull-staff.png");
			装備種[ItemType::書物].Load("file/game_icons/wizard-staff.png");
			装備種[ItemType::水晶].Load("file/game_icons/lunar-wand.png");

			装備種[ItemType::重鎧].Load("file/game_icons/breastplate.png");
			装備種[ItemType::軽鎧].Load("file/game_icons/leather-armor.png");
			装備種[ItemType::軽装].Load("file/game_icons/robe.png");
			装備種[ItemType::外套].Load("file/game_icons/Plastron.png");

			装備種[ItemType::すべて].Load("file/game_icons/talk.png");

			ステータス種[StatusType::力].Load("file/game_icons/fist.png");
			ステータス種[StatusType::技].Load("file/game_icons/juggler.png");
			ステータス種[StatusType::知].Load("file/game_icons/white-book.png");

			static Image img_emote;
			img_emote.Load("file/system/emo.png");
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
			std::string f1 = "file/font/mplus-1m-Regular.ttf";
			std::string f1b = "file/font/mplus-1m-Bold.ttf";

			//f1 = "file/font/PixelMplus12-Regular.ttf";
			//f1b = "file/font/PixelMplus12-Bold.ttf";

			//f1b = "file/font/PixelMplus12-Bold.ttf";
			//f1 = "file/font/JF-Dot-k14.ttf";
			//f1b = "file/font/JF-Dot-k14.ttf";
			
			SSize.Load(f1.c_str(), 14 , 2);
			MSize.Load(f1.c_str(), 18 , 3);
			LSize.Load(f1.c_str(), 24 , 4);
			BSSize.Load(f1b.c_str(), 14 , 2);
			BMSize.Load(f1b.c_str(), 18 , 3);
			BLSize.Load(f1b.c_str(), 24 , 4);

			//0を０(オー)にする
			bool iszeroswap = true;
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
		EnumArray<ImagePack, EffectAnimeType> エフェクト;

		static void Load()
		{
			エフェクト[EffectAnimeType::斬].Load("file/effect/pipo-btleffect001.png", 5, 5, 1);
			エフェクト[EffectAnimeType::打].Load("file/effect/pipo-btleffect002.png", 9, 9, 1);
			エフェクト[EffectAnimeType::突].Load("file/effect/pipo-btleffect006_.png", 7, 7, 1);
			エフェクト[EffectAnimeType::炎].Load("file/effect/pipo-btleffect024.png", 8, 8, 1);
			エフェクト[EffectAnimeType::雷].Load("file/effect/pipo-btleffect027.png", 8, 8, 1);
			エフェクト[EffectAnimeType::氷].Load("file/effect/pipo-btleffect029.png", 8, 8, 1);
			エフェクト[EffectAnimeType::バフ].Load("file/effect/pipo-btleffect019.png", 10, 10, 1);
			エフェクト[EffectAnimeType::デバフ].Load("file/effect/pipo-btleffect020.png", 10, 10, 1);
			エフェクト[EffectAnimeType::回復].Load("file/effect/pipo-btleffect045.png", 10, 10, 1);
			エフェクト[EffectAnimeType::異常].Load("file/effect/pipo-btleffect017.png", 8, 8, 1);
			エフェクト[EffectAnimeType::爪].Load("file/effect/pipo-btleffect121.png", 8, 5, 2);
			エフェクト[EffectAnimeType::牙].Load("file/effect/pipo-btleffect122.png", 8, 5, 2);
		}
	}

	//職業立ち絵と歩行グラ
	namespace MJob
	{
		Image 立ち絵[12];//画像数上限は暫定
		ImagePack ちび[12];

		static void Load()
		{
			立ち絵[0].Load("file/job/BR97.png");
			立ち絵[1].Load("file/job/BR40.png");
			立ち絵[2].Load("file/job/BR223.png");
			立ち絵[3].Load("file/job/BR99.png");
			立ち絵[4].Load("file/job/BR122.png");
			立ち絵[5].Load("file/job/BR42.png");
			立ち絵[6].Load("file/job/BR113.png");
			立ち絵[7].Load("file/job/BR16.zip");
			立ち絵[8].Load("file/job/BR200.png");
			立ち絵[9].Load("file/job/BR92.png");
			立ち絵[10].Load("file/job/BR207.png");
			立ち絵[11].Load("file/job/BR44.png");

			ちび[0].Load("file/job/chibi/BR97.png",9,3,6);
			ちび[1].Load("file/job/chibi/BR40.png", 9, 3,6);
			ちび[2].Load("file/job/chibi/BR223.png", 9, 3,6);
			ちび[3].Load("file/job/chibi/BR99.png", 9, 3,6);
			ちび[4].Load("file/job/chibi/BR122.png", 9, 3,6);
			ちび[5].Load("file/job/chibi/BR42.png", 9, 3,6);
			ちび[6].Load("file/job/chibi/BR113.png", 9, 3,6);
			ちび[7].Load("file/job/chibi/BR16.png", 9, 3,6);
			ちび[8].Load("file/job/chibi/BR200.png", 9, 3,6);
			ちび[9].Load("file/job/chibi/BR92.png", 9, 3,6);
			ちび[10].Load("file/job/chibi/BR207.png", 9, 3,6);
			ちび[11].Load("file/job/chibi/BR44.png", 9, 3,6);
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
			BGM[BGMType::タイトル].Load("file/music/ouzokunokeifu.mp3");

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
	namespace MSystem
	{
		ImagePack ウィンドウ枠;
		Image ダンジョン背景[5];

		Image メインゲーム前景;
		Image メインゲーム背景;

		Image タイトル背景;
		Image タイトル前景;

		Image タイトルロゴ;

		Image 吹き出し;

		static void Load()
		{
			ウィンドウ枠.Load("file/system/window_skin.png", 60, 10, 6);

			ダンジョン背景[0].Load("file/system/forest.png");
			ダンジョン背景[1].Load("file/system/cave.png");
			ダンジョン背景[2].Load("file/system/cave.png");

			メインゲーム背景.Load("file/title/background4.png");
			メインゲーム前景.Load("file/title/middleground6.png");

			タイトル背景.Load("file/title/background5.png");
			タイトル前景.Load("file/title/middleground5.png");

			吹き出し.Load("file/system/huki_01.png");

			タイトルロゴ.Load("file/title/titlelogo.png");
		}
	}

	//後でライブラリに追加する候補の描画関数
	namespace MSystem
	{
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

		//バー２色
		static void DrawBarTwo(const Point& 座標, const int 横幅, const int 縦幅, double 前割合 , double 後割合, int 枠太さ, const Color& 前色 , const Color& 後色, const Color& 枠色, const Color& 中色, bool is左側)
		{
			前割合 = std::max(0.0, 前割合);
			前割合 = std::min(1.0, 前割合);

			後割合 = std::max(0.0, 後割合);
			後割合 = std::min(1.0, 後割合);

			DrawBoxBold(座標, 横幅, 縦幅, 中色, 枠太さ, 枠色);

			int ww = int((横幅 - 枠太さ * 2) * 後割合);
			int hh = 縦幅 - 枠太さ * 2;

			if ( ww > 0 )
			{
				if (is左側)
				{
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 後色);
				} else {
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 後色);
				}
			}

			ww = int((横幅 - 枠太さ * 2) * 前割合);

			if (ww > 0)
			{
				if (is左側)
				{
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 前色);
				} else {
					DrawBox({ 座標.x + 枠太さ,座標.y + 枠太さ }, ww, hh, 前色);
				}
			}
		}


		static void DrawSkill(Image* スキル種, const Point& 座標, Color 色, std::string messe = "")
		{
			Drawing::Rect({ 座標.x ,座標.y ,29,29 }, 色, true);
			Drawing::Rect({ 座標.x + 1,座標.y + 1,27,27 }, Color::White, true);
			Drawing::Rect({ 座標.x + 2,座標.y + 2 ,25,25 }, 色, true);

			スキル種->Draw({ 座標.x + 2,座標.y + 2 });
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
		/*
		while (System::Update())
		{
			int nowC = Loading::GetLoadingCount();
			int sucC = Loading::GetSuccesCount();

			if (nowC == sucC)
			{
				break;
			}
		}
		*/
	}
}