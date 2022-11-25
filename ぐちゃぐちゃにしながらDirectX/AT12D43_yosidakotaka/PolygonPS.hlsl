//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}
//頂点シェーダーから送られるデータ
//※SV_POSITIONは使えないが、定着しないと
//データの受け取りがうまくいかない
struct PS_IN {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};

//ピクセルシェーダーでテクスチャデータを扱う
Texture2D tex:register(t0);
SamplerState samp : register(s0);

//ピクセルシェーダーで色の計算
//戻り値が表示される色
float4 main(PS_IN pin) :SV_TARGET{
	//return float4(1.0f,1.0f,1.0f,1.0f);
	return tex.Sample(samp,pin.uv);
}