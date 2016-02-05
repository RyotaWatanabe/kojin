/*===========================================================================================
概　略：FBXファイルを描画
作成日：9/10
更新日：9/16
制作者：渡邉諒太
=============================================================================================*/


#pragma once
#include "Global.h"
#include <fbxsdk.h>
#pragma comment(lib,"libfbxsdk-mt.lib")


//レイキャスト用構造体
struct RayCastData
{
	D3DXVECTOR3 start;	//レイ発射位置
	D3DXVECTOR3 dir;	//レイの向きベクトル
	float		dist;	//衝突点までの距離
	D3DXVECTOR3 normal;	//衝突点の法線
	D3DXVECTOR3 pos;	//衝突位置
	BOOL		hit;	//レイが当たったか
};

class Fbx
{
	FbxManager*		manager;	//FBX機能を管理
	FbxImporter*	importer;	//ファイルを開く
	FbxScene*		scene;		//開いたファイルを管理

	//頂点の数
	int vertexCount;
	//ポリゴン数を入れる
	int polygonCount;
	//インデックス数を入れる
	int indexCount;
	//マテリアルを入れる
	int materialCount;
	//マテリアルごとのポリゴン数を入れる
	int* polygonCountOfMaterial;


	//作った頂点バッファを入れる
	IDirect3DVertexBuffer9 *pVertexBuffer;
	//作ったインデックスバッファを入れる
	IDirect3DIndexBuffer9 **pIndexBuffer;
	//マテリアルの配列を作るためのポインタ
	D3DMATERIAL9          *pMaterial;
	//テクスチャオブジェクト
	LPDIRECT3DTEXTURE9 *pTexture;

	//ノードの内容を調べる
	HRESULT CheckNode(FbxNode* pNode);
	//頂点情報
	HRESULT CheckMesh(FbxMesh* pMesh);

	//1つの頂点に必要なデータ
	struct Vertex
	{
		D3DXVECTOR3 pos;	//位置
		D3DXVECTOR3 normal;	//法線情報
		D3DXVECTOR2 uv;		//UV情報
	};

	//
	D3DXMATRIX TestWorldMatrix;

public:
	//コンストラクタ
	Fbx();
	//デストラクタ
	~Fbx();
	//読み込み処理
	HRESULT Load(char* fileName);
	//描画処理
	HRESULT Draw(D3DXMATRIX* matWorld);

	BOOL RayCast(RayCastData *data);

	
};

