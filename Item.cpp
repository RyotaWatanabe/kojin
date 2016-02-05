/*=======================================================================================================
概　略：アイテム
作成日：12/7
更新日：1/22
制作者：渡邉　諒太
=======================================================================================================*/


#include "Item.h"
#include "Player.h"



//コンストラクタ
Item::Item()
{
	//初期スクロール位置
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);

	//初期位置
	position = D3DXVECTOR3(500, WINDOW_HEIGHT-CHIP_SIZE*3, 0);

	item = NULL;
}


//デストラクタ
Item::~Item()
{
	SAFE_DELETE(item);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Item::Load()
{
	item = new Sprite;

	//プレイヤーの読み込み
	if (FAILED(item->Load("Assets\\Pict\\item.png")))
	{
		MessageBox(0, "アイテムを読み込めませんでした。", "読み込みエラー", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：更新処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Item::Update()
{
	return S_OK;
}


//――――――――――――――――――――――
// 機能：衝突判定処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Item::Hit(UnitBase* pTarget)
{
	//ターゲットがアイテムだったら
	if (typeid(*pTarget) == typeid(Player))
	{
		//現在の位置
		Player* player = (Player*)pTarget;
		D3DXVECTOR3 playerPos = player->GetPos();

		//アイテムからプレイヤーまでの距離の2乗を求める
		int distance = (position.x - playerPos.x)*(position.x - playerPos.x) +
					   (position.y - playerPos.y)*(position.y - playerPos.y);

		//2乗以内だったら
		if (distance <= ACTOR_SIZE*ACTOR_SIZE)
		{
			position.y = 999;
		}
	}
	return S_OK;
}

//――――――――――――――――――――――
// 機能：描画処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Item::Render()
{
	SpriteData itemData;
	itemData.pos = D3DXVECTOR3(position.x + g_stageScrollPos.x, position.y + g_stageScrollPos.y, 0);
	item->Draw(&itemData);
	return S_OK;
}