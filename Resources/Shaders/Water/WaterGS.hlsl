/*
 *	@File	WaterGS.hlsl
 *	@Brief	水面のジオメトリシェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

static const int VNUM = 4 * 4;
static const float CONST_XZ = 2.5f / 4;
static const float CONST_Y = -0.5f;
static const float4 offset[VNUM] =
{
	// 区間１
    float4(-(CONST_XZ * 1), CONST_Y,  (CONST_XZ * 1), 0), // 左上
	float4( (CONST_XZ * 1), CONST_Y,  (CONST_XZ * 1), 0), // 右上
	float4(-(CONST_XZ * 1), CONST_Y, -(CONST_XZ * 1), 0), // 左下
	float4( (CONST_XZ * 1), CONST_Y, -(CONST_XZ * 1), 0), // 右下
	// 区間２
	float4(-(CONST_XZ * 2), CONST_Y,  (CONST_XZ * 2), 0), // 左上
	float4( (CONST_XZ * 2), CONST_Y,  (CONST_XZ * 2), 0), // 右上
	float4(-(CONST_XZ * 2), CONST_Y, -(CONST_XZ * 2), 0), // 左下
	float4( (CONST_XZ * 2), CONST_Y, -(CONST_XZ * 2), 0), // 右下
	// 区間３
	float4(-(CONST_XZ * 3), CONST_Y,  (CONST_XZ * 3), 0), // 左上
	float4( (CONST_XZ * 3), CONST_Y,  (CONST_XZ * 3), 0), // 右上
	float4(-(CONST_XZ * 3), CONST_Y, -(CONST_XZ * 3), 0), // 左下
	float4( (CONST_XZ * 3), CONST_Y, -(CONST_XZ * 3), 0), // 右下
	// 区間４
	float4(-(CONST_XZ * 4), CONST_Y,  (CONST_XZ * 4), 0), // 左上
	float4( (CONST_XZ * 4), CONST_Y,  (CONST_XZ * 4), 0), // 右上
	float4(-(CONST_XZ * 4), CONST_Y, -(CONST_XZ * 4), 0), // 左下
	float4( (CONST_XZ * 4), CONST_Y, -(CONST_XZ * 4), 0), // 右下
};

[maxvertexcount(VNUM)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
    for (int i = 0; i < VNUM; i++)
    {
        PS_INPUT element;

		// 色を取得
        element.Color = input[0].Color;

		// 座標を設定
        element.Pos = input[0].Pos + mul(offset[i] * ScaleW, World);

		// ビューと射影行列を適用
        element.Pos = mul(element.Pos, View);
        element.Pos = mul(element.Pos, Proj);

		// テクスチャにワールド座標を適用
        element.Tex.x = offset[i].x + 1.0f; // xをずらす
        element.Tex.y = -offset[i].z + 1.0f; // yをZ軸としてみなす
        element.Tex /= 2.0f;

		// 加工データを出力に反映
        output.Append(element);
    }

	output.RestartStrip();
}