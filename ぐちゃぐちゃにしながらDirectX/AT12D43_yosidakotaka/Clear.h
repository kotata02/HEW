#ifndef _CLEAR_H_

#define _CLEAR_H_

#include "Sprite.h"

class Clear
{
public:
	Clear(SpriteDesc desc);
	~Clear();
	void Update();
	void Draw();
private:
	//AnimeUV m_uv;
	Transform m_transform;
	Sprite* m_pSprite;
};

#endif // !_CLEAR_H_

