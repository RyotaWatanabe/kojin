/*===========================================================================================
�T�@���FFBX�t�@�C����`��
�쐬���F9/10
�X�V���F9/16
����ҁF�n糗ȑ�
=============================================================================================*/


#pragma once
#include "Global.h"
#include <fbxsdk.h>
#pragma comment(lib,"libfbxsdk-mt.lib")


//���C�L���X�g�p�\����
struct RayCastData
{
	D3DXVECTOR3 start;	//���C���ˈʒu
	D3DXVECTOR3 dir;	//���C�̌����x�N�g��
	float		dist;	//�Փ˓_�܂ł̋���
	D3DXVECTOR3 normal;	//�Փ˓_�̖@��
	D3DXVECTOR3 pos;	//�Փˈʒu
	BOOL		hit;	//���C������������
};

class Fbx
{
	FbxManager*		manager;	//FBX�@�\���Ǘ�
	FbxImporter*	importer;	//�t�@�C�����J��
	FbxScene*		scene;		//�J�����t�@�C�����Ǘ�

	//���_�̐�
	int vertexCount;
	//�|���S����������
	int polygonCount;
	//�C���f�b�N�X��������
	int indexCount;
	//�}�e���A��������
	int materialCount;
	//�}�e���A�����Ƃ̃|���S����������
	int* polygonCountOfMaterial;


	//��������_�o�b�t�@������
	IDirect3DVertexBuffer9 *pVertexBuffer;
	//������C���f�b�N�X�o�b�t�@������
	IDirect3DIndexBuffer9 **pIndexBuffer;
	//�}�e���A���̔z�����邽�߂̃|�C���^
	D3DMATERIAL9          *pMaterial;
	//�e�N�X�`���I�u�W�F�N�g
	LPDIRECT3DTEXTURE9 *pTexture;

	//�m�[�h�̓��e�𒲂ׂ�
	HRESULT CheckNode(FbxNode* pNode);
	//���_���
	HRESULT CheckMesh(FbxMesh* pMesh);

	//1�̒��_�ɕK�v�ȃf�[�^
	struct Vertex
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 normal;	//�@�����
		D3DXVECTOR2 uv;		//UV���
	};

	//
	D3DXMATRIX TestWorldMatrix;

public:
	//�R���X�g���N�^
	Fbx();
	//�f�X�g���N�^
	~Fbx();
	//�ǂݍ��ݏ���
	HRESULT Load(char* fileName);
	//�`�揈��
	HRESULT Draw(D3DXMATRIX* matWorld);

	BOOL RayCast(RayCastData *data);

	
};

