/*
 *	@File	Fade.cpp
 *	@Brief	��ʑJ�ڎ��̃t�F�[�h�����B
 *	@Date	2023-06-27
 *  @Author NakamuraRyo
 */

#include "pch.h"

#include "../Transition/Transition.h"

#include "Fade.h"

 //==============================================================================
 // �R���X�g���N�^
 //==============================================================================
Fade::Fade(float speed)
	: m_fadeValue{}			// �t�F�[�h�J�E���^
	, m_fadeSpeed{speed}	// �t�F�[�h���x
	, m_filePath{L""}		// �t�@�C���p�X
	, is_fadeInFlag{}		// �t�F�[�h�C���t���O
	, is_fadeOutFlag{}		// �t�F�[�h�A�E�g�t���O
	, is_endFlag{}			// �I������t���O
{
	m_fadeValue = MAX_NUM;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Fade::~Fade()
{
}

//==============================================================================
// ����������
//==============================================================================
void Fade::Initialize()
{
	// �g�����W�V�������쐬
	m_transition = std::make_unique<Transition>();
	m_transition->Create(m_filePath);
}

//==============================================================================
// �X�V����
//==============================================================================
void Fade::Update(XMVECTORF32 color)
{
	// �t�F�[�h���I����Ă����珈�����Ȃ�
	if (is_endFlag) return;

	// �F���Z�b�g
	m_transition->SetColor(color);

	// �t�F�[�h�C��
	if (is_fadeInFlag)
	{
 		m_fadeValue -= m_fadeSpeed;
		if (m_fadeValue < MIN_NUM)
		{
			m_fadeValue = MIN_NUM;
		}
	}
	// �t�F�[�h�A�E�g
	if (is_fadeOutFlag)
	{
		m_fadeValue += m_fadeSpeed;
		if (m_fadeValue > MAX_NUM)
		{
			m_fadeValue = MAX_NUM;
		}
	}

	// �I������
	if (m_fadeValue == MAX_NUM || m_fadeValue == MIN_NUM)
	{
		is_endFlag = true;
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void Fade::Draw()
{
	// �t�F�[�h���I����Ă�����`�悵�Ȃ�
	if (is_endFlag) return;

	// �`��֐�
	m_transition->Render((m_fadeValue * SPEED) / MAX_NUM);
}

//==============================================================================
// �t�F�[�h�C�����J�n����
//==============================================================================
void Fade::SetFadeIn()
{
	Reset();
	is_endFlag = false;
	is_fadeInFlag = true;
	m_fadeValue = MAX_NUM;
}

//==============================================================================
// �t�F�[�h�A�E�g���J�n����
//==============================================================================
void Fade::SetFadeOut()
{
	Reset();
	is_endFlag = false;
	is_fadeOutFlag = true;
	m_fadeValue = MIN_NUM;
}

//==============================================================================
// �J�n�O�Ƀ��Z�b�g����
//==============================================================================
void Fade::Reset()
{
	m_fadeValue = 0.0f;
	is_fadeInFlag = false;
	is_fadeOutFlag = false;
	is_endFlag = false;
}
