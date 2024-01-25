/*
 *	@File	Button.cpp
 *	@Brief	マウスクリックで動作するボタン。
 *	@Date	2023-01-10
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/Input/Input.h"
#include "Button.h"

//==============================================================================
// コンストラクタ
//==============================================================================
Button::Button(const wchar_t* name, const wchar_t* image)
	: m_name{ name }
	, m_correctionPosition{}
{
	// 画像の設定
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(name, image);
}

//==============================================================================
// デストラクタ
//==============================================================================
Button::~Button()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化処理
//==============================================================================
void Button::Initialize(SimpleMath::Vector2 position, SimpleMath::Vector2 rate, RECT_U rect,
	SimpleMath::Vector2 screenRatio, XMVECTORF32 color)
{
	// 座標を設定
	m_position = position * screenRatio;

	// ステータスを初期化
	m_states = State::Release;

	// 拡大率を設定
	m_rate = rate * screenRatio;

	// 色を設定
	m_color = color;

	// 画像サイズを設定
	m_size = rect;
}

//==============================================================================
// 更新
//==============================================================================
void Button::Update()
{
	auto& _ms = Mouse::Get();
	auto& _mt = Input::GetInstance()->GetMouseTrack();

	float _right = static_cast<float>(m_size.right * m_rate.x);
	float _left = static_cast<float>(m_size.bottom * m_rate.y);

	// 範囲外に行ったらリリース
	if (m_position.x < _ms.GetState().x && _ms.GetState().x < m_position.x + _right &&
		m_position.y < _ms.GetState().y && _ms.GetState().y < m_position.y + _left)
	{
		// ボタンをクリックする
		if (_mt->leftButton == Mouse::ButtonStateTracker::PRESSED)
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

	// ボタンの状態を更新
	ChangeButton();
}

//==============================================================================
// 描画
//==============================================================================
void Button::Draw()
{
	m_sprite->DrawTexture(m_name, m_position + m_correctionPosition, m_color, m_rate, { 0,0 } , m_size);
}

//==============================================================================
// ボタンの状態を変更する
//==============================================================================
void Button::ChangeButton()
{
	switch (m_states)
	{
	case Button::State::Release:
		m_color = SimpleMath::Color(m_color.x, m_color.y, m_color.z, 1.0f);
		break;
	case Button::State::Hover:
		m_color = SimpleMath::Color(m_color.x, m_color.y, m_color.z, 0.8f);
		break;
	case Button::State::Push:
		m_color = SimpleMath::Color(m_color.x, m_color.y, m_color.z, 0.6f);
		break;
	default:
		break;
	}
}

