/*===========================================================================================
�T�@���F�v���C���[����������
�쐬���F10/15
�X�V���F12/9
����ҁF�n糗ȑ�
=============================================================================================*/


#pragma once
#include "Global.h"
#include "UnitBase.h"
#include "Sprite.h"
#include "Fbx.h"
#include "windef.h"


//���݂̃X�N���[���ʒu�iPlayScene.cpp�Ő錾�j
extern D3DXVECTOR3 g_stageScrollPos;

class Player :public UnitBase
{
	typedef struct RECT 
	{
		int x;
		int y;	
		int w;
		int h;
	};
	RECT playerRect;

	//�v���C���[�̏��
	enum
	{
		STATUS_NORMAL,	//�ʏ�
		STATUS_DEAD,	//���񂾂Ƃ��i�G�̍U���ɓ���������A�g���b�v�Ɉ�������������A�����������肵���Ƃ��j
		DOWN_SCROLL,	//���փX�N���[��
		UP_SCROLL		//��փX�N���[��
	}status;

	//�v���C���[��`�悷�邽�߂̃X�v���C�g�^�ϐ�
	Sprite* player;	

	int deadCount;	//��e���Ă���̃t���[����

	int dir;	//�v���C���[�̌���
	int anim;	//�v���C���[�̑�����

	BOOL JumpFlag;		//�W�����v�t���O

	void Move();		//�v���C���[�̈ړ�����
	//void Attack();	//�v���C���[�̍U��
	void Dead();		//�v���C���[�����񂾂Ƃ��̏���

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//�ǂݍ��ݏ���
	HRESULT Load();
	//�X�V����
	HRESULT Update();
	//�Փ˔��菈��
	//�����FpTarget	���肷�鑊�胆�j�b�g
	HRESULT Hit(UnitBase* pTarget);
	//�`�揈��
	//�����Fhdc	�f�o�C�X�R���e�L�X�g�n���h��
	HRESULT Render();
};