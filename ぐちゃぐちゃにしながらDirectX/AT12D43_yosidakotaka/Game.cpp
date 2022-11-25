#include "Game.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "DirectXTex/TextureLoad.h"
#include "BlendState.h"
#include"SamplerState.h"
#include"Keyboard.h"

#include "Player.h"
#include "BackGround.h"
#include"Camera.h"
#include"Title.h"
#include"Clear.h"
#include"Gameover.h"
#include "Sound.h"
#include"Wall.h"
#include"Sprite.h"

//�v���g�^�C�v�錾
Float2 CollisionBlock(Transform trans, CollisionData col, CollisionData targetcol,Transform oldpos);

//----�O���[�o���ϐ�
VertexBuffer* g_pPolygon;
VertexShader* g_pVS;
VertexShader* g_pAnimeVS;
VertexShader* g_pTransformVS;
PixelShader* g_pPS;
PixelShader* g_pNegaPosiPS;
ConstantBuffer* g_pUVBuf;
ConstantBuffer* g_pTransformBuf;
//ID3D11ShaderResourceView* g_pTexture;
BlendState* g_pBlendState;
BlendState* g_pAddBlend;
SamplerState* g_pSamplerState;

Player* g_pPlayer;
BackGround* g_BackGround;
Camera* g_pCamera;
Title* g_pTitle;
Clear* g_pClear;
GameOver* g_pGameOver;

XAUDIO2_BUFFER* g_pBGM;
XAUDIO2_BUFFER* g_pSE;

CWall* g_pWall[MAP_HIGHT / PANEL_HIGHT][MAP_WIDE / PANEL_WIDE];

int Plife;
int Enemycount;
int enemydie;
int fpscount;

ROOMID nowroom;

SCENETYPE sceneType = TITLESCENE;		//���݂̃V�[��
SCENETYPE nextsceneType;	//���̃V�[��

IXAudio2SourceVoice* pSource;

//���̃}�b�v�z��ɍD���ȃ}�b�v�̔z��̒l������
int mapchip[MAP_HIGHT / PANEL_HIGHT][MAP_WIDE / PANEL_WIDE];

Float2 mapchipPos[MAP_HIGHT / PANEL_HIGHT][MAP_WIDE / PANEL_WIDE];

