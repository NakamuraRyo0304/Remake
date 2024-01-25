/*
 *  @File    BrownTV.hlsli
 *  @Brief   ブラウン管テレビのシェーダー定義。
 *  @Date    2023-12-06
 *  @Author  NakamuraRyo
 */

// コンスタントバッファ
cbuffer ConstBuffer : register(b0)
{
    float4 TIME;                            // タイマー
    matrix WORLD;                           // ワールド変換行列
    matrix VIEW;                            // ビュー変換行列
    matrix PROJ;                            // プロジェクション変換行列
};

// 頂点シェーダーの入力構造体
struct VS_INPUT
{
    float3 Pos          : POSITION;         // 頂点座標
    float4 Color        : COLOR;            // 頂点色
    float2 Tex          : TEXCOORD;         // テクスチャ座標
};

// ピクセルシェーダーの入力構造体
struct PS_INPUT
{
    float4 Pos          : SV_POSITION;      // 頂点のスクリーン座標
    float4 Color        : COLOR;            // 頂点の色
    float2 Tex          : TEXCOORD;         // テクスチャ座標
};