/*
 *  @File   VS_Transition.hlsli
 *  @Brief  �g�����W�V�����V�F�[�_�[�̒��_�V�F�[�_�[
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

#include "Transition.hlsli"

// �s�N�Z���V�F�[�_�[�ւ̓��͍\����
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // ���_���W���z���W�j�A�X���W�ɕϊ�
    output.Pos = float4(input.Pos, 1);

    // �F�ƃe�N�X�`�����W�����̂܂܏o��
    output.Color = input.Color;
    output.Tex = input.Tex;

    return output;
}
