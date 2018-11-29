//Copyright © 2017 (´･@･)
//[License]GNU Affero General Public License, version 3
//[Contact]http://tacoika.blog87.fc2.com/
#pragma once
#include <SDXFramework.h>
#include "../System/enum_type.h"

namespace SDX_BSC
{
	using namespace SDX;
	//画像、音声、フォント

	//ユニット画像
	namespace MUnit
	{
		EnumArray<ImagePack, UnitImageType> ユニット画像[3];//青,赤,影の順番、ちょっとわかりにくいかも？

		static void Load()
		{
			ユニット画像[0][UnitImageType::ゼラルー].Load("image/unit/001b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::ゴブリン].Load("image/unit/002b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::オーガ].Load("image/unit/003b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::歩兵].Load("image/unit/004b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::竜王].Load("image/unit/005b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::重装兵].Load("image/unit/006b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::機動兵].Load("image/unit/007b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::僧兵].Load("image/unit/008b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::魔法兵].Load("image/unit/009b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::妖精].Load("image/unit/010b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::忍者].Load("image/unit/011b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::くノ一].Load("image/unit/012b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::女エルフ].Load("image/unit/013b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::男エルフ].Load("image/unit/014b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::魔族].Load("image/unit/015b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::格闘家].Load("image/unit/016b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::傭兵].Load("image/unit/017b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::魔貴族].Load("image/unit/018b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::斧兵].Load("image/unit/019b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::勇者].Load("image/unit/020b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::王子].Load("image/unit/021b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::王].Load("image/unit/022b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::王女].Load("image/unit/023b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::老兵].Load("image/unit/024b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::主人公].Load("image/unit/025b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::エルフ王].Load("image/unit/026b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::騎士].Load("image/unit/027b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::司祭].Load("image/unit/028b.png", 9, 3, 4);
			ユニット画像[0][UnitImageType::骸骨].Load("image/unit/029b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::海人].Load("image/unit/030b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::ゴーレム].Load("image/unit/031b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::獣人].Load("image/unit/032b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::ゴブリン王].Load("image/unit/033b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::竜].Load("image/unit/034b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::悪魔].Load("image/unit/035b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::樹人].Load("image/unit/036b.png", 9, 3, 3);
			ユニット画像[0][UnitImageType::怪鳥].Load("image/unit/037b.png", 9, 3, 3);

			ユニット画像[1][UnitImageType::ゼラルー].Load("image/unit/001r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::ゴブリン].Load("image/unit/002r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::オーガ].Load("image/unit/003r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::歩兵].Load("image/unit/004r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::竜王].Load("image/unit/005r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::重装兵].Load("image/unit/006r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::機動兵].Load("image/unit/007r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::僧兵].Load("image/unit/008r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::魔法兵].Load("image/unit/009r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::妖精].Load("image/unit/010r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::忍者].Load("image/unit/011r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::くノ一].Load("image/unit/012r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::女エルフ].Load("image/unit/013r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::男エルフ].Load("image/unit/014r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::魔族].Load("image/unit/015r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::格闘家].Load("image/unit/016r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::傭兵].Load("image/unit/017r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::魔貴族].Load("image/unit/018r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::斧兵].Load("image/unit/019r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::勇者].Load("image/unit/020r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::王子].Load("image/unit/021r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::王].Load("image/unit/022r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::王女].Load("image/unit/023r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::老兵].Load("image/unit/024r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::主人公].Load("image/unit/025r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::エルフ王].Load("image/unit/026r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::騎士].Load("image/unit/027r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::司祭].Load("image/unit/028r.png", 9, 3, 4);
			ユニット画像[1][UnitImageType::骸骨].Load("image/unit/029r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::海人].Load("image/unit/030r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::ゴーレム].Load("image/unit/031r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::獣人].Load("image/unit/032r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::ゴブリン王].Load("image/unit/033r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::竜].Load("image/unit/034r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::悪魔].Load("image/unit/035r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::樹人].Load("image/unit/036r.png", 9, 3, 3);
			ユニット画像[1][UnitImageType::怪鳥].Load("image/unit/037r.png", 9, 3, 3);

			ユニット画像[2][UnitImageType::ゼラルー].Load("image/unit/001w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::ゴブリン].Load("image/unit/002w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::オーガ].Load("image/unit/003w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::歩兵].Load("image/unit/004w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::竜王].Load("image/unit/005w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::重装兵].Load("image/unit/006w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::機動兵].Load("image/unit/007w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::僧兵].Load("image/unit/008w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::魔法兵].Load("image/unit/009w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::妖精].Load("image/unit/010w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::忍者].Load("image/unit/011w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::くノ一].Load("image/unit/012w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::女エルフ].Load("image/unit/013w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::男エルフ].Load("image/unit/014w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::魔族].Load("image/unit/015w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::格闘家].Load("image/unit/016w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::傭兵].Load("image/unit/017w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::魔貴族].Load("image/unit/018w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::斧兵].Load("image/unit/019w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::勇者].Load("image/unit/020w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::王子].Load("image/unit/021w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::王].Load("image/unit/022w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::王女].Load("image/unit/023w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::老兵].Load("image/unit/024w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::主人公].Load("image/unit/025w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::エルフ王].Load("image/unit/026w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::騎士].Load("image/unit/027w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::司祭].Load("image/unit/028w.png", 9, 3, 4);
			ユニット画像[2][UnitImageType::骸骨].Load("image/unit/029w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::海人].Load("image/unit/030w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::ゴーレム].Load("image/unit/031w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::獣人].Load("image/unit/032w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::ゴブリン王].Load("image/unit/033w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::竜].Load("image/unit/034w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::悪魔].Load("image/unit/035w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::樹人].Load("image/unit/036w.png", 9, 3, 3);
			ユニット画像[2][UnitImageType::怪鳥].Load("image/unit/037w.png", 9, 3, 3);
		}
	}

	//その他のアイコン
	namespace MIcon
	{
		static void Load()
		{

		}
	}

	//UI等のシステム画像
	namespace MSystem
	{
		Image マップ;
		ImagePack 背景;
		ImagePack 場面;
		ImagePack 感情;
		ImagePack 陣形;
		ImagePack 道具;
		Image モラルバー;
		Image モラルゲージ;
		Image 吹き出し;
		Image 穴;
		ImagePack 火;
		Image 柵;
		Image 岩;

		static void Load()
		{
			マップ.Load("image/system/map.png");
			背景.Load("image/system/back", "jpg", 11);
			場面.Load("image/system/bamen", "png", 4);
			感情.Load("image/system/emote.png", 10, 5, 2);
			陣形.Load("image/system/formation.png", 6, 3, 2);
			道具.Load("image/system/item.png", 15, 5, 3);
			モラルバー.Load("image/system/moralbar.png");
			モラルゲージ.Load("image/system/moral.png");
			吹き出し.Load("image/system/hukidasi.png");
			穴.Load("image/system/ana.png");
			火.Load("image/system/fire.png",4,4,1);
			柵.Load("image/system/saku.png");
			岩.Load("image/system/iwa.png");

		}
	}

	//文字データ
	namespace MFont
	{
		Font ゴシック小;
		Font ゴシック大;
		Font 数字;
		ImagePack 白数字;

		static void Load()
		{

			static Image ゴシック12;
			static Image ゴシック16;
			白数字.Load("font/number.png", 10, 10, 1);
			ゴシック12.Load("font/12.png");
			ゴシック16.Load("font/16.png");

			ゴシック小.LoadBMPFont(ゴシック12, "font/bmp_font_list.txt");
			ゴシック大.LoadBMPFont(ゴシック16, "font/bmp_font_list.txt");
			数字.Load("", 3, 0);
			数字.SetImageS("0", &白数字 , 10);

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
			戦闘中.Load("music/sentou.mp3");
			敗北.Load("music/haiboku.mp3");
			戦闘開始.Load("music/kaisi.mp3");
			内政中.Load("music/naisei.mp3");
			勝利.Load("music/syouri.mp3");
		}
	}

	//効果音
	namespace MSound
	{
		EnumArray<Sound, SEType> 効果音;

		static void Load()
		{
			
		}
	}

	//全読み込み
	static void LoadMaterial()
	{
		MFont::Load();

		Loading::Start();

		MUnit::Load();
		MIcon::Load();
		MSystem::Load();

		MMusic::Load();
		MSound::Load();

		Loading::End();

		//非同期読み込み完了確認
		while (System::Update())
		{
			MFont::数字.Draw({ 10,10 }, { 255,255,255 }, Loading::GetLoadingCount());
			MFont::数字.Draw({ 10,20 }, { 255,255,255 }, { Loading::GetSuccesCount() , "C" , 1} );

			if (Loading::GetLoadingCount() == Loading::GetSuccesCount()) break;			
		}

	}

}