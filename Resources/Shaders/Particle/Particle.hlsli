/*
 *	@File	Particle.hlsl
 *	@Brief	パーティクル
 *	@Date	2023-01-21
 *  @Author NakamuraRyo
 */

// コンスタントバッファ
cbuffer ConstBuffer	: register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
	float4 Timer;
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