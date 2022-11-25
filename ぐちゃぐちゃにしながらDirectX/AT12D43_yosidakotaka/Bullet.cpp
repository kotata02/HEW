#include"Bullet.h"
#include"Game.h"

//íeópÇÃíËêî
const float BULLET_LIMIT_MARGIN = 50.0f;

const float BULLET_LIMIT_LEFT = 
	0.0f-BULLET_LIMIT_MARGIN;

const float BULLET_LIMIT_RIGHT =
2010.0f + BULLET_LIMIT_MARGIN;

const float BULLET_LIMIT_TOP =
-100.0f - BULLET_LIMIT_MARGIN;

const float BULLET_LIMIT_BOTTOM =
540.0f + BULLET_LIMIT_MARGIN;


Bullet::Bullet(SpriteDesc desc)
:m_transform{0.0f,0.0f,1.0f,1.0f,0.0f}
,m_isDestroy(false)
,m_moveX(0.0f)
,m_moveY(0.0f)
{
	
	Vertex vtx[] =
	{
		{ {-10.0f, -10.0f, 0.0f}, { 0.0f,0.0f }},
		{ {10.0f, -10.0f, 0.0f}, { 1.0f,0.0f }},
		{ {-10.0f,10.0f, 0.0f}, { 0.0f,1.0f }},
		{ {10.0f, 10.0f, 0.0f}, { 1.0f,1.0f }}

	};
	desc.pVtx = vtx;
	desc.pTexture = "Assets/BULLET.PNG";

	m_pSprite = new Sprite(desc);

	//íeÇÃëÂÇ´Ç≥åvéZ
	m_sizeW = vtx[1].pos[0] - vtx[0].pos[0];
	m_sizeH= vtx[2].pos[1] - vtx[0].pos[1];
}

Bullet::~Bullet()
{
	delete m_pSprite;
}

void Bullet::Update()
{
	//à⁄ìÆèàóù
	m_transform.posX += m_moveX;
	m_transform.posY += m_moveY;

	//âÒì]èàóù
	//m_transform.angle += 12 * 3.141592f / 180;//ÉâÉWÉAÉìäpÇ…íºÇ∑

	//âÊñ äOîªíË
	if (m_transform.posX < BULLET_LIMIT_LEFT)
	{
		m_isDestroy = true;
	}
	if (m_transform.posX > BULLET_LIMIT_RIGHT)
	{
		m_isDestroy = true;
	}
	if (m_transform.posY < BULLET_LIMIT_TOP)
	{
		m_isDestroy = true;
	}
	if (m_transform.posY > BULLET_LIMIT_BOTTOM)
	{
		m_isDestroy = true;
	}

}

void Bullet::Draw()
{
	Transform transform = m_transform;
	transform.posX -= GetCamera()->GetPosX();

	m_pSprite->Write(&transform, 0);
	m_pSprite->Draw();
}

void Bullet::SetPos(float x, float y)
{
	m_transform.posX = x;
	m_transform.posY = y;
}

void Bullet::SetMove(float x, float y)
{
	m_moveX = x;
	m_moveY = y;
}

bool Bullet::IsDestroy()
{
	return m_isDestroy;
}

void Bullet::Destroy()
{
	m_isDestroy = true;
}

Transform Bullet::GetTransform()
{
	return m_transform;
}

float Bullet::GetWidth()
{
	return m_sizeW;
}

float Bullet::GetHeight()
{
	return m_sizeH;
}
