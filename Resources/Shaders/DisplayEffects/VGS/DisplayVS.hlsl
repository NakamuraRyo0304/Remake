/*
 *	@File	DisplayVS.hlsl
 *	@Brief	�f�B�X�v���C�̒��_�V�F�[�_�[�B
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

// ���_�V�F�[�_�[�̃��C���֐�
PS_INPUT main(VS_INPUT input)
{
    // �o�͗p�̍\���̂�������
    PS_INPUT output = (PS_INPUT) 0;

    // ���͂��ꂽ���W���i�[
    output.Pos = float4(input.Pos, 1);

    // ���͂��ꂽ�F�����i�[
    output.Color = input.Color;

    // ���͂��ꂽ�e�N�X�`�����W���i�[
    output.Tex = input.Tex;

    // �o�͗p�̍\���̂�Ԃ�
    return output;
}
