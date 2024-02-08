/*
 *	@File	WaterGS.hlsl
 *	@Brief	���ʂ̃W�I���g���V�F�[�_�[�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

static const int vnum = 4;
static const float offX = 3.5f;
static const float4 offset[vnum] =
{
	// x,z�ʂŕ`�悷��
	float4(-offX, -5.0f, offX, 0.0f),	// ����
	float4( offX, -5.0f, offX, 0.0f),	// �E��
	float4(-offX, -5.0f,-offX, 0.0f),	// ����
	float4( offX, -5.0f,-offX, 0.0f),	// �E��
};

[maxvertexcount(vnum)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
	for (int i = 0; i < vnum; i++)
	{
		PS_INPUT element;

		// �F���擾
		element.Color = input[0].Color;

		// ���W��ݒ�
        element.Pos = input[0].Pos + mul(offset[i] * ScaleW, matWorld);

		// �r���[�Ǝˉe�s���K�p
		element.Pos = mul(element.Pos, matView);
		element.Pos = mul(element.Pos, matProj);

		// �e�N�X�`���Ƀ��[���h���W��K�p
		element.Tex.x =  offset[i].x + 1.0f; // x�����炷
		element.Tex.y = -offset[i].z + 1.0f; // y��Z���Ƃ��Ă݂Ȃ�
		element.Tex /= 2.0f;

		// ���H�f�[�^���o�͂ɔ��f
		output.Append(element);
	}
	output.RestartStrip();
}