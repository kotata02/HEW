#ifndef _Sprite_H_
#define _Sprite_H_
#include"VertexBuffer.h"
#include"Shader.h"
#include"ConstantBuffer.h"

struct AnimeUV
{
	float uvWidth;		//分割後の横幅
	float uvHeight;		//分割後の縦幅
	float uvTopLeftX;	//左上のX座標
	float uvTopLeftY;	//左上のY座標
};

struct Transform
{
	float posX, posY;		//ポリゴンの位置
	float scaleX, scaleY;	//ポリゴンの大きさ
	float angle;			//ポリゴンの（回転時計回りが＋）
	float dummy[3];			//16バイトで区切れるように数合わせ
};
struct CollisionData	//当たり判定のデータ
{
	float x;				//中心座標X
	float y;				//中心座標Y
	float Width;			//横幅
	float Height;			//縦幅
	float kyori;			//距離
};

//当たり判定用データ
struct Collisiondata
{
	float posX, posY;		//当たり判定の位置
	float scaleX, scaleY;	//当たり判定の大きさ
};

//ポリゴンクラスを作成するための情報
struct SpriteDesc
{
	Vertex* pVtx;
	const char* pTexture;
	VertexShader* pVS;
	PixelShader* pPS;
	ConstantBuffer* pConst[4];
};

class Sprite
{
public:
	Sprite(SpriteDesc desc);
	~Sprite();

	void Write(void* pData, int slot);
	void Draw();
private:
	VertexBuffer* m_pVtxBuf;
	ID3D11ShaderResourceView* m_pTexture;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
	ConstantBuffer* m_pConstantBuf[4];
};

#endif // _Sprite_H_

