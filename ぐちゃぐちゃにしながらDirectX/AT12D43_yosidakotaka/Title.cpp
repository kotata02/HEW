#include "Title.h"

Title::Title(SpriteDesc desc)
{
	HRESULT hr;
	Vertex vtx[] =
	{
		{ {-50.0f, -100.0f, 0.0f}, { 0.0f,0.0f }},
		{ {50.0f, -100.0f, 0.0f}, { 1.0f,0.0f }},
		{ {-50.0f, 0.0f, 0.0f}, { 0.0f,1.0f }},
		{ {50.0f, 0.0f, 0.0f}, { 1.0f,1.0f }}

	};
	//移動回転拡縮
	m_transform.posX = 0.0f;
	m_transform.posY = 0.0f;
	m_transform.scaleX = 2.0f;
	m_transform.scaleY = 2.0f;
	m_transform.angle = 0.0f;

	//スプライトの作成
	desc.pVtx = vtx;
	desc.pTexture = "Assets/MAINTITLE.PNG";
	m_pSprite = new Sprite(desc);

	m_transform.posX = 500.0f;
	m_transform.posY = 400.0f;
	m_transform.scaleX = 3.0f;
	m_transform.scaleY = 3.0f;
}

Title::~Title()
{
	delete m_pSprite;
}

void Title::Update()
{
}

void Title::Draw()
{
	//定数バッファ更新

	m_pSprite->Write(&m_transform, 0);
	m_pSprite->Draw();
}
