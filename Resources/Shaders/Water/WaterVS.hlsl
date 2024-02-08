/*
 *	@File	WaterVS.hlsl
 *	@Brief	水面の頂点シェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = float4(input.Pos,1);

	output.Color = input.Color;
	output.Tex = input.Tex;
	return output;
}