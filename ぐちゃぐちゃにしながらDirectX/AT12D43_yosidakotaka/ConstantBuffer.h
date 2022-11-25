#ifndef _CONSTANT_BUFFER_H_
#define _CONSTANT_BUFFER_H_

#include "DirectX.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	//�萔�o�b�t�@�͒��g��p�ɂ�
	//����������̂ŏ������ݐ��
	//�e�ʂ��w�肵�č쐬
	HRESULT Create(int size);
	//�萔�o�b�t�@�ւ̃f�[�^����������
	//void�قǂ̃|�C���^�ł��n����
	void Write(void* pData);
	//GPU�ɒ萔�o�b�t�@�𗘗p����悤�w��
	void Bind(int slot);
private:
	//
	ID3D11Buffer* m_pBuffer;
};

#endif //!_CONSTANT_BUFFER_H_

