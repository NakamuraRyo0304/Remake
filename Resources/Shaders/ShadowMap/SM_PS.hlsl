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
#define SHADOW_EPSILON 0.0001f

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
        // 正規化デバイス座標にする(-1から1に正規化)
        pin.LightPosPS.xyz /= pin.LightPosPS.w;

        // シャドウマップのUV値を求める
        float2 uv = pin.LightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;

        // シャドウマップの深度値とライト空間のピクセルのZ値を比較して影になるか調べる
        float percentLit = tex.SampleCmpLevelZero(samplerState, uv, pin.LightPosPS.z - SHADOW_EPSILON).x;

        // ピクセルの法線を正規化
        float3 worldNormal = normalize(pin.NormalWS);

        // 光の強さを内積から算出する
        float3 dotL = saturate(dot(-lightDir, worldNormal));

        // ライトによる明るさを求める
        float3 lightAmount = dotL * percentLit * (1.0f - LightAmbient) + LightAmbient;

        // ディフューズ色を求める
        diffuse = float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a);

        // 視線ベクトル
        float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);

        // ハーフベクトル
        float3 halfVector = normalize(eyeVector - lightDir);

        // スペキュラの影響割合を内積を使い求める
        float dotH = saturate(dot(halfVector, worldNormal));

        // スペキュラパワーを指数として使いハイライトのかかり具合を調整
        specular = pow(dotH, SpecularPower) * dotL * SpecularColor * percentLit;
    }
    else
    {
        // スポットライトの外
        diffuse = float4(LightAmbient, 1.0f) * DiffuseColor;
    }

    // テクスチャ色とディフューズ色を掛ける
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;

    // スペキュラを加える
    color.rgb += specular * diffuse.a;

    return color;
}

