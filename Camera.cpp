/*=======================================================================================================
概　略：カメラの設定
作成日：8/27
更新日：9/15
制作者：渡邉諒太
=======================================================================================================*/


#include "Camera.h"


//コンストラクタ
Camera::Camera()
{
	pos = D3DXVECTOR3(0, 10, -30);	//カメラの位置
	target = D3DXVECTOR3(0, 0, 0);	//カメラの焦点位置
	upVec = D3DXVECTOR3(0, 1, 0);	//上方向

	//画角
	angle = 60;
	//アスペクト比
	aspect = (float)WINDOW_WIDTH / WINDOW_HEIGHT;
	//近クリッピング
	nearClip = 0.1f;
	//遠クリッピング
	farClip = 1000.0f;
}


//デストラクタ
Camera::~Camera()
{

}


//――――――――――――――――――――――
// 機能：カメラの位置や向きを設定（ビュー行列）
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Camera::SetView()
{
	//ビュー行列を作成
	D3DXMatrixLookAtLH(&view, &pos, &target, &upVec);

	//行列の種類を指定（ビュー行列）
	if (FAILED(g_pDevice->SetTransform(D3DTS_VIEW, &view)))
	{
		//失敗した場合メッセージを表示
		MessageBox(0, "ビュー行列の設定に失敗しました", "Camera", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：画角やアスペクト比を設定（射影行列）
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Camera::SetProjection()
{
	//射影行列を作成
	D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(angle), aspect, nearClip, farClip);

	//行列の種類を指定（射影行列）
	if (FAILED(g_pDevice->SetTransform(D3DTS_PROJECTION, &proj)))
	{
		//失敗した場合メッセージを表示
		MessageBox(0, "射影行列の設定に失敗しました", "Camera", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：更新処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Camera::Update()
{
	//Camera::SetView関数を呼ぶ
	if (FAILED(SetView()))
	{
		return E_FAIL;
	}

	//Camera::SetProjection関数を呼ぶ
	if (FAILED(SetProjection()))
	{
		return E_FAIL;
	}

	return S_OK;
}

