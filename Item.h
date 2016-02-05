/*=======================================================================================================
�T�@���F�A�C�e��
�쐬���F12/7
�X�V���F12/7
����ҁF�n糁@�ȑ�
=======================================================================================================*/

#pragma once
#include "UnitBase.h"
#include "Sprite.h"
#include "Global.h"

//���݂̃X�N���[���ʒu�iPlayScene.cpp�Ő錾�j
extern D3DXVECTOR3 g_stageScrollPos;

class Item : public UnitBase
{
	//�A�C�e���I�u�W�F�N�g
	Sprite* item;

public:
	Item();
	~Item();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�X�V����
	HRESULT Update();
	//�Փ˔��菈��
	HRESULT Hit(UnitBase* pTarget);
	//�`�揈��
	HRESULT Render();
};

