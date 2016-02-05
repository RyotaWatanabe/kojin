/*=======================================================================================================
�T�@���F����炷
�쐬���F6/24
�X�V���F6/25
����ҁF�n糗ȑ�
=======================================================================================================*/

#pragma once
#include "Global.h"
#include <xact3.h>

class Audio
{
	IXACT3Engine* xactEngine;		//XACT�G���W��������
	IXACT3WaveBank* waveBank;
	IXACT3SoundBank*   soundBank;
	LPVOID        mapWaveBank;
	BYTE*    soundBankData;

	HRESULT InitEngine();					//XACT�G���W���̍쐬
	HRESULT LoadWaveBank(char* fileName);	//WaveBank�ǂݍ���
	HRESULT LoadSoundBank(char* fileName);	//SoundBank�ǂݍ���
public:
	Audio();
	~Audio();
	//3�̊֐����܂Ƃ߂�
	HRESULT Load(char* waveBankFileName, char* soundBankFileName);
	HRESULT Play(char* cueName);	//�����Đ�����
	HRESULT Stop(char* cueName);	//��~����
};


