/*===========================================================================================
概　略：画像を表示するための処理
作成日：12/14
更新日：12/14
制作者：渡邉諒太
=============================================================================================*/


#include "Picture.h"


Picture::~Picture()
{
	//メモリデバイスコンテキストハンドル解放
	DeleteDC(hdc_mem);	
}


//――――――――――――――――――――――
// 機能：読み込み処理
// 引数：hWnd		ウィンドウハンドル
// 引数：fileName	ファイル名
//――――――――――――――――――――――
HRESULT Picture::Load(HWND hWnd, char* fileName)
{
	HDC		hdc;			//デバイスコンテキストハンドル
	HBITMAP	hBitmap;		//ビットマップハンドル

	//ウィンドウのデバイスコンテキストハンドルを取得
	hdc = GetDC(hWnd);

	//メモリデバイスコンテキスト（見えない画用紙）を作成
	hdc_mem = CreateCompatibleDC(hdc);

	//ウィンドウのデバイスコンテキストハンドルはもう使わない
	ReleaseDC(hWnd, hdc);

	//画像ファイルを開く
	hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//開いた画像をメモリデバイスコンテキストへ
	SelectObject(hdc_mem, hBitmap);

	//画像サイズを取得
	BITMAP bmp;				//色々な情報が入る変数
	GetObject(hBitmap, sizeof(BITMAP), &bmp);	//情報を取得
	bmpW = bmp.bmWidth;		//幅
	bmpH = bmp.bmHeight;	//高さ

	//画像を解放
	DeleteObject(hBitmap);

	return S_OK;
}


//――――――――――――――――――――――
// 機能：描画処理
// 引数：hdc			ウィンドウのデバイスコンテキストハンドル
// 引数：posX,posY		描画位置
// 引数：sizeX,sizeY	描画サイズ
// 引数：cutX,cutY		切抜き位置
//――――――――――――――――――――――
HRESULT Picture::Draw(HDC hdc, int posX, int posY, int sizeX, int sizeY, int cutX, int cutY)
{
	//画像を描画
	BitBlt(hdc, posX, posY, sizeX, sizeY, hdc_mem, cutX, cutY, SRCCOPY);

	return S_OK;
}

//――――――――――――――――――――――
// 機能：描画処理（指定位置に画像全体を描画）
// 引数：hdc			ウィンドウのデバイスコンテキストハンドル
// 引数：posX,posY		描画位置
// 戻値：なし
//――――――――――――――――――――――
//描画（指定位置に画像全体を描画）
HRESULT Picture::Draw(HDC hdc, int posX, int posY)
{
	Draw(hdc, posX, posY, bmpW, bmpH, 0, 0);

	return S_OK;
}