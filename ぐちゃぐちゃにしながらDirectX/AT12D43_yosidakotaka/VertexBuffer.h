#ifndef _VERTEX_BUFFER_
#define _VERTEX_BUFFER_
#include"DirectX.h"

//頂点情報
struct Vertex
{
	float pos[3];//座標
	float uv[2];
};

class VertexBuffer
{
public:
	//pVtx 作成のもととなる頂点の配列
	//num 配列の数
	HRESULT Create(Vertex* pVtx,int num);

	void Draw(void);

private:
	ID3D11Buffer* m_pVtxBuf;
};

#endif//_VERTEX_BUFFER_
