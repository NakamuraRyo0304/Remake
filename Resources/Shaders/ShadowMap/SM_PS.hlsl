/*
 *	@File	SM_PS.hlsl
 *	@Brief	シャドウマップのピクセルシェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "SM_Common.hlsli"

Texture2D tex : register(t1); // シャドウマップテクスチャ
SamplerComparisonState samplerState : register(s1); // シャドウマップサンプラー

struct Input
{
    float2 TexCoord   : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS   : TEXCOORD2;
    float4 LightPosPS : TEXCOORD3;
};

// マッハバンド対策
#define SHADOW_EPSILON 0.00015f
// ライトの影響度を計算
float calcPercent(float3 lightDir, float4 lightPosPS)
{
    // スポットライトの範囲内なら影の影響を与える
    if (dot(lightDir, LightDir) > fCosTheta)
    {
        // 正規化デバイス座標に変換
        float3 normalPos = lightPosPS.xyz / lightPosPS.w;
        float2 uv = normalPos.xy * float2(0.5f, -0.5f) + 0.5f;

        // シャドウマップをサンプリングして影の影響度を取得
        return tex.SampleCmpLevelZero(samplerState, uv, normalPos.z - SHADOW_EPSILON).x;
    }
    else
    {
        return 0.0f; // スポットライトの範囲外では影響度は0
    }
}

// スペキュラを計算
float3 calcSpecular(float3 position, float3 worldNormal, float3 lightDir, float3 dotLight, float percent)
{
    float3 eyeVector = normalize(EyePosition - position);
    float3 eyeVectorNormal = normalize(eyeVector - lightDir);
    float dotHalfVector = saturate(dot(eyeVectorNormal, worldNormal));

    return pow(dotHalfVector, SpecularPower) * dotLight * SpecularColor * percent;
}

// ディフューズを計算
float4 calcDiffuse(float3 dotLight, float percent)
{
    // ピクセルの法線を正規化
    float3 lightAmount = dotLight * percent * (1.0f - LightAmbient) + LightAmbient;

    // スポットライトの範囲外ではアンビエントライトのみを使う
    float4 diffuse = lerp(
        float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a),
        float4(LightAmbient, 1.0f) * DiffuseColor,
        step(percent, 0.0f)
    );

    return diffuse;
}

float4 main(Input pin) : SV_TARGET0
{
    // ライトの向きを算出
    float3 lightDir = normalize(pin.PositionWS.xyz - LightPos.xyz);

    // 影響度数を計算
    float percent = calcPercent(lightDir, pin.LightPosPS);

    // ピクセルの法線を正規化
    float3 worldNormal = normalize(pin.NormalWS);

    // 光の強さからディフューズ色を計算
    float3 dotLight = saturate(dot(-lightDir, worldNormal));

    // ディフューズを計算
    float4 diffuse = calcDiffuse(dotLight, percent);

    // スペキュラを計算
    float3 specular = calcSpecular(pin.PositionWS.xyz, worldNormal, lightDir, dotLight, percent);

    // 計算結果を乗算
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;
    color.rgb += specular * diffuse.a;

    // 最終出力
    return color;
}
