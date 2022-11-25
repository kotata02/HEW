#ifndef _BULLET_H_
#define _BULLET_H_

#include "Sprite.h"

class Bullet
{
public:
	Bullet(SpriteDesc desc);
	~Bullet();
	void Update();
	void Draw();

	void SetPos(float x, float y);
	void SetMove(float x, float y);
	bool IsDestroy();
	void Destroy();

	Transform GetTransform();
	float GetWidth();
	float GetHeight();

private:
		Transform m_transform;
	Sprite* m_pSprite;

	//�e�̏��
	bool m_isDestroy;	//�e�j���t���O
	float m_moveX;		//�e�̈ړ�����X
	float m_moveY;		//�e�̈ړ�����Y
	float m_sizeW;		//�����̑傫��
	float m_sizeH;		//�c���̑傫��

};

#endif // !_BULLET_H_

