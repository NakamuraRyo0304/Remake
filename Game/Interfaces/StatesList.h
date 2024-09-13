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
	Default,			// 設定なし
	T_Bird,				// タイトルの鳥
	T_Logo,				// ロゴ
	A_Skydome,			// スカイドーム
	PE_Player,			// プレイヤ
	P_Flag,				// プレイヤが追跡する旗
	PE_Air,				// エディタ用判定ブロック
	PE_Flozen,			// 氷床ブロック
	PE_Coin,			// コインブロック
	PE_Cloud,			// 雲ブロック
	PE_Goal,			// ゴールオブジェクト
	PE_Spike,			// 棘オブジェクト
	PE_Cursor_Object,	// カーソルの3D位置
	P_Iceberg,			// 氷山
	P_Island,			// 孤島

	////////////////
	//// 特殊ID ////
	////////////////

	Deleted,			// 削除済み
	Length,				// 全ID数
};

