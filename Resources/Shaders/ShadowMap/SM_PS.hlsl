/*
 *	@File	SM_PS.hlsl
 *	@Brief	シャドウマップのピクセルシェーダー。
 *	@Date	2024-02-08
 *  @Author NakamuraRyo
 */

#include "SM_Common.hlsli"

// シャドウマップテクスチャ
Texture2D tex : register(t1);

// シャドウマップ用テクスチャサンプラー
SamplerComparisonState samplerState : register(s1);

struct Input
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS   : TEXCOORD3;
};

// マッハバンド対策
#define SHADOW_EPSILON 0.00015f

float4 main(Input pin) : SV_TARGET0
{
    // ディフューズ・スぺキュラ
    float4 diffuse = float4(0, 0, 0, 0);
    float3 specular = 0;

    // ライトの向きを求める
    float3 lightDir = normalize(pin.PositionWS.xyz - LightPos.xyz);

    // スポットライトの範囲内ならライトの影響を与えて影をつける
    if (dot(lightDir, LightDir) > fCosTheta)
    {
        // 正規化デバイス座標にしてUVを計算
        pin.LightPosPS.xyz /= pin.LightPosPS.w;
        float2 uv = pin.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

        // 深度値とライト空間のピクセルのZ値を比較して影になる場所を計算
        float percentLit = tex.SampleCmpLevelZero(samplerState, uv, pin.LightPosPS.z - SHADOW_EPSILON).x;

        // ピクセルの法線を正規化
        float3 worldNormal = normalize(pin.NormalWS);

        // 光の強さからディフューズ色を計算
        float3 dotL = saturate(dot(-lightDir, worldNormal));
        float3 lightAmount = dotL * percentLit * (1.0f - LightAmbient) + LightAmbient;
        diffuse = float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a);

        // ベクトルからスぺキュラのかかり具合を計算
        float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
        float3 eVecNormal = normalize(eyeVector - lightDir);
        float dotH = saturate(dot(eVecNormal, worldNormal));
        specular = pow(dotH, SpecularPower) * dotL * SpecularColor * percentLit;
    }
    else
    {
        diffuse = float4(LightAmbient, 1.0f) * DiffuseColor;
    }

    // テクスチャ色とディフューズ色・スぺキュラを乗算
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;
    color.rgb += specular * diffuse.a;

    // 出力する
    return color;
}

