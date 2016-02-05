/*===========================================================================================
概　略：ステージの描画
作成日：10/21
更新日：11/2
制作者：渡邉諒太
=============================================================================================*/


#pragma once
#include "Global.h"
#include "UnitBase.h"
#include "Sprite.h"


//現在のスクロール位置（PlayScene.cppで宣言）
extern D3DXVECTOR3 g_stageScrollPos;

class Stage : public UnitBase
{
	//ステージ（地面）を描画するために必要な変数
	Sprite* stage;

public:
	Stage();
	~Stage();

	//読み込み処理
	HRESULT Load();
	//描画処理
	HRESULT Render();
	//ステージ情報を取得するアクセス関数
	Sprite* GetStage(){ return stage; }
};

