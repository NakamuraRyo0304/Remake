/*
 *	@File	DisplayVS.hlsl
 *	@Brief	ディスプレイの頂点シェーダー。
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

// 頂点シェーダーのメイン関数
PS_INPUT main(VS_INPUT input)
{
    // 出力用の構造体を初期化
    PS_INPUT output = (PS_INPUT) 0;

    // 入力された座標を格納
    output.Pos = float4(input.Pos, 1);

    // 入力された色情報を格納
    output.Color = input.Color;

    // 入力されたテクスチャ座標を格納
    output.Tex = input.Tex;

    // 出力用の構造体を返す
    return output;
}
