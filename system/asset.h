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
		Font* S;
		Font* M;
		Font* L;

		Font SDot;
		Font MDot;
		Font LDot;

		Font SAlias;
		Font MAlias;
		Font LAlias;

		static void Load()
		{
			std::string f1 = "file/font/PixelMplus12-Regular.ttf";
			std::string f1b = "file/font/mplus-1m-Regular.ttf";

			//ドットフォントとエイリアスフォントの描画位置が近くなるよう、Y座標に補正を入れる
			SDot.Load(f1.c_str(), 12 , 2 );
			MDot.Load(f1.c_str(), 24 , 4 );
			LDot.Load(f1.c_str(), 36 , 6 );
			SAlias.Load(f1b.c_str(), 12 , 2, 1);
			MAlias.Load(f1b.c_str(), 24 , 4, 2);
			LAlias.Load(f1b.c_str(), 36 , 6, 3);

			//0を０(オー)にする
			bool iszeroswap = true;
			if (iszeroswap)
			{
				SDot.SetImage("0", SDot.GetImage("O"));
				MDot.SetImage("0", MDot.GetImage("O"));
				LDot.SetImage("0", LDot.GetImage("O"));
				SAlias.SetImage("0", SAlias.GetImage("O"));
				MAlias.SetImage("0", MAlias.GetImage("O"));
				LAlias.SetImage("0", LAlias.GetImage("O"));
			}
		}
	}

	//戦闘エフェクト
	namespace MEffect
	{
		ImagePack エフェクト[12];
		int エフェクト種類[12];//0 通常、1加算、2減算

		static void Load()
		{
			エフェクト[0].Load("file/effect/pipo-btleffect001.png", 5, 5, 1);
			エフェクト[1].Load("file/effect/pipo-btleffect002.png", 9, 9, 1);
			エフェクト[2].Load("file/effect/pipo-btleffect006_.png", 7, 7, 1);
			エフェクト[3].Load("file/effect/pipo-btleffect024.png", 8, 8, 1);
			エフェクト[4].Load("file/effect/pipo-btleffect027.png", 8, 8, 1);
			エフェクト[5].Load("file/effect/pipo-btleffect029.png", 8, 8, 1);
			エフェクト[6].Load("file/effect/pipo-btleffect019.png", 10, 10, 1);
			エフェクト[7].Load("file/effect/pipo-btleffect020.png", 10, 10, 1);
			エフェクト[8].Load("file/effect/pipo-btleffect045.png", 10, 10, 1);
			エフェクト[9].Load("file/effect/pipo-btleffect017.png", 8, 8, 1);
			エフェクト[10].Load("file/effect/pipo-btleffect121.png", 8, 5, 2);
			エフェクト[11].Load("file/effect/pipo-btleffect122.png", 8, 5, 2);
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