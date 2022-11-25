struct VS_IN {
	float3 pos:POSITION0;
	float2 uv:TEXCOORD0;
};

struct VS_OUT {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};

VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	
	vout.uv = vin.uv;

	vout.pos = float4(vin.pos, 1.0f);
	
	vout.pos.x /= 480.0f;
	vout.pos.y /= 270.0f;

	vout.pos.y *= -1.0f;

	vout.pos.x -= 1.0f;
	vout.pos.y += 1.0f;
	
	return vout;
}