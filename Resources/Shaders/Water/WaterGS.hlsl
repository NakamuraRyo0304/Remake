/*
 *	@File	WaterGS.hlsl
 *	@Brief	水面のジオメトリシェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

static const int vnum = 4;
static const float offX = 3.5f;
static const float4 offset[vnum] =
{
	// x,z面で描画する
	float4(-offX, -5.0f, offX, 0.0f),	// 左上
	float4( offX, -5.0f, offX, 0.0f),	// 右上
	float4(-offX, -5.0f,-offX, 0.0f),	// 左下
	float4( offX, -5.0f,-offX, 0.0f),	// 右下
};

[maxvertexcount(vnum)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
	for (int i = 0; i < vnum; i++)
	{
		PS_INPUT element;

		// 色を取得
		element.Color = input[0].Color;

		// 座標を設定
        element.Pos = input[0].Pos + mul(offset[i] * ScaleW, matWorld);

		// ビューと射影行列を適用
		element.Pos = mul(element.Pos, matView);
		element.Pos = mul(element.Pos, matProj);

		// テクスチャにワールド座標を適用
		element.Tex.x =  offset[i].x + 1.0f; // xをずらす
		element.Tex.y = -offset[i].z + 1.0f; // yをZ軸としてみなす
		element.Tex /= 2.0f;

		// 加工データを出力に反映
		output.Append(element);
	}
	output.RestartStrip();
}