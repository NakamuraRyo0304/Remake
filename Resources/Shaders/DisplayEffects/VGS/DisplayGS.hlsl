/*
 *	@File	DisplayGS.hlsl
 *	@Brief	�f�B�X�v���C�̃W�I���g���V�F�[�_�[�B
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

static const int vnum = 6;

static const float4 tex_offset[vnum] =
{
    float4(-1.0f, 1.0f, 0.0f, 0.0f), // ����	////////////////
	float4(-1.0f,-1.0f, 0.0f, 0.0f), // ����	/// ���O�p�` ///
	float4( 0.0f, 1.0f, 0.0f, 0.0f), // ����	////////////////
	float4( 0.0f,-1.0f, 0.0f, 0.0f), // ����	////////////////
	float4( 1.0f, 1.0f, 0.0f, 0.0f), // �E��	/// �E�O�p�` ///
	float4( 1.0f,-1.0f, 0.0f, 0.0f), // �E��	////////////////
};

// �W�I���g���V�F�[�_�[�̃��C���֐�
[maxvertexcount(vnum)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
	for (int i = 0; i < vnum; i++)
	{
		PS_INPUT element;

		// �F���擾
		element.Color = input[0].Color;

		// ���W��ݒ�
        element.Pos = input[0].Pos + mul(tex_offset[i], WORLD);

		// �r���[�Ǝˉe�s���K�p
		element.Pos = mul(element.Pos, VIEW);
		element.Pos = mul(element.Pos, PROJ);

		// �e�N�X�`���Ƀ��[���h���W��K�p
		element.Tex.x =  tex_offset[i].x + 1.0f;
		element.Tex.y = -tex_offset[i].y + 1.0f;
		element.Tex *= 0.5f;

		// ���H�f�[�^���o�͂ɔ��f
		output.Append(element);
	}
	output.RestartStrip();
}