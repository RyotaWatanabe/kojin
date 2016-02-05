/*===========================================================================================
�T�@���F�Q�[���̓��͏���
�쐬���F6/10
�X�V���F6/23
����ҁF�n糗ȑ�
=============================================================================================*/


#include "Input.h"


//�R���X�g���N�^
Input::Input()
{
	//������
	ZeroMemory(keyState, sizeof(keyState));
}


//�f�X�g���N�^
Input::~Input()
{
	//�L�[�{�[�h�̃A�N�Z�X�������
	if (pKeyDevice)
	{
		pKeyDevice->Unacquire();
	}

	//DirectInput���
	SAFE_RELEASE(pKeyDevice);
	SAFE_RELEASE(pDinput);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�FDirectInput�̏���
// �����FhWnd
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Input::Init(HWND hWnd)
{
	//DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (LPVOID*)&pDinput, NULL)))
	{
		return E_FAIL;
	}

	// �uDirectInput�f�o�C�X�v�I�u�W�F�N�g�̍쐬
	if (FAILED(pDinput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, NULL)))
	{
		return E_FAIL;
	}

	// �f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(pKeyDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������x���̐ݒ�
	if (FAILED(pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND)))
	{
		return E_FAIL;
	}
	return S_OK;
}


//
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�e���̓f�o�C�X�̏�Ԃ��擾
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT  Input::Update()
{
	//�O��̃R���g���[���[�̏�Ԃ��m��
	memcpy(&prevControllerState, &controllerState, sizeof(&controllerState));


	////�R���g���[���[�̏�Ԃ��擾
	//for (int i = 0; i < 4; i++)
	//{
	//	
	//}

	Keyflg = XInputGetState(0, &controllerState[0]);

	// �f�o�C�X�̃A�N�Z�X�����擾����
	HRESULT hr = pKeyDevice->Acquire();


	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		//�O��̃L�[�̏�Ԃ��m��
		memcpy(prevKeyState, keyState, sizeof(keyState));
		//�S�ẴL�[�̏�Ԃ��擾
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);
		return S_OK;
	}
	return E_FAIL;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�C�ӂ̃L�[��������Ă��邩�`�F�b�N
// �����FkeyCode
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL Input::IsKeyPush(DWORD keyCode)
{
	//�C�ӂ̃L�[��������Ă��邩
	if (keyState[keyCode] & 0x80)
	{
		return TRUE; //�����Ă���
	}
	return FALSE;    //�����ĂȂ�
}



//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�C�ӂ̃L�[�������ꂽ�u�Ԃ��`�F�b�N
// �����FkeyCode
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL Input::IsKeyTap(DWORD keyCode)
{
	if (!(prevKeyState[keyCode] & 0x80) && keyState[keyCode] & 0x80)
	{
		return TRUE; //�������u��
	}
	return FALSE;    //���̑�
}



//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�C�ӂ̃L�[�𗣂����u�Ԃ��`�F�b�N
// �����FkeyCode
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL Input::IsKeyRelease(DWORD keyCode)
{
	if (prevKeyState[keyCode] & 0x80 && !(keyState[keyCode] & 0x80))
	{
		return TRUE; //�������u��
	}
	return FALSE;    //���̑�
}


////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�R���g���[���[�̃{�^����������Ă��邩
//// �����FbuttonCode
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//BOOL Input::IsPadButtonPush(DWORD buttonCode, int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	if (controllerState[ID].Gamepad.wButtons & buttonCode)
//	{
//		return TRUE; //�����Ă�
//	}
//	return FALSE;   //�����ĂȂ�
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�R���g���[���[�̃{�^���������ꂽ�u�Ԃ��`�F�b�N
//// �����FbuttonCode
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
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
//		return TRUE; //�������u��
//	}
//	return FALSE;   //���̑�
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�R���g���[���[�̃{�^���𗣂����u�Ԃ��`�F�b�N
//// �����FbuttonCode
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
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
//		return TRUE; //�������u��
//	}
//	return FALSE;   //���̑�
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F���X�e�B�b�N�̍��E�̌X��
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//float Input::GetPadLStickX(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbLX;
//	//�f�b�h�]�[��
//	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F���X�e�B�b�N�̏㉺�̌X��
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//float Input::GetPadLStickY(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbLY;
//	//�f�b�h�]�[��
//	if (value < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�E�X�e�B�b�N�̍��E�̌X��
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//float Input::GetPadRStickX(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbRX;
//	//�f�b�h�]�[��
//	if (value < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�E�X�e�B�b�N�̏㉺�̌X��
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//float Input::GetPadRStickY(int ID)
//{
//	if (Keyflg == ERROR_DEVICE_NOT_CONNECTED)
//	{
//		return 0.0f;
//	}
//
//	float value = controllerState[ID].Gamepad.sThumbRY;
//	//�f�b�h�]�[��
//	if (value < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && value > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
//	{
//		return 0.0f;
//	}
//	return value / 32768;
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F���g���K�[�̉�������
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//float Input::GetPadLTrigger(int ID)
//{
//	float value = controllerState[ID].Gamepad.bLeftTrigger;
//	//�f�b�h�]�[��
//	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
//	{
//		return 0.0f;
//	}
//	return value / 255;
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�E�g���K�[�̉�������
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//float Input::GetPadRTrigger(int ID)
//{
//	float value = controllerState[ID].Gamepad.bRightTrigger;
//	//�f�b�h�]�[��
//	if (value < XINPUT_GAMEPAD_TRIGGER_THRESHOLD  && value > -XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
//	{
//		return 0.0f;
//	}
//	return value / 255;
//}
//
//
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//// �@�\�F�U���G�t�F�N�g
//// �����FleftSpeed�@�����̃��[�^�[�̐U���̋���
//// �����FrightSpeed �E���̃��[�^�[�̐U���̋���
//// �����FID
//// �ߒl�F����/���s
////�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//void Input::Vibration(float leftSpeed, float rightSpeed, int ID)
//{
//	XINPUT_VIBRATION vibration[4];
//	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));		//������
//	//�U���̋���
//	vibration[ID].wLeftMotorSpeed = leftSpeed * 65535;		//�����[�^�[
//	vibration[ID].wRightMotorSpeed = rightSpeed * 65535;	//�E���[�^�[
//	XInputSetState(ID, &vibration[ID]);
//}