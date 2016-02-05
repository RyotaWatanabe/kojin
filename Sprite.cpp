/*===========================================================================================
概　略：2D画像を表示するための処理
作成日：
更新日：
制作者：渡邉諒太
=============================================================================================*/


#include "Sprite.h"


//コンストラクタ
Sprite::Sprite()
{
}


//デストラクタ
Sprite::~Sprite()
{
	//解放
	SAFE_RELEASE(pTexture);
	SAFE_RELEASE(pSprite);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：fileName　ファイル名
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Sprite::Load(char* fileName)
{
	// 「スプライトオブジェクト」の作成
	if (FAILED(D3DXCreateSprite(g_pDevice, &pSprite)))
	{
		MessageBox(0, "スプライトの作成に失敗しました", "エラー", MB_OK);
		return E_FAIL;
	}
	//「テクスチャオブジェクト」の作成
	if (FAILED(D3DXCreateTextureFromFileEx(g_pDevice, fileName, 0, 0, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xff000000, NULL, NULL, &pTexture)))
	{
		MessageBox(0, "テクスチャの作成に失敗しました", fileName, MB_OK);
		return E_FAIL;
	}

	//テクスチャのサイズを取得
	D3DSURFACE_DESC  d3dds;
	pTexture->GetLevelDesc(0, &d3dds);
	texSize.x = d3dds.Width;
	texSize.y = d3dds.Height;

	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：data
// 戻値：成功/失敗
//――――――――――――――――――――――
void Sprite::Draw(SpriteData* data)
{
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	//サイズを省略した場合は画像サイズを使う
	if (data->size.x == -999) data->size.x = texSize.x;
	if (data->size.y == -999) data->size.y = texSize.y;

	//描画位置
	D3DXVECTOR3 position = data->pos;
	//切り抜き範囲
	RECT cut = { data->cut.x, data->cut.y, data->cut.x + data->size.x, data->cut.y + data->size.y };
	//基準点
	D3DXVECTOR3 center = data->center;
	center.z = NULL;
	if (center.x == -999 && center.y == -999)      //未設定の場合は画像の中心
	{
		center.x = data->size.x / 2;
		center.y = data->size.y / 2;
	}

	//拡大行列
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, data->scale.x, data->scale.y, 1);

	//回転行列
	D3DXMATRIX matRotate;
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(data->angle));

	//移動行列
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, data->pos.x + center.x*data->scale.x, data->pos.y + center.y*data->scale.y, 0);

	//合成行列
	D3DXMATRIX matWorld = matScale * matRotate*matTrans;

	//スプライトに行列を適用
	pSprite->SetTransform(&matWorld);

	//基準値をさらに移動
	center.x += data->pos.x;
	center.y += data->pos.y;

	//描画
	pSprite->Draw(pTexture, &cut, &center, &position, D3DCOLOR_ARGB(data->color.a, data->color.r, data->color.g, data->color.b));

	pSprite->End();
}