/*
 *	@File	Editor.cpp
 *	@Brief	�G�f�B�^�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
// �I�u�W�F�N�g
#include "Game/Common/BlockManager/BlockManager.h"

#include "Editor.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v
using HitKinds = BlockManager::BlockKinds;				// �u���b�N�̎��

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Editor::Editor()
	: IScene()				// ���N���X�̃R���X�g���N�^
{
	Debug::DrawString::GetInstance().DebugLog(L"Editor�̃R���X�g���N�^���Ă΂�܂����B\n");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Editor::~Editor()
{
}

//==============================================================================
// ����������
//==============================================================================
void Editor::Initialize()
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
void Editor::Update()
{
	auto _input = Input::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// �V�[���J��
	if (IsCanUpdate())
	{
	}

	// �J�����̍X�V
	m_adminCamera->Update();

	// �u���b�N�̍X�V
	m_blockManager->Update();
}

//==============================================================================
// �`�揈��
//==============================================================================
void Editor::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix  _projection = m_adminCamera->GetProjection();

	// �u���b�N�̕`��
	m_blockManager->Draw(*_states, _view, _projection);

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
void Editor::Finalize()
{
	m_adminCamera.reset();
	m_blockManager.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void Editor::CreateWDResources()
{
	// �f�t�H���g�J�����ݒ�
	GetSystemManager()->GetCamera()->CreateProjection(GetWindowSize(), GetDefaultCameraAngle());

	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// �u���b�N�}�l�[�W��
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void Editor::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void Editor::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 }, Colors::Yellow, L"Editor");
	_string.DrawFormatString(states, { 0,25 }, Colors::Yellow, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Yellow, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Yellow, L"Timer::%.2f", _time.GetTotalSeconds());
}