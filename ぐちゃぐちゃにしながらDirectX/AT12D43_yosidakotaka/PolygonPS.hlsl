//float4 main() : SV_TARGET
//{
//	return float4(1.0f, 1.0f, 1.0f, 1.0f);
//}
//���_�V�F�[�_�[���瑗����f�[�^
//��SV_POSITION�͎g���Ȃ����A�蒅���Ȃ���
//�f�[�^�̎󂯎�肪���܂������Ȃ�
struct PS_IN {
	float4 pos:SV_POSITION;
	float2 uv:TEXCOORD0;
};

//�s�N�Z���V�F�[�_�[�Ńe�N�X�`���f�[�^������
Texture2D tex:register(t0);
SamplerState samp : register(s0);

//�s�N�Z���V�F�[�_�[�ŐF�̌v�Z
//�߂�l���\�������F
float4 main(PS_IN pin) :SV_TARGET{
	//return float4(1.0f,1.0f,1.0f,1.0f);
	return tex.Sample(samp,pin.uv);
}