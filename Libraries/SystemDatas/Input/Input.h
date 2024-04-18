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
public:

	// キーボードトラッカーを取得
	const std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>& GetKeyTrack();
	// マウストラッカーを取得
	const std::unique_ptr<DirectX::Mouse::ButtonStateTracker>& GetMouseTrack();

	// インスタンスを取得
	static Input* GetInstance()
	{
		static Input instance;
		return &instance;
	}
	// デストラクタ
	~Input() = default;
	// 更新
	void Update();

private:

	// コンストラクタ
	Input();

private:

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	// マウス
	std::unique_ptr<DirectX::Mouse> m_mouse;
	// キーが押された瞬間を検知する
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardStateTracker;
	// マウスが押された瞬間を検知する
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> m_mouseStateTracker;

};

#endif // INPUT