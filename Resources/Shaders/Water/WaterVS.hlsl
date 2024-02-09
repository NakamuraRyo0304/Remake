/*
 *	@File	WaterVS.hlsl
 *	@Brief	水面の頂点シェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

#define WAVE_AMPLITUDE 1.5f          // 波の高さ
#define WAVE_SPEED 0.05f             // 波の速度

// ランダム関数
float rand(in float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // 時間を使って波の動きを作成
    // 頂点の x 座標に基づいて、各頂点ごとに異なる波の振る舞いを適用
    float waveHeight = sin(input.Pos.x * WAVE_SPEED + Time) * WAVE_AMPLITUDE;

    // 頂点毎に異なるランダムな波の高さを生成
    float randomOffset = rand(input.Pos.xy) * WAVE_AMPLITUDE + 1.0f;

    // 波の高さを頂点座標に加算
    output.Pos = float4(input.Pos.x, input.Pos.y + waveHeight + randomOffset, input.Pos.z, 1.0);

    output.Color = input.Color;
    output.Tex = input.Tex;

    return output;
}