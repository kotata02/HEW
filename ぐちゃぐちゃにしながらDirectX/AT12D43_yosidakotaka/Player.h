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
	int m_vector;//�����i�E�P�F���O�j
	AnimeUV m_uv;
	int m_frame;//�t���[���J�E���g�p
	int m_sinFrame;

	bool m_move;//�����Ă��邩
};

#endif // _PLAYER_H_

