/*
 *	@File	ParticleVS.hlsl
 *	@Brief	�p�[�e�B�N���̃o�[�e�b�N�X�V�F�[�_�[
 *	@Date	2023-01-21
 *  @Author NakamuraRyo
 */

#include "Particle.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = float4(input.Pos,1);

	output.Color = input.Color;
	output.Tex = input.Tex;
	return output;
}