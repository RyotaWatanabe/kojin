/*===========================================================================================
�T�@���FFBX�t�@�C����`��
�쐬���F9/10
�X�V���F9/15
����ҁF�n糗ȑ�
=============================================================================================*/


#include "Fbx.h"


//�R���X�g���N�^
Fbx::Fbx()
{
	vertexCount = 0;
	polygonCount = 0;
	indexCount = 0;
	materialCount = 0;
	pVertexBuffer = NULL;
	pIndexBuffer = NULL;
	pMaterial = NULL;
	polygonCountOfMaterial = NULL;
	pTexture = NULL;
	D3DXMatrixIdentity(&TestWorldMatrix);
}


//�f�X�g���N�^
Fbx::~Fbx()
{
	//���
	for (int i = 0; i < materialCount; i++)
	{
		SAFE_RELEASE(pIndexBuffer[i]);
	}
	SAFE_DELETE_ARRAY(pIndexBuffer);
	SAFE_RELEASE(pVertexBuffer);
	SAFE_DELETE_ARRAY(pMaterial);
	SAFE_DELETE_ARRAY(polygonCountOfMaterial);
	SAFE_DELETE_ARRAY(pTexture);
	manager->Destroy();
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�ǂݍ��ݏ���
// �����FfileName
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Fbx::Load(char* fileName)
{
	//�}�l�[�W���[���쐬�iFBX�@�\���Ǘ��j
	manager = FbxManager::Create();
	//�C���|�[�^�[�i�t�@�C�����J���j
	importer = FbxImporter::Create(manager, "");
	//�V�[���i�J�����t�@�C�����Ǘ��j
	scene = FbxScene::Create(manager, "");

	//�C���|�[�^�[���g��FBX�t�@�C�����J��
	importer->Initialize(fileName);
	//�J�����t�@�C�����V�[���ɓn��
	importer->Import(scene);
	//���
	importer->Destroy();

	//���݂̃J�����g�f�B���N�g���𒲂ׂ�
	char  defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	char    dir[MAX_PATH];
	//�t�H���_���𔲂������dir�ɓ����
	_splitpath_s(fileName, NULL, 0, dir, MAX_PATH, NULL, 0, NULL, 0);
	//�ȍ~�t�@�C���̓ǂݏ����͂��̃t�H���_�ɍs��
	SetCurrentDirectory(dir);

	//FBX�t�@�C����ǂݍ��񂾃V�[�����烋�[�g�m�[�h�����o��
	FbxNode* rootNode = scene->GetRootNode();
	//���[�g�m�[�h�̎q���ǂ̂��炢����̂����ׂ�
	int childCount = rootNode->GetChildCount();

	//�q�̐��������[�v�������ԂɃm�[�h����n���Ă���
	for (int i = 0; childCount > i; i++)	
	{
		CheckNode(rootNode->GetChild(i));	//����->GetChild(��)�́A�����́��Ԗڂ̎q���Ƃ����Ӗ�
	}

	SetCurrentDirectory(defaultCurrentDir);

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�`�揈��
// �����FmatWorld
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Fbx::Draw(D3DXMATRIX* matWorld)
{
	//���[���h�s��̎w��
	if (FAILED(g_pDevice->SetTransform(D3DTS_WORLD, matWorld)))
	{
		MessageBox(0, "���[���h�s��̐ݒ�Ɏ��s���܂���", "Fbx", MB_OK);
		return E_FAIL;
	}

	//���_�X�g���[���̎w��i�@�����ǉ��j
	if (FAILED(g_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)))
	{
		MessageBox(0, "���_�X�g���[���̐ݒ�Ɏ��s���܂���", "Fbx", MB_OK);
		return E_FAIL;
	}

	//���_�o�b�t�@�̎w��
	if (FAILED(g_pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex))))
	{
		MessageBox(0, "���_�o�b�t�@�̐ݒ�Ɏ��s���܂���", "Fbx", MB_OK);
		return E_FAIL;
	}

	for (int i = 0; i < materialCount; i++)
	{
		//�C���f�b�N�X�o�b�t�@�̎w��
		if (FAILED(g_pDevice->SetIndices(pIndexBuffer[i])))
		{
			MessageBox(0, "�C���f�b�N�X�o�b�t�@�̐ݒ�Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}

		//�}�e���A���̎w��
		if (FAILED(g_pDevice->SetMaterial(&pMaterial[i])))
		{
			MessageBox(0, "�}�e���A���̐ݒ�Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}

		//�e�N�X�`���̃Z�b�g
		if (FAILED(g_pDevice->SetTexture(0, pTexture[i])))
		{
			MessageBox(0, "�e�N�X�`���̃Z�b�g�Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}

		//���b�V���̕`��
		if (FAILED(g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, indexCount, 0, polygonCountOfMaterial[i])))
		{
			MessageBox(0, "���b�V���̕`��Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}
	}

	//
	TestWorldMatrix = *matWorld;

	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F�m�[�h�̓��e�𒲂ׂ�
// �����FpNode
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT Fbx::CheckNode(FbxNode* pNode)
{	
	//�󂯎�����m�[�h�̑������擾
	FbxNodeAttribute* attr = pNode->GetNodeAttribute();

	//�^�C�v��FbxNodeAttribute::eMesh�Ȃ�
	if (attr->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		//���b�V���m�[�h������
		materialCount = pNode->GetMaterialCount();
		//�}�e���A���̐��𒲂ׁA�}�e���A��������ϐ���z��ɂ���
		pMaterial = new D3DMATERIAL9[materialCount];
		//�e�N�X�`�����}�e���A�����Ɏw��
		pTexture = new LPDIRECT3DTEXTURE9[materialCount];

		//�P���}�e���A������ǂݍ���
		for (int i = 0; i < materialCount; i++)
		{
			FbxSurfaceLambert* pLambert = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			//�f�B�t�[�Y�i�|���S���̐F�j�擾
			FbxDouble3  diffuse = pLambert->Diffuse;
			//�A���r�G���g�i�����j�擾
			FbxDouble3  ambient = pLambert->Ambient;

			ZeroMemory(&pMaterial[i], sizeof(D3DMATERIAL9));

			//�f�B�t�[�Y���擾
			pMaterial[i].Diffuse.r = (float)diffuse[0];
			pMaterial[i].Diffuse.g = (float)diffuse[1];
			pMaterial[i].Diffuse.b = (float)diffuse[2];
			pMaterial[i].Diffuse.a = 1.0f;

			//�A���r�G���g���擾
			pMaterial[i].Ambient.r = (float)ambient[0];
			pMaterial[i].Ambient.g = (float)ambient[1];
			pMaterial[i].Ambient.b = (float)ambient[2];
			pMaterial[i].Ambient.a = 1.0f;

			//�e�N�X�`���̏����w��
			FbxProperty  lProperty = pNode->GetMaterial(i)->FindProperty(FbxSurfaceMaterial::sDiffuse);
			//�t�@�C���̏����擾
			FbxFileTexture* textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);

			//textureFile��NULL�ɂȂ��Ă�΃e�N�X�`����\���ĂȂ�
			if (textureFile == NULL)
			{
				pTexture[i] = NULL;
			}
			else
			{
				//�摜�t�@�C����ǂݍ���
				const char* textureFileName = textureFile->GetFileName();

				char    name[_MAX_FNAME];	//�t�@�C����
				char    ext[_MAX_EXT];		//�g���q

				//name��ext�Ƀt�@�C�����Ɗg���q������
				_splitpath_s(textureFileName, NULL, 0, NULL, 0, name, _MAX_FNAME, ext, _MAX_EXT);

				//name�Ɂu������.�����v�Ƃ����悤�Ƀt�@�C�����{�g���q������
				wsprintf(name, "%s%s", name, ext);

				//�e�N�X�`�����쐬
				if (FAILED(D3DXCreateTextureFromFileEx(g_pDevice, name, 0, 0, 0, 0, D3DFMT_UNKNOWN,
					D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &pTexture[i])))
				{
					MessageBox(0, "�e�N�X�`���̍쐬�Ɏ��s���܂���", name, MB_OK);
					return E_FAIL;
				}
			}
		}

		CheckMesh(pNode->GetMesh());
	}
	else
	{
		//�����̎q�̐��𒲂ׂĂ��ꂼ��̎q�Ɋւ��Ă�CheckNode�֐��Œ��ׂ�
		int childCount = pNode->GetChildCount();
		for (int i = 0; childCount > i; i++)
		{
			//�ċA�Ăяo��
			CheckNode(pNode->GetChild(i));
		}
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F���_���i�ʒu�A�F�Ȃǁj�����o��
// �����FpMesh
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
HRESULT  Fbx::CheckMesh(FbxMesh* pMesh)
{
	//���_����ǂݍ��ށi�擪�A�h���X���m�ہj
	FbxVector4* pVertexPos = pMesh->GetControlPoints();

	//���_�̐��𒲂ׂ�
	vertexCount = pMesh->GetControlPointsCount();
	Vertex* pVertexList = new Vertex[vertexCount];

	//�񎟌��z��ɂȂ��Ă���pVertexPos����A�������pVertexList�̃����o�ϐ�pos�Ƀf�[�^���R�s�[
	for (int i = 0; vertexCount > i; i++)
	{
		pVertexList[i].pos.x = (float)pVertexPos[i][0];
		pVertexList[i].pos.y = (float)pVertexPos[i][1];
		pVertexList[i].pos.z = (float)pVertexPos[i][2];
	}

	FbxStringList uvSetName;
	pMesh->GetUVSetNames(uvSetName);
	int uvCount = uvSetName.GetCount();
	bool unMap = false;
	FbxVector2  uv;

	//�|���S�����擾
	polygonCount = pMesh->GetPolygonCount();

	//�|���S�����Ƃɒ��ׂ邽�߂Ƀ|���S���̐��������[�v������
	for (int i = 0; i < polygonCount; i++)
	{
		//i�Ԗڂ̃|���S�����ǂ̒��_�łł��Ă���̂��𒲂ׂ�
		int   startIndex = pMesh->GetPolygonVertexIndex(i);

		//3���_���̏���������
		for (int j = 0; j < 3; j++)
		{
			//index�ɒ��ׂ������_�̔ԍ�������
			int index = pMesh->GetPolygonVertices()[startIndex + j];

			//�@���̎擾
			FbxVector4  Normal;
			pMesh->GetPolygonVertexNormal(i, j, Normal);

			//�\���̂̒��_���ɓ������
			pVertexList[index].normal = D3DXVECTOR3((float)Normal[0], (float)Normal[1], (float)Normal[2]);

			//UV���̎擾
			//i�Ԗڂ̃|���S����j�Ԗڂ̒��_��UV��񂪉��Ԗڂɓ����Ă��邩�����߂�
			//int uvIndex = pMesh->GetTextureUVIndex(i, j, FbxLayerElement::eTextureDiffuse);

			////�ϐ�uv�Ɂ��Ԗڂ�UV��������
			//FbxVector2  uv = pMesh->GetLayer(0)->GetUVs()->GetDirectArray().GetAt(uvIndex);
			//pVertexList[index].uv = D3DXVECTOR2((float)uv.mData[0], (float)(1.0 - uv.mData[1]));

			for (int k = 0; k < uvCount; k++)
			{
				FbxString name = uvSetName.GetStringAt(k);
				pMesh->GetPolygonVertexUV(i, j, name, uv, unMap);
				pVertexList[index].uv = D3DXVECTOR2((float)uv.mData[0], (float)(1.0 - uv.mData[1]));
			}
		}
	}

	//��̒��_�o�b�t�@��p�ӂ���i�@�����ǉ��j
	if (FAILED(g_pDevice->CreateVertexBuffer(sizeof(Vertex)* vertexCount, 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
		D3DPOOL_MANAGED, &pVertexBuffer, 0)))
	{
		MessageBox(0, "���_�o�b�t�@�̍쐬�Ɏ��s���܂���", "Fbx", MB_OK);
		return E_FAIL;
	}

	//���_��������Vertex�\���̌^�̃|�C���^
	Vertex *pVertexCopy;

	//���_�o�b�t�@�̃��b�N�A�܂�pVertexCopy�ɓ��ꂽ���̂����_�o�b�t�@�ɂȂ�
	if (FAILED(pVertexBuffer->Lock(0, 0, (void**)&pVertexCopy, 0)))
	{
		MessageBox(0, "���_�o�b�t�@�̃��b�N�Ɏ��s���܂���", "Fbx", MB_OK);
		return E_FAIL;
	}
	
	//pVertexCopy��pVertexList�̓��e���R�s�[
	memcpy(pVertexCopy, pVertexList, sizeof(Vertex)*vertexCount);

	//���_�o�b�t�@���A�����b�N
	if (FAILED(pVertexBuffer->Unlock()))
	{
		MessageBox(0, "���_�o�b�t�@�̃A�����b�N�Ɏ��s���܂���", "Fbx", MB_OK);
		return E_FAIL;
	}

	//���
	SAFE_DELETE_ARRAY(pVertexList);

	//�C���f�b�N�X���擾
	indexCount = pMesh->GetPolygonVertexCount();

	//�C���f�b�N�X����ǂݍ��ޑO�ɔz��ɂ���
	pIndexBuffer = new IDirect3DIndexBuffer9*[materialCount];

	//�}�e���A���̐��̔z��
	polygonCountOfMaterial = new int[materialCount];

	for (int i = 0; i < materialCount; i++)
	{
		//�ꎞ�I�ɃC���f�b�N�X�������邽�߂̔z��
		int* pIndexList = new int[indexCount];
		int count = 0;

		//�C���f�b�N�X�������Ă���
		//pMesh->GetPolygonVertex(��,��)�Ə����΁A���Ԗڂ̃|���S���́��Ԗڂ̒��_�̔ԍ������߂���B
		for (int polygon = 0; polygon < polygonCount; polygon++)
		{
			//�����Ă���|���S�������Ԗڂ̃}�e���A���̂��̂��m�F
			int materialID = pMesh->GetLayer(0)->GetMaterials()->GetIndexArray().GetAt(polygon);

			//���ꂪi�Ԗڂł���΂��̃|���S����3���_���C���f�b�N�X���ipIndexList�j�ɒǉ�
			if (materialID == i)
			{
				for (int vertex = 0; vertex < 3; vertex++)
				{
					pIndexList[count++] = pMesh->GetPolygonVertex(polygon, vertex);
				}
			}
		}
		//count�ϐ����o�^�������_���ɂȂ��Ă��邩�炻���3�Ŋ���΃|���S�����ɂȂ�
		polygonCountOfMaterial[i] = count / 3;

		//��̃C���f�b�N�X�o�b�t�@�̍쐬
		if (FAILED(g_pDevice->CreateIndexBuffer(sizeof(int)* indexCount, 0, D3DFMT_INDEX32,
			D3DPOOL_MANAGED, &pIndexBuffer[i], 0)))
		{
			MessageBox(0, "�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}

		//�f�[�^���R�s�[���邽�߂̕ϐ�
		DWORD *pIndexCopy;

		//�C���f�b�N�X�o�b�t�@�̃��b�N
		if (FAILED(pIndexBuffer[i]->Lock(0, 0, (void**)&pIndexCopy, 0)))
		{
			MessageBox(0, "�C���f�b�N�X�o�b�t�@�̃��b�N�Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}

		//pVertexCopy��pVertexList�̓��e���R�s�[
		memcpy(pIndexCopy, pIndexList, sizeof(int)* indexCount);

		//�C���f�b�N�X�o�b�t�@�̃A�����b�N
		if (FAILED(pIndexBuffer[i]->Unlock()))
		{
			MessageBox(0, "�C���f�b�N�X�o�b�t�@�̃A�����b�N�Ɏ��s���܂���", "Fbx", MB_OK);
			return E_FAIL;
		}

		//���
		SAFE_DELETE_ARRAY(pIndexList);
	}
	return S_OK;
}


//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
// �@�\�F���C�ɂ���ďՓ˂����o����
// �����Fdata	
// �ߒl�F����/���s
//�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\�\
BOOL Fbx::RayCast(RayCastData *data)
{
	data->dist = 99999.0f;
	data->hit = false;


	//���_�o�b�t�@�ɃA�N�Z�X�ł���悤��
	Vertex *pVertexCopy;
	pVertexBuffer->Lock(0, 0, (void**)&pVertexCopy, 0);


	//�}�e���A����
	for (DWORD i = 0; i < materialCount; i++)
	{
		//�C���f�b�N�X�o�b�t�@�ɃA�N�Z�X�ł���悤��
		DWORD *pIndexCopy;
		pIndexBuffer[i]->Lock(0, 0, (void**)&pIndexCopy, 0);

		//���̃}�e���A���̃|���S����
		for (DWORD j = 0; j < polygonCountOfMaterial[i]; j++)
		{
			//3���_��
			D3DXVECTOR3 ver[3];
			ver[0] = pVertexCopy[pIndexCopy[j * 3 + 0]].pos;
			ver[1] = pVertexCopy[pIndexCopy[j * 3 + 1]].pos;
			ver[2] = pVertexCopy[pIndexCopy[j * 3 + 2]].pos;

			D3DXVec3TransformCoord(&ver[0], &ver[0], &TestWorldMatrix);
			D3DXVec3TransformCoord(&ver[1], &ver[1], &TestWorldMatrix);
			D3DXVec3TransformCoord(&ver[2], &ver[2], &TestWorldMatrix);

			//�Ԃ����Ă邩�`�F�b�N
			float dist, u, v;
			BOOL hit = D3DXIntersectTri(&ver[0], &ver[1], &ver[2], &data->start, &data->dir, &u, &v, &dist);

			//���܂ň�ԋ߂��H
			if (hit && dist < data->dist)
			{
				data->hit = true;
				data->dist = dist;
				D3DXVECTOR3 v1 = ver[2]-ver[0];
				D3DXVECTOR3 v2 = ver[1]-ver[0];
				D3DXVec3Cross(&data->normal , &v1, &v2);
				D3DXVec3Normalize(&data->normal, &data->normal);
				
				data->pos = ver[0] + u * (ver[1] - ver[0]) + v * (ver[2] - ver[0]);
			}
		}

		//�C���f�b�N�X�o�b�t�@�g�p�I��
		pIndexBuffer[i]->Unlock();
	}

	//���_�o�b�t�@�g�p�I��
	pVertexBuffer->Unlock();

	return data->hit;
}