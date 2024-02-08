/*
 *	@File	Water.hlsli
 *	@Brief	水面シェーダーのヘッダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

// 頻繁に更新されるもの
cbuffer ConstBuffer	: register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
    float Time;
    float3 pad;
};

// 極稀に更新されるもの
cbuffer WaterConst : register(b1)
{
    float ScaleW;
    float3 padw;
};


struct VS_INPUT
{
	float3 Pos : POSITION;
	float4 Color: COLOR;
	float2 Tex : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color: COLOR;
	float2 Tex : TEXCOORD;
};