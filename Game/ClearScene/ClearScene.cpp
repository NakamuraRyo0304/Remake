/*
 *  @File   ClearScene.cpp
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Game/ClearScene/System/MomentCanv/MomentCanv.h"
#include "ClearScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================

//==============================================================================
// �G�C���A�X�錾
//==============================================================================
using KeyCode = Keyboard::Keys;							// �L�[�R�[�h
using RepeatType = SoundManager::SE_MODE;				// �T�E���h�̃^�C�v
using MouseClick = Mouse::ButtonStateTracker;			// �}�E�X�̃N���b�N

//==============================================================================
// �R���X�g���N�^
//==============================================================================
ClearScene::ClearScene()
	: IScene()						// ���N���X�̃R���X�g���N�^
{
	Debug::DrawString::GetInstance().DebugLog(L"ClearScene�̃R���X�g���N�^���Ă΂�܂����B\n");
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
ClearScene::~ClearScene()
{
}

//==============================================================================
// ����������
//==============================================================================
void ClearScene::Initialize()
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
void ClearScene::Update()
{
	auto _input = Input::GetInstance();
	auto _key = Keyboard::Get().GetState();

	// �\�t�g�I��
	if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Escape)) { ChangeScene(SCENE::SELECT); }

	// �V�[���J��
	if (IsCanUpdate())
	{
		// ���[�����g�L�����o�X�̍X�V
		m_momentCanv->Update();

		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene(SCENE::SELECT);
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void ClearScene::Draw()
{
	// �����_�����O�ϐ����擾
	auto _states = GetSystemManager()->GetCommonStates();

	// ���[�����g�L�����o�X�̃��N�g�Ɗg�嗦�A���S�ʒu
	RECT_U _rectMC =
		RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));
	SimpleMath::Vector2 _rateMC = GetWindowSize() / GetFullHDSize();
	SimpleMath::Vector2 _originMC = GetWindowSize() * _rateMC * 0.5f;


	// ���[�����g�L�����o�X�̕`��
	m_momentCanv->Draw(_rateMC, SimpleMath::Vector4::One,
		SimpleMath::Vector2::One * 0.5f, _originMC, _rectMC);

	// �f�o�b�O�`��
#ifdef _DEBUG
	DebugDraw(*_states);
#endif
}

//==============================================================================
// �I������
//==============================================================================
void ClearScene::Finalize()
{
	m_momentCanv.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void ClearScene::CreateWDResources()
{
	// ���[�����g�L�����o�X�̍쐬
	m_momentCanv = std::make_unique<MomentCanv>();

}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void ClearScene::SetSceneValues()
{
	// ���[�����g�L�����o�X�̏�����
	m_momentCanv->Initialize();

}

//==============================================================================
// �f�o�b�O�`��
//==============================================================================
void ClearScene::DebugDraw(CommonStates& states)
{
	auto& _string = Debug::DrawString::GetInstance();
	auto& _time = DX::StepTimer::GetInstance();

	// �����̕`��
	_string.DrawFormatString(states, { 0,0 }, Colors::DarkGreen, L"ClearScene");
	_string.DrawFormatString(states, { 0,25 }, Colors::DarkGreen, L"ScreenSize::%.2f | %.2f", GetWindowSize().x, GetWindowSize().y);
	_string.DrawFormatString(states, { 0,50 }, Colors::DarkGreen, L"FPS::%d", _time.GetFramesPerSecond());
	_string.DrawFormatString(states, { 0,75 }, Colors::DarkGreen, L"Timer::%.2f", _time.GetTotalSeconds());
}
