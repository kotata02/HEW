#ifndef _ENEMY_BASE_H_
#define _ENEMY_BASE_H_

#include"Sprite.h"

class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();
	void Update();
	void Draw();

	void SetPos(float x, float y);
	bool IsDestroy();
	void Destroy();

	Transform GetTransform();
	float GetWidth();
	float GetHeight();
	int GetLife();
	void NockBack(int vector);
	
protected:
	//子クラスのコンストラクタ内で呼び出す
	void CreateSprite(SpriteDesc desc);
	

protected:
	AnimeUV m_uv;
	Transform m_transform;
	int m_life;
	Sprite* m_pSprite;
private:
	
	bool m_isDestroy;
	float m_sizeW;
	float m_sizeH;

};

#endif // _ENEMY_BASE_H_