HRESULT InitGame(void)
{
	enemydie = 0;
	Enemycount = 0;
	fpscount = 0;
	HRESULT hr;
	Vertex vtx[] = 
	{
		{{420.0f,10.0f,0.0f},{0.0f,0.0f}},
		{{930.0f,10.0f,0.0f},{1.0f,0.0f}},
		{{420.0f,500.0f,0.0f},{0.0f,1.0f}},
		{{930.0f,500.0f,0.0f},{1.0f,1.0f}},
	};
	g_pPolygon = new VertexBuffer;
	hr = g_pPolygon->Create(vtx, 4);
	if (FAILED(hr)) { return hr; }

	// �V�F�[�_�[�̓Ǎ�
	g_pVS = new VertexShader;
	hr = g_pVS->Load(GetDevice(), "PolygonVS.cso");
	if (FAILED(hr)) { return hr; }

	g_pAnimeVS = new VertexShader;
	hr = g_pAnimeVS->Load(GetDevice(), "AnimePolygonVS.cso");
	if (FAILED(hr)) { return hr; }

	g_pTransformVS = new VertexShader;
	hr = g_pTransformVS->Load(GetDevice(), "TransformVS.cso");
	if (FAILED(hr)) { return hr; }

	g_pPS = new PixelShader;
	hr = g_pPS->Load(GetDevice(), "PolygonPS.cso");
	if (FAILED(hr)) { return hr; }

	g_pNegaPosiPS = new PixelShader();
	hr = g_pNegaPosiPS->Load(GetDevice(),"NegaPosiPS.cso");
	if (FAILED(hr)){return hr;}

	//�萔�o�b�t�@�쐬
	g_pUVBuf = new ConstantBuffer;
	hr = g_pUVBuf->Create(sizeof(AnimeUV));
	if (FAILED(hr)) { return hr; }

	g_pTransformBuf = new ConstantBuffer;
	hr = g_pTransformBuf->Create(sizeof(Transform));
	if (FAILED(hr)) { return hr; }

	if (g_pBGM == nullptr)
	{
		//�T�E���h�̓ǂݍ���
		g_pBGM = CreateSound("Assets/�߂��݂ō炭��.mp3", true);
		if (g_pBGM == nullptr) { return E_FAIL; }

		pSource = StartSound(g_pBGM);
		pSource->SetVolume(0.6f);
	}
	if (g_pSE == nullptr)
	{
		g_pSE = CreateSound("Assets/�y���p���`.mp3", false);
		if (g_pSE == nullptr) { return E_FAIL; }
	}

	// �u�����h�X�e�[�g�쐬
	g_pBlendState = new BlendState(false);
	g_pAddBlend = new BlendState(true);
	//�T���v���[�X�e�[�g�쐬
	g_pSamplerState = new SamplerState;

	//������
		// �Q�[���̃I�u�W�F�N�g�쐬
	SpriteDesc desc;
	switch (sceneType)
	{
	case TITLESCENE:
		ZeroMemory(&desc, sizeof(SpriteDesc));
		desc.pVS = g_pTransformVS;
		desc.pPS = g_pPS;
		desc.pConst[0] = g_pTransformBuf;
		g_pTitle = new Title(desc);

		break;
	case GAMESCENE:

		ZeroMemory(&desc, sizeof(SpriteDesc));
		desc.pVS = g_pAnimeVS;
		desc.pPS = g_pPS;
		desc.pConst[0] = g_pUVBuf;
		desc.pConst[1] = g_pTransformBuf;
		g_pPlayer = new Player(desc);

		//�v���C���[�̂��ƂɃJ�����쐬
		g_pCamera = new Camera(g_pPlayer);

		ZeroMemory(&desc, sizeof(SpriteDesc));
		desc.pVS = g_pTransformVS;
		desc.pPS = g_pPS;
		desc.pConst[0] = g_pTransformBuf;
		g_BackGround = new BackGround(desc);

		CreateMap(IRUKAROOM,"Assets/Lifeicon.png");


		break;
	case CLEARSCENE:

		ZeroMemory(&desc, sizeof(SpriteDesc));
		desc.pVS = g_pTransformVS;
		desc.pPS = g_pPS;
		desc.pConst[0] = g_pTransformBuf;
		g_pClear = new Clear(desc);

		break;
	case GAMEOVERSCENE:

		ZeroMemory(&desc, sizeof(SpriteDesc));
		desc.pVS = g_pTransformVS;
		desc.pPS = g_pPS;
		desc.pConst[0] = g_pTransformBuf;
		g_pGameOver = new GameOver(desc);

		break;
	default:
		break;
	}

	return hr;
}


void UninitGame(void)
{
	switch (sceneType)
	{
	case TITLESCENE:
		delete g_pTitle;
		break;
	case GAMESCENE:
		delete g_BackGround;
		delete g_pCamera;
		delete g_pPlayer;

		break;
	case CLEARSCENE:
		delete g_pClear;
		break;
	case GAMEOVERSCENE:
		delete g_pGameOver;
		break;
	default:
		break;
	}

	delete g_pSamplerState;
	delete g_pAddBlend;
	delete g_pBlendState;
	delete g_pTransformBuf;
	delete g_pUVBuf;
	delete g_pNegaPosiPS;
	delete g_pPS;				//  �������m�ۂ̋t���Ń������J��
	delete g_pTransformVS;
	delete g_pAnimeVS;
	delete g_pVS;
	delete g_pPolygon;
}

