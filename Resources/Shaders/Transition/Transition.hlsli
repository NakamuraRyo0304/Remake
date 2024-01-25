/*
 *  @File   Transition.hlsli
 *  @Brief  トランジションシェーダー
 *  @Date   2023-10-28
 *  @Author NakamuraRyo
 */

// 定数バッファ
cbuffer ConstBuffer : register(b0)
{
    matrix WORLD;   // ワールド変換行列
    matrix VIEW;    // ビュー変換行列
    matrix PROJ;    // プロジェクション変換行列
    float4 DIFFUSE; // ディフューズカラー
    float4 TIME;    // タイマー
};

// 頂点シェーダー入力
struct VS_INPUT
{
    float3 Pos      : POSITION; // 頂点座標
    float4 Color    : COLOR;    // 頂点の色
    float2 Tex      : TEXCOORD; // テクスチャ座標
};

// ピクセルシェーダー入力
struct PS_INPUT
{
    float4 Pos      : SV_POSITION;  // 出力座標
    float4 Color    : COLOR;        // 出力色
    float2 Tex      : TEXCOORD;     // 出力テクスチャ座標
};
