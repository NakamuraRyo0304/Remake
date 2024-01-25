/*
 *	@File	BrownPS.hlsl
 *	@Brief	�u���E���ǃe���r(�s�N�Z���V�F�[�_�[)�B
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

#define LINE_COLORS 123.0f      // �J���[�̐�
#define LINE_POWER 7.0f         // ���C���m�C�Y�̋���
#define LINE_SPAN 0.001f        // ���C���̏o���Ԋu
#define VIGNETTE_WIDTH 1.2f     // �r�l�b�g�̕�(��ʂ̖��邳)
#define FRAME_DISTANCE  0.525f  // �g�̑傫��
#define FLICKERING 100          // ���ׂ̍���
#define SHIMMELING 0.0025f      // �h�炬�̑傫��
#define BLOCK_SIZE 25           // �h�炬�u���b�N�̑傫��

// �񎟌������𐶐�����
float random(float2 st)
{
    return frac(sin(dot(st, float2(12.9898, 78.233))) * 43758.5453);
}

// �O���[�X�P�[��
float gray(float4 col)
{
    return col.r * 0.3f + col.r * 0.6f + col.r * 0.1f;
}

// �Z�s�A
float4 sepia(float4 col)
{
    float g = gray(col);
    return float4(g * 1.44f, g * 0.99f, g * 0.57f, col.a);
}

// �J���[�m�C�Y
float3 colorNoise(float3 col, float2 texUV)
{
    float3 newCol = col;
    newCol.r = tex.Sample(samLinear, texUV).r;
    newCol.g = tex.Sample(samLinear, texUV + float2(0.002f, 0.0f)).g;
    newCol.b = tex.Sample(samLinear, texUV + float2(0.004f, 0.0f)).b;

    return newCol;
}

// ���C���m�C�Y
float3 lineNoise(float3 col, float2 uv, float2 texUV)
{
    float3 newCol = col;
    newCol = lerp(col,
    float3(random(uv + float2(LINE_COLORS + TIME.x, 0)),
           random(uv + float2(LINE_COLORS + TIME.x, 1)),
           random(uv + float2(LINE_COLORS + TIME.x, 2))),
      step(random(floor(texUV.y * FLICKERING) + TIME.x), LINE_SPAN));

    return newCol;
}

// �t���[�����쐬����
void createFrame(inout float4 base, float2 uv, float distance)
{
    base = lerp(base, sepia(float4(0, 0, 0, 1)), step(0, max(abs(uv.y) - distance, abs(uv.x) - distance)));
}

// �u���E����
float4 oldTV(float2 inUV)
{
    float2 uv = inUV;
    float power = 0.2f;

    // ���S�����炷
    uv = uv - 0.5f;
    float vignette = length(uv);
    uv /= 1 - vignette * power;

    // ���S��߂�
    float2 texUV = uv + 0.5f;
    float4 base = tex.Sample(samLinear, texUV);

    // �h�炬
    texUV.x += (random(floor(uv.y * BLOCK_SIZE) + TIME.x) - 0.5f) * SHIMMELING;
    texUV.y += (random(floor(uv.x * BLOCK_SIZE) + TIME.x) - 0.5f) * SHIMMELING;

    // �J���[�m�C�Y
    float3 col = colorNoise(col, texUV);

    // ���C���m�C�Y �~ �r�l�b�g����
    col = lineNoise(col, uv, texUV) * (1 - vignette * VIGNETTE_WIDTH);

    // �A���t�@�l�͂��̂܂܂ō���
    base = float4(col, base.a);

    // ���g�����
    createFrame(base, uv, FRAME_DISTANCE);

    return base;
}

// �s�N�Z���V�F�[�_�[�̃��C���֐�
float4 main(PS_INPUT input) : SV_TARGET
{
    float4 old = oldTV(input.Tex);
    return sepia(old);
}

/*
    // �G�b�W���o
    float3 sobel = abs(current.rgb - old.rgb);
    float edge = max(max(sobel.r, sobel.g), sobel.b);
    edge = smoothstep(0.1f, 0.4f, edge); // ����

    // �A�E�g���C���ǉ�
    float3 outlinedColor = lerp(current.rgb, OUTLINE_COLOR, edge);
    float4 result = float4(outlinedColor, current.a);
*/