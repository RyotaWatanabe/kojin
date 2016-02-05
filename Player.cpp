/*=======================================================================================================
�T�@���F�v���C���[���j�b�g
�쐬���F10/15
�X�V���F2/5
����ҁF�n糁@�ȑ�
=======================================================================================================*/


#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Block.h"
#include "Item.h"


//-----------------�萔�錾--------------------
#define MOVE_SPEED	2		//�v���C���[�̈ړ����x
#define DASH_SPEED	0.3f	//�v���C���[�̃_�b�V�����x
#define JUMP_POWER	9.0f	//�W�����v��
#define DAMAGE_TIME	25		//�����閳�G����


Player::Player()
{
	//�v���C���[�̏����ʒu
	position = D3DXVECTOR3(0, WINDOW_HEIGHT - 96, 0);
	//�ړ���
	move = D3DXVECTOR3(0, 0, 0);
	//�����X�N���[���ʒu
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);
	//�������
	status = STATUS_NORMAL;
	//������
	player = NULL;

	playerRect.x = 0;
	playerRect.y = 0;
	playerRect.w = 32;
	playerRect.h = 32;
}


Player::~Player()
{
	//���
	SAFE_DELETE(player);
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Player::Load()
{
	player = new Sprite;
	//�v���C���[�̓ǂݍ���
	if (FAILED(player->Load("Assets\\Pict\\Actor.png")))
	{
		MessageBox(0, "�v���C���[��ǂݍ��߂܂���ł����B", "�ǂݍ��݃G���[", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�X�V����
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Player::Update()
{
	//��Ԃ��Ƃɏ����𕪂���
	switch (status)
	{
		//�ʏ���
	case STATUS_NORMAL:
		Move();		//�v���C���[�̈ړ�
		//Attack();	//�U��
		break;

		//���փX�N���[����
	case DOWN_SCROLL:
		g_stageScrollPos.y -= 20;	//��ʂ��X�N���[��
		position.y += 3;			//�v���C���[���ړ�
		//�L���̗ǂ��Ƃ���܂ł�������ʏ��Ԃɖ߂�
		if ((int)g_stageScrollPos.y % WINDOW_HEIGHT == 0)
		{
			status = STATUS_NORMAL;
		}
		break;

		//��փX�N���[����
	case UP_SCROLL:
		g_stageScrollPos.y += 20;
		position.y -= 3;
		if ((int)g_stageScrollPos.y % WINDOW_HEIGHT == 0)
		{
			status = STATUS_NORMAL;
		}
		break;

		//���񂾏��
	case STATUS_DEAD:
		Dead();		//��莞�Ԍo������ʏ��Ԃɖ߂�
		break;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�Փ˔��菈��
// �����F�Ȃ�
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Player::Hit(UnitBase* pTarget)
{
	//�^�[�Q�b�g���G��������
	if (typeid(*pTarget) == typeid(Enemy))
	{
		//�G�̌��݂̈ʒu
		Enemy* enemy = (Enemy*)pTarget;
		D3DXVECTOR2 enemyPos = enemy->GetPos();

		//�v���C���[����G�܂ł̋�����2������߂�
		int distance = (position.x - enemyPos.x) * (position.x - enemyPos.x) +
					   (position.y - enemyPos.y) * (position.y - enemyPos.y);

		//�L�����T�C�Y��2��ȓ���������
		if (distance <= (ACTOR_SIZE * ACTOR_SIZE))
		{
			//�v���C���[����
			status = STATUS_DEAD;
		}
	}

	//�^�[�Q�b�g���u���b�N��������
	if (typeid(*pTarget) == typeid(Block))
	{
		//���݂̈ʒu
		Block* block = (Block*)pTarget;

		int x = position.x;
		int y = position.y;

		if (block->GetMap(y , x) == 1 )
		{
			
			move.y = 0;
		}
		
	}

	//�^�[�Q�b�g���A�C�e����������
	if (typeid(*pTarget) == typeid(Item))
	{
		//���݂̈ʒu
		Item* item = (Item*)pTarget;
		D3DXVECTOR3 itemPos = item->GetPos();

		//�v���C���[����u���b�N�܂ł̋�����2������߂�
		int distance = (position.x - itemPos.x)*(position.x - itemPos.x) +
			(position.y - itemPos.y)*(position.y - itemPos.y);

		//2��ȓ���������
		if (distance <= ACTOR_SIZE*ACTOR_SIZE)
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
HRESULT Player::Render()
{
	//�v���C���[�摜�̃T�C�Y����
	SpriteData playerData;
	playerData.pos = position + g_stageScrollPos;	//�\���ʒu�̓X�N���[�����������炷
	playerData.size = D3DXVECTOR2(32,32);			//�T�C�Y
	playerData.cut.y = dir * 32;					//�ؔ����ʒu
	playerData.cut.x = ((anim / 9) % 4) * 32;
	
	switch (status)
	{
		//�ʏ��Ԃ̂Ƃ�
	case STATUS_NORMAL:
		//�v���C���[�̕`��
		player->Draw(&playerData);
		break;

		//���񂾂Ƃ�
	case STATUS_DEAD:
		Dead();
		break;
	}

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ړ�����
// �����F�Ȃ�
// �ߒl�F�Ȃ�
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void Player::Move()
{
	//�uA�v���������ꍇ
	if (g_pInput->IsKeyPush(DIK_A))
	{
		//�������֐i��
		position.x -= MOVE_SPEED;
		dir = 1;	//��������
		anim++;		//������
	}

	//�uA�v�Ɓu��Shift�v�������Ă���ꍇ
	if (g_pInput->IsKeyPush(DIK_A) && g_pInput->IsKeyPush(DIK_LSHIFT))
	{
		//�������փ_�b�V��
		position.x -= MOVE_SPEED + DASH_SPEED;
		dir = 1;	//��������
		anim++;		//������
	}

	//�uD�v�������Ă���ꍇ
	if (g_pInput->IsKeyPush(DIK_D))
	{
		//�E�����֐i��
		position.x += MOVE_SPEED;
		dir = 2;	//�E������
		anim++;		//������
	}

	//�uD�v�Ɓu��Shift�v�������Ă���ꍇ
	if (g_pInput->IsKeyPush(DIK_D) && g_pInput->IsKeyPush(DIK_LSHIFT))
	{
		//�E�����փ_�b�V��
		position.x += MOVE_SPEED +DASH_SPEED;
		dir = 2;	//�E������
		anim++;		//������
	}

	//��ʍ��[�ɒ�������
	if (position.x <= 0)
	{
		//���[�ɂԂ���
		position.x = 0;		
	}

	//�W�����v�t���O�������ĂȂ���΁i�n�ʂɂ��鎞�j
	if (!JumpFlag)
	{
		//�X�y�[�X�L�[�������ƃW�����v����
		if (g_pInput->IsKeyTap(DIK_SPACE))
		{
			move.y -= JUMP_POWER;
			JumpFlag = TRUE;
		}
	}
	
	//�v���C���[�ɏd�͂�������
	position.y += move.y;
	move.y += GRAVITY;

	//�n�ʂɍ~���ۂɒn�ʂɒ��n����悤�ɂ���
	if (position.y >= WINDOW_HEIGHT - 96)
	{
		move.y = 0;
		JumpFlag = FALSE;
	}

	//�v���C���[���^�񒆂ɗ���悤�A���X�N���[���ʒu���Z�o
	g_stageScrollPos.x = -position.x + (WINDOW_WIDTH / 2 - 32);

	//���X�N���[���������̏ꍇ�̏���
	if (g_stageScrollPos.x > 0)
		g_stageScrollPos.x = 0;

	if (g_stageScrollPos.x < -(2000 - WINDOW_WIDTH))
		g_stageScrollPos.x = -(2000 - WINDOW_WIDTH);

	////��ʉ��[�܂ōs�����Ƃ�
	//if (position.y + g_stageScrollPos.y > WINDOW_HEIGHT - 64)
	//{
	//	//���փX�N���[������
	//	status = DOWN_SCROLL;
	//}

	//��ʏ�[�܂ōs�����Ƃ�
	if (position.y + g_stageScrollPos.y < 0)
	{
		//��փX�N���[������
		status = UP_SCROLL;
	}
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�u���v��Ԃ̎��̏���
// �����F�Ȃ�
// �ߒl�F�Ȃ�
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
void Player::Dead()
{
	//�J�E���g�A�b�v
	deadCount++;

	//��莞�Ԍo������ʏ��Ԃɖ߂�
	if (deadCount >= DAMAGE_TIME)
	{
		status = STATUS_NORMAL;
	}
}