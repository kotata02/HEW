#ifndef _GAME_H_
#define _GAME_H_

#include<d3d11.h>
#include"DirectX.h"
#include"Camera.h"
#include"Effect.h"
#include"Mapchip.h"

enum SCENETYPE
{
	TITLESCENE,
	GAMESCENE,
	CLEARSCENE,
	GAMEOVERSCENE,
};

struct Float2
{
	float x;
	float y;
};

HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

Camera* GetCamera();
void SceneChange(SCENETYPE nextscene);
void CreateMap(ROOMID nextroom,const char* pAWalltex);
void UpdateMap(const char* pAWalltex, const char* pBWalltex,const char* psuisoutex);
#endif // !_GAME_H_

