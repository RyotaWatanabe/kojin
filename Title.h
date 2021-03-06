/*===========================================================================================
概　略：タイトル画面を扱う処理
作成日：4/20
更新日：9/14
制作者：渡邉諒太
=============================================================================================*/
#pragma once

//---------------インクルード-----------------------
#include "UnitBase.h"
#include "Sprite.h"
#include "Audio.h"

//―――――――――――――――――――――
//	タイトルクラス
//―――――――――――――――――――――
class Title:public UnitBase
{
	//スプライト型の変数
	Sprite	sprite;

public:
	//コンストラクタ
	Title();
	//デストラクタ
	~Title();

	//読み込み処理
	HRESULT Load();
	//更新処理
	HRESULT Update();
	//描画処理
	//引数：hdc	デバイスコンテキストハンドル
	HRESULT Render();
};

