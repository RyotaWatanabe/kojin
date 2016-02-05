/*===========================================================================================
概　略：ステージの描画
作成日：10/21
更新日：11/11
制作者：渡邉諒太
=============================================================================================*/


#include "Stage.h"
#include "Camera.h"

//コンストラクタ
Stage::Stage()
{
	//初期スクロール位置
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);

	//初期化
	stage = NULL;
}


//デストラクタ
Stage::~Stage()
{
	//解放
	SAFE_DELETE(stage);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Stage::Load()
{
	//ステージ(背景読み込み)
	stage = new Sprite;
	if (FAILED(stage->Load("Assets\\Pict\\stage2.jpg")))
	{
		MessageBox(0, "ステージを読み込めませんでした。", "読み込みエラー", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Stage::Render()
{
	//ステージ（背景）の描画
	SpriteData stageData;
	stageData.pos = D3DXVECTOR3(g_stageScrollPos.x, g_stageScrollPos.y*WINDOW_HEIGHT, 0);
	stage->Draw(&stageData);

	return S_OK;
}