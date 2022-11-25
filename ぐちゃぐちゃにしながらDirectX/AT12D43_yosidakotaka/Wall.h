#pragma once

#include"Sprite.h"

class CWall
{
public:
	CWall(SpriteDesc desc, int sizeW, int sizeH, int uvNo);
	~CWall();
	void Update(void);
	void Draw(void);

	void SetObject(float x, float y);
	Transform GetTransform();
	CollisionData GetCollision();
private:
	AnimeUV m_uv;
	CollisionData m_collision;
	Transform m_transform;
	Sprite* m_pSprite;
};
