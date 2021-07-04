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
		ImagePack モンスター[100];

		static void Load()
		{
			for (int i = 0; i < 100; i++)
			{
				std::string path = "file/monster/";
				path += std::to_string(i / 100);
				path += std::to_string(i / 10 % 10);
				path += std::to_string(i % 10);
				path += ".png";
				モンスター[i].Load(path.c_str(), 2, 2, 1);
			}
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

			素材[CraftType::木材].Load("file/system/mat_002.png");
			素材[CraftType::石材].Load("file/system/mat_008.png");
			素材[CraftType::鉄材].Load("file/system/mat_001.png");
			素材[CraftType::革材].Load("file/system/mat_003.png");
			素材[CraftType::骨材].Load("file/system/mat_004.png");
			素材[CraftType::魔材].Load("file/system/mat_010.png");

			for (int i = 0; i < 100; i++)
			{
				投資[i].Load("file/icon/meisei.png");
				Aスキル[i].Load("file/icon/meisei.png");
				Pスキル[i].Load("file/icon/meisei.png");
			}

			//探索用
			UI[IconType::探索_伐採].Load("file/system/wood_get.png");
			UI[IconType::探索_採掘].Load("file/system/iron_get.png");
			UI[IconType::探索_採石].Load("file/system/stone_get.png");
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

			装備品[(int)ItemType::アクセサリー].Load("file/equip/armor003.png");

			アクセサリ[0].Load("file/accessory/boots_007.png");
			//素材
			ダンジョン[0].Load("file/system/move_01.png");
			ダンジョン[1].Load("file/system/move_01.png");
			ダンジョン[2].Load("file/system/move_01.png");
			ダンジョン[3].Load("file/system/move_01.png");
			ダンジョン[4].Load("file/system/move_01.png");

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
		constexpr int フォント数 = 2;

		Font* F[3];

		Font* S;
		Font* M;
		Font* L;

		Font SDot;
		Font MDot;
		Font LDot;

		Font SAlias;
		Font MAlias;
		Font LAlias;

		//Font SMaru;
		//Font MMaru;
		//Font LMaru;

		static void Load()
		{
			std::string fa = "file/font/PixelMplus12-Regular.ttf";
			std::string fb = "file/font/mplus-1m-Regular.ttf";
			std::string fc = "file/font/PixelMplus10-Regular.ttf";
			//std::string fc = "file/font/misaki_gothic_2nd.ttf";

			//ドットフォントとエイリアスフォントの描画位置が近くなるよう、Y座標に補正を入れる
			SDot.Load(fa.c_str(), 12 , 2,0 ,false);
			MDot.Load(fc.c_str(), 20 , 3,0 ,false);
			LDot.Load(fa.c_str(), 24 , 4,0 ,false);

			SAlias.Load(fb.c_str(), 12 , 2, 1,false);
			MAlias.Load(fb.c_str(), 20 , 3, 2, false);
			LAlias.Load(fb.c_str(), 24 , 4, 3, false);
			
			//SMaru.Load(fc.c_str(), 12, 2, 1);
			//MMaru.Load(fc.c_str(), 18, 3, 2);
			//LMaru.Load(fc.c_str(), 24, 4, 3);

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
		ImagePack エフェクト[200];
		int エフェクト種類[200];//0 通常、1加算、2減算

		static void Load()
		{
			for (int i = 0; i < 200; i++)
			{
				エフェクト[i].Load("file/effect/pipo-btleffect001.png", 5, 5, 1);
			}

			エフェクト[1].Load("file/effect/pipo-btleffect001.png", 5, 5, 1);
			エフェクト[2].Load("file/effect/pipo-btleffect002.png", 9, 9, 1);
			エフェクト[6].Load("file/effect/pipo-btleffect006_.png", 7, 7, 1);
			エフェクト[24].Load("file/effect/pipo-btleffect024.png", 8, 8, 1);
			エフェクト[27].Load("file/effect/pipo-btleffect027.png", 8, 8, 1);
			エフェクト[29].Load("file/effect/pipo-btleffect029.png", 8, 8, 1);
			エフェクト[19].Load("file/effect/pipo-btleffect019.png", 10, 10, 1);
			エフェクト[20].Load("file/effect/pipo-btleffect020.png", 10, 10, 1);
			エフェクト[45].Load("file/effect/pipo-btleffect045.png", 10, 10, 1);
			エフェクト[17].Load("file/effect/pipo-btleffect017.png", 8, 8, 1);
			エフェクト[121].Load("file/effect/pipo-btleffect121.png", 8, 5, 2);
			エフェクト[122].Load("file/effect/pipo-btleffect122.png", 8, 5, 2);

			エフェクト種類[45] = 1;

		}
	}

	//職業立ち絵と歩行グラ
	namespace MJob
	{
		Image 立ち絵[12];//画像数上限は暫定
		ImagePack ちび[12];

		static void Load()
		{
			//スレイヤー
			立ち絵[0].Load("file/job/BR16.zip");
			ちび[0].Load("file/job/chibi/BR16.png", 9, 3, 6);

			//ガーディアン
			立ち絵[1].Load("file/job/BR97.png");
			ちび[1].Load("file/job/chibi/BR97.png", 9, 3, 6);

			//デッドアイ
			立ち絵[2].Load("file/job/BR92.png");
			ちび[2].Load("file/job/chibi/BR92.png", 9, 3, 6);

			//エレメンタリスト
			立ち絵[3].Load("file/job/BR207.png");
			ちび[3].Load("file/job/chibi/BR207.png", 9, 3, 6);

			//プリースト
			立ち絵[4].Load("file/job/BR99.png");
			ちび[4].Load("file/job/chibi/BR99.png", 9, 3, 6);

			//オカルティスト
			立ち絵[5].Load("file/job/BR42.png");
			ちび[5].Load("file/job/chibi/BR42.png", 9, 3, 6);

			//グラディエーター
			立ち絵[6].Load("file/job/BR40.png");
			ちび[6].Load("file/job/chibi/BR40.png", 9, 3, 6);

			//アサシン
			立ち絵[7].Load("file/job/BR200.png");
			ちび[7].Load("file/job/chibi/BR200.png", 9, 3, 6);

			//バーサーカー
			立ち絵[8].Load("file/job/BR113.png");
			ちび[8].Load("file/job/chibi/BR113.png", 9, 3, 6);

			//トリックスター
			立ち絵[9].Load("file/job/BR44.png");
			ちび[9].Load("file/job/chibi/BR44.png", 9, 3, 6);

			//ミスティック
			立ち絵[10].Load("file/job/BR122.png");
			ちび[10].Load("file/job/chibi/BR122.png", 9, 3, 6);

			//パスファインダー
			立ち絵[11].Load("file/job/BR223.png");
			ちび[11].Load("file/job/chibi/BR223.png", 9, 3,6);
		}
	}

	//BGM
	namespace MMusic
	{
		EnumArray<Music, BGMType> BGM;

		static void Load()
		{
			BGM[BGMType::準備中].Load("file/music/furattoguild.mp3");
			BGM[BGMType::探検中].Load("file/music/mamonotoyukukouya.mp3");
			BGM[BGMType::通常ボス].Load("file/music/yudanhakinmotsu.mp3");
			BGM[BGMType::エリアボス].Load("file/music/imasuguketsudannwo.mp3");
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
		Image 円;
		Image 点;

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

			円.Load("file/system/circle.png");
			点.Load("file/system/dot.png");
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