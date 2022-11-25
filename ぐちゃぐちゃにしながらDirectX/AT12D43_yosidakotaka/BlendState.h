#ifndef _BLEND_STATE_H_
#define _BLEND_STATE_H_

#include"DirectX.h"

class BlendState
{
public:
		BlendState(bool add);
	~BlendState();

	void Bind(void);
private:
	ID3D11BlendState* m_pBlendState;
};

#endif // _BLEND_STATE_H_

