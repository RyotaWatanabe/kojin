/*===========================================================================================
�T�@���F�X�e�[�W�̕`��
�쐬���F10/21
�X�V���F11/11
����ҁF�n糗ȑ�
=============================================================================================*/


#include "Stage.h"
#include "Camera.h"

//�R���X�g���N�^
Stage::Stage()
{
	//�����X�N���[���ʒu
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);

	//������
	stage = NULL;
}


//�f�X�g���N�^
Stage::~Stage()
{
	//���
	SAFE_DELETE(stage);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Stage::Load()
{
	//�X�e�[�W(�w�i�ǂݍ���)
	stage = new Sprite;
	if (FAILED(stage->Load("Assets\\Pict\\stage2.jpg")))
	{
		MessageBox(0, "�X�e�[�W��ǂݍ��߂܂���ł����B", "�ǂݍ��݃G���[", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Stage::Render()
{
	//�X�e�[�W�i�w�i�j�̕`��
	SpriteData stageData;
	stageData.pos = D3DXVECTOR3(g_stageScrollPos.x, g_stageScrollPos.y*WINDOW_HEIGHT, 0);
	stage->Draw(&stageData);

	return S_OK;
}