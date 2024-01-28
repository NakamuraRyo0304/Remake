/*
 *	@File	IGameObjectStates.h
 *	@Brief	ゲームオブジェクトのステータス宣言。
 *	@Date	2023-11-18
 *  @Author NakamuraRyo
 */

#pragma once

/// <summary>
/// オブジェクトID
/// Back:背景等|Obj:判定ありオブジェクト
/// </summary>
enum class ID
{
	Default,		// 設定なし
	Back_Bird,		// タイトルの鳥
	Back_Logo,		// ロゴ
	Back_Sky,		// スカイドーム
	Obj_Sand,		// 砂ブロック
	Obj_Coin,		// コインブロック
	Obj_Cloud,		// 雲ブロック
	Deleted,		// 削除済み
	Length,			// 全ID数
};

// 重さ無し
constexpr double NON_WEIGHT = -1.0;