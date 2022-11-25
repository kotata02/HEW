#include "Player.h"
#include"Keyboard.h"
#include"Game.h"

const float LIMIT_TOP = 0.0f;
const float LIMIT_BOTTOM = 540.0f;
const float LIMIT_LEFT = 0.0f;
const float LIMIT_RIGHT = 2010.0f;



Player::Player(SpriteDesc desc)
	:m_frame(0),m_sinFrame(0)
{
	HRESULT hr;
	Vertex vtx[] = 
	{
		{ {-30.0f, -30.0f, 0.0f}, { 0.0f,0.0f }},
		{ {30.0f, -30.0f, 0.0f}, { 1.0f,0.0f }},
		{ {-30.0f, 30.0f, 0.0f}, { 0.0f,1.0f }},
		{ {30.0f, 30.0f, 0.0f}, { 1.0f,1.0f }}
	};
	
	// �A�j���[�V������UV��ύX���邽�߂̃f�[�^

	m_uv.uvWidth = 1.0f / 4; // ��4�����̉摜
	m_uv.uvHeight = 1.0f / 3; // �c3�����̉摜
	m_uv.uvTopLeftX = 0.25f;
	m_uv.uvTopLeftY = 0;

	//�ړ���]�g�k
	m_transform.posX = 0.0f;
	m_transform.posY = 0.0f;
	m_transform.scaleX=1.0f;
	m_transform.scaleY=1.0f;
	m_transform.angle = 0.0f;
	
	m_vector = 1;

	//�X�v���C�g�̍쐬
	desc.pVtx = vtx;
	desc.pTexture = "Assets/bbb.png";

	m_pSprite = new Sprite(desc);

	m_transform.posX = 500.0f;
	m_transform.posY = 270.0f;
}

Player::~Player()
{
	delete m_pSprite;
}

void Player::Update()
{
	if (m_frame >= 10 && m_move ==true)
	{
		// �L�����N�^�[�̃A�j���[�V������
	// UV��ω������Ă���

		if (m_vector)//�E����
		{
			m_uv.uvTopLeftY = 0;
			m_uv.uvTopLeftX -= m_uv.uvWidth;
			if (m_uv.uvTopLeftX <= 0.0f)
			{
				m_uv.uvTopLeftX = 0.75f;
			}
		}
		else//������
		{
			m_uv.uvTopLeftY = 0.333f;
			m_uv.uvTopLeftX += m_uv.uvWidth;
			if (m_uv.uvTopLeftX >= 1.0f)
			{
				m_uv.uvTopLeftX = 0.25f;
			}

		//	// ���̃t���[���𐔂��邽�߂�
		}
		m_frame = 0;
	}
	
	m_frame++;
	
	const float MOVE_SPEED_X = 2.0f;
	//const float MOVE_SPEED_XY = 0.05f;
	const float MOVE_SPEED_Y = 2.0f;

	/*if (IsKeyPress(VK_LEFT)) { m_transform.posX -= MOVE_SPEED_X; }
	if(IsKeyPress(VK_RIGHT)){ m_transform.posX += MOVE_SPEED_X; }
	if (IsKeyPress(VK_UP)) { m_transform.posX += MOVE_SPEED_XY; m_transform.posY -= MOVE_SPEED_Y; }
	if (IsKeyPress(VK_DOWN)) { m_transform.posX -= MOVE_SPEED_XY; m_transform.posY += MOVE_SPEED_Y;}
	if (m_transform.posX < LIMIT_LEFT) { m_transform.posX = LIMIT_LEFT; }
	if (m_transform.posX > LIMIT_RIGHT) { m_transform.posX = LIMIT_RIGHT; }
	if (m_transform.posY < LIMIT_TOP) { m_transform.posY = LIMIT_TOP; }
	if (m_transform.posY > LIMIT_BOTTOM) { m_transform.posY = LIMIT_BOTTOM; }
	float scale = (m_transform.posY - LIMIT_TOP) / (LIMIT_BOTTOM - LIMIT_TOP)*0.2f + 0.9f;
	m_transform.scaleX = scale;
	m_transform.scaleY = scale;
*/
	//if (�_���[�W��static�ɂ��Ă����ł�������悤�ɂ���)
	//{
	//	m_move = false;
	//	m_uv.uvTopLeftX = 0.5f;
	//	m_transform.posX - 20.0f;
	//}
	//else
	//{

	m_oldtransform = m_transform;

		if (IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT) || IsKeyPress(VK_UP) || IsKeyPress(VK_DOWN))
		{
			if (IsKeyPress(VK_RIGHT))
			{
				m_transform.posX += MOVE_SPEED_X;
				m_move = true;
				m_vector = true;
			}
			
			if (IsKeyPress(VK_LEFT))
			{
				m_transform.posX -= MOVE_SPEED_X;
				m_move = true;
				m_vector = false;
			}
			
			if (IsKeyPress(VK_UP))
			{
				m_transform.posY -= MOVE_SPEED_Y; m_move = true;
			}
			
			if (IsKeyPress(VK_DOWN))
			{
				m_transform.posY += MOVE_SPEED_Y; m_move = true;
			}
			if (m_transform.posX < LIMIT_LEFT) { m_transform.posX = LIMIT_LEFT; }
			if (m_transform.posX > LIMIT_RIGHT) { m_transform.posX = LIMIT_RIGHT; }
			if (m_transform.posY < LIMIT_TOP) { m_transform.posY = LIMIT_TOP; }
			if (m_transform.posY > LIMIT_BOTTOM) { m_transform.posY = LIMIT_BOTTOM; }
		}
		else
		{
			m_move = false;
			m_uv.uvTopLeftX = 0.5f;
		}

		//�����蔻��̑傫�������߂�
		m_collision.x = m_transform.posX-10;
		m_collision.y = m_transform.posY-10;
		m_collision.Width = 22;
		m_collision.Height = 28;
	//}
	//�J�[�\���̓���
	//m_transform.posX=sinf(m_sinFrame*360.0f/60*3.14f/180)*10.0f+0;

	//�h�����
	/*
	m_transform.angle = sin(m_sinFrame*360.0f/100*3.14f/180)*10.0f*3.14/180;*/

	//��̃A�j���[�V����
	/*float rad = m_sinFrame * 360.0f / 120 * 3.14f / 180;
	m_transform.scaleX = (sin(rad)*0.5f + 0.5f)*0.4f + 0.8f;
	m_transform.scaleY = (sin(rad + 3.14f)*0.5f + 0.5f)*0.4f + 0.8f;*/
	

	/*m_transform.posX -= 1.1f;
	if (m_transform.posX <= 0)
		m_transform.posX = 980;*/

	m_sinFrame++;
}

void Player::Draw()
{
	//�J�����̈ʒu�����ɁA��ʓ��Ɏ��܂�悤��
	//�����߂�
	//�萔�o�b�t�@�X�V

		Transform transform = m_transform;
		transform.posX -= GetCamera()->GetPosX();
		m_pSprite->Write(&m_uv, 0);
		m_pSprite->Write(&transform, 1);
	m_pSprite->Draw();


}

bool Player::GetVector()
{
	return m_vector;
}

void Player::SetObject(float x, float y)
{
	m_transform.posX = x;
	m_transform.posY = y;
}

Transform Player::GetTransform()
{
	return m_transform;
}

Transform Player::GetOldtransform()
{
	return m_oldtransform;
}

CollisionData Player::GetCollision()
{
	return m_collision;
}