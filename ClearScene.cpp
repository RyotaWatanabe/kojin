/*===========================================================================================
概　略：クリアシーン
作成日：
更新日：
制作者：渡邉諒太
=============================================================================================*/


//---------------インクルード-----------------------
#include "ClearScene.h"
#include "Clear.h"

//――――――――――――――――――――――
//	コンストラクタ
//――――――――――――――――――――――
ClearScene::ClearScene()
{
	//ユニットを追加
	unit.push_back(new Clear);	//クリア画面
}

