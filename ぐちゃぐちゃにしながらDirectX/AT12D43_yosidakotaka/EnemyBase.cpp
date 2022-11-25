#include "EnemyBase.h"
#include "Game.h"

EnemyBase::EnemyBase()
	:m_transform{ 0.0f,0.0f,1.0f,1.0f,0.0f }
	,m_life(6)
	,m_pSprite(nullptr)
	,m_sizeW(0.0f)
	, m_sizeH(0.0f)
	,m_isDestroy(false)
{

	//頂点バッファやテクスチャの設定は
	//継承した元のクラスで行う

}

EnemyBase::~EnemyBase()
{
	delete m_pSprite;
}

void EnemyBase::Update()
{

}

void EnemyBase::Draw()
{
	Transform transform = m_transform;
	transform.posX -= GetCamera()->GetPosX();

	m_pSprite->Write(&m_uv, 0);
	m_pSprite->Write(&transform, 1);
	m_pSprite->Draw();
}

void EnemyBase::SetPos(float x, float y)
{
	m_transform.posX = x;
	m_transform.posY = y;
}

bool EnemyBase::IsDestroy()
{
	return m_isDestroy;
}

void EnemyBase::Destroy()
{
	m_isDestroy = true;
}

Transform EnemyBase::GetTransform()
{
	return m_transform;
}

float EnemyBase::GetWidth()
{
	return m_sizeW;
}

float EnemyBase::GetHeight()
{
	return m_sizeH;
}

int EnemyBase::GetLife()
{
	m_life--;
	return m_life;
}

void EnemyBase::CreateSprite(SpriteDesc desc)
{
	m_pSprite = new Sprite(desc);
	//大きさの設定
	m_sizeW = desc.pVtx[1].pos[0] - desc.pVtx[0].pos[0];
	m_sizeH = desc.pVtx[2].pos[1] - desc.pVtx[0].pos[1];

}

void EnemyBase::NockBack(int vector)
{
	m_transform.posX = m_transform.posX + 10 * vector;
}
