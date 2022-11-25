#ifndef _Object2_H_
#define _Object2_H_

#include"Sprite.h"


class Object2
{
public:
	Object2(SpriteDesc desc);
	~Object2();

	void Update(void);
	void Draw(void);

private:

	AnimeUV m_uv;
	int m_frame;//フレームカウント用
	Transform m_transform;
	int m_sinFrame;
	Sprite* m_pSprite;
};

#endif // !_Object2_H_

