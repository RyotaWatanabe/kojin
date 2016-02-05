/*=======================================================================================================
�T�@���F�G���j�b�g
�쐬���F10/28
�X�V���F12/7
����ҁF�n糁@�ȑ�
=======================================================================================================*/


#include "Enemy.h"
#include "Player.h"


//�R���X�g���N�^
Enemy::Enemy()
{
	//�G�̏����ʒu
	position.x = 300;
	position.y = WINDOW_HEIGHT - 140;
	//�G�̈ړ���
	move.x = 0.7;
	move.y = 0;
	//�����X�N���[���ʒu
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);
	//������
	enemy = NULL;
	enemy2 = NULL;
	//�G�������Ă��鎞TRUE�i�t���O�j
	enemyLive = TRUE;
}


//�f�X�g���N�^
Enemy::~Enemy()
{
	//���
	SAFE_DELETE(enemy);
	SAFE_DELETE(enemy2);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Enemy::Load()
{
	enemy = new Sprite;
	enemy2 = new Sprite;

	//�G�̓ǂݍ���
	if (FAILED(enemy->Load("Assets\\Pict\\enemy1.png")))
	{
		MessageBox(0, "�G��ǂݍ��߂܂���ł����B", "�ǂݍ��݃G���[", MB_OK);
		return E_FAIL;
	}
	if (FAILED(enemy2->Load("Assets\\Pict\\enemy1_1.png")))
	{
		MessageBox(0, "�G��ǂݍ��߂܂���ł����B", "�ǂݍ��݃G���[", MB_OK);
		return E_FAIL;
	}
	
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Enemy::Update()
{
	//�����Ă����
	if (enemyLive)
	{
		//�ȒP�Ȉړ�
		position.x += move.x;
	
		//��ʍ��[
		if (position.x < 300)
			move.x *= -1;		//���˕Ԃ�

		//��ʉE�[
		if (position.x > 400)
			move.x *= -1;		//���˕Ԃ�
	}
	
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Enemy::Hit(UnitBase* pTarget)
{
	
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Enemy::Render()
{
	//�G��`�悷�邽�߂̃X�v���C�g�f�[�^�^�ϐ����쐬
	SpriteData enemyData;
	//�G�̈ʒu
	enemyData.pos = D3DXVECTOR3(position.x + g_stageScrollPos.x, position.y + g_stageScrollPos.y, 0);

	//�����Ă���Ε\������
	if (enemyLive)
	{
		//�`��
		enemy->Draw(&enemyData);
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�G��|�����Ƃ��̏���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Enemy::Kill()
{
	//�t���O��߂�
	enemyLive = FALSE;

	//�Ԃ���Ȃ��悤�K���Ȉʒu��
	position.y = -999;

	return S_OK;
}