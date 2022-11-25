#ifndef _TITLE_H_
#define _TITLE_H_

#include "Sprite.h"

class Title
{
public:
	Title(SpriteDesc desc);
	~Title();
	void Update();
	void Draw();
private:
	//AnimeUV m_uv;
	Transform m_transform;
	Sprite* m_pSprite;
};


#endif // !_TITLE_H_

