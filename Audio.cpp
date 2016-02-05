/*=======================================================================================================
概　略：ゲーム全体の流れを扱う処理
作成日：
更新日：7/
制作者：渡邉諒太
=======================================================================================================*/


#include "Audio.h"


//コンストラクタ
Audio::Audio()
{
}


//デストラクタ
Audio::~Audio()
{
	//XACTシャットダウン
	xactEngine->ShutDown();
	//サウンドバンク開放
	SAFE_DELETE_ARRAY(soundBankData);
	//ウェーブバンク開放
	UnmapViewOfFile(mapWaveBank);
	//エンジン開放
	SAFE_RELEASE(xactEngine);
	//COMライブラリ開放
	CoUninitialize();
}


//――――――――――――――――――――――
// 機能：XACTエンジンの作成
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Audio::InitEngine()
{
	//COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//エンジン作成
	if (FAILED(XACT3CreateEngine(0, &xactEngine)))
	{
		//メッセージボックスを表示
		MessageBox(0, "XACTエンジンの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}

	//パラメータ設定
	XACT_RUNTIME_PARAMETERS xactParam = { 0 };
	xactParam.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;

	if (FAILED(xactEngine->Initialize(&xactParam)))
	{
		//メッセージ表示
		MessageBox(0, "XACTエンジンのパラメータ設定に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：WaveBankの読み込み
// 引数：fileName　ファイル名　　
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Audio::LoadWaveBank(char* fileName)
{
	//ファイルを開く
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//ファイルサイズを調べる
	DWORD  fileSize = GetFileSize(hFile, &fileSize);

	//マッピング
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, fileSize, NULL);
	mapWaveBank = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	//ウェーブバンク作成
	if (FAILED(xactEngine->CreateInMemoryWaveBank(mapWaveBank, fileSize, 0, 0, &waveBank)))
	{
		MessageBox(0, "ウェーブバンク作成に失敗しました", fileName, MB_OK);
		return E_FAIL;
	}
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	return S_OK;
}


//――――――――――――――――――――――
// 機能：SoundBankの読み込み
// 引数：fileName
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Audio::LoadSoundBank(char* fileName)
{
	//ファイルを開く
	HANDLE  hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	//ファイルサイズを調べる
	DWORD fileSize = GetFileSize(hFile, &fileSize);

	//データを全部読む
	soundBankData = new BYTE[fileSize];
	DWORD  byteRead;
	ReadFile(hFile, soundBankData, fileSize, &byteRead, NULL);

	//サウンドバンク作成
	if (FAILED(xactEngine->CreateSoundBank(soundBankData, fileSize, 0, 0, &soundBank)))
	{
		//メッセージ表示
		MessageBox(0, "サウンドバンク作成に失敗しました", fileName, MB_OK);
		return E_FAIL;
	}
	//ハンドルを消す
	CloseHandle(hFile);
	return S_OK;
}


//
//――――――――――――――――――――――
// 機能：上記の3つの関数を呼ぶ
// 引数：waveBankFileName	ウェーブバンクのファイル名
// 引数：soundBankFileName	サウンドバンクのファイル名
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Audio::Load(char* waveBankFileName, char* soundBankFileName)
{
	//XACTエンジンの作成
	if (FAILED(InitEngine()))
	{
		return E_FAIL;
	}

	//WaveBank読み込み
	if (FAILED(LoadWaveBank(waveBankFileName)))
	{
		return E_FAIL;
	}

	//SoundBank読み込み
	if (FAILED(LoadSoundBank(soundBankFileName)))
	{
		return E_FAIL;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：音を再生
// 引数：cueName
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Audio::Play(char* cueName)
{
	//キューの番号を取得
	XACTINDEX cueIndex = soundBank->GetCueIndex(cueName);

	//再生
	if (FAILED(soundBank->Play(cueIndex, 0, 0, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：停止する
// 引数：cueName
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Audio::Stop(char* cueName)
{
	//キューの番号を取得
	XACTINDEX cueIndex = soundBank->GetCueIndex(cueName);

	//停止
	if (FAILED(soundBank->Stop(cueIndex, XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE)))
	{
		return E_FAIL;
	}
	return S_OK;
}