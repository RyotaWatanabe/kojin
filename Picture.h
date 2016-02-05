/*===========================================================================================
概　略：画像を表示するための処理
作成日：12/14
更新日：12/14
制作者：渡邉諒太
=============================================================================================*/


#pragma once
#include <Windows.h>

class Picture
{
	HDC hdc_mem;		//メモリデバイスコンテキストハンドル
	int bmpW, bmpH;		//画像のサイズ

public:
	//デストラクタ
	~Picture();

	//読み込み
	HRESULT Load(HWND hWnd, char* fileName);
	//描画
	HRESULT Draw(HDC hdc, int posX, int posY, int sizeX, int sizeY, int cutX, int cutY);
	//描画（指定位置に画像全体を描画）
	HRESULT Draw(HDC hdc, int posX, int posY);

	//アクセス関数
	int GetWidth(){ return bmpW; }
	int GetHeight(){ return bmpH; }
};

