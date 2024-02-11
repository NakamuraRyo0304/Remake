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

class DrawNumber;
class UI_PlayArea;
class UI_Play final : public IUserInterface
{
private:

	// 数字を描画する
	std::unique_ptr<DrawNumber> m_nums[4];

	// UIエリア
	std::unique_ptr<UI_PlayArea> m_area;

	// コイン数
	int m_coinNum, m_maxCoinNum;


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
	// コインの最大数を設定
	void SetCoinMaxNum(const int& num) { m_maxCoinNum = num; }

};

#endif // UI_PLAY