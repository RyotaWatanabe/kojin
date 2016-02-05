/*=======================================================================================================
�T�@���F�Q�[���S�̗̂������������
�쐬���F
�X�V���F1/13
����ҁF�n糗ȑ�
=======================================================================================================*/


//---------------�C���N���[�h-----------------------
#include "Game.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ClearScene.h"
#include "GameOverScene.h"
#include "Camera.h"


//----------------�O���[�o���ϐ�----------------
GAME_SCENE			g_gameScene;	//���݂̃Q�[���V�[��
LPDIRECT3DDEVICE9	g_pDevice;		//Direct3D�f�o�C�X�I�u�W�F�N�g
Input*          g_pInput;			//���͏����I�u�W�F�N�g
Camera*			g_pCamera;			//�J�����I�u�W�F�N�g


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Game::Game()
{
	//�e�V�[���I�u�W�F�N�g�̐���
	scene[SC_TITLE] =	new TitleScene;		//�^�C�g���V�[��
	scene[SC_PLAY] =	new PlayScene;		//�v���C�V�[��
	scene[SC_CLEAR] =	new ClearScene;		//�N���A�V�[��
	scene[SC_GAMEOVER] = new GameOverScene;	//�Q�[���I�[�o�[�V�[��

	//�ŏ��̃V�[��
	g_gameScene = SC_TITLE;

	//�J����
	g_pCamera = new Camera;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�f�X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
Game::~Game()
{
	//�e�V�[���̉��
	for (int i = 0; i < SC_MAX; i++)
	{
		SAFE_DELETE(scene[i]);
	}

	//Direct3D���
	SAFE_RELEASE(g_pDevice);
	SAFE_RELEASE(pD3d);

	//�J�����I�u�W�F�N�g�̉��
	SAFE_DELETE(g_pCamera);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�FDirect3D������
// �����FhWnd
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::InitD3d(HWND hWnd)
{
   // �uDirect3D�v�I�u�W�F�N�g�̍쐬
   if (NULL == (pD3d = Direct3DCreate9(D3D_SDK_VERSION)))
   {
      MessageBox(0, "Direct3D�̍쐬�Ɏ��s���܂���", "", MB_OK);
      return E_FAIL;
   }

   //�uDIRECT3D�f�o�C�X�v�I�u�W�F�N�g�̍쐬
   D3DPRESENT_PARAMETERS d3dpp;
   ZeroMemory(&d3dpp, sizeof(d3dpp));	//����������
   d3dpp.BackBufferFormat =			D3DFMT_UNKNOWN;			//�o�b�t�@�̃T�[�t�F�X�t�H�[�}�b�g���w��
   d3dpp.BackBufferCount =			1;						//�o�b�N�o�b�t�@�̐����擾
   d3dpp.SwapEffect =				D3DSWAPEFFECT_DISCARD;	//�X���b�v�G�t�F�N�g���`
   d3dpp.Windowed =					TRUE;					
   d3dpp.EnableAutoDepthStencil =	TRUE;
   d3dpp.AutoDepthStencilFormat =	D3DFMT_D16;
 
   if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
	   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))
   {
	   MessageBox(0, "HAL���[�h��DIRECT3D�f�o�C�X���쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�", NULL, MB_OK);

	   if (FAILED(pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
		   D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice)))
	   {
		   MessageBox(0, "DIRECT3D�f�o�C�X�̍쐬�Ɏ��s���܂���", NULL, MB_OK);
		   return E_FAIL;
	   }
   }

   if (FAILED(g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)))
   {
	   MessageBox(0, "�J�����O���[�h�̐ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
	   return E_FAIL;
   }

   if (FAILED(g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE) ||
	   g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA) ||
	   g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA)))
   {
	   MessageBox(0, "�A���t�@�u�����h�̐ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
	   return E_FAIL;
   }

   if (FAILED(g_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2)))
   {
	   MessageBox(0, "�e�N�X�`���X�e�[�g�̐ݒ�Ɏ��s���܂���", "�G���[", MB_OK);
	   return E_FAIL;
   }

   //Game::InitLight�֐����Ă�
   if (FAILED(InitLight()))
   {
	   return E_FAIL;
   }
   return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�Փ˔���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Hit()
{
	if (FAILED(scene[g_gameScene]->Hit()))
	{
		return E_FAIL;
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Load()
{
	for (int i = 0; i < SC_MAX; i++)
	{
		if (FAILED(scene[i]->Load()))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Update()
{
	if (FAILED(g_pCamera->Update()))
	{
		return E_FAIL;
	}

	g_pInput->Update();
	
	if (FAILED(scene[g_gameScene]->Update()))
	{
		return E_FAIL;
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::Render()
{
	//��ʂ��N���A
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
									D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pDevice->BeginScene()))
	{
		//�Q�[����ʂ̕`��
		if (FAILED(scene[g_gameScene]->Render()))
		{
			return E_FAIL;
		}

		//�`��I��
		g_pDevice->EndScene();
	}

	//�t���b�v
	g_pDevice->Present(NULL, NULL, NULL, NULL);
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F���C�g�̐ݒ�
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Game::InitLight()
{
	//���C�g�̐ݒ荀�ڂ��܂Ƃ߂��\���̂̕ϐ���p��
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ��f�B���N�V���i�����C�g�i���s�����j�ɂ���
	light.Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̌������w��
	light.Direction = D3DXVECTOR3(1.0f, -1.0f, 1.0f);

	//���C�g�̐F�i�����j
	light.Diffuse.r = 1.0f;	//��
	light.Diffuse.g = 1.0f;	//��
	light.Diffuse.b = 1.0f;	//��

	//�A���r�G���g�i�Ԑڌ��j
	light.Ambient.r = 0.4f;
	light.Ambient.g = 0.4f;
	light.Ambient.b = 0.4f;

	//���C�g�̍쐬
	if (FAILED(g_pDevice->SetLight(0, &light)))
	{
		MessageBox(0, "���C�g���Z�b�g�ł��܂���ł���", "Game", MB_OK);
		return E_FAIL;
	}

	//���C�g��ON�ɂ���
	if (FAILED(g_pDevice->LightEnable(0, TRUE)))
	{
		MessageBox(0, "���C�g��L���ɂł��܂���ł���", "Game", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}