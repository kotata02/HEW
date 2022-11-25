#ifndef _CONSTANT_BUFFER_H_
#define _CONSTANT_BUFFER_H_

#include "DirectX.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	//定数バッファは中身を頻繁に
	//書き換えるので書き込み先の
	//容量を指定して作成
	HRESULT Create(int size);
	//定数バッファへのデータを書き込み
	//voidほどのポインタでも渡せる
	void Write(void* pData);
	//GPUに定数バッファを利用するよう指定
	void Bind(int slot);
private:
	//
	ID3D11Buffer* m_pBuffer;
};

#endif //!_CONSTANT_BUFFER_H_

