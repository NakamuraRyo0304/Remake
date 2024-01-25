/*
 *  @File   GS_Transition.hlsl
 *  @Brief  �g�����W�V�����V�F�[�_�[�̃W�I���g���V�F�[�_�[
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

#include "Transition.hlsli"

// ���_���̐ݒ�
static const int vnum = 4;

// �I�t�Z�b�g�̔z��
static const float4 offset_array[vnum] =
{
    float4(-1.0f,  1.0f, 0.0f, 0.0f),    // ����
    float4( 1.0f,  1.0f, 0.0f, 0.0f),    // �E��
    float4(-1.0f, -1.0f, 0.0f, 0.0f),    // ����
    float4( 1.0f, -1.0f, 0.0f, 0.0f),    // �E��
};

// �W�I���g���V�F�[�_�[�̃��C���֐�
[maxvertexcount(vnum)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
    for (int i = 0; i < vnum; i++)
    {
        PS_INPUT element;

        // �I�t�Z�b�g��K�p���č��W��ݒ�
        element.Pos = input[0].Pos + mul(offset_array[i], WORLD);

        // �r���[�Ǝˉe�s���K�p
        element.Pos = mul(element.Pos, VIEW);
        element.Pos = mul(element.Pos, PROJ);

        // �J���[�ƃe�N�X�`�����W�̐ݒ�
        element.Color = input[0].Color;
        element.Tex.x = offset_array[i].x + 1.0f;
        element.Tex.y = -offset_array[i].y + 1.0f;
        element.Tex *= 0.5f;

        // �o�͂ɒǉ�
        output.Append(element);
    }

    // �X�g���b�v�����X�^�[�g
    output.RestartStrip();
}
