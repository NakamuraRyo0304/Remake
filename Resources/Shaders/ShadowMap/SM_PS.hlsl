/*
 *	@File	SM_PS.hlsl
 *	@Brief	�V���h�E�}�b�v�̃s�N�Z���V�F�[�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "SM_Common.hlsli"

Texture2D tex : register(t1); // �V���h�E�}�b�v�e�N�X�`��
SamplerComparisonState samplerState : register(s1); // �V���h�E�}�b�v�T���v���[

struct Input
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 LightPosPS : TEXCOORD3;
};

// �}�b�n�o���h�΍�
#define SHADOW_EPSILON 0.00015f
// ���C�g�̉e���x���v�Z
float calcPercent(float3 lightDir, float4 lightPosPS)
{
    // �X�|�b�g���C�g�͈͓̔��Ȃ�e�̉e����^����
    if (dot(lightDir, LightDir) > fCosTheta)
    {
        // ���K���f�o�C�X���W�ɕϊ�
        float3 normalPos = lightPosPS.xyz / lightPosPS.w;
        float2 uv = normalPos.xy * float2(0.5f, -0.5f) + 0.5f;

        // �V���h�E�}�b�v���T���v�����O���ĉe�̉e���x���擾
        return tex.SampleCmpLevelZero(samplerState, uv, normalPos.z - SHADOW_EPSILON).x;
    }
    else
    {
        return 0.0f; // �X�|�b�g���C�g�͈̔͊O�ł͉e���x��0
    }
}

// �X�y�L�������v�Z
float3 calcSpecular(float3 position, float3 worldNormal, float3 lightDir, float3 dotLight, float percent)
{
    float3 eyeVector = normalize(EyePosition - position);
    float3 eyeVectorNormal = normalize(eyeVector - lightDir);
    float dotHalfVector = saturate(dot(eyeVectorNormal, worldNormal));

    return pow(dotHalfVector, SpecularPower) * dotLight * SpecularColor * percent;
}

// �f�B�t���[�Y���v�Z
float4 calcDiffuse(float3 dotLight, float percent)
{
    // �s�N�Z���̖@���𐳋K��
    float3 lightAmount = dotLight * percent * (1.0f - LightAmbient) + LightAmbient;

    // �X�|�b�g���C�g�͈̔͊O�ł̓A���r�G���g���C�g�݂̂��g��
    float4 diffuse = lerp(
        float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a),
        float4(LightAmbient, 1.0f) * DiffuseColor,
        step(percent, 0.0f)
    );

    return diffuse;
}

float4 main(Input pin) : SV_TARGET0
{
    // ���C�g�̌������Z�o
    float3 lightDir = normalize(pin.PositionWS.xyz - LightPos.xyz);

    // �e���x�����v�Z
    float percent = calcPercent(lightDir, pin.LightPosPS);

    // �s�N�Z���̖@���𐳋K��
    float3 worldNormal = normalize(pin.NormalWS);

    // ���̋�������f�B�t���[�Y�F���v�Z
    float3 dotLight = saturate(dot(-lightDir, worldNormal));

    // �f�B�t���[�Y���v�Z
    float4 diffuse = calcDiffuse(dotLight, percent);

    // �X�y�L�������v�Z
    float3 specular = calcSpecular(pin.PositionWS.xyz, worldNormal, lightDir, dotLight, percent);

    // �v�Z���ʂ���Z
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;
    color.rgb += specular * diffuse.a;

    // �ŏI�o��
    return color;
}
