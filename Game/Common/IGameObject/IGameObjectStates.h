/*
 *	@File	IGameObjectStates.h
 *	@Brief	ゲームオブジェクトのステータス宣言。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once

/// <summary>
/// オブジェクトID
/// オブジェクトの判定を可能にする
/// </summary>
enum class ID
{
	Default,		// 設定なし
	Back_Bird,		// タイトルの鳥
	Back_Logo,		// ロゴ
	Back_Sky,		// スカイドーム
	Obj_Player,		// プレイヤ
	Obj_Air,		// エディタ用判定ブロック
	Obj_Sand,		// 砂ブロック
	Obj_Coin,		// コインブロック
	Obj_Cloud,		// 雲ブロック
	Obj_Goal,		// ゴールオブジェクト
	Obj_Spike,		// 棘オブジェクト
	CursorPos,		// カーソルの3D位置




	////////////////
	//// 特殊ID ////
	////////////////

	Deleted,		// 削除済み
	Length,			// 全ID数
};

// 重さ無し
constexpr double NON_WEIGHT = -1.0;