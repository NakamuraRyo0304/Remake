/*
 *  @File   PS_Transition.hlsl
 *  @Brief  トランジションシェーダーのピクセルシェーダー
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

#include "Transition.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

// 閾値
#define EDGE_THRESHOLD 0.01f

// ピクセルシェーダーのメイン関数
float4 main(PS_INPUT input) : SV_TARGET
{
    // 出力カラーの初期化
    float4 output = DIFFUSE;

    // テクスチャの色情報を取得
    float4 color = tex.Sample(samLinear, input.Tex);

    // エッジ条件を設定し、縁取りしながらフェードさせる
    float edge = saturate((color.b - TIME.x) / EDGE_THRESHOLD);
    output.a *= (TIME.x - edge);

    return output;
}