/*
 *	@File	Editor.cpp
 *	@Brief	�G�f�B�^�B
 *	@Date	2023-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/Cameras/AdminCamera/AdminCamera.h"
#include "Game/Editor/System/UI_Editor/UI_Editor.h"
#include "Game/Editor/System/EditorCollision/EditorCollision.h"
#include "Game/Common/WorldMouse/WorldMouse.h"
#include "Libraries/UserUtility.h"
// �I�u�W�F�N�g
#include "Game/Common/BlockManager/BlockManager.h"
#include "Game/Common/CursorObject/CursorObject.h"

#include "Editor.h"

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using CameraType = AdminCamera::Type;					// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v
using BN = UI_Editor::BUTTON_NAME;						// �{�^���̖��O

//==============================================================================
// �R���X�g���N�^
//==============================================================================
Editor::Editor()
	: IScene()						// ���N���X�̃R���X�g���N�^
	, m_selectionID{ ID::Obj_Flozen }	// �����͍���ݒ�
{
	Debug::DrawString::GetInstance().DebugLog(L"Editor�̃R���X�g���N�^���Ă΂�܂����B\n");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
Editor::~Editor()
{
	Finalize();
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
}

//==============================================================================
// �X�V����
//==============================================================================
void Editor::Update()
{
	auto _input = Input::GetInstance();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// UI�̍X�V
	m_ui->Update();

	// �V�[���J��
	if (IsCanUpdate())
	{
		if (m_ui->IsClickButton(BN::LoadFile))
		{
			m_blockManager->ReLoad();
			m_adminCamera->SetType(CameraType::Editor_Moving);
		}
		if (m_ui->IsClickButton(BN::WriteFile))
		{
			m_blockManager->OutputStage();
		}
	}

	// �u���b�N�̍X�V
	m_blockManager->Update();

	// �J�����̍X�V
	m_adminCamera->Update();

	// �I�u�W�F�N�g���Z�b�g����
	SetDrawObject();

	// ���[���h�}�E�X���X�V
	m_worldMouse->Update();

	// ���[���h�}�E�X�̍��W���R���W�����E���o���I�u�W�F�N�g�ɐݒ�
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
	m_editorCollision->SetPosition(m_worldMouse->GetPosition());

	// �J�[�\���I�u�W�F�N�g���X�V
	m_cursorObject->Update();

	// �G�f�B�^�R���W�����̍X�V
	UpdateCollisions(m_selectionID);
}

//==============================================================================
// �`�揈��
//==============================================================================
void Editor::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();
	auto _context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix _view = m_adminCamera->GetView();
	SimpleMath::Matrix _projection = m_adminCamera->GetProjection();

	// �u���b�N�̕`��
	m_blockManager->Draw(_context, *_states, _view, _projection);

	// ���[���h�}�E�X�̕`��֘A���X�V
	m_worldMouse->Draw(_view, _projection);

	// �J�[�\���I�u�W�F�N�g�̕`��
	m_cursorObject->Draw(_context, *_states, _view, _projection);

	// �f�o�b�O�`��
#if _DEBUG
	auto _grid = GetSystemManager()->GetGridFloor();
	_grid->Draw(*_states, _view, _projection, Colors::Green);
	DebugDraw(*_states);
#endif

	// UI�̕`��(�őO�ʂɕ`��)
	m_ui->Draw();
}

//==============================================================================
// �I������
//==============================================================================
void Editor::Finalize()
{
	m_adminCamera.reset();
	m_blockManager.reset();
	m_ui.reset();
	m_editorCollision.reset();
	m_worldMouse.reset();
	m_cursorObject.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void Editor::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// �u���b�N�}�l�[�W���쐬
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/sample1.json");
	m_blockManager->SetPlay(false);

	// UI�쐬
	m_ui = std::make_unique<UI_Editor>(GetWindowSize(),GetFullHDSize());

	// �G�f�B�^�R���W�����쐬
	m_editorCollision = std::make_unique<EditorCollision>();

	// ���[���h�}�E�X�쐬
	m_worldMouse = std::make_unique<WorldMouse>();

	// �J�[�\���I�u�W�F�N�g�쐬
	m_cursorObject = std::make_unique<CursorObject>();
}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void Editor::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetInterpolation(false);

	// ID�����ɐݒ�
	m_selectionID = ID::Obj_Flozen;

	// �u���b�N�̏�����
	m_blockManager->Initialize();

	// �G�f�B�^���[�h�ɂ���
	m_worldMouse->ToEditMode();

	// ���W��ݒ�
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void Editor::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 },  Colors::Black, L"Editor");
	_string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", _time.GetTotalSeconds());
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	_string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	_string.DrawFormatString(states, { 0,125 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_editorCollision->GetPosition().x, m_editorCollision->GetPosition().y, m_editorCollision->GetPosition().z);
	_string.DrawFormatString(states, { 0,150 }, Colors::Black, L"AddPosition::%.2f,%.2f",
		m_ui->GetAddPosition().x, m_ui->GetAddPosition().y);
}

//==============================================================================
// �R���W�����̍X�V
//==============================================================================
void Editor::UpdateCollisions(ID id)
{
	//////////////////////////////////////////
	///            �������ȗ�              ///
	//////////////////////////////////////////

	for (auto& obj : m_blockManager->GetAirBlock())		// �G�A�I�u�W�F�N�g
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetFlozenBlock())	// ���u���b�N
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetCloudBlock())	// �_�M�~�b�N
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetCoinBlock())	// �R�C���I�u�W�F�N�g
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetPlayerBlock())	// �v���C���I�u�W�F�N�g
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetGoalObject())	// �S�[���|�C���g
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
	for (auto& obj : m_blockManager->GetSpikeEnemy())	// ���G�l�~�[
	{
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	}
}

//==============================================================================
// �I�u�W�F�N�g���Z�b�g����
//==============================================================================
void Editor::SetDrawObject()
{
	if (m_ui->IsClickButton(BN::Flozen_bn))	m_selectionID = ID::Obj_Flozen;	// ��
	if (m_ui->IsClickButton(BN::Cloud_bn))	m_selectionID = ID::Obj_Cloud;	// �_
	if (m_ui->IsClickButton(BN::Coin_bn))	m_selectionID = ID::Obj_Coin;	// �R�C��
	if (m_ui->IsClickButton(BN::Air_bn))	m_selectionID = ID::Obj_Air;	// �G�A
	if (m_ui->IsClickButton(BN::Player_bn))	m_selectionID = ID::Obj_Player;	// �v���C��
	if (m_ui->IsClickButton(BN::Goal_bn))	m_selectionID = ID::Obj_Goal;	// �S�[��
	if (m_ui->IsClickButton(BN::Spike_bn))	m_selectionID = ID::Obj_Spike;	// ��
}
