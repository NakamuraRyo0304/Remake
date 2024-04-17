/*
 *	@File	Button.cpp
 *	@Brief	マウスクリックで動作するボタン。
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Libraries/UserUtility.h"
#include "Button.h"

// コンストラクタ
Button::Button(const wchar_t* name, const wchar_t* image)
	:
	m_name(name),					// 名前
	m_baseRate(),					// 倍率
	m_position(),					// 座標
	m_adder(),						// 加算座標
	m_screenRate(),					// スクリーン倍率
	m_size(),						// 切り取りサイズ
	m_states{ State::Release }		// ボタンの状態
{
	// 画像の設定と作成
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(name, image);
}

// デストラクタ
Button::~Button()
{
	m_sprite.reset();
}

// 初期化
void Button::Initialize(SimpleMath::Vector2 position, SimpleMath::Vector2 rate, RECT_U rect,
	SimpleMath::Vector2 screenRate, XMVECTORF32 color)
{
	// 座標を設定
	m_position = position * screenRate;
	// ステータスを初期化
	m_states = State::Release;
	// 拡大率を設定
	m_screenRate = screenRate;
	m_baseRate = m_rate = rate * screenRate;
	// 色を設定
	m_color = color;
	// 画像サイズを設定
	m_size = rect;
}

// 更新
void Button::Update()
{
	auto& ms = Mouse::Get();
	auto& mt = Input::GetInstance()->GetMouseTrack();

	float right = static_cast<float>(m_size.right * m_rate.x);
	float left = static_cast<float>(m_size.bottom * m_rate.y);

	// 範囲外に行ったらリリース
	SimpleMath::Vector2 addPos = m_adder * m_screenRate;
	if ((m_position + addPos).x < ms.GetState().x && ms.GetState().x < (m_position + addPos).x + right &&
		(m_position + addPos).y < ms.GetState().y && ms.GetState().y < (m_position + addPos).y + left)
	{
		// ボタンをクリックする
		if (mt->leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			m_states = State::Push;
		}
		else
		{
			m_states = State::Hover;
		}
	}
	else
	{
		m_states = State::Release;
	}
}

// 描画
void Button::Draw()
{
	SimpleMath::Vector2 addPos = m_adder * m_screenRate;
	m_sprite->DrawTexture(m_name, m_position + addPos, m_color, m_rate, { 0,0 } , m_size);
}

