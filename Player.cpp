/*=======================================================================================================
概　略：プレイヤーユニット
作成日：10/15
更新日：2/5
制作者：渡邉　諒太
=======================================================================================================*/


#include "Player.h"
#include "Camera.h"
#include "Enemy.h"
#include "Block.h"
#include "Item.h"


//-----------------定数宣言--------------------
#define MOVE_SPEED	2		//プレイヤーの移動速度
#define DASH_SPEED	0.3f	//プレイヤーのダッシュ速度
#define JUMP_POWER	9.0f	//ジャンプ力
#define DAMAGE_TIME	25		//いわゆる無敵時間


Player::Player()
{
	//プレイヤーの初期位置
	position = D3DXVECTOR3(0, WINDOW_HEIGHT - 96, 0);
	//移動量
	move = D3DXVECTOR3(0, 0, 0);
	//初期スクロール位置
	g_stageScrollPos = D3DXVECTOR3(0, 0, 0);
	//初期状態
	status = STATUS_NORMAL;
	//初期化
	player = NULL;

	playerRect.x = 0;
	playerRect.y = 0;
	playerRect.w = 32;
	playerRect.h = 32;
}


Player::~Player()
{
	//解放
	SAFE_DELETE(player);
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Player::Load()
{
	player = new Sprite;
	//プレイヤーの読み込み
	if (FAILED(player->Load("Assets\\Pict\\Actor.png")))
	{
		MessageBox(0, "プレイヤーを読み込めませんでした。", "読み込みエラー", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：更新処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Player::Update()
{
	//状態ごとに処理を分ける
	switch (status)
	{
		//通常状態
	case STATUS_NORMAL:
		Move();		//プレイヤーの移動
		//Attack();	//攻撃
		break;

		//下へスクロール中
	case DOWN_SCROLL:
		g_stageScrollPos.y -= 20;	//画面をスクロール
		position.y += 3;			//プレイヤーも移動
		//キリの良いところまでいったら通常状態に戻す
		if ((int)g_stageScrollPos.y % WINDOW_HEIGHT == 0)
		{
			status = STATUS_NORMAL;
		}
		break;

		//上へスクロール中
	case UP_SCROLL:
		g_stageScrollPos.y += 20;
		position.y -= 3;
		if ((int)g_stageScrollPos.y % WINDOW_HEIGHT == 0)
		{
			status = STATUS_NORMAL;
		}
		break;

		//死んだ状態
	case STATUS_DEAD:
		Dead();		//一定時間経ったら通常状態に戻す
		break;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：衝突判定処理
// 引数：なし
// 戻値：成功/失敗
//――――――――――――――――――――――
HRESULT Player::Hit(UnitBase* pTarget)
{
	//ターゲットが敵だったら
	if (typeid(*pTarget) == typeid(Enemy))
	{
		//敵の現在の位置
		Enemy* enemy = (Enemy*)pTarget;
		D3DXVECTOR2 enemyPos = enemy->GetPos();

		//プレイヤーから敵までの距離の2乗を求める
		int distance = (position.x - enemyPos.x) * (position.x - enemyPos.x) +
					   (position.y - enemyPos.y) * (position.y - enemyPos.y);

		//キャラサイズの2乗以内だったら
		if (distance <= (ACTOR_SIZE * ACTOR_SIZE))
		{
			//プレイヤー死ぬ
			status = STATUS_DEAD;
		}
	}

	//ターゲットがブロックだったら
	if (typeid(*pTarget) == typeid(Block))
	{
		//現在の位置
		Block* block = (Block*)pTarget;

		int x = position.x;
		int y = position.y;

		if (block->GetMap(y , x) == 1 )
		{
			
			move.y = 0;
		}
		
	}

	//ターゲットがアイテムだったら
	if (typeid(*pTarget) == typeid(Item))
	{
		//現在の位置
		Item* item = (Item*)pTarget;
		D3DXVECTOR3 itemPos = item->GetPos();

		//プレイヤーからブロックまでの距離の2乗を求める
		int distance = (position.x - itemPos.x)*(position.x - itemPos.x) +
			(position.y - itemPos.y)*(position.y - itemPos.y);

		//2乗以内だったら
		if (distance <= ACTOR_SIZE*ACTOR_SIZE)
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
HRESULT Player::Render()
{
	//プレイヤー画像のサイズ調整
	SpriteData playerData;
	playerData.pos = position + g_stageScrollPos;	//表示位置はスクロールした分ずらす
	playerData.size = D3DXVECTOR2(32,32);			//サイズ
	playerData.cut.y = dir * 32;					//切抜き位置
	playerData.cut.x = ((anim / 9) % 4) * 32;
	
	switch (status)
	{
		//通常状態のとき
	case STATUS_NORMAL:
		//プレイヤーの描画
		player->Draw(&playerData);
		break;

		//死んだとき
	case STATUS_DEAD:
		Dead();
		break;
	}

	return S_OK;
}


//――――――――――――――――――――――
// 機能：移動処理
// 引数：なし
// 戻値：なし
//――――――――――――――――――――――
void Player::Move()
{
	//「A」を押した場合
	if (g_pInput->IsKeyPush(DIK_A))
	{
		//左方向へ進む
		position.x -= MOVE_SPEED;
		dir = 1;	//左を向く
		anim++;		//足踏み
	}

	//「A」と「左Shift」を押している場合
	if (g_pInput->IsKeyPush(DIK_A) && g_pInput->IsKeyPush(DIK_LSHIFT))
	{
		//左方向へダッシュ
		position.x -= MOVE_SPEED + DASH_SPEED;
		dir = 1;	//左を向く
		anim++;		//足踏み
	}

	//「D」を押している場合
	if (g_pInput->IsKeyPush(DIK_D))
	{
		//右方向へ進む
		position.x += MOVE_SPEED;
		dir = 2;	//右を向く
		anim++;		//足踏み
	}

	//「D」と「左Shift」を押している場合
	if (g_pInput->IsKeyPush(DIK_D) && g_pInput->IsKeyPush(DIK_LSHIFT))
	{
		//右方向へダッシュ
		position.x += MOVE_SPEED +DASH_SPEED;
		dir = 2;	//右を向く
		anim++;		//足踏み
	}

	//画面左端に着いたら
	if (position.x <= 0)
	{
		//左端にぶつかる
		position.x = 0;		
	}

	//ジャンプフラグが立ってなければ（地面にいる時）
	if (!JumpFlag)
	{
		//スペースキーを押すとジャンプする
		if (g_pInput->IsKeyTap(DIK_SPACE))
		{
			move.y -= JUMP_POWER;
			JumpFlag = TRUE;
		}
	}
	
	//プレイヤーに重力を加える
	position.y += move.y;
	move.y += GRAVITY;

	//地面に降りる際に地面に着地するようにする
	if (position.y >= WINDOW_HEIGHT - 96)
	{
		move.y = 0;
		JumpFlag = FALSE;
	}

	//プレイヤーが真ん中に来るよう、横スクロール位置を算出
	g_stageScrollPos.x = -position.x + (WINDOW_WIDTH / 2 - 32);

	//横スクロールしすぎの場合の処理
	if (g_stageScrollPos.x > 0)
		g_stageScrollPos.x = 0;

	if (g_stageScrollPos.x < -(2000 - WINDOW_WIDTH))
		g_stageScrollPos.x = -(2000 - WINDOW_WIDTH);

	////画面下端まで行ったとき
	//if (position.y + g_stageScrollPos.y > WINDOW_HEIGHT - 64)
	//{
	//	//下へスクロールする
	//	status = DOWN_SCROLL;
	//}

	//画面上端まで行ったとき
	if (position.y + g_stageScrollPos.y < 0)
	{
		//上へスクロールする
		status = UP_SCROLL;
	}
}


//――――――――――――――――――――――
// 機能：「＊」状態の時の処理
// 引数：なし
// 戻値：なし
//――――――――――――――――――――――
void Player::Dead()
{
	//カウントアップ
	deadCount++;

	//一定時間経ったら通常状態に戻す
	if (deadCount >= DAMAGE_TIME)
	{
		status = STATUS_NORMAL;
	}
}