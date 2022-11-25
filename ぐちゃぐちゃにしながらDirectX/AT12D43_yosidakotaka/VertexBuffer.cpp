#include "VertexBuffer.h"

HRESULT VertexBuffer::Create(Vertex * pVtx, int num)
{
	HRESULT hr;
	ID3D11Device* pDevice = GetDevice();

	// バッファ情報　設定
	D3D11_BUFFER_DESC vtxBufDesc;
	ZeroMemory(&vtxBufDesc, sizeof(vtxBufDesc));
	vtxBufDesc.ByteWidth =
		sizeof(Vertex) * num;							// バッファの大きさ
	vtxBufDesc.Usage = D3D11_USAGE_DEFAULT;				// メモリ上での管理方法
	vtxBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// GPU上での利用方法

	// バッファ初期　データ設定
	D3D11_SUBRESOURCE_DATA vtxSubResource;
	ZeroMemory(&vtxSubResource, sizeof(vtxSubResource));
	vtxSubResource.pSysMem = pVtx;						// バッファに入れ込むデータ

	// 作成
	hr = pDevice->CreateBuffer(&vtxBufDesc, &vtxSubResource, &m_pVtxBuf);
	if (FAILED(hr)) { return hr; }
}

void VertexBuffer::Draw(void)
{
	ID3D11DeviceContext* pContext = GetContext();

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pContext->IASetVertexBuffers(0, 1, &m_pVtxBuf, &stride, &offset); // 頂点バッファをGPUに渡す
	pContext->Draw(4, 0); // 描画
}
