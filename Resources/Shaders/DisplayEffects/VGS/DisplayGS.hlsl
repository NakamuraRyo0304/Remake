/*
 *	@File	DisplayGS.hlsl
 *	@Brief	ディスプレイのジオメトリシェーダー。
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

static const int vnum = 6;

static const float4 tex_offset[vnum] =
{
    float4(-1.0f, 1.0f, 0.0f, 0.0f), // 左上	////////////////
	float4(-1.0f,-1.0f, 0.0f, 0.0f), // 左下	/// 左三角形 ///
	float4( 0.0f, 1.0f, 0.0f, 0.0f), // 中上	////////////////
	float4( 0.0f,-1.0f, 0.0f, 0.0f), // 中下	////////////////
	float4( 1.0f, 1.0f, 0.0f, 0.0f), // 右上	/// 右三角形 ///
	float4( 1.0f,-1.0f, 0.0f, 0.0f), // 右下	////////////////
};

// ジオメトリシェーダーのメイン関数
[maxvertexcount(vnum)]
void main(point PS_INPUT input[1], inout TriangleStream<PS_INPUT> output)
{
	for (int i = 0; i < vnum; i++)
	{
		PS_INPUT element;

		// 色を取得
		element.Color = input[0].Color;

		// 座標を設定
        element.Pos = input[0].Pos + mul(tex_offset[i], WORLD);

		// ビューと射影行列を適用
		element.Pos = mul(element.Pos, VIEW);
		element.Pos = mul(element.Pos, PROJ);

		// テクスチャにワールド座標を適用
		element.Tex.x =  tex_offset[i].x + 1.0f;
		element.Tex.y = -tex_offset[i].y + 1.0f;
		element.Tex *= 0.5f;

		// 加工データを出力に反映
		output.Append(element);
	}
	output.RestartStrip();
}