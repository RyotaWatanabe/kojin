/*===========================================================================================
�T�@���F�v���C�V�[��
�쐬���F
�X�V���F12/7
����ҁF�n糗ȑ�
=============================================================================================*/


//---------------�C���N���[�h-----------------------
#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Block.h"
#include "Item.h"
#include "Trap.h"

//���݂̃X�N���[���ʒu
D3DXVECTOR3	g_stageScrollPos;

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//	�R���X�g���N�^
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
PlayScene::PlayScene()
{
	//���j�b�g��ǉ�
	unit.push_back(new Stage);
	unit.push_back(new Block);
	unit.push_back(new Item);
	unit.push_back(new Enemy);
	unit.push_back(new Player);
	unit.push_back(new Trap);

	
}