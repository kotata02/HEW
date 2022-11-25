#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "Sprite.h"

class GameOver
{
public:
	GameOver(SpriteDesc desc);
	~GameOver();
	void Update();
	void Draw();
private:
	//AnimeUV m_uv;
	Transform m_transform;
	Sprite* m_pSprite;
};

#endif // !_GAMEOVER_H_

