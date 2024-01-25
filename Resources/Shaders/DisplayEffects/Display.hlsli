/*
 *  @File    BrownTV.hlsli
 *  @Brief   �u���E���ǃe���r�̃V�F�[�_�[��`�B
 *  @Date    2023-12-06
 *  @Author  NakamuraRyo
 */

// �R���X�^���g�o�b�t�@
cbuffer ConstBuffer : register(b0)
{
    float4 TIME;                            // �^�C�}�[
    matrix WORLD;                           // ���[���h�ϊ��s��
    matrix VIEW;                            // �r���[�ϊ��s��
    matrix PROJ;                            // �v���W�F�N�V�����ϊ��s��
};

// ���_�V�F�[�_�[�̓��͍\����
struct VS_INPUT
{
    float3 Pos          : POSITION;         // ���_���W
    float4 Color        : COLOR;            // ���_�F
    float2 Tex          : TEXCOORD;         // �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�[�̓��͍\����
struct PS_INPUT
{
    float4 Pos          : SV_POSITION;      // ���_�̃X�N���[�����W
    float4 Color        : COLOR;            // ���_�̐F
    float2 Tex          : TEXCOORD;         // �e�N�X�`�����W
};