/*
 *	@File	WaterPS.hlsl
 *	@Brief	���ʂ̃s�N�Z���V�F�[�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

#define FLOW_VELOCITY 0.1f      // ������
#define SWING_SPEED 0.01f       // ���E�ɐU����
#define FN_UV_PATH1 0.05f       // �t���N�^���m�C�Y�̌��ʂɏ�Z����l
#define FN_UV_PATH2 0.06f       // �t���N�^���m�C�Y�̌��ʂɏ�Z����l
#define FN_UV_POWER 25          // uv�̃T�C�Y
#define FN_OCTAVES 10.0f        // �I�N�^�[�u
#define FN_PERSISTENCE 0.6f     // �����x
#define RANDOM_OFFSET 0.01f     // �����_���I�t�Z�b�g

// �񎟌������𐶐�����
float2 random(float2 st)
{
    st = float2(dot(st, float2(127.1f, 311.7f)),
                dot(st, float2(269.5f, 183.3f)));

    return -1.0f + 2.0f * frac(sin(st) * 43758.5453f);
}

// �p�[�����m�C�Y
float perlinNoise(float2 uv)
{
    float2 p = floor(uv);
    float2 f = frac(uv);
    float2 u = f * f * (3.0 - 2.0 * f);

    float2 v00 = random(p + float2(0, 0));
    float2 v10 = random(p + float2(1, 0));
    float2 v01 = random(p + float2(0, 1));
    float2 v11 = random(p + float2(1, 1));

    return lerp(lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
         lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x), u.y);
}

// �t���N�^���m�C�Y�𐶐�����֐�
float fractalNoise(float2 uv)
{
    float noise = 0.0;
    float amplitude = 1.0;
    float frequency = 1.0;

    // �����̃I�N�^�[�u�Ńm�C�Y�𐶐����A��������
    for (float i = 0; i < FN_OCTAVES; ++i)
    {
        noise += perlinNoise(uv * frequency) * amplitude;
        amplitude *= FN_PERSISTENCE;
        frequency *= 2.0; // ���g����{�ɂ��邱�ƂŎ��̃I�N�^�[�u�Ɉڂ�
    }

    return noise;
}

// �����_���ȃI�t�Z�b�g�𐶐�����
float2 randomOffset(float2 uv)
{
    float2 randomOffset = float2(
        frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453),
        frac(cos(dot(uv, float2(12.9898, 78.233))) * 43758.5453));
    return randomOffset * RANDOM_OFFSET;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.Tex;

    // �����_���ȃI�t�Z�b�g�𐶐�
    float2 offset = perlinNoise(uv);

    // UV�l�ɃI�t�Z�b�g��������
    uv += offset;

    // �t���N�^���m�C�Y�ŗh�炷
    float p = fractalNoise(uv * FN_UV_POWER);

    // UV�l��s�K���ɗh�炷
    uv += float2(p * FN_UV_PATH1 * cos(Time), p * FN_UV_PATH2 * sin(Time));

    // UVX�l�����Ԃɉ����Ċ��炩�Ɉړ�������
    uv.x += Time * FLOW_VELOCITY;

    // UVY�l�����E�ɐU��
    uv.y += cos(Time) * SWING_SPEED;

    // �o�͂���
    return tex.Sample(samLinear, uv);
}