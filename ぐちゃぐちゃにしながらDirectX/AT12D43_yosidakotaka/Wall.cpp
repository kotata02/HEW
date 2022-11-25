#include "Wall.h"
#include"Game.h"
CWall::CWall(SpriteDesc desc,int sizeW,int sizeH,int uvNo)
{
	HRESULT hr;
	Vertex vtx[] =
	{
		{ {-10.0f, -10.0f, 0.0f}, { 0.0f,0.0f }},
		{ {10.0f, -10.0f, 0.0f}, { 1.0f,0.0f }},
		{ {-10.0f, 10.0f, 0.0f}, { 0.0f,1.0f }},
		{ {10.0f, 10.0f, 0.0f}, { 1.0f,1.0f }}

	};

	// UVの分割
	m_uv.uvWidth = 1.0f / sizeW; // 横分割の画像
	m_uv.uvHeight = 1.0f / sizeH; // 縦分割の画像

	int noY = uvNo / sizeH;
	int noX = uvNo % sizeW;



	m_uv.uvTopLeftX = (m_uv.uvWidth * noX);
	m_uv.uvTopLeftY = (m_uv.uvHeight * noY);

	//移動回転拡縮
	m_transform.posX = 0.0f;
	m_transform.posY = 0.0f;
	m_transform.scaleX = 1.0f;
	m_transform.scaleY = 1.0f;
	m_transform.angle = 0.0f;

	//スプライトの作成
	desc.pVtx = vtx;
	m_pSprite = new Sprite(desc);
}

CWall::~CWall()
{
	delete m_pSprite;
}

void CWall::Update(void)
{
	//当たり判定の大きさを決める
	m_collision.x = m_transform.posX;
	m_collision.y = m_transform.posY;
	m_collision.Width = 20;
	m_collision.Height = 20;
}

void CWall::Draw(void)
{
	Transform transform = m_transform;
	transform.posX -= GetCamera()->GetPosX();
	//定数バッファ更新
	m_pSprite->Write(&m_uv, 0);
	m_pSprite->Write(&transform, 1);
	m_pSprite->Draw();
	/*m_pSprite->Write(&m_transform, 0);
	m_pSprite->Draw();*/
}

void CWall::SetObject(float x, float y)
{
	m_transform.posX = x;
	m_transform.posY = y;
}

Transform CWall::GetTransform()
{
	return m_transform;
}

CollisionData CWall::GetCollision()
{
	return m_collision;
}