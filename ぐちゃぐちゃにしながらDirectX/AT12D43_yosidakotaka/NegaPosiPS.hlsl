struct PS_IN
{
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};

Texture2D tex:register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = tex.Sample(samp,pin.uv);
	//float4にはrgbaの4つのメンバ変数がある
	//ネガポジ反転は1-色で計算できる
	color.r = 1.0f - color.r;
	color.g = 1.0f - color.g;
	color.b = 1.0f - color.b;

	return color;
}
