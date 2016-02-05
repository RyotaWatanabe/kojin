/*=======================================================================================================
概　略：アイテム
作成日：12/7
更新日：12/7
制作者：渡邉　諒太
=======================================================================================================*/

#pragma once
#include "UnitBase.h"
#include "Sprite.h"
#include "Global.h"

//現在のスクロール位置（PlayScene.cppで宣言）
extern D3DXVECTOR3 g_stageScrollPos;

class Item : public UnitBase
{
	//アイテムオブジェクト
	Sprite* item;

public:
	Item();
	~Item();

	//読み込み処理
	HRESULT Load();
	//更新処理
	HRESULT Update();
	//衝突判定処理
	HRESULT Hit(UnitBase* pTarget);
	//描画処理
	HRESULT Render();
};

