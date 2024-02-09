/*
 *	@File	WaterGS.hlsl
 *	@Brief	���ʂ̃W�I���g���V�F�[�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

static const int VNUM = 4 * 4;
static const float CONST_XZ = 2.5f / 4;
static const float CONST_Y = -0.5f;
static const float4 offset[VNUM] =
{
	// ��ԂP
    float4(-(CONST_XZ * 1), CONST_Y,  (CONST_XZ * 1), 0), // ����
	float4( (CONST_XZ * 1), CONST_Y,  (CONST_XZ * 1), 0), // �E��
	float4(-(CONST_XZ * 1), CONST_Y, -(CONST_XZ * 1), 0), // ����
	float4( (CONST_XZ * 1), CONST_Y, -(CONST_XZ * 1), 0), // �E��
	// ��ԂQ
	float4(-(CONST_XZ * 2), CONST_Y,  (CONST_XZ * 2), 0), // ����
	float4( (CONST_XZ * 2), CONST_Y,  (CONST_XZ * 2), 0), // �E��
	float4(-(CONST_XZ * 2), CONST_Y, -(CONST_XZ * 2), 0), // ����
	float4( (CONST_XZ * 2), CONST_Y, -(CONST_XZ * 2), 0), // �E��
	// ��ԂR
	float4(-(CONST_XZ * 3), CONST_Y,  (CONST_XZ * 3), 0), // ����
	float4( (CONST_XZ * 3), CONST_Y,  (CONST_XZ * 3), 0), // �E��
	float4(-(CONST_XZ * 3), CONST_Y, -(CONST_XZ * 3), 0), // ����
	float4( (CONST_XZ * 3), CONST_Y, -(CONST_XZ * 3), 0), // �E��
	// ��ԂS
	float4(-(CONST_XZ * 4), CONST_Y,  (CONST_XZ * 4), 0), // ����
	float4( (CONST_XZ * 4), CONST_Y,  (CONST_XZ * 4), 0), // �E��
	float4(-(CONST_XZ * 4), CONST_Y, -(CONST_XZ * 4), 0), // ����
	float4( (CONST_XZ * 4), CONST_Y, -(CONST_XZ * 4), 0), // �E��
};

[maxvertexcount(VNUM)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
    for (int i = 0; i < VNUM; i++)
    {
        PS_INPUT element;

		// �F���擾
        element.Color = input[0].Color;

		// ���W��ݒ�
        element.Pos = input[0].Pos + mul(offset[i] * ScaleW, World);

		// �r���[�Ǝˉe�s���K�p
        element.Pos = mul(element.Pos, View);
        element.Pos = mul(element.Pos, Proj);

		// �e�N�X�`���Ƀ��[���h���W��K�p
        element.Tex.x = offset[i].x + 1.0f; // x�����炷
        element.Tex.y = -offset[i].z + 1.0f; // y��Z���Ƃ��Ă݂Ȃ�
        element.Tex /= 2.0f;

		// ���H�f�[�^���o�͂ɔ��f
        output.Append(element);
    }

	output.RestartStrip();
}