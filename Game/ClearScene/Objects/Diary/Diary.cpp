/*
 *  @File   Diary.cpp
 *  @Brief  ���L�B
 *  @Date   2024-04-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "Libraries/UserUtility.h"
#include "Diary.h"

// �R���X�g���N�^
Diary::Diary()
	:
	m_color(UserUtility::ColorsVector::BLACK)	// �F
{
	m_sprite = std::make_unique<DrawSprite>();
	m_color.w = 0.0f;	// �A���t�@���O�ɂ���
}

// �f�X�g���N�^
Diary::~Diary()
{
	m_sprite.reset();
}

// ������
void Diary::Initialize(float time, int collect, int maxCoin)
{
	// ���ꂼ��̊������v�Z����
	std::wstring times = CalcTimePer(time);
	std::wstring coins = CalcCoinPer(collect, maxCoin);

	// �摜�쐬
	m_sprite->MakeSpriteBatch();
	m_sprite->AddTextureData(L"Time", times);
	m_sprite->AddTextureData(L"Coin", coins);
	m_sprite->AddTextureData(L"Note", L"Resources/Textures/Diary/Note.dds");

}

// �X�V
void Diary::Update()
{
	// �A���t�@���t�F�[�h�C��
	m_color.w = UserUtility::Lerp(m_color.w, 1.0f);
}

// �`��
void Diary::Draw()
{
	m_sprite->DrawTexture(L"Note", { 50.0f,864.0f }, UserUtility::ColorsVector::WHITE,
		SimpleMath::Vector2::One, SimpleMath::Vector2::Zero, { 0,0,1216,192 });
	m_sprite->DrawTexture(L"Time", { 50.0f,928.0f }, m_color,
		SimpleMath::Vector2::One, SimpleMath::Vector2::Zero, { 0,0,1216,64 });
	m_sprite->DrawTexture(L"Coin", { 50.0f,972.0f }, m_color,
		SimpleMath::Vector2::One, SimpleMath::Vector2::Zero, { 0,0,1216,64 });
}

// ���Ԃ��當������擾
std::wstring Diary::CalcTimePer(const float& time) const
{
    if (time >= 30.0f) // 30�b
        return L"Resources/Textures/Diary/TextTimeMax.dds"; // "����"
    else if (time >= 15.0f) // 15�b
        return L"Resources/Textures/Diary/TextTimeMid.dds"; // "����"
    else
        return L"Resources/Textures/Diary/TextTimeMin.dds"; // "�Z��"
}

// �R�C���̎擾�����當������擾
std::wstring Diary::CalcCoinPer(const int& collect, const int& max) const
{
    float percent = static_cast<float>(collect) / static_cast<float>(max);

    if (percent >= 0.8f) // 80%
        return L"Resources/Textures/Diary/TextCoinMax.dds"; // "����"
    else if (percent >= 0.5f) // 50%
        return L"Resources/Textures/Diary/TextCoinMid.dds"; // "���傤��"
    else
        return L"Resources/Textures/Diary/TextCoinMin.dds"; // "���Ȃ�"
}
