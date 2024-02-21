/*
 *	@File	UI_Play.h
 *	@Brief	プレイUI。
 *	@Date	2023-01-25
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef UI_PLAY
#define UI_PLAY

//==============================================================================
// 親シーンクラス
//==============================================================================
#include "Game/Common/IUserInterface/IUserInterface.h"

class UI_CoinNum;
class UI_PlayArea;
class DrawKeys;
class DrawSprite;
class UI_Play final : public IUserInterface
{
public:

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

	// キー描画
	std::map<KEY_NAME, std::unique_ptr<DrawKeys>> m_keys;

	// 画像描画
	std::unique_ptr<DrawSprite> m_sprite;
	DirectX::SimpleMath::Vector2 m_coinTexPos;

	// コイン数
	int m_coinNum;

private:

	static const DirectX::SimpleMath::Vector4 WHITE;
	static const DirectX::SimpleMath::Vector4 RED;

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="scS">画面サイズ</param>
	/// <param name="mscS">最大サイズ</param>
	/// <returns>なし</returns>
	UI_Play(DirectX::SimpleMath::Vector2 scS, DirectX::SimpleMath::Vector2 mscs);
	~UI_Play();

	/// <summary>
	/// 初期化関数
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Draw() override;

	// コインの枚数を設定
	void SetCoinNum(const int& num) { m_coinNum = num; }
};

#endif // UI_PLAY