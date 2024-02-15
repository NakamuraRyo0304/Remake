/*
 *  @File   ClearScene.cpp
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/ClearScene/System/ScoreBoard/ScoreBoard.h"
#include "Game/ClearScene/System/UI_Clear/UI_Clear.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#include "Libraries/UserUtility.h"
// �I�u�W�F�N�g
#include "Game/ClearScene/Objects/MomentCanv/MomentCanv.h"
#include "Game/ClearScene/Objects/BG_Clear/BG_Clear.h"
#include "Game/ClearScene/Objects/Tape/Tape.h"
#include "Game/ClearScene/Objects/Seal/Seal.h"
#include "ClearScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector4 ClearScene::WHITE = SimpleMath::Vector4(1, 1, 1, 1);	// ���F

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v
using MouseClick = Mouse::ButtonStateTracker;			// �}�E�X�̃N���b�N
using Selection = UI_Clear::SELECT;						// ���̑I��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
ClearScene::ClearScene(float time, int coins, int stage, int max)
	: IScene()						// ���N���X�̃R���X�g���N�^
	, m_clearTime{ time }			// �N���A�^�C��
	, m_collectedCoin{ coins }		// �W�߂��R�C����
	, m_stageNumber{ stage }		// �X�e�[�W�ԍ�
	, m_maxNumber{ max }			// �ő�X�e�[�W�ԍ�
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearScene�̃R���X�g���N�^���Ă΂�܂����B\n");

	// �\�����E�l�ŃN�����v
	m_clearTime = UserUtility::Clamp(m_clearTime, 0.0f, 99.0f);
	m_collectedCoin = UserUtility::Clamp(m_collectedCoin, 0, 99);
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
ClearScene::~ClearScene()
{
}

//==============================================================================
// ����������
//==============================================================================
void ClearScene::Initialize()
{
	// ��ʈˑ��̏�����
	CreateWDResources();

	// �ϐ��̏�����
	SetSceneValues();

	// BGM��炷
	//auto _se = SoundManager::GetInstance();
	//_se->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_TEST, RepeatType::LOOP);
}

//==============================================================================
// �X�V����
//==============================================================================
void ClearScene::Update()
{
	auto _input = Input::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// �V�[���J��
	if (IsCanUpdate())
	{
		// ���[�����g�L�����o�X�̍X�V
		m_momentCanv->Update();

		// ���[�����g�L�����o�X���܂������Ă�����UI�̏��������Ȃ�
		if (not m_momentCanv->IsEndMoving()) return;

		// �^�C���E�R�C���̃X�R�A���X�V����
		m_direction->Start();
		m_direction->Update(true);
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

//==============================================================================
// �`�揈��
//==============================================================================
void ClearScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();

	// �w�i�̕`��
	m_backGround->Draw();

	// ���[�����g�L�����o�X�̃��N�g�Ɗg�嗦�A���S�ʒu
	RECT_U _rectMC =
		RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));
	SimpleMath::Vector2 _originMC = GetFullHDSize() * 0.5f;

	// ���[�����g�L�����o�X�̕`��
	m_momentCanv->Draw(SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, _originMC, _rectMC);

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
	DebugDraw(*_states);
#endif
}

//==============================================================================
// �I������
//==============================================================================
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

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void ClearScene::CreateWDResources()
{
	// ���[�����g�L�����o�X�쐬
	m_momentCanv = std::make_unique<MomentCanv>(GetWindowSize() / GetFullHDSize());

	// UI�쐬
	m_ui = std::make_unique<UI_Clear>(GetWindowSize(), GetFullHDSize());

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

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void ClearScene::SetSceneValues()
{
	// ���[�����g�L�����o�X�̏�����
	m_momentCanv->Initialize();

	// �w�i�̏�����
	m_backGround->Initialize();

	// �X�R�A�{�[�h�̏�����(1�������Ԋu��������)
	m_coinBoard->Initialize({ 1500.0f,100.0f }, WHITE,
		SimpleMath::Vector2::One, GetWindowSize() / GetFullHDSize(), 1.0);
	m_timeBoard->Initialize({ 1500.0f,250.0f }, WHITE,
		SimpleMath::Vector2::One, GetWindowSize() / GetFullHDSize(), 1.0);

	// �e�[�v�̏�����
	m_tape[0]->Initialize({ 110.0f,460.0f }, SimpleMath::Vector2::One,
		GetWindowSize() / GetFullHDSize(), XMConvertToRadians(-55.0f));
	m_tape[1]->Initialize({ 1150.0f,530.0f }, SimpleMath::Vector2::One,
		GetWindowSize() / GetFullHDSize(), XMConvertToRadians(-60.0f));

	// �V�[���̏�����
	m_seal[Sticker::Coin]->Initialize({ 1400.0f, 160.0f }, SimpleMath::Vector2::One * 0.5f,
		GetWindowSize() / GetFullHDSize(), XMConvertToRadians(-55.0f));
	m_seal[Sticker::Clock]->Initialize({ 1420.0f, 312.0f }, SimpleMath::Vector2::One * 0.4f,
		GetWindowSize() / GetFullHDSize(), XMConvertToRadians(-53.0f));
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void ClearScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 }, Colors::DarkGreen, L"ClearScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Time::%.2f",m_clearTime);
	_string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"Coin::%.d",m_collectedCoin);
	_string.DrawFormatString(states, { 0,125 }, Colors::DarkGreen, L"Stage::%.d", m_stageNumber);
	_string.DrawFormatString(states, { 0,150 }, Colors::DarkGreen, L"Direc::%.2f", m_direction->GetCount());
}

//==============================================================================
// �V�[���I��
//==============================================================================
void ClearScene::SceneSelection()
{
	auto _input = Input::GetInstance();

	// �V�[����I������
	auto _selection = m_ui->GetSelecion();
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
		_input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
	{
		UserUtility::Increment(&_selection);	// �C���N�������g
	}
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
		_input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
	{
		UserUtility::Decrement(&_selection);	// �f�N�������g
	}
	_selection = UserUtility::LoopClamp(_selection, Selection::NEXT, Selection::STAGES);
	m_ui->SetSelection(_selection);

	// ���̑J�ڂ�����
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
	{
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
