/*=======================================================================================================
概　略：カメラの設定
作成日：8/27(木)
更新日：8/27(木)
制作者：渡邉諒太
=======================================================================================================*/


#pragma once
#include "Global.h"


class Camera
{
	D3DXVECTOR3 pos;    //カメラの位置
	D3DXVECTOR3 target; //焦点位置
	D3DXVECTOR3 upVec;  //上方向

	float angle;        //画角
	float aspect;		//アスペクト比
	float nearClip;		//近クリッピング
	float farClip;		//遠クリッピング

	D3DXMATRIX  view;   //ビュー行列
	D3DXMATRIX  proj;	//射影行列

	HRESULT SetView();			//ビュー行列を作る関数
	HRESULT SetProjection();	//射影行列を作る関数

public:
	Camera();
	~Camera();

	HRESULT Update();	//更新処理

	//アクセス関数
	void SetPos(D3DXVECTOR3 v){ pos = v; }
	void SetTarget(D3DXVECTOR3 v){ target = v; }
	void SetUp(D3DXVECTOR3 v){ upVec = v; }

	void SetAngle(float f){ angle = f; }
	void SetAspect(float f){ aspect = f; }
	void SetNearClip(float f){ nearClip = f; }
	void SetFarClip(float f){ farClip = f; }

};

