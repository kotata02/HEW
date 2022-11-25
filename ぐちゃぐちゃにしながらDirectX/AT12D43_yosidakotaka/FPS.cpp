#include "FPS.h"

#pragma comment(lib,"winmm.lib")

FPS::FPS()
{
	timeBeginPeriod(1); // 時間の初期化

	// 開始時点の時間
	m_preTime = timeGetTime();
}

FPS::~FPS()
{
	timeEndPeriod(1);
}

bool FPS::IsCheck(void)
{
	// 1フレーム(16.6667ミリ秒)経過したか確認
	DWORD nowTime = timeGetTime();
	if (nowTime - m_preTime >= 1000 / 60)
	{
		// 時間を更新
		m_preTime = nowTime;
		return true;
	}
	return false;
}
