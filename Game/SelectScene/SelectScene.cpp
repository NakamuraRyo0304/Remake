/*
 *	@File	SelectScene.cpp
 *	@Brief	�Z���N�g�V�[���B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"											// �v���R���p�C���ς݃w�b�_�[
#include "Game/Cameras/AdminCamera/AdminCamera.h"			// �����J����
#include "Game/SelectScene/System/UI_Select/UI_Select.h"	// ���[�U�C���^�[�t�F�[�X

#include "Game/SelectScene/Objects/BG_Select/BG_Select.h"	// �w�i

#include "Game/Common/BlockManager/BlockManager.h"			// �u���b�N�Ǘ��N���X
#include "Game/Common/Water/Water.h"						// �C

#include "SelectScene.h"									// �Z���N�g�V�[��

// �G�C���A�X�錾
using KeyCode = Keyboard::Keys;				// �L�[�R�[�h
using CameraType = AdminCamera::Type;		// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;	// �T�E���h�̃^�C�v

// �R���X�g���N�^
SelectScene::SelectScene(const int& selection)
	:
	IScene(),						// ���N���X�̃R���X�g���N�^
	m_stageSelection(selection)		// �I��ԍ�
{
	Debug::DrawString::GetInstance().DebugLog(L"SelectScene�̃R���X�g���N�^���Ă΂�܂����B\n");
}

// �f�X�g���N�^
SelectScene::~SelectScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"SelectScene�̃f�X�g���N�^���Ă΂�܂����B\n");
	Finalize();
}

// ������
void SelectScene::Initialize()
{
	// ��ʈˑ��̏�����
	CreateWDResources();

	// �ϐ��̏�����
	SetSceneValues();

	// �{�����[���ݒ�E���ʍĐ��J�n(BGM�E����)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,  0.7f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,  RepeatType::LOOP);
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_SE_WAVE2, 0.7f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE2, RepeatType::LOOP);
}

// �X�V
void SelectScene::Update()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// �^�C�g���ɖ߂�
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		ChangeScene(SCENE::TITLE);
	}

	// UI�̍X�V
	m_ui->Update();

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �J�����̐؂�ւ�����
		ChangeAdminCamera();

		// �V�[���Z���N�g
		SelectNext();
	}

	// �J�����̍X�V
	m_adminCamera->Update();

	// �X�e�[�W�̍X�V
	for (int i = 0; i < MAX_SAMPLE_NUM; i++)
	{
		m_stage[i]->Update();
	}
}

// �`��
void SelectScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix view = m_adminCamera->GetView();
	SimpleMath::Matrix projection = m_adminCamera->GetProjection();

	// �u���b�N�̕`��
	for (int i = 0; i < MAX_SAMPLE_NUM; i++)
	{
		m_stage[i]->Draw(context, *states, view, projection);
	}

	// ���̕`��
	m_water->Draw(view, projection);

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

// �I��
void SelectScene::Finalize()
{
	m_adminCamera.reset();
	m_ui.reset();
	m_stage->reset();
	m_water.reset();
	m_backGround.reset();
}

// ��ʁA�f�o�C�X�ˑ��̏�����
void SelectScene::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// UI�쐬
	m_ui = std::make_unique<UI_Select>(GetWindowSize(), GetFullHDSize());

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

// �V�[�����̕ϐ��������֐�
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
		m_stage[1]->SetOffset(SimpleMath::Vector3(10.5f, 0.0f, 0.0f));
		m_stage[2]->SetOffset(SimpleMath::Vector3(10.5f, 0.0f, -10.5f));
		m_stage[3]->SetOffset(SimpleMath::Vector3(0.0f, 0.0f, -10.5f));
	}
}

// �f�o�b�O�`��
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// �����̕`��
	string.DrawFormatString(states, { 0,0 },	Colors::DarkGreen, L"SelectScene");
	string.DrawFormatString(states, { 0,25 },	Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 },	Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 },	Colors::DarkGreen, L"Timer::%.2f", timer.GetTotalSeconds());
	string.DrawFormatString(states, { 0,100 }, Colors::DarkGreen, L"StageNum::%d", m_stageSelection);
}

// �J�����̐؂�ւ�����
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

// �V�[����I������
void SelectScene::SelectNext()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// �X�e�[�W�̑I��
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		m_stageSelection++;
	}
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::W) ||
		input->GetKeyTrack()->IsKeyPressed(KeyCode::Up))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		m_stageSelection--;
	}

	// ���[�v�N�����v
	m_stageSelection = UserUtility::LoopClamp(m_stageSelection, EDITOR_NUM, MAX_SAMPLE_NUM);
	m_ui->SetSelectionNum(m_stageSelection);
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Space) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Z))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);

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
