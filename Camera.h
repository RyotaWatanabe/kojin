/*=======================================================================================================
�T�@���F�J�����̐ݒ�
�쐬���F8/27(��)
�X�V���F8/27(��)
����ҁF�n糗ȑ�
=======================================================================================================*/


#pragma once
#include "Global.h"


class Camera
{
	D3DXVECTOR3 pos;    //�J�����̈ʒu
	D3DXVECTOR3 target; //�œ_�ʒu
	D3DXVECTOR3 upVec;  //�����

	float angle;        //��p
	float aspect;		//�A�X�y�N�g��
	float nearClip;		//�߃N���b�s���O
	float farClip;		//���N���b�s���O

	D3DXMATRIX  view;   //�r���[�s��
	D3DXMATRIX  proj;	//�ˉe�s��

	HRESULT SetView();			//�r���[�s������֐�
	HRESULT SetProjection();	//�ˉe�s������֐�

public:
	Camera();
	~Camera();

	HRESULT Update();	//�X�V����

	//�A�N�Z�X�֐�
	void SetPos(D3DXVECTOR3 v){ pos = v; }
	void SetTarget(D3DXVECTOR3 v){ target = v; }
	void SetUp(D3DXVECTOR3 v){ upVec = v; }

	void SetAngle(float f){ angle = f; }
	void SetAspect(float f){ aspect = f; }
	void SetNearClip(float f){ nearClip = f; }
	void SetFarClip(float f){ farClip = f; }

};

