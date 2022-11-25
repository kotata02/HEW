#ifndef _SAMPLER_STATE_H_
#define _SAMPLER_STATE_H_

#include"DirectX.h"

class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void Bind();
private:
	ID3D11SamplerState* m_pState;
};

#endif // _SAMPLER_STATE_H_