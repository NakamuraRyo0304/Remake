/*
 *  @File   PS_Transition.hlsl
 *  @Brief  �g�����W�V�����V�F�[�_�[�̃s�N�Z���V�F�[�_�[
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

#include "Transition.hlsli"

// �V���h�E�}�b�v�e�N�X�`���ƃT���v���[�X�e�[�g�̒�`
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

// �s�N�Z���V�F�[�_�[�̃��C���֐�
float4 main(PS_INPUT input) : SV_TARGET
{
    // �o�̓J���[�̏�����
    float4 output = float4(1, 1, 1, 1);

    // �e�N�X�`���̐F�����擾
    float4 color = tex.Sample(samLinear, input.Tex);

    // �G�b�W������ݒ肵�A����肵�Ȃ���t�F�[�h������
    float edge = saturate((color.b - TIME.x) / 0.1f);
    output.a *= (TIME.x - edge);

    return output * input.Color;
}
