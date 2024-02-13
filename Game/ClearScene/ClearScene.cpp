/*
 *  @File   ClearScene.cpp
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/ClearScene/System/MomentCanv/MomentCanv.h"
#include "Game/ClearScene/System/ScoreBoard/ScoreBoard.h"
#include "Game/ClearScene/System/UI_Clear/UI_Clear.h"
#include "Libraries/SystemDatas/Timer/Timer.h"
#include "ClearScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector4 ClearScene::BLACK_COLOR = SimpleMath::Vector4(0, 0, 0, 1);	// ���F

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

		// �R�C���̃X�R�A���X�V����
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

	// ���[�����g�L�����o�X�̃��N�g�Ɗg�嗦�A���S�ʒu
	RECT_U _rectMC =
		RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));
	SimpleMath::Vector2 _originMC = GetFullHDSize() * 0.5f;

	// ���[�����g�L�����o�X�̕`��
	m_momentCanv->Draw(SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, _originMC, _rectMC);

	// �X�R�A�{�[�h�̕`��
	if (m_momentCanv->IsEndMoving())
	{
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
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void ClearScene::SetSceneValues()
{
	// ���[�����g�L�����o�X�̏�����
	m_momentCanv->Initialize();

	// �X�R�A�{�[�h�̏�����(1.5�������Ԋu��������)
	m_coinBoard->Initialize({ 1500.0f,100.0f }, BLACK_COLOR,
		SimpleMath::Vector2::One, GetWindowSize() / GetFullHDSize(), 1.5);
	m_timeBoard->Initialize({ 1500.0f,250.0f }, BLACK_COLOR,
		SimpleMath::Vector2::One, GetWindowSize() / GetFullHDSize(), 1.5);
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
