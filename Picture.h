/*===========================================================================================
�T�@���F�摜��\�����邽�߂̏���
�쐬���F12/14
�X�V���F12/14
����ҁF�n糗ȑ�
=============================================================================================*/


#pragma once
#include <Windows.h>

class Picture
{
	HDC hdc_mem;		//�������f�o�C�X�R���e�L�X�g�n���h��
	int bmpW, bmpH;		//�摜�̃T�C�Y

public:
	//�f�X�g���N�^
	~Picture();

	//�ǂݍ���
	HRESULT Load(HWND hWnd, char* fileName);
	//�`��
	HRESULT Draw(HDC hdc, int posX, int posY, int sizeX, int sizeY, int cutX, int cutY);
	//�`��i�w��ʒu�ɉ摜�S�̂�`��j
	HRESULT Draw(HDC hdc, int posX, int posY);

	//�A�N�Z�X�֐�
	int GetWidth(){ return bmpW; }
	int GetHeight(){ return bmpH; }
};

