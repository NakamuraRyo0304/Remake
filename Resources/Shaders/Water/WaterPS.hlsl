/*
 *	@File	WaterPS.hlsl
 *	@Brief	水面のピクセルシェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "Water.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

#define FLOW_VELOCITY 0.1f      // 流れる力
#define SWING_SPEED 0.01f       // 左右に振れる力
#define FN_UV_PATH1 0.05f       // フラクタルノイズの結果に乗算する値
#define FN_UV_PATH2 0.06f       // フラクタルノイズの結果に乗算する値
#define FN_UV_POWER 25          // uvのサイズ
#define FN_OCTAVES 10.0f        // オクターブ
#define FN_PERSISTENCE 0.6f     // 持続度
#define RANDOM_OFFSET 0.01f     // ランダムオフセット

// 二次元乱数を生成する
float2 random(float2 st)
{
    st = float2(dot(st, float2(127.1f, 311.7f)),
                dot(st, float2(269.5f, 183.3f)));

    return -1.0f + 2.0f * frac(sin(st) * 43758.5453f);
}

// パーリンノイズ
float perlinNoise(float2 uv)
{
    float2 p = floor(uv);
    float2 f = frac(uv);
    float2 u = f * f * (3.0 - 2.0 * f);

    float2 v00 = random(p + float2(0, 0));
    float2 v10 = random(p + float2(1, 0));
    float2 v01 = random(p + float2(0, 1));
    float2 v11 = random(p + float2(1, 1));

    return lerp(lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
         lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x), u.y);
}

// フラクタルノイズを生成する関数
float fractalNoise(float2 uv)
{
    float noise = 0.0;
    float amplitude = 1.0;
    float frequency = 1.0;

    // 複数のオクターブでノイズを生成し、合成する
    for (float i = 0; i < FN_OCTAVES; ++i)
    {
        noise += perlinNoise(uv * frequency) * amplitude;
        amplitude *= FN_PERSISTENCE;
        frequency *= 2.0; // 周波数を倍にすることで次のオクターブに移る
    }

    return noise;
}

// ランダムなオフセットを生成する
float2 randomOffset(float2 uv)
{
    float2 randomOffset = float2(
        frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453),
        frac(cos(dot(uv, float2(12.9898, 78.233))) * 43758.5453));
    return randomOffset * RANDOM_OFFSET;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.Tex;

    // ランダムなオフセットを生成
    float2 offset = perlinNoise(uv);

    // UV値にオフセットを加える
    uv += offset;

    // フルクタルノイズで揺らす
    float p = fractalNoise(uv * FN_UV_POWER);

    // UV値を不規則に揺らす
    uv += float2(p * FN_UV_PATH1 * cos(Time), p * FN_UV_PATH2 * sin(Time));

    // UVX値を時間に応じて滑らかに移動させる
    uv.x += Time * FLOW_VELOCITY;

    // UVY値を左右に振る
    uv.y += cos(Time) * SWING_SPEED;

    // 出力する
    return tex.Sample(samLinear, uv);
}