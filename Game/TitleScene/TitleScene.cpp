/*
 *	@File	TitleScene.cpp
 *	@Brief	�^�C�g���V�[���B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/TitleScene/System/UI_Title/UI_Title.h"
// �I�u�W�F�N�g
#include "Game/TitleScene/Objects/Sky_Title/Sky_Title.h"
#include "Game/TitleScene/Objects/Bird_Title/Bird_Title.h"
#include "Game/Common/Water/Water.h"
#include "Game/TitleScene/Objects/Logo/Logo.h"
#include "TitleScene.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v

//==============================================================================
// �R���X�g���N�^
//==============================================================================
TitleScene::TitleScene()
	: IScene()				// ���N���X�̃R���X�g���N�^
{
	Debug::DrawString::GetInstance().DebugLog(L"TitleScene�̃R���X�g���N�^���Ă΂�܂����B\n");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
TitleScene::~TitleScene()
{
}

//==============================================================================
// ����������
//==============================================================================
void TitleScene::Initialize()
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
void TitleScene::Update()
{
	auto _input = Input::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::EXIT); }

	// UI�̍X�V
	m_ui->Update();

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �X�y�[�X����������J�ڂ���
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			m_ui->GetSelection() == UI_Title::Start ? ChangeScene(SCENE::SELECT) : ChangeScene(SCENE::EXIT);
		}
	}

	// �J�����̍X�V
	m_adminCamera->Update();

	// �X�J�C���̍X�V(�J�����𒆐S�ɃX�J�C�����Z�b�g����@�`��؂��h��)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// �g���̍X�V
	m_birdTitle->Update();
}

//==============================================================================
// �`�揈��
//==============================================================================
void TitleScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// ��̕`��
	m_sky->Draw(_context, *_states, _view, _projection);

	// �g���̕`��
	m_birdTitle->Draw(_context, *_states, _view, _projection);

	// ���̕`��
	m_water->Draw(_view, _projection);

	// UI�̕\��
	m_ui->Draw();


	// �f�o�b�O�`��
#if _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif
}

//==============================================================================
// �I������
//==============================================================================
void TitleScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_ui.reset();
	m_birdTitle.reset();
	m_water.reset();
	m_logo.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void TitleScene::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// �X�J�C���I�u�W�F�N�g�쐬
	m_sky = std::make_unique<Sky_Title>();

	// UI�쐬
	m_ui = std::make_unique<UI_Title>(GetWindowSize(), GetFullHDSize());

	// �g���I�u�W�F�N�g�쐬
	m_birdTitle = std::make_unique<Bird_Title>();

	// ���쐬
	m_water = std::make_unique<Water>();

	// ���S�쐬
	m_logo = std::make_unique<Logo>(GetWindowSize() / GetFullHDSize());
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void TitleScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);

	// ���̏�����
	m_water->Create(L"Resources/Textures/ShaderTex/water.png");

	// ���S�̏�����
	m_logo->Initialize();
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void TitleScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 },  Colors::DarkGreen, L"TitleScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", _time.GetTotalSeconds());
}