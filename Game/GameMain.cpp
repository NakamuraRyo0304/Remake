/*
 *	@File	GameMain.cpp
 *	@Brief	�Q�[�����[�v�������N���X
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "GameMain.h"
#include "Libraries/SystemDatas/ScreenEffects/Fade/Fade.h"
#include "Libraries/UserUtility.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const wchar_t* GameMain::FADE_TEXTURE_PATH = L"Resources/Textures/Transitions/Rule_Haze.png";
const XMVECTORF32 GameMain::FADE_COLOR = Colors::White;
const float GameMain::PLAY_FADE_SPEED = 2.0f;

//==============================================================================
// �V�[���̃C���N���[�h
//==============================================================================
#include "TitleScene/TitleScene.h"
#include "SelectScene/SelectScene.h"
#include "Editor/Editor.h"
#include "PlayScene/PlayScene.h"
#include "ClearScene/ClearScene.h"

//==============================================================================
// �R���X�g���N�^
//==============================================================================
GameMain::GameMain()
	: m_nextScene{ SCENE::TITLE }		// ����̃V�[��
	, m_prevScene{ SCENE::NONE }		// �O��̃V�[��
	, m_nowScene{ nullptr }				// ���̃V�[���|�C���^
	, m_screenSize{}					// �X�N���[���T�C�Y
	, m_stageNumber{ 1 }				// �X�e�[�W�ԍ�
{
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
GameMain::~GameMain()
{
	Finalize();
}

//==============================================================================
// ����������
//==============================================================================
void GameMain::Initialize()
{
	// �V�[���쐬
	CreateScene();

	// �t�F�[�h�C��
	m_fade->SetFadeIn();
}

//==============================================================================
// �X�V����
//==============================================================================
void GameMain::Update()
{
	// �t�F�[�h�̍X�V
	m_fade->Update(FADE_COLOR);

	// ���̃V�[�����ݒ肳��Ă�����V�[���؂�ւ�
	if (m_nextScene != SCENE::NONE && m_fade->GetEndFlag())
	{
		// �V�[���폜
		DeleteScene();

		// �V�[���쐬
		CreateScene();
	}

	// ���̂�����΍X�V
	if (m_nowScene)
	{
		// �V�[���̍X�V����
		m_nowScene->Update();

		// �t�F�[�h�̒l���Z�b�g
		m_nowScene->SetFadeValue(m_fade->GetFadeValue());

		// �t�F�[�h���I����Ă�����V�[����؂�ւ���
		if (m_fade->GetEndFlag())
		{
			m_nextScene = m_nowScene->GetNextScene();
		}
		else
		{
			m_nowScene->StopNextScene();
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void GameMain::Draw()
{
	// ���Ԃ�����Ε`��
	if (m_nowScene)
	{
		m_nowScene->Draw();
	}
	// �t�F�[�h�̕`��
	m_fade->Draw();
}

//==============================================================================
// �I������
//==============================================================================
void GameMain::Finalize()
{
	m_nowScene.reset();
	m_fade.reset();
}

//==============================================================================
// �V�[���쐬
//==============================================================================
void GameMain::CreateScene()
{
	// �V�[�����쐬����Ă���Ώ������Ȃ�
	if (m_nowScene) return;

	// TODO:�V�[���͂�������ǉ�
	switch (m_nextScene)
	{
		case SCENE::TITLE:		// �^�C�g���V�[��
		{
			m_nowScene = std::make_unique<TitleScene>();

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::SELECT:		// �Z���N�g�V�[��
		{
			m_nowScene = std::make_unique<SelectScene>();

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::EDIT:		// ����V�[��
		{
			m_nowScene = std::make_unique<Editor>();

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::PLAY:		// �Q�[���V�[��
		{
			m_nowScene = std::make_unique<PlayScene>(m_stageNumber);

			m_fade->SetFadeSpeed(PLAY_FADE_SPEED);
			break;
		}
		case SCENE::CLEAR:		// �N���A�V�[��
		{
			m_nowScene = std::make_unique<ClearScene>();

			m_fade->SetFadeSpeed(DEFAULT_FADE_SPEED);
			break;
		}
		case SCENE::EXIT:		// �Q�[���I��
		{
			if (m_fade->GetEndFlag()) { ExitApp(); }
			return;
		}
		default:
			break;
	}

	// �쐬�����V�[����������
	m_nowScene->SetWindowSize(m_screenSize);
	m_nowScene->Initialize();

	// �t�F�[�h�C��
	m_fade->SetFadeIn();

	// ���ւ̃V�[������������
	m_nextScene = SCENE::NONE;
}

//==============================================================================
// �V�[���̍폜
//==============================================================================
void GameMain::DeleteScene()
{
	// �V�[�����쐬����Ă��Ȃ���Ώ������Ȃ�
	if (not m_nowScene) return;


	//==============================================================================
	// �V�[���Ԃ̒l�󂯓n���͂����ōs��
	//==============================================================================

	// ���̃V�[���F�Q�[���V�[�� / �����F�Z���N�g�V�[������X�e�[�W�ԍ����擾����
	if (m_nextScene == SCENE::PLAY && m_prevScene == SCENE::SELECT)
	{
		m_stageNumber = CastSceneType<SelectScene>(m_nowScene)->GetSelectedNumber();
	}



	// ���V�[���̏I������
	if (m_fade->GetFadeValue() >= m_fade->GetMaxValue())
	{
		// ���V�[���̊��S�폜
		m_nowScene->Finalize();
		m_nowScene.reset();
		m_prevScene = m_nextScene;
	}
	else
	{
		m_fade->SetFadeOut();
	}
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void GameMain::CreateWDResources(const int& screenWidth, const int& screenHeight)
{
	// �X�N���[���T�C�Y�̐ݒ�
	m_screenSize.x = static_cast<float>(screenWidth);
	m_screenSize.y = static_cast<float>(screenHeight);

	// �t�F�[�h�̐ݒ�
	m_fade = std::make_unique<Fade>(DEFAULT_FADE_SPEED);
	m_fade->SetRuleTexture(FADE_TEXTURE_PATH);
	m_fade->Initialize();
}