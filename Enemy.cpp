/*=======================================================================================================
概　略：敵ユニット
作成日：10/28
更新日：12/7
制作者：渡邉　諒太
=======================================================================================================*/


#include "Enemy.h"
#include "Player.h"


//コンストラクタ
Enemy::Enemy()
{
	//敵の初期位置
	position.x = 300;
	position.y = WINDOW_HEIGHT - 140;
	//敵の移動量
	move.x = 0.7;
	move.y = 0;
	//初期スクロール位置
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);
	//初期化
	enemy = NULL;
	enemy2 = NULL;
	//敵が生きている時TRUE（フラグ）
	enemyLive = TRUE;
}


//デストラクタ
Enemy::~Enemy()
{
	//解放
	SAFE_DELETE(enemy);
	SAFE_DELETE(enemy2);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Enemy::Load()
{
	enemy = new Sprite;
	enemy2 = new Sprite;

	//敵の読み込み
	if (FAILED(enemy->Load("Assets\\Pict\\enemy1.png")))
	{
		MessageBox(0, "敵を読み込めませんでした。", "読み込みエラー", MB_OK);
		return E_FAIL;
	}
	if (FAILED(enemy2->Load("Assets\\Pict\\enemy1_1.png")))
	{
		MessageBox(0, "敵を読み込めませんでした。", "読み込みエラー", MB_OK);
		return E_FAIL;
	}
	
	return S_OK;
}


//――――――――――――――――――――――
// 機能：更新処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Enemy::Update()
{
	//生きていれば
	if (enemyLive)
	{
		//簡単な移動
		position.x += move.x;
	
		//画面左端
		if (position.x < 300)
			move.x *= -1;		//跳ね返る

		//画面右端
		if (position.x > 400)
			move.x *= -1;		//跳ね返る
	}
	
	return S_OK;
}


//――――――――――――――――――――――
// 機能：更新処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Enemy::Hit(UnitBase* pTarget)
{
	
	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Enemy::Render()
{
	//敵を描画するためのスプライトデータ型変数を作成
	SpriteData enemyData;
	//敵の位置
	enemyData.pos = D3DXVECTOR3(position.x + g_stageScrollPos.x, position.y + g_stageScrollPos.y, 0);

	//生きていれば表示する
	if (enemyLive)
	{
		//描画
		enemy->Draw(&enemyData);
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：敵を倒したときの処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Enemy::Kill()
{
	//フラグを戻す
	enemyLive = FALSE;

	//ぶつからないよう適当な位置へ
	position.y = -999;

	return S_OK;
}