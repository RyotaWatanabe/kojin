/*=======================================================================================================
�T�@���F�g���b�v
�쐬���F1/21
�X�V���F1/21
����ҁF�n糁@�ȑ�
=======================================================================================================*/


#pragma once
#include "UnitBase.h"
#include "Global.h"
#include "Sprite.h"

//���݂̃X�N���[���ʒu�iPlayScene.cpp�Ő錾�j
extern D3DXVECTOR3 g_stageScrollPos;

class Trap : public UnitBase
{
	Sprite* trap;

	int dis;

public:
	Trap();
	~Trap();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�X�V����
	HRESULT Update();
	//�`�揈��
	//�Փ˔��菈��
	HRESULT Hit(UnitBase* pTarget);
	//�����Fhdc	�f�o�C�X�R���e�L�X�g�n���h��
	HRESULT Render();
};

