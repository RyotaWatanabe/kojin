/*===========================================================================================
概　略：FBXファイルを描画
作成日：9/10
更新日：9/15
制作者：渡邉諒太
=============================================================================================*/


#include "Fbx.h"


//コンストラクタ
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


//デストラクタ
Fbx::~Fbx()
{
	//解放
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


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：fileName
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Fbx::Load(char* fileName)
{
	//マネージャーを作成（FBX機能を管理）
	manager = FbxManager::Create();
	//インポーター（ファイルを開く）
	importer = FbxImporter::Create(manager, "");
	//シーン（開いたファイルを管理）
	scene = FbxScene::Create(manager, "");

	//インポーターを使いFBXファイルを開く
	importer->Initialize(fileName);
	//開いたファイルをシーンに渡す
	importer->Import(scene);
	//解放
	importer->Destroy();

	//現在のカレントディレクトリを調べる
	char  defaultCurrentDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, defaultCurrentDir);

	char    dir[MAX_PATH];
	//フォルダ名を抜き取ってdirに入れる
	_splitpath_s(fileName, NULL, 0, dir, MAX_PATH, NULL, 0, NULL, 0);
	//以降ファイルの読み書きはそのフォルダに行う
	SetCurrentDirectory(dir);

	//FBXファイルを読み込んだシーンからルートノードを取り出す
	FbxNode* rootNode = scene->GetRootNode();
	//ルートノードの子がどのくらいあるのか調べる
	int childCount = rootNode->GetChildCount();

	//子の数だけループさせ順番にノード情報を渡していく
	for (int i = 0; childCount > i; i++)	
	{
		CheckNode(rootNode->GetChild(i));	//○○->GetChild(△)は、○○の△番目の子供という意味
	}

	SetCurrentDirectory(defaultCurrentDir);

	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：matWorld
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Fbx::Draw(D3DXMATRIX* matWorld)
{
	//ワールド行列の指定
	if (FAILED(g_pDevice->SetTransform(D3DTS_WORLD, matWorld)))
	{
		MessageBox(0, "ワールド行列の設定に失敗しました", "Fbx", MB_OK);
		return E_FAIL;
	}

	//頂点ストリームの指定（法線情報追加）
	if (FAILED(g_pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)))
	{
		MessageBox(0, "頂点ストリームの設定に失敗しました", "Fbx", MB_OK);
		return E_FAIL;
	}

	//頂点バッファの指定
	if (FAILED(g_pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(Vertex))))
	{
		MessageBox(0, "頂点バッファの設定に失敗しました", "Fbx", MB_OK);
		return E_FAIL;
	}

	for (int i = 0; i < materialCount; i++)
	{
		//インデックスバッファの指定
		if (FAILED(g_pDevice->SetIndices(pIndexBuffer[i])))
		{
			MessageBox(0, "インデックスバッファの設定に失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}

		//マテリアルの指定
		if (FAILED(g_pDevice->SetMaterial(&pMaterial[i])))
		{
			MessageBox(0, "マテリアルの設定に失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}

		//テクスチャのセット
		if (FAILED(g_pDevice->SetTexture(0, pTexture[i])))
		{
			MessageBox(0, "テクスチャのセットに失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}

		//メッシュの描画
		if (FAILED(g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, indexCount, 0, polygonCountOfMaterial[i])))
		{
			MessageBox(0, "メッシュの描画に失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}
	}

	//
	TestWorldMatrix = *matWorld;

	return S_OK;
}


//――――――――――――――――――――――
// 機能：ノードの内容を調べる
// 引数：pNode
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Fbx::CheckNode(FbxNode* pNode)
{	
	//受け取ったノードの属性を取得
	FbxNodeAttribute* attr = pNode->GetNodeAttribute();

	//タイプがFbxNodeAttribute::eMeshなら
	if (attr->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		//メッシュノードだった
		materialCount = pNode->GetMaterialCount();
		//マテリアルの数を調べ、マテリアルを入れる変数を配列にする
		pMaterial = new D3DMATERIAL9[materialCount];
		//テクスチャをマテリアル毎に指定
		pTexture = new LPDIRECT3DTEXTURE9[materialCount];

		//１つずつマテリアル情報を読み込む
		for (int i = 0; i < materialCount; i++)
		{
			FbxSurfaceLambert* pLambert = (FbxSurfaceLambert*)pNode->GetMaterial(i);
			//ディフーズ（ポリゴンの色）取得
			FbxDouble3  diffuse = pLambert->Diffuse;
			//アンビエント（環境光）取得
			FbxDouble3  ambient = pLambert->Ambient;

			ZeroMemory(&pMaterial[i], sizeof(D3DMATERIAL9));

			//ディフーズ情報取得
			pMaterial[i].Diffuse.r = (float)diffuse[0];
			pMaterial[i].Diffuse.g = (float)diffuse[1];
			pMaterial[i].Diffuse.b = (float)diffuse[2];
			pMaterial[i].Diffuse.a = 1.0f;

			//アンビエント情報取得
			pMaterial[i].Ambient.r = (float)ambient[0];
			pMaterial[i].Ambient.g = (float)ambient[1];
			pMaterial[i].Ambient.b = (float)ambient[2];
			pMaterial[i].Ambient.a = 1.0f;

			//テクスチャの情報を指定
			FbxProperty  lProperty = pNode->GetMaterial(i)->FindProperty(FbxSurfaceMaterial::sDiffuse);
			//ファイルの情報を取得
			FbxFileTexture* textureFile = lProperty.GetSrcObject<FbxFileTexture>(0);

			//textureFileがNULLになってればテクスチャを貼ってない
			if (textureFile == NULL)
			{
				pTexture[i] = NULL;
			}
			else
			{
				//画像ファイルを読み込む
				const char* textureFileName = textureFile->GetFileName();

				char    name[_MAX_FNAME];	//ファイル名
				char    ext[_MAX_EXT];		//拡張子

				//nameとextにファイル名と拡張子を入れる
				_splitpath_s(textureFileName, NULL, 0, NULL, 0, name, _MAX_FNAME, ext, _MAX_EXT);

				//nameに「○○○.△△」というようにファイル名＋拡張子が入る
				wsprintf(name, "%s%s", name, ext);

				//テクスチャを作成
				if (FAILED(D3DXCreateTextureFromFileEx(g_pDevice, name, 0, 0, 0, 0, D3DFMT_UNKNOWN,
					D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, NULL, NULL, NULL, &pTexture[i])))
				{
					MessageBox(0, "テクスチャの作成に失敗しました", name, MB_OK);
					return E_FAIL;
				}
			}
		}

		CheckMesh(pNode->GetMesh());
	}
	else
	{
		//自分の子の数を調べてそれぞれの子に関してもCheckNode関数で調べる
		int childCount = pNode->GetChildCount();
		for (int i = 0; childCount > i; i++)
		{
			//再帰呼び出し
			CheckNode(pNode->GetChild(i));
		}
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：頂点情報（位置、色など）を取り出す
// 引数：pMesh
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT  Fbx::CheckMesh(FbxMesh* pMesh)
{
	//頂点情報を読み込む（先頭アドレスを確保）
	FbxVector4* pVertexPos = pMesh->GetControlPoints();

	//頂点の数を調べる
	vertexCount = pMesh->GetControlPointsCount();
	Vertex* pVertexList = new Vertex[vertexCount];

	//二次元配列になっているpVertexPosから、今作ったpVertexListのメンバ変数posにデータをコピー
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

	//ポリゴン数取得
	polygonCount = pMesh->GetPolygonCount();

	//ポリゴンごとに調べるためにポリゴンの数だけループさせる
	for (int i = 0; i < polygonCount; i++)
	{
		//i番目のポリゴンがどの頂点でできているのかを調べる
		int   startIndex = pMesh->GetPolygonVertexIndex(i);

		//3頂点分の処理をする
		for (int j = 0; j < 3; j++)
		{
			//indexに調べたい頂点の番号が入る
			int index = pMesh->GetPolygonVertices()[startIndex + j];

			//法線の取得
			FbxVector4  Normal;
			pMesh->GetPolygonVertexNormal(i, j, Normal);

			//構造体の頂点情報に入れられる
			pVertexList[index].normal = D3DXVECTOR3((float)Normal[0], (float)Normal[1], (float)Normal[2]);

			//UV情報の取得
			//i番目のポリゴンのj番目の頂点のUV情報が何番目に入っているかを求める
			//int uvIndex = pMesh->GetTextureUVIndex(i, j, FbxLayerElement::eTextureDiffuse);

			////変数uvに○番目のUV情報を入れる
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

	//空の頂点バッファを用意する（法線情報追加）
	if (FAILED(g_pDevice->CreateVertexBuffer(sizeof(Vertex)* vertexCount, 0, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1,
		D3DPOOL_MANAGED, &pVertexBuffer, 0)))
	{
		MessageBox(0, "頂点バッファの作成に失敗しました", "Fbx", MB_OK);
		return E_FAIL;
	}

	//頂点情報を扱うVertex構造体型のポインタ
	Vertex *pVertexCopy;

	//頂点バッファのロック、つまりpVertexCopyに入れたものが頂点バッファになる
	if (FAILED(pVertexBuffer->Lock(0, 0, (void**)&pVertexCopy, 0)))
	{
		MessageBox(0, "頂点バッファのロックに失敗しました", "Fbx", MB_OK);
		return E_FAIL;
	}
	
	//pVertexCopyにpVertexListの内容をコピー
	memcpy(pVertexCopy, pVertexList, sizeof(Vertex)*vertexCount);

	//頂点バッファをアンロック
	if (FAILED(pVertexBuffer->Unlock()))
	{
		MessageBox(0, "頂点バッファのアンロックに失敗しました", "Fbx", MB_OK);
		return E_FAIL;
	}

	//解放
	SAFE_DELETE_ARRAY(pVertexList);

	//インデックス数取得
	indexCount = pMesh->GetPolygonVertexCount();

	//インデックス情報を読み込む前に配列にする
	pIndexBuffer = new IDirect3DIndexBuffer9*[materialCount];

	//マテリアルの数の配列
	polygonCountOfMaterial = new int[materialCount];

	for (int i = 0; i < materialCount; i++)
	{
		//一時的にインデックス数を入れるための配列
		int* pIndexList = new int[indexCount];
		int count = 0;

		//インデックス情報を入れていく
		//pMesh->GetPolygonVertex(○,△)と書けば、○番目のポリゴンの△番目の頂点の番号を求められる。
		for (int polygon = 0; polygon < polygonCount; polygon++)
		{
			//今見ているポリゴンが何番目のマテリアルのものか確認
			int materialID = pMesh->GetLayer(0)->GetMaterials()->GetIndexArray().GetAt(polygon);

			//それがi番目であればそのポリゴンの3頂点をインデックス情報（pIndexList）に追加
			if (materialID == i)
			{
				for (int vertex = 0; vertex < 3; vertex++)
				{
					pIndexList[count++] = pMesh->GetPolygonVertex(polygon, vertex);
				}
			}
		}
		//count変数が登録した頂点数になっているからそれを3で割ればポリゴン数になる
		polygonCountOfMaterial[i] = count / 3;

		//空のインデックスバッファの作成
		if (FAILED(g_pDevice->CreateIndexBuffer(sizeof(int)* indexCount, 0, D3DFMT_INDEX32,
			D3DPOOL_MANAGED, &pIndexBuffer[i], 0)))
		{
			MessageBox(0, "インデックスバッファの作成に失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}

		//データをコピーするための変数
		DWORD *pIndexCopy;

		//インデックスバッファのロック
		if (FAILED(pIndexBuffer[i]->Lock(0, 0, (void**)&pIndexCopy, 0)))
		{
			MessageBox(0, "インデックスバッファのロックに失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}

		//pVertexCopyにpVertexListの内容をコピー
		memcpy(pIndexCopy, pIndexList, sizeof(int)* indexCount);

		//インデックスバッファのアンロック
		if (FAILED(pIndexBuffer[i]->Unlock()))
		{
			MessageBox(0, "インデックスバッファのアンロックに失敗しました", "Fbx", MB_OK);
			return E_FAIL;
		}

		//解放
		SAFE_DELETE_ARRAY(pIndexList);
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：レイによって衝突を検出する
// 引数：data	
// 戻値：成功/失敗
//――――――――――――――――――――――
BOOL Fbx::RayCast(RayCastData *data)
{
	data->dist = 99999.0f;
	data->hit = false;


	//頂点バッファにアクセスできるように
	Vertex *pVertexCopy;
	pVertexBuffer->Lock(0, 0, (void**)&pVertexCopy, 0);


	//マテリアル毎
	for (DWORD i = 0; i < materialCount; i++)
	{
		//インデックスバッファにアクセスできるように
		DWORD *pIndexCopy;
		pIndexBuffer[i]->Lock(0, 0, (void**)&pIndexCopy, 0);

		//そのマテリアルのポリゴン毎
		for (DWORD j = 0; j < polygonCountOfMaterial[i]; j++)
		{
			//3頂点分
			D3DXVECTOR3 ver[3];
			ver[0] = pVertexCopy[pIndexCopy[j * 3 + 0]].pos;
			ver[1] = pVertexCopy[pIndexCopy[j * 3 + 1]].pos;
			ver[2] = pVertexCopy[pIndexCopy[j * 3 + 2]].pos;

			D3DXVec3TransformCoord(&ver[0], &ver[0], &TestWorldMatrix);
			D3DXVec3TransformCoord(&ver[1], &ver[1], &TestWorldMatrix);
			D3DXVec3TransformCoord(&ver[2], &ver[2], &TestWorldMatrix);

			//ぶつかってるかチェック
			float dist, u, v;
			BOOL hit = D3DXIntersectTri(&ver[0], &ver[1], &ver[2], &data->start, &data->dir, &u, &v, &dist);

			//今まで一番近い？
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

		//インデックスバッファ使用終了
		pIndexBuffer[i]->Unlock();
	}

	//頂点バッファ使用終了
	pVertexBuffer->Unlock();

	return data->hit;
}