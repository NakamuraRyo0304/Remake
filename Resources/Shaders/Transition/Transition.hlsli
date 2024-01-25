/*
 *  @File   Transition.hlsli
 *  @Brief  �g�����W�V�����V�F�[�_�[
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

// �萔�o�b�t�@
cbuffer ConstBuffer : register(b0)
{
    matrix WORLD;   // ���[���h�ϊ��s��
    matrix VIEW;    // �r���[�ϊ��s��
    matrix PROJ;    // �v���W�F�N�V�����ϊ��s��
    float4 DIFFUSE; // �f�B�t���[�Y�J���[
    float4 TIME;    // �^�C�}�[
};

// ���_�V�F�[�_�[����
struct VS_INPUT
{
    float3 Pos      : POSITION; // ���_���W
    float4 Color    : COLOR;    // ���_�̐F
    float2 Tex      : TEXCOORD; // �e�N�X�`�����W
};

// �s�N�Z���V�F�[�_�[����
struct PS_INPUT
{
    float4 Pos      : SV_POSITION;  // �o�͍��W
    float4 Color    : COLOR;        // �o�͐F
    float2 Tex      : TEXCOORD;     // �o�̓e�N�X�`�����W
};
