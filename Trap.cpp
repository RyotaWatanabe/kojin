/*=======================================================================================================
概　略：トラップ
作成日：1/21
更新日：1/22
制作者：渡邉　諒太
=======================================================================================================*/

#include <stdlib.h>
#include "Trap.h"
#include "Player.h"


Trap::Trap()
{
	position = D3DXVECTOR3(rand() % 2000, 0, 0);
	move = D3DXVECTOR3(0, 0, 0);
	//初期スクロール位置
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);
	trap = NULL;
}


Trap::~Trap()
{
	//解放
	SAFE_DELETE(trap);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Trap::Load()
{
	trap = new Sprite;
	//クリア画面の読み込み
	if (FAILED(trap->Load("assets\\pict\\iwa.png")))
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
HRESULT Trap::Update()
{
	return S_OK;
}


//――――――――――――――――――――――
// 機能：衝突判定処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Trap::Hit(UnitBase* pTarget)
{
	//ターゲットがプレイヤーだったら
	if (typeid(*pTarget) == typeid(Player))
	{
		//現在の位置
		Player* player = (Player*)pTarget;
		D3DXVECTOR3 playerPos = player->GetPos();

		//プレイヤーからトラップまでの距離の2乗を求める
		int distance = (position.x - playerPos.x)*(position.x - playerPos.x) +
					   (position.y - playerPos.y)*(position.y - playerPos.y);

		//2乗以内だったら
		if (distance >= ACTOR_SIZE*ACTOR_SIZE)
		{
			
		}
	}
	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Trap::Render()
{
	SpriteData trapData;
	trapData.pos = D3DXVECTOR3(position.x + g_stageScrollPos.x, position.y + g_stageScrollPos.y, 0);
	trapData.scale = D3DXVECTOR2(0.3f, 0.3f);
	trap->Draw(&trapData);
	return S_OK;
}