/*
 *  @File   ClearScene.cpp
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"											// �v���R���p�C���ς݃w�b�_�[
#include "Libraries/UserUtility.h"							// ���[�e�B���e�B
#include "Game/ClearScene/System/UI_Clear/UI_Clear.h"		// ���[�U�C���^�[�t�F�[�X
#include "Libraries/SystemDatas/Timer/Timer.h"				// �^�C�}�[

#include "Game/ClearScene/System/ScoreBoard/ScoreBoard.h"	// �X�R�A�{�[�h
#include "Game/ClearScene/Objects/MomentCanv/MomentCanv.h"	// �v���C�V�[���̃X�N�V���\��
#include "Game/ClearScene/Objects/BG_Clear/BG_Clear.h"		// �w�i
#include "Game/ClearScene/Objects/Tape/Tape.h"				// �e�[�v�I�u�W�F�N�g
#include "Game/ClearScene/Objects/Seal/Seal.h"				// �V�[���I�u�W�F�N�g

#include "ClearScene.h"										// �N���A�V�[��

// �G�C���A�X�錾
using KeyCode = Keyboard::Keys;					// �L�[�R�[�h
using RepeatType = SoundManager::SE_MODE;		// �T�E���h�̃^�C�v
using MouseClick = Mouse::ButtonStateTracker;	// �}�E�X�̃N���b�N
using Selection = UI_Clear::SELECT;				// ���̑I��

// �R���X�g���N�^
ClearScene::ClearScene(float time, int coins, int stage, int max)
	:
	IScene(),					// ���N���X�̃R���X�g���N�^
	m_clearTime(time),			// �N���A�^�C��
	m_collectedCoin(coins),		// �W�߂��R�C����
	m_stageNumber(stage),		// �X�e�[�W�ԍ�
	m_maxNumber(max)			// �ő�X�e�[�W�ԍ�
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearScene�̃R���X�g���N�^���Ă΂�܂����B\n");

	// �\�����E�l�ŃN�����v
	m_clearTime = UserUtility::Clamp(m_clearTime, 0.0f, 99.0f);
	m_collectedCoin = UserUtility::Clamp(m_collectedCoin, 0, 99);
}

// �f�X�g���N�^
ClearScene::~ClearScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearScene�̃f�X�g���N�^���Ă΂�܂����B\n");
	Finalize();
}

// ������
void ClearScene::Initialize()
{
	// ��ʈˑ��̏�����
	CreateWDResources();

	// �ϐ��̏�����
	SetSceneValues();

	// �{�����[���ݒ�E���ʍĐ��J�n(BGM�E����)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_BGM_CLEAR, 0.5f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_CLEAR, RepeatType::LOOP);
}

// �X�V
void ClearScene::Update()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// �Z���N�g�ɖ߂�
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		ChangeScene(SCENE::SELECT);
	}

	// �V�[���J��
	if (IsCanUpdate())
	{
		// ���[�����g�L�����o�X�̍X�V
		m_momentCanv->Update();

		// ���[�����g�L�����o�X���܂������Ă�����UI�̏��������Ȃ�
		if (not m_momentCanv->IsEndMoving()) return;

		// �^�C���E�R�C���̃X�R�A���X�V����
		m_direction->Update();
		if (m_direction->Alarm())
		{
			m_coinBoard->SetNumber(m_collectedCoin);
			m_timeBoard->SetNumber(static_cast<int>(m_clearTime));
		}
		else
		{
			m_coinBoard->SetNumber(static_cast<int>(UserUtility::Random(10.0, 60.0)));
			m_timeBoard->SetNumber(static_cast<int>(UserUtility::Random(10.0, 60.0)));
		}

		// UI�̍X�V
		m_ui->Update();

		// UI�̈ړ����܂��I����Ă��Ȃ���Ώ��������Ȃ�
		if (not m_ui->IsEndMoving()) return;

		// ���̑J�ڂ�I������
		SceneSelection();
	}
}

// �`��
void ClearScene::Draw()
{
	// �w�i�̕`��
	m_backGround->Draw();

	// ���[�����g�L�����o�X�̃��N�g�Ɗg�嗦�A���S�ʒu
	RECT_U rect =
		RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));
	SimpleMath::Vector2 origin = FULL_HD * 0.5f;

	// ���[�����g�L�����o�X�̕`��
	m_momentCanv->Draw(SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, origin, rect);

	if (m_momentCanv->IsEndMoving())
	{
		// �e�[�v�̕`��
		m_tape[0]->Draw();
		m_tape[1]->Draw();

		// �V�[���̕`��
		m_seal[Sticker::Coin]->Draw();
		m_seal[Sticker::Clock]->Draw();

		// �{�[�h�̕`��
		m_coinBoard->Draw();
		m_timeBoard->Draw();
	}

	// UI�̕`��
	m_ui->Draw();

	// �f�o�b�O�`��
#ifdef _DEBUG
	//DebugDraw(*_states);
#endif
}

// �I��
void ClearScene::Finalize()
{
	m_momentCanv.reset();
	m_ui.reset();
	m_direction.reset();
	m_coinBoard.reset();
	m_timeBoard.reset();
	m_backGround.reset();
	m_tape->reset();
	m_seal->reset();
}

// ��ʁA�f�o�C�X�ˑ��̏�����
void ClearScene::CreateWDResources()
{
	// ���[�����g�L�����o�X�쐬
	m_momentCanv = std::make_unique<MomentCanv>(GetWindowSize() / FULL_HD);

	// UI�쐬
	m_ui = std::make_unique<UI_Clear>(GetWindowSize(), FULL_HD);

	// �X�R�A�{�[�h�쐬
	m_coinBoard = std::make_unique<ScoreBoard>();
	m_timeBoard = std::make_unique<ScoreBoard>();

	// �f�B���N�g�^�C�}�[�쐬(3�b)
	m_direction = std::make_unique<Timer>(Timer::Mode::limited, 3.0f);

	// �w�i�쐬
	m_backGround = std::make_unique<BG_Clear>();

	// �e�[�v�쐬
	m_tape[0] = std::make_unique<Tape>();
	m_tape[1] = std::make_unique<Tape>();

	// �V�[���쐬
	m_seal[Sticker::Coin] = std::make_unique<Seal>(L"Resources/Textures/UI_Clear/coinSeal.dds");
	m_seal[Sticker::Clock] = std::make_unique<Seal>(L"Resources/Textures/UI_Clear/clockSeal.dds");
}

// �V�[�����̕ϐ��������֐�
void ClearScene::SetSceneValues()
{
	// ���[�����g�L�����o�X�̏�����
	m_momentCanv->Initialize();

	// �w�i�̏�����
	m_backGround->Initialize();

	// �X�R�A�{�[�h�̏�����(1�������Ԋu��������)
	m_coinBoard->Initialize({ 1500.0f,100.0f }, UserUtility::ColorsVector::WHITE,
		SimpleMath::Vector2::One, GetWindowSize() / FULL_HD, 1.0);
	m_timeBoard->Initialize({ 1500.0f,250.0f }, UserUtility::ColorsVector::WHITE,
		SimpleMath::Vector2::One, GetWindowSize() / FULL_HD, 1.0);

	// �e�[�v�̏�����
	m_tape[0]->Initialize({ 110.0f,460.0f }, SimpleMath::Vector2::One,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-55.0f));
	m_tape[1]->Initialize({ 1150.0f,530.0f }, SimpleMath::Vector2::One,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-60.0f));

	// �V�[���̏�����
	m_seal[Sticker::Coin]->Initialize({ 1400.0f, 160.0f }, SimpleMath::Vector2::One * 0.5f,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-55.0f));
	m_seal[Sticker::Clock]->Initialize({ 1420.0f, 312.0f }, SimpleMath::Vector2::One * 0.4f,
		GetWindowSize() / FULL_HD, XMConvertToRadians(-53.0f));

	// �^�C�}�[���J�n����
	m_direction->Start();
}

// �f�o�b�O�`��
void ClearScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// �����̕`��
	string.DrawFormatString(states, { 0,0 }, Colors::DarkGreen, L"ClearScene");
	string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Time::%.2f",m_clearTime);
	string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"Coin::%.d",m_collectedCoin);
	string.DrawFormatString(states, { 0,125 }, Colors::DarkGreen, L"Stage::%.d", m_stageNumber);
	string.DrawFormatString(states, { 0,150 }, Colors::DarkGreen, L"Direc::%.2f", m_direction->GetCount());
}

// �V�[���I��
void ClearScene::SceneSelection()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// �V�[����I������
	auto selection = m_ui->GetSelecion();
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		UserUtility::Increment(&selection);	// �C���N�������g
	}
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		UserUtility::Decrement(&selection);	// �f�N�������g
	}
	selection = UserUtility::LoopClamp(selection, Selection::NEXT, Selection::STAGES);
	m_ui->SetSelection(selection);

	// ���̑J�ڂ�����
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Space) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Z))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		switch (m_ui->GetSelecion())
		{
		case Selection::NEXT:
			m_stageNumber++;
			m_stageNumber = UserUtility::LoopClamp(m_stageNumber, 1, m_maxNumber);
			ChangeScene(SCENE::PLAY);
			break;
		case Selection::RESTART:
			ChangeScene(SCENE::PLAY);
			break;
		case Selection::STAGES:
			ChangeScene(SCENE::SELECT);
		default:
			break;
		}
	}
}
