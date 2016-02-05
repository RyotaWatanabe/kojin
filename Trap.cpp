/*=======================================================================================================
�T�@���F�g���b�v
�쐬���F1/21
�X�V���F1/22
����ҁF�n糁@�ȑ�
=======================================================================================================*/

#include <stdlib.h>
#include "Trap.h"
#include "Player.h"


Trap::Trap()
{
	position = D3DXVECTOR3(rand() % 2000, 0, 0);
	move = D3DXVECTOR3(0, 0, 0);
	//�����X�N���[���ʒu
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);
	trap = NULL;
}


Trap::~Trap()
{
	//���
	SAFE_DELETE(trap);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Trap::Load()
{
	trap = new Sprite;
	//�N���A��ʂ̓ǂݍ���
	if (FAILED(trap->Load("assets\\pict\\iwa.png")))
	{
		return E_FAIL;
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Trap::Update()
{
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�Փ˔��菈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Trap::Hit(UnitBase* pTarget)
{
	//�^�[�Q�b�g���v���C���[��������
	if (typeid(*pTarget) == typeid(Player))
	{
		//���݂̈ʒu
		Player* player = (Player*)pTarget;
		D3DXVECTOR3 playerPos = player->GetPos();

		//�v���C���[����g���b�v�܂ł̋�����2������߂�
		int distance = (position.x - playerPos.x)*(position.x - playerPos.x) +
					   (position.y - playerPos.y)*(position.y - playerPos.y);

		//2��ȓ���������
		if (distance >= ACTOR_SIZE*ACTOR_SIZE)
		{
			
		}
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Trap::Render()
{
	SpriteData trapData;
	trapData.pos = D3DXVECTOR3(position.x + g_stageScrollPos.x, position.y + g_stageScrollPos.y, 0);
	trapData.scale = D3DXVECTOR2(0.3f, 0.3f);
	trap->Draw(&trapData);
	return S_OK;
}