#ifndef _Sprite_H_
#define _Sprite_H_
#include"VertexBuffer.h"
#include"Shader.h"
#include"ConstantBuffer.h"

struct AnimeUV
{
	float uvWidth;		//������̉���
	float uvHeight;		//������̏c��
	float uvTopLeftX;	//�����X���W
	float uvTopLeftY;	//�����Y���W
};

struct Transform
{
	float posX, posY;		//�|���S���̈ʒu
	float scaleX, scaleY;	//�|���S���̑傫��
	float angle;			//�|���S���́i��]���v��肪�{�j
	float dummy[3];			//16�o�C�g�ŋ�؂��悤�ɐ����킹
};
struct CollisionData	//�����蔻��̃f�[�^
{
	float x;				//���S���WX
	float y;				//���S���WY
	float Width;			//����
	float Height;			//�c��
	float kyori;			//����
};

//�����蔻��p�f�[�^
struct Collisiondata
{
	float posX, posY;		//�����蔻��̈ʒu
	float scaleX, scaleY;	//�����蔻��̑傫��
};

//�|���S���N���X���쐬���邽�߂̏��
struct SpriteDesc
{
	Vertex* pVtx;
	const char* pTexture;
	VertexShader* pVS;
	PixelShader* pPS;
	ConstantBuffer* pConst[4];
};

class Sprite
{
public:
	Sprite(SpriteDesc desc);
	~Sprite();

	void Write(void* pData, int slot);
	void Draw();
private:
	VertexBuffer* m_pVtxBuf;
	ID3D11ShaderResourceView* m_pTexture;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
	ConstantBuffer* m_pConstantBuf[4];
};

#endif // _Sprite_H_

