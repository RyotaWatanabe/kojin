/*=======================================================================================================
概　略：音を鳴らす
作成日：6/24
更新日：6/25
制作者：渡邉諒太
=======================================================================================================*/

#pragma once
#include "Global.h"
#include <xact3.h>

class Audio
{
	IXACT3Engine* xactEngine;		//XACTエンジンを入れる
	IXACT3WaveBank* waveBank;
	IXACT3SoundBank*   soundBank;
	LPVOID        mapWaveBank;
	BYTE*    soundBankData;

	HRESULT InitEngine();					//XACTエンジンの作成
	HRESULT LoadWaveBank(char* fileName);	//WaveBank読み込み
	HRESULT LoadSoundBank(char* fileName);	//SoundBank読み込み
public:
	Audio();
	~Audio();
	//3つの関数をまとめる
	HRESULT Load(char* waveBankFileName, char* soundBankFileName);
	HRESULT Play(char* cueName);	//音を再生する
	HRESULT Stop(char* cueName);	//停止する
};


