struct VS_IN {
	float3 pos:POSITION0;
	float2 uv:TEXCOORD0;
};

struct VS_OUT {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};

cbuffer Transform:register(b0)
{
	float posX, posY;
	float scaleX, scaleY;
	float angle;
	float dummy[3];
}

VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.uv = vin.uv;

	vout.pos = float4(vin.pos, 1.0f);

	vout.pos.x *= scaleX;
	vout.pos.y *= scaleY;
	float4 work = vout.pos;
	vout.pos.x = work.x*cos(angle) - work.y*sin(angle);
	vout.pos.y = work.x*sin(angle) + work.y*cos(angle);
	vout.pos.x += posX;
	vout.pos.y += posY;

	vout.pos.x /= 480.0f;
	vout.pos.y /= 270.0f;

	vout.pos.y *= -1.0f;

	vout.pos.x -= 1.0f;
	vout.pos.y += 1.0f;

	return vout;
}