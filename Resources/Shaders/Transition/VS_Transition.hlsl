/*
 *  @File   VS_Transition.hlsli
 *  @Brief  トランジションシェーダーの頂点シェーダー
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

#include "Transition.hlsli"

// ピクセルシェーダーへの入力構造体
PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;

    // 頂点座標をホモジニアス座標に変換
    output.Pos = float4(input.Pos, 1);

    // 色とテクスチャ座標をそのまま出力
    output.Color = input.Color;
    output.Tex = input.Tex;

    return output;
}
