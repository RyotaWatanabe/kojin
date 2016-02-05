/*===========================================================================================
概　略：ゲームオーバー画面を扱う処理
作成日：2016/1/13
更新日：2016/1/13
制作者：渡邉諒太
=============================================================================================*/


#pragma once
#include "UnitBase.h"
#include "Sprite.h"

class GameOver : public UnitBase
{
	Sprite* gameover;
public:
	GameOver();
	~GameOver();

	//読み込み処理
	HRESULT Load();
	//更新処理
	HRESULT Update();
	//描画処理
	//引数：hdc	デバイスコンテキストハンドル
	HRESULT Render();
};

