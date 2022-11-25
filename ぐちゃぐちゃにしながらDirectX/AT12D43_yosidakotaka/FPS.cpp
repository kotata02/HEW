#include "FPS.h"

#pragma comment(lib,"winmm.lib")

FPS::FPS()
{
	timeBeginPeriod(1); // ���Ԃ̏�����

	// �J�n���_�̎���
	m_preTime = timeGetTime();
}

FPS::~FPS()
{
	timeEndPeriod(1);
}

bool FPS::IsCheck(void)
{
	// 1�t���[��(16.6667�~���b)�o�߂������m�F
	DWORD nowTime = timeGetTime();
	if (nowTime - m_preTime >= 1000 / 60)
	{
		// ���Ԃ��X�V
		m_preTime = nowTime;
		return true;
	}
	return false;
}
