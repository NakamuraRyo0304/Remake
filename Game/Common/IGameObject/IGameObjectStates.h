/*
 *	@File	IGameObjectStates.h
 *	@Brief	ゲームオブジェクトのステータス宣言。
 *	@Date	2023-11-18
 *  @Author NakamuraRyo
 */

#pragma once

// オブジェクトID
enum class ID
{
	Default,		// 設定なし
	Player,			// プレイヤー
	Enemy,			// 敵
	Item,			// アイテム
	Length,			// 全ID数
};

// 重さ無し
constexpr double NON_WEIGHT = -1.0;