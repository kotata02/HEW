#ifndef _ENEMYZAKO_H_
#define _ENEMYZAKO_H_

#include "EnemyBase.h"

class EnemyZako:public EnemyBase
{
public:
	EnemyZako(SpriteDesc desc);
	~EnemyZako();
	void Update(Transform PTransform);
	void Attack();
	bool DameGet();
protected:
	bool damege;
private:
	float stayposX;
	float stayposY;
	int m_frame;
};


#endif // _ENEMYZAKO_H_

