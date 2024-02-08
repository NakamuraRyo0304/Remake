/*
 *	@File	SM_VS_Depth.hlsl
 *	@Brief	�V���h�E�}�b�v�̒��_�f�v�X�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "SM_Common.hlsli"

struct Input
{
    float4 Position     : SV_Position;
    float3 Normal       : NORMAL;
    float2 TexCoord     : TEXCOORD0;
    float4 Color        : COLOR;
};

struct Output
{
    float4 PositionPS : SV_Position;
};

Output main(Input vin)
{
    Output output;

    // ���_�̈ʒu�𓊉e��Ԃ�
    output.PositionPS = mul(vin.Position, WorldViewProj);

    return output;
}

