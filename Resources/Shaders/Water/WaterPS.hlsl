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
#define FN_UV_PATH1 0.05f       // ノイズの結果に乗算する値
#define FN_UV_PATH2 0.06f       // ノイズの結果に乗算する値
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

// パーリンノイズを生成する関数
float perlinNoise(float2 uv)
{
    // uv座標を整数部と小数部に分割
    float2 p = floor(uv);
    float2 f = frac(uv);

    // fの補間関数を計算
    float2 u = f * f * (3.0f - 2.0f * f);

    // 隣接する4つの整数座標に対してランダム値を取得
    float2 v00 = random(p + float2(0, 0));
    float2 v10 = random(p + float2(1, 0));
    float2 v01 = random(p + float2(0, 1));
    float2 v11 = random(p + float2(1, 1));

    // 補間と線形補間を使用してパーリンノイズ値を計算
    return lerp(lerp(dot(v00, f - float2(0, 0)), dot(v10, f - float2(1, 0)), u.x),
                lerp(dot(v01, f - float2(0, 1)), dot(v11, f - float2(1, 1)), u.x), u.y);
}

// オリジナルノイズを生成する関数
float originalNoise(float2 uv)
{
    float output = 0.0f;
    float amplitude = 1.0f;// 振幅
    float frequency = 1.0f;// 頻度

    // 複数のオクターブでノイズを生成し、合成する
    for (float i = 0; i < FN_OCTAVES; ++i)
    {
        output += perlinNoise(uv * frequency) * amplitude;
        amplitude *= FN_PERSISTENCE;
        frequency *= 2.0f; // 周波数を倍にすることで次のオクターブに移る
    }

    return output;
}

// 波打ち関数
void waveUV(inout float2 uv)
{
    uv.x += Time * FLOW_VELOCITY;       // 横移動
    uv.y += cos(Time) * SWING_SPEED;    // 縦揺れ
}

float4 main(PS_INPUT input) : SV_TARGET
{
    // ランダムなオフセットを生成
    float2 uv = input.Tex;
    float2 offset = perlinNoise(uv);
    uv += offset;

    // オリジナルノイズで揺らす
    float p = originalNoise(uv * FN_UV_POWER);
    uv += float2(p * FN_UV_PATH1 * cos(Time), p * FN_UV_PATH2 * sin(Time));

    // UV値を時間に応じて滑らかに移動させる
    waveUV(uv);

    // 最終出力
    return tex.Sample(samLinear, uv);
}
