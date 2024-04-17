/*
 *	@File	TitleScene.cpp
 *	@Brief	�^�C�g���V�[���B
 *	@Date	2024-01-25
 *  @Author NakamuraRyo
 */

#include "pch.h"											// �v���R���p�C���ς݃w�b�_�[
#include "Game/Cameras/AdminCamera/AdminCamera.h"			// �����J����
#include "Game/TitleScene/System/UI_Title/UI_Title.h"		// ���[�U�C���^�[�t�F�[�X
#include "Libraries/SystemDatas/Timer/Timer.h"				// �^�C�}�[
#include "Game/TitleScene/System/MoveMonitor/MoveMonitor.h"	// ���j�^�[�Ď���

#include "Game/TitleScene/Objects/Sky_Title/Sky_Title.h"	// �X�J�C�h�[��
#include "Game/TitleScene/Objects/Logo/Logo.h"				// �^�C�g�����S

#include "Game/TitleScene/Objects/Bird_Title/Bird_Title.h"	// �y���M��
#include "Game/Common/Water/Water.h"						// �C
#include "Game/PlayScene/Objects/Iceberg/Iceberg.h"			// �X�R
#include "Game/Common/Island/Island.h"						// �Ǔ�

#include "TitleScene.h"										// �^�C�g���V�[��

// �萔�̐ݒ�
const float TitleScene::LOGO_FADE_IN_SPEED = 0.025f;		// ���S�t�F�[�h�C�����x
const float TitleScene::LOGO_FADE_OUT_SPEED = 0.1f;			// ���S�t�F�[�h�A�E�g���x

// �G�C���A�X�錾
using KeyCode = Keyboard::Keys;				// �L�[�R�[�h
using CameraType = AdminCamera::Type;		// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;	// �T�E���h�̃^�C�v

// �R���X�g���N�^
TitleScene::TitleScene()
	:
	IScene()												// ���N���X�̃R���X�g���N�^
{
	Debug::DrawString::GetInstance().DebugLog(L"TitleScene�̃R���X�g���N�^���Ă΂�܂����B\n");
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
	Debug::DrawString::GetInstance().DebugLog(L"TitleScene�̃f�X�g���N�^���Ă΂�܂����B\n");
	Finalize();
}

// ������
void TitleScene::Initialize()
{
	// ��ʈˑ��̏�����
	CreateWDResources();

	// �ϐ��̏�����
	SetSceneValues();

	// �{�����[���ݒ�E���ʍĐ��J�n(BGM�E����)
	auto sound = SoundManager::GetInstance();
	sound->SetVolume(XACT_WAVEBANK_AUDIOPACK_BGM_DEFAULT, 0.25f);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_BGM_DEFAULT, RepeatType::LOOP);
	sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_WAVE,     RepeatType::LOOP);
}

