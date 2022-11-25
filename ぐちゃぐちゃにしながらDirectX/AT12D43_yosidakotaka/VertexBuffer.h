#ifndef _VERTEX_BUFFER_
#define _VERTEX_BUFFER_
#include"DirectX.h"

//���_���
struct Vertex
{
	float pos[3];//���W
	float uv[2];
};

class VertexBuffer
{
public:
	//pVtx �쐬�̂��ƂƂȂ钸�_�̔z��
	//num �z��̐�
	HRESULT Create(Vertex* pVtx,int num);

	void Draw(void);

private:
	ID3D11Buffer* m_pVtxBuf;
};

#endif//_VERTEX_BUFFER_
