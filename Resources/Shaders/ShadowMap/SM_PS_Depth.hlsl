/*
 *	@File	SM_PS_Depth.hlsl
 *	@Brief	�V���h�E�}�b�v�̃s�N�Z���f�v�X�B
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

struct Input
{
    float4 PositionPS : SV_Position;
};

float4 main(Input pin) : SV_TARGET0
{
    // Z�l���o�͂���
    return pin.PositionPS.z;
}
