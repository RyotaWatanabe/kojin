/*=======================================================================================================
�T�@���F�A�C�e��
�쐬���F12/7
�X�V���F1/22
����ҁF�n糁@�ȑ�
=======================================================================================================*/


#include "Item.h"
#include "Player.h"



//�R���X�g���N�^
Item::Item()
{
	//�����X�N���[���ʒu
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);

	//�����ʒu
	position = D3DXVECTOR3(500, WINDOW_HEIGHT-CHIP_SIZE*3, 0);

	item = NULL;
}


//�f�X�g���N�^
Item::~Item()
{
	SAFE_DELETE(item);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Item::Load()
{
	item = new Sprite;

	//�v���C���[�̓ǂݍ���
	if (FAILED(item->Load("Assets\\Pict\\item.png")))
	{
		MessageBox(0, "�A�C�e����ǂݍ��߂܂���ł����B", "�ǂݍ��݃G���[", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Item::Update()
{
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�Փ˔��菈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Item::Hit(UnitBase* pTarget)
{
	//�^�[�Q�b�g���A�C�e����������
	if (typeid(*pTarget) == typeid(Player))
	{
		//���݂̈ʒu
		Player* player = (Player*)pTarget;
		D3DXVECTOR3 playerPos = player->GetPos();

		//�A�C�e������v���C���[�܂ł̋�����2������߂�
		int distance = (position.x - playerPos.x)*(position.x - playerPos.x) +
					   (position.y - playerPos.y)*(position.y - playerPos.y);

		//2��ȓ���������
		if (distance <= ACTOR_SIZE*ACTOR_SIZE)
		{
			position.y = 999;
		}
	}
	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Item::Render()
{
	SpriteData itemData;
	itemData.pos = D3DXVECTOR3(position.x + g_stageScrollPos.x, position.y + g_stageScrollPos.y, 0);
	item->Draw(&itemData);
	return S_OK;
}