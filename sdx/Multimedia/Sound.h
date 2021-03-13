//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Loading.h>

namespace SDX
{
	/** 効果音用音声を表すクラス.*/
	/** \include Sound.h*/
	/** @todo 同時に複数の効果音を鳴らす場合の挙動に不安*/
	class Sound
	{
	private:
		Mix_Chunk* handle = nullptr;//!<
		int leftPan = 255;//!<
		int rightPan = 255;//!<

		double volume = 1.0;
		int angle = 0;
		int distance = -1;
	public:
		Sound(){}

		~Sound(){}

		/** 音声ファイルをメモリに読み込む.*/
		Sound(const char *ファイル名, double 音量 = 1.0)
		{
			Load(ファイル名);
		}

		/** 音声ファイルをメモリに読み込む.*/
		bool Load(const char *ファイル名, double 音量 = 1.0)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(ファイル名,音量); });
				return true;
			}

			if (handle != nullptr){ return false; }

			handle = Mix_LoadWAV(ファイル名);
			if (!handle){ return false; }
			
			volume = std::min(音量,1.0);

			Mix_VolumeChunk(handle, int(volume * 128));
			return true;
		}

		/** 音声ファイルをメモリから開放.*/
		bool Release()
		{
			if (handle == nullptr){ return false; }
			Mix_FreeChunk(handle);
			return true;
		}

		/** ハンドルを取得.*/
		Mix_Chunk* GetHandle() const
		{
			return this->handle;
		}

		/** 音声ファイルを再生.*/
		bool Play() const
		{
			//static int channel = 0;
			//channel = (++channel) % 2;
			Mix_PlayChannel(0, handle, 0);

			if (distance >= 0)
			{
				Mix_SetPosition(0, angle, distance);
			}
			else if (leftPan < 255 || rightPan < 255)
			{
				Mix_SetPanning(0, leftPan, rightPan);
			}

			return true;
		}

		/** 音量を0～1.0の範囲で設定.*/
		bool SetVolume(double 音量)
		{
			volume = std::max(音量, 0.0);
			volume = std::min(音量, 1.0);
			Mix_VolumeChunk(handle, int(音量 * MIX_MAX_VOLUME));
			return true;
		}

		/** 音量を取得.*/
		double GetVolume()
		{
			return volume;
		}

		/** 音声パンを設定.*/
		/** スピーカー左右の音量を変える、0.0～1.0*/
		void SetPanning(double 左パン = 1.0, double 右パン = 1.0)
		{
			leftPan = std::min(int(左パン*255),255);
			rightPan = std::min(int(右パン*255),255);
		}

		/** 3D音声再生効果を付ける.*/
		/** 距離は[近]0～1.0[遠]、角度は[正面]0[左]-PAI/2[右]PAI/2で指定*/
		/** 距離を0以下にすると無効になる*/
		/** SetPanよりこっちが優先される*/
		/** @todo 距離指定がバグってる？*/
		void Set3DEffect(double 距離 = -1, double 角度 = 0)
		{
			distance = std::min((int)距離*255,255);
			angle = int(角度 * 180 / PAI);//℃に変換
			if (angle < 0)
			{
				angle = 360 -(std::abs(angle) % 360);
			}
		}

		/** 全体の音量を0～1.0の範囲で設定.*/
		/** 一度もこの関数を使用していない場合は最大音量*/
		static void SetMainVolume(double 音量)
		{
			//全チャンネルの音量を変更
			Mix_Volume(-1,int(音量 * MIX_MAX_VOLUME));
		}
	};
}