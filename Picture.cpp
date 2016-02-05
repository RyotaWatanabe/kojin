/*===========================================================================================
�T�@���F�摜��\�����邽�߂̏���
�쐬���F12/14
�X�V���F12/14
����ҁF�n糗ȑ�
=============================================================================================*/


#include "Picture.h"


Picture::~Picture()
{
	//�������f�o�C�X�R���e�L�X�g�n���h�����
	DeleteDC(hdc_mem);	
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����FhWnd		�E�B���h�E�n���h��
// �����FfileName	�t�@�C����
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Picture::Load(HWND hWnd, char* fileName)
{
	HDC		hdc;			//�f�o�C�X�R���e�L�X�g�n���h��
	HBITMAP	hBitmap;		//�r�b�g�}�b�v�n���h��

	//�E�B���h�E�̃f�o�C�X�R���e�L�X�g�n���h�����擾
	hdc = GetDC(hWnd);

	//�������f�o�C�X�R���e�L�X�g�i�����Ȃ���p���j���쐬
	hdc_mem = CreateCompatibleDC(hdc);

	//�E�B���h�E�̃f�o�C�X�R���e�L�X�g�n���h���͂����g��Ȃ�
	ReleaseDC(hWnd, hdc);

	//�摜�t�@�C�����J��
	hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//�J�����摜���������f�o�C�X�R���e�L�X�g��
	SelectObject(hdc_mem, hBitmap);

	//�摜�T�C�Y���擾
	BITMAP bmp;				//�F�X�ȏ�񂪓���ϐ�
	GetObject(hBitmap, sizeof(BITMAP), &bmp);	//�����擾
	bmpW = bmp.bmWidth;		//��
	bmpH = bmp.bmHeight;	//����

	//�摜�����
	DeleteObject(hBitmap);

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����Fhdc			�E�B���h�E�̃f�o�C�X�R���e�L�X�g�n���h��
// �����FposX,posY		�`��ʒu
// �����FsizeX,sizeY	�`��T�C�Y
// �����FcutX,cutY		�ؔ����ʒu
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Picture::Draw(HDC hdc, int posX, int posY, int sizeX, int sizeY, int cutX, int cutY)
{
	//�摜��`��
	BitBlt(hdc, posX, posY, sizeX, sizeY, hdc_mem, cutX, cutY, SRCCOPY);

	return S_OK;
}

//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈���i�w��ʒu�ɉ摜�S�̂�`��j
// �����Fhdc			�E�B���h�E�̃f�o�C�X�R���e�L�X�g�n���h��
// �����FposX,posY		�`��ʒu
// �ߒl�F�Ȃ�
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
//�`��i�w��ʒu�ɉ摜�S�̂�`��j
HRESULT Picture::Draw(HDC hdc, int posX, int posY)
{
	Draw(hdc, posX, posY, bmpW, bmpH, 0, 0);

	return S_OK;
}