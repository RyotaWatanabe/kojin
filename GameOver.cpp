/*===========================================================================================
概　略：ゲームオーバー画面を扱う処理
作成日：2016/1/13
更新日：2016/1/21
制作者：渡邉諒太
=============================================================================================*/


#include "GameOver.h"

//コンストラクタ
GameOver::GameOver()
{
	gameover = NULL;
}


//デストラクタ
GameOver::~GameOver()
{
	SAFE_DELETE(gameover);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT GameOver::Load()
{
	gameover = new Sprite;
	//ゲームオーバー画面の読み込み
	if (FAILED(gameover->Load("assets\\pict\\gameover.png")))
	{
		return E_FAIL;
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：更新処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT GameOver::Update()
{
	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT GameOver::Render()
{
	SpriteData gameoverData;
	gameover->Draw(&gameoverData);
	return S_OK;
}
