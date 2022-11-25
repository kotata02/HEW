#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"Sprite.h"

class Player
{
public:
	Player(SpriteDesc desc);
	~Player();

	void Update();
	void Draw();

	bool GetVector();
	void SetObject(float x, float y);
	Transform GetTransform();
	Transform GetOldtransform();
	CollisionData GetCollision();
private:
	CollisionData m_collision;
	Transform m_transform;
	Transform m_oldtransform;
	Sprite* m_pSprite;
	int m_vector;//向き（右１：左０）
	AnimeUV m_uv;
	int m_frame;//フレームカウント用
	int m_sinFrame;

	bool m_move;//動いているか
};

#endif // _PLAYER_H_

