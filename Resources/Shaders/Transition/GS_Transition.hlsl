/*
 *  @File   GS_Transition.hlsl
 *  @Brief  トランジションシェーダーのジオメトリシェーダー
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

#include "Transition.hlsli"

// 頂点数の設定
static const int vnum = 4;

// オフセットの配列
static const float4 offset_array[vnum] =
{
    float4(-1.0f,  1.0f, 0.0f, 0.0f),    // 左上
    float4( 1.0f,  1.0f, 0.0f, 0.0f),    // 右上
    float4(-1.0f, -1.0f, 0.0f, 0.0f),    // 左下
    float4( 1.0f, -1.0f, 0.0f, 0.0f),    // 右下
};

// ジオメトリシェーダーのメイン関数
[maxvertexcount(vnum)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
    for (int i = 0; i < vnum; i++)
    {
        PS_INPUT element;

        // オフセットを適用して座標を設定
        element.Pos = input[0].Pos + mul(offset_array[i], WORLD);

        // ビューと射影行列を適用
        element.Pos = mul(element.Pos, VIEW);
        element.Pos = mul(element.Pos, PROJ);

        // カラーとテクスチャ座標の設定
        element.Color = input[0].Color;
        element.Tex.x = offset_array[i].x + 1.0f;
        element.Tex.y = -offset_array[i].y + 1.0f;
        element.Tex *= 0.5f;

        // 出力に追加
        output.Append(element);
    }

    // ストリップをリスタート
    output.RestartStrip();
}
