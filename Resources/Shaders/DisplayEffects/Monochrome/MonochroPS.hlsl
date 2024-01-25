/*
 *	@File	MonochroPS.hlsl
 *	@Brief	���m�N���i�s�N�Z���V�F�[�_�[�j
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

// �O���[�X�P�[��
float gray(float4 col)
{
    return col.r * 0.3f + col.r * 0.6f + col.r * 0.1f;
}

// �s�N�Z���V�F�[�_�[�̃��C���֐�
float4 main(PS_INPUT input) : SV_TARGET
{
    float g = gray(tex.Sample(samLinear, input.Tex));
    return float4(g, g, g, 1.0f);
}