void UpdateGame(void)
{
	fpscount++;
	if (fpscount == 100000)
	{
		fpscount = 0;
	}
	//�V�[����؂蕪���Ȃ���J��Ԃ��̏���
	switch (sceneType)
	{
	case TITLESCENE:	//�^�C�g���V�[��

		if (IsKeyTrigger(VK_RETURN))//ENTER�L�[�������ƃV�[����؂�ւ�
		{
			SceneChange(GAMESCENE);
		}
		g_pTitle->Update();

		break;
	case GAMESCENE:		//�Q�[���V�[��

		
		//g_pObject->Update();
		g_pPlayer->Update();

		g_BackGround->Update();

		//�\���}�b�v�̍X�V
		UpdateMap("Assets/Lifeicon.png", "Assets/white.png", "Assets/suisou.jpg");

		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (g_pWall[j][i])//�z�����null�ȊO�̎�
				{
					g_pWall[j][i]->Update();
				}
			}
		}
		//�ǂƃv���C���[�̓����蔻��
		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (g_pWall[j][i])//�z�����null�ȊO�̎�
				{
					Float2 Ppos = 
						CollisionBlock(g_pPlayer->GetTransform(), g_pPlayer->GetCollision(), g_pWall[j][i]->GetCollision(), g_pPlayer->GetOldtransform());
					g_pPlayer->SetObject(Ppos.x, Ppos.y);
				}
			}
		}

		g_pCamera->Update();

		break;
		
		case CLEARSCENE:	//�Q�[���N���A�V�[���i���U���g�V�[���j
			g_pClear->Update();
			if (IsKeyTrigger(VK_RETURN))//ENTER�L�[�������ƃV�[����؂�ւ�
			{
				SceneChange(TITLESCENE);
			}
			break;

		case GAMEOVERSCENE:		//�Q�[���I�[�o�[�V�[��
			g_pGameOver->Update();
			if (IsKeyTrigger(VK_RETURN))//ENTER�L�[�������ƃV�[����؂�ւ�
			{
				SceneChange(TITLESCENE);
			}
			break;

		default:
			break;
	};
}

void DrawGame(void)
{

	g_pPolygon->Draw();


	g_pBlendState->Bind();
	g_pSamplerState->Bind();

	g_pVS->Bind(GetContext());
	g_pPS->Bind(GetContext());

	switch (sceneType)
	{
	case TITLESCENE:	//�^�C�g���V�[��

		g_pTitle->Draw();

		break;
	case GAMESCENE:		//�Q�[���V�[��

		g_BackGround->Draw();

		g_pPlayer->Draw();
		
		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (g_pWall[j][i] != nullptr)
				{
					g_pWall[j][i]->Draw();
				}
			}
		}

		break;

	case CLEARSCENE:	//�Q�[���N���A�V�[���i���U���g�V�[���j

		g_pClear->Draw();

		break;

	case GAMEOVERSCENE:		//�Q�[���I�[�o�[�V�[��

		g_pGameOver->Draw();

		break;

	default:
		break;
	};

}

Camera * GetCamera()
{
	return g_pCamera;
}

void SceneChange(SCENETYPE nextscene)
{
	UninitGame();
	sceneType = nextscene;
	InitGame();
}

void CreateMap(ROOMID nextroom, const char* pAWalltex)
{
	
	//�O�̕����̕��N���A
	//map�z��̃N���A
	for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
	{
		for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
		{
			if (mapchip[j][i])//�C���J�����̔z�����0�ȊO�̎�
				mapchip[j][i] = NULL;
		}
	}
	nowroom = nextroom;
	//map�z��̍쐬
	switch (nowroom)
	{
	case IRUKAROOM:
		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (irukaroom_chip[j][i])//�C���J�����̔z�����0�ȊO�̎�
					mapchip[j][i] = irukaroom_chip[j][i];
			}
		}
		break;
	case ENTRANCE:
		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (entrance_chip[j][i])
					mapchip[j][i] = entrance_chip[j][i];
			}
		}
		break;
	case ROOMA:
		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (roomA_chip[j][i])
					mapchip[j][i] = roomA_chip[j][i];
			}
		}
		break;
	case ROOMB:
		for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
		{
			for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
			{
				if (roomB_chip[j][i])
					mapchip[j][i] = roomB_chip[j][i];
			}
		}
		break;
	default:
		break;
	}

	
}

