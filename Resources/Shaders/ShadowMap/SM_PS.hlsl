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
        // ���K���f�o�C�X���W�ɂ���(-1����1�ɐ��K��)
        pin.LightPosPS.xyz /= pin.LightPosPS.w;

        // �V���h�E�}�b�v��UV�l�����߂�
        float2 uv = pin.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

        // �V���h�E�}�b�v�̐[�x�l�ƃ��C�g��Ԃ̃s�N�Z����Z�l���r���ĉe�ɂȂ邩���ׂ�
        float percentLit = tex.SampleCmpLevelZero(samplerState, uv, pin.LightPosPS.z - SHADOW_EPSILON).x;

        // �s�N�Z���̖@���𐳋K��
        float3 worldNormal = normalize(pin.NormalWS);

        // ���̋�������ς���Z�o����
        float3 dotL = saturate(dot(-lightDir, worldNormal));

        // ���C�g�ɂ�閾�邳�����߂�
        float3 lightAmount = dotL * percentLit * (1.0f - LightAmbient) + LightAmbient;

        // �f�B�t���[�Y�F�����߂�
        diffuse = float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a);

        // �����x�N�g��
        float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);

        // �n�[�t�x�N�g��
        float3 halfVector = normalize(eyeVector - lightDir);

        // �X�y�L�����̉e����������ς��g�����߂�
        float dotH = saturate(dot(halfVector, worldNormal));

        // �X�y�L�����p���[���w���Ƃ��Ďg���n�C���C�g�̂������𒲐�
        specular = pow(dotH, SpecularPower) * dotL * SpecularColor * percentLit;
    }
    else
    {
        // �X�|�b�g���C�g�̊O
        diffuse = float4(LightAmbient, 1.0f) * DiffuseColor;
    }

    // �e�N�X�`���F�ƃf�B�t���[�Y�F���|����
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;

    // �X�y�L������������
    color.rgb += specular * diffuse.a;

    return color;
}

