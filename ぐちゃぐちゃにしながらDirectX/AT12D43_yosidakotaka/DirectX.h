#ifndef _DIRECT_H_
#define _DIRECT_H_

#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

//DirectXの初期化
//width 画面の横幅
//height 画面の縦幅
//hWnd 画面の更新を行うウィンドウ
//fullScreen 全画面
//戻り値　初期化に成功したか
//
HRESULT InitDirectX(UINT width, UINT height, HWND hWnd, bool fullScreen);
//終了処理
void UninitDirectX(void);

//DirectXの描画処理
void BeginDrawDirectX(void);
void EndDrawDirectX(void);

//DirectXの情報を渡す関数
ID3D11Device* GetDevice(void);

ID3D11DeviceContext* GetContext(void);

#endif//_DIRECT_H_