void UpdateMap(const char * pAWalltex,const char* pBWalltex, const char* psuisoutex)
{
	float PposX = g_pPlayer->GetTransform().posX;
	float PposY = g_pPlayer->GetTransform().posY;


	for (int j = 0; j < (MAP_HIGHT / PANEL_HIGHT); j++)
	{
		for (int i = 0; i < (MAP_WIDE / PANEL_WIDE); i++)
		{
			//Pos�z��Ƀu���b�N�̍��W����
			
			mapchipPos[j][i].x = PANEL_WIDE * i ;
			mapchipPos[j][i].y = PANEL_HIGHT * j;

			if (mapchipPos[j][i].x <= (PposX + 520) && mapchipPos[j][i].x >= (PposX - 520)
				&& mapchipPos[j][i].y <= 540 && mapchipPos[j][i].y >= 0
				&& mapchip[j][i] > 0)
			{
				
				if (g_pWall[j][i] == nullptr)
				{
					SpriteDesc desc;
					ZeroMemory(&desc, sizeof(SpriteDesc));
					desc.pVS = g_pAnimeVS;
					desc.pPS = g_pPS;
					desc.pConst[0] = g_pUVBuf;
					desc.pConst[1] = g_pTransformBuf;

					switch (mapchip[j][i])
					{
					case ��:
						desc.pTexture = pAWalltex;
						g_pWall[j][i] = new CWall(desc,1,1,1);
						g_pWall[j][i]->SetObject(mapchipPos[j][i].x, mapchipPos[j][i].y);
						break;
					case ��:
						desc.pTexture = pBWalltex;
						g_pWall[j][i] = new CWall(desc,1,1,1);
						g_pWall[j][i]->SetObject(mapchipPos[j][i].x, mapchipPos[j][i].y);
						break;
					case �C://����
						desc.pTexture = psuisoutex;
						g_pWall[j][i] = new CWall(desc, 3, 3 ,0);
						g_pWall[j][i]->SetObject(mapchipPos[j][i].x, mapchipPos[j][i].y);
						break;
					case 4:
						break;
					case 5:
						break;
					case 6:
						break;
					case 7:
						break;
					case 8:
						break;
					case 9:
						break;
					case 10:
						break;
					case 11:
						break;
					
					default:
						break;
					}
				}
			}
			else
			{
				if (g_pWall[j][i] != nullptr)
				{
					delete g_pWall[j][i];
					g_pWall[j][i] = nullptr;
				}
			}

		}
	}
}

//�^�[�Q�b�g�ɓ����������ɒ��˕Ԃ��ꂽ���̍��W��Ԃ�
Float2 CollisionBlock(Transform trans, CollisionData col, CollisionData targetcol,Transform oldpos)
{
	Float2 topos;
	//�[
	float Rightside =	col.x + (col.Width / 2);
	float Leftside	=	col.x - (col.Width / 2);
	float Upside	=	col.y - (col.Height / 2);
	float Downside	=	col.y + (col.Height / 2);

	float TRightside	= targetcol.x + (targetcol.Width / 2);
	float TLeftside		= targetcol.x - (targetcol.Width / 2);
	float TUpside		= targetcol.y - (targetcol.Height / 2);
	float TDownside		= targetcol.y + (targetcol.Height / 2);

	if ((Rightside > TLeftside) && (Leftside < TRightside) && (Upside < TDownside) && (Downside > TUpside))	//������
	{

		topos.x = oldpos.posX;
		topos.y = oldpos.posY;
	}
	else
	{
		topos.x = trans.posX;
		topos.y = trans.posY;
	}
	return topos;
}
