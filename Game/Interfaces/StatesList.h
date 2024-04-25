/*
 *	@File	StatesList.h
 *	@Brief	ゲームオブジェクトのステータスリスト。
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#pragma once

// オブジェクトID
enum class ID
{
	Default,		// 設定なし
	Back_Bird,		// タイトルの鳥
	Back_Logo,		// ロゴ
	Back_Sky,		// スカイドーム
	Obj_Player,		// プレイヤ
	Obj_Flag,		// プレイヤが追跡する旗
	Obj_Air,		// エディタ用判定ブロック
	Obj_Flozen,		// 氷床ブロック
	Obj_Coin,		// コインブロック
	Obj_Cloud,		// 雲ブロック
	Obj_Goal,		// ゴールオブジェクト
	Obj_Spike,		// 棘オブジェクト
	CursorPos,		// カーソルの3D位置
	Back_Iceberg,	// 氷山
	Back_Island,	// 孤島

	////////////////
	//// 特殊ID ////
	////////////////

	Deleted,		// 削除済み
	Length,			// 全ID数
};

