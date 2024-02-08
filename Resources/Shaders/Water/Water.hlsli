/*
 *	@File	Water.hlsli
 *	@Brief	���ʃV�F�[�_�[�̃w�b�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

// �p�ɂɍX�V��������
cbuffer ConstBuffer	: register(b0)
{
	matrix matWorld;
	matrix matView;
	matrix matProj;
    float Time;
    float3 pad;
};

// �ɋH�ɍX�V��������
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