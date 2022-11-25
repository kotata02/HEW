#ifndef _CAMERA_H_
#define _CAMERA_H_

#include"Player.h"

class Camera
{
public:
	Camera(Player* Player);
	~Camera();
	void Update();
	float GetPosX();
	float GetPosY();
private:
	Player* m_pPlayer;
	float m_posX;
	float m_posY;
};

#endif // _CAMERA_H_

