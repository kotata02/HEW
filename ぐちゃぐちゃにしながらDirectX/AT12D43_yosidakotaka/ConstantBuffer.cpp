#include "ConstantBuffer.h"

ConstantBuffer::ConstantBuffer()
	:m_pBuffer(nullptr)
{
	
}

ConstantBuffer::~ConstantBuffer()
{
	if (m_pBuffer != nullptr)
	{
		m_pBuffer->Release();
	}
}

HRESULT ConstantBuffer::Create(int size)
{
	HRESULT hr;

	D3D11_BUFFER_DESC bufDesc = {};
	bufDesc.ByteWidth = size;
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags =
		D3D11_BIND_CONSTANT_BUFFER;

	hr = GetDevice()->CreateBuffer(&bufDesc, nullptr, &m_pBuffer);

	return hr;
}

void ConstantBuffer::Write(void * pData)
{
	GetContext()->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}

void ConstantBuffer::Bind(int slot)
{
	//1番目の引数で何番の定数バッファに割り当てるか決める
	GetContext()->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}
