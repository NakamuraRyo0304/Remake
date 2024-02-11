/*
 *	@File	SM_PS.hlsl
 *	@Brief	�V���h�E�}�b�v�̃s�N�Z���V�F�[�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "SM_Common.hlsli"

// �V���h�E�}�b�v�e�N�X�`��
Texture2D tex : register(t1);

// �V���h�E�}�b�v�p�e�N�X�`���T���v���[
SamplerComparisonState samplerState : register(s1);

struct Input
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
};

// �}�b�n�o���h�΍�
#define SHADOW_EPSILON 0.00015f

float4 main(Input pin) : SV_TARGET0
{
    // �f�B�t���[�Y�E�X�؃L����
    float4 diffuse = float4(0, 0, 0, 0);
    float3 specular = 0;

    // ���C�g�̌��������߂�
    float3 lightDir = normalize(pin.PositionWS.xyz - LightPos.xyz);

    // �X�|�b�g���C�g�͈͓̔��Ȃ烉�C�g�̉e����^���ĉe������
    if (dot(lightDir, LightDir) > fCosTheta)
    {
        // ���K���f�o�C�X���W�ɂ���UV���v�Z
        pin.LightPosPS.xyz /= pin.LightPosPS.w;
        float2 uv = pin.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

        // �[�x�l�ƃ��C�g��Ԃ̃s�N�Z����Z�l���r���ĉe�ɂȂ�ꏊ���v�Z
        float percentLit = tex.SampleCmpLevelZero(samplerState, uv, pin.LightPosPS.z - SHADOW_EPSILON).x;

        // �s�N�Z���̖@���𐳋K��
        float3 worldNormal = normalize(pin.NormalWS);

        // ���̋�������f�B�t���[�Y�F���v�Z
        float3 dotL = saturate(dot(-lightDir, worldNormal));
        float3 lightAmount = dotL * percentLit * (1.0f - LightAmbient) + LightAmbient;
        diffuse = float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a);

        // �x�N�g������X�؃L�����̂��������v�Z
        float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
        float3 eVecNormal = normalize(eyeVector - lightDir);
        float dotH = saturate(dot(eVecNormal, worldNormal));
        specular = pow(dotH, SpecularPower) * dotL * SpecularColor * percentLit;
    }
    else
    {
        diffuse = float4(LightAmbient, 1.0f) * DiffuseColor;
    }

    // �e�N�X�`���F�ƃf�B�t���[�Y�F�E�X�؃L��������Z
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;
    color.rgb += specular * diffuse.a;

    // �o�͂���
    return color;
}

