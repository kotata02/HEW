#include "Object.h"

Object::Object(SpriteDesc desc)
	:m_frame(0), m_sinFrame(0)
{
	HRESULT hr;
	Vertex vtx[] =
	{
		{ {-50.0f, -100.0f, 0.0f}, { 0.0f,0.0f }},
		{ {50.0f, -100.0f, 0.0f}, { 1.0f,0.0f }},
		{ {-50.0f, 0.0f, 0.0f}, { 0.0f,1.0f }},
		{ {50.0f, 0.0f, 0.0f}, { 1.0f,1.0f }}

	};

	// アニメーションでUVを変更するためのデータ

	m_uv.uvWidth = 1.0f / 4; // 横4分割の画像
	m_uv.uvHeight = 1.0f / 3; // 縦3分割の画像
	m_uv.uvTopLeftX = 0.25f;
	m_uv.uvTopLeftY = 0.3f;

	//移動回転拡縮
	m_transform.posX = 0.0f;
	m_transform.posY = 0.0f;
	m_transform.scaleX = 1.0f;
	m_transform.scaleY = 1.0f;
	m_transform.angle = 0.0f;

	//スプライトの作成
	desc.pVtx = vtx;
	desc.pTexture = "Assets/aaaa.png";
	m_pSprite = new Sprite(desc);

	m_transform.posX = 280.0f;
	m_transform.posY = 480.0f;


}

Object::~Object()
{
	delete m_pSprite;
}

void Object::Update(void)
{
	if (m_frame >= 10)
	{
		// キャラクターのアニメーションは
	// UVを変化させていく
		m_uv.uvTopLeftX += m_uv.uvWidth;
		if (m_uv.uvTopLeftX >= 1.0f)
		{
			m_uv.uvTopLeftX = 0.25f;
		}
		// 次のフレームを数えるために
		m_frame = 0;
	}
	m_frame++;

	//カーソルの動き
	//m_transform.posX=sinf(m_sinFrame*360.0f/60*3.14f/180)*10.0f+0;

	//揺れもの
	/*
	m_transform.angle = sin(m_sinFrame*360.0f/100*3.14f/180)*10.0f*3.14/180;*/

	//軟体アニメーション
	/*float rad = m_sinFrame * 360.0f / 120 * 3.14f / 180;
	m_transform.scaleX = (sin(rad)*0.5f + 0.5f)*0.4f + 0.8f;
	m_transform.scaleY = (sin(rad + 3.14f)*0.5f + 0.5f)*0.4f + 0.8f;*/

	m_transform.posX -= 1.0f;
	if (m_transform.posX <= 0)
		m_transform.posX = 980;

	m_sinFrame++;
}

void Object::Draw(void)
{
	//定数バッファ更新
	m_pSprite->Write(&m_uv, 0);
	m_pSprite->Write(&m_transform, 1);
	m_pSprite->Draw();
}