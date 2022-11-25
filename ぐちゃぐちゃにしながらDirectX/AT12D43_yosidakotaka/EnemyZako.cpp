#include "EnemyZako.h"

int a ;
int ATKcount;
EnemyZako::EnemyZako(SpriteDesc desc)
{
	ATKcount = 0;
	Vertex vtx[]=
	{
	{ {-50.0f, -100.0f, 0.0f}, { 0.0f,0.0f }},
	{ {50.0f, -100.0f, 0.0f}, { 1.0f,0.0f }},
	{ {-50.0f, 0.0f, 0.0f}, { 0.0f,1.0f }},
	{ {50.0f, 0.0f, 0.0f}, { 1.0f,1.0f }}

	};
	m_uv.uvWidth = 1.0f / 2; // ‰¡3•ªŠ„‚Ì‰æ‘œ
	m_uv.uvHeight = 1.0f; // c1•ªŠ„‚Ì‰æ‘œ
	m_uv.uvTopLeftX = 0.0f;
	m_uv.uvTopLeftY = 0.0f;

	m_transform.scaleX = 1.5f;
	m_transform.scaleY = 1.5f;
	

	desc.pVtx = vtx;
	desc.pTexture = "Assets/Doro.png";
	CreateSprite(desc);

	stayposX = m_transform.posX;
	stayposY = m_transform.posY;
	a=1;
	damege = false;
	m_frame = 0;
}

EnemyZako::~EnemyZako()
{

}

void EnemyZako::Update(Transform PTransform)
{

	damege = false;
	if (m_frame >= 20)
	{
		m_uv.uvTopLeftX += m_uv.uvWidth;
		if (m_uv.uvTopLeftX >= 1.0f)
		{
			m_uv.uvTopLeftX = 0.0f;
		}
		m_frame = 0;
	}
	m_frame++;

	float PLpos = PTransform.posX-40.0f;
	float PRpos = PTransform.posX+40.0f;
	float PUpos = PTransform.posY - 100.0f;
	float PDpos = PTransform.posY + 0.0f;

	float Lpos = m_transform.posX - 50.0f;
	float Rpos = m_transform.posX + 50.0f;
	float Upos = m_transform.posY - 100.0f;
	float Dpos = m_transform.posY + 0.0f;

	if (PRpos > Lpos &&
		PLpos < Rpos &&
		PUpos < Dpos &&
		PDpos > Upos 
		)
	{
		if (m_transform.posX != PTransform.posX)
		{
			if (m_transform.posX-30 > PTransform.posX + 40)
				m_transform.posX -= 0.7f;
			if (m_transform.posX-30 < PTransform.posX + 40)
				m_transform.posX += 0.7f;
		}
		if (m_transform.posY != PTransform.posY)
		{
			if (m_transform.posY-40 > PTransform.posY)
				m_transform.posY -= 0.7f;
			if (m_transform.posY-40 < PTransform.posY)
				m_transform.posY += 0.7f;
		}
		stayposX = m_transform.posX;
		stayposY = m_transform.posY;
	}
	else
	{
		
		if (m_transform.posX <= stayposX - 100+((int)stayposY % 30))
		{
			a = 1;
		}
		if (m_transform.posX >= stayposX + 100+((int)stayposY %30))
		{
			a = -1;
		}
		m_transform.posX = m_transform.posX + (0.6f*a);
	}

	//Õ“ËŽž‚Ìƒ_ƒ[ƒW”»’è
	if (PRpos-25 > Lpos+25 &&
		PLpos+25 < Rpos-25 &&
		PUpos+35 < Dpos-35 &&
		PDpos-35 > Upos+35 &&
		ATKcount > 100)
	{
		ATKcount = 0;
		damege = true;
	}
	ATKcount++;
}

void EnemyZako::Attack()
{
	
}

bool EnemyZako::DameGet()
{
	return damege;
}
