/*
 *	@File	Normal.hlsl
 *	@Brief	そのまま出力する
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

// コンスタントバッファ
cbuffer ConstBuffer	: register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
	float4 Move;
};

// 頂点シェーダーのインプット
struct VS_INPUT
{
	float3 Pos : POSITION;
	float4 Color: COLOR;
	float2 Tex : TEXCOORD;
};

// ピクセルシェーダーのインプット
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color: COLOR;
	float2 Tex : TEXCOORD;
};