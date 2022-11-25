#include "Clear.h"

Clear::Clear(SpriteDesc desc)
{
	HRESULT hr;
	Vertex vtx[] =
	{
		{ {-50.0f, -100.0f, 0.0f}, { 0.0f,0.0f }},
		{ {50.0f, -100.0f, 0.0f}, { 1.0f,0.0f }},
		{ {-50.0f, 0.0f, 0.0f}, { 0.0f,1.0f }},
		{ {50.0f, 0.0f, 0.0f}, { 1.0f,1.0f }}

	};
	//�ړ���]�g�k
	m_transform.posX = 0.0f;
	m_transform.posY = 0.0f;
	m_transform.scaleX = 2.0f;
	m_transform.scaleY = 2.0f;
	m_transform.angle = 0.0f;

	//�X�v���C�g�̍쐬
	desc.pVtx = vtx;
	desc.pTexture = "Assets/Clear.PNG";
	m_pSprite = new Sprite(desc);

	m_transform.posX = 500.0f;
	m_transform.posY = 400.0f;
	m_transform.scaleX = 3.0f;
	m_transform.scaleY = 3.0f;
}

Clear::~Clear()
{
	delete m_pSprite;
}

void Clear::Update()
{
}

void Clear::Draw()
{
	//�萔�o�b�t�@�X�V

	m_pSprite->Write(&m_transform, 0);
	m_pSprite->Draw();
}
