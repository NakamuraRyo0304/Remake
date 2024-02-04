/*
 *	@File	PlayScene.cpp
 *	@Brief	�v���C�V�[���B
 *	@Date	2024-01-30
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/PlayScene/System/StageCollision/StageCollision.h"
//#include "Game/PlayScene/System/UI_Title/UI_Title.h"
// �I�u�W�F�N�g
#include "Game/PlayScene/Objects/Sky_Play/Sky_Play.h"
#include "Game/PlayScene/Objects/Player/Player.h"
#include "Game/Common/CursorObject/CursorObject.h"
#include "PlayScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================


//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v
using MouseClick = Mouse::ButtonStateTracker;			// �}�E�X�̃N���b�N

//==============================================================================
// �R���X�g���N�^
//==============================================================================
PlayScene::PlayScene(const int& number)
	: IScene()					// ���N���X�̃R���X�g���N�^
	, m_stageNumber{ number }	// �X�e�[�W�ԍ�
{
	Debug::DrawString::GetInstance().DebugLog(L"PlayScene�̃R���X�g���N�^���Ă΂�܂����B\n");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
PlayScene::~PlayScene()
{
}

//==============================================================================
// ����������
//==============================================================================
void PlayScene::Initialize()
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
void PlayScene::Update()
{
	auto _input = Input::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// �V�[���J��
	if (IsCanUpdate())
	{
		// �ǐՃp�X��ǉ�
		if (_input->GetMouseTrack()->leftButton == MouseClick::PRESSED)
		{
			SimpleMath::Vector3 _followPath = m_worldMouse->GetPosition();
			_followPath.y = m_player->GetPosition().y;
			m_player->PushBackFollowPath(_followPath);
		}

		// �S�[��������V�[���J�� ���ŃZ���N�g��
		if (m_blockManager->IsArrived())
		{
			m_adminCamera->SetEasing(true);// ��ԃ��[�h�ɂ���
			if (m_adminCamera->GetType() != CameraType::Select1_Floating)
			{
				m_adminCamera->SetType(CameraType::Select1_Floating);
			}
			ChangeScene(SCENE::SELECT);
		}

		// ���񂾂�ēǂݍ���
		if (m_player->IsDeath())
		{
			ChangeScene(SCENE::PLAY);
		}
	}

#ifdef _DEBUG

	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
	{
		m_player->ResetGoalPosition();
		m_player->SetPosition({ 1.0f,0.5f,1.0f });
	}

#endif

	// �J�����̍X�V
	m_adminCamera->Update();

	// ���[���h�}�E�X�̍X�V
	m_worldMouse->Update();

	// �J�[�\���I�u�W�F�N�g���X�V
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
	m_cursorObject->Update();

	// �X�J�C���̍X�V(�J�����𒆐S�ɃX�J�C�����Z�b�g����@�`��؂��h��)
	m_sky->SetPosition(m_adminCamera->GetPosition());
	m_sky->Update();

	// �u���b�N�̍X�V
	m_blockManager->Update();

	// �v���C���[�̍X�V
	m_player->Update();

	// �����蔻��̍X�V
	m_stageCollision->Update(m_player.get(), m_blockManager.get());
}

//==============================================================================
// �`�揈��
//==============================================================================
void PlayScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// ���[���h�}�E�X�̕`��
	m_worldMouse->Draw(_view, _projection);

	// �J�[�\���I�u�W�F�N�g�̕`��
	m_cursorObject->Draw(_context, *_states, _view, _projection);

	// ��̕`��
	m_sky->Draw(_context, *_states, _view, _projection);

	// �u���b�N�̕`��
	m_blockManager->Draw(_context, *_states, _view, _projection);

	// �v���C���[�̕`��
	m_player->Draw(_context, *_states, _view, _projection);

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
void PlayScene::Finalize()
{
	m_adminCamera.reset();
	m_sky.reset();
	m_player.reset();
	m_worldMouse.reset();
	m_blockManager.reset();
	m_stageCollision.reset();
	m_cursorObject.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void PlayScene::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// �X�J�C���I�u�W�F�N�g�쐬
	m_sky = std::make_unique<Sky_Play>();

	// �v���C���[�쐬
	m_player = std::make_unique<Player>();

	// ���[���h�}�E�X�쐬
	m_worldMouse = std::make_unique<WorldMouse>();

	// �u���b�N�}�l�[�W���쐬
	m_blockManager = std::make_unique<BlockManager>(GetStagePath());

	// �X�e�[�W�R���W�����쐬
	m_stageCollision = std::make_unique<StageCollision>();

	// �J�[�\���I�u�W�F�N�g�쐬
	m_cursorObject = std::make_unique<CursorObject>();
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void PlayScene::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetEasing(false);	// ��Ԃ�؂�

	// �u���b�N�̏����ݒ�
	m_blockManager->SetPlay(true);
	m_blockManager->Initialize();

	// �v���C���[�̍��W��Ԃ�
	m_player->SetPosition(m_blockManager->GetPlayerPosition());

	// �J�[�\���I�u�W�F�N�g�Ƀ��[���h�}�E�X�̍��W��ݒ�
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void PlayScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 },  Colors::Black, L"PlayScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"StageNum::%.d", m_stageNumber);
	_string.DrawFormatString(states, { 0,125 }, Colors::Black, L"PlayerPos::%.2f,%.2f,%.2f",
		m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	_string.DrawFormatString(states, { 0,150 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_worldMouse->GetPosition().x, m_worldMouse->GetPosition().y, m_worldMouse->GetPosition().z);
	_string.DrawFormatString(states, { 0,175 }, Colors::Black, L"SettingPath::%d", m_player->GetGoalPoints().size());
	_string.DrawFormatString(states, { 0,200 }, Colors::Black, L"HaveCoinNum::%d", m_player->GetCoinNum());
}

//==============================================================================
// �X�e�[�W�̃p�X���擾����
//==============================================================================
const wchar_t* PlayScene::GetStagePath()
{
	switch (m_stageNumber)
	{
	case 1:
		return L"Resources/Stages/sample1.json";
	case 2:
		return L"Resources/Stages/sample2.json";
	case 3:
		return L"Resources/Stages/sample3.json";


	default:
		return L"Resources/Stages/sample1.json";
	}
}
