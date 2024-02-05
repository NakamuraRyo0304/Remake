Texture2D<float4> Texture   : register(t0);
sampler Sampler             : register(s0);

// DirectXTK�ɓ����Ă���p�����[�^
cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);
    float3 EmissiveColor            : packoffset(c1);
    float3 SpecularColor            : packoffset(c2);
    float SpecularPower             : packoffset(c2.w);

    float3 LightDirection[3]        : packoffset(c3);
    float3 LightDiffuseColor[3]     : packoffset(c6);
    float3 LightSpecularColor[3]    : packoffset(c9);

    float3 EyePosition              : packoffset(c12);

    float3 FogColor                 : packoffset(c13);
    float4 FogVector                : packoffset(c14);

    float4x4 World                  : packoffset(c15);
    float3x3 WorldInverseTranspose  : packoffset(c19);
    float4x4 WorldViewProj          : packoffset(c22);
};

// �e�Ɏg���p�����[�^
cbuffer Parameters : register(b1)
{
    float4x4 LightViewProj  : packoffset(c0);
    float4 LightPos         : packoffset(c4);
    float3 LightDir         : packoffset(c5);
    float3 LightAmbient     : packoffset(c6);
};

// ���C�g�͈̔͂����߂�p�����[�^
cbuffer Parameters : register(b2)
{
    float fCosTheta : packoffset(c0);
};
