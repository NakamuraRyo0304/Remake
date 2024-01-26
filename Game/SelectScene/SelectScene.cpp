/*
 *	@File	SelectScene.cpp
 *	@Brief	�Z���N�g�V�[���B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
 // ���C�u����
#include "Libraries/SystemDatas/Button/Button.h"
#include "Libraries/SystemDatas/XController/XController.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/SelectScene/System/UI_Select/UI_Select.h"
// �I�u�W�F�N�g

#include "SelectScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================


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
	//auto _se = SoundManager::GetInstance();
	//auto _xcon = XController::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UI�̍X�V
	m_ui->Update();

	// �V�[���J��
	if (IsCanUpdate())
	{
		// UI���̏������s��

	}

	// �J�����̍X�V
	m_adminCamera->Update();

}

//==============================================================================
// �`�揈��
//==============================================================================
void SelectScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix  _projection = m_adminCamera->GetProjection();


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
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void SelectScene::CreateWDResources()
{
	// �f�t�H���g�J�����ݒ�
	GetSystemManager()->GetCamera()->CreateProjection(GetWindowSize(), GetDefaultCameraAngle());

	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// UI�쐬
	m_ui = std::make_unique<UI_Select>(GetWindowSize(), GetFullHDSize());
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void SelectScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void SelectScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 }, Colors::Black, L"SelectScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
}