/*===========================================================================================
�T�@���F�Q�[���I�[�o�[��ʂ���������
�쐬���F2016/1/13
�X�V���F2016/1/13
����ҁF�n糗ȑ�
=============================================================================================*/


#pragma once
#include "UnitBase.h"
#include "Sprite.h"

class GameOver : public UnitBase
{
	Sprite* gameover;
public:
	GameOver();
	~GameOver();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�X�V����
	HRESULT Update();
	//�`�揈��
	//�����Fhdc	�f�o�C�X�R���e�L�X�g�n���h��
	HRESULT Render();
};

