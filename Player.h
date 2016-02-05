/*===========================================================================================
概　略：プレイヤーを扱う処理
作成日：10/15
更新日：12/9
制作者：渡邉諒太
=============================================================================================*/


#pragma once
#include "Global.h"
#include "UnitBase.h"
#include "Sprite.h"
#include "Fbx.h"
#include "windef.h"


//現在のスクロール位置（PlayScene.cppで宣言）
extern D3DXVECTOR3 g_stageScrollPos;

class Player :public UnitBase
{
	typedef struct RECT 
	{
		int x;
		int y;	
		int w;
		int h;
	};
	RECT playerRect;

	//プレイヤーの状態
	enum
	{
		STATUS_NORMAL,	//通常
		STATUS_DEAD,	//死んだとき（敵の攻撃に当たったり、トラップに引っかかったり、落下死したりしたとき）
		DOWN_SCROLL,	//下へスクロール
		UP_SCROLL		//上へスクロール
	}status;

	//プレイヤーを描画するためのスプライト型変数
	Sprite* player;	

	int deadCount;	//被弾してからのフレーム数

	int dir;	//プレイヤーの向き
	int anim;	//プレイヤーの足踏み

	BOOL JumpFlag;		//ジャンプフラグ

	void Move();		//プレイヤーの移動処理
	//void Attack();	//プレイヤーの攻撃
	void Dead();		//プレイヤーが死んだときの処理

public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//読み込み処理
	HRESULT Load();
	//更新処理
	HRESULT Update();
	//衝突判定処理
	//引数：pTarget	判定する相手ユニット
	HRESULT Hit(UnitBase* pTarget);
	//描画処理
	//引数：hdc	デバイスコンテキストハンドル
	HRESULT Render();
};