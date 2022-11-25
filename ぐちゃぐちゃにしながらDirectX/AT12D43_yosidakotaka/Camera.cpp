#include "Camera.h"

Camera::Camera(Player* player)
	:m_posX(0.0f)
	,m_posY(0.0f)
,m_pPlayer(player)
{


}

Camera::~Camera()
{

}

void Camera::Update()
{


		m_posX = m_pPlayer->GetTransform().posX;
		m_posY = m_pPlayer->GetTransform().posY;

}

float Camera::GetPosX()
{
	return m_posX-480;
}

float Camera::GetPosY()
{
	return m_posY;
}
