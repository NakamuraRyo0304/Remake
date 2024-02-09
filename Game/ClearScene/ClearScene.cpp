/*
 *  @File   ClearScene.cpp
 *  @Brief  �N���A�V�[���B
 *  @Date   2024-02-09
 *  @Author NakamuraRyo
 */

#include "pch.h"
// �V�X�e��
#include "Libraries/SystemDatas/DrawSprite/DrawSprite.h"
#include "ClearScene.h"

//==============================================================================
// �萔�̐ݒ�
//==============================================================================
const SimpleMath::Vector2 ClearScene::PLAY_SC_OFFSET = { 50.0f, 50.0f };	// �I�t�Z�b�g

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
		if (_input->GetKeyTrack()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene(SCENE::TITLE);
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void ClearScene::Draw()
{
	auto _states = GetSystemManager()->GetCommonStates();

	// �摜�̃��N�g���쐬
	RECT_U _rect = RECT_U(0, 0, static_cast<LONG>(GetWindowSize().x), static_cast<LONG>(GetWindowSize().y));

	// ��ʂ̊g�嗦
	SimpleMath::Vector2 _rate = GetWindowSize() / GetFullHDSize();

	// �v���C�V�[���̃X�N�V����`��
	m_sprite->DrawTexture(L"PlayPic",
		// ���W
		PLAY_SC_OFFSET * _rate,
		// �F �g�嗦
		SimpleMath::Vector4(1, 1, 1, 0.5f), SimpleMath::Vector2::One * 0.5f * _rate,
		// ���S�ʒu	��ʃT�C�Y
		SimpleMath::Vector2::Zero, _rect);

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
	m_sprite.reset();
}

//==============================================================================
// ��ʁA�f�o�C�X�ˑ��̏�����
//==============================================================================
void ClearScene::CreateWDResources()
{
	// �X�v���C�g�`��̍쐬
	m_sprite = std::make_unique<DrawSprite>();
	m_sprite->MakeSpriteBatch();

}

//==============================================================================
// �V�[�����̕ϐ��������֐�
//==============================================================================
void ClearScene::SetSceneValues()
{
	// �X�v���C�g�̐ݒ�
	m_sprite->AddTextureData(L"PlayPic", L"Resources/Textures/ScreenShot/image.dds");
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
