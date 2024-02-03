/*
 *	@File	SelectScene.cpp
 *	@Brief	�Z���N�g�V�[���B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/SelectScene/System/UI_Select/UI_Select.h"
#include "Game/SelectScene/Objects/Sky_Select/Sky_Select.h"
// �I�u�W�F�N�g
#include "Game/Common/BlockManager/BlockManager.h"

#include "SelectScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const int SelectScene::MAX_SAMPLE_NUM = 3;		// �T���v���X�e�[�W��

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v

//==============================================================================
// �R���X�g���N�^
//==============================================================================
SelectScene::SelectScene()
	: IScene()				// ���N���X�̃R���X�g���N�^
	, m_stageSelection{ 1 }	// �X�e�[�W�P����X�^�[�g
{
	Debug::DrawString::GetInstance().DebugLog(L"SelectScene�̃R���X�g���N�^���Ă΂�܂����B\n");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
SelectScene::~SelectScene()
{
}

//==============================================================================
// ����������
//==============================================================================
void SelectScene::Initialize()
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
void SelectScene::Update()
{
	auto _input = Input::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UI�̍X�V
	m_ui->Update();

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �X�e�[�W�̑I��
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
			_input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
		{
			m_stageSelection++;
		}
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
			_input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
		{
			m_stageSelection--;
		}

		// ���[�v�N�����v
		m_stageSelection = UserUtility::LoopClamp(m_stageSelection, EDITOR_NUM, MAX_SAMPLE_NUM);
		m_ui->SetSelectionNum(m_stageSelection);
	}

	// �J�����̐؂�ւ�����
	ChangeAdminCamera();

	// �V�[���Z���N�g
	SelectNext();

	// �J�����̍X�V
	m_adminCamera->Update();

	// �X�J�C���̍X�V
	m_sky->Update();
	m_sky->SetPosition(m_adminCamera->GetPosition());

	// �u���b�N�̍X�V
	m_blockManager->Update();
}

//==============================================================================
// �`�揈��
//==============================================================================
void SelectScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// �X�e�[�W�I�u�W�F�N�g�̕`��
	m_sky->Draw(_context, *_states, _view, _projection);

	// �u���b�N�̕`��
	m_blockManager->Draw(_context, *_states, _view, _projection);

	// UI�̕`��
	m_ui->Draw();

	// �f�o�b�O�`��
#ifdef _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif
}

//==============================================================================
// �I������
//==============================================================================
void SelectScene::Finalize()
{
	m_adminCamera.reset();
	m_ui.reset();
	m_sky.reset();
	m_blockManager.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void SelectScene::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// UI�쐬
	m_ui = std::make_unique<UI_Select>(GetWindowSize(), GetFullHDSize());

	// �X�J�C���쐬
	m_sky = std::make_unique<Sky_Select>();

	// �u���b�N�}�l�[�W��
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
	m_blockManager->SetPlay(true);
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void SelectScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);

	// �I�𒆂̔ԍ���ݒ�
	m_ui->SetSelectionNum(m_stageSelection);

	// �u���b�N�̏�����
	m_blockManager->Initialize();
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 }, Colors::Yellow, L"SelectScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Yellow, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Yellow, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Yellow, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Yellow, L"StageNum::%d", m_stageSelection);
}

//==============================================================================
// �J�����̐؂�ւ�����
//==============================================================================
void SelectScene::ChangeAdminCamera()
{
	if(m_stageSelection == EDITOR_NUM)
		m_adminCamera->SetType(CameraType::Title_FixedPoint);
	if (m_stageSelection == 1)
		m_adminCamera->SetType(CameraType::Select1_Floating);
	if (m_stageSelection == 2)
		m_adminCamera->SetType(CameraType::Select2_Floating);
	if (m_stageSelection == 3)
		m_adminCamera->SetType(CameraType::Select3_Floating);
}

//==============================================================================
// �V�[����I������
//==============================================================================
void SelectScene::SelectNext()
{
	auto _input = Input::GetInstance();

	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
	{
		// �X�e�[�W�����
		if (m_stageSelection == EDITOR_NUM)
			ChangeScene(SCENE::EDIT);

		// �X�e�[�W���v���C����
		if (m_stageSelection == 1)
			ChangeScene(SCENE::PLAY);
		if (m_stageSelection == 2)
			ChangeScene(SCENE::PLAY);
		if (m_stageSelection == 3)
			ChangeScene(SCENE::PLAY);
	}
}
