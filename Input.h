/*===========================================================================================
概　略：ゲームの入力処理
作成日：6/10
更新日：6/23
制作者：渡邉諒太
=============================================================================================*/

#pragma once

#define DIRECTINPUT_VERSION 0x800 //DirectInput のバージョン設定
#define SAFE_RELEASE(p) { if(p != NULL) { (p)->Release(); (p) = NULL; } }
#include <dinput.h>
#include "XInput.h"
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"Xinput.lib")

class Input
{
	LPDIRECTINPUT8 pDinput;					//DirectInputオブジェクト
	LPDIRECTINPUTDEVICE8  pKeyDevice;		//デバイスオブジェクト（キーボード）
	BYTE keyState[256];						//各キーの状態
	BYTE prevKeyState[256];					//前回の各キーの状態
	XINPUT_STATE    controllerState[4];		//コントローラーの状態
	XINPUT_STATE    prevControllerState[4];	//前回のコントローラーの状態
	DWORD Keyflg;		//エラー用
public:
	Input();	//コンストラクタ
	~Input();	//デストラクタ
	HRESULT Init(HWND hWnd);					//DirectInputの準備
	HRESULT Update();							//各入力デバイスの状態を取得
	BOOL  IsKeyPush(DWORD keyCode);				//任意のキーが押されているかチェック
	BOOL  IsKeyTap(DWORD keyCode);				//任意のキーが押された瞬間かチェック
	BOOL  IsKeyRelease(DWORD keyCode);			//任意のキーを離した瞬間かチェック
	//BOOL  IsPadButtonPush(DWORD buttonCode, int ID = 0);	//コントローラーのボタンが押されているか
	//BOOL  IsPadButtonTap(DWORD buttonCode, int ID = 0);		//コントローラーのボタンが押された瞬間かチェック
	//BOOL  IsPadButtonRelease(DWORD buttonCode, int ID = 0);	//コントローラーのボタンを離した瞬間かチェック
	//float GetPadLStickX(int ID = 0);						//左スティックの左右の傾き
	//float GetPadLStickY(int ID = 0);						//左スティックの上下の傾き
	//float GetPadRStickX(int ID = 0);						//右スティックの左右の傾き
	//float GetPadRStickY(int ID = 0);						//右スティックの上下の傾き
	//float GetPadLTrigger(int ID = 0);						//左トリガーの押し込み
	//float GetPadRTrigger(int ID = 0);						//右トリガーの押し込み
	//void  Vibration(float leftSpeed, float rightSpeed, int ID = 0);	//振動エフェクト
};


