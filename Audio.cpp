/*=======================================================================================================
�T�@���F�Q�[���S�̗̂������������
�쐬���F
�X�V���F7/
����ҁF�n糗ȑ�
=======================================================================================================*/


#include "Audio.h"


//�R���X�g���N�^
Audio::Audio()
{
}


//�f�X�g���N�^
Audio::~Audio()
{
	//XACT�V���b�g�_�E��
	xactEngine->ShutDown();
	//�T�E���h�o���N�J��
	SAFE_DELETE_ARRAY(soundBankData);
	//�E�F�[�u�o���N�J��
	UnmapViewOfFile(mapWaveBank);
	//�G���W���J��
	SAFE_RELEASE(xactEngine);
	//COM���C�u�����J��
	CoUninitialize();
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�FXACT�G���W���̍쐬
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Audio::InitEngine()
{
	//COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//�G���W���쐬
	if (FAILED(XACT3CreateEngine(0, &xactEngine)))
	{
		//���b�Z�[�W�{�b�N�X��\��
		MessageBox(0, "XACT�G���W���̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}

	//�p�����[�^�ݒ�
	XACT_RUNTIME_PARAMETERS xactParam = { 0 };
	xactParam.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;

	if (FAILED(xactEngine->Initialize(&xactParam)))
	{
		//���b�Z�[�W�\��
		MessageBox(0, "XACT�G���W���̃p�����[�^�ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�FWaveBank�̓ǂݍ���
// �����FfileName�@�t�@�C�����@�@
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Audio::LoadWaveBank(char* fileName)
{
	//�t�@�C�����J��
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//�t�@�C���T�C�Y�𒲂ׂ�
	DWORD  fileSize = GetFileSize(hFile, &fileSize);

	//�}�b�s���O
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
	mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	//�E�F�[�u�o���N�쐬
	if (FAILED(xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank)))
	{
		MessageBox(0, "�E�F�[�u�o���N�쐬�Ɏ��s���܂���", fileName, MB_OK);
		return E_FAIL;
	}
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�FSoundBank�̓ǂݍ���
// �����FfileName
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Audio::LoadSoundBank(char* fileName)
{
	//�t�@�C�����J��
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//�t�@�C���T�C�Y�𒲂ׂ�
	DWORD fileSize = GetFileSize(hFile, &fileSize);

	//�f�[�^��S���ǂ�
	soundBankData = new BYTE[fileSize];
	DWORD  byteRead;
	ReadFile(hFile, soundBankData, fileSize, &byteRead, NULL);

	//�T�E���h�o���N�쐬
	if (FAILED(xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank)))
	{
		//���b�Z�[�W�\��
		MessageBox(0, "�T�E���h�o���N�쐬�Ɏ��s���܂���", fileName, MB_OK);
		return E_FAIL;
	}
	//�n���h��������
	CloseHandle(hFile);
	return S_OK;
}


//
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F��L��3�̊֐����Ă�
// �����FwaveBankFileName	�E�F�[�u�o���N�̃t�@�C����
// �����FsoundBankFileName	�T�E���h�o���N�̃t�@�C����
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Audio::Load(char* waveBankFileName, char* soundBankFileName)
{
	//XACT�G���W���̍쐬
	if (FAILED(InitEngine()))
	{
		return E_FAIL;
	}

	//WaveBank�ǂݍ���
	if (FAILED(LoadWaveBank(waveBankFileName)))
	{
		return E_FAIL;
	}

	//SoundBank�ǂݍ���
	if (FAILED(LoadSoundBank(soundBankFileName)))
	{
		return E_FAIL;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�����Đ�
// �����FcueName
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Audio::Play(char* cueName)
{
	//�L���[�̔ԍ����擾
	XACTINDEX cueIndex = soundBank->GetCueIndex(cueName);

	//�Đ�
	if (FAILED(soundBank->Play(cueIndex, 0, 0, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F��~����
// �����FcueName
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Audio::Stop(char* cueName)
{
	//�L���[�̔ԍ����擾
	XACTINDEX cueIndex = soundBank->GetCueIndex(cueName);

	//��~
	if (FAILED(soundBank->Stop(cueIndex, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE)))
	{
		return E_FAIL;
	}
	return S_OK;
}