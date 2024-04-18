/*
 *	@File	Editor.cpp
 *	@Brief	�G�f�B�^�B
 *	@Date	2024-01-26
 *  @Author NakamuraRyo
 */

#include "pch.h"													// �v���R���p�C���ς݃w�b�_�[
#include "Game/Cameras/AdminCamera/AdminCamera.h"					// �����J����
#include "Game/Editor/System/UI_Editor/UI_Editor.h"					// ���[�U�C���^�[�t�F�[�X

#include "Game/Common/BlockManager/BlockManager.h"					// �u���b�N�Ǘ��N���X
#include "Game/Editor/System/EditorCollision/EditorCollision.h"		// �G�f�B�^�����蔻��
#include "Game/Common/WorldMouse/WorldMouse.h"						// �R�c�ϊ���̃}�E�X�V�X�e��
#include "Game/Common/CursorObject/CursorObject.h"					// �R�c�ϊ���̃}�E�X�I�u�W�F�N�g
#include "Game/Editor/System/EditorGrids/EditorGrids.h"				// �G�f�B�^�p�O���b�h��

#include "Editor.h"													// �G�f�B�^�V�[��

// �G�C���A�X�錾
using KeyCode = Keyboard::Keys;				// �L�[�R�[�h
using CameraType = AdminCamera::Type;		// �J�����̃^�C�v
using RepeatType = SoundManager::SE_MODE;	// �T�E���h�̃^�C�v
using BN = UI_Editor::BUTTON_NAME;			// �{�^���̖��O

// �R���X�g���N�^
Editor::Editor()
	:
	BaseScene(),						// ���N���X�̃R���X�g���N�^
	m_selectionID(ID::Obj_Flozen)		// �����͕X����ݒ�
{
	Debug::DrawString::GetInstance().DebugLog(L"Editor�̃R���X�g���N�^���Ă΂�܂����B\n");
}

// �f�X�g���N�^
Editor::~Editor()
{
	Debug::DrawString::GetInstance().DebugLog(L"Editor�̃f�X�g���N�^���Ă΂�܂����B\n");
	Finalize();
}

// ������
void Editor::Initialize()
{
	// ��ʈˑ��̏�����
	CreateWDResources();

	// �ϐ��̏�����
	SetSceneValues();
}

// �X�V
void Editor::Update()
{
	auto input = Input::GetInstance();

	// �Z���N�g�ɖ߂�
	if (input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape))
	{
		ChangeScene(SCENE::SELECT);
	}

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
			m_blockManager->ReLoad(m_blockManager->GetStagePath());
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

// �`��
void Editor::Draw()
{
	// �����_�����O�ϐ����擾
	auto states = GetSystemManager()->GetCommonStates();
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// �J�����̃}�g���N�X���擾
	SimpleMath::Matrix view = m_adminCamera->GetView();
	SimpleMath::Matrix projection = m_adminCamera->GetProjection();

	// �u���b�N�̕`��
	m_blockManager->Draw(context, *states, view, projection);

	// ���[���h�}�E�X�̕`��֘A���X�V
	m_worldMouse->Draw(view, projection);

	// �J�[�\���I�u�W�F�N�g�̕`��
	m_cursorObject->Draw(context, *states, view, projection);

	// �O���b�h�̕`��
	for (int y = 0; y < 5; y++)
	{
		m_editorGrids->Draw(*states, SimpleMath::Matrix::Identity, view, projection, Colors::LightBlue,
			{ 4.5f, static_cast<float>(y) - 0.5f,4.5f });
	}
	m_editorGrids->Draw(*states, SimpleMath::Matrix::Identity, view, projection, Colors::Red,
		{ 4.5f, m_worldMouse->GetPosition().y - 0.5f,4.5f });

#if _DEBUG
	DebugDraw(*states);
#endif

	// UI�̕`��(�őO�ʂɕ`��)
	m_ui->Draw();
}

// �I������
void Editor::Finalize()
{
	m_adminCamera.reset();
	m_blockManager.reset();
	m_ui.reset();
	m_editorCollision.reset();
	m_worldMouse.reset();
	m_cursorObject.reset();
	m_editorGrids.reset();
}

