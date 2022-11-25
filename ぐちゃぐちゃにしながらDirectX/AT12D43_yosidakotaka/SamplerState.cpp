#include "SamplerState.h"

SamplerState::SamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//テクスチャ描画時の補間方法
	//LINEAR...間を補間　/　POINT...間を補間しない
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	HRESULT hr;
	hr = GetDevice()->CreateSamplerState(&desc,&m_pState);


}

SamplerState::~SamplerState()
{
	m_pState->Release();
}

void SamplerState::Bind()
{
	GetContext()->PSSetSamplers(0, 1, &m_pState);
}
