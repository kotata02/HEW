#include"BackGround.h"
#include"Game.h"

BackGround::BackGround(SpriteDesc desc)
	:m_transform{0.0f,0.0f,1.0f,1.0f,0.0f}
{
	HRESULT hr;
	Vertex vtx[] =
	{
		{{0.0f,0.0f,0.0f},{0.0f,0.0f}},
		{{2000.0f,-2000.0f,0.0f},{1.0f,0.0f}},
		{{0.0f,2000.0f,0.0f},{0.0f,1.0f}},
		{{2000.0f,2000.0f,0.0f},{1.0f,1.0f}},
	};

	//ˆÚ“®‰ñ“]Šgk
	m_transform.posX = 0.0f;
	m_transform.posY = 0.0f;
	m_transform.scaleX = 1.0f;
	m_transform.scaleY = 1.0f;
	m_transform.angle = 0.0f;

	desc.pVtx = vtx;
	desc.pTexture="Assets/BackGround.PNG";
	m_pSprite = new Sprite(desc);

}

BackGround::~BackGround()
{
	delete m_pSprite;
}

void BackGround::Update(void)
{
	//“®‚©‚·ƒXƒs[ƒh
	//1•b=60ƒtƒŒ[ƒ€‚È‚ç1/60‚Å“®‚©‚¹‚Î
	//60‰ñˆ—‚µ‚½‚Æ‚«60/60‚ÅUVÀ•W1.0•ªˆÚ“®
	/*float scroll = 1.0f/900;
	m_animeUV.uvTopLeftX += scroll;
	m_animeUV.uvTopLeftY -= scroll;*/

	/*float scroll = GetCamera()->GetPosX() / 960.0f;
		m_animeUV.uvTopLeftX = scroll;*/
}

void BackGround::Draw(void)
{
	//m_pSprite->Write(&m_animeUV, 0);
	Transform transform = m_transform;
	transform.posX -= GetCamera()->GetPosX();

	m_pSprite->Write(&transform, 0);
	m_pSprite->Draw();
}
