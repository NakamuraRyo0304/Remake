/*
 *  @File   MomentCanv.cpp
 *  @Brief  クリアした瞬間の画像を表示する。
 *  @Date   2024-02-11
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/UserUtility.h"
#include "MomentCanv.h"

//==============================================================================
// 定数の設定
//==============================================================================
const SimpleMath::Vector2 MomentCanv::LAST_POSITION = { 640.0f,460.0f };		// 最終座標
const SimpleMath::Vector2 MomentCanv::OUT_POSITION = { -2000.0f, -1500.0f };	// 画面外座標
const float MomentCanv::LAST_ROTATE = XMConvertToRadians(-385.0f);				// 最終回転
const float MomentCanv::SPEED_TO_LAST = 0.1f;									// 速度

//==============================================================================
// コンストラクタ
//==============================================================================
MomentCanv::MomentCanv(SimpleMath::Vector2 screenRate)
	: m_position{}					// 座標
	, m_screenRate{ screenRate }	// 画面比率
{
	// スプライト描画の作成
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();
}

//==============================================================================
// デストラクタ
//==============================================================================
MomentCanv::~MomentCanv()
{
	m_sprite.reset();
}

//==============================================================================
// 初期化関数
//==============================================================================
void MomentCanv::Initialize()
{
	// スプライトの設定
	m_sprite->AddTextureData(L"PlayPic", L"Resources/Textures/ScreenShot/image.dds");

	// 画面外から始める
	m_position = OUT_POSITION * m_screenRate;
}

//==============================================================================
// 更新処理
//==============================================================================
void MomentCanv::Update()
{
	// 座標の移動
	m_position = UserUtility::Lerp(m_position, LAST_POSITION, SPEED_TO_LAST);

	// 画像の回転
	m_sprite->CreateRotation(L"PlayPic",
		UserUtility::Lerp(m_sprite->GetRotate(L"PlayPic"), LAST_ROTATE, SPEED_TO_LAST));
}

//==============================================================================
// 描画関数
//==============================================================================
void MomentCanv::Draw(SimpleMath::Vector4 color, SimpleMath::Vector2 rate,
	SimpleMath::Vector2 origin, RECT_U rect)
{
	m_sprite->DrawTexture(L"PlayPic",
		m_position * m_screenRate, color, rate, origin * m_screenRate, rect);
}
