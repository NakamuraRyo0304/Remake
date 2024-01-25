/*
 *	@File	BrownPS.hlsl
 *	@Brief	ブラウン管テレビ(ピクセルシェーダー)。
 *	@Date	2023-12-06
 *  @Author NakamuraRyo
 */

#include "../Display.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

#define LINE_COLORS 123.0f      // カラーの数
#define LINE_POWER 7.0f         // ラインノイズの強さ
#define LINE_SPAN 0.001f        // ラインの出現間隔
#define VIGNETTE_WIDTH 1.2f     // ビネットの幅(画面の明るさ)
#define FRAME_DISTANCE  0.525f  // 枠の大きさ
#define FLICKERING 100          // 線の細かさ
#define SHIMMELING 0.0025f      // 揺らぎの大きさ
#define BLOCK_SIZE 25           // 揺らぎブロックの大きさ

// 二次元乱数を生成する
float random(float2 st)
{
    return frac(sin(dot(st, float2(12.9898, 78.233))) * 43758.5453);
}

// グレースケール
float gray(float4 col)
{
    return col.r * 0.3f + col.r * 0.6f + col.r * 0.1f;
}

// セピア
float4 sepia(float4 col)
{
    float g = gray(col);
    return float4(g * 1.44f, g * 0.99f, g * 0.57f, col.a);
}

// カラーノイズ
float3 colorNoise(float3 col, float2 texUV)
{
    float3 newCol = col;
    newCol.r = tex.Sample(samLinear, texUV).r;
    newCol.g = tex.Sample(samLinear, texUV + float2(0.002f, 0.0f)).g;
    newCol.b = tex.Sample(samLinear, texUV + float2(0.004f, 0.0f)).b;

    return newCol;
}

// ラインノイズ
float3 lineNoise(float3 col, float2 uv, float2 texUV)
{
    float3 newCol = col;
    newCol = lerp(col,
    float3(random(uv + float2(LINE_COLORS + TIME.x, 0)),
           random(uv + float2(LINE_COLORS + TIME.x, 1)),
           random(uv + float2(LINE_COLORS + TIME.x, 2))),
      step(random(floor(texUV.y * FLICKERING) + TIME.x), LINE_SPAN));

    return newCol;
}

// フレームを作成する
void createFrame(inout float4 base, float2 uv, float distance)
{
    base = lerp(base, sepia(float4(0, 0, 0, 1)), step(0, max(abs(uv.y) - distance, abs(uv.x) - distance)));
}

// ブラウン管
float4 oldTV(float2 inUV)
{
    float2 uv = inUV;
    float power = 0.2f;

    // 中心をずらす
    uv = uv - 0.5f;
    float vignette = length(uv);
    uv /= 1 - vignette * power;

    // 中心を戻す
    float2 texUV = uv + 0.5f;
    float4 base = tex.Sample(samLinear, texUV);

    // 揺らぎ
    texUV.x += (random(floor(uv.y * BLOCK_SIZE) + TIME.x) - 0.5f) * SHIMMELING;
    texUV.y += (random(floor(uv.x * BLOCK_SIZE) + TIME.x) - 0.5f) * SHIMMELING;

    // カラーノイズ
    float3 col = colorNoise(col, texUV);

    // ラインノイズ × ビネット効果
    col = lineNoise(col, uv, texUV) * (1 - vignette * VIGNETTE_WIDTH);

    // アルファ値はそのままで合成
    base = float4(col, base.a);

    // 黒枠を作る
    createFrame(base, uv, FRAME_DISTANCE);

    return base;
}

// ピクセルシェーダーのメイン関数
float4 main(PS_INPUT input) : SV_TARGET
{
    float4 old = oldTV(input.Tex);
    return sepia(old);
}

/*
    // エッジ検出
    float3 sobel = abs(current.rgb - old.rgb);
    float edge = max(max(sobel.r, sobel.g), sobel.b);
    edge = smoothstep(0.1f, 0.4f, edge); // 調整

    // アウトライン追加
    float3 outlinedColor = lerp(current.rgb, OUTLINE_COLOR, edge);
    float4 result = float4(outlinedColor, current.a);
*/