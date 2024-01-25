/*
 *	@File	Input.h
 *	@Brief	インプットシステム。
 *	@Date	2023-10-31
 *  @Author NakamuraRyo
 */

#pragma once
#ifndef INPUT
#define INPUT

class Input
{
private:
	// キーボード
	std::unique_ptr<DirectX::Keyboard>							m_keyboard;
	// マウス
	std::unique_ptr<DirectX::Mouse>								m_mouse;
	// 押された瞬間を検知する
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>	m_keyboardStateTracker;
	// 押された瞬間を検知する
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker>			m_mouseStateTracker;

private:

	// シングルトン
	Input();

public:

	/// <summary>
	/// インプットを参照
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>インプットシングルトン</returns>
	static Input* GetInstance()
	{
		static Input in;

		return &in;
	}

	~Input() = default;

	/// <summary>
	/// インプットシステムの更新
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>なし</returns>
	void Update();

	/// <summary>
	/// キーボードトラッカーを取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>キーボードトラッカー</returns>
	const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyTrack();

	/// <summary>
	/// マウストラッカーを取得
	/// </summary>
	/// <param name="引数無し"></param>
	/// <returns>マウストラッカー</returns>
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTrack();
};

#endif // INPUT