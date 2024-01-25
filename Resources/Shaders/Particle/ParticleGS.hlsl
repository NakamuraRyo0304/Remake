/*
 *	@File	ParticleGS.hlsl
 *	@Brief	パーティクルのジオメトリシェーダー
 *	@Date	2023-01-21
 *  @Author NakamuraRyo
 */

#include "Particle.hlsli"

static const int VNUM = 4;

static const float4 offset_array[VNUM] =
{
	float4(-0.5f,  0.5f, 0.0f, 0.0f),	// 左上
	float4( 0.5f,  0.5f, 0.0f, 0.0f),	// 右上
	float4(-0.5f, -0.5f, 0.0f, 0.0f),	// 左下
	float4( 0.5f, -0.5f, 0.0f, 0.0f),	// 右下
};

[maxvertexcount(VNUM)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
	for (int i = 0; i < VNUM; i++)
	{
		PS_INPUT element;

		float4 res = offset_array[i];

		element.Pos =input[0].Pos + mul(offset_array[i]* input[0].Tex.x, World);

		element.Pos = mul(element.Pos, View);
		element.Pos = mul(element.Pos, Proj);

		element.Color = input[0].Color;
		element.Tex.x =  offset_array[i].x + 0.5f;
		element.Tex.y = -offset_array[i].y + 0.5f;


		output.Append(element);
	}
	output.RestartStrip();
}