// ��ʁA�f�o�C�X�ˑ��̏�����
void Editor::CreateWDResources()
{
	// �Q�[���J�����쐬
	m_adminCamera = std::make_unique<AdminCamera>(GetWindowSize());

	// �u���b�N�}�l�[�W���쐬
	m_blockManager = std::make_unique<BlockManager>(L"Resources/Stages/flat.json");
	m_blockManager->SetPlay(false);

	// UI�쐬
	m_ui = std::make_unique<UI_Editor>(GetWindowSize(), FULL_HD);

	// �G�f�B�^�R���W�����쐬
	m_editorCollision = std::make_unique<EditorCollision>();

	// ���[���h�}�E�X�쐬
	m_worldMouse = std::make_unique<WorldMouse>();

	// �J�[�\���I�u�W�F�N�g�쐬
	m_cursorObject = std::make_unique<CursorObject>();

	// �O���b�h�쐬
	m_editorGrids = std::make_unique<EditorGrids>(10, 10);
}

// �V�[�����̕ϐ��������֐�
void Editor::SetSceneValues()
{
	// �J�����̏����ݒ�-����
	m_adminCamera->SetType(CameraType::Editor_Moving);
	m_adminCamera->SetActive(true);
	m_adminCamera->SetInterpolation(false);

	// ID�̏�����
	m_selectionID = ID::Obj_Flozen;

	// �u���b�N�̏�����
	m_blockManager->SetPlay(false);
	m_blockManager->Initialize();

	// �G�f�B�^���[�h�ɂ���
	m_worldMouse->ToEditMode();

	// ���W��ݒ�
	m_cursorObject->SetCursorPosition(m_worldMouse->GetPosition());
}

// �f�o�b�O�`��
void Editor::DebugDraw(CommonStates& states)
{
	auto& string = Debug::DrawString::GetInstance();
	auto& timer = DX::StepTimer::GetInstance();

	// �����̕`��
	string.DrawFormatString(states, { 0,0 },  Colors::Black, L"Editor");
	string.DrawFormatString(states, { 0,25 }, Colors::Black, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	string.DrawFormatString(states, { 0,50 }, Colors::Black, L"FPS::%d", timer.GetFramesPerSecond());
	string.DrawFormatString(states, { 0,75 }, Colors::Black, L"Timer::%.2f", timer.GetTotalSeconds());
	string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	string.DrawFormatString(states, { 0,100 }, Colors::Black, L"Forward::%.2f,%.2f,%.2f",
		m_adminCamera->GetView().Forward().x, m_adminCamera->GetView().Forward().y, m_adminCamera->GetView().Forward().z);
	string.DrawFormatString(states, { 0,125 }, Colors::Black, L"WorldMouse::%.2f,%.2f,%.2f",
		m_editorCollision->GetPosition().x, m_editorCollision->GetPosition().y, m_editorCollision->GetPosition().z);
	string.DrawFormatString(states, { 0,150 }, Colors::Black, L"AddPosition::%.2f,%.2f",
		m_ui->GetAddPosition().x, m_ui->GetAddPosition().y);
}

// �I�u�W�F�N�g���Z�b�g����
void Editor::SetDrawObject()
{
	if (m_ui->IsClickButton(BN::Flozen_bn))	m_selectionID = ID::Obj_Flozen;	// �X��
	if (m_ui->IsClickButton(BN::Cloud_bn))	m_selectionID = ID::Obj_Cloud;	// �_
	if (m_ui->IsClickButton(BN::Coin_bn))	m_selectionID = ID::Obj_Coin;	// �R�C��
	if (m_ui->IsClickButton(BN::Air_bn))	m_selectionID = ID::Obj_Air;	// �G�A
	if (m_ui->IsClickButton(BN::Player_bn))	m_selectionID = ID::Obj_Player;	// �v���C��
	if (m_ui->IsClickButton(BN::Goal_bn))	m_selectionID = ID::Obj_Goal;	// �S�[��
	if (m_ui->IsClickButton(BN::Spike_bn))	m_selectionID = ID::Obj_Spike;	// ��
	if (m_ui->IsClickButton(BN::Lift_bn))	m_selectionID = ID::Obj_Lift;	// ���t�g
}

// �R���W�����̍X�V
void Editor::UpdateCollisions(ID id)
{
	for (auto& obj : m_blockManager->GetAirs())		// �G�A�[�i����p�u���b�N�j
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetFlozens())	// �X���u���b�N
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetClouds())	// �_�M�~�b�N
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetCoins())	// �R�C���I�u�W�F�N�g
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetPlayers())	// �v���C���I�u�W�F�N�g
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetGoals())	// �S�[���|�C���g
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetSpikes())	// ���G�l�~�[
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
	for (auto& obj : m_blockManager->GetLifts())	// ���t�g�u���b�N
		m_editorCollision->Update(UserUtility::UniqueCast<IGameObject>(obj), id);
}
