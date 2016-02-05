/*===========================================================================================
概　略：各ゲームユニットの親クラス
作成日：
更新日：10/29
制作者：渡邉諒太
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "Global.h"
#include <typeinfo.h>


//―――――――――――――――――――――
//	各ゲームユニットの親クラス
//―――――――――――――――――――――
class UnitBase
{
protected:
	//ユニットの位置
	D3DXVECTOR3	position;
	//ユニットの移動量
	D3DXVECTOR3 move;

public:
	virtual ~UnitBase(){}

	//読み込み処理
	virtual HRESULT Load();

	//更新処理
	virtual HRESULT Update();

	//衝突判定処理
	//引数：pTarget	判定する相手ユニット
	virtual HRESULT Hit(UnitBase* pTarget);

	//描画処理
	//引数：hdc	デバイスコンテキストハンドル
	virtual HRESULT Render();

	//現在の位置を取得
	//戻値：現在の位置
	D3DXVECTOR3 GetPos()	{ return position; }

	D3DXVECTOR3 GetMove()	{ return move; }
};

