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
#include "Game/Common/Water/Water.h"
#include "Game/SelectScene/Objects/BG_Select/BG_Select.h"
#include "SelectScene.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v

//==============================================================================
// �R���X�g���N�^
//==============================================================================
SelectScene::SelectScene(const int& selection)
	: IScene()						// ���N���X�̃R���X�g���N�^
	, m_stageSelection{ selection }	// �I��ԍ�
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

	// �^�C�g���ɖ߂�
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		ChangeScene(SCENE::TITLE);
	}

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
	for (int i = 0; i < MAX_SAMPLE_NUM; i++)
	{
		m_stage[i]->Draw(_context, *_states, _view, _projection);
	}

	// ���̕`��
	m_water->Draw(_view, _projection);

	// �w�i�̕`��
	m_backGround->Draw();

	// UI�̕`��
	m_ui->Draw();

	// �f�o�b�O�`��
#if _DEBUG
	//auto _grid = GetSystemManager()->GetGridFloor();
	//_grid->Draw(*_states, _view, _projection, Colors::Green);
	//DebugDraw(*_states);
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
	m_stage->reset();
	m_water.reset();
	m_backGround.reset();
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

	// ���쐬
	m_water = std::make_unique<Water>();

	// �w�i�쐬
	m_backGround = std::make_unique<BG_Select>();

	// �u���b�N�}�l�[�W��
	m_stage[0] = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
	m_stage[1] = std::make_unique<BlockManager>(L"Resources/Stages/sample2.json");
	m_stage[2] = std::make_unique<BlockManager>(L"Resources/Stages/sample3.json");
	m_stage[3] = std::make_unique<BlockManager>(L"Resources/Stages/sample4.json");
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void SelectScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Select1_Floating);
	m_adminCamera->SetActive(true);

	// �I�𒆂̔ԍ���ݒ�
	m_ui->SetSelectionNum(m_stageSelection);

	// ���̏����ݒ�
	m_water->Create(L"Resources/Textures/ShaderTex/water.png");

	// �w�i�̏����ݒ�
	m_backGround->Initialize();

	// �u���b�N�̏����ݒ�
	{
		// �v���C���[�h�ɐݒ肵�ď�����
		for (int i = 0; i < MAX_SAMPLE_NUM; i++)
		{
			m_stage[i]->SetPlay(true);
			m_stage[i]->Initialize();
		}

		// �I�t�Z�b�g��ݒ�
		m_stage[1]->SelectOffset(SimpleMath::Vector3(10.5f, 0.0f, 0.0f));
		m_stage[2]->SelectOffset(SimpleMath::Vector3(10.5f, 0.0f, -10.5f));
		m_stage[3]->SelectOffset(SimpleMath::Vector3(0.0f, 0.0f, -10.5f));

		// �s��v�Z
		for (int i = 0; i < MAX_SAMPLE_NUM; i++)
		{
			m_stage[i]->Update();
		}
	}
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 },	Colors::DarkGreen, L"SelectScene");
	_string.DrawFormatString(states, { 0,25 },	Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 },	Colors::DarkGreen, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 },	Colors::DarkGreen, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"StageNum::%d", m_stageSelection);
}

//==============================================================================
// �J�����̐؂�ւ�����
//==============================================================================
void SelectScene::ChangeAdminCamera()
{
	if(m_stageSelection == EDITOR_NUM)
		m_adminCamera->SetType(CameraType::Select0_Floating);
	if (m_stageSelection == 1)
		m_adminCamera->SetType(CameraType::Select1_Floating);
	if (m_stageSelection == 2)
		m_adminCamera->SetType(CameraType::Select2_Floating);
	if (m_stageSelection == 3)
		m_adminCamera->SetType(CameraType::Select3_Floating);
	if (m_stageSelection == 4)
		m_adminCamera->SetType(CameraType::Select4_Floating);
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
		if (m_stageSelection == 4)
			ChangeScene(SCENE::PLAY);
	}
}
