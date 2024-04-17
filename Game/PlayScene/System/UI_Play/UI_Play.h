/*
 *	@File	UI_Play.h
 *	@Brief	プレイUI。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAY
#define UI_PLAY

// 親シーンクラス
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_CoinNum;
class UI_PlayArea;
class DrawKeys;
class DrawSprite;
class Button;
class UI_Play final : public IUserInterface
{
public:

	// コインの枚数を設定
	void SetCoinNum(const int& num) { m_coinNum = num; }
	// リトライボタンの状況取得
	bool IsPushRetry() const { return is_retryPush; }

	// コンストラクタ
	UI_Play(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	// デストラクタ
	~UI_Play();
	// 初期化
	void Initialize() override;
	// 更新
	void Update() override;
	// 描画
	void Draw() override;

public:

	// キーの名前
	enum KEY_NAME
	{
		WKEY,
		SKEY,
		AKEY,
		DKEY,

		Length__key
	};

private:

	// UIエリア
	std::unique_ptr<UI_PlayArea> m_area;
	// コイン数
	std::unique_ptr<UI_CoinNum> m_coins;
	// リトライボタン
	std::unique_ptr<Button> m_retryButton;
	// 判定フラグ
	bool is_retryPush;
	// キー描画
	std::map<KEY_NAME, std::unique_ptr<DrawKeys>> m_keys;
	// 画像描画
	std::unique_ptr<DrawSprite> m_sprite;
	DirectX::SimpleMath::Vector2 m_coinTexPos, m_cameraTexPos;
	// コイン数
	int m_coinNum;

};

#endif // UI_PLAY