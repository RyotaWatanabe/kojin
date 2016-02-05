/*=======================================================================================================
概　略：トラップ
作成日：1/21
更新日：1/21
制作者：渡邉　諒太
=======================================================================================================*/


#pragma once
#include "UnitBase.h"
#include "Global.h"
#include "Sprite.h"

//現在のスクロール位置（PlayScene.cppで宣言）
extern D3DXVECTOR3 g_stageScrollPos;

class Trap : public UnitBase
{
	Sprite* trap;

	int dis;

public:
	Trap();
	~Trap();

	//読み込み処理
	HRESULT Load();
	//更新処理
	HRESULT Update();
	//描画処理
	//衝突判定処理
	HRESULT Hit(UnitBase* pTarget);
	//引数：hdc	デバイスコンテキストハンドル
	HRESULT Render();
};

