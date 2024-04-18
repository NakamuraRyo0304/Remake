/*
 *	@File	GameMain.cpp
 *	@Brief	�Q�[�����[�v�������N���X
 *	@Date	2023-03-31
 *  @Author NakamuraRyo
 */

#include "pch.h"
#include "GameMain.h"
#include "Libraries/SystemDatas/ScreenEffects/Fade/Fade.h"
#ifdef _DEBUG
#include "Libraries/SystemDatas/DrawString/DrawString.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#endif

// �萔�̐ݒ�
const wchar_t* GameMain::FADE_TEXTURE_PATH = L"Resources/Textures/Transitions/Rule_Haze.png";
const XMVECTORF32 GameMain::FADE_COLOR = Colors::LightSkyBlue;
const float GameMain::PLAY_FADE_SPEED = 2.0f;

// �V�[���̃C���N���[�h
#include "TitleScene/TitleScene.h"
#include "SelectScene/SelectScene.h"
#include "Editor/Editor.h"
#include "PlayScene/PlayScene.h"
#include "ClearScene/ClearScene.h"

// �R���X�g���N�^
GameMain::GameMain()
	:
	m_nextScene(SCENE::TITLE),		// ����̃V�[��
	m_prevScene(SCENE::NONE),		// �O��̃V�[��
	m_screenSize(),					// �X�N���[���T�C�Y
	m_stageNumber(1),				// �X�e�[�W�ԍ�
	m_clearTime(0.0f),				// �N���A����
	m_collectedCoin(0),				// �W�߂��R�C����
	m_maxNumber(999)				// �ő�X�e�[�W�ԍ�
{
	// �J�[�\�����\��
	ShowCursor(false);

	// �^�C�}�[�v���J�n
#ifdef _DEBUG
	m_timer = std::make_unique<Timer>(Timer::Mode::infinited);
	m_timer->Start();
	Debug::DrawString::GetInstance().DebugLog(L"�^�C�}�[�v���J�n�I\n");
#endif

}

// �f�X�g���N�^
GameMain::~GameMain()
{
	Finalize();

	// �J�[�\����\��
	ShowCursor(true);
}

// ������
void GameMain::Initialize()
{
	// �V�[���쐬
	CreateScene();

	// �t�F�[�h�C��
	m_fade->SetFadeIn();
}

// �X�V
void GameMain::Update()
{
	// �^�C�}�[�X�V
#ifdef _DEBUG
	m_timer->Update();
#endif

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

// �`��
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

// �I��
void GameMain::Finalize()
{
	m_nowScene.reset();
	m_fade.reset();

	// �^�C�}�[�v���X�g�b�v
#ifdef _DEBUG
	m_timer->Stop();
	Debug::DrawString::GetInstance().DebugLog(L"�^�C�}�[�v���I���I\n");
	int minite = static_cast<int>(m_timer->GetCount() / 60.0f);
	int second = static_cast<int>(m_timer->GetCount()) % 60;
	std::wstring output = L"�N�����Ԃ�" + std::to_wstring(minite) + L"��" + std::to_wstring(second) + L"�b\n";
	Debug::DrawString::GetInstance().DebugLog(output.c_str());
#endif
}

// �V�[���쐬
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
			m_nowScene = std::make_unique<SelectScene>(m_stageNumber);

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
			m_nowScene = std::make_unique<ClearScene>(
				m_clearTime, m_collectedCoin, m_stageNumber, m_maxNumber);

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

	// ���������ݒ�ɖ߂�
	SoundManager::GetInstance()->InitAllSounds();

	// �쐬�����V�[����������
	m_nowScene->SetWindowSize(m_screenSize);
	m_nowScene->Initialize();

	// �t�F�[�h�C��
	m_fade->SetFadeIn();

	// ���ւ̃V�[������������
	m_nextScene = SCENE::NONE;
}

// �V�[���̍폜
void GameMain::DeleteScene()
{
	// �V�[�����쐬����Ă��Ȃ���Ώ������Ȃ�
	if (not m_nowScene) return;

	// �V�[���Ԃ̒l�󂯓n���́@�@<<��������

	// �Z���N�g�V�[�� ----> �v���C�V�[��
	// �����F�I�����ꂽ�X�e�[�W�ԍ��𑗐M
	if (m_prevScene == SCENE::SELECT && m_nextScene == SCENE::PLAY)
	{
		m_stageNumber   = CastSceneType<SelectScene>(m_nowScene)->GetSelectedNumber();
		m_maxNumber     = CastSceneType<SelectScene>(m_nowScene)->GetMaxNumber();
	}
	// �N���A�V�[�� ----> �v���C�V�[��
	// �����F���̃X�e�[�W�ԍ��𑗐M�i�ő�ɂȂ�����P�ɖ߂��j
	if (m_prevScene == SCENE::CLEAR && m_nextScene == SCENE::PLAY)
	{
		m_stageNumber   = CastSceneType<ClearScene>(m_nowScene)->GetStageNumber();
	}

	// �v���C�V�[�� ----> �N���A�V�[��
	// �����F�X�e�[�W�ԍ��A�N���A���ԁA�l���R�C���𑗐M
	if (m_prevScene == SCENE::PLAY && m_nextScene == SCENE::CLEAR)
	{
		m_clearTime     = CastSceneType<PlayScene>(m_nowScene)->GetGameTimer();
		m_collectedCoin = CastSceneType<PlayScene>(m_nowScene)->GetCollectedCoin();
		m_stageNumber   = CastSceneType<PlayScene>(m_nowScene)->GetStageNumber();
	}

	// �V�[���Ԃ̒l�󂯓n���́@�@<<�����܂�


	// ���V�[���̏I������
	if (m_fade->GetFadeValue() >= m_fade->GetMaxValue())
	{
		m_nowScene->Finalize();
		m_nowScene.reset();
		m_prevScene = m_nextScene;
	}
	else
	{
		m_fade->SetFadeOut();
	}
}

// ��ʁA�f�o�C�X�ˑ��̏�����
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