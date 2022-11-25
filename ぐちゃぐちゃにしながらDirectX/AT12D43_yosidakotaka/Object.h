#ifndef _OBJECT_H_
#define _OBJECT_H_

#include"Sprite.h"


class Object
{
public:
	Object(SpriteDesc desc);
	~Object();

	void Update(void);
	void Draw(void);

private:

	AnimeUV m_uv;
	int m_frame;//フレームカウント用
	Transform m_transform;
	int m_sinFrame;
	Sprite* m_pSprite;
};

#endif // !_OBJECT_H_

