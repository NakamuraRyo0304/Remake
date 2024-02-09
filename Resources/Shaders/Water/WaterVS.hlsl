/*
 *	@File	WaterVS.hlsl
 *	@Brief	���ʂ̒��_�V�F�[�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

#define WAVE_AMPLITUDE 1.5f          // �g�̍���
#define WAVE_SPEED 0.05f             // �g�̑��x

// �����_���֐�
float rand(in float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // ���Ԃ��g���Ĕg�̓������쐬
    // ���_�� x ���W�Ɋ�Â��āA�e���_���ƂɈقȂ�g�̐U�镑����K�p
    float waveHeight = sin(input.Pos.x * WAVE_SPEED + Time) * WAVE_AMPLITUDE;

    // ���_���ɈقȂ郉���_���Ȕg�̍����𐶐�
    float randomOffset = rand(input.Pos.xy) * WAVE_AMPLITUDE + 1.0f;

    // �g�̍����𒸓_���W�ɉ��Z
    output.Pos = float4(input.Pos.x, input.Pos.y + waveHeight + randomOffset, input.Pos.z, 1.0);

    output.Color = input.Color;
    output.Tex = input.Tex;

    return output;
}