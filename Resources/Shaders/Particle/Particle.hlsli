/*
 *	@File	Particle.hlsl
 *	@Brief	�p�[�e�B�N��
 *	@Date	2023-01-21
 *  @Author NakamuraRyo
 */

// �R���X�^���g�o�b�t�@
cbuffer ConstBuffer	: register(b0)
{
	matrix World;
	matrix View;
	matrix Proj;
	float4 Timer;
};

// ���_�V�F�[�_�[�̃C���v�b�g
struct VS_INPUT
{
	float3 Pos : POSITION;
	float4 Color: COLOR;
	float2 Tex : TEXCOORD;
};

// �s�N�Z���V�F�[�_�[�̃C���v�b�g
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float4 Color: COLOR;
	float2 Tex : TEXCOORD;
};