#include"DirectX.h"

//グローバル変数
//アセット情報を取り扱う機能
ID3D11Device *g_pDevice;
//命令を送る機能
ID3D11DeviceContext *g_pContext;

IDXGISwapChain *g_pSwapChain;

ID3D11RenderTargetView *g_pRTV;
//初期化処理
HRESULT InitDirectX(UINT width, UINT height, HWND hWnd, bool fullScreen)
{
	HRESULT hr;//成功はS_OK,失敗はE_FALLを返す

	//スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width						= width;
	sd.BufferDesc.Height					= height;
	sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator		= 60;
	sd.BufferDesc.RefreshRate.Denominator	= 1;
	sd.SampleDesc.Count						= 1;
	sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;//フレームバッファの使用方法
	sd.BufferCount							= 1;//フレームバッファの数
	sd.OutputWindow							= hWnd;//関連付けるウィンドウ
	sd.Windowed								= fullScreen ? FALSE : TRUE;
	sd.Flags								= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//DeviceとContextの作成
	//ドライバの種類
	D3D_DRIVER_TYPE driverType;
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,D3D_DRIVER_TYPE_WARP,D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	//機能レベル
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,D3D_FEATURE_LEVEL_9_2,D3D_FEATURE_LEVEL_9_1
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);
	UINT createDeviceFlags = 0;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//作成可能な設定でDirectXの機能を有効化
	for (UINT i = 0; i < numDriverTypes; i++) {
		driverType = driverTypes[i];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pDevice, &featureLevel, &g_pContext);
		//成功してるか判定
		if (SUCCEEDED(hr)) 
		{ 
			break;
		}
	}
	//失敗してるか判定
	if (FAILED(hr)) { return hr; }

	//レンダーターゲットの作成
	//GPUの出力先をあらかじめ決めておく
	//※決めないとどこに書き込めばいいのか分からない
	//
	ID3D11Texture2D *pBackBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, _uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (SUCCEEDED(hr)) {
		hr = g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRTV);
		g_pContext->OMSetRenderTargets(1, &g_pRTV, nullptr);//GPUの出力設定
	}

	//ビューポートの作成
	//フレームバッファのどの位置に表示するか
	//細かく設定
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(vp));
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pContext->RSSetViewports(1, &vp);

	return hr;

}
//終了処理
void UninitDirectX(void)
{
	g_pRTV->Release();
	g_pSwapChain->SetFullscreenState(false, NULL);
	g_pSwapChain->Release();
	g_pContext->ClearState();
	g_pContext->Release();
	g_pDevice->Release();
}
void BeginDrawDirectX(void)
{
	float color[4] = { 0.7,1.0f,0.8f,1.0f };
	g_pContext->ClearRenderTargetView(g_pRTV, color);
}
void EndDrawDirectX(void)
{
	g_pSwapChain->Present(0, 0);
}
ID3D11Device* GetDevice(void)
{
	return g_pDevice;
}
ID3D11DeviceContext* GetContext(void)
{
	return g_pContext;
}