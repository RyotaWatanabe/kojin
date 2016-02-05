/*===========================================================================================
概　略：ゲームの入力処理
作成日：6/10
更新日：6/23
制作者：渡邉諒太
=============================================================================================*/


#include "Input.h"


//コンストラクタ
Input::Input()
{
	//初期化
	ZeroMemory(keyState, sizeof(keyState));
}


//デストラクタ
Input::~Input()
{
	//キーボードのアクセス権を解放
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}

	//DirectInput解放
	SAFE_RELEASE(pKeyDevice);
	SAFE_RELEASE(pDinput);
}


//――――――――――――――――――――――
// 機能：DirectInputの準備
// 引数：hWnd
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Input::Init(HWND hWnd)
{
	//DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (LPVOID*)&pDinput, NULL)))
	{
		return E_FAIL;
	}

	// 「DirectInputデバイス」オブジェクトの作成
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return E_FAIL;
	}

	// デバイスをキーボードに設定
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調レベルの設定
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return E_FAIL;
	}
	return S_OK;
}


//
//――――――――――――――――――――――
// 機能：各入力デバイスの状態を取得
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT  Input::Update()
{
	//前回のコントローラーの状態を確保
	memcpy(&prevControllerState, &controllerState, sizeof(&controllerState));


	////コントローラーの状態を取得
	//for (int i = 0; i < 4; i++)
	//{
	//	
	//}

	Keyflg = XInputGetState(0, &controllerState[0]);

	// デバイスのアクセス権を取得する
	HRESULT hr = pKeyDevice->Acquire();


	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		//前回のキーの状態を確保
		memcpy(prevKeyState, keyState, sizeof(keyState));
		//全てのキーの状態を取得
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
		return S_OK;
	}
	return E_FAIL;
}


//――――――――――――――――――――――
// 機能：任意のキーが押されているかチェック
// 引数：keyCode
// 戻値：成功/失敗
//――――――――――――――――――――――
BOOL Input::IsKeyPush(DWORD keyCode)
{
	//任意のキーが押されているか
	if (keyState[keyCode] & 0x80)
	{
		return TRUE; //押している
	}
	return FALSE;    //押してない
}



//――――――――――――――――――――――
// 機能：任意のキーが押された瞬間かチェック
// 引数：keyCode
// 戻値：成功/失敗
//――――――――――――――――――――――
BOOL Input::IsKeyTap(DWORD keyCode)
{
	if (!(prevKeyState[keyCode] & 0x80) && keyState[keyCode] & 0x80)
	{
		return TRUE; //押した瞬間
	}
	return FALSE;    //その他
}



//――――――――――――――――――――――
// 機能：任意のキーを離した瞬間かチェック
// 引数：keyCode
// 戻値：成功/失敗
//――――――――――――――――――――――
BOOL Input::IsKeyRelease(DWORD keyCode)
{
	if (prevKeyState[keyCode] & 0x80 && !(keyState[keyCode] & 0x80))
	{
		return TRUE; //離した瞬間
	}
	return FALSE;    //その他
}


////――――――――――――――――――――――
//// 機能：コントローラーのボタンが押されているか
//// 引数：buttonCode
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//BOOL Input::IsPadButtonPush(DWORD buttonCode, int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	if (controllerState[ID].Gamepad.wButtons & buttonCode)
//	{
//		return TRUE; //押してる
//	}
//	return FALSE;   //押してない
//}
//
//
////――――――――――――――――――――――
//// 機能：コントローラーのボタンが押された瞬間かチェック
//// 引数：buttonCode
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//BOOL Input::IsPadButtonTap(DWORD buttonCode, int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	if (!(prevControllerState[ID].Gamepad.wButtons & buttonCode)
//		&& controllerState[ID].Gamepad.wButtons & buttonCode)
//	{
//		return TRUE; //押した瞬間
//	}
//	return FALSE;   //その他
//}
//
//
////――――――――――――――――――――――
//// 機能：コントローラーのボタンを離した瞬間かチェック
//// 引数：buttonCode
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//BOOL Input::IsPadButtonRelease(DWORD buttonCode, int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	if (prevControllerState[ID].Gamepad.wButtons & buttonCode
//		&& !(controllerState[ID].Gamepad.wButtons & buttonCode))
//	{
//		return TRUE; //離した瞬間
//	}
//	return FALSE;   //その他
//}
//
//
////――――――――――――――――――――――
//// 機能：左スティックの左右の傾き
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//float Input::GetPadLStickX(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbLX;
//	//デッドゾーン
//	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////――――――――――――――――――――――
//// 機能：左スティックの上下の傾き
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//float Input::GetPadLStickY(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbLY;
//	//デッドゾーン
//	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////――――――――――――――――――――――
//// 機能：右スティックの左右の傾き
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//float Input::GetPadRStickX(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbRX;
//	//デッドゾーン
//	if (value < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////――――――――――――――――――――――
//// 機能：右スティックの上下の傾き
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//float Input::GetPadRStickY(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbRY;
//	//デッドゾーン
//	if (value < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////――――――――――――――――――――――
//// 機能：左トリガーの押し込み
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//float Input::GetPadLTrigger(int ID)
//{
//	float value = controllerState[ID].Gamepad.bLeftTrigger;
//	//デッドゾーン
//	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
//	{
//		return 0.0f;
//	}
//	return value / 255;
//}
//
//
////――――――――――――――――――――――
//// 機能：右トリガーの押し込み
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//float Input::GetPadRTrigger(int ID)
//{
//	float value = controllerState[ID].Gamepad.bRightTrigger;
//	//デッドゾーン
//	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
//	{
//		return 0.0f;
//	}
//	return value / 255;
//}
//
//
////――――――――――――――――――――――
//// 機能：振動エフェクト
//// 引数：leftSpeed　左側のモーターの振動の強さ
//// 引数：rightSpeed 右側のモーターの振動の強さ
//// 引数：ID
//// 戻値：成功/失敗
////――――――――――――――――――――――
//void Input::Vibration(float leftSpeed, float rightSpeed, int ID)
//{
//	XINPUT_VIBRATION vibration[4];
//	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));		//初期化
//	//振動の強さ
//	vibration[ID].wLeftMotorSpeed = leftSpeed * 65535;		//左モーター
//	vibration[ID].wRightMotorSpeed = rightSpeed * 65535;	//右モーター
//	XInputSetState(ID, &vibration[ID]);
//}