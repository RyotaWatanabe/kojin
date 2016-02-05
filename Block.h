/*===========================================================================================
概　略：ブロック（壁や地面、障害）を配置
作成日：11/2
更新日：1/22
制作者：渡邉諒太
=============================================================================================*/


#pragma once
#include "UnitBase.h"
#include "Global.h"
#include "Sprite.h"

//現在のスクロールの位置(PlayScene.cppで宣言済み)
extern D3DXVECTOR3 g_stageScrollPos;
extern int mapTable[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

class Block : public UnitBase
{
	typedef struct RECT
	{
		int left;	//左上x座標
		int top;		//左上y座標
		int right;	//右下x座標
		int bottom;	//右下y座標
	}RECT;

	//ブロックを配置するためのスプライト型変数
	Sprite* block;
	

public:
	Block();
	~Block();

	//読み込み処理
	HRESULT Load();
	//更新処理
	HRESULT Update();
	//衝突判定処理
	HRESULT Hit(UnitBase* pTarget);
	//描画処理
	HRESULT Render();

	int GetMap(int y, int x){ return mapTable[y][x]; }
};