/*
 *	@File	ParticleVS.hlsl
 *	@Brief	�p�[�e�B�N���̃o�[�e�b�N�X�V�F�[�_�[
 *	@Date	2023-01-21
 *  @Author NakamuraRyo
 */

#include "Particle.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.Tex);
	return output * input.Color;
}