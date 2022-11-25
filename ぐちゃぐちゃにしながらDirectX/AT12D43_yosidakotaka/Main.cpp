#include <Windows.h>　// Windowsの機能を利用 
#include <stdio.h> // sprintfを使用
#include "DirectX.h"
#include "Game.h"
#include "FPS.h"
#include "Keyboard.h"
#include"Sound.h"

// プロトタイプ宣言
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message,
	WPARAM wPatram, LPARAM IParam);

// ウィンドウを表示するためのプログラム

 int WINAPI WinMain(
	// 起動しているプログラムを
	// OSが判別するために振られる数字
	HINSTANCE hInstance,
	// 昔の名残で残ってるだけのデータ
	HINSTANCE hPrevInstance,
	// コマンドライン引数
	// ※プログラムを実行する時に渡す引数
	LPSTR lpCmdLine,
	// 最初の表示状態
	int nCmdShow)
{

	// ウィンドウクラス情報の設定
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	// 紐づけ対象
	wcex. hInstance = hInstance;
	// クラス情報を識別する名称
	wcex. lpszClassName = "Class Name";
	
	wcex. lpfnWndProc = WndProc;
	wcex. style = CS_CLASSDC;

	// 構造体のサイズ指定
	wcex. cbSize = sizeof(WNDCLASSEX);
	// タスクバーに表示されるアイコンの設定
	wcex. hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex. hIconSm = wcex. hIcon;
	// マウスカーソルの見た目の設定
	wcex. hCursor = LoadCursor(NULL, IDC_ARROW);
	// ウィンドウの背景の色
	wcex. hbrBackground =
		(HBRUSH)GetStockObject(WHITE_BRUSH);
	// ウィンドウクラス情報の登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"ウィンドウ情報の登録に失敗",
			"ERROR！", MB_OK | MB_ICONERROR);
		return 0;
	}

	// ウィンドウの作成
	HWND hWnd;
	hWnd = CreateWindowEx(
		// ウィンドウの外観を決定（拡張版）
		// ※デフォルトはこれ↓
		WS_EX_OVERLAPPEDWINDOW,
		// 作成元のウィンドウクラス情報
		wcex.lpszClassName,
		// タイトルバーの設定
		"ゲーム",
		// ウィンドウの外観を決定
		WS_CAPTION | WS_SYSMENU,
		// ウィンドウを表示する座標
		// CW_USEDEFAULTでお任せ位置に表示
		CW_USEDEFAULT, CW_USEDEFAULT,
		// ウィンドウのサイズ
		960, 540,
		// ウィンドウの親子関係、一つのアプリで
		// 複数のウィンドウが表示できる
		HWND_DESKTOP,
		NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL,
			"ウィンドウの作成に失敗",
			"エラー", MB_ICONERROR | MB_OK);
		return 0;
	}

		// 
		//CreateWindow(
		//	"BUTTON", "Push!",//ボタンの表示
		//	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		//	0, 0, 100, 50,
		//	hWnd, NULL, hInstance, NULL
		//);

		////TextBox
		//CreateWindow(
		//	"EDIT", "",
		//	WS_CHILD | WS_VISIBLE | ES_MULTILINE,	//←改行（高さがいっていないとダメ）
		//	0, 0, 200, 70,
		//	hWnd, NULL, hInstance, NULL
		//);

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// DirectXの初期化
	HRESULT hr;
	hr = InitDirectX(960, 540, hWnd, false);

	if (FAILED(hr))
	{
		MessageBox(hWnd,
			"DirectXの初期化に失敗",
			"エラー", MB_OK | MB_ICONERROR);
		return 0;
	}

	hr = InitSound();
	if (FAILED(hr))
	{
		MessageBox(hWnd, "サウンドの初期化失敗","エラー", MB_OK | MB_ICONERROR);
		return 0;
	}

	// ゲームの初期化
	hr = InitGame();
	if (FAILED(hr))
	{
		MessageBox(hWnd,
			"ゲームの初期化に失敗",
			"エラー", MB_OK | MB_ICONERROR); ///
	}

	// メッセージループ
	MSG message;
	FPS fps;
	while (1)
	{
		//メッセージがあるか確認
		if (PeekMessage(
			&message, NULL, 0, 0, PM_NOREMOVE))
		{
			// メッセージを取得
			// ※WM_QUITが送られていると戻り値がfalse
			if (!GetMessage(&message,NULL,0,0))
			{
				break;
			}
			else
			{
				// ウィンドウプロシージャへ
				// メッセージを転送
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		// メッセージがなければゲームの処理
		else
		{
			if (fps.IsCheck())
			{
				// 更新処理
				KayboadUpdate();
				UpdateGame();

				// 描画処理
				BeginDrawDirectX();
				DrawGame();
				EndDrawDirectX();
			}
			
		}
	}
	
	//課題一
	//int button;
	//int button2;
	//int button3;
	//int button4;
	//// メッセージボックスを表示する関数
	//button = MessageBox(NULL,
	//	"", "質問1",
	//	// ４つめの引数に、様々な定数を指定して
	//	// 色んな種類のメッセージボックスを表現する
	//	MB_YESNO |
	//	MB_ICONINFORMATION);
	// // 戻り値の値で押されたボタンを判定
	//if (button == IDYES)


	// 終了処理 （初期化と逆順で終了する）
	UninitGame();
	UninitSound();
	UninitDirectX();

	return 0;

}

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message,
	WPARAM wPatram, LPARAM IParam)
{
	switch (message)
	{

	//case WM_MOUSEMOVE: // マウスが移動 // WORD = 整数のデータ　2bit
	//{
		//マウスの座標はIParamに格納されている
		//IParamは４バイト（32ビット）のデータで
		//上位2バイト（上位16ビット）にY座標
		//下位2バイト（下位16ビット）にX座標を
		//格納している
		//利用する場合ビット演算で取り出す処理が必要
	//	WORD x = LOWORD(IParam); //下位16ビットを取り出す
	//	WORD y = HIWORD(IParam); //上位16ビットを取り出す
	//	char text[256];
	//	sprintf(text, "x:%d,y:%d", x, y);
	//	MessageBox(hWnd,
	//		text, "座標", MB_OK);
	//}
	//	break;

	case WM_KEYDOWN: // キーボードが押された
		//wParamにキー情報が格納されている  バーチャルキー
		if (wPatram == VK_ESCAPE)
		{
			// 確認メッセージの表示
			if (MessageBox(hWnd,
				"終了しますか？", "確認",
				MB_YESNO) == IDYES);
			{
				// ウィンドウを破壊
				// WM_DESTROYを通知
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE: // 〔×〕ボタンが押された
		if (MessageBox(hWnd,
			"終了しますか？", "確認",
			MB_YESNO) == IDNO)
		{
			return 0;
		}
		break;

	case WM_DESTROY: // ウィンドウが閉じられた
			// プログラムの終了を通知
			PostQuitMessage(0);
			break;
	}

	// デフォルトのウィンドウ処理を実行
	return DefWindowProc(
		hWnd, message, wPatram, IParam);
}
