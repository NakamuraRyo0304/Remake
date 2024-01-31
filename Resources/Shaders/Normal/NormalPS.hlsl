/*
 *	@File	NormalPS.hlsl
 *	@Brief	ピクセルシェーダー
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "Normal.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	float4 output = tex.Sample(samLinear, input.Tex);
	return output * input.Color;
}