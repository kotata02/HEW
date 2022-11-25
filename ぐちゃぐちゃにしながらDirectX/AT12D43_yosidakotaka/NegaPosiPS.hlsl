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
	//float4�ɂ�rgba��4�̃����o�ϐ�������
	//�l�K�|�W���]��1-�F�Ōv�Z�ł���
	color.r = 1.0f - color.r;
	color.g = 1.0f - color.g;
	color.b = 1.0f - color.b;

	return color;
}
