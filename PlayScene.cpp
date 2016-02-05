/*===========================================================================================
概　略：プレイシーン
作成日：
更新日：12/7
制作者：渡邉諒太
=============================================================================================*/


//---------------インクルード-----------------------
#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "Block.h"
#include "Item.h"
#include "Trap.h"

//現在のスクロール位置
D3DXVECTOR3	g_stageScrollPos;

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
PlayScene::PlayScene()
{
	//ユニットを追加
	unit.push_back(new Stage);
	unit.push_back(new Block);
	unit.push_back(new Item);
	unit.push_back(new Enemy);
	unit.push_back(new Player);
	unit.push_back(new Trap);

	
}