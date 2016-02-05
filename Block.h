/*===========================================================================================
�T�@���F�u���b�N�i�ǂ�n�ʁA��Q�j��z�u
�쐬���F11/2
�X�V���F1/22
����ҁF�n糗ȑ�
=============================================================================================*/


#pragma once
#include "UnitBase.h"
#include "Global.h"
#include "Sprite.h"

//���݂̃X�N���[���̈ʒu(PlayScene.cpp�Ő錾�ς�)
extern D3DXVECTOR3 g_stageScrollPos;
extern int mapTable[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

class Block : public UnitBase
{
	typedef struct RECT
	{
		int left;	//����x���W
		int top;		//����y���W
		int right;	//�E��x���W
		int bottom;	//�E��y���W
	}RECT;

	//�u���b�N��z�u���邽�߂̃X�v���C�g�^�ϐ�
	Sprite* block;
	

public:
	Block();
	~Block();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�X�V����
	HRESULT Update();
	//�Փ˔��菈��
	HRESULT Hit(UnitBase* pTarget);
	//�`�揈��
	HRESULT Render();

	int GetMap(int y, int x){ return mapTable[y][x]; }
};