// �X�V
void TitleScene::Update()
{
	auto input = Input::GetInstance();
	auto sound = SoundManager::GetInstance();

	// �\�t�g�I��
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		ChangeScene(SCENE::EXIT);
	}

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �^�C�}�[�̍X�V
		m_timer->Update();

		// ���j�^�[�Ď��҂̍X�V
		m_moveMonitor->Update();

		// UI�̍X�V
		m_ui->Update();

		// �������͂�����΃^�C�}�[���ăX�^�[�g
		if (m_ui->IsAnything() || m_moveMonitor->IsMove())
		{
			m_timer->ReStart();
		}

		// �^�C�}�[���w�莞�ԂɒB��������s����
		if (m_timer->Alarm())
		{
			// ���S���t�F�[�h�A�E�g������
			m_logo->SetColor(UserUtility::Lerp(
				m_logo->GetColor(), SimpleMath::Vector4::One * QUARTER, LOGO_FADE_OUT_SPEED)
			);
		}
		else
		{
			// ���S���t�F�[�h�C��������
			m_logo->SetColor(UserUtility::Lerp(
				m_logo->GetColor(), SimpleMath::Vector4::One, LOGO_FADE_IN_SPEED)
			);
		}

		// �I������炷
		if (input->GetKeyTrack()->IsKeyPressed(KeyCode::W)  || input->GetKeyTrack()->IsKeyPressed(KeyCode::S) ||
			input->GetKeyTrack()->IsKeyPressed(KeyCode::Up) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Down))
		{
			sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_SELECT, RepeatType::ONCE);
		}
		// �X�y�[�X����������J�ڂ���
		if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Space) || input->GetKeyTrack()->IsKeyPressed(KeyCode::Z))
		{
			m_ui->GetSelection() == UI_Title::Start ? ChangeScene(SCENE::SELECT) : ChangeScene(SCENE::EXIT);
			sound->PlaySound(XACT_WAVEBANK_AUDIOPACK_SE_CLICK, RepeatType::ONCE);
		}
	}

	// �J�����̍X�V
	m_adminCamera->Update();

	// �X�J�C���̍X�V(�J�����𒆐S�ɃX�J�C�����Z�b�g����@�`��؂��h��)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// �g���̍X�V
	m_birdTitle->Update();

	// �X�R�̍X�V
	m_iceberg->Update();
}

// �`��
void TitleScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix view = m_adminCamera->GetView();
	SimpleMath::Matrix projection = m_adminCamera->GetProjection();

	// ��̕`��
	m_sky->Draw(context, *states, view, projection);

	// �g���̕`��
	m_birdTitle->Draw(context, *states, view, projection);

	// �X�R�̕`��
	m_iceberg->Draw(context, *states, view, projection);

	// �Ǔ��̕`��
	m_island->Draw(context, *states, view, projection);

	// ���̕`��
	m_water->Draw(view, projection);

	// UI�̕\��
	m_ui->Draw();

	// �^�C�g�����S�̕\��
	m_logo->Draw();


	// �f�o�b�O�`��
#if _DEBUG
	//auto _grid = GetSystemManager()->GetGridFloor();
	//_grid->Draw(*_states, _view, _projection, Colors::Green);
	//DebugDraw(*_states);
#endif
}

// �I��
void TitleScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_ui.reset();
	m_birdTitle.reset();
	m_water.reset();
	m_logo.reset();
	m_timer.reset();
	m_iceberg.reset();
	m_island.reset();
	m_moveMonitor.reset();
}

// ��ʁA�f�o�C�X�ˑ��̏�����
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

	// �^�C�}�[�쐬(10�b�ɐݒ�)
	m_timer = std::make_unique<Timer>(Timer::Mode::limited, 10.0f);

	// �X�R�쐬
	m_iceberg = std::make_unique<Iceberg>(SimpleMath::Vector3(-20.0f, -25.0f, -50.0f), 10.0f, 0.0f);

	// �Ǔ��쐬
	m_island = std::make_unique<Island>(SimpleMath::Vector3(5.0f, -6.0f, 10.0f), 4.0f, 0.0f);

	// ���j�^�[�Ď��ҍ쐬
	m_moveMonitor = std::make_unique<MoveMonitor>();
}

// �V�[�����̕ϐ��������֐�
void TitleScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Title_FixedPoint);
	m_adminCamera->SetActive(true);

	// ���̏�����
	m_water->Create(L"Resources/Textures/ShaderTex/water.png");

	// ���S�̏�����
	m_logo->Initialize({ 150.0f ,120.0f }, SimpleMath::Vector4::Zero, { 2,2 });

	// �^�C�}�[���J�n
	m_timer->Start();

	// �Ǔ��̍s����쐬
	m_island->CreateWorldMatrix();
}

// �f�o�b�O�`��
void TitleScene::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// �����̕`��
	string.DrawFormatString(states, { 0,0 },  Colors::DarkGreen, L"TitleScene");
	string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", m_timer->GetCount());
}