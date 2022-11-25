#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include"Sprite.h"

class BackGround
{
public:
	BackGround(SpriteDesc desc);
	~BackGround();

	void Update();
	void Draw();

private:
	Sprite* m_pSprite;
	Transform m_transform;
};

#endif