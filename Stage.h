/*===========================================================================================
�T�@���F�X�e�[�W�̕`��
�쐬���F10/21
�X�V���F11/2
����ҁF�n糗ȑ�
=============================================================================================*/


#pragma once
#include "Global.h"
#include "UnitBase.h"
#include "Sprite.h"


//���݂̃X�N���[���ʒu�iPlayScene.cpp�Ő錾�j
extern D3DXVECTOR3 g_stageScrollPos;

class Stage : public UnitBase
{
	//�X�e�[�W�i�n�ʁj��`�悷�邽�߂ɕK�v�ȕϐ�
	Sprite* stage;

public:
	Stage();
	~Stage();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�`�揈��
	HRESULT Render();
	//�X�e�[�W�����擾����A�N�Z�X�֐�
	Sprite* GetStage(){ return stage; }
};

