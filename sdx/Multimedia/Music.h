//Copyright © 2014 SDXFramework
//[License]GNU Affero General Public License, version 3
//[Contact]http://sourceforge.jp/projects/dxframework/
#pragma once
#include <Multimedia/SDX.h>
#include <Multimedia/Sound.h>
#include <chrono>
#include <string>

namespace SDX
{
	/** BGM用音声を表すクラス.*/
	/** \include Music.h*/
	/**@todo 中途再生周りのテスト、音量変更時ノイズっぽいのが出る？*/
	class Music
	{
		friend class System;
	private:
		static Music *active;//!< 現在再生中のMusic
		static Music *next;//!< fadeOutの次に再生するMusic
		static bool nextLoop;//!< 次に再生するMusicがループするか
		static bool nextRestart;//!< 次に再生するMusicがリスタートするか
		static double mainVolume;

		Mix_Music* handle = nullptr;//!<音楽リソースのハンドル
		std::string fileName;//!<音声ファイル名
		double volume = 0;//!<再生音量

		int fadeInTime = 0;//!< フェードイン時間(ミリ秒)
		int fadeOutTime = 0;//!< フェードアウト時間(ミリ秒)

		std::chrono::system_clock::time_point startTime;//再生開始時刻
		double restartPosition = 0;//!< 再生再開位置

		/** 停止時のコールバック専用関数.*/
		/** 普通に呼び出してはいけない*/
		static void Finished()
		{
			//ここでは再生処理等をしてはいけない
			//途中で終了した場合
			auto diff = std::chrono::system_clock::now() - active->startTime;
			active->restartPosition += (double)std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() / 1000;
			active = nullptr;
		}

		static void PlayVolume(double volume)
		{
			volume *= mainVolume;

			if (volume <= 0)
			{
				Mix_VolumeMusic(0);
			} else {
				if (int(volume / MIX_MAX_VOLUME) <= 0)
				{
					Mix_VolumeMusic(1);
				} else {
					Mix_VolumeMusic(int(volume / MIX_MAX_VOLUME));
				}
			}
		}


	public:
		Music(){};

		~Music(){}

		/** 音声ファイルを登録.*/
		Music(const char *ファイル名, double 音量 = 1.0)
		{
			Music::Load(ファイル名, 音量);
		}

		/** 音声ファイルを登録.*/
		/** 音量は 0～1.0で指定、ファイルはメモリには読み込まない。*/
		bool Load(const char *ファイル名, double 音量 = 1.0)
		{
			if (Loading::isLoading)
			{
				Loading::AddLoading([=]{ Load(ファイル名, 音量); });
				return true;
			}

			if (handle != nullptr){ return false; }

			fileName = ファイル名;
			handle = Mix_LoadMUS(ファイル名);
			volume = 音量 * MIX_MAX_VOLUME;

			return true;
		}

		/** 音声ファイルを解放.*/
		bool Destroy()
		{
			if (handle == nullptr){ return false; }

			Mix_FreeMusic(handle);
			return true;
		}

		/** 音声ファイルを先頭から再生.*/
		/** Musicは複数同時に再生する事は出来ない。\n*/
		bool Play( bool ループ再生フラグ = true )
		{
			next = nullptr;
			if (handle == nullptr){ return false; }

			//現在再生中のBGMにfadeOutTimeが設定されている場合
			if (active && active->fadeOutTime > 0)
			{
				next = this;
				nextLoop = ループ再生フラグ;
				nextRestart = false;
				Stop();
				return true;
			}

			int isLoop = ( 1 - ループ再生フラグ * 2);

			if (fadeInTime <= 0)
			{
				Mix_PlayMusic(handle, isLoop );
			}
			else			
			{
				Mix_FadeInMusic(handle, isLoop , fadeInTime);
			}

			startTime = std::chrono::system_clock::now();

			PlayVolume(volume);
			active = this;

			return true;
		}

		/** 前回停止した位置から再生.*/
		/** Musicは複数同時に再生する事は出来ない。\n*/
		bool Restart(bool ループ再生フラグ = true)
		{
			next = nullptr;
			if (handle == nullptr){ return false; }

			//現在再生中のBGMにfadeOutTimeが設定されている場合
			if (active && active->fadeOutTime > 0)
			{
				next = this;
				nextLoop = ループ再生フラグ;
				nextRestart = true;
				Stop();
				return true;
			}
			else if ( active )
			{
				//止めてから再生する
				Stop();
			}

			int isLoop = ( 1 - ループ再生フラグ * 2);

			if (fadeInTime <= 0)
			{
				Mix_PlayMusic(handle, isLoop);
				if (restartPosition > 0)
				{
					Mix_SetMusicPosition(restartPosition);
				}
			}
			else
			{
				Mix_FadeInMusicPos(handle, isLoop, fadeInTime, restartPosition);
			}

			startTime = std::chrono::system_clock::now();
			PlayVolume(volume);
			active = this;

			return true;
		}

		/**0～1.0で音量を設定.*/
		void SetVolume(double 音量)
		{
			volume = 音量 * MIX_MAX_VOLUME;
		}

		/** 再生時のフェードイン時間を設定[ミリ秒].*/
		/** 指定の時間で徐々に音量を上げていく*/
		void SetFadeInTime(int フェードイン時間)
		{
			fadeInTime = std::max(0,フェードイン時間);
		}

		/** 停止時のフェードアウト時間を設定[ミリ秒].*/
		/** 指定の時間で徐々に音量を下げていく*/
		void SetFadeOutTime(int フェードアウト時間)
		{
			fadeOutTime = std::max(0,フェードアウト時間);
		}

		/** 再生中か確認.*/
		/** いずれかのMusicが再生中ならtureを返す*/
		static bool Check()
		{
			//何故かこの関数だけ成功時は1
			return (Mix_PlayingMusic() == 1);
		}

		/** 再生中のMusicを停止.*/
		/** フェードアウト時間[mm秒]が1以上の場合、徐々に音量を下げて停止する*/
		static bool Stop()
		{
			if (!Check()){ return false; }

			if (active->fadeOutTime <= 0)
			{
				Mix_HaltMusic();
			}
			else
			{
				Mix_FadeOutMusic( active->fadeOutTime );
			}

			return true;
		}

		/** 再生中の音量を変更.*/
		/** いずれかのMusicが再生中なら音量を変更*/
		static void ChangeVolume(double 音量)
		{
			PlayVolume(音量);
		}

		/** 全体の音量を0～1.0の範囲で設定.*/
		/** 一度もこの関数を使用していない場合は最大音量*/
		static void SetMainVolume(double 音量)
		{
			//元音量を変更
			mainVolume = 音量 * MIX_MAX_VOLUME;
			
			//再生中なら現在の音量も変化
			if (Check())
			{
				PlayVolume(active->volume);
			}
		}

		/** fadeOut付きで終了した後に次Musicを再生するための処理.*/
		/** System::Update内で呼ばれている*/
		static bool Update()
		{
			if (!active && next)
			{
				if (nextRestart)
				{
					return next->Restart(nextLoop);
				}
				else
				{
					return next->Play(nextLoop);
				}
			}
			return false;
		}

	};
}