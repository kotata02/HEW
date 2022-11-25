#ifndef _FPS_H_
#define _FPS_H_

#include<Windows.h>
class FPS
{
public:
	FPS();
	~FPS();

	bool IsCheck(void);

private:
	DWORD m_preTime;//’¼‘O‚ÉÀs‚µ‚½ŠÔ
};

#endif // _FPS_H_
