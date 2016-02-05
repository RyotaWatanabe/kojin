/*=======================================================================================================
�T�@���F�J�����̐ݒ�
�쐬���F8/27
�X�V���F9/15
����ҁF�n糗ȑ�
=======================================================================================================*/


#include "Camera.h"


//�R���X�g���N�^
Camera::Camera()
{
	pos = D3DXVECTOR3(0, 10, -30);	//�J�����̈ʒu
	target = D3DXVECTOR3(0, 0, 0);	//�J�����̏œ_�ʒu
	upVec = D3DXVECTOR3(0, 1, 0);	//�����

	//��p
	angle = 60;
	//�A�X�y�N�g��
	aspect = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
	//�߃N���b�s���O
	nearClip = 0.1f;
	//���N���b�s���O
	farClip = 1000.0f;
}


//�f�X�g���N�^
Camera::~Camera()
{

}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�J�����̈ʒu�������ݒ�i�r���[�s��j
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Camera::SetView()
{
	//�r���[�s����쐬
	D3DXMatrixLookAtLH(&view, &pos, &target, &upVec);

	//�s��̎�ނ��w��i�r���[�s��j
	if (FAILED(g_pDevice->SetTransform(D3DTS_VIEW, &view)))
	{
		//���s�����ꍇ���b�Z�[�W��\��
		MessageBox(0, "�r���[�s��̐ݒ�Ɏ��s���܂���", "Camera", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F��p��A�X�y�N�g���ݒ�i�ˉe�s��j
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Camera::SetProjection()
{
	//�ˉe�s����쐬
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(angle), aspect, nearClip, farClip);

	//�s��̎�ނ��w��i�ˉe�s��j
	if (FAILED(g_pDevice->SetTransform(D3DTS_PROJECTION, &proj)))
	{
		//���s�����ꍇ���b�Z�[�W��\��
		MessageBox(0, "�ˉe�s��̐ݒ�Ɏ��s���܂���", "Camera", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Camera::Update()
{
	//Camera::SetView�֐����Ă�
	if (FAILED(SetView()))
	{
		return E_FAIL;
	}

	//Camera::SetProjection�֐����Ă�
	if (FAILED(SetProjection()))
	{
		return E_FAIL;
	}

	return S_OK;
}

