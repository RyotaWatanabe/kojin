/*===========================================================================================
�T�@���F�N���A��ʂ���������
�쐬���F4/21
�X�V���F
����ҁF�n糗ȑ�
=============================================================================================*/
#pragma once

//---------------�C���N���[�h-----------------------
#include "UnitBase.h"
#include "Sprite.h"

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�N���A�N���X
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
class Clear :public UnitBase
{
	Sprite sprite;

public:
	//�R���X�g���N�^
	Clear();
	//�f�X�g���N�^
	~Clear();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�X�V����
	HRESULT Update();
	//�`�揈��
	//�����Fhdc	�f�o�C�X�R���e�L�X�g�n���h��
	HRESULT Render();
};
