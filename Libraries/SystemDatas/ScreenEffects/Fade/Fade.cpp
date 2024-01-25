/*
 *	@File	Fade.cpp
 *	@Brief	画面遷移時のフェード処理。
 *	@Date	2023-06-27
 *  @Author NakamuraRyo
 */

#include "pch.h"

#include "../Transition/Transition.h"

#include "Fade.h"

 //==============================================================================
 // コンストラクタ
 //==============================================================================
Fade::Fade(float speed)
	: m_fadeValue{}			// フェードカウンタ
	, m_fadeSpeed{speed}	// フェード速度
	, m_filePath{L""}		// ファイルパス
	, is_fadeInFlag{}		// フェードインフラグ
	, is_fadeOutFlag{}		// フェードアウトフラグ
	, is_endFlag{}			// 終了判定フラグ
{
	m_fadeValue = MAX_NUM;
}

//==============================================================================
// デストラクタ
//==============================================================================
Fade::~Fade()
{
}

//==============================================================================
// 初期化処理
//==============================================================================
void Fade::Initialize()
{
	// トランジションを作成
	m_transition = std::make_unique<Transition>();
	m_transition->Create(m_filePath);
}

//==============================================================================
// 更新処理
//==============================================================================
void Fade::Update(XMVECTORF32 color)
{
	// フェードが終わっていたら処理しない
	if (is_endFlag) return;

	// 色をセット
	m_transition->SetColor(color);

	// フェードイン
	if (is_fadeInFlag)
	{
 		m_fadeValue -= m_fadeSpeed;
		if (m_fadeValue < MIN_NUM)
		{
			m_fadeValue = MIN_NUM;
		}
	}
	// フェードアウト
	if (is_fadeOutFlag)
	{
		m_fadeValue += m_fadeSpeed;
		if (m_fadeValue > MAX_NUM)
		{
			m_fadeValue = MAX_NUM;
		}
	}

	// 終了判定
	if (m_fadeValue == MAX_NUM || m_fadeValue == MIN_NUM)
	{
		is_endFlag = true;
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void Fade::Draw()
{
	// フェードが終わっていたら描画しない
	if (is_endFlag) return;

	// 描画関数
	m_transition->Render((m_fadeValue * SPEED) / MAX_NUM);
}

//==============================================================================
// フェードインを開始する
//==============================================================================
void Fade::SetFadeIn()
{
	Reset();
	is_endFlag = false;
	is_fadeInFlag = true;
	m_fadeValue = MAX_NUM;
}

//==============================================================================
// フェードアウトを開始する
//==============================================================================
void Fade::SetFadeOut()
{
	Reset();
	is_endFlag = false;
	is_fadeOutFlag = true;
	m_fadeValue = MIN_NUM;
}

//==============================================================================
// 開始前にリセットする
//==============================================================================
void Fade::Reset()
{
	m_fadeValue = 0.0f;
	is_fadeInFlag = false;
	is_fadeOutFlag = false;
	is_endFlag = false;
}
