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

//==============================================================================
// コンストラクタ
//==============================================================================
Button::Button(const wchar_t* name, const wchar_t* image)
	: m_name{ name }
	, m_baseRate{}
	, m_position{}
	, m_adder{}
	, m_screenRate{}
	, m_size{}
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
	auto _addPosition = m_adder * m_screenRate;
	if ((m_position + _addPosition).x < _ms.GetState().x && _ms.GetState().x < (m_position + _addPosition).x + _right &&
		(m_position + _addPosition).y < _ms.GetState().y && _ms.GetState().y < (m_position + _addPosition).y + _left)
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
}

//==============================================================================
// 描画
//==============================================================================
void Button::Draw()
{
	auto _addPosition = m_adder * m_screenRate;
	m_sprite->DrawTexture(m_name, m_position + _addPosition, m_color, m_rate, { 0,0 } , m_size);
}

