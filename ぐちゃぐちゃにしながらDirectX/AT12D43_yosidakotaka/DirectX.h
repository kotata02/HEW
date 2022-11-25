#ifndef _DIRECT_H_
#define _DIRECT_H_

#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

//DirectX�̏�����
//width ��ʂ̉���
//height ��ʂ̏c��
//hWnd ��ʂ̍X�V���s���E�B���h�E
//fullScreen �S���
//�߂�l�@�������ɐ���������
//
HRESULT InitDirectX(UINT width, UINT height, HWND hWnd, bool fullScreen);
//�I������
void UninitDirectX(void);

//DirectX�̕`�揈��
void BeginDrawDirectX(void);
void EndDrawDirectX(void);

//DirectX�̏���n���֐�
ID3D11Device* GetDevice(void);

ID3D11DeviceContext* GetContext(void);

#endif//_DIRECT_